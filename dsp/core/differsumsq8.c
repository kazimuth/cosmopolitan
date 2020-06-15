/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ This program is free software; you can redistribute it and/or modify         │
│ it under the terms of the GNU General Public License as published by         │
│ the Free Software Foundation; version 2 of the License.                      │
│                                                                              │
│ This program is distributed in the hope that it will be useful, but          │
│ WITHOUT ANY WARRANTY; without even the implied warranty of                   │
│ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU             │
│ General Public License for more details.                                     │
│                                                                              │
│ You should have received a copy of the GNU General Public License            │
│ along with this program; if not, write to the Free Software                  │
│ Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA                │
│ 02110-1301 USA                                                               │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "dsp/core/core.h"
#include "dsp/core/q.h"

/**
 * Computes Σ𝑥ᵢΣ𝑥ⱼΣ𝑥ₖΣ𝑥ₗΣ𝑥ₘΣ𝑥ₙΣ𝑥ₚΣ𝑥ₛ(δ₁𝑥ᵢ+δ₂𝑥ⱼ+δ₃𝑥ₖ+δ₄𝑥ₗ+δ₅𝑥ₘ+δ₆𝑥ₙ+δₚ𝑥ₚ+δₛ𝑥ₛ)²
 *
 *   “As soon as an Analytical Engine exists, it will necessarily
 *    guide the future course of the science. Whenever any result
 *    is sought by its aid, the question will then arise — by what
 *    course of calculation can these results be arrived at by the
 *    machine in the shortest time?
 *
 *                    — Charles Babbage (Life of a Philosopher, 1864)
 *
 */
double DifferSumSq8(const double D[static 8], double L, double H) {
  double T10, T100, T101, T102, T103, T104, T105, T106, T107, T108, T109, T11;
  double T110, T111, T112, T113, T114, T115, T116, T117, T118, T119, T12, T120;
  double T121, T122, T123, T124, T125, T126, T127, T128, T129, T13, T130, T131;
  double T132, T133, T134, T135, T136, T137, T138, T139, T14, T140, T141, T142;
  double T143, T144, T145, T146, T147, T148, T149, T15, T150, T151, T152, T153;
  double T154, T155, T156, T157, T158, T159, T16, T160, T161, T162, T163, T164;
  double T165, T166, T167, T168, T169, T17, T170, T171, T172, T173, T174, T175;
  double T176, T177, T178, T179, T18, T180, T181, T182, T183, T184, T185, T186;
  double T187, T188, T189, T19, T190, T191, T192, T193, T194, T195, T196, T197;
  double T198, T199, T2, T20, T200, T201, T202, T203, T204, T205, T206, T207;
  double T208, T209, T21, T210, T211, T212, T213, T214, T215, T216, T217, T218;
  double T219, T22, T220, T221, T222, T223, T224, T225, T226, T227, T228, T229;
  double T230, T231, T232, T233, T234, T235, T236, T237, T238, T239, T24, T240;
  double T241, T242, T243, T244, T245, T246, T247, T248, T249, T25, T250, T251;
  double T252, T253, T254, T255, T256, T257, T258, T259, T26, T260, T261, T262;
  double T263, T264, T265, T266, T267, T268, T269, T27, T270, T271, T272, T273;
  double T274, T275, T276, T277, T278, T279, T28, T280, T281, T282, T283, T284;
  double T285, T286, T287, T288, T289, T29, T290, T291, T292, T293, T294, T295;
  double T296, T297, T298, T299, T3, T30, T300, T301, T302, T303, T304, T305;
  double T307, T308, T309, T31, T310, T311, T312, T313, T314, T315, T316, T317;
  double T318, T319, T32, T320, T321, T322, T323, T324, T325, T326, T327, T328;
  double T329, T33, T330, T331, T332, T333, T334, T335, T336, T337, T338, T339;
  double T34, T340, T341, T342, T343, T344, T345, T346, T347, T348, T349, T35;
  double T350, T351, T352, T353, T354, T355, T356, T357, T358, T359, T36, T360;
  double T361, T362, T363, T364, T365, T366, T367, T368, T369, T37, T370, T371;
  double T372, T373, T374, T375, T376, T377, T378, T379, T38, T380, T381, T382;
  double T383, T384, T385, T386, T387, T388, T389, T39, T390, T391, T392, T393;
  double T394, T395, T396, T397, T398, T399, T4, T40, T400, T401, T402, T403;
  double T405, T406, T407, T41, T42, T43, T44, T45, T46, T47, T48, T49, T5, T50;
  double T51, T52, T53, T54, T55, T56, T57, T58, T59, T6, T60, T61, T62, T63;
  double T65, T66, T67, T68, T69, T7, T70, T71, T72, T73, T74, T75, T76, T77;
  double T79, T8, T80, T81, T82, T83, T84, T85, T86, T87, T88, T89, T9, T90;
  double T92, T93, T94, T95, T96, T97, T98, T99, T23, T306, T91, T78, T64, T404;
  T2 = 4 * D[5], T3 = 3 * D[4], T4 = 3 * D[3], T5 = 3 * D[2], T6 = 3 * D[1],
  T7 = 3 * D[0], T8 = D[7] * D[7], T9 = D[6] * D[6], T10 = -28 * D[5],
  T11 = -18 * D[4], T12 = -18 * D[3], T13 = -18 * D[2], T14 = -18 * D[1],
  T15 = -18 * D[0], T16 = D[5] * D[5], T17 = D[4] * D[4], T18 = D[3] * D[3],
  T19 = D[2] * D[2], T20 = D[1] * D[1], T21 = D[0] * D[0], T22 = -34 * D[5],
  T23 = -24 * D[4], T24 = -24 * D[3], T25 = -24 * D[2], T26 = -24 * D[1],
  T27 = -24 * D[0], T28 = 84 * D[5], T29 = 39 * D[4], T30 = 39 * D[3],
  T31 = 39 * D[2], T32 = 39 * D[1], T33 = 39 * D[0], T34 = 210 * D[5],
  T35 = 120 * D[4], T36 = 120 * D[3], T37 = 120 * D[2], T38 = 120 * D[1],
  T39 = 120 * D[0], T40 = 128 * D[5], T41 = 84 * D[4], T42 = 84 * D[3],
  T43 = 84 * D[2], T44 = 84 * D[1], T45 = 84 * D[0];
  T46 = -144 * D[5], T47 = (T23 + T24 + T25 + T26 + T27) * D[5],
  T48 = (T24 + T25 + T26 + T27) * D[4], T49 = (T25 + T26 + T27) * D[3],
  T50 = (T26 + T27) * D[2], T51 = -24 * D[0] * D[1], T52 = -552 * D[5],
  T53 = -192 * D[4], T54 = -192 * D[3], T55 = -192 * D[2], T56 = -192 * D[1],
  T57 = -192 * D[0], T58 = H * H, T59 = -688 * D[5], T60 = -336 * D[4],
  T61 = -336 * D[3], T62 = -336 * D[2], T63 = -336 * D[1], T64 = -336 * D[0],
  T65 = -280 * D[5], T66 = -168 * D[4], T67 = -168 * D[3], T68 = -168 * D[2],
  T69 = -168 * D[1], T70 = -168 * D[0], T71 = 168 * D[5], T72 = -42 * D[4],
  T73 = -42 * D[3], T74 = -42 * D[2], T75 = -42 * D[1], T76 = -42 * D[0],
  T77 = (H * H * H), T78 = 336 * D[4], T79 = 336 * D[3], T80 = 336 * D[2],
  T81 = 336 * D[1], T82 = 336 * D[0], T83 = 1568 * D[5],
  T84 = 336 * D[0] * D[1], T85 = 1288 * D[5], T86 = 504 * D[4],
  T87 = 504 * D[3], T88 = 504 * D[2], T89 = 504 * D[1], T90 = 504 * D[0],
  T91 = 392 * D[5], T92 = 210 * D[4], T93 = 210 * D[3], T94 = 210 * D[2],
  T95 = 210 * D[1], T96 = 210 * D[0], T97 = 84 * T8, T98 = 168 * D[6],
  T99 = 84 * T9, T100 = 84 * T16, T101 = (T41 + T42 + T43 + T44 + T45) * D[5],
  T102 = 84 * T17, T103 = (T42 + T43 + T44 + T45) * D[4], T104 = 84 * T18,
  T105 = (T43 + T44 + T45) * D[3], T106 = 84 * T19, T107 = (T44 + T45) * D[2],
  T108 = 84 * T20, T109 = 84 * D[0] * D[1], T110 = 84 * T21, T111 = -924 * D[5],
  T112 = (T78 + T79 + T80 + T81 + T82) * D[5],
  T113 = (T79 + T80 + T81 + T82) * D[4], T114 = (T80 + T81 + T82) * D[3],
  T115 = (T81 + T82) * D[2], T116 = (H * H * H * H), T117 = -2128 * D[5],
  T118 = -2520 * D[5], T119 = (T66 + T67 + T68 + T69 + T70) * D[5],
  T120 = (T67 + T68 + T69 + T70) * D[4], T121 = (T68 + T69 + T70) * D[3],
  T122 = (T69 + T70) * D[2], T123 = -168 * D[0] * D[1], T124 = -1512 * D[5],
  T125 = -420 * D[4], T126 = -420 * D[3], T127 = -420 * D[2],
  T128 = -420 * D[1], T129 = -420 * D[0], T130 = -364 * D[5];
  T131 = T97 + (T98 + T71 + T72 + T73 + T74 + T75 + T76) * D[7] + T99 +
         (T71 + T72 + T73 + T74 + T75 + T76) * D[6] + T100 +
         (T72 + T73 + T74 + T75 + T76) * D[5] + T102 +
         (T73 + T74 + T75 + T76) * D[4] + T104 + (T74 + T75 + T76) * D[3] +
         T106 + (T75 + T76) * D[2] + T108 - 42 * D[0] * D[1] + T110;
  T132 = 462 * T8, T133 = 924 * D[6], T134 = 924 * D[5], T135 = 462 * T9,
  T136 = 462 * T16, T137 = (T60 + T61 + T62 + T63 + T64) * D[5],
  T138 = 462 * T17, T139 = (T61 + T62 + T63 + T64) * D[4], T140 = 462 * T18,
  T141 = (T62 + T63 + T64) * D[3], T142 = 462 * T19, T143 = (T63 + T64) * D[2],
  T144 = 462 * T20, T145 = 462 * T21, T146 = (H * H * H * H * H),
  T147 = 2240 * D[5], T148 = -840 * D[4], T149 = -840 * D[3],
  T150 = -840 * D[2], T151 = -840 * D[1], T152 = -840 * D[0],
  T153 = 3080 * D[5], T154 = (T148 + T149 + T150 + T151 + T152) * D[5],
  T155 = (T149 + T150 + T151 + T152) * D[4], T156 = (T150 + T151 + T152) * D[3],
  T157 = (T151 + T152) * D[2], T158 = -840 * D[0] * D[1], T159 = 1260 * T8,
  T160 = 2520 * D[6], T161 = 2520 * D[5], T162 = 1260 * T9, T163 = 1260 * T16,
  T164 = 1260 * T17, T165 = 1260 * T18, T166 = 1260 * T19, T167 = 1260 * T20,
  T168 = 210 * D[0] * D[1], T169 = 1260 * T21, T170 = 168 * D[4],
  T171 = 168 * D[3], T172 = 168 * D[2], T173 = 168 * D[1], T174 = 168 * D[0],
  T175 = 1148 * D[5], T176 = 168 * D[0] * D[1], T177 = 224 * D[5];
  T178 = -72 * T8 + (-144 * D[6] + T46 + T23 + T24 + T25 + T26 + T27) * D[7] -
         72 * T9 + (T46 + T23 + T24 + T25 + T26 + T27) * D[6] - 72 * T16 + T47 -
         72 * T17 + T48 - 72 * T18 + T49 - 72 * T19 + T50 - 72 * T20 + T51 -
         72 * T21;
  T179 = 420 * T8, T180 = 840 * D[6], T181 = 840 * D[5], T182 = 420 * T9,
  T183 = 840 * D[5] * D[6], T184 = 420 * T16, T185 = 420 * T17,
  T186 = 420 * T18, T187 = 420 * T19, T188 = 420 * T20, T189 = 420 * T21,
  T190 = (H * H * H * H * H * H);
  T191 = -1064 * T8 +
         (-2128 * D[6] + T117 + T78 + T79 + T80 + T81 + T82) * D[7] -
         1064 * T9 + (T117 + T78 + T79 + T80 + T81 + T82) * D[6] - 1064 * T16 +
         T112 - 1064 * T17 + T113 - 1064 * T18 + T114 - 1064 * T19 + T115 -
         1064 * T20 + T84 - 1064 * T21;
  T192 = 1540 * T8, T193 = 3080 * D[6], T194 = 840 * D[4], T195 = 840 * D[3],
  T196 = 840 * D[2], T197 = 840 * D[1], T198 = 840 * D[0], T199 = 1540 * T9,
  T200 = 1540 * T16, T201 = 1540 * T17, T202 = 1540 * T18, T203 = 1540 * T19,
  T204 = 1540 * T20, T205 = 840 * D[0] * D[1], T206 = 1540 * T21,
  T207 = -2800 * D[5], T208 = (T194 + T195 + T196 + T197 + T198) * D[5],
  T209 = (T195 + T196 + T197 + T198) * D[4], T210 = (T196 + T197 + T198) * D[3],
  T211 = (T197 + T198) * D[2], T212 = -1624 * D[5], T213 = -88 * D[5];
  T214 = 42 * T8 + (84 * D[6] + T28 + T29 + T30 + T31 + T32 + T33) * D[7] +
         42 * T9 + (T28 + T29 + T30 + T31 + T32 + T33) * D[6] + 42 * T16 +
         (T29 + T30 + T31 + T32 + T33) * D[5] + 42 * T17 +
         (T30 + T31 + T32 + T33) * D[4] + 42 * T18 + (T31 + T32 + T33) * D[3] +
         42 * T19 + (T32 + T33) * D[2] + 42 * T20 + 39 * D[0] * D[1] + 42 * T21;
  T215 = 276 * T8, T216 = 552 * D[6], T217 = 552 * D[5], T218 = 192 * D[4],
  T219 = 192 * D[3], T220 = 192 * D[2], T221 = 192 * D[1], T222 = 192 * D[0],
  T223 = 276 * T9, T224 = 276 * T16, T225 = 276 * T17, T226 = 276 * T18,
  T227 = 276 * T19, T228 = 276 * T20, T229 = 192 * D[0] * D[1],
  T230 = 276 * T21, T231 = (H * H * H * H * H * H * H);
  T232 = 784 * T8 + (1568 * D[6] + T83 + T78 + T79 + T80 + T81 + T82) * D[7] +
         784 * T9 + (T83 + T78 + T79 + T80 + T81 + T82) * D[6] + 784 * T16 +
         T112 + 784 * T17 + T113 + 784 * T18 + T114 + 784 * T19 + T115 +
         784 * T20 + T84 + 784 * T21;
  T233 = (T170 + T171 + T172 + T173 + T174) * D[5];
  T234 = (T171 + T172 + T173 + T174) * D[4];
  T235 = (T172 + T173 + T174) * D[3];
  T236 = (T173 + T174) * D[2];
  T237 = T159 + (T160 + T161 - T92 - T93 - T94 - T95 - T96) * D[7] + T162 +
         (T161 - T92 - T93 - T94 - T95 - T96) * D[6] + T163 +
         (-T92 - T93 - T94 - T95 - T96) * D[5] + T164 +
         (-T93 - T94 - T95 - T96) * D[4] + T165 + (-T94 - T95 - T96) * D[3] +
         T166 + (-T95 - T96) * D[2] + T167 - T168 + T169;
  T238 = 812 * T8, T239 = 1624 * D[6], T240 = 1624 * D[5], T241 = 812 * T9,
  T242 = 812 * T16, T243 = 812 * T17, T244 = 812 * T18, T245 = 812 * T19,
  T246 = 812 * T20, T247 = 812 * T21, T248 = 672 * D[5], T249 = 20 * D[5],
  T250 = (T3 + T4 + T5 + T6 + T7) * D[5], T251 = (T4 + T5 + T6 + T7) * D[4],
  T252 = (T5 + T6 + T7) * D[3], T253 = (T6 + T7) * D[2], T254 = 3 * D[0] * D[1];
  T255 = -14 * T8 + (-28 * D[6] + T10 + T11 + T12 + T13 + T14 + T15) * D[7] -
         14 * T9 + (T10 + T11 + T12 + T13 + T14 + T15) * D[6] - 14 * T16 +
         (T11 + T12 + T13 + T14 + T15) * D[5] - 14 * T17 +
         (T12 + T13 + T14 + T15) * D[4] - 14 * T18 + (T13 + T14 + T15) * D[3] -
         14 * T19 + (T14 + T15) * D[2] - 14 * T20 - 18 * D[0] * D[1] - 14 * T21;
  T256 = 105 * T8, T257 = 210 * D[6], T258 = 105 * T9, T259 = 105 * T16,
  T260 = 105 * T17, T261 = 105 * T18, T262 = 105 * T19, T263 = 105 * T20,
  T264 = 120 * D[0] * D[1], T265 = 105 * T21,
  T266 = (H * H * H * H * H * H * H * H);
  T267 = -344 * T8 + (-688 * D[6] + T59 + T60 + T61 + T62 + T63 + T64) * D[7] -
         344 * T9 + (T59 + T60 + T61 + T62 + T63 + T64) * D[6] - 344 * T16 +
         T137 - 344 * T17 + T139 - 344 * T18 + T141 - 344 * T19 + T143 -
         344 * T20 - T84 - 344 * T21;
  T268 = 644 * T8, T269 = 1288 * D[6], T270 = 644 * T9, T271 = 644 * T16,
  T272 = 644 * T17, T273 = 644 * T18, T274 = 644 * T19, T275 = 644 * T20,
  T276 = 504 * D[0] * D[1], T277 = 644 * T21;
  T278 = -756 * T8 +
         (-1512 * D[6] + T124 + T125 + T126 + T127 + T128 + T129) * D[7] -
         756 * T9 + (T124 + T125 + T126 + T127 + T128 + T129) * D[6] -
         756 * T16 + (T125 + T126 + T127 + T128 + T129) * D[5] - 756 * T17 +
         (T126 + T127 + T128 + T129) * D[4] - 756 * T18 +
         (T127 + T128 + T129) * D[3] - 756 * T19 + (T128 + T129) * D[2] -
         756 * T20 - 420 * D[0] * D[1] - 756 * T21;
  T279 = 574 * T8, T280 = 1148 * D[6], T281 = 574 * T9, T282 = 574 * T16,
  T283 = 574 * T17, T284 = 574 * T18, T285 = 574 * T19, T286 = 574 * T20,
  T287 = 574 * T21;
  T288 = -280 * T8 + (-560 * D[6] - 560 * D[5]) * D[7] - 280 * T9 -
         560 * D[5] * D[6] - 280 * T16 - 280 * T17 - 280 * T18 - 280 * T19 -
         280 * T20 - 280 * T21;
  T289 = 24 * D[4], T290 = 24 * D[3], T291 = 24 * D[2], T292 = 24 * D[1],
  T293 = 24 * D[0], T294 = 24 * D[0] * D[1], T295 = -14 * T8, T296 = -28 * D[6],
  T297 = -14 * T9, T298 = 6 * D[4], T299 = 6 * D[3], T300 = 6 * D[2],
  T301 = 6 * D[1], T302 = 6 * D[0], T303 = -14 * T16, T304 = -14 * T17,
  T305 = -14 * T18, T306 = -14 * T19, T307 = -14 * T20, T308 = -14 * T21;
  T309 = 2 * T8 + (4 * D[6] + T2 + T3 + T4 + T5 + T6 + T7) * D[7] + 2 * T9 +
         (T2 + T3 + T4 + T5 + T6 + T7) * D[6] + 2 * T16 + T250 + 2 * T17 +
         T251 + 2 * T18 + T252 + 2 * T19 + T253 + 2 * T20 + T254 + 2 * T21;
  T310 = 17 * T8, T311 = 34 * D[6], T312 = 34 * D[5], T313 = 17 * T9,
  T314 = 17 * T16, T315 = (T289 + T290 + T291 + T292 + T293) * D[5];
  T316 = 17 * T17, T317 = (T290 + T291 + T292 + T293) * D[4];
  T318 = 17 * T18, T319 = (T291 + T292 + T293) * D[3];
  T320 = 17 * T19, T321 = (T292 + T293) * D[2];
  T322 = 17 * T20, T323 = 17 * T21, T324 = (H * H * H * H * H * H * H * H * H);
  T325 = 64 * T8,
  T326 = (128 * D[6] + T40 + T41 + T42 + T43 + T44 + T45) * D[7];
  T327 = 64 * T9, T328 = (T40 + T41 + T42 + T43 + T44 + T45) * D[6];
  T329 = 64 * T16, T330 = 64 * T17, T331 = 64 * T18, T332 = 64 * T19,
  T333 = 64 * T20, T334 = 64 * T21, T335 = 140 * T8, T336 = 280 * D[6],
  T337 = 280 * D[5], T338 = 140 * T9, T339 = 140 * T16, T340 = 140 * T17,
  T341 = 140 * T18, T342 = 140 * T19, T343 = 140 * T20, T344 = 140 * T21,
  T345 = 196 * T8;
  T346 = (392 * D[6] + T91 + T92 + T93 + T94 + T95 + T96) * D[7];
  T347 = 196 * T9;
  T348 = (T91 + T92 + T93 + T94 + T95 + T96) * D[6];
  T349 = 196 * T16;
  T350 = (T92 + T93 + T94 + T95 + T96) * D[5];
  T351 = 196 * T17;
  T352 = (T93 + T94 + T95 + T96) * D[4];
  T353 = 196 * T18;
  T354 = (T94 + T95 + T96) * D[3];
  T355 = 196 * T19;
  T356 = (T95 + T96) * D[2];
  T357 = 196 * T20, T358 = 196 * T21, T359 = 182 * T8, T360 = 364 * D[6],
  T361 = 364 * D[5], T362 = 182 * T9, T363 = 182 * T16, T364 = 182 * T17,
  T365 = 182 * T18, T366 = 182 * T19, T367 = 182 * T20, T368 = 182 * T21,
  T369 = 112 * T8;
  T370 = (224 * D[6] + T177 + T41 + T42 + T43 + T44 + T45) * D[7];
  T371 = 112 * T9;
  T372 = (T177 + T41 + T42 + T43 + T44 + T45) * D[6];
  T373 = 112 * T16, T374 = 112 * T17, T375 = 112 * T18, T376 = 112 * T19,
  T377 = 112 * T20, T378 = 112 * T21, T379 = 44 * T8, T380 = 88 * D[6],
  T381 = 88 * D[5], T382 = 44 * T9, T383 = 44 * T16, T384 = 44 * T17,
  T385 = 44 * T18, T386 = 44 * T19, T387 = 44 * T20, T388 = 44 * T21,
  T389 = 10 * T8, T390 = (20 * D[6] + T249 + T3 + T4 + T5 + T6 + T7) * D[7];
  T391 = 10 * T9, T392 = (T249 + T3 + T4 + T5 + T6 + T7) * D[6];
  T393 = 10 * T16, T394 = 10 * T17, T395 = 10 * T18, T396 = 10 * T19,
  T397 = 10 * T20, T398 = 10 * T21, T399 = 2 * D[6], T400 = 2 * D[5],
  T401 = 2 * D[5] * D[6];
  T402 = T309 * (L * L * L * L * L * L * L * L * L * L) +
         (T255 * H - T310 + (-T311 + T22 + T23 + T24 + T25 + T26 + T27) * D[7] -
          T313 + (T22 + T23 + T24 + T25 + T26 + T27) * D[6] - T314 + T47 -
          T316 + T48 - T318 + T49 - T320 + T50 - T322 + T51 - T323) *
             (L * L * L * L * L * L * L * L * L) +
         (T214 * T58 +
          (T256 + (T257 + T34 + T35 + T36 + T37 + T38 + T39) * D[7] + T258 +
           (T34 + T35 + T36 + T37 + T38 + T39) * D[6] + T259 +
           (T35 + T36 + T37 + T38 + T39) * D[5] + T260 +
           (T36 + T37 + T38 + T39) * D[4] + T261 + (T37 + T38 + T39) * D[3] +
           T262 + (T38 + T39) * D[2] + T263 + T264 + T265) *
              H +
          T325 + T326 + T327 + T328 + T329 + T101 + T330 + T103 + T331 + T105 +
          T332 + T107 + T333 + T109 + T334) *
             (L * L * L * L * L * L * L * L) +
         (T178 * T77 +
          (-T215 + (-T216 + T52 + T53 + T54 + T55 + T56 + T57) * D[7] - T223 +
           (T52 + T53 + T54 + T55 + T56 + T57) * D[6] - T224 +
           (T53 + T54 + T55 + T56 + T57) * D[5] - T225 +
           (T54 + T55 + T56 + T57) * D[4] - T226 + (T55 + T56 + T57) * D[3] -
           T227 + (T56 + T57) * D[2] - T228 - T229 - T230) *
              T58 +
          T267 * H - T335 + (-T336 + T65 + T66 + T67 + T68 + T69 + T70) * D[7] -
          T338 + (T65 + T66 + T67 + T68 + T69 + T70) * D[6] - T339 + T119 -
          T340 + T120 - T341 + T121 - T342 + T122 - T343 + T123 - T344) *
             (L * L * L * L * L * L * L);
  T403 =
      T402 +
      (T131 * T116 +
       (T179 + (T180 + T181) * D[7] + T182 + T183 + T184 + T185 + T186 + T187 +
        T188 + T189) *
           T77 +
       T232 * T58 +
       (T268 + (T269 + T85 + T86 + T87 + T88 + T89 + T90) * D[7] + T270 +
        (T85 + T86 + T87 + T88 + T89 + T90) * D[6] + T271 +
        (T86 + T87 + T88 + T89 + T90) * D[5] + T272 +
        (T87 + T88 + T89 + T90) * D[4] + T273 + (T88 + T89 + T90) * D[3] +
        T274 + (T89 + T90) * D[2] + T275 + T276 + T277) *
           H +
       T345 + T346 + T347 + T348 + T349 + T350 + T351 + T352 + T353 + T354 +
       T355 + T356 + T357 + T168 + T358) *
          (L * L * L * L * L * L) +
      ((-T97 + (-T98 - T71 + T41 + T42 + T43 + T44 + T45) * D[7] - T99 +
        (-T71 + T41 + T42 + T43 + T44 + T45) * D[6] - T100 + T101 - T102 +
        T103 - T104 + T105 - T106 + T107 - T108 + T109 - T110) *
           T146 +
       (-T132 + (-T133 + T111 + T78 + T79 + T80 + T81 + T82) * D[7] - T135 +
        (T111 + T78 + T79 + T80 + T81 + T82) * D[6] - T136 + T112 - T138 +
        T113 - T140 + T114 - T142 + T115 - T144 + T84 - T145) *
           T116 +
       T191 * T77 +
       (-T159 + (-T160 + T118 + T66 + T67 + T68 + T69 + T70) * D[7] - T162 +
        (T118 + T66 + T67 + T68 + T69 + T70) * D[6] - T163 + T119 - T164 +
        T120 - T165 + T121 - T166 + T122 - T167 + T123 - T169) *
           T58 +
       T278 * H - T359 + (-T360 + T130 + T66 + T67 + T68 + T69 + T70) * D[7] -
       T362 + (T130 + T66 + T67 + T68 + T69 + T70) * D[6] - T363 + T119 - T364 +
       T120 - T365 + T121 - T366 + T122 - T367 + T123 - T368) *
          (L * L * L * L * L);
  T404 =
      T403 +
      (T131 * T190 +
       (T132 + (T133 + T134 + T60 + T61 + T62 + T63 + T64) * D[7] + T135 +
        (T134 + T60 + T61 + T62 + T63 + T64) * D[6] + T136 + T137 + T138 +
        T139 + T140 + T141 + T142 + T143 + T144 - T84 + T145) *
           T146 +
       (1120 * T8 +
        (2240 * D[6] + T147 + T148 + T149 + T150 + T151 + T152) * D[7] +
        1120 * T9 + (T147 + T148 + T149 + T150 + T151 + T152) * D[6] +
        1120 * T16 + T154 + 1120 * T17 + T155 + 1120 * T18 + T156 + 1120 * T19 +
        T157 + 1120 * T20 + T158 + 1120 * T21) *
           T116 +
       (T192 + (T193 + T153 + T148 + T149 + T150 + T151 + T152) * D[7] + T199 +
        (T153 + T148 + T149 + T150 + T151 + T152) * D[6] + T200 + T154 + T201 +
        T155 + T202 + T156 + T203 + T157 + T204 + T158 + T206) *
           T77 +
       T237 * T58 +
       (T279 + (T280 + T175 + T170 + T171 + T172 + T173 + T174) * D[7] + T281 +
        (T175 + T170 + T171 + T172 + T173 + T174) * D[6] + T282 + T233 + T283 +
        T234 + T284 + T235 + T285 + T236 + T286 + T176 + T287) *
           H +
       T369 + T370 + T371 + T372 + T373 + T101 + T374 + T103 + T375 + T105 +
       T376 + T107 + T377 + T109 + T378) *
          (L * L * L * L) +
      (T178 * T231 +
       (-T179 + (-T180 - T181) * D[7] - T182 - T183 - T184 - T185 - T186 -
        T187 - T188 - T189) *
           T190 +
       T191 * T146 +
       (-T192 + (-T193 - T153 + T194 + T195 + T196 + T197 + T198) * D[7] -
        T199 + (-T153 + T194 + T195 + T196 + T197 + T198) * D[6] - T200 + T208 -
        T201 + T209 - T202 + T210 - T203 + T211 - T204 + T205 - T206) *
           T116 +
       (-1400 * T8 +
        (-2800 * D[6] + T207 + T194 + T195 + T196 + T197 + T198) * D[7] -
        1400 * T9 + (T207 + T194 + T195 + T196 + T197 + T198) * D[6] -
        1400 * T16 + T208 - 1400 * T17 + T209 - 1400 * T18 + T210 - 1400 * T19 +
        T211 - 1400 * T20 + T205 - 1400 * T21) *
           T77 +
       (-T238 + (-T239 + T212 + T78 + T79 + T80 + T81 + T82) * D[7] - T241 +
        (T212 + T78 + T79 + T80 + T81 + T82) * D[6] - T242 + T112 - T243 +
        T113 - T244 + T114 - T245 + T115 - T246 + T84 - T247) *
           T58 +
       T288 * H - T379 + (-T380 + T213 + T23 + T24 + T25 + T26 + T27) * D[7] -
       T382 + (T213 + T23 + T24 + T25 + T26 + T27) * D[6] - T383 + T47 - T384 +
       T48 - T385 + T49 - T386 + T50 - T387 + T51 - T388) *
          (L * L * L);
  T405 =
      T214 * T266 +
      (T215 + (T216 + T217 + T218 + T219 + T220 + T221 + T222) * D[7] + T223 +
       (T217 + T218 + T219 + T220 + T221 + T222) * D[6] + T224 +
       (T218 + T219 + T220 + T221 + T222) * D[5] + T225 +
       (T219 + T220 + T221 + T222) * D[4] + T226 + (T220 + T221 + T222) * D[3] +
       T227 + (T221 + T222) * D[2] + T228 + T229 + T230) *
          T231 +
      T232 * T190 +
      (T159 + (T160 + T161 + T170 + T171 + T172 + T173 + T174) * D[7] + T162 +
       (T161 + T170 + T171 + T172 + T173 + T174) * D[6] + T163 + T233 + T164 +
       T234 + T165 + T235 + T166 + T236 + T167 + T176 + T169) *
          T146 +
      T237 * T116 +
      (T238 + (T239 + T240 + T60 + T61 + T62 + T63 + T64) * D[7] + T241 +
       (T240 + T60 + T61 + T62 + T63 + T64) * D[6] + T242 + T137 + T243 + T139 +
       T244 + T141 + T245 + T143 + T246 - T84 + T247) *
          T77 +
      (336 * T8 + (672 * D[6] + T248 + T66 + T67 + T68 + T69 + T70) * D[7] +
       336 * T9 + (T248 + T66 + T67 + T68 + T69 + T70) * D[6] + 336 * T16 +
       T119 + 336 * T17 + T120 + 336 * T18 + T121 + 336 * T19 + T122 +
       336 * T20 - T176 + 336 * T21) *
          T58 +
      (T97 + (T98 + T71 + T23 + T24 + T25 + T26 + T27) * D[7] + T99 +
       (T71 + T23 + T24 + T25 + T26 + T27) * D[6] + T100 + T47 + T102 + T48 +
       T104 + T49 + T106 + T50 + T108 + T51 + T110) *
          H +
      T389 + T390 + T391;
  T406 = T255 * T324 +
         (-T256 + (-T257 - T34 - T35 - T36 - T37 - T38 - T39) * D[7] - T258 +
          (-T34 - T35 - T36 - T37 - T38 - T39) * D[6] - T259 +
          (-T35 - T36 - T37 - T38 - T39) * D[5] - T260 +
          (-T36 - T37 - T38 - T39) * D[4] - T261 + (-T37 - T38 - T39) * D[3] -
          T262 + (-T38 - T39) * D[2] - T263 - T264 - T265) *
             T266 +
         T267 * T231 +
         (-T268 + (-T269 - T85 - T86 - T87 - T88 - T89 - T90) * D[7] - T270 +
          (-T85 - T86 - T87 - T88 - T89 - T90) * D[6] - T271 +
          (-T86 - T87 - T88 - T89 - T90) * D[5] - T272 +
          (-T87 - T88 - T89 - T90) * D[4] - T273 + (-T88 - T89 - T90) * D[3] -
          T274 + (-T89 - T90) * D[2] - T275 - T276 - T277) *
             T190 +
         T278 * T146 +
         (-T279 + (-T280 - T175 + T66 + T67 + T68 + T69 + T70) * D[7] - T281 +
          (-T175 + T66 + T67 + T68 + T69 + T70) * D[6] - T282 + T119 - T283 +
          T120 - T284 + T121 - T285 + T122 - T286 - T176 - T287) *
             T116 +
         T288 * T77 +
         (-T97 + (-T98 - T71 + T289 + T290 + T291 + T292 + T293) * D[7] - T99 +
          (-T71 + T289 + T290 + T291 + T292 + T293) * D[6] - T100 + T315 -
          T102 + T317 - T104 + T319 - T106 + T321 - T108 + T294 - T110) *
             T58;
  T407 = T404 +
         (T405 + T392 + T393 + T250 + T394 + T251 + T395 + T252 + T396 + T253 +
          T397 + T254 + T398) *
             L * L +
         (T406 +
          (T295 + (T296 + T10 + T298 + T299 + T300 + T301 + T302) * D[7] +
           T297 + (T10 + T298 + T299 + T300 + T301 + T302) * D[6] + T303 +
           (T298 + T299 + T300 + T301 + T302) * D[5] + T304 +
           (T299 + T300 + T301 + T302) * D[4] + T305 +
           (T300 + T301 + T302) * D[3] + T306 + (T301 + T302) * D[2] + T307 +
           6 * D[0] * D[1] + T308) *
              H -
          T8 + (-T399 - T400) * D[7] - T9 - T401 - T16 - T17 - T18 - T19 - T20 -
          T21) *
             L +
         T309 * (H * H * H * H * H * H * H * H * H * H) +
         (T310 + (T311 + T312 + T289 + T290 + T291 + T292 + T293) * D[7] +
          T313 + (T312 + T289 + T290 + T291 + T292 + T293) * D[6] + T314 +
          T315 + T316 + T317 + T318 + T319 + T320 + T321 + T322 + T294 + T323) *
             T324 +
         (T325 + T326 + T327 + T328 + T329 + T101 + T330 + T103 + T331 + T105 +
          T332 + T107 + T333 + T109 + T334) *
             T266 +
         (T335 + (T336 + T337 + T170 + T171 + T172 + T173 + T174) * D[7] +
          T338 + (T337 + T170 + T171 + T172 + T173 + T174) * D[6] + T339 +
          T233 + T340 + T234 + T341 + T235 + T342 + T236 + T343 + T176 + T344) *
             T231 +
         (T345 + T346 + T347 + T348 + T349 + T350 + T351 + T352 + T353 + T354 +
          T355 + T356 + T357 + T168 + T358) *
             T190;
  return (T407 +
          (T359 + (T360 + T361 + T170 + T171 + T172 + T173 + T174) * D[7] +
           T362 + (T361 + T170 + T171 + T172 + T173 + T174) * D[6] + T363 +
           T233 + T364 + T234 + T365 + T235 + T366 + T236 + T367 + T176 +
           T368) *
              T146 +
          (T369 + T370 + T371 + T372 + T373 + T101 + T374 + T103 + T375 + T105 +
           T376 + T107 + T377 + T109 + T378) *
              T116 +
          (T379 + (T380 + T381 + T289 + T290 + T291 + T292 + T293) * D[7] +
           T382 + (T381 + T289 + T290 + T291 + T292 + T293) * D[6] + T383 +
           T315 + T384 + T317 + T385 + T319 + T386 + T321 + T387 + T294 +
           T388) *
              T77 +
          (T389 + T390 + T391 + T392 + T393 + T250 + T394 + T251 + T395 + T252 +
           T396 + T253 + T397 + T254 + T398) *
              T58 +
          (T8 + (T399 + T400) * D[7] + T9 + T401 + T16 + T17 + T18 + T19 + T20 +
           T21) *
              H) /
         6;
}
