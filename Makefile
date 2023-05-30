all:
	gcc tp2virtual.c -o tp2virtual -lm
run:
	./tp2virtual fifo compilador.log 4 128
clean:
	rm tp2virtual