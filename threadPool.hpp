//
// Created by 张淇 on 2019/11/8.
//

#ifndef NETWORK_LAB1_THREADPOOL_HPP
#define NETWORK_LAB1_THREADPOOL_HPP

#include "dealConnect.h"

template<typename T>
class threadPool {
private:
	int maxThread;
	int size;
	pthread_t *pthreadPool;
	
};

#endif //NETWORK_LAB1_THREADPOOL_HPP
