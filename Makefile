# project name (generate executable with this name)
TARGET   = larasnake
T_TARGET = testAll

CC       = gcc
# compiling flags here
CFLAGS   = -Wall -I. `sdl-config --libs` -lSDL_image -lSDL_ttf -g

LINKER   = gcc -o
# linking flags here
LFLAGS   = -I. -lm `sdl-config --libs` -lSDL_image -lSDL_ttf -g

# change these to set the proper directories where each files shoould be
SRCDIR   = src
OBJDIR   = build
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

OBJBASIC = $(filter-out build/main.o, $(OBJECTS))

T_DIR = tests
T_SOURCES  := $(wildcard $(T_DIR)/*.c)
T_OBJECTS  := $(T_SOURCES:$(T_DIR)/%.c=$(OBJDIR)/%.o)


####################################################################

all: $(BINDIR)/$(TARGET)
test: $(BINDIR)/$(T_TARGET)

####################################################################

$(BINDIR)/$(TARGET): $(OBJECTS)
	@test -d $(BINDIR) || mkdir -p $(BINDIR)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compiled "$<" successfully!"


#####################################################################



$(BINDIR)/$(T_TARGET): $(OBJBASIC) $(T_OBJECTS)
	@test -d $(BINDIR) || mkdir -p $(BINDIR)
	@$(LINKER) $@ $(OBJBASIC) $(T_OBJECTS) $(LFLAGS) -l cmocka
	@echo "Linking complete!"

$(T_OBJECTS): $(OBJDIR)/%.o : $(T_DIR)/%.c
	@test -d $() || mkdir -p $(OBJDIR)
	@$(CC) -c $< -o $@ $(CFLAGS) -l cmocka
	@echo "Compiled "$<" successfully!"


#####################################################################


.PHONEY: clean
clean:
	@$(rm) $(OBJDIR)/*.o
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@$(rm) $(BINDIR)/testAll
	@echo "Executable removed!"
