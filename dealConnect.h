//
// Created by 张淇 on 2019/11/1.
//

#ifndef NETWORK_LAB1_DEALCONNECT_H
#define NETWORK_LAB1_DEALCONNECT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/event.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <zconf.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <thread>

#include "widget.h"
#include <QObject>
#include <QSpinBox>
#include <QSlider>
#include <QFormLayout>



#define DEBUG

const int buffSize = 1024;
const int maxLink = 500;
const int maxConnect = 500;
const int defaultPort = 80;


#endif //NETWORK_LAB1_DEALCONNECT_H
