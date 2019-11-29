//
// Created by 张淇 on 2019/11/8.
//

#ifndef NETWORK_LAB1_THREADPOOL_HPP
#define NETWORK_LAB1_THREADPOOL_HPP

#include <semaphore.h>
#include "dealConnect.h"


template<typename T>
class threadPool {
private:
	int maxThread;
	int maxLink;
	pthread_t *pthreadPool;
	std::queue<T *> activeQueue;
	pthread_mutex_t queueLocker;
	sem_t *queueState;
	bool stop;
public:
	threadPool () {
		maxThread = 20;
		maxLink = 1000;
		stop = false;
		pthreadPool = new pthread_t[maxThread];
		queueState = sem_open ("queueState", O_CREAT, 0644, 1);
		pthread_mutex_init (&queueLocker, nullptr);
		for (int i = 0; i < maxThread; i++) {
			if (pthread_create (pthreadPool + i, nullptr, init, this) != 0) {
				delete[] pthreadPool;
				throw std::exception ();
			}
			if (pthread_detach (pthreadPool[i])) {
				delete[] pthreadPool;
				throw std::exception ();
			}
		}
	}

	~threadPool () {
		/*sem_unlink("queueState");
		sem_close (queueState);
		pthread_mutex_destroy (&queueLocker);*/
		delete[] pthreadPool;
		stop = true;
	}

private:
	static void *init (void *arg);

	void work ();

public:
	bool insertThread (T *request);
};

template<typename T>
void *threadPool<T>::init (void *arg) {
	threadPool *pool = (threadPool *) arg;
	pool->work ();
	return pool;
}

template<typename T>
bool threadPool<T>::insertThread (T *request) {
	pthread_mutex_lock (&queueLocker);
	if (activeQueue.size () > maxLink) {
		pthread_mutex_unlock (&queueLocker);
		return false;
	}
	activeQueue.push (request);
	pthread_mutex_unlock (&queueLocker);
	sem_post (queueState);
	return true;
}

template<typename T>
void threadPool<T>::work () {
	while (!stop) {
		sem_wait (queueState);
		pthread_mutex_lock (&queueLocker);
		if (activeQueue.empty ()) {
			pthread_mutex_unlock (&queueLocker);
			continue;
		}
		T *request = activeQueue.front ();
		activeQueue.pop ();
		pthread_mutex_unlock (&queueLocker);
		if (request == nullptr)
			continue;
		request->handleRequest ();
	}
}



#endif //NETWORK_LAB1_THREADPOOL_HPP
