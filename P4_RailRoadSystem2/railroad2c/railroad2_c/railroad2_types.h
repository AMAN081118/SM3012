/* --- Generated the 16/11/2025 at 12:57 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc railroad2.ept -target c -targetpath ./railroad2c --- */

#ifndef RAILROAD2_TYPES_H
#define RAILROAD2_TYPES_H

#include "stdbool.h"
#include "assert.h"
#include "pervasives.h"
typedef enum {
  Railroad2__St_Wait,
  Railroad2__St_Bridge,
  Railroad2__St_Away
} Railroad2__st;

Railroad2__st Railroad2__st_of_string(char* s);

char* string_of_Railroad2__st(Railroad2__st x, char* buf);

#endif // RAILROAD2_TYPES_H
