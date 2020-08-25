IDIR = ./code
ODIR = ./bin

CXX = g++
CXXFLAGS = -I $(IDIR) -ljsoncpp

_DEPS = GraphUtils.h GraphSearch.h GraphAlgorithms.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# _CODE = GraphAlgorithms.cc GraphSearch.cc GraphUtils.cc GraphMain.cc
# CODE = $(patsubst %,$(IDIR)/%,$(_CODE))

_OBJ = GraphUtils.o GraphSearch.o GraphAlgorithms.o GraphMain.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(IDIR)/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

graph_program: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
clean:
	rm $(ODIR)/*.o graph_program
	# rm -d $(ODIR)

