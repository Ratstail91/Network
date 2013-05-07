CXXFLAGS+=-std=c++11
SRC=network.cpp network_tcp.cpp network_udp.cpp
OBJ=$(SRC:.cpp=.o)
LIB=-lwsock32 -lWS2_32

#targets
all: tcp udp

clean:
	$(RM) *.o *.a *.exe

rebuild: clean all

#templated targets
BUILD_TEMPLATE=$(CXX) $(CXXFLAGS) -o $@ $@.cpp $(OBJ) $(LIB)

tcp: tcp_server tcp_client
udp: udp_server udp_client

tcp_server: $(OBJ)
	$(BUILD_TEMPLATE)

tcp_client: $(OBJ)
	$(BUILD_TEMPLATE)

udp_server: $(OBJ)
	$(BUILD_TEMPLATE)

udp_client: $(OBJ)
	$(BUILD_TEMPLATE)
