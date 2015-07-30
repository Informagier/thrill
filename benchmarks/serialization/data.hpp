#ifndef C7A_DATA_HEADER
#define C7A_DATA_HEADER

#include <vector>
#include <stdint.h>
#include <string>
#include <cereal/types/vector.hpp>

const std::string bench_string  = "shgfkghsdfjhgsfjhfgjhfgjsffghgsfdhgsfdfkdjhfioukjhkfdljgdfkgvjafdhasgdfwurtjkghfsdjkfg";

struct BenchVector {
    BenchVector() {};
    BenchVector(std::vector<int64_t> bv) : bench_vector(bv) {};

    std::vector<int64_t> bench_vector;

    template <typename Archive>
    void serialize (Archive& archive) {
        archive(bench_vector);
    }
};

const BenchVector bv = BenchVector({
        34492,6603,44033,8874,47607,38416,20395,29192,38620,36775,
        35058,20501,39664,64574,11261,35679,16607,26020,39476,16699,
        21505,20947,53587,24746,45980,18827,137,61753,53340,25406,
        31601,38267,47951,62073,6738,42983,19246,34384,51818,157,
        628,40807,41177,49445,60677,23663,22312,20616,28922,20389,
        28543,48407,63986,7216,61601,6647,7956,47434,29257,28162,
        25582,29941,55019,60580,47503,6662,35851,23648,61464,43188,
        23519,37727,36778,62597,27203,31950,23796,62866,54914,4507,
        7775,39256,56141,36388,58687,42619,30909,47784,44209,38712,
        39387,37342,36743,17467,21181,36301,3918,10068,16204,50558,
        33633,6164,111,30859,56608,3320,17784,17842,3623,9258,
        38514,46795,60113,5658,38229,16986,64707,17010,35380,34811,
        13179,21861,23487,27513,18226,29112,41034,57128,27903,5484,
        64117,27389,45096,15321,42035,30690,13359,20005,35723,52158,
        29700,2895,46899,54388,50709,44269,11880,43493,46848,47523,
        64268,11074,673,62425,10609,21895,65353,51268,30048,8327,
        15020,13098,8614,9162,44230,34945,49663,35106,37002,13147,
        23661,47571,58767,27158,58907,18884,29017,49330,21161,20261,
        22381,57315,11034,39237,35876,52748,52135,3652,5573,11120,
        35955,16213,32062,32349,26362,7882,39528,40116,378,3620,
        23121,39308,39836,55477,12003,34089,54450,23870,1952,58445,
        38567,53959,32265,10354,57972,31510,264,44462,61043,48989,
        59504,34995,21591,56088,47298,64849,51629,64161,30990,34752,
        28699,58836,28310,27686,53360,58218,1382,12294,17239,24411,
        50012,11485,2732,43364,34433,12782,23748,25393,49417,19316,
        56304,54887,48832,4473,31997,8192,14593,32054,54448,60709,
        26749,18928,53574,8031,23681,61479,32115,48730,15694,51143,
        37232,25059,11327,31269,18035,24905,30575,35576,50878,63566,
        7213,10140,13121,13487,53861,3487,58552,11636,42412,59239,
        38086,16738,16197,45757,47844,18248,14385,64858,2785,43969,
        55873,34166,42623,15441,55015,9219,47800,3659,47139,54900,
        36120,23551,51858,64110,44719,51319,17756,56240,44986,22746,
        4944,50980,43252,4881,53006,12039,41658,49870,54730,10213,
        15296,9139,54583,7345,10260,58177,4126,46487,15644,1323,
        7767,40475,61334,33814,296,4202,58954,60710,47287,17842,
        62948,40443,16982,64708,45849,58300,16400,20536,38687,3543,
        14340,17591,37874,58282,12109,61025,17392,4014,39117,40912,
        24572,39998,57703,4373,28314,27751,11307,43386,28218,4223,
        10843,46516,48966,472,54111,55663,33428,52509,3845,5647,
        3164,36542,16868,5700,44693,1240,12757,22308,12715,9024,
        11999,42661,57211,50848,14944,59955,59208,41264,20033,23019,
        6368,43478,48738,14758,41280,24076,64014,52013,24937,46899,
        59046,52457,22428,27505,43159,17779,26304,23403,52731,32394,
        11878,6003,29789,43818,59314,20329,58069,13081,61424,27718,
        29996,21610,3205,14477,37523,35003,36286,62906,44191,31058,
        53068,826,49309,1705,44214,29908,19433,61948,46663,42710,
        15534,7807,36492,51075,56749,56906,28946,10316,12099,38561,
        41455,12573,42613,18640,64463,61175,61712,57225,10181,60007,
        49094,30559,59477,48603,15646,56068,58417,29704,40969,37530,
        18769,35771,62828,64452,43719,35415,9679,48100,37102,2014,
        37901,40564,5231,35279,31257,46681,36297,49026,30314,53309,
        1772,15145,34777,28019,28568,11004,55343,63726,32528,7595,
        7288,61637,55329,11723,41610,36885,34524,9144,58781,31381,
        31576,51243,65449,3883,24602,41301,49332,30071,24731,53076,
        18835,30948,31196,15758,58879,8007,16244,56729,31879,13324,
        30246,59487,40604,41656,9922,16564,41094,26477,14418,47704,
        46087,43602,35364,3468,28154,40737,22138,29789,22868,29611,
        137,18409,26366,11641,24154,33214,53316,54678,56564,6485,
        63859,30593,23819,63569,40255,28125,3821,58358,26034,27326,
        20168,39097,34762,3861,54465,48588,41685,9521,42716,60424,
        61811,64517,55711,28716,5876,16802,43184,32158,12460,33802,
        43630,57941,65454,57092,23134,1757,42449,56716,47808,31003,
        52358,59607,60476,14763,48276,61767,52541,15148,59109,60993,
        8607,56930,13760,52036,4132,61711,4915,59651,11062,750,
        32426,26748,61727,1006,38136,15828,5934,5901,37067,46827,
        11884,17393,6322,58799,45596,60370,61443,46045,64246,48987,
        2765,29446,10923,21875,48410,39056,42986,5562,17903,63126,
        57165,16031,63190,41857,20363,25337,60583,34165,12117,31144,
        15233,32201,50866,19101,22325,45683,41215,28885,42919,56843,
        26045,18702,32409,4802,11310,50435,18268,34070,56862,48307,
        27179,35722,23159,5270,62523,55928,37842,1469,52744,63149,
        61265,28590,10318,36834,31225,55332,26967,34844,53898,13550,
        45088,18743,10663,64974,29124,42159,34634,3895,22055,5649,
        53895,30439,38264,18351,980,62663,5479,32694,2392,14157,
        34319,34875,42709,52995,35927,63947,62191,63907,24903,15705,
        40955,50782,64934,62454,19404,53365,25945,57405,41221,12921,
        34291,15944,32298,4083,30010,44032,41316,28130,31221,18940,
        44513,5513,24837,54233,9899,39933,29068,23247,47440,52698,
        63372,8945,51493,57120,52514,20487,60260,59814,1484,24789,
        33866,45112,14526,60221,50973,25125,5991,48481,33017,59821,
        42654,51735,63141,55833,14490,35443,44171,62286,36815,23160,
        32977,31387,20525,49812,1295,43744,18217,34480,58203,61045,
        25528,48777,55709,47339,37999,49039,45022,35884,33880,44348,
        1526,6778,14068,16467,699,3820,2828,55811,62784,22958,
        21898,18678,15946,42931,47002,933,19312,32862,25994,6791,
        58533,15443,21048,11212,28899,9618,9053,61352,45516,23407,
        35256,58880,36406,36544,6981,30273,65302,37871,10065,19591,
        6464,15831,40594,62620,61300,39313,57367,56539,21501,61070,
        13632,27764,60371,47978,38670,33853,31205,49260,56140,18928,
        27245,47480,45291,64421,19547,29616,38608,45751,62137,18789,
        59923,25449,57664,9889,18109,26588,20278,51672,21209,23202,
        29419,55090,35147,32818,15270,49125,30648,64720,29814,57758,
        25352,11149,3703,16912,60520,34110,42527,1438,36294,17877,
        52345,28849,16183,34088,37493,39997,54697,970,14983,60268,
        19566,32131,54265,10366,49778,1520,43174,34006,64401,58034,
        35005,27621,65337,58940,9671,6424,61857,22542,30725,61777,
        12539,29197,24034,28450,2769,41642,50160,47847,18152,51053,
        47843,61836,25260,36400,22250,17010,29460,51714,42262,28230,
        54088,34531,17424,36588,53806,32847,11804,28344,16504,38941,
        23441,53703,31551,61990,59981,19355,32417,16169,64680,1600
    });

using p_is = std::pair<int, std::string>;
p_is p_is0 = std::make_pair(9, "blablablabalbalbla");
using p_pi = std::pair<p_is, int>;
p_pi p_pi0 = std::make_pair(p_is0, 89);
using t_pp = std::tuple<p_is, p_pi>;
t_pp t_pp0 = std::make_tuple(p_is0, p_pi0);
using t_ttpi = std::tuple<t_pp, t_pp, p_pi, int>;
t_ttpi t_ttpi0 = std::make_tuple(t_pp0, t_pp0, p_pi0, 8769);
t_ttpi t_ttpi1 = std::make_tuple(t_pp0, t_pp0, p_pi0, 870999);
using t_tt = std::tuple<t_ttpi, t_ttpi, t_ttpi, t_ttpi>;
t_tt bench_tuple = std::make_tuple(t_ttpi0, t_ttpi0, t_ttpi1, t_ttpi1);


#endif