CXX = g++-11 -std=c++20
CXXFLAGS = -Wall -g -MMD -I include 
SOURCES = $(wildcard src/*.cc)
OBJECTS = $(patsubst src/%.cc, build/%.o, $(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)
EXEC = chess

$(EXEC): $(OBJECTS) | build
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) -lX11

build/%.o: src/%.cc | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

-include $(DEPENDS)

.PHONY: clean 
clean:
	rm -rf build/*.o build/*.d $(EXEC)