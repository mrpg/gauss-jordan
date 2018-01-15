/*
 * colors.h
 *
 * This file is hereby placed in the PUBLIC DOMAIN. Note that the
 * other files have been released under the GNU General Public License
 * version 2 or any later version.
 *
 * There is NO WARRANTY.
 *
 */

#ifndef COLORS_H
#define COLORS_H

#define COL_RED "\x1B[31m"
#define COL_GREEN "\x1B[32m"
#define COL_BLUE "\x1B[34m"
#define COL_WHITE "\x1B[37m"
#define COL_NONE "\x1B[0m"
#define COL_BOLD "\033[1m"

#define COLOR(COL, STRING) COL_##COL STRING COL_NONE

#endif
