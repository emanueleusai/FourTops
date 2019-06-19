CXX := g++
CXXFLAGS := -Wall `root-config --glibs --cflags` -fPIC -O3
LD := g++
LDFLAGS := -g

OBJ_DIR := build
SRC_DIR := src
EXE_DIR := bin
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
# HEADERS := $(SRC:%.cpp=include/%.h)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
# OBJECTS=$(SOURCES:.cpp=.o)
# HEADERS=$(SOURCES:.cpp=.h)
EXECUTABLE=$(EXE_DIR)/FourTops

#CXXFLAGS += $(shell root-config --cflags)
#LIBS = $(shell root-config --libs)
#NGLIBS = $(shell root-config --glibs)
#GLIBS = $(filter-out -lNew, $(NGLIBS))

.SUFFIXES: .cpp


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SOURCES)
	$(CXX) -c $(CXXFLAGS) $< -o $@ -I$(PWD)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)