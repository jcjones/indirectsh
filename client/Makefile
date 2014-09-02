PKG_DEPS=libpubnub-cpp 
SYS_CXXFLAGS=`pkg-config --cflags ${PKG_DEPS}`
CXXFLAGS=-std=c++11 -Wall -ggdb3 -O3 ${SYS_CXXFLAGS}

LIBS=`pkg-config --libs ${PKG_DEPS}` -levent

all: ../ish

../ish: main.o
	g++ -o $@ $^ $(LIBS)

clean:
	rm -f *.o ../ish
