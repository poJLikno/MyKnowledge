SRC_DIR=src
OUT_FILE=x64/out.exe

CC=g++11
#CC=g++
CFLAGS=--std=c++20 -Wall -O2 -fsanitize=address -g -fno-omit-frame-pointer

SOURCES=$(shell find $(SRC_DIR) -type f -name "*.cpp")
#SOURCES=$(shell dir $(SRC_DIR)\*.cpp /S /B)

.PHONY: run clean

$(OUT_FILE): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@
	
run: $(OUT_FILE)
	./$(OUT_FILE)

clean:
#del /F /S /Q x64\*
	rm -fr x64/*
