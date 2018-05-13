#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>
#include <sys/wait.h>

#define BSIZE 256

#define BASH_EXEC  "/bin/bash"
#define FIND_EXEC  "/usr/bin/find"
#define XARGS_EXEC "/usr/bin/xargs"
#define GREP_EXEC  "/bin/grep"
#define SORT_EXEC  "/usr/bin/sort"
#define HEAD_EXEC  "/usr/bin/head"

int main(int argc, char *argv[])
{
  int status;
  char find[BSIZE];
  bzero(find, BSIZE);
  int mypipe[2]; //first pipe
  int mypipe2[2]; //second pipe
  int mypipe3[3]; //third pipe
  pid_t pid_1, pid_2, pid_3, pid_4;

  if (argc != 4) {
    printf("usage: finder DIR STR NUM_FILES\n");
    exit(0);
  }

  //create a pipe with both windows
  pipe(mypipe); //pipe that connect between pid_1 and pid_2

  pid_1 = fork();
  if (pid_1 == 0) {
    /* First Child */
    sprintf(find, "%s %s -name '*'.[ch]", FIND_EXEC, argv[1]);
    char* myArgs[] = {BASH_EXEC, "-c", find, (char*)0};
    dup2(mypipe[1], 1); //connect mypipein to stdin
    if(execv(BASH_EXEC, myArgs) < 0){
      fprintf((stderr), "\nError execing find. ERROR#%d\n", errno);
      return EXIT_FAILURE;
    }
    exit(0);
  }
  // close parent side
  close(mypipe[1]);
  pipe(mypipe2); //connect pipe between child 2 and child 3
  pid_2 = fork();
  if (pid_2 == 0) {
    /* Second Child */
    dup2(mypipe[0], 0); //connect mypipein to stdin
    dup2(mypipe2[1], 1);
    char find[BSIZE];
    bzero(find, BSIZE);
    sprintf(find, "%s %s -c %s", XARGS_EXEC, GREP_EXEC, argv[2]);
    char* myArgs[] = {BASH_EXEC, "-c", find, (char*)0};
    if(execv(BASH_EXEC, myArgs) < 0){
      fprintf((stderr), "\nError execing find. ERROR#%d\n", errno);
      return EXIT_FAILURE;
    }
    exit(0);
  }
  close(mypipe[0]);
  close(mypipe2[1]);

  pipe(mypipe3);
  pid_3 = fork();
  if (pid_3 == 0) {
    /* Third Child */
    dup2(mypipe2[0], 0);
    dup2(mypipe3[1], 1);
    sprintf(find, "%s -t : +1.0 -2.0 --numeric --reverse", SORT_EXEC);
    char* myArgs[] = {BASH_EXEC, "-c", find, (char*)0};
    if(execv(BASH_EXEC, myArgs) < 0){
      fprintf((stderr), "\nError execing find. ERROR#%d\n", errno);
      return EXIT_FAILURE;
    }
    exit(0);
  }

  close(mypipe3[1]);
  pid_4 = fork();
  if (pid_4 == 0) {
    /* Fourth Child */
    dup2(mypipe3[0], 0);
    sprintf(find, "%s --lines=%s", HEAD_EXEC, argv[3]);
    char* myArgs[] = {BASH_EXEC, "-c", find, (char*)0};
    if(execv(BASH_EXEC, myArgs) < 0){
      fprintf((stderr), "\nError execing find. ERROR#%d\n", errno);
      return EXIT_FAILURE;
    }
    exit(0);
  }

  if ((waitpid(pid_1, &status, 0)) == -1) {
    fprintf(stderr, "Process 1 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }
  if ((waitpid(pid_2, &status, 0)) == -1) {
    fprintf(stderr, "Process 2 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }
  if ((waitpid(pid_3, &status, 0)) == -1) {
    fprintf(stderr, "Process 3 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }
  if ((waitpid(pid_4, &status, 0)) == -1) {
    fprintf(stderr, "Process 4 encountered an error. ERROR%d", errno);
    return EXIT_FAILURE;
  }

  return 0;
}
