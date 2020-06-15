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
#include "libc/dce.h"
#include "libc/nt/files.h"
#include "libc/str/str.h"
#include "libc/calls/internal.h"
#include "libc/sysv/errfuns.h"
#include "libc/sysv/consts/at.h"

/**
 * Deletes file.
 *
 * Please note the deletion process has different interesting properties
 * on each platform. For example, on System V, if open descriptors exist
 * then only the name of the file is removed and it's actually deleted
 * later on when appropriate.
 *
 * @return 0 on success, or -1 w/ errno
 * @asyncsignalsafe
 */
int unlink(const char *name) {
  if (!name) return 0;
  if (!IsWindows()) {
    return unlinkat$sysv(AT_FDCWD, name, 0);
  } else {
    return unlink$nt(name);
  }
}
