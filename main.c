#include <errno.h>
#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  printf("bruh\n");

  pid_t child = fork();
  printf("child pid: %d\n", child);

  if (child == 0) {
    printf("childish bruh\n");
    int code = execl("/bin/ls", "ls", "-l", "-a", "-h", NULL);
    printf("exit code: %i\n", code);

    switch (errno) {
    case EACCES:
      printf("access error\n");
      break;
    case ENOENT:
      printf("path does not exist\n");
      break;
    case EFAULT:
      printf("fault\n");
      break;
    default:
      printf("other error\n");
      printf("errno: %i\n", errno);
    }
  }

  return 0;
}
