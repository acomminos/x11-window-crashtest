all: crashtest

crashtest: crashtest.c
	gcc crashtest.c $(shell pkg-config --libs x11) -o crashtest
