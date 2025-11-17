/* --- Generated the 16/11/2025 at 12:19 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc railroad1.ept -target c -targetpath ./railroad1c --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "railroad1_types.h"

Railroad1__st Railroad1__st_of_string(char* s) {
  if ((strcmp(s, "St_Wait")==0)) {
    return Railroad1__St_Wait;
  };
  if ((strcmp(s, "St_Bridge")==0)) {
    return Railroad1__St_Bridge;
  };
  if ((strcmp(s, "St_Away")==0)) {
    return Railroad1__St_Away;
  };
}

char* string_of_Railroad1__st(Railroad1__st x, char* buf) {
  switch (x) {
    case Railroad1__St_Wait:
      strcpy(buf, "St_Wait");
      break;
    case Railroad1__St_Bridge:
      strcpy(buf, "St_Bridge");
      break;
    case Railroad1__St_Away:
      strcpy(buf, "St_Away");
      break;
    default:
      break;
  };
  return buf;
}

