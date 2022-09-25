#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv [ ]) {
  int pp[2], fd;
  int prime, num;
  int status = 0;

  pipe(pp);
  for ( num = 2;num <= 35;++num )
    write(pp[1], &num, sizeof(num));
  fd = dup(pp[0]);
  close(pp[0]);
  close(pp[1]);
  read(fd, &prime, sizeof(prime));
  pipe(pp);

  while ( fork() == 0 ) {
    fd = dup(pp[0]);
    close(pp[0]);
    close(pp[1]);
    //最后一个进程
    if ( read(fd, &prime, sizeof(prime)) != sizeof(prime) ) {
      close(fd);
      exit(0);
    }
    pipe(pp);
  }

  printf("prime %d\n", prime);
  while ( read(fd, &num, sizeof(num)) == sizeof(num) ) {
    if ( num % prime != 0 )
      write(pp[1], &num, sizeof(num));
  }
  close(pp[0]);
  close(pp[1]);
  close(fd);
  wait(&status);


  exit(0);
}
