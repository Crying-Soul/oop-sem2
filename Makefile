CC := g++
CXXFLAGS := -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wconversion -Weffc++ -Wfloat-equal -fstack-protector-strong -fPIE -pie
LIBS := 
SRC_DIR := src
INCDIR := include
OBJDIR := obj

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

EXECUTABLE := sea_battle

DOXYGEN_CONFIG := Doxyfile

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CXXFLAGS) $^ -o $@ $(LIBS)


$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR) $(EXECUTABLE)

docs:
	@doxygen $(DOXYGEN_CONFIG)

.PHONY: all clean docs
