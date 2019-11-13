#include "webConnect.hpp"


int main (int argc,char const *argv[]) {
	if(argc<0){
		perror ("error:cannot match configure");
		return -1;
	}
	webConnect conn (AF_INET, INADDR_ANY, defaultPort);
	conn.preServer (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int cnt = 10;
	while (cnt--) {
		conn.service ();
	}
	return 0;
}