#include <iostream>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080

using namespace std;

static struct sockaddr_in address;

void err(const char* message) {
  perror(message);
  exit(EXIT_FAILURE);
}

int input() {
  int i = 0;
  cin >> i;
  return i;
}

int connect() {
  int sock;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    err("Socket unable to comply.");
  }
  
  if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
    err("Invalid address.");
  }
  
  if (connect(sock, ((struct sockaddr*)&address), sizeof(address)) < 0) {
    err("Connection Failed.");
  }
  return sock;
}

int main() {
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  cout << "Client online" << endl;
  

  char e = 'n';
  int sock = connect();
  while (e == 'n') {
    int e_0 = htonl((int)e);
    write(sock, &e_0, sizeof(e_0));
    cout << "Enter two numbers: ";
    int n[3] = {(int)htonl(input()), (int)htonl(input()), 0};
    char c;
    cout << "\nEnter + or -: ";
    cin >> c;
    
    n[2] = (c == '+') ? 0 : (c == '-') ? 1 : -1;
    if (n[2] == 0 || n[2] == 1) {
      n[2] = htonl(n[2]);
      for (int i = 0; i < 3; i++) {
        write(sock, &n[i], sizeof(n[i]));
      }
      
      int n0 = 0;
      if(read(sock, &n0, sizeof(n0)) < 0) {err("Socket FAIL");}
      
      cout << "Result: " << (int)ntohl(n0) << endl;// Cast to int so negative values show up.
    }
    else {cout << "Invalid input" << endl;}
    cout << "Exit? (y/n): ";
    cin >> e;
  }
  e = htonl(e);
  write(sock, &e, sizeof(e));
  read(sock, &e, sizeof(e));
  close(sock);
}
