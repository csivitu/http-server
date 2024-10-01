serve: ./src/*
	gcc src/main.c src/response.c src/server.c src/logger.c -o server -g -Wall -fsanitize=address



run: serve
    export $(cat .env | xargs); ./server