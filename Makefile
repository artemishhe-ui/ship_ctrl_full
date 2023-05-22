# Makefile for building and installing mysharedlib.so

CXX = g++

SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBDIR = lib
INSTALLDIR = /usr/local/lib

CXXFLAGS = -Wall -Wextra -g -fPIC -I$(INCDIR) -std=c++20 -flto -O3
#LDFLAGS = -shared -flto -O3 -Wl,-soname,lib$(LIB_NAME).so.$(LIB_VERSION)

# Library options
#LIB_NAME = DllShip
#LIB_VERSION = 1
#LIB_SO_VERSION = $(LIB_VERSION).0.0
#LIB_TARGET = $(LIBDIR)/lib$(LIB_NAME).so.$(LIB_SO_VERSION)


PCH = $(INCDIR)/pch.h
PCH_OBJECT = $(OBJDIR)/pch.h.gch

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

TARGET = nmea_console

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)

#$(PCH_OBJECT): $(PCH)
#	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#test: $(LIB_TARGET)
#	$(CXX) $(CXXFLAGS) -L/usr/local/lib -Wl,-rpath=/usr/local/lib -Wall -o test $(SRCDIR)/test.cpp -l:libDllShip.so.1
#	./test

GNSSData:
	$(CXX) $(CXXFLAGS) -L/usr/local/lib -Wl,-rpath=/usr/local/lib -o GNSSData $(SRCDIR)/GNSSData.cpp -lglog
	./GNSSData

clean:
	rm -f $(OBJECTS) $(OBJECT) $(TARGET) test

test: $(TARGET)
	./nmea_console

install:
	install -m 644 $(LIB_TARGET) $(INSTALLDIR)
	ldconfig