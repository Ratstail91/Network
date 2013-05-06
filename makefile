CXXFLAGS+=-std=c++11
SRC=network.cpp network_tcp.cpp network_udp.cpp
OBJ=$(SRC:.cpp=.o)
OUT=network.a
LIB=-lwsock32 -lWS2_32

all: $(OBJ)
	$(CXX) $(CXXFLAGS) -o server server.cpp $(OBJ) $(LIB)
	$(CXX) $(CXXFLAGS) -o client client.cpp $(OBJ) $(LIB)

clean:
	$(RM) *.o *.a *.exe

rebuild: clean all
