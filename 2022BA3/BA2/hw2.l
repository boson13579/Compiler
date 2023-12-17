%{
#include <stdio.h>

//if using not prototype type
//should define here 
#include <stdbool.h>
typedef struct {
    bool arr[15];
    int i;
}len;

#include "hw2.tab.h" 

%}

%%

"<and>" {return(AND);}
"</and>" {return(EAND);}
"<or>" {return(OR);}
"</or>" {return(EOR);}
"<not>" {return(NOT);}
"</not>" {return(ENOT);}
"<true/>" {return(TRUE);}
"<false/>" {return(FALSE);}
\n {;}
\t {;}
. {;}

%%

