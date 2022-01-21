CXX = g++
CC = g++
CXXFLAGS = -std=c++17 
OBJDIR = k

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

CXXFLAGS += -I$(INCDIR)

$(BINDIR)/main: $(OBJDIR)/main.o $(OBJDIR)/osc.o
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJDIR)/main.o $(OBJDIR)/osc.o -o $(BINDIR)/main

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INCDIR)/osc.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/osc.o: $(SRCDIR)/osc.cpp $(INCDIR)/osc.hpp $(INCDIR)/stream_interface.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/osc.cpp -o $(OBJDIR)/osc.o
tags:
	ctags -R src/ include/
