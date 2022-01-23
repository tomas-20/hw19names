#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void capitalize(char *string) {
  while (*string) {
    if ('a' <= *string && *string <= 'z') {
      *string -= 32;
    }
    string ++;
  }
}

int main() {
  int interface_to_worker = open("interface_to_worker", O_RDONLY);
  int worker_to_interface = open("worker_to_interface", O_WRONLY);
  char line[1000];
  while (1) {
    read(interface_to_worker, line, sizeof line);
    capitalize(line);
    write(worker_to_interface, line, sizeof line);
  }
  return 0;
}
