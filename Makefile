make: syncthread.c
	gcc -std=c99 -pthread -o syncthread syncthread.c

.PHONY: clean
clean:
	rm syncthread
