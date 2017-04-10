SRCS = ./fnbounds/fnbounds_dynamic.c \
			 ./fnbounds/fnbounds_common.c \
			 ./utils/urand.c \
			 ./utils/cskiplist.c \
			 ./utils/usec_time.c \
			 ./utils/binarytree.c \
			 ./utils/BalancedTree.c \
			 ./utils/pfq-rwlock.c \
			 ./utils/mcs-lock.c \
			 ./utils/spinlock.c \
			 ./utils/randomizer.c \
			 ./utils/generic_pair.c \
			 ./utils/tokenize.c \
			 ./ip-normalized.c \
			 ./messages/debug-flag.c \
			 ./trampoline/common/trampoline.c \
			 ./unwind/common/backtrace-lite.c \
			 ./unwind/common/uw_recipe_map.c \
			 ./unwind/common/interval_t.c \
			 ./unwind/common/unw-throw.c \
			 ./unwind/common/ildmod_stat.c \
			 ./unwind/common/stack_troll.c \
			 ./unwind/common/backtrace.c \
			 ./unwind/common/binarytree_uwi.c \
			 ./unwind/x86-family/amd-xop.c \
			 ./unwind/x86-family/x86-unwind.c \
			 ./unwind/x86-family/x86-unwind-support.c \
			 ./unwind/x86-family/x86-unwind-interval.c \
			 ./unwind/x86-family/x86-validate-retn-addr.c \
			 ./unwind/x86-family/x86-cold-path.c \
			 ./unwind/x86-family/x86-all.c \
			 ./unwind/x86-family/x86-unwind-interval-fixup.c \
			 ./os/linux/dylib.c \
			 ./srg_backtrace.c \
			 ./loadmap.c \
			 ./unwind/x86-family/manual-intervals/x86-gcc-main64.c \
			 ./unwind/x86-family/manual-intervals/x86-linux-dlresolver.c \
			 ./unwind/x86-family/manual-intervals/x86-intel11-f90main.c \
			 ./unwind/x86-family/manual-intervals/x86-intel-align32.c \
			 ./unwind/x86-family/manual-intervals/x86-intel-align64.c \
			 ./unwind/x86-family/manual-intervals/x86-intel-composer2013-mic.c \
			 ./unwind/x86-family/manual-intervals/x86-32bit-main.c \
			 ./unwind/x86-family/manual-intervals/x86-32bit-icc-variant.c \
			 ./unwind/x86-family/manual-intervals/x86-pgi-mp_pexit.c

#./fnbounds/ba/amd-xop.c \
	./unwind/common/default_validation_summary.c \

INCS =  ./frame.h \
				./fnbounds/fnbounds_interface.h \
				./fnbounds/fnbounds_file_header.h \
				./fnbounds/fnbounds_table_interface.h \
				./utils/tokenize.h \
				./utils/BalancedTree.h \
				./utils/stdatomic.h \
				./utils/generic_val.h \
				./utils/urand.h \
				./utils/pfq-rwlock.h \
				./utils/cskiplist_defs.h \
				./utils/randomizer.h \
				./utils/spinlock.h \
				./utils/mcs-lock.h \
				./utils/usec_time.h \
				./utils/binarytree.h \
				./utils/generic_pair.h \
				./utils/cskiplist.h \
				./srg_backtrace.h \
				./ip-normalized.h \
				./messages/messages.h \
				./messages/debug-flag.h \
				./loadmap.h \
				./trampoline/common/trampoline.h \
				./unwind/common/backtrace_info.h \
				./unwind/common/interval_t.h \
				./unwind/common/binarytree_uwi.h \
				./unwind/common/unwindr_info.h \
				./unwind/common/unwind-interval.h \
				./unwind/common/uw_recipe.h \
				./unwind/common/unw-datatypes.h \
				./unwind/common/validate_return_addr.h \
				./unwind/common/uw_recipe_map.h \
				./unwind/common/fence_enum.h \
				./unwind/common/stack_troll.h \
				./unwind/common/backtrace.h \
				./unwind/common/unwind.h \
				./unwind/common/unw-throw.h \
				./unwind/common/std_unw_cursor.h \
				./unwind/common/ildmod_stat.h \
				./unwind/common/dbg_backtrace.h \
				./unwind/x86-family/x86-cold-path.h \
				./unwind/x86-family/x86-interval-highwatermark.h \
				./unwind/x86-family/x86-push.h \
				./unwind/x86-family/x86-unwind-interval.h \
				./unwind/x86-family/x86-move.h \
				./unwind/x86-family/x86-unwind-analysis.h \
				./unwind/x86-family/x86-jump.h \
				./unwind/x86-family/x86-addsub.h \
				./unwind/x86-family/x86-process-inst.h \
				./unwind/x86-family/x86-return.h \
				./unwind/x86-family/x86-and.h \
				./unwind/x86-family/x86-lea.h \
				./unwind/x86-family/x86-build-intervals.h \
				./unwind/x86-family/x86-decoder.h \
				./unwind/x86-family/x86-enter.h \
				./unwind/x86-family/x86-leave.h \
				./unwind/x86-family/x86-validate-retn-addr.h \
				./unwind/x86-family/amd-xop.h \
				./unwind/x86-family/x86-canonical.h \
				./unwind/x86-family/x86-call.h \
				./unwind/x86-family/mcontext.h \
				./unwind/x86-family/x86-unwind-interval-fixup.h \
				./unwind/x86-family/x86-interval-arg.h \
				./unwind/x86-family/unw-datatypes-specific.h \
				./os/linux/dylib.h \
				./syserv-mesg.h \
				./include/gcc-attr.h \
				./include/uint.h \
				./memory/hpcrun-malloc.h \
				./memory/mem_manager.h \
				./isa-x86-instruction-set.h \
				./config.h

#./fnbounds/ba/process-ranges.h \
				./fnbounds/ba/function-entries.h \
				./fnbounds/ba/intervals.h \
				./fnbounds/ba/server.h \
				./fnbounds/ba/amd-xop.h \
				./fnbounds/ba/code-ranges.h 

DEPS = $(INCS)

#CXX = gcc 
CXX = clang
#-D_GNU_SOURCE 

SYMTAB_LIBS_ROOT = /home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/symtabAPI/lib
SYMTAB_LIBS = -L$(SYMTAB_LIBS_ROOT) -lsymtabAPI -lcommon -ldynDwarf -ldynElf  
SYMTAB_INC = /home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/symtabAPI/include 

DWARF_LIBS_ROOT = /home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/libdwarf/lib
DWARF_LIBS = -L$(DWARF_LIBS_ROOT) -ldwarf 
DWAEF_INC = /home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/libdwarf/include

ELF_LIBS_ROOT = /home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/libelf/lib
ELF_LIBS = -L$(ELF_LIBS_ROOT) -lelf
ELF_INC = /home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-externals-dist/libelf/include

XED2_LIBS_ROOT = /home/hongyuliu/workspace/backtrace/libs/xed2/lib
XED2_LIBS = -L$(XED2_LIBS_ROOT) -lxed
XED2_INC = /home/hongyuliu/workspace/backtrace/libs/xed2/include

# Framework
CFLAGS += -O0 -Wall -g -fPIC -fno-omit-frame-pointer -D_GNU_SOURCE -D__GNUC_ATOMICS

INCLUDE_DIRS = -I. -I$(SYMTAB_INC) -I$(DWAEF_INC) -I$(ELF_INC) -I$(XED2_INC) -Wl,-rpath,$(SYMTAB_LIBS_ROOT):$(DWARF_LIBS_ROOT):$(ELF_LIBS_ROOT):$(XED2_LIBS_ROOT)
LIBS = $(SYMTAB_LIBS) $(DWARF_LIBS) $(ELF_LIBS) $(XED2_LIBS) -ldl

FNBOUNDS = function-entries.o x86-process-ranges.o binaryanalysis.o intervals.o code-ranges.o
FNBOUNDS_OBJS = $(addprefix fnbounds/ba/, $(FNBOUNDS))

TARGETS = libbacktrace.so

all: $(TARGETS)

FNBOUNDS_MK:	
	cd fnbounds/ba && make -f Makefile 
	
#gcc -fPIC -std=c99 -c pthread_create.c
$(TARGETS): $(DEPS) FNBOUNDS_MK
#	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $(SRCS) -c -o backtrace.o
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) -shared $(SRCS) $(FNBOUNDS_OBJS) -o $(TARGETS) $(LIBS)

clean:
	rm -f $(TARGETS)
	cd fnbounds/ba && make -f Makefile clean 

