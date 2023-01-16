CXX = g++
STD = c++14
CFLAGS = -std=$(STD)

SRC = ./src
HEADERS = ./headers
HELPERS = ./helpers
CFLAGS += -I$(HELPERS) -I$(HEADERS) -lpthread

TESTING = nothing

SOURCES = $(SRC)/utils.cpp
ifdef TESTING
	SOURCES += $(SRC)/test.cpp
else
	SOURCES += $(SRC)/main.cpp
endif
OBJECTS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

TARGET = lgm

%.o:$(SRC)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET):$(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(CFLAGS)

all: $(TARGET)

clean:
	rm $(TARGET) $(OBJECTS)
