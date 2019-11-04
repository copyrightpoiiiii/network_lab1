#include "web_connect.h"


int main (int argc,char const *argv[]) {
	if(argc<0){
		perror ("error:cannot match configure");
		return -1;
	}
	web_connect conn(AF_INET,INADDR_ANY,DEFAULT_PORT);
	conn.creat_socket (AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(conn.sock () == -1) {
		perror ("error:cannot creat socket");
		return -2;
	}
	if(conn.creat_bind () == -1){
		perror("error:cannot bind with socket");
		return -3;
	}
	if(conn.start_listen () == -1){
		perror("error:cannot start monitor the socket");
		return -4;
	}
	while(1){


	}
	return 0;
}