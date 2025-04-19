.ONESHELL:
.RECIPEPREFIX=>

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=termclock

CFLAGS=-g0
CFLAGS+=-m64
CFLAGS+=-march=native
CFLAGS+=-mtune=native
CFLAGS+=-O2
CFLAGS+=-pedantic
CFLAGS+=-pedantic-errors
CFLAGS+=-pipe
CFLAGS+=-s
CFLAGS+=-std=c23
CFLAGS+=-Wall
CFLAGS+=-Werror
CFLAGS+=-Wextra
CFLAGS+=-Wpedantic

all: $(TARGET)
>$(RM) $(OBJECTS)

clean:
>$(RM) $(TARGET)

run:
>./$(TARGET)

$(TARGET): $(OBJECTS)
>$(LINK.c) $^ -o $@
