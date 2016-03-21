# project name (generate executable with this name)
TARGET   = larasnake

CC       = gcc
# compiling flags here
CFLAGS   = -Wall -I. `sdl-config --libs` -lSDL_image

LINKER   = gcc -o
# linking flags here
LFLAGS   = -I. -lm `sdl-config --libs` -lSDL_image

# change these to set the proper directories where each files shoould be
SRCDIR   = src
OBJDIR   = build
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@test -d $(BINDIR) || mkdir -p $(BINDIR)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compiled "$<" successfully!"

.PHONEY: test
test: build/board.o tests/testAll.o tests/testBoard.o
	gcc -o bin/testAll build/board.o tests/testBoard.o tests/testAll.o -l cmocka

testAll.o: tests/testBoard.h
	gcc -o tests/testAll.o -c tests/testAll.c -l cmocka

testBoard.o: src/board.h tests/testBoard.h tests/testBoard.c
	gcc -o tests/testBoard.o -c tests/testBoard.c -l cmocka


.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@$(rm) $(BINDIR)/testLarasnake
	@echo "Executable removed!"
