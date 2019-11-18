//
// Created by 张淇 on 2019/11/1.
//

#ifndef NETWORK_LAB1_WEBCONNECT_HPP
#define NETWORK_LAB1_WEBCONNECT_HPP


#include "dealConnect.h"
#include "webMes.hpp"

class webConnect {
private:
	int socketFd{}, connectFd{};
	struct sockaddr_in serveAddress{};

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

	int preServer (int af, int type, int protocol);

	int service ();
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
};

webConnect::webConnect () {
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
	socketFd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	return socketFd;
}

int webConnect::creatBind () {
	return bind (socketFd, (struct sockaddr *) &serveAddress, sizeof (serveAddress));
}

int webConnect::startListen () {
	return listen (socketFd, maxLink);
}

int webConnect::service () {
	while (true) {
		struct sockaddr_in client{};
		socklen_t clientAddrLen = sizeof (client);
		connectFd = accept (socketFd, (struct sockaddr *) &client, &clientAddrLen);
		if (connectFd < 0) {
			perror ("error:cannot accept connect query");
			return -5;
		} else {
			webMes recData (connectFd);
			recData.readRequest ();
			bool rec = recData.handleRequest ();
		}
	}
}

int webConnect::preServer (int af, int type, int protocol) {
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
	return 0;
}


#endif //NETWORK_LAB1_WEBCONNECT_HPP
