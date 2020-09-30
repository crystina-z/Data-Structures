CXX = g++
CXXFLAGS = $(shell pkg-config)
CXXFLAGS += -g -Wall -std=c++1y -MMD


FILES = sorting/MergeSort.cpp sorting/SortBase.cpp
OBJECTS = sorting/MergeSort.o sorting/SortBase.o
DEPENDS = $(OBJECTS:.o=.d)

all: mergesort

sorting/%.o: sorting/%.cpp $(CXX) $(CXXFLAGS) -c $< -o $@

mergesort: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

depend:
	makedepend -f- -- $(CXXFLAGS) -- $(FILES) > .depend

-include $(DEPENDS)

# Clean up extra dependencies and objects.
clean:
	/bin/rm -f $(DEPENDS) $(OBJECTS) mergesort
