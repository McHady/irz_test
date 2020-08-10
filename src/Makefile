CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=main.c problem.c str_utils.c error_handling.c sp_pnt.c 
OBJFILES=$(SOURCES:.c=.o)
OBJECTS=$(OBJFILES)
EXECUTABLE=main.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@