#This is a Makefile
CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99
SANI := -fsanitize=undefined -fsanitize=address
NLBS := $(wildcard *.nlb)
RESULTS := $(NLBS:.nlb=.result)

all: parse parse_s parse_v interp interp_s interp_v

interp: nlab.c nlab.h
	$(CC) nlab.c $(CFLAGS) -O2 -DINTERP -o interp -lm

interp_s: nlab.c nlab.h
	$(CC) nlab.c $(CFLAGS) $(SANI) -g3 -DINTERP -o interp_s -lm

interp_v: nlab.c nlab.h
	$(CC) nlab.c $(CFLAGS) -g3 -DINTERP -o interp_v -lm

parse: nlab.c nlab.h
	$(CC) nlab.c $(CFLAGS) -O2 -o parse -lm
parse_s: nlab.c nlab.h
	$(CC) nlab.c $(CFLAGS) $(SANI) -g3 -o parse_s -lm
parse_v: nlab.c nlab.h
	$(CC) nlab.c $(CFLAGS) -g3 -o parse_v -lm

runall: $(RESULTS)

%.result:
	./interp $*.nlb > $*.result

clean:
	rm -f parse parse_v parse_s interp interp_s interp_v $(RESULTS)