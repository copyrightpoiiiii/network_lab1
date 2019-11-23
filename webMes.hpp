//
// Created by 张淇 on 2019/11/3.
//

#ifndef NETWORK_LAB1_WEBMES_HPP
#define NETWORK_LAB1_WEBMES_HPP

#include "dealConnect.h"

/*
	 * NO_REQUEST是代表请求不完整，需要客户继续输入
	 * BAD_REQUEST是HTTP请求语法不正确
	 * GET_REQUEST代表获得并且解析了一个正确的HTTP请求
	 * FORBIDDEN_REQUEST是代表访问资源的权限有问题
	 * FILE_REQUEST代表GET方法资源请求
	 * INTERNAL_ERROR代表服务器自身问题
	 * NOT_FOUND代表请求的资源文件不存在
	 * DYNAMIC_FILE表示是一个动态请求
	 * POST_FILE表示获得一个以POST方式请求的HTTP请求
	*/

const unsigned bufSize = 2000;


class webMes {
private:
	enum httpCode {
		NoRequest,
		GetRequest,
		BadRequest,
		ForbiddenRequest,
		FileRequest,
		InternalError,
		NotFound,
		DynamicFile,
		PostFile
	};
	/*
 * HTTP请求解析的状态转移
 * HEAD表示解析头部信息
 * REQUEST表示解析请求行
*/
	enum checkStatus {
		Head, Request
	};
	unsigned bufLen;
	int readCount;
	int index;
	unsigned len;
	char buffer[bufSize]{};
	checkStatus status;
	httpCode requestState;
	char postBuf[1035];
	char filePath[250];
	char filename[205];
	char *method;//request function
	char *requestFile;
	int fileSize;
	char *host;
	char requestHeadBuf[2000];
	char *serverPath;
	int connectFd;
public:

	char *version;
	char *argv;
	bool alive;
	bool activeRequest;
	int httpLen;

	webMes () {
		memset (buffer, 0, sizeof (buffer));
		memset (postBuf, 0, sizeof (postBuf));
		len = readCount = index = 0;
		bufLen = sizeof (buffer);
		status = Request;
		method = requestFile = version = nullptr;
		serverPath = getcwd (nullptr, 0);
	}

	webMes (int inFd) {
		connectFd = inFd;
		memset (buffer, 0, sizeof (buffer));
		memset (postBuf, 0, sizeof (postBuf));
		len = readCount = index = 0;
		bufLen = sizeof (buffer);
		status = Request;
		method = requestFile = version = nullptr;
		serverPath = getcwd (nullptr, 0);
	}

private:

	httpCode analyseHeadLine (char *buf);

	httpCode analyseRequestLine (char *buf);

	int splitByLine (int &index);

	bool analyseRequestInfo (char *buf);

	httpCode doGet ();

	httpCode doPost ();

	httpCode analyseRequest ();

	bool requestOk ();

	/*
	bool requestBadRequest();

	bool requestForbidden();

	bool requestNotFound();
	 */

	bool sendFile ();

	bool sendPicture ();

	bool sendHtml ();

	bool sendMoive ();

public:

	unsigned length () {
		return len;
	}

	unsigned size () {
		return sizeof (buffer);
	}

	int readRequest ();

	bool handleRequest ();

	bool badRequest ();

	bool illegalRequest ();

	bool unknownRequest ();
};


int webMes::readRequest () {
	memset (buffer, 0, sizeof (buffer));
	int ret = recv (connectFd, buffer + readCount, bufSize - readCount, 0);//阻塞模式下读入
	if (ret < 0 && !(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN))
		return 0;
	readCount += ret;
	strcpy (postBuf, buffer);
	len = strlen (buffer);
	return 1;
}

webMes::httpCode webMes::analyseRequest () {
	int startLine = 0, start = 0;
	index = 0;
	char *charPoint = buffer;
	while ((splitByLine (index)) == 1) {
		charPoint = buffer + startLine;
		startLine = index;
		switch (status) {
			case Request: {
				httpCode ret = analyseRequestLine (charPoint);
				if (ret == BadRequest) {
					perror ("BAD Request");
					return BadRequest;
				}
				break;
			}
			case Head: {
				httpCode ret = analyseHeadLine (charPoint);
				if (ret == GetRequest) {
					if (strcmp (method, "GET") == 0) {
						return doGet ();
					} else if (strcmp (method, "POST") == 0) {
						return doPost ();
					} else return BadRequest;
				}
				break;
			}
			default:
				return InternalError;
		}
	}
	return NoRequest;
}

/*check a complete line*/
int webMes::splitByLine (int &ind) {
	for (; index < len; index++) {
		char ch = buffer[index];
		if (ch == '\r' && index + 1 < len && buffer[index + 1] == '\n') {
			buffer[index++] = '\0';
			buffer[index++] = '\0';
			return 1;
		}
	}
	return 0;
}

bool webMes::analyseRequestInfo (char *buf) {
	char *now = buf;
	method = now;
	while (((*now) != ' ') && ((*now) != '\r'))now++;
	*now = '\0';
	now++;
	requestFile = now;
	while (((*now) != ' ') && ((*now) != '\r'))now++;
	*now = '\0';
	now++;
	version = now;
	while ((*now) != '\r')now++;
	*now = '\0';
	now++;
	*now = '\0';
	now++;
#ifdef DEBUG
	std::cout << "method: " << method << std::endl;
	std::cout << "requestFile: " << requestFile << std::endl;
	std::cout << "version: " << version << std::endl;
#endif
	if (method == nullptr || (strcmp (method, "GET") != 0 && strcmp (method, "POST") != 0))
		return false;
	if (requestFile == nullptr || requestFile[0] != '/')
		return false;
	return !(version == nullptr || strcmp (version, "HTTP/1.1") != 0);
}

webMes::httpCode webMes::analyseRequestLine (char *buf) {
	char *now = buf;
	if (analyseRequestInfo (buf)) {
		status = Head;
		return NoRequest;
	} else return BadRequest;
}

webMes::httpCode webMes::analyseHeadLine (char *buf) {
#ifdef DEBUG
	std::cout << "HeadLine: " << buf << std::endl;
#endif
	if ((*buf) == '\0')
		return GetRequest;
	else if (strncasecmp (buf, "Connection:", 11) == 0) {
		buf += 11;
		while (*buf == ' ')buf++;
		if (strcasecmp (buf, "keep-alive") == 0)
			alive = true;
	} else if (strncasecmp (buf, "Content-Length:", 15) == 0) {
		buf += 15;
		while (*buf == ' ')buf++;
		httpLen = atol (buf);
	} else if (strncasecmp (buf, "Host:", 5) == 0) {
		buf += 5;
		while (*buf == ' ')buf++;
		host = buf;
	}
	return NoRequest;
}

webMes::httpCode webMes::doGet () {
#ifdef DEBUG
	std::cout << filename << std::endl;
	std::cout << serverPath << std::endl;
#endif
	char *ch = strchr (requestFile, (int) '?');
	if (ch) {
		argv = ch + 1;
		*ch = '\0';
		strcpy (filename, requestFile);
		return DynamicFile;
	} else {
		strcpy (filename, serverPath);
		strcat (filename, requestFile);
		struct stat fileState;
		int result = stat (filename, &fileState);
		if (result != 0) {
#ifdef DEBUG
			std::cout << errno << std::endl;
#endif
			switch (errno) {
				case ENOENT:
					return NotFound;
				case EINVAL:
					return BadRequest;
				case EACCES:
					return ForbiddenRequest;
				default:
					return BadRequest;
			}
		}
		fileSize = fileState.st_size;
		return FileRequest;
	}
}

webMes::httpCode webMes::doPost () {
	char *serverPath;
	serverPath = getcwd (nullptr, 0);
	strcpy (filename, serverPath);
	strcat (filename, filePath);
	unsigned postStart = len - httpLen;
	argv = postBuf + postStart;
	if (argv == nullptr)return BadRequest;
	argv[strlen (argv) + 1] = '\0';
	return PostFile;
}

bool webMes::handleRequest () {
	requestState = analyseRequest ();
	switch (requestState) {
		case FileRequest: {
			requestOk ();
			bool rec = sendFile ();
			return rec;
		}
		case NoRequest: {
			badRequest ();
			bool rec = sendFile ();
			return rec;
		}
		case ForbiddenRequest: {
			illegalRequest ();
			bool rec = sendFile ();
			return rec;
		}
		case NotFound: {
			unknownRequest ();
			bool rec = sendFile ();
			return rec;
		}
		case PostFile: {

			return true;
		}
		default:
			return false;
	}
}

bool webMes::sendFile () {
	if (strstr (filename, ".jpg") != nullptr) {
#ifdef DEBUG
		std::cout << "picture: " << filename << std::endl;
#endif
		return sendPicture ();
	} else if (strstr (filename, ".mp4") != nullptr) {
#ifdef DEBUG
		std::cout << "movie: " << filename << std::endl;
#endif
		return sendMoive ();
	} else return sendHtml ();
}

bool webMes::sendPicture () {
	sprintf (requestHeadBuf,
	         "HTTP/1.1 200 ok\r\nContent-Type: image/jpeg\r\nConnection: Keep-Alive\r\ncontent-length:%d\r\n\r\n",
	         fileSize);
	std::ifstream fileRequest (filename, std::ifstream::binary);
	int ret = write (connectFd, requestHeadBuf, strlen (requestHeadBuf));
	if (ret < 0) {
		fileRequest.close ();
		return false;
	}
	int lastPos = fileRequest.tellg ();
	while (!fileRequest.eof ()) {
		fileRequest.read (requestHeadBuf, 1024);
		int nowPos = fileRequest.tellg ();
		write (connectFd, requestHeadBuf, nowPos - lastPos >= 0 ? nowPos - lastPos : fileSize - lastPos);
		lastPos = fileRequest.tellg ();
	}
#ifdef DEBUG
	std::cout << "send successful!" << std::endl;
#endif
	if (!fileRequest)
		return false;
	fileRequest.close ();
	return true;
}

bool webMes::sendHtml () {
	memset (requestHeadBuf, 0, sizeof (requestHeadBuf));
	sprintf (requestHeadBuf, "HTTP/1.1 200 ok\r\nConnection: close\r\ncontent-length:%d\r\n\r\n", fileSize);
	std::ifstream fileRequest (filename, std::ifstream::binary);
	int ret = write (connectFd, requestHeadBuf, strlen (requestHeadBuf));
	if (ret < 0) {
		fileRequest.close ();
		return false;
	}
	while (!fileRequest.eof ()) {
		fileRequest.read (requestHeadBuf, 1024);
		write (connectFd, requestHeadBuf, strlen (requestHeadBuf));
	}
	if (!fileRequest)
		return false;
	fileRequest.close ();
	return true;
}

bool webMes::sendMoive () {
	memset (requestHeadBuf, 0, sizeof (requestHeadBuf));
	sprintf (requestHeadBuf,
	         "HTTP/1.1 200 ok\r\nContent-Type: video/mpeg4\r\nConnection: close\r\ncontent-length:%d\r\n\r\n",
	         fileSize);
	std::ifstream fileRequest (filename, std::ifstream::binary);
	int ret = write (connectFd, requestHeadBuf, strlen (requestHeadBuf));
	if (ret < 0) {
		fileRequest.close ();
		return false;
	}
	int lastPos = fileRequest.tellg ();
	while (!fileRequest.eof ()) {
		fileRequest.read (requestHeadBuf, 1024);
		int nowPos = fileRequest.tellg ();
		write (connectFd, requestHeadBuf, nowPos - lastPos >= 0 ? nowPos - lastPos : fileSize - lastPos);
		std::cout << nowPos << std::endl;
		lastPos = fileRequest.tellg ();
	}
#ifdef DEBUG
	std::cout << "send successful!" << std::endl;
#endif
	if (!fileRequest)
		return false;
	fileRequest.close ();
	return true;
}

bool webMes::requestOk () {
	activeRequest = false;
	memset (requestHeadBuf, 0, sizeof (requestHeadBuf));
	return sprintf (requestHeadBuf, R"(HTTP/1.1 200 ok\r\nConnection: close\r\ncontent-length:%d\r\n\r\n)", fileSize);
}

bool webMes::badRequest () {
	memset (filename, 0, sizeof (filename));
	strcpy (filename, serverPath);
	strcat (filename, "/200.html");
	struct stat returnFile;
	stat (filename, &returnFile);
	fileSize = returnFile.st_size;
	memset (requestHeadBuf, 0, sizeof (requestHeadBuf));
	sprintf (requestHeadBuf, "HTTP/1.1 400 BAD_REQUESTION\r\nConnection: close\r\ncontent-length:%d\r\n\r\n", fileSize);
	return true;
}

bool webMes::illegalRequest () {
	memset (filename, 0, sizeof (filename));
	strcpy (filename, serverPath);
	strcat (filename, "/403.html");
	struct stat returnFile;
	stat (filename, &returnFile);
	fileSize = returnFile.st_size;
	memset (requestHeadBuf, 0, sizeof (requestHeadBuf));
	sprintf (requestHeadBuf, "HTTP/1.1 403 FORBIDDEN\r\nConnection: close\r\ncontent-length:%d\r\n\r\n", fileSize);
	return true;
}

bool webMes::unknownRequest () {
	memset (filename, 0, sizeof (filename));
	strcpy (filename, serverPath);
	strcat (filename, "/404.html");
#ifdef DEBUG
	std::cout << filename << std::endl;
#endif
	struct stat returnFile;
	stat (filename, &returnFile);
	fileSize = returnFile.st_size;
	memset (requestHeadBuf, 0, sizeof (requestHeadBuf));
	sprintf (requestHeadBuf, "HTTP/1.1 404 NOT_FOUND\r\nConnection: close\r\ncontent-length:%d\r\n\r\n", fileSize);
	return true;
}


#endif //NETWORK_LAB1_WEBMES_HPP
