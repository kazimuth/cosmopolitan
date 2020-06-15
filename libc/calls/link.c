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
#include "libc/calls/internal.h"
#include "libc/calls/calls.h"
#include "libc/sysv/errfuns.h"
#include "libc/sysv/consts/at.h"

/**
 * Creates hard filesystem link.
 *
 * This allows two names to point to the same file data on disk. They
 * can only be differentiated by examining the inode number.
 *
 * @return 0 on success, or -1 w/ errno
 * @asyncsignalsafe
 */
int link(const char *existingpath, const char *newpath) {
  if (!existingpath || !newpath) return efault();
  if (!IsWindows()) {
    return linkat$sysv(AT_FDCWD, existingpath, AT_FDCWD, newpath, 0);
  } else {
    return link$nt(existingpath, newpath);
  }
}
