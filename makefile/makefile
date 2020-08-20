IDIR = ./src
ODIR = ./bin

CXX = g++
CXXFLAGS = -I $(IDIR)

_DEPS = Data.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_CODE = Data.cc MemoryManagement.cc
CODE = $(patsubst %,$(IDIR)/%,$(_CODE))

_OBJ = Data.o MemoryManagement.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(IDIR)/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

memory_management_example: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
clean:
	rm $(ODIR)/*.o memory_management_example
	# rm -d $(ODIR)

