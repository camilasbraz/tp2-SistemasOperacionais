CC = gcc
CFLAGS = -lm
TARGET = tp2virtual

all: $(TARGET)

$(TARGET): tp2virtual.c
	$(CC) tp2virtual.c -o $(TARGET) $(CFLAGS)

run: $(TARGET)
	./$(TARGET) 2a compilador.log 32 128 debug

clean:
	rm -f $(TARGET)


# all:
# 	gcc tp2virtual.c -o tp2virtual -lm
# run:
# 	./tp2virtual fifo compilador.log 32 128
# clean:
# 	rm tp2virtual