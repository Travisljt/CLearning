CC := clang
CWARNS := -Wall -Wpedantic -Wextra -Wfloat-equal -Wvla
CFLAGNOABORT := $(CWARNS) -std=c99 -O3
CFLAGS := $(CFLAGNOABORT) -Werror
LDLIBS := -lm
SOURCES := $(wildcard *.c)
EXES := $(SOURCES:.c=)
GENC := General/general.c
STACK := Stack/stack.c
PARSER := Parser/parser.c
INTERPRETER := Interpreter/interpreter.c
RESULTS := $(NLBS:.nlb=.result)
NLBS := $(wildcard ./testfiles/*.nlb)


parse: $(PARSER)
	$(CC) $(CFLAGS) -DPARSER $< main.c -Iinclude $(LDLIBS) -o $@

interp: $(INTERPRETER)
	$(CC) $(CFLAGS) $< main.c $(GENC) $(STACK) -Iinclude $(LDLIBS) -o $@

test_parse:
	./parse ./testfiles/trivial.nlb
	./parse ./testfiles/setprinta.nlb
	./parse ./testfiles/setprintb.nlb
	./parse ./testfiles/setprintc.nlb
	./parse ./testfiles/loopa.nlb
	./parse ./testfiles/loopb.nlb
	./parse ./testfiles/nestedloop.nlb
	./parse ./testfiles/onesprint.nlb
	./parse ./testfiles/lifeb3s23.nlb


test_interp:
	./interp ./testfiles/trivial.nlb
	./interp ./testfiles/setprinta.nlb
	./interp ./testfiles/setprintb.nlb
	./interp ./testfiles/setprintc.nlb
	./interp ./testfiles/loopa.nlb
	./interp ./testfiles/loopb.nlb
	./interp ./testfiles/nestedloop.nlb
	./interp ./testfiles/onesprint.nlb
	./interp ./testfiles/lifeb3s23.nlb

runall: $(RESULTS)

runtest: interp $(RESULTS)

%.result:
	./interp ./testfiles/$*.nlb > $*.result

clean:
	rm -f parse interp $(RESULTS)

