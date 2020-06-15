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
#include "libc/str/str.h"
#include "tool/build/lib/elfwriter.h"

void elfwriter_yoink(struct ElfWriter *elf, const char *symbol) {
  unsigned char *p;
  struct ElfWriterSymRef sym;
  const unsigned char nopl[8] = "\x0f\x1f\x04\x25\x00\x00\x00\x00";
  p = elfwriter_reserve(elf, 8);
  memcpy(p, nopl, sizeof(nopl));
  sym = elfwriter_linksym(elf, symbol, ELF64_ST_INFO(STB_GLOBAL, STT_OBJECT),
                          STV_HIDDEN);
  elfwriter_appendrela(elf, sizeof(nopl) - 4, sym, R_X86_64_32, 0);
  elfwriter_commit(elf, sizeof(nopl));
}
