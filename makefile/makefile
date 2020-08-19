IDIR = ./code
CXX = g++
CXXFLAGS = -I $(IDIR)

ODIR = ./code/objects

_DEPS = GraphAlgorithms.h GraphRepresentation.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_CODE = GraphAlgorithms.cc GraphRepresentation.cc Graphs.cc
CODE = $(patsubst %,$(IDIR)/%,$(_CODE))

_OBJ = GraphAlgorithms.o GraphRepresentation.o Graphs.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(IDIR)/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

graphs: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
clean:
	rm $(ODIR)/*.o graphs

