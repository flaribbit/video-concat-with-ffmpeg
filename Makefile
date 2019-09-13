CC=g++
CFLAGS=-lshlwapi -lcomctl32 -s -DNDEBUG -O2 -mwindows
FILES=resource.o main.cpp

main.exe: ${FILES}
	${CC} ${FILES} ${CFLAGS} -o main.exe

resource.o: resource.rc
	windres resource.rc -o resource.o
	
clean:
	-exec rm main.exe
	-exec rm resource.o