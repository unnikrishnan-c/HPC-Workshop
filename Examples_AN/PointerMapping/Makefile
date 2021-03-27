EXEFILES:=$(shell grep 'int main' -lr . | sed 's/\.c/\.out/g')

all: $(EXEFILES)

%.out: %.c Misc.c
	-gcc-10 -fno-lto -fopenmp -foffload=nvptx-none -fstack-protector  $^ -o $@ -lm
	@echo "-----------------------------------------------------\n"
.PHONY: clean
clean:
	-rm -rf *.o *.out


