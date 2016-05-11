# Executables
TARGET   = larasnake
T_TARGET = testAll

# Compiler
CC       = gcc
# Compiling flags
CFLAGS   = -Wall -I. `sdl-config --libs` -lSDL_image -lSDL_ttf -lSDL_mixer -g

# Linker
LINKER   = gcc -o
# Linking flags
LFLAGS   = -I. -lm `sdl-config --libs` -lSDL_image -lSDL_ttf -lSDL_mixer -g

# Project directories
SRCDIR   = src
OBJDIR   = build
BINDIR   = bin

# Get files for tests compiling
T_DIR = tests
T_SOURCES  := $(wildcard $(T_DIR)/*.c)
T_OBJECTS  := $(T_SOURCES:$(T_DIR)/%.c=$(OBJDIR)/%.o)

# Get files to compile the project
SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Get all objects without the main.o
OBJBASIC = $(filter-out build/main.o, $(OBJECTS))

# Shortcut to rm files
rm       = rm -f


####################################################################
# Every compiling links availables

all: $(BINDIR)/$(TARGET)
test: $(BINDIR)/$(T_TARGET)

####################################################################
# Compiles the project

$(BINDIR)/$(TARGET): $(OBJECTS)
	@test -d $(BINDIR) || mkdir -p $(BINDIR)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compiled "$<" successfully!"


#####################################################################
# Compiles the test

$(BINDIR)/$(T_TARGET): $(OBJBASIC) $(T_OBJECTS)
	@test -d $(BINDIR) || mkdir -p $(BINDIR)
	@$(LINKER) $@ $(OBJBASIC) $(T_OBJECTS) $(LFLAGS) -l cmocka
	@echo "Linking complete!"

$(T_OBJECTS): $(OBJDIR)/%.o : $(T_DIR)/%.c
	@test -d $() || mkdir -p $(OBJDIR)
	@$(CC) -c $< -o $@ $(CFLAGS) -l cmocka
	@echo "Compiled "$<" successfully!"


#####################################################################
# Allow to clean and remove

.PHONEY: clean
clean:
	@$(rm) $(OBJDIR)/*.o
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@$(rm) $(BINDIR)/testAll
	@echo "Executable removed!"
