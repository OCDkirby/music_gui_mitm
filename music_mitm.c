
// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <signal.h>
#include <stdlib.h>
void sigint_handler (int signum) {
  exit(0);
}
struct sockaddr_un {
    __SOCKADDR_COMMON (sun_);
    char sun_path[108];		/* Path name.  */
  };
void error(char *msg)
{
  perror(msg);
  exit(1);
}
 
int main()
{
  // Connect to PCSX2
  struct sockaddr_un server;
  int pcsx2 = socket(AF_UNIX, SOCK_STREAM, 0);
  server.sun_family = AF_UNIX;
  strcpy(server.sun_path, "/run/user/1000/pcsx2.sock");
  printf("Connecting to pcsx2...\n");
  if (connect(pcsx2, (struct sockaddr *)&server,
    sizeof(struct sockaddr_un)) < 0) {
    printf("pcsx2 was not open, or PINE was not enabled. Check that PINE in Settings -> Advanced Settings is set to 28011 and try again.\n");
    close(pcsx2);
    return 1;
  }
  printf("Connected!\n");

  // Wait for Music_GUI to start
  int bindsock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serv_addr, cli_addr;

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(28011);
  if (bind(bindsock, (struct sockaddr *) &serv_addr,
    sizeof(serv_addr)) < 0) 
    error("ERROR on binding");
  listen(bindsock,5);
  int clilen = sizeof(cli_addr);
  printf("Waiting for Music_GUI, blocking\n");
  int music = accept(bindsock, (struct sockaddr *) &cli_addr, &clilen);
  printf("Connected to Music_GUI!\n");

  signal(SIGINT,sigint_handler); // Close socks with exit(0)

  // man in the middle forever
  char buf[2];
  buf[1] = '\0';
  while(1) {
    read(music, buf, 1);
    printf("a%s", buf);
    write(pcsx2,buf, 1);
  }

  close(pcsx2);
  close(bindsock);
  close(music);
  return 0;
  }

