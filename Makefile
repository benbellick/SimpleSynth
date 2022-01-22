#Compiler
CXX = g++
CC = g++
CXXFLAGS = -std=c++17 

#Dirs
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

#Files
OBJS = $(OBJDIR)/main.o $(OBJDIR)/osc.o $(OBJDIR)/breakpoints.o

CXXFLAGS += -I$(INCDIR)

$(BINDIR)/main: $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BINDIR)/main

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INCDIR)/osc.hpp $(INCDIR)/breakpoints.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/breakpoints.o: $(SRCDIR)/breakpoints.cpp $(INCDIR)/breakpoints.hpp $(INCDIR)/stream_interface.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/breakpoints.cpp -o $(OBJDIR)/breakpoints.o

$(OBJDIR)/osc.o: $(SRCDIR)/osc.cpp $(INCDIR)/osc.hpp $(INCDIR)/stream_interface.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/osc.cpp -o $(OBJDIR)/osc.o
tags:
	ctags -R src/ include/