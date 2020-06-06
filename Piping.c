#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
int main(void){
  int fd[2];
  int wd[2];
  int input_int = 0, read_int = 0;
  char input_char,read_char;
  int sum = 0;
  pid_t childpid;
  pipe(fd);
  pipe(wd);
  if((childpid = fork ()) == -1){
    perror("Unable to fork ");
    exit(0);
    }
  if (childpid == 0){
    close(fd[0]);
    printf("Enter integer: ");
    scanf("%d", &input_int);
    input_char = input_int;
    write(fd[1], &input_char, sizeof(input_char));//sends input to parent.
    while(input_int != -1) {
      printf("Enter integer: ");
      scanf("%d", &input_int);
      input_char = (char) input_int;//This converts in integer read into a 1-byte char
      write(fd[1], &input_char, sizeof(input_char));//sends input to parent
    }
    close(wd[1]);
    read(wd[0], &read_int, sizeof(read_int));
    printf("\nSum recieved from parent: %d\n", read_int);
    exit(0);
  }
  else{
    close(fd[1]);
    read(fd[0], &read_char, sizeof(read_char));
    read_int = (int)read_char;
    while (read_int!=-1){
      sum += read_int;
      read(fd[0], &read_char, sizeof(read_char));
      read_int = (int) read_char;
    }
    close(wd[0]);
    write(wd[1], &sum, sizeof(sum));
  }
return 0;}
