#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv [ ]) {
  if ( argc < 2 ) {
    printf("sleep: Incorrect format\n");
    printf("Usage: sleep <time>...\n");
    exit(0);
  }
  int num = 0, i;
  for ( i = 1;i < argc;++i ) {
    num += atoi(argv[i]);
  }
  sleep(num);

  exit(0);
}
