all: music_mitm.exe linux_side.dll.so

linux_side.dll.so:
	winegcc -shared -o linux_side linux_side.c linux_side.spec

music_mitm.exe: linux_side.dll.so
	winegcc -o music_mitm music_mitm.c -L . -l:linux_side.dll.so -lws2_32

test: music_mitm.exe
	LD_LIBRARY_PATH="$$PWD:$$LD_LIBRARY_PATH" wine music_mitm.exe

clean:
	rm *.so && rm *.exe

