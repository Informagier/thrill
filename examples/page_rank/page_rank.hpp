/*******************************************************************************
 * examples/page_rank/page_rank.hpp
 *
 * Part of Project Thrill - http://project-thrill.org
 *
 * Copyright (C) 2016 Timo Bingmann <tb@panthema.net>
 *
 * All rights reserved. Published under the BSD-2 license in the LICENSE file.
 ******************************************************************************/

#pragma once
#ifndef THRILL_EXAMPLES_PAGE_RANK_PAGE_RANK_HEADER
#define THRILL_EXAMPLES_PAGE_RANK_PAGE_RANK_HEADER

#include <thrill/api/cache.hpp>
#include <thrill/api/collapse.hpp>
#include <thrill/api/generate.hpp>
#include <thrill/api/groupby_index.hpp>
#include <thrill/api/max.hpp>
#include <thrill/api/print.hpp>
#include <thrill/api/reduce_to_index.hpp>
#include <thrill/api/size.hpp>
#include <thrill/api/zip.hpp>
#include <thrill/common/logger.hpp>

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace thrill; // NOLINT

namespace examples {

static const bool debug = false;

static const double dampening = 0.85;

using PageId = std::size_t;
using Rank = double;

//! A pair (page source, page target)
struct PagePageLink {
    PageId src, tgt;

    friend std::ostream& operator << (std::ostream& os, const PagePageLink& a) {
        return os << '(' << a.src << '>' << a.tgt << ')';
    }
} THRILL_ATTRIBUTE_PACKED;

//! A pair (page, rank)
struct PageRankPair {
    PageId page;
    Rank   rank;

    friend std::ostream& operator << (std::ostream& os, const PageRankPair& a) {
        return os << '(' << a.page << '|' << a.rank << ')';
    }
} THRILL_ATTRIBUTE_PACKED;

using OutgoingLinks = std::vector<PageId>;
using OutgoingLinksRank = std::pair<std::vector<PageId>, Rank>;

template <typename InStack>
auto PageRank(const DIA<std::string, InStack>&input_links, size_t iterations) {

    api::Context& ctx = input_links.context();

    auto input =
        input_links
        .Map([](const std::string& input) {
                 // parse "source\ttarget\n" lines
                 char* endptr;
                 unsigned long src = std::strtoul(input.c_str(), &endptr, 10);
                 die_unless(endptr && *endptr == '\t' && "Could not parse src tgt line");
                 unsigned long tgt = std::strtoul(endptr + 1, &endptr, 10);
                 die_unless(endptr && *endptr == 0 && "Could not parse src tgt line");
                 return PagePageLink { src, tgt };
             });

    size_t num_pages =
        input
        .Map([](const PagePageLink& ppl) { return std::max(ppl.src, ppl.tgt); })
        .Max() + 1;

    sLOG1 << "num_pages" << num_pages;
    mem::malloc_tracker_print_status();

    // aggregate all outgoing links of a page in this format: by index
    // ([linked_url, linked_url, ...])

    // group outgoing links from input file

    auto links = input.template GroupByIndex<OutgoingLinks>(
        [](const PagePageLink& p) { return p.src; },
        [num_pages, all = std::vector < PageId > ()](auto& r, const PageId&) mutable {
            all.clear();
            while (r.HasNext()) {
                all.push_back(r.Next().tgt);
            }
            return all;
        },
        num_pages).Cache();

    // initialize all ranks to 1.0: (url, rank)

    DIA<Rank> ranks = Generate(
        ctx, [](const size_t&) { return (Rank)1.0; }, num_pages).Collapse();

    // do iterations
    for (size_t iter = 0; iter < iterations; ++iter) {
        LOG1 << "iteration " << iter;

        // for all outgoing link, get their rank contribution from all
        // links by doing:
        //
        // 1) group all outgoing links with rank of its parent page: (Zip)
        // ([linked_url, linked_url, ...], rank_parent)
        //
        // 2) compute rank contribution for each linked_url: (FlatMap)
        // (linked_url, rank / OUTGOING.size)

        auto outs_rank = links.Zip(
            ranks,
            [](const OutgoingLinks& ol, const Rank& r) {
                return OutgoingLinksRank(ol, r);
            });

        if (debug) {
            outs_rank
            .Map([](const OutgoingLinksRank& ol) {
                     return common::Join(',', ol.first)
                     + " <- " + std::to_string(ol.second);
                 })
            .Print("outs_rank");
        }

        auto contribs = outs_rank.template FlatMap<PageRankPair>(
            [](const OutgoingLinksRank& p, auto emit) {
                if (p.first.size() > 0) {
                    Rank rank_contrib = p.second / p.first.size();
                    // assert (rank_contrib <= 1);
                    for (const PageId& tgt : p.first) {
                        LOG << "contribs2 " << tgt << " " << rank_contrib;
                        emit(PageRankPair { tgt, rank_contrib });
                    }
                }
            });

        // reduce all rank contributions by adding all rank contributions and
        // compute the new rank: (url, rank)

        ranks =
            contribs
            .ReduceToIndex(
                [](const PageRankPair& p) { return p.page; },
                [](const PageRankPair& p1, const PageRankPair& p2) {
                    return PageRankPair { p1.page, p1.rank + p2.rank };
                }, num_pages)
            .Map([num_pages](const PageRankPair& p) {
                     Rank r = dampening * p.rank + (1 - dampening) / num_pages;
                     LOG << "ranks2 in " << p << "out" << r;
                     return r;
                 }).Execute().Collapse();
    }

    // construct output as (pageid, rank)

    auto node_ids = Generate(
        ctx, [](const size_t& index) { return index; }, num_pages);

    // write result to line. add 1 to node_ids to revert back to normal
    auto res = ranks.Zip(
        node_ids,
        [](const Rank& r, const PageId& p) {
            return std::to_string(p) + ": " + std::to_string(r);
        });

    assert(res.Keep().Size() == num_pages);

    return res;
}

} // namespace examples

#endif // !THRILL_EXAMPLES_PAGE_RANK_PAGE_RANK_HEADER

/******************************************************************************/
