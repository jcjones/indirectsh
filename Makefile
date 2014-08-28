PKG_DEPS=libpubnub-cpp 
SYS_CXXFLAGS=`pkg-config --cflags ${PKG_DEPS}`
CXXFLAGS=-std=c++11 -Wall -ggdb3 -O3 ${SYS_CXXFLAGS} -I/usr/include/curlpp

LIBS=`pkg-config --libs ${PKG_DEPS}` -lcurlpp

all: indirectshd

indirectshd: main.o pubnub_channel.o event_loop.o shell.o pipe.o ip_location_cmd.o shell_cmd.o
	g++ -o $@ $^ $(LIBS)

clean:
	rm -f *.o indrectshd
