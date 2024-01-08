#ifndef WIFI_MINILIB_H
#define WIFI_MINILIB_H

#include <nds.h>
#include <dswifi9.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SSID "MES-NDS"


//WiFi initialization
int initWiFi();
//Socket initialization
int openSocket();
//Receive data trough the socket
int receiveData(char* data_buff, int bytes);
//Send data through the socket
int sendData(char* data_buff, int bytes);
//Close the Socket
void closeSocket();
//Disconnect the WiFi
void disconnectFromWiFi();


#endif // WIFI_MINILIB_H
