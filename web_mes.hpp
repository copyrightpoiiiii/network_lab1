//
// Created by 张淇 on 2019/11/3.
//

#ifndef NETWORK_LAB1_WEB_MES_HPP
#define NETWORK_LAB1_WEB_MES_HPP

#include "dealConnect.h"

/*
	 * NO_REQUESTION是代表请求不完整，需要客户继续输入
	 * BAD_REQUESTION是HTTP请求语法不正确
	 * GET_REQUESTION代表获得并且解析了一个正确的HTTP请求
	 * FORBIDDEN_REQUESTION是代表访问资源的权限有问题
	 * FILE_REQUESTION代表GET方法资源请求
	 * INTERNAL_ERROR代表服务器自身问题
	 * NOT_FOUND代表请求的资源文件不存在
	 * DYNAMIC_FILE表示是一个动态请求
	 * POST_FILE表示获得一个以POST方式请求的HTTP请求
	*/

const unsigned BUF_SIZE = 2000;


class web_mes {
private:
	unsigned buf_len;
protected:
	enum HTTP_CODE {
		NO_REQUESTION,
		GET_REQUESTION,
		BAD_REQUESTION,
		FORBIDDEN_REQUESTION,
		FILE_REQUESTION,
		INTERNAL_ERROR,
		NOT_FOUND,
		DYNAMIC_FILE,
		POST_FILE
	};
	/*
	 * HTTP请求解析的状态转移
	 * HEAD表示解析头部信息
	 * REQUESTION表示解析请求行
	*/
	enum CHECK_STATUS {
		HEAD, REQUESTION
	};
	unsigned len;
	char buffer[BUF_SIZE]{};
	CHECK_STATUS status;
	char file_path[250];
public:

	web_mes () {
		memset (buffer, 0, sizeof (buffer));
		len = 0;
		buf_len = sizeof (buffer);
		status = REQUESTION;
	}

	unsigned length () {
		return len;
	}

	unsigned size () {
		return sizeof (buffer);
	}

};

class mes_rec : web_mes {
private:
	char post_buf[1000];//buffer for post
	int read_count;
	int index;
public:
	char *method;//request function
	char *filename;
	char *version;
	char *argv;
	bool m_linger;
	bool m_flag;
	int m_http_len;
	char* m_host;
	mes_rec () {
		memset (post_buf, 0, sizeof (post_buf));
		method = filename = version = nullptr;
		read_count = 0;
		index = 0;
	}

	int read_request (int connect_fd);

private:

	HTTP_CODE analyse_request ();

	HTTP_CODE analyse_headLine (char *buf);

	HTTP_CODE analyse_requestLine (char *buf);

	int split_by_line (int &index, unsigned &buf_len);

	bool analyse_requesetInfo (char *buf);

	HTTP_CODE do_GET();
	HTTP_CODE do_POST();

};

int mes_rec::read_request (int connect_fd) {
	memset (buffer, 0, sizeof (buffer));
	while (true) {
		int ret = recv (connect_fd, buffer + read_count, BUF_SIZE - read_count, 0);
		if (ret == -1) {
			if (errno == EAGAIN || errno == EWOULDBLOCK)//end correct
				break;
			else return 0;
		} else if (ret == 0)
			return 0;
		read_count += ret;
	}
	strcpy (post_buf, buffer);
	len = strlen (buffer);
	return 1;
}

web_mes::HTTP_CODE mes_rec::analyse_request () {
	int start_line=0, start=0, flag=0;
	index = 0;
	unsigned buf_len = length ();
	char* char_point=buffer;
	while ((flag = split_by_line (index, buf_len)) == 1) {
		char_point=buffer+start_line;
		start_line=index;
		switch (status) {
			case REQUESTION: {
				HTTP_CODE ret = analyse_requestLine (char_point);
				if (ret == BAD_REQUESTION) {
					perror ("BAD REQUESTION");
					return BAD_REQUESTION;
				}
				break;
			}
			case HEAD: {
				HTTP_CODE ret = analyse_headLine (char_point);
				if (ret == GET_REQUESTION) {
					if (strcmp (method, "GET") == 0) {
						return do_GET ();
					} else if (strcmp (method, "POST") == 0) {
						return do_POST ();
					} else return BAD_REQUESTION;
				}
				break;
			}
			default:
				return INTERNAL_ERROR;
		}
	}
	return NO_REQUESTION;
}

/*check a complete line*/
int mes_rec::split_by_line (int &ind, unsigned &buf_len) {
	std::cout << buffer << std::endl;
	for (; ind + 1 < buf_len; ind++) {
		char ch = buffer[ind];
		if (ch == '\r' && buffer[ind + 1] == '\n') {
			buffer[ind] = '\0';
			buffer[ind + 1] = '\0';
			return 1;
		}
	}
	return 0;
}

bool mes_rec::analyse_requesetInfo (char *buf) {
	char *now = buf;
	method = now;
	while (((*now) != ' ') && ((*now) != '\r'))now++;
	*now = '\0';
	now++;
	filename = now;
	while (((*now) != ' ') && ((*now) != '\r'))now++;
	*now = '\0';
	now++;
	version = now;
	while ((*now) != '\r')now++;
	*now = '\0';
	now++;
	*now = '\0';
	now++;
#ifdef debug
	std::cout << "method: " << method << std::endl;
	std::cout << "filename: " << filename << std::endl;
	std::cout << "version: " << version << std::endl;
#endif
	if (method == nullptr || (strcmp (method, "GET") != 0 && strcmp (method, "POST") != 0))
		return false;
	if (filename == nullptr || filename[0]!='/')
		return false;
	return !(version == nullptr || strcmp (version, "HTTP/1.1") != 0);
}

web_mes::HTTP_CODE mes_rec::analyse_requestLine (char *buf) {
	char *now = buf;
	if(analyse_requesetInfo (buf)){
		status = HEAD;
		return NO_REQUESTION;
	}
	else return BAD_REQUESTION;
}

web_mes::HTTP_CODE mes_rec::analyse_headLine (char *buf) {
	if((*buf)=='\0')
		return GET_REQUESTION;
	else if(strncasecmp (buf,"Connection:",11)==0){
		buf+=11;
		while(*buf==' ')buf++;
		if(strcasecmp (buf,"keep-alive")==0)
			m_linger=true;
	}
	else if(strncasecmp (buf,"Content-Length:",15)==0){
		buf+=15;
		while(*buf==' ')buf++;
		m_http_len=atol (buf);
	}
	else if(strncasecmp (buf,"Host:",5)==0){
		buf+=5;
		while(*buf==' ')buf++;
		m_host=buf;
	}
	return NO_REQUESTION;
}

#endif //NETWORK_LAB1_WEB_MES_HPP
