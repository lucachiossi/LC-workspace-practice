IDIR = ./src
ODIR = ./bin

CXX = g++
CXXFLAGS = -I $(IDIR)

_DEPS = Lib.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_CODE = Lib.cc Main.cc
CODE = $(patsubst %,$(IDIR)/%,$(_CODE))

_OBJ = Lib.o Main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(IDIR)/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

program: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
clean:
	rm $(ODIR)/*.o program
