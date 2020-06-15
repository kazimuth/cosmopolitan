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
#include "libc/bits/bits.h"
#include "libc/macros.h"
#include "libc/nexgen32e/x86info.h"

const struct X86ProcessorModel kX86ProcessorModels[] = {
    /* <SORTED> */
    {0x060F, X86_MARCH_CORE2, X86_GRADE_CLIENT},
    {0x0616, X86_MARCH_CORE2, X86_GRADE_MOBILE},
    {0x0617, X86_MARCH_CORE2, X86_GRADE_SERVER},
    {0x061A, X86_MARCH_NEHALEM, X86_GRADE_DENSITY},
    {0x061C, X86_MARCH_BONNELL, X86_GRADE_APPLIANCE},
    {0x061D, X86_MARCH_CORE2, X86_GRADE_SERVER},
    {0x061E, X86_MARCH_NEHALEM, X86_GRADE_CLIENT},
    {0x061F, X86_MARCH_NEHALEM, X86_GRADE_DESKTOP},
    {0x0625, X86_MARCH_WESTMERE, X86_GRADE_CLIENT},
    {0x0626, X86_MARCH_BONNELL, X86_GRADE_TABLET},
    {0x0627, X86_MARCH_SALTWELL, X86_GRADE_TABLET},
    {0x062A, X86_MARCH_SANDYBRIDGE, X86_GRADE_CLIENT},
    {0x062C, X86_MARCH_WESTMERE, X86_GRADE_DENSITY},
    {0x062D, X86_MARCH_SANDYBRIDGE, X86_GRADE_SERVER},
    {0x062E, X86_MARCH_NEHALEM, X86_GRADE_SERVER},
    {0x062F, X86_MARCH_WESTMERE, X86_GRADE_SERVER},
    {0x0635, X86_MARCH_SALTWELL, X86_GRADE_TABLET},
    {0x0636, X86_MARCH_SALTWELL, X86_GRADE_APPLIANCE},
    {0x0637, X86_MARCH_SILVERMONT, X86_GRADE_APPLIANCE},
    {0x063A, X86_MARCH_IVYBRIDGE, X86_GRADE_CLIENT},
    {0x063C, X86_MARCH_HASWELL, X86_GRADE_CLIENT},
    {0x063D, X86_MARCH_BROADWELL, X86_GRADE_CLIENT},
    {0x063E, X86_MARCH_IVYBRIDGE, X86_GRADE_SERVER},
    {0x063F, X86_MARCH_HASWELL, X86_GRADE_SERVER},
    {0x0645, X86_MARCH_HASWELL, X86_GRADE_MOBILE},
    {0x0646, X86_MARCH_HASWELL, X86_GRADE_DESKTOP},
    {0x0647, X86_MARCH_BROADWELL, X86_GRADE_DESKTOP},
    {0x064A, X86_MARCH_SILVERMONT, X86_GRADE_TABLET},
    {0x064C, X86_MARCH_AIRMONT, X86_GRADE_APPLIANCE},
    {0x064D, X86_MARCH_SILVERMONT, X86_GRADE_DENSITY},
    {0x064E, X86_MARCH_SKYLAKE, X86_GRADE_MOBILE},
    {0x064F, X86_MARCH_BROADWELL, X86_GRADE_SERVER},
    {0x0655, X86_MARCH_SKYLAKE, X86_GRADE_SERVER},
    {0x0656, X86_MARCH_BROADWELL, X86_GRADE_DENSITY},
    {0x0657, X86_MARCH_KNIGHTSLANDING, X86_GRADE_SCIENCE},
    {0x065A, X86_MARCH_AIRMONT, X86_GRADE_TABLET},
    {0x065C, X86_MARCH_GOLDMONT, X86_GRADE_APPLIANCE},
    {0x065E, X86_MARCH_SKYLAKE, X86_GRADE_CLIENT},
    {0x065F, X86_MARCH_GOLDMONT, X86_GRADE_DENSITY},
    {0x0666, X86_MARCH_CANNONLAKE, X86_GRADE_MOBILE},
    {0x066A, X86_MARCH_ICELAKE, X86_GRADE_SERVER},
    {0x066C, X86_MARCH_ICELAKE, X86_GRADE_DENSITY},
    {0x0675, X86_MARCH_AIRMONT, X86_GRADE_APPLIANCE},
    {0x067A, X86_MARCH_GOLDMONTPLUS, X86_GRADE_APPLIANCE},
    {0x067D, X86_MARCH_ICELAKE, X86_GRADE_CLIENT},
    {0x067E, X86_MARCH_ICELAKE, X86_GRADE_MOBILE},
    {0x0685, X86_MARCH_KNIGHTSMILL, X86_GRADE_SCIENCE},
    {0x0686, X86_MARCH_TREMONT, X86_GRADE_APPLIANCE},
    {0x068C, X86_MARCH_TIGERLAKE, X86_GRADE_MOBILE},
    {0x068D, X86_MARCH_TIGERLAKE, X86_GRADE_CLIENT},
    {0x068E, X86_MARCH_KABYLAKE, X86_GRADE_MOBILE},
    {0x0696, X86_MARCH_TREMONT, X86_GRADE_APPLIANCE},
    {0x069D, X86_MARCH_ICELAKE, X86_GRADE_SCIENCE},
    {0x069E, X86_MARCH_KABYLAKE, X86_GRADE_CLIENT},
    /* </SORTED> */
};

const size_t kX86ProcessorModelCount = ARRAYLEN(kX86ProcessorModels);
