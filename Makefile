TARGET=anagramme

CFLAGS=-Wall -Werror
CFLAGS+=-g -O0

all:	$(TARGET)

clean:
	$(RM) $(TARGET)
