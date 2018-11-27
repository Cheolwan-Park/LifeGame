#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef __WIN32__
#define c "cls"
#else
#define c "clear"
#endif

const char *game =
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                   x                    "
    "                     x                  "
    "                  xx  xxx               "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        "
    "                                        ";

int main(int argc, char *argv[]){
  char *map = 0, *imap, *buf=0, *ibuf;
  int w=0, h=0, i=0, j=0, s=0, mw=0, mh=0, x=0, y=0;

  // dummy data
  w = 40;
  h = 20;
  mw = 300;
  mh = 300;

  s = mw*mh;
  map = (char*)malloc(s);
  buf = (char*)malloc(s);
  memset(map, 0, s);
  memset(buf, 0, s);

  x = (mw-w)/2;
  y = (mh-h)/2;

  for(i=0; i<h; ++i) {
    for(j=0; j<w; ++j) {
      imap = map+(y+i)*mw+x+j;
      if(game[i*w+j] != 32) {
        *imap = 1;
      }
      else {
        *imap = 0;
      }
    }
  }

  int loop = 1;
  while(loop) {
    // counting
    for(i=0; i<mh; ++i) {
      imap = map+i*mw;
      ibuf = buf+i*mw;
      for(j=0; j<mw-2; ++j) {
        *ibuf = *imap + *(imap+1) + *(imap+2);
        ++ibuf;
        ++imap;
      }
    }

    for(i=0; i<mh-2; ++i) {
      ibuf = buf+i*mw;
      for(j=0; j<mw; ++j) {
        *ibuf = *ibuf + *(ibuf+mw) + *(ibuf+2*mw);
        ++ibuf;
      }
    }

    // updating
    for(i=1; i<mh-1; ++i) {
      for(j=1; j<mw-1; ++j) {
        s = buf[(i-1)*mw+j-1];
        imap = map+i*mw+j;
        if(*imap) {
          --s;
          *imap = 0;
          if(s == 2 || s == 3) {
            *imap = 1;
          }
        } else {
          if(s == 3) {
            *imap = 1;
          }
        }
      }
    }

//     print
    system(c);
    for(i=1; i<mh-1; ++i) {
      for(j=1; j<mw-1; ++j) {
        if(map[i*mw+j]) {
          printf("x ");
        } else {
          printf("  ");
        }
      }
      printf("\n");
    }
    printf("\n");
    usleep(200000);
  }
}