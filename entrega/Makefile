CC = gcc
CFLAGS = -lm
TARGET = tp2virtual

all: $(TARGET)

$(TARGET): tp2virtual.c
	$(CC) tp2virtual.c -o $(TARGET) $(CFLAGS)

run: $(TARGET)
	./$(TARGET) 2a compilador.log 4 128
clean: 
	rm -f $(TARGET)
