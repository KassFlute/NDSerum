#include <nds.h>
#include <dswifi9.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int initWiFi();
int openSocket();
int receiveData(char *data_buff, int bytes);
int sendData(char *data_buff, int bytes);
void closeSocket();
void disconnectFromWiFi();
