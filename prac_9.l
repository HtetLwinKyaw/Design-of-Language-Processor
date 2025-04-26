%{
#include "y.tab.h"
%}

%%

i      { return I; }
t      { return T; }
e      { return 'e'; }
b      { return B; }
a      { return A; }
[ \t\n]  ; /* Ignore whitespace */
.      { return -1; } /* Invalid token */

%%

int yywrap() {
    return 1;
}
