#ifndef COSMOPOLITAN_LIBC_DOS_H_
#define COSMOPOLITAN_LIBC_DOS_H_

/**
 * @fileoverview MS-DOS Data Structures.
 */

#define DOS_DATE(YEAR, MONTH_IDX1, DAY_IDX1) \
  (((YEAR)-1980) << 9 | (MONTH_IDX1) << 5 | (DAY_IDX1))

#define DOS_TIME(HOUR, MINUTE, SECOND) \
  ((HOUR) << 11 | (MINUTE) << 5 | (SECOND) >> 1)

#endif /* COSMOPOLITAN_LIBC_DOS_H_ */
