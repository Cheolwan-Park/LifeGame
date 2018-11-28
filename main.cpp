#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
#define c "cls"
#else
#define c "clear"
#endif

const int BOARD_WIDTH = 400;
const int BOARD_HEIGHT = 300;
const int SIMULATION_INTERVAL = 200000;
#define mw BOARD_WIDTH
#define mh BOARD_HEIGHT


int main(int argc, char *argv[]){
  int w=0, h=1, i=0, j=0, s=0, x=0, y=0;
  long l = 0;
  char map[mh][mw]={0}, buf[mh][mw]={0}, *ibuf, *imap, *g=nullptr;
  FILE *f = 0;


  if(2 != argc) {
    printf("usage : LifeGame.exe <game filename>\n");
    return -1;
  }
  f = fopen(argv[1], "rb");
  if(!f) {
    printf("%s not exist\n", argv[1]);
    return -1;
  }
  fseek(f, 0, SEEK_END);
  l = ftell(f);
  rewind(f);
  g = (char*)malloc(l);
  fread(g, 1, l, f);
  fclose(f);

  while(i<l) {
    if(g[i] == 10) {
      w = w > x ? w : x;
      x=0;
      ++h;
    } else {
      ++x;
    }
    ++i;
  }
  printf("\n");

  x = (mw-w)/2;
  y = (mh-h)/2;

  s = 0;
  for(i=0; s<l; ++i) {
    for(j=0; 10 != g[s] && s<l; ++j) {
      imap = &map[y+i][x+j];
      if(g[s] != 32) {
        *imap = 1;
      }
      else {
        *imap = 0;
      }
      ++s;
    }
    ++s;
  }
  free(g);

  int loop = 1;
  while(loop) {
    // counting
    for(i=0; i<mh; ++i) {
      imap = map[i];
      ibuf = buf[i];
      for(j=0; j<mw-2; ++j) {
        *ibuf = *imap + *(imap+1) + *(imap+2);
        ++ibuf;
        ++imap;
      }
    }

    for(i=0; i<mh-2; ++i) {
      ibuf = buf[i];
      for(j=0; j<mw; ++j) {
        *ibuf = *ibuf + *(ibuf+mw) + *(ibuf+2*mw);
        ++ibuf;
      }
    }

    // updating
    for(i=1; i<mh-1; ++i) {
      for(j=1; j<mw-1; ++j) {
        s = buf[i-1][j-1];
        imap = &map[i][j];
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

    // print
    system(c);
    for(i=1; i<mh-1; ++i) {
      for(j=1; j<mw-1; ++j) {
        if(map[i][j]) {
          printf("x ");
        } else {
          printf("  ");
        }
      }
      printf("\n");
    }
    printf("\n");
    usleep(SIMULATION_INTERVAL);
  }
}