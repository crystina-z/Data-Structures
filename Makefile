CXX = g++
CXXFLAGS = $(shell pkg-config)
CXXFLAGS += -g -Wall -std=c++1y -MMD


FILES = sorting/MergeSort.cpp sorting/SortBase.cpp VanEmdeBoas.cpp
MERGESORT_OBJECTS = sorting/MergeSort.o sorting/SortBase.o
VEB_OBJECTS = VanEmdeBoas.o

OBJECTS = $(MERGESORT_OBJECTS) $(VEB_OBJECTS)
DEPENDS = $(OBJECTS:.o=.d)
EXECS = mergesort veb

all: $(EXECS)
mergesort: mergesort
veb: veb
#mergesort veb

%.o: %.cpp $(CXX) $(CXXFLAGS) -c $< -o $@
sorting/%.o: sorting/%.cpp $(CXX) $(CXXFLAGS) -c $< -o $@

mergesort: $(MERGESORT_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

veb: $(VEB_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

depend:
	makedepend -f- -- $(CXXFLAGS) -- $(FILES) > .depend

-include $(DEPENDS)

# Clean up extra dependencies and objects.
clean:
	/bin/rm -f $(DEPENDS) $(OBJECTS) $(EXECS)
