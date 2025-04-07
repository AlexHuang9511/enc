#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <unistd.h>

#define PATH "/usr/bin/openssl";
#define FILE_ENC "file.enc"
#define FILE_TXT "file.txt"

int encode() {

  pid_t child = fork();

  if (child == 0) {
    printf("child\n");
    char *path = PATH;
    char *in = FILE_ENC;
    char *out = FILE_TXT;
    char iter[4];

    printf("Enter iter: ");
    fflush(stdout);
    fflush(stdin);
    read(STDIN_FILENO, iter, sizeof(iter));

    int code = execl(path, "openssl", "enc", "-aes-256-cbc", "-e", "-iter",
                     iter, "-salt", "-in", in, "-out", out, NULL);

    if (code != -1) {
      return errno;
    }
  }
  return 0;
}

int decode(char *iter, char *in, char *out) {

  pid_t child = fork();

  if (child == 0) {
    printf("child\n");
    char *path = PATH;
    char *out = FILE_TXT;
    char *in = FILE_ENC;
    char iter[4];

    printf("Enter iter: ");
    fflush(stdout);
    read(STDIN_FILENO, iter, sizeof(iter));

    int code = execl(path, "openssl", "enc", "-aes-256-cbc", "-d", "-iter",
                     iter, "-in", in, "-out", out, NULL);

    if (code != -1) {
      return errno;
    }
  }
  return 0;
}

int main() {
  char buf[1];

  printf("1 - encrypt\n");
  printf("2 - decrypt\n");
  printf("3 - add\n");
  printf("-> ");
  fflush(stdout);
  fflush(stdin);
  fgets(buf, sizeof(buf), stdin);
  fflush(stdin);

  printf("input: --%s--\n", buf);

  if (strcmp(buf, "1") == 0) {

    printf("encode\n");

    int exitCode = encode();
    int status;
    wait(&status);
    if (exitCode != 0) {
      printf("exitCode: %i\n", exitCode);
    }

  } else if (strcmp(buf, "2") == 0) {

    printf("decode\n");

    int exitCode = decode("1000", "test.txt", "test.enc");
    int status;
    wait(&status);
    if (exitCode != 0) {
      printf("exitCode: %i\n", exitCode);
    }
  } else if (strcmp(buf, "3") == 0) {

    printf("add\n");

  } else {
    printf("unknown: '%s'\n", buf);
  }

  // printf("errno: %i\n", exitCode);

  return 0;
}
