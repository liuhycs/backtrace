SRCS = function-entries.cpp \
			 x86-process-ranges.cpp \
			 binaryanalysis.cpp \
			 intervals.cpp \
			 code-ranges.cpp

INCS = process-ranges.h \
			 function-entries.h \
			 intervals.h \
			 binaryanalysis.h \
			 code-ranges.h

DEPS = $(INCS)

#CXX = g++
CXX = clang++
#-D_GNU_SOURCE 

SYMTAB_LIBS = -L/home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/symtabAPI/lib -lsymtabAPI -lcommon -ldynDwarf -ldynElf  
SYMTAB_INC = /home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/symtabAPI/include 

DWARF_LIBS = -L/home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/libdwarf/lib -ldwarf 
DWAEF_INC = /home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/libdwarf/include

ELF_LIBS = -L/home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/libelf/lib -lelf
ELF_INC = /home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/libelf/include

XED2_LIBS = -L/home/hongyuliu/workspace/backtrace/libs/xed2/lib -lxed
XED2_INC = /home/hongyuliu/workspace/backtrace/libs/xed2/include

# Framework
CFLAGS += -O2 -Wall -g -fPIC -fno-omit-frame-pointer 

INCLUDE_DIRS = -I. -I../.. -I$(SYMTAB_INC) -I$(DWAEF_INC) -I$(ELF_INC) -I$(XED2_INC)
LIBS = $(SYMTAB_LIBS) $(DWARF_LIBS) $(ELF_LIBS) $(XED2_LIBS) 

TARGETS = function-entries.o x86-process-ranges.o binaryanalysis.o intervals.o code-ranges.o

all: $(TARGETS)

%.o:%.cpp $(DEPS)
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $<

$(TARGETS1): $(DEPS)
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $(SRCS) -c -o $(TARGETS) $(LIBS)

clean:
	rm -f $(TARGETS)

