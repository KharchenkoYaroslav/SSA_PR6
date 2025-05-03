# docker build -t task .
# docker run --rm -it task /bin/bash
# gcc -g task.c -o task -lm
# gcc -g -fsanitize=address task.c -o task_asan
# valgrind ./task
# ./task_asan

FROM debian:bullseye-slim

WORKDIR /app

RUN apt-get update && apt-get install -y \
    gcc \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

COPY task.c .

