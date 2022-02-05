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
OBJS = $(OBJDIR)/main.o $(OBJDIR)/osc.o $(OBJDIR)/envelope.o $(OBJDIR)/static_osc_bank.o $(OBJDIR)/lookup_osc.o

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

$(OBJDIR)/static_osc_bank.o: $(SRCDIR)/static_osc_bank.cpp $(INCDIR)/static_osc_bank.hpp $(INCDIR)/stream_interface.hpp $(INCDIR)/osc.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/static_osc_bank.cpp -o $(OBJDIR)/static_osc_bank.o

$(OBJDIR)/lookup_osc.o: $(SRCDIR)/lookup_osc.cpp $(INCDIR)/lookup_osc.hpp $(INCDIR)/stream_interface.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/lookup_osc.cpp -o $(OBJDIR)/lookup_osc.o

$(OBJDIR)/osc.o: $(SRCDIR)/osc.cpp $(INCDIR)/osc.hpp $(INCDIR)/stream_interface.hpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(SRCDIR)/osc.cpp -o $(OBJDIR)/osc.o
tags:
	ctags -R src/ include/
