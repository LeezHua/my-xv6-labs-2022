#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAXMEM 512

int main(int argc, char* argv [ ]) {
  char ch;
  char* args[MAXARG] = { 0 };
  char* tmp = 0;
  void* NULL = 0;
  int i, j = 0;
  int n;      //当前已分配空间的参数个数
  ushort f = 0; //前一个字母是否是空格

  for ( i = 0;i < argc - 1;++i )
    args[i] = argv[i + 1];
  args[i] = malloc(MAXMEM);
  n = i;

  while ( read(0, &ch, 1) == 1 ) {
    if ( ch == '\n' ) {
      tmp = args[i + 1];
      args[i][j] = 0;
      args[i + 1] = NULL;   
      if ( fork() == 0 ) {
        exec(args[0], args);
        exit(1);
      }
      else {
        wait(0);
        args[i + 1] = tmp;
        i = argc - 1;
        j = 0;
      }
    }
    else if ( ch == ' ' ) {
      if ( f ) {
        args[i][j] = 0;
        j = 0;
        f = 0;
      }
    }
    else {
      if ( !f ) {
        if ( i + 1 < MAXARG ) {
          if ( i == n ) {
            args[i + 1] = malloc(MAXMEM);
            ++n;
          }
          ++i;
          f = 1;
        }
      }
      args[i][j++] = ch;
    }
  }
  for ( i = argc;i <= n;++i ) {
    memset(args[i], 0, sizeof(args[i]));
    free(args[i]);
  }

  exit(0);
}
