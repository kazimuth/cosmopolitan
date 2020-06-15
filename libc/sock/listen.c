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
#include "libc/calls/internal.h"
#include "libc/dce.h"
#include "libc/sock/internal.h"
#include "libc/sock/sock.h"
#include "libc/sysv/errfuns.h"

/**
 * Asks system to accept incoming connections on socket.
 *
 * The socket() and bind() functions need to be called beforehand. Once
 * this function is called, accept() is used to wait for connections.
 * Using this on connectionless sockets will allow it to receive packets
 * on a designated address.
 *
 * @param backlog <= SOMAXCONN
 * @return 0 on success or -1 w/ errno
 */
int listen(int fd, int backlog) {
  if (!IsWindows()) {
    return listen$sysv(fd, backlog);
  } else if (isfdkind(fd, kFdSocket)) {
    return listen$nt(&g_fds.p[fd], backlog);
  } else {
    return ebadf();
  }
}
