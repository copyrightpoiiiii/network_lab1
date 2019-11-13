//
// Created by 张淇 on 2019/11/1.
//

#ifndef NETWORK_LAB1_DEALCONNECT_H
#define NETWORK_LAB1_DEALCONNECT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/event.h>
#include <cerrno>
#include <netinet/in.h>
#include <zconf.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <fstream>
#include <iostream>

#define DEBUG

const int buffsize = 1024;
const int maxlink = 10;
const int defaultPort = 8888;


#endif //NETWORK_LAB1_DEALCONNECT_H
