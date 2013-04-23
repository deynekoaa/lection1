TARGET=readline

CFLAGS ?= -O1

all: $(TARGET)

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURSES:.c=.o) 



$(TARGET): help.o readline.o worker.o
	$(CC) $(CFLAGS) help.o readline.o worker.o -o readline -lreadline

clean:
	rm -fr *.o $(TARGET)







