LIBS = 
CXX_FLAGS= -Wall -std=c++11
CXX= g++
CPP_FLAGS= -g
OBJS= extra_math.o graph.o

app: $(foreach obj,$(OBJS),$(obj))
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CXX_FLAGS) $(CPP_FLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f *.o app