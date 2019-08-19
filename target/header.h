#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>	
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
DIR *path;
struct dirent *folder;
char *commands[6];
char output[300];
int externfd;
#define ADDRESS "127.0.0.1"
#define PORT "4445"
