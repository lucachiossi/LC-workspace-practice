IDIR = ./code
ODIR = ./bin

CXX = g++
CXXFLAGS = -I $(IDIR) -ljsoncpp

_DEPS = GraphAlgorithms.h GraphSearch.h GraphUtils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# _CODE = GraphAlgorithms.cc GraphSearch.cc GraphUtils.cc GraphMain.cc
# CODE = $(patsubst %,$(IDIR)/%,$(_CODE))

_OBJ = GraphAlgorithms.o GraphSearch.o GraphUtils.o GraphMain.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(IDIR)/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

graph_program: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
clean:
	rm $(ODIR)/*.o graph_program
	# rm -d $(ODIR)

