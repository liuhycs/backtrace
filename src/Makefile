SRCS = disabled.c loadmap.c trampoline/common/trampoline.c \
			 fnbounds/fnbounds_common.c srg_backtrace.c os/linux/dylib.c \
			 ip-normalized.c fnbounds/fnbounds_client.c fnbounds/fnbounds_dynamic.c \
			 unwind/common/backtrace.c unwind/common/unw-throw.c \
			 unwind/common/binarytree_uwi.c unwind/common/ildmod_stat.c \
			 unwind/common/interval_t.c unwind/common/stack_troll.c \
			 unwind/common/uw_recipe_map.c \
			 unwind/x86-family/x86-all.c unwind/x86-family/amd-xop.c \
			 unwind/x86-family/x86-cold-path.c \
			 unwind/x86-family/x86-validate-retn-addr.c \
			 unwind/x86-family/x86-unwind-interval.c \
			 unwind/x86-family/x86-unwind-interval-fixup.c \
			 unwind/x86-family/x86-unwind.c \
			 unwind/x86-family/x86-unwind-support.c 

#\ unwind/x86-family/manual-intervals/x86-gcc-main64.c \
			 unwind/x86-family/manual-intervals/x86-linux-dlresolver.c \
			 unwind/x86-family/manual-intervals/x86-intel11-f90main.c \
			 unwind/x86-family/manual-intervals/x86-intel-align32.c \
			 unwind/x86-family/manual-intervals/x86-intel-align64.c \
			 unwind/x86-family/manual-intervals/x86-intel-composer2013-mic.c \
			 unwind/x86-family/manual-intervals/x86-32bit-main.c \
			 unwind/x86-family/manual-intervals/x86-32bit-icc-variant.c \
			 unwind/x86-family/manual-intervals/x86-pgi-mp_pexit.c

INCS =  ip-normalized.h \
				srg_backtrace.h \
				os/linux/dylib.h

DEPS = $(INCS)

#CXX = gcc -std=gnu99 
CXX = clang -std=gnu99
#-D_GNU_SOURCE 

XED2_LIBS = -L/home/hongyuliu/workspace/backtrace/libs/xed2/lib -lxed
XED2_INC = /home/hongyuliu/workspace/backtrace/libs/xed2/include

# Framework
CFLAGS += -O2 -Wall -g -fPIC -fno-omit-frame-pointer -D_GNU_SOURCE -D__GNUC_ATOMICS

INCLUDE_DIRS = -I. -I$(XED2_INC) -Wl,-rpath,/home/hongyuliu/workspace/backtrace/libs/xed2/lib
LIBS = $(XED2_LIBS)

TARGETS = libbacktrace.so

all: $(TARGETS)

#gcc -fPIC -std=c99 -c pthread_create.c
$(TARGETS): $(DEPS)
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) -shared -fPIC $(SRCS) -o $(TARGETS) $(LIBS)

clean:
	rm -f $(TARGETS)


