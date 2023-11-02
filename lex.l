%{  
    int tabnum = 0;
%}

leftbrace [^\n\{]*\{[^\n]*\n 
rightbrace [^\n\}]*\}[^\n]*\n
line [^\n\{\}]*\n 

%%
{rightbrace} { 
    tabnum--;
    for(int i=0 ; i<tabnum ; i++) printf("\t"); 
    ECHO;
}
{leftbrace} {
    for(int i=0 ; i<tabnum ; i++) printf("\t"); 
    ECHO;
    tabnum++;
} 
{line} {
    for(int i=0 ; i<tabnum ; i++) printf("\t");
    ECHO;     
}

%%
int main(int argc, char* argv[]){
    yylex();
    return 0;
}