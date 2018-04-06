#include <iostream>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <thread>
#include <vector>
#define PORT 8080

using namespace std;

void err(const char* message) {
  perror(message);
  exit(EXIT_FAILURE);
}

int main() {
  struct sockaddr_in address, from;
  int addrlen = sizeof(address), server_fd, fromLength = sizeof(from);
  if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
    err("Socket unable to comply");
  }
  
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
  
  if (bind(server_fd, (struct sockaddr*)&address, addrlen) < 0) {
    err("Binding failed.");
  }
  
  cout << "Server online" << endl;
  
  while (true) {
    int result[3];
    if ((recvfrom(server_fd, &result, sizeof(result), 0, (sockaddr*)&from, (socklen_t*)&fromLength)) < 0) {
      err("Unacceptable");
    }
    else {
      int n0 = ntohl(result[0]), n1 = ntohl(result[1]), n2 = ntohl(result[2]);
      if (n2 == 1) {n1 = -n1;}
      else if (n2 == -1) {
        n0 = 0;
        n1 = 0;
      }
      int res = htonl(n0 + n1);
      sendto(server_fd, &res, sizeof(res), 0, (sockaddr*)&from, (socklen_t)fromLength);
    }
  }
  cout << "Terminating" << endl;
  close(server_fd);
}
