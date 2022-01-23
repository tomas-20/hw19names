#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


void get_input(char *string, int length) {
  fgets(string, length, stdin);
  while (*string) {
    if (*string == '\n') {
      *string = '\0';
    }
    else {
      string ++;
    }
  }
}

int main() {
  mkfifo("interface_to_worker", 0644);
  mkfifo("worker_to_interface", 0644);
  int interface_to_worker = open("interface_to_worker", O_WRONLY);
  int worker_to_interface = open("worker_to_interface", O_RDONLY);
  char line[1000];
  while (1) {
    get_input(line, sizeof line);
    write(interface_to_worker, line, sizeof line);
    read(worker_to_interface, line, sizeof line);
    printf("[%s]\n", line);
  }
  return 0;
}
