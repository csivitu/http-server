serve: ./src/*
	gcc src/main.c src/response.c src/server.c -o server -g
