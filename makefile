TARGET  = ShiftAnd$(EXEEXT)
SOURCES = ShiftAnd.cpp

CXXFLAGS = -Wall -W -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wfloat-equal -Wpointer-arith
INCLUDES = -idirafter .
OBJECTS  = $(SOURCES:.cpp=.o)

.PHONY: all 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

.SUFFIXES: .cpp .o
.cpp.o: 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

depend: 
	$(CXX) -MM $(INCLUDES) $(CXXFLAGS) $(SOURCES) > dependencies

clean: 
	rm -f $(OBJECTS) $(TARGET)
