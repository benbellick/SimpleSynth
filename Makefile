#Compiler
CXX = g++
CC = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lsndFile

#Dirs
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

#Files
OBJS = $(OBJDIR)/main.o $(OBJDIR)/osc.o $(OBJDIR)/envelope.o $(OBJDIR)/osc_bank.o

CXXFLAGS += -I$(INCDIR)

$(BINDIR)/main: $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(BINDIR)/main

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INCDIR)/osc.hpp $(INCDIR)/envelope.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/envelope.o: $(SRCDIR)/envelope.cpp $(INCDIR)/envelope.hpp $(INCDIR)/stream_interface.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/envelope.cpp -o $(OBJDIR)/envelope.o

$(OBJDIR)/osc_bank.o: $(SRCDIR)/osc_bank.cpp $(INCDIR)/osc_bank.hpp $(INCDIR)/stream_interface.hpp $(INCDIR)/osc.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/osc_bank.cpp -o $(OBJDIR)/osc_bank.o

$(OBJDIR)/osc.o: $(SRCDIR)/osc.cpp $(INCDIR)/osc.hpp $(INCDIR)/stream_interface.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/osc.cpp -o $(OBJDIR)/osc.o
tags:
	ctags -R src/ include/
