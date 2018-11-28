#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


const int BOARD_WIDTH = 400;
const int BOARD_HEIGHT = 300;
const int SIMULATION_INTERVAL = 80000;

#if defined(_WIN32) || defined(_WIN64)
#define c "cls"
#else
#define c "clear"
#endif
#define z BOARD_WIDTH
#define v BOARD_HEIGHT
#define u SIMULATION_INTERVAL
#define S(f) (fseek(f,0,SEEK_END))
#define M (char*)malloc
#define P printf
#define I int
#define C char
#define R return
#define W while
#define F for
#define E else
#define V system

w,h,i,j,                  s,x,y,l;main(I      t,C**n){C m[v][z]={0     },b[v][z]={0},*q,*e,
*g;FILE*                  f=0;if(2!=t){R      -1;}f=fopen(n[1],"rb"    );if(!f){R -1;}S(f);
l=ftell(                    f);rewind         (f);g=M(                 l);fread
(g,1,l,f                    );fclose(         f);W(i<l){if(g[i]==      10){w=w>x?w:x;x=0;++
h;}E{++x                    ;}++i;}x=         (z-w)/2;y=(v-h)/2;s      =0;F(i=0;s<l;++i){F(
j=0;10!=                    g[s]&&s<l         ;++j){e=                 &m[y+i][
x+j];if(g[s]!=32){*e      =1;}E{*e=0;}++      s;}++s;}                 free(g);W(1){F(i=0;i
<v;++i){e=m[i];q =b[      i];F(j=0;j<z-2      ;++j){*q                 =*e+*(e+1)+*(e+2);++
    
q;++ e ; I you_cannot_read_this=0 ;}}F( i=0;i<v-2 ; ++i ) { I lifegame_is_lifgame=1; q = b[


              i];F(j=0;j<z;      ++j){*q      =*q+*   (q+z)   +*(q+2*z);++q
              ;}}F(i=1;i<v-    1;++i){F(j=    1;j<z- 1;++j)   {s=b[i-1][j-1
              ];e=             &m[    i][j    ];if(*e){--s;   *e=0
              ;if(   s==2||    s==    3){*    e=1  ;}   }E{   if(s==3){*e=1
              ;}}}     }V(c    );F(i=1;i<v    -1;  ++   i){   F(j=
              1;j<z-1;++j){    if(    m[i]    [j]       ){P   ("x ");} E {P
              ("  ");} } P(    "\n"   );}     P (       "\n"  );usleep(u);}}
