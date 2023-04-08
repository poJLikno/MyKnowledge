#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "NetSockets/NetSockets.h"
#include "Window/Window.h"

// Window instance
Window *window;

// UDP & TCP sockets
UDPClient *udpClient;
TCPClient *tcpClient;

// Keyboard listener
KeyboardListener kbl;

// Window width & height
uint32_t winWidth = 600, winHeight = 600;
// Remote screen resolution
std::string remoteResolutionX, remoteResolutionY;
// Image & input threads acceptions
bool imgThr, inpThr;
// Coefficients for remote mouse position
float cofx, cofy;

#endif