INCLDIR	:= include
OBJDIR	:= obj
SRCDIR	:= src
BINDIR	:= bin
DEBDIR	:= debug

CC      := gcc
VPATH		:=
LDFLAGS :=
LIBRARY :=
CXXFLAGS:= -std=c99 -Wall -I$(INCLDIR)

#Source and object files (automatic)
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(subst $(SRCDIR)/,$(OBJDIR)/, $(subst .c,.o, $(SRCS)))

# Define here your main source files separated by spaces (without suffix!)
EXEC = main

#Phony = do not represent a file
#.PHONY: all
all : makedir $(EXEC)

debug: CXXFLAGS += -DDEBUG -g
debug: BINDIR = $(DEBDIR)
debug: makedir $(EXEC)

# For multiple binaries
$(EXEC) : %: %.c $(OBJS)
	$(CC) $(CXXFLAGS) -o $(BINDIR)/$@ $^ -lm -lxml2

# ... With debug mode on
$(DEBUG) : %: %.c $(OBJS)
	$(CC) $(CXXFLAGS) -g -o $(BINDIR)/$@ $^

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CXXFLAGS) -c -o $@ $<

#Clean: delete every binaries and object files
.PHONY: clean
clean :
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*
	rm -rf $(DEBDIR)/*

#Building folders (-p : no error if folder do not exist)
.PHONY: makedir
makedir :
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)

#For some debug
.PHONY: print
print :
	echo $(SRCS)
	echo $(OBJS)

#Remarks:
# $@ : filename representing the target
# $< : filename of the first prerequisite
# $^ : filenames of all prerequisites, separated by spaces. Dupplicated are removed.
# $? : names of all prerequisites that are newer than the target, separated by spaces
# $+ : similar to $^ but include dupplicates
# $* : stem of target file (filename without suffix)
