// Take the Music_GUI commands and shove em at pcsx2
// Some code shamelessly stolen from PINE reference implementation
// Other bits taken from pcsx2 directly

#include "linux_side.h"
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

// void sigint_handler (int signum) {
  // exit(0);
// }
// void error(char *msg)
// {
//   perror(msg);
//   exit(1);
// }
 
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
  // TODO change this to windows code


  // int bindsock = socket(AF_INET, SOCK_STREAM, 0);
  // struct sockaddr_in serv_addr, cli_addr;
  //
  // serv_addr.sin_family = AF_INET;
  // serv_addr.sin_addr.s_addr = INADDR_ANY;
  // serv_addr.sin_port = htons(28011);
  // if (bind(bindsock, (struct sockaddr *) &serv_addr,
  //   sizeof(serv_addr)) < 0) 
  //   error("ERROR on binding");
  // listen(bindsock,5);
  // int clilen = sizeof(cli_addr);
  // printf("Waiting for Music_GUI, blocking\n");
  // int music = accept(bindsock, (struct sockaddr *) &cli_addr, &clilen);
  // printf("Connected to Music_GUI!\n");
  //
  // signal(SIGINT,sigint_handler); // Close socks with exit(0)
  //
  // // man in the middle forever
  // char buf[2];
  // buf[1] = '\0';
  // while(1) {
  //   read(music, buf, 1);
  //   printf("a%s", buf);
  //   write(pcsx2,buf, 1);
  // }
  //
  // close(bindsock);
  // close(music);
  destroy(pcsx2);
  return 0;
  }

