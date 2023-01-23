CXX = g++
STD = c++11
CFLAGS = -std=$(STD)

IMGUI = ./imgui
IMGUI_BACKENDS = $(IMGUI)/backends
IMGUI_SOURCES = $(wildcard $(IMGUI)/*.cpp)
IMGUI_SOURCES += $(wildcard $(IMGUI_BACKENDS)/*.cpp)
IMGUI_CFLAGS = -I$(IMGUI) -I$(IMGUI_BACKENDS) `pkg-config --static --libs glfw3` `pkg-config --cflags glfw3`
IMGUI_OBJS = $(addsuffix .o, $(basename $(notdir $(IMGUI_SOURCES))))

SRC = ./src
RUNNERS_SRC = $(SRC)/runners
PKG_MANAGERS= $(SRC)/pkgmanagers
HEADERS = ./headers
HELPERS = ./helpers
CFLAGS += -I$(HELPERS) -I$(HEADERS) -lpthread -lGL -g -Wall -Wformat
CFLAGS += $(IMGUI_CFLAGS)

# set TESTING to null for release build
# e.g. "TESTING = "
TESTING = 

SOURCES = $(SRC)/gui.cpp $(SRC)/utils.cpp $(RUNNERS_SRC)/steam.cpp $(PKG_MANAGERS)/snap.cpp $(PKG_MANAGERS)/flatpak.cpp
ifeq ($(TESTING),debug)
	SOURCES += $(SRC)/test.cpp
else
	SOURCES += $(SRC)/main.cpp
endif
OBJECTS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
OBJECTS += $(IMGUI_OBJS)

TARGET = lgm

%.o:$(SRC)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

%.o:$(RUNNERS_SRC)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

%.o:$(PKG_MANAGERS)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

%.o:$(IMGUI)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

%.o:$(IMGUI_BACKENDS)/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

$(TARGET):$(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(CFLAGS)

all: $(TARGET)

clean:
	rm $(TARGET) $(OBJECTS)
