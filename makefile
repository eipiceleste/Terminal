CC = gcc


CFLAGS = -Iinclude -Wall


SOURCES = src/*.c


TARGET = jogo.exe


clear:
	del $(TARGET)

run all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) && .\$(TARGET)