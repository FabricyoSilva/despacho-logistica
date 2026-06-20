# Makefile - Sistema de Despacho de Logistica Urbana
#
#   make          -> compila e gera o executavel ./despacho
#   make run      -> compila e roda com o mapa de exemplo
#   make clean    -> remove objetos e executavel

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude
SRCDIR  = src
OBJDIR  = build
TARGET  = despacho

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET) data/mapa_exemplo.txt

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all run clean
