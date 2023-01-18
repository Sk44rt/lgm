CXX = g++
STD = c++14
CFLAGS = -std=$(STD)

SRC = ./src
RUNNERS_SRC = $(SRC)/runners
HEADERS = ./headers
HELPERS = ./helpers
CFLAGS += -I$(HELPERS) -I$(HEADERS) -lpthread

# set TESTING to null for release build
# e.g. "TESTING = "
TESTING = debug

SOURCES = $(SRC)/utils.cpp $(RUNNERS_SRC)/steam.cpp
ifeq ($(TESTING),debug)
	SOURCES += $(SRC)/test.cpp
else
	SOURCES += $(SRC)/main.cpp
endif
OBJECTS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

TARGET = lgm

%.o:$(SRC)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

%.o:$(RUNNERS_SRC)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET):$(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(CFLAGS)

all: $(TARGET)

clean:
	rm $(TARGET) $(OBJECTS)
