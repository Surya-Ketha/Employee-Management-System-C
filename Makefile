CC = gcc
employee_app: build/json_handler.o build/validation.o build/employee_ops.o build/main.o
	$(CC) build/json_handler.o build/validation.o build/employee_ops.o build/main.o -o employee_app -ljson-c

employee_app2: build/json_handler.o build/validation.o build/employee_ops2.o build/main2.o
	$(CC) build/json_handler.o build/validation.o build/employee_ops2.o build/main2.o -o employee_app2 -ljson-c -lpthread

build/main2.o: json_handler.h validation.h employee_ops.h main2.c
	mkdir -p build
	$(CC) -c main2.c -o build/main2.o

build/employee_ops2.o: validation.h employee_ops.h employee_ops2.c
	mkdir -p build
	$(CC) -c employee_ops2.c -o build/employee_ops2.o

build/json_handler.o: json_handler.h json_handler.c
	mkdir -p build
	$(CC) -c json_handler.c -o build/json_handler.o

build/validation.o: validation.h validation.c
	mkdir -p build
	$(CC) -c validation.c -o build/validation.o

build/main.o:	json_handler.h validation.h employee_ops.h main.c
	mkdir -p build
	$(CC) -c main.c -o build/main.o

build/employee_ops.o: validation.h employee_ops.h employee_ops.c
	mkdir -p build
	$(CC) -c employee_ops.c -o build/employee_ops.o

clean:
	rm -rf build employee_app employee_app2

arm: clean
	$(MAKE) CC=arm-linux-gnueabihf-gcc
