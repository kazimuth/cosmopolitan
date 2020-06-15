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
#include "dsp/mpeg/mpeg.h"
#include "libc/limits.h"
#include "libc/log/check.h"
#include "libc/macros.h"
#include "libc/nexgen32e/x86feature.h"
#include "libc/rand/rand.h"
#include "libc/runtime/buffer.h"
#include "libc/testlib/ezbench.h"
#include "libc/testlib/testlib.h"

short pcm[8][8];

TEST(scalevolume, testIncreaseVolumeByOneIncrement) {
  pcm[0][0] = INT16_MIN;
  pcm[0][1] = INT16_MIN / 2;
  pcm[0][2] = -2;
  pcm[0][3] = -1;
  pcm[0][4] = 0;
  pcm[0][5] = 1;
  pcm[0][6] = 2;
  pcm[0][7] = INT16_MAX / 2;
  pcm[1][0] = INT16_MAX;
  scalevolume(ARRAYLEN(pcm), pcm, 1);
  EXPECT_EQ(INT16_MIN, pcm[0][0]);
  EXPECT_EQ(INT16_MIN, pcm[0][1]);
  EXPECT_EQ(-4, pcm[0][2]);
  EXPECT_EQ(-2, pcm[0][3]);
  EXPECT_EQ(0, pcm[0][4]);
  EXPECT_EQ(2, pcm[0][5]);
  EXPECT_EQ(4, pcm[0][6]);
  EXPECT_EQ(INT16_MAX - 1, pcm[0][7]);
  EXPECT_EQ(INT16_MAX, pcm[1][0]);
}

TEST(scalevolume, testDecreaseVolumeByOneIncrement) {
  pcm[0][0] = INT16_MIN;
  pcm[0][1] = INT16_MIN / 2;
  pcm[0][2] = -2;
  pcm[0][3] = -1;
  pcm[0][4] = 0;
  pcm[0][5] = 1;
  pcm[0][6] = 2;
  pcm[0][7] = INT16_MAX / 2;
  pcm[1][0] = INT16_MAX;
  scalevolume(ARRAYLEN(pcm), pcm, -1);
  EXPECT_EQ(INT16_MIN / 2, pcm[0][0]);
  EXPECT_EQ(INT16_MIN / 4, pcm[0][1]);
  EXPECT_EQ(-1, pcm[0][2]);
  EXPECT_EQ(-1, pcm[0][3]);
  EXPECT_EQ(0, pcm[0][4]);
  EXPECT_EQ(0, pcm[0][5]);
  EXPECT_EQ(1, pcm[0][6]);
  EXPECT_EQ(INT16_MAX / 4, pcm[0][7]);
  EXPECT_EQ(INT16_MAX / 2, pcm[1][0]);
}

TEST(scalevolume, testScaleByZero_doesNothing) {
  pcm[0][0] = INT16_MIN;
  pcm[0][1] = INT16_MIN / 2;
  pcm[0][2] = -2;
  pcm[0][3] = -1;
  pcm[0][4] = 0;
  pcm[0][5] = 1;
  pcm[0][6] = 2;
  pcm[0][7] = INT16_MAX / 2;
  pcm[1][0] = INT16_MAX;
  scalevolume(ARRAYLEN(pcm), pcm, 0);
  EXPECT_EQ(INT16_MIN, pcm[0][0]);
  EXPECT_EQ(INT16_MIN / 2, pcm[0][1]);
  EXPECT_EQ(-2, pcm[0][2]);
  EXPECT_EQ(-1, pcm[0][3]);
  EXPECT_EQ(0, pcm[0][4]);
  EXPECT_EQ(1, pcm[0][5]);
  EXPECT_EQ(2, pcm[0][6]);
  EXPECT_EQ(INT16_MAX / 2, pcm[0][7]);
  EXPECT_EQ(INT16_MAX, pcm[1][0]);
}

TEST(scalevolume, testBiggestScale_justSaturates) {
  pcm[0][0] = INT16_MIN;
  pcm[0][1] = INT16_MIN / 2;
  pcm[0][2] = -2;
  pcm[0][3] = -1;
  pcm[0][4] = 0;
  pcm[0][5] = 1;
  pcm[0][6] = 2;
  pcm[0][7] = INT16_MAX / 2;
  pcm[1][0] = INT16_MAX;
  scalevolume(ARRAYLEN(pcm), pcm, 123);
  EXPECT_EQ(INT16_MIN, pcm[0][0]);
  EXPECT_EQ(INT16_MIN, pcm[0][1]);
  EXPECT_EQ(INT16_MIN, pcm[0][2]);
  EXPECT_EQ(INT16_MIN, pcm[0][3]);
  EXPECT_EQ(0, pcm[0][4]);
  EXPECT_EQ(INT16_MAX, pcm[0][5]);
  EXPECT_EQ(INT16_MAX, pcm[0][6]);
  EXPECT_EQ(INT16_MAX, pcm[0][7]);
  EXPECT_EQ(INT16_MAX, pcm[1][0]);
}

TEST(scalevolume, testSmallestScale_justSaturates) {
  pcm[0][0] = INT16_MIN;
  pcm[0][1] = INT16_MIN / 2;
  pcm[0][2] = -2;
  pcm[0][3] = -1;
  pcm[0][4] = 0;
  pcm[0][5] = 1;
  pcm[0][6] = 2;
  pcm[0][7] = INT16_MAX / 2;
  pcm[1][0] = INT16_MAX;
  scalevolume(ARRAYLEN(pcm), pcm, -123);
  EXPECT_EQ(-1, pcm[0][0]);
  EXPECT_EQ(-1, pcm[0][1]);
  EXPECT_EQ(-1, pcm[0][2]);
  EXPECT_EQ(-1, pcm[0][3]);
  EXPECT_EQ(0, pcm[0][4]);
  EXPECT_EQ(0, pcm[0][5]);
  EXPECT_EQ(0, pcm[0][6]);
  EXPECT_EQ(0, pcm[0][7]);
  EXPECT_EQ(0, pcm[1][0]);
}

//////////////////////////////////////////////////////////////////////
// audio volume adjustment latency:
//   -   ~1µs w/ -Os
//   - ~500ns w/ -O3
//   - ~200ns w/ -O3 -march=skylake MODE=rel

void randomizeaudio(void) {
  rngset(pcm, sizeof(pcm), rand64, -1);
}

void scalevolume_pure(int amt) {
  scalevolume(ARRAYLEN(pcm), pcm, amt);
}

BENCH(scalevolume, audioframe) {
  EZBENCH(randomizeaudio(), scalevolume_pure(0));
  EZBENCH(randomizeaudio(), scalevolume_pure(1));
  EZBENCH(randomizeaudio(), scalevolume_pure(15));
}
