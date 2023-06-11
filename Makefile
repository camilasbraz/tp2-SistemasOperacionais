# CC = gcc
# CFLAGS = -lm
# TARGET = tp2virtual

# all: $(TARGET)

# $(TARGET): tp2virtual.c
# 	$(CC) tp2virtual.c -o $(TARGET) $(CFLAGS)

# run: $(TARGET)
# 	./$(TARGET) fifo teste2.log 32 128

# clean:
# 	rm -f $(TARGET)


all:
	gcc tp2virtual.c -o tp2virtual -lm
run:
	./tp2virtual lru compilador.log 32 128
clean:
	rm tp2virtual