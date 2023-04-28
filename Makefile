#CC  = /home/junlin/Hi3559V200/compiler/arm-himix100-linux/arm-himix100-linux/bin/arm-himix100-linux-gcc
CC = gcc
CXX = g++

CXXFLAGS  += -g -Wall -Werror -pthread
INCLUDES += -I 
LFLAGS += -L 
LIBS = -lpthread 

all : udp 

#SRC_PATH := src/
#CXX_SRC = ${wildcard $(SRC_PATH)/*.c}

CC_SRC = ${wildcard udp.c}

CXX_SRC =${wildcard client.c}



TARGET_SEND=client
$(TARGET_SEND): $(CXX_SRC)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)


TARGET=udp
$(TARGET): $(CC_SRC)
	$(CC) -o $@ $^ $(CXXFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)  



clean:
	rm -f *.so *.o $(TARGET)  $(TARGET_SEND)

