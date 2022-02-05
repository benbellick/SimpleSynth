#Directories
SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.cpp)
INCDIR = include
INC = $(wildcard $(INCDIR)/*.hpp)
OBJDIR = obj
OBJ = $(subst $(SRCDIR),$(OBJDIR),$(SRC:.cpp=.o))
BINDIR = bin

#Compiler
CXX = g++
CXXFLAGS = -std=c++17 -I$(INCDIR)
LDFLAGS = -lsndFile

$(BINDIR)/main: $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) $^  -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@
.PHONY: clean
clean:
	rm -f $(OBJ) $(BINDIR)/main

tags: $(SRC) $(INC)
	ctags -R $^
