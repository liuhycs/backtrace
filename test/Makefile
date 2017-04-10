all:
	gcc -O0 -g -I../src -o test test.c -rdynamic ../src/libbacktrace.so -ldl

run:
	export HPCRUN_FNBOUNDS_CMD="/home/hongyuliu/workspace/hpctoolkitbin/hpctoolkit-dist/libexec/hpctoolkit/hpcfnbounds"
	./test

clean:
	rm -rf test

