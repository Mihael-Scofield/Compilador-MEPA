%{
#include "posfixo.tab.h"
%}

%%

[\n\t ]  

\+    { return MAIS; }
\-    { return MENOS; }
\*    { return ASTERISCO;  }
\/    { return DIV;  }
a     { return INT;   }
b     { return BOOL;   }
and   { return AND; }
or    { return OR; }

%%

