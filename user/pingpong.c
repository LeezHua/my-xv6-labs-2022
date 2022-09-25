#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv [ ]) {
  int pp[2];
  char buf[5];
  int status = 0;
  int pid;

  pipe(pp);
  if ( fork() == 0 ) {
    pid = getpid();
    read(pp[0], buf, 4);
    write(pp[1], "pong", 4);
    printf("%d: received %s\n", pid, buf);
  }
  else {
    pid = getpid();
    write(pp[1], "ping", 4);
    wait(&status);
    read(pp[0], buf, 4);
    printf("%d: received %s\n", pid, buf);
  }
  close(pp[0]);
  close(pp[1]);

  exit(0);
}
