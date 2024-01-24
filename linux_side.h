#include <windef.h>

__stdcall int WINAPI connect_to_pcsx2();
__stdcall int WINAPI send_to_pcsx2(int fd, char *buf, int bytes);
__stdcall int WINAPI destroy(int fd);
