#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_pid_t.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <unistd.h>

int encode(char *iter, char *in, char *out, char *path) {

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
  char buf[10];
  char *path = "/usr/bin/openssl";

  printf("1 - encrypt\n");
  printf("2 - decrypt\n");
  printf("3 - add\n");
  printf("-> ");
  read(STDIN_FILENO, buf, sizeof(buf));

  printf("input: %s\n", buf);

  if (strcmp(buf, "1")) {

    printf("one\n");
    int exitCode = encode("1000", "test.txt", "test.enc", path);
    int status;
    wait(&status);
    if (exitCode != 0) {
      printf("exitCode: %i\n", exitCode);
    }

  } else if (strcmp(buf, "2")) {

    printf("two\n");

  } else if (strcmp(buf, "3")) {

    printf("three\n");

  } else {
    printf("unknown: '%s'\n", buf);
  }



  //printf("errno: %i\n", exitCode);

  return 0;
}
