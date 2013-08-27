CXX=g++
CXXFLAGS= -w -g
	
LIB=Leap
LIB_PARAMS=$(foreach d,$(LIB),-l$d)

LIBDIR=/usr/lib/ /usr/local/lib $(LEAP_SDK_DIR)/lib
LIB_DIR_PARAMS=$(foreach l, $(LIBDIR),-L$l)

INC=$(LEAP_SDK_DIR)/include
INC_PARAMS=$(foreach d, $(INC),-I$d)

SOURCES=LeapTapDemo.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=LeapTapDemo

default: all

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LIB_DIR_PARAMS) $(LIB_PARAMS) -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INC_PARAMS) -c -o $@ $<
