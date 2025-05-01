#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/_types/_ssize_t.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <unistd.h>

#define PATH "/usr/bin/openssl";
#define ENC "file.enc"
#define TXT "file.txt"

int encode(char *iter, char *in, char *out) {

  pid_t child = fork();

  if (child == 0) {
    printf("child\n");
    char* path = PATH;

    if (access(in, F_OK) != 0) {
      printf("%s does not exist.\n", in);
      return -1;
    }

    int code = execl(path, "openssl", "enc", "-aes-256-cbc", "-e", "-iter", iter, "-salt", "-in", in, "-out", out, NULL);

    if (code != -1) {
      return errno;
    }
  }
  return 0;
}

int decode(char *iter, char* in, char* out) {

  pid_t child = fork();

  if (child == 0) {
    printf("child\n");
    char* path = PATH;

    if (access(in, F_OK) != 0) {
      printf("%s does not exist.\n", in);
      return -1;
    }

    int code = execl(path, "openssl", "enc", "-aes-256-cbc", "-d", "-iter", iter, "-in", in, "-out", out, NULL);

    if (code != -1) {
      return errno;
    }
  }
  return 0;
}

int main() {
  char buf[2];
  char iter[5];
  int c; 
  
  printf("Enter iter: ");
  fflush(stdout);

  fgets(iter, sizeof(iter), stdin);
  //:TODO finish 

  while((c = getchar()) != '\n' && c != EOF);

  printf("1 - encrypt\n");
  printf("2 - decrypt\n");
  printf("3 - add\n");
  printf("-> ");
  fflush(stdout);

  fgets(buf, sizeof(iter), stdin);

  buf[1] = '\0';

  //while((c = getchar()) != '\n' && c != EOF);

  printf("input: --%s--\n", buf);
  printf("iter: --%s--\n", iter);


  if (strcmp(buf, "1") == 0) {

    printf("encode\n");

    int exitCode = encode(iter, TXT, ENC);
    int status;
    wait(&status);
    if (exitCode != 0) {
      printf("exitCode: %i\n", exitCode);
    }

  } else if (strcmp(buf, "2") == 0) {

    printf("decode\n");

    int exitCode = decode(iter, ENC, TXT);
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

  return 0;
}
