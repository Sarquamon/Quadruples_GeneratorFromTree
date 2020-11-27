
arithmetic: lib/Parser.o lib/PostfixEvaluation.o lib/ShuntingYard.o arithmetic.cpp

test: lib/Parser.o lib/PostfixEvaluation.o lib/ShuntingYard.o test.cpp

clean:
	rm -f arithmetic test lib/*.o
