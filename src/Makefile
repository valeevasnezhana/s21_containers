CC=g++ -std=c++20 -pedantic -Wall -Werror -Wextra -pedantic
CHECKFLAGS=-lgtest -pedantic-errors -pthread
REPORTDIR=gcov_report
GCOV=--coverage
OS = $(shell uname)

all: test

s21_matrix_oop.a:
	$(CC) -c s21_matrix_oop.cc -o matrix_oop.o
	ar rcs s21_matrix_oop.a matrix_oop.o

test: clean
	$(CC) $(GCOV) -c s21_matrix_oop.cc
	$(CC) -c test.cc $(CHECKFLAGS)
	$(CC) $(GCOV) -o matrix_test test.o s21_matrix_oop.o $(CHECKFLAGS)
	./matrix_test

gcov_report: test
	lcov -t "Unit-tests" -o s21_matrix_oop.info -c -d .
	genhtml -o $(REPORTDIR) s21_matrix_oop.info
	open -a "Safari" ./$(REPORTDIR)/index.html

clean:
	rm -rf ./*.o ./*.a ./a.out ./*.gcno ./*.gcda ./$(REPORTDIR) *.info ./*.info report matrix_test matrix_oop
