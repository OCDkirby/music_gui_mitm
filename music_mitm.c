// Take the Music_GUI commands and shove em at pcsx2
// Some code shamelessly stolen from PINE reference implementation
// Other bits taken from pcsx2 directly

#include "linux_side.h"
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>

// void sigint_handler (int signum) {
  // exit(0);
// }
// void error(char *msg)
// {
//   perror(msg);
//   exit(1);
// }
BOOL WINAPI consoleHandler(DWORD signal) {
  if (signal == CTRL_C_EVENT)
    exit(0);

  return TRUE;
}
 
int main()
{
  // Connect to PCSX2
  printf("Connecting to pcsx2...\n");
  int pcsx2 = connect_to_pcsx2(); // get a linux socket fd
  if(pcsx2 < 0) {
    printf("pcsx2 was not open, or PINE was not enabled. Check that PINE in Settings -> Advanced Settings is set to 28011 and try again.\n");
    exit(1);
  }
  printf("Connected!\n");

  // Wait for Music_GUI to start
  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;
  SOCKET m_sock = socket(AF_INET, SOCK_STREAM, 0);
  SOCKET m_msgsock;
  struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // localhost only
	server.sin_port = htons(28011);
  if (bind(m_sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("MITM: Error while binding to socket! Shutting down...\n");
		destroy(pcsx2);
		exit(1);
	}
	listen(m_sock, 5);
	printf("Waiting on music_gui...\n");
	m_msgsock = accept(m_sock, 0, 0);
	printf("Music_GUI connected\n");
  SetConsoleCtrlHandler(consoleHandler, TRUE);

  // man in the middle forever
  ulong count = 0;
  char buf[2];
  buf[1] = '\0';
  while(1) {
    recv(m_msgsock, buf, 1, 0);
    printf("%ul\n",count);
    send_to_pcsx2(pcsx2,buf, 1);
  }
  closesocket(m_sock);
  closesocket(m_msgsock);
  destroy(pcsx2);
  return 0;
  }

