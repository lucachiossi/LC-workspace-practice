IDIR = .
CXX = g++
CXXFLAGS = -I $(IDIR)

ODIR = .
# LDIR=../lib
# LIBS=-lm $(LDIR)

_DEPS = SortAlgorithms.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = SortAlgorithms.o Sort.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

sort: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm $(ODIR)/*.o sort
