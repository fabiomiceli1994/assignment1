# generated files
RESULTS=result.dat
PROGRAM=sparsematrix
OBJS=main.o sparsematrix.o

# additional variables
CPPFLAGS=-std=c++11


all: $(RESULTS)

$(RESULTS): $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) $(OBJS) -o $(PROGRAM)

$(OBJS): %.o: %.cc
	g++ -O3 -Wall -Wfatal-errors -pedantic $(CPPFLAGS) -c $^ -o $@


clean:
	rm -rf $(OBJS) $(PROGRAM) $(RESULTS)
