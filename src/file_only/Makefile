compile:
	gcc -Wall -g3 -fsanitize=address -ffreestanding -pthread client.c -o client
	gcc -Wall -g3 -fsanitize=address -Wno-unused-variable -pthread server.c -o server
