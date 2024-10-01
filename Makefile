serve: ./src/*
	gcc src/main.c src/response.c src/server.c src/logger.c -o server -g



run: serve
    export $(cat .env | xargs); ./server