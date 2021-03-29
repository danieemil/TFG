
#Commands
CC = g++
CXXFLAGS = -g -Wall -std=gnu++11 -I./src -I./obj


#Directories and files
SOURCE_DIR = src
COMPILED_DIR = obj

SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.cpp)
COMPILED_FILES := $(foreach dir,$(SOURCE_FILES:.cpp=.o), $(COMPILED_DIR)/$(notdir $(dir)))

GRAPHICS = gfx

TSXFILES = $(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.tsx)))
TSXFILESDIR = $(foreach dir,$(GRAPHICS), $(wildcard $(dir)/*.tsx))
TILESETNAMES = $(patsubst %.tsx, %, $(TSXFILES))
TILESETDIRS = $(addprefix gfx/, $(TILESETNAMES))
T3SFILES = $(patsubst %.tsx, %.t3s, $(TSXFILESDIR))

LINKED_FILE := /home/tuba/Escritorio/project3ds/TFG/conversor

LINKED_FILE := conversor

.PHONY: all clean


all: $(LINKED_FILE)




#Compiling .cpp
$(COMPILED_DIR)/%.o: $(SOURCE_DIR)/%.cpp

	$(CC) -o $@ -c $< $(CXXFLAGS)

#Linking all into one file
$(LINKED_FILE): $(COMPILED_FILES)

	@echo Linking: $^
	@$(CC) $^ -o $@ $(CXXFLAGS)



clean:
	@rm -rf $(COMPILED_DIR)/*.o $(LINKED_FILE) $(TILESETDIRS) $(T3SFILES)

$(TILESETDIRS):
	@mkdir -p $@

crop: $(TILESETDIRS) $(T3SFILES)


%.t3s: %.tsx
	. env/bin/activate; python crop_tilesets.py $(CURDIR)/$<