CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -Iinclude
LDFLAGS = -lyaml-cpp

SOURCES = src/skill_engine.cpp src/file_processor.cpp src/pattern_scanner.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = libskill_engine.a

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

install:
	cp $(TARGET) /usr/local/lib/
	cp -r include/* /usr/local/include/

.PHONY: all clean install