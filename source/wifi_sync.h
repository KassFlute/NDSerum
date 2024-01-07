#ifndef WIFI_MINILIB_H
#define WIFI_MINILIB_H

#include <nds.h>
#include <dswifi9.h>
//#include <dswifi7.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int initWiFi();
int openSocket();
int receiveData(char *data_buff, int bytes);
int sendData(char *data_buff, int bytes);
void closeSocket();
void disconnectFromWiFi();
void send_freq(int freq);
void send_amp(float amp);
void send_phase(int phase);

#endif //  WIFI_MINILIB_H
