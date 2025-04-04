#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <unistd.h>

int encode(char* iter, char* in, char* out, char* path) {

  pid_t child = fork();

  if (child == 0) {
    printf("child\n");

    int code = execl(path, "openssl", "enc", "-aes-256-cbc", "-e", "-iter", iter, "-salt", "-in", in, "-out", out, NULL);

    if (code != -1) {
      return errno;
    }
  }
 return 0;
}

int main() {

  printf("bruh\n");

  char* path = "/usr/bin/openssl";

  int exitCode = encode("1000", "test.txt", "test.enc", path);

  int status;
  wait(&status);

  printf("errno: %i\n", exitCode);



  return 0;
}
