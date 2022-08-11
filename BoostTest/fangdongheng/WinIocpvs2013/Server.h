/*
 * =====================================================================================
 *
 *       Filename:  Server.h
 *
 *    Description:
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Dongheng (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef YT_WIN_IOCP_SERVER_H
#define YT_WIN_IOCP_SERVER_H
#ifndef UNICODE
#define UNICODE
#endif
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <cstdio>
#include <iostream>

#include <functional>
#include "ServerSocket.h"

class Server {
	public:
		Server(u_short port);
		~Server();
		bool startAccept();
		void waitingForAccept();
		void waitingForIo();
		bool isRunning() const { return m_running;}
		void stop() { m_running = false;}
		typedef std::function<void(ServerSocket::pointer)> HandleNewConnect;
		HandleNewConnect newConn;
    ServerSocket::HandleRecvFunction socketRecv;
    ServerSocket::HandleClose socketClose;
    ServerSocket::HandleError socketError;

  private:
		u_short m_port;
		SOCKET m_listenSocket;
		HANDLE m_completePort;
		LPFN_ACCEPTEX lpfnAcceptEx;
		SOCKET m_currentAccetSocket;
		WSAOVERLAPPED m_acceptUnit;
		HANDLE m_ioCompletePort;
		bool m_running;
		std::vector<char> m_acceptBuffer;
		bool tryNewConn();
};
#endif

