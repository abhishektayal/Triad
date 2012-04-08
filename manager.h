#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
using namespace std;



//outfile.open ("stage1.manager.out");

#define BACKLOG 100 // how many pending connections queue will hold
#define BUF_SIZE 100
#define MAXDATASIZE 100


extern int PORT;
extern void fork_clients(int NODES, uint32_t tkcc);
extern char* str_to_char(string);
extern string STAGE;

