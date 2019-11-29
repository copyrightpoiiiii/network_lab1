//
// Created by 张淇 on 2019/11/1.
//

#ifndef NETWORK_LAB1_WEBCONNECT_HPP
#define NETWORK_LAB1_WEBCONNECT_HPP


#include "dealConnect.h"
#include "webMes.hpp"
#include "threadPool.hpp"

class webConnect : public QObject {
Q_OBJECT
private:
	QString outBuf;
	int socketFd{};/*server socket*/
	int connectFd{};
	int kq{};//kqueue
	struct kevent newEvent{};
	struct sockaddr_in serveAddress{};
	struct kevent events[maxConnect + 5]{};
	struct timespec timeout = {10, 0};
	webMes *users = new webMes[maxConnect + 5];
	threadPool<webMes> *pool = new threadPool<webMes>;

	/*
	 * sockaddr_in:
	 * sa_family_t      sin_family
	 * uint16_t         sin_port 16bits port of TCP/UDP
	 * struct in_addr   sin_addr 32bits IPv4 address
	 * char             sin_zero[8]
	 */

	int sock () { return socketFd; }

	int creatSocket (int af, int type, int protocol);

	/*
	 * socket(af,type,protocol)
	 * af:address family:AF_NET(ipv4),AF_INET6(ipv6)
	 * type:sock_stream,sock_dgram
	 * protocol:TCP/UDP
	 *
	 * creat a socket process
	 */

	int creatBind ();

	/*
	 * bind(sockfd,addr,addrlen)
	 * sockfd:the id of socket
	 * addr:the address of host
	 * addrlen:the length of address
	 *
	 * connect socket with host's address
	 */
	int startListen ();

	/*
	 * listen(sockfd,backlog)
	 * sockfd:the id of monitored socket
	 * backlog:the max number of processes in queue
	 *
	 * monitor the given socket
	 */

public:
	webConnect ();

	webConnect (int af, unsigned addr, unsigned short port);

	~webConnect () override {
		closeService ();
	}

	int preServer (int af, int type, int protocol);

	void service ();

	/*
	 * accept(sockfd,addr,addrlen)
	 * sockfd:the socket monitored
	 * addr:client's address
	 *
	 * recv(s,buf,len,flags)
	 * s:receive data form this socket
	 * buf:buffer
	 * len:buffer's length
	 * flags:0
	 */

	void closeService ();

	void changePort (int port);

signals:

	void outSignal (const QString &out);

public slots:

	void slotService ();
};

webConnect::webConnect () {
	//QObject (parent);
	memset (&serveAddress, 0, sizeof (serveAddress));
	serveAddress.sin_family = AF_INET;
	serveAddress.sin_addr.s_addr = htonl (INADDR_ANY);
	serveAddress.sin_port = htons (defaultPort);
}

webConnect::webConnect (int af, unsigned addr, unsigned short port) {
	memset (&serveAddress, 0, sizeof (serveAddress));
	serveAddress.sin_family = af;
	serveAddress.sin_addr.s_addr = htonl (addr);
	serveAddress.sin_port = htons (port);
}

int webConnect::creatSocket (int af, int type, int protocol) {
	socketFd = socket (AF_INET, SOCK_STREAM, 0);
	return socketFd;
}

int webConnect::creatBind () {
	return bind (socketFd, (struct sockaddr *) &serveAddress, sizeof (serveAddress));
}

int webConnect::startListen () {
	return listen (socketFd, maxLink);
}

void webConnect::service () {
	outBuf = "Service Start\n";
	emit outSignal (outBuf);
	while (true) {
		int eventNum = kevent (kq, nullptr, 0, events, 10, &timeout);
		if (eventNum < 0) {
			outBuf = "kevent error\n";
			emit outSignal (outBuf);
			perror ("kevent error\n");
			continue;
		} else {
			for (int j = 0; j < eventNum; j++) {
				struct kevent curEvent = events[j];
				int eventFd = (int) curEvent.ident;
				if (curEvent.ident == STDIN_FILENO) {
					char inputMsg[100];
					memset (inputMsg, 0, sizeof (inputMsg));
					fgets (inputMsg, sizeof (inputMsg), stdin);
					closeService ();
					exit (0);
				} else if (eventFd == socketFd) {
					struct sockaddr_in clientAddress{};
					socklen_t clientAddrLen = sizeof (clientAddress);
					int clientFd = accept (socketFd, (struct sockaddr *) &clientAddress, &clientAddrLen);
					if (clientFd < 0) {
						outBuf = "error:cannot accept connect query\n";
						emit outSignal (outBuf);
						perror ("error:cannot accept connect query");
						return;
					}
					EV_SET (&newEvent, clientFd, EVFILT_READ, EV_ADD, 0, 0, nullptr);
					kevent (kq, &newEvent, 1, nullptr, 0, nullptr);
					users[clientFd].init (clientFd);
					outBuf.sprintf ("client %d has registered address is: %s : %d\n", clientFd,
					                inet_ntoa (clientAddress.sin_addr), ntohs(clientAddress.sin_port));
					emit outSignal (outBuf);
					std::cout << "client" << clientFd << " has registered address is: "
					          << inet_ntoa (clientAddress.sin_addr) << ntohs(clientAddress.sin_port) << std::endl;
				} else {
					if (users[eventFd].readRequest () != 0) {
						pool->insertThread (users + eventFd);
					} else {
						EV_SET (&newEvent, curEvent.ident, EVFILT_READ, EV_DELETE, 0, 0, nullptr);
						kevent (kq, &newEvent, 1, nullptr, 0, nullptr);
						users[eventFd].close ();
						outBuf.sprintf ("client %d has quited\n", eventFd);
						emit outSignal (outBuf);
						std::cout << "client" << eventFd << " has quited" << std::endl;
					}
				}
			}
		}
	}
}

int webConnect::preServer (int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP) {
	creatSocket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock () == -1) {
		perror ("error:cannot creat socket");
		return -2;
	}
	if (creatBind () == -1) {
		perror ("error:cannot bind with socket");
		return -3;
	}
	if (startListen () == -1) {
		perror ("error:cannot start monitor the socket");
		return -4;
	}
	std::cout << "server creat socket and monitor port" << std::endl;
	kq = kqueue ();
	EV_SET (&newEvent, STDIN_FILENO, EVFILT_READ, EV_ADD, 0, 0, nullptr);
	kevent (kq, &newEvent, 1, nullptr, 0, nullptr);
	EV_SET (&newEvent, socketFd, EVFILT_READ, EV_ADD, 0, 0, nullptr);
	kevent (kq, &newEvent, 1, nullptr, 0, nullptr);
	return 0;
}

void webConnect::slotService () {
	closeService ();
}

void webConnect::closeService () {
	if (socketFd != -1)::close (socketFd);
	if (connectFd != -1)::close (connectFd);
	delete[] users;
	delete pool;
}

void webConnect::changePort (int port) {
	memset (&serveAddress, 0, sizeof (serveAddress));
	serveAddress.sin_family = AF_INET;
	serveAddress.sin_addr.s_addr = htonl (INADDR_ANY);
	serveAddress.sin_port = htons (port);
	preServer ();
	users = new webMes[maxConnect + 5];
	pool = new threadPool<webMes>;
	std::cout << port << std::endl;
	service ();
}


#include "webConnect.moc"

#endif //NETWORK_LAB1_WEBCONNECT_HPP
