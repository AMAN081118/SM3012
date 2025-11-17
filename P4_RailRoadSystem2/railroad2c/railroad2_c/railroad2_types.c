/* --- Generated the 16/11/2025 at 12:57 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc railroad2.ept -target c -targetpath ./railroad2c --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "railroad2_types.h"

Railroad2__st Railroad2__st_of_string(char* s) {
  if ((strcmp(s, "St_Wait")==0)) {
    return Railroad2__St_Wait;
  };
  if ((strcmp(s, "St_Bridge")==0)) {
    return Railroad2__St_Bridge;
  };
  if ((strcmp(s, "St_Away")==0)) {
    return Railroad2__St_Away;
  };
}

char* string_of_Railroad2__st(Railroad2__st x, char* buf) {
  switch (x) {
    case Railroad2__St_Wait:
      strcpy(buf, "St_Wait");
      break;
    case Railroad2__St_Bridge:
      strcpy(buf, "St_Bridge");
      break;
    case Railroad2__St_Away:
      strcpy(buf, "St_Away");
      break;
    default:
      break;
  };
  return buf;
}

