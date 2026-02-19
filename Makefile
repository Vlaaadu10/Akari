# Copyright PCLP Team, 2025

# Compiler setup.
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99

# Define targets, e.g., ninel, codeinvim, vectsecv, nomogram.
TARGETS=akari
OBJ_FILES=$(TARGETS:%=%.o)

# Manually define all targets.
build: $(TARGETS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
akari: akari.o
	$(CC) $(CFLAGS) $^ -o $@
# Pack the solution into a zip file.
pack:
	zip -FSr 314CA_AlexandruVladutStefan_Tema1.zip README Makefile *.c *.h

# Clean the solution.
clean:
	rm -f $(TARGETS) $(OBJ_FILES) *.out *.error

.PHONY: build pack clean
