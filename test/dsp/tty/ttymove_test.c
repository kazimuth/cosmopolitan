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
#include "dsp/tty/tty.h"
#include "libc/bits/bits.h"
#include "libc/rand/rand.h"
#include "libc/str/str.h"
#include "libc/testlib/ezbench.h"
#include "libc/testlib/testlib.h"

char p[16];
struct TtyCursor c;

void SetUp(void) { rngset(p, sizeof(p), rand64, -1); }

TEST(ttymove, sameCoord_doesNothing) {
  c.y = 0;
  c.x = 0;
  EXPECT_EQ(0, ttymove(&c, p, 0, 0) - p);
  EXPECT_STREQ("", p);
  EXPECT_EQ(0, c.y);
  EXPECT_EQ(0, c.x);
}

TEST(ttymove, crlf) {
  c.y = 0;
  c.x = 10;
  EXPECT_EQ(2, ttymove(&c, p, 1, 0) - p);
  EXPECT_STREQ("\r\n", p);
  EXPECT_EQ(1, c.y);
  EXPECT_EQ(0, c.x);
}

TEST(ttymove, cr) {
  c.y = 7;
  c.x = 10;
  EXPECT_EQ(1, ttymove(&c, p, 7, 0) - p);
  EXPECT_STREQ("\r", p);
  EXPECT_EQ(7, c.y);
  EXPECT_EQ(0, c.x);
}

TEST(ttymove, forwardOne) {
  c.y = 0;
  c.x = 10;
  EXPECT_EQ(3, ttymove(&c, p, 0, 11) - p);
  EXPECT_STREQ("\e[C", p);
  EXPECT_EQ(0, c.y);
  EXPECT_EQ(11, c.x);
}

TEST(ttymove, forwardTwo) {
  c.y = 0;
  c.x = 0;
  EXPECT_EQ(4, ttymove(&c, p, 0, 2) - p);
  EXPECT_STREQ("\e[2C", p);
  EXPECT_EQ(0, c.y);
  EXPECT_EQ(2, c.x);
}

TEST(ttymove, forwardHuge_moves255increments) {
  c.y = 0;
  c.x = 0;
  EXPECT_EQ(6 + 3, ttymove(&c, p, 0, 256) - p);
  EXPECT_STREQ("\e[255C\e[C", p);
  EXPECT_EQ(0, c.y);
  EXPECT_EQ(256, c.x);
}

TEST(ttymove, topleft) {
  c.y = 1000;
  c.x = 888;
  EXPECT_EQ(3, ttymove(&c, p, 0, 0) - p);
  EXPECT_STREQ("\e[H", p);
  EXPECT_EQ(0, c.y);
  EXPECT_EQ(0, c.x);
}

#define MOVE(WANT, Y, X)                             \
  EXPECT_EQ(strlen(WANT), ttymove(&c, p, Y, X) - p); \
  EXPECT_STREQ(WANT, p);                             \
  EXPECT_EQ(Y, c.y);                                 \
  EXPECT_EQ(X, c.x)

TEST(ttymove, absoluteYandX_is1indexed) {
  c.y = 1000;
  c.x = 888;
  MOVE("\e[4;3H", 3, 2);
}

TEST(ttymove, absoluteYandX_implicit1y) {
  c.y = 1000;
  c.x = 888;
  MOVE("\e[;3H", 0, 2);
}

TEST(ttymove, absoluteYandX_implicit1x) {
  c.y = 1000;
  c.x = 888;
  MOVE("\e[4H", 3, 0);
}

TEST(ttymove, up) {
  c.y = 70, c.x = 70;
  MOVE("\eM", 69, 70);
  c.y = 70, c.x = 70;
  MOVE("\e[2A", 68, 70);
}

TEST(ttymove, down) {
  c.y = 70, c.x = 70;
  MOVE("\eD", 71, 70);
  c.y = 70, c.x = 70;
  MOVE("\e[2B", 72, 70);
}

TEST(ttymove, right) {
  c.y = 70, c.x = 70;
  MOVE("\e[C", 70, 71);
  c.y = 70, c.x = 70;
  MOVE("\e[2C", 70, 72);
  c.y = 70, c.x = 0;
  MOVE("\e[123C", 70, 123);
}

TEST(ttymove, left) {
  c.y = 70, c.x = 70;
  MOVE("\e[D", 70, 69);
  c.y = 70, c.x = 70;
  MOVE("\e[2D", 70, 68);
}

/* TEST(ttymove, bench_absmove) { */
/*   EZBENCH( */
/*       { */
/*         c.y = 70; */
/*         c.x = 30; */
/*       }, */
/*       ttymove(&c, p, 7, 9)); */
/*   ASSERT_STREQ("\e[8;10H", p); */
/* } */

/* TEST(ttymove, bench_crlf) { */
/*   EZBENCH( */
/*       { */
/*         c.y = 0; */
/*         c.x = 10; */
/*       }, */
/*       ttymove(&c, p, 1, 0)); */
/*   ASSERT_STREQ("\r\n", p); */
/* } */

/* TEST(ttymove, bench_forward1) { */
/*   EZBENCH( */
/*       { */
/*         c.y = 0; */
/*         c.x = 10; */
/*       }, */
/*       ttymove(&c, p, 0, 11)); */
/*   ASSERT_STREQ("\e[C", p); */
/* } */

/* TEST(ttymove, bench_forward2) { */
/*   int y2, x2; */
/*   EZBENCH( */
/*       { */
/*         y2 = rand32() & 127; */
/*         x2 = rand32() & 127; */
/*         c.y = rand32() & 127; */
/*         c.x = rand32() & 127; */
/*       }, */
/*       ttymove(&c, p, y2, x2)); */
/*   int z; */
/*   EZBENCH(z = rand32() & 127, _memcpy(&z, "\e[2C", 4)); */
/* } */
