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

int get(int socket) {
  int var = 0;
  if (read(socket, &var, sizeof(var)) > 0) {return ntohl(var);}
  return -1;
}

void serve(int socket) {
  int e = get(socket);
  cout << "Start Serve" << endl;
  while (e == 110) {
    cout << "e: " << e << endl;
    int n0 = get(socket), n1 = get(socket), n2 = get(socket);
    if (n2 == 1) {n1 = -n1;}
    else if (n2 == -1) {
      n0 = 0;
      n1 = 0;
    }
    
    int res = htonl(n0 + n1);
    write(socket, &res, sizeof(res));
    e = get(socket);
  }
  int ok = 0;
  write(socket, &ok, sizeof(ok));
  close(socket);
  cout << "End Serve" << endl;
  return;
}

int main() {
  struct sockaddr_in address;
  int addrlen = sizeof(address), opt = 1, server_fd;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    err("Socket unable to comply");
  }
  
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    err("Socket opt failed.");
  }
  
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
  
  if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
    err("Binding failed.");
  }
  
  if (listen(server_fd, 3) < 0) {err("Can't listen.");}
  
  cout << "Server online" << endl;
  
  int new_Socket;
  while (true) {
    if ((new_Socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
      err("Unacceptable");
    }
    else {
      thread t(serve, new_Socket);
      t.detach();
    }
  }
  cout << "Terminating" << endl;
}
