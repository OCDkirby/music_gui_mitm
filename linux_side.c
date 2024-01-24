#include <windef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "linux_side.h"
#include <netinet/in.h>

struct sockaddr_un {
    __SOCKADDR_COMMON (sun_);
    char sun_path[108];		/* Path name.  */
  };

__stdcall int WINAPI connect_to_pcsx2() {
  // Connect to PCSX2
  struct sockaddr_un server;
  int pcsx2 = socket(AF_UNIX, SOCK_STREAM, 0);
  server.sun_family = AF_UNIX;
  strcpy(server.sun_path, "/run/user/1000/pcsx2.sock");
  if (connect(pcsx2, (struct sockaddr *)&server,
    sizeof(struct sockaddr_un)) < 0) {
    close(pcsx2);
    return -1;
  }

  return pcsx2;
}

__stdcall int WINAPI send_to_pcsx2(int fd, char* buf, int bytes) {
  return write(fd,buf,bytes);
}

__stdcall int WINAPI destroy(int fd) {
  close(fd);
  return 0;
}
