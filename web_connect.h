//
// Created by 张淇 on 2019/11/1.
//

#ifndef NETWORK_LAB1_WEB_CONNECT_H
#define NETWORK_LAB1_WEB_CONNECT_H

#include <iostream>
#include <netinet/in.h>
#include "dealConnect.h"
#include "web_mes.hpp"

class web_connect {
private:
	int socket_fd{}, connect_fd{};
	struct sockaddr_in serve_address{};
	/*
	 * sockaddr_in:
	 * sa_family_t      sin_family
	 * uint16_t         sin_port 16bits port of TCP/UDP
	 * struct in_addr   sin_addr 32bits IPv4 address
	 * char             sin_zero[8]
	 */
public:
	web_connect ();

	web_connect (int af, unsigned addr, unsigned short port);

	int sock () { return socket_fd; }

	int creat_socket (int af, int type, int protocol);

	/*
	 * socket(af,type,protocol)
	 * af:address family:AF_NET(ipv4),AF_INET6(ipv6)
	 * type:sock_stream,sock_dgram
	 * protocol:TCP/UDP
	 *
	 * creat a socket process
	 */

	int creat_bind ();

	/*
	 * bind(sockfd,addr,addrlen)
	 * sockfd:the id of socket
	 * addr:the address of host
	 * addrlen:the length of address
	 *
	 * connect socket with host's address
	 */
	int start_listen ();
	/*
	 * listen(sockfd,backlog)
	 * sockfd:the id of monitored socket
	 * backlog:the max number of processes in queue
	 *
	 * monitor the given socket
	 */

	int service();
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

web_connect::web_connect () {
	memset (&serve_address, 0, sizeof (serve_address));
	serve_address.sin_family = AF_INET;
	serve_address.sin_addr.s_addr = htonl (INADDR_ANY);
	serve_address.sin_port = htons (DEFAULT_PORT);
}

web_connect::web_connect (int af, unsigned addr, unsigned short port) {
	memset (&serve_address, 0, sizeof (serve_address));
	serve_address.sin_family = af;
	serve_address.sin_addr.s_addr = htonl (addr);
	serve_address.sin_port = htons (port);
}

int web_connect::creat_socket (int af, int type, int protocol) {
	socket_fd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

	return socket_fd;
}

int web_connect::creat_bind () {
	return bind (socket_fd, (struct sockaddr *) &serve_address, sizeof (serve_address));
}

int web_connect::start_listen () {
	return listen (socket_fd, MAXLINK);
}

int web_connect::service () {
	while(true) {
		struct sockaddr_in client{};
		socklen_t client_addrlen = sizeof (client);
		connect_fd = accept (socket_fd, (struct sockaddr *) &client, &client_addrlen);
		if (connect_fd < 0) {
			perror ("error:canot accpet connect query");
			return -5;
		} else {
			mes_rec rec_data;
			rec_data.read_request (connect_fd);

		}
	}
}


#endif //NETWORK_LAB1_WEB_CONNECT_H
