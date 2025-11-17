/* --- Generated the 16/11/2025 at 12:19 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc railroad1.ept -target c -targetpath ./railroad1c --- */

#ifndef RAILROAD1_TYPES_H
#define RAILROAD1_TYPES_H

#include "stdbool.h"
#include "assert.h"
#include "pervasives.h"
typedef enum {
  Railroad1__St_Wait,
  Railroad1__St_Bridge,
  Railroad1__St_Away
} Railroad1__st;

Railroad1__st Railroad1__st_of_string(char* s);

char* string_of_Railroad1__st(Railroad1__st x, char* buf);

#endif // RAILROAD1_TYPES_H
