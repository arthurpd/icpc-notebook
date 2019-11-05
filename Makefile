CXX= g++

CPPFILES =  $(filter-out misc/bit_tricks/bit_tricks.cpp, $(shell find $(SRCDIR) -name '*.cpp'))
OBJFILES = $(patsubst %.cpp,%.o,$(CPPFILES))
HASHFILES = $(patsubst %.cpp,%.cpp.hash,$(CPPFILES))
OUTFILES = $(patsubst %.cpp,%.out,$(CPPFILES))

CPPFLAGS= -g -std=c++14 -Wall -Wextra -Wno-unused-result -Wconversion -Wfatal-errors -fsanitize=undefined,address

SRCDIR = combinatorial contest data_structures geometry graph misc number_theory numerical string

EXEFILE = main.exe

all: $(OBJFILES)
	cd latex && pdflatex notebook.tex
	cd latex && pdflatex applications.tex

%.o: %.cpp
	./gen_hash.sh $<
	./check_line_width.sh $<
#$(CXX) -c $< -o $@ $(CPPFLAGS)

clean:
	rm -f $(OBJFILES) $(HASHFILES) $(OUTFILES)
	rm -f latex/*~ latex/*.{aux,log,nav,out,snm,toc,vrb}

