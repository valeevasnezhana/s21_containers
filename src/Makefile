CC = gcc
CFLAGS := -lstdc++ -std=c++17 -Wall -Werror -Wextra

EXECUTABLE = test

SRC_TEST = test.cc


SOURCE = $(SRC_TEST)

UNAME = $(shell uname)

OPEN_REPORT :=
LEAKS :=

ifeq ($(UNAME), Linux)
OPEN_REPORT += xdg-open
LEAKS += valgrind --leak-check=full -s -q --track-origins=yes
endif

ifeq ($(UNAME), Darwin)
OPEN_REPORT += open
LEAKS += leaks -atExit --
endif

all: clean test

clean:
	@rm -rf $(EXECUTABLE)
	@rm -rf a.out
	@rm -rf $(OBJ_LIST_TEST)
	@rm -rf $(OBJ_STACK_TEST)
	@rm -rf *.gcno *.gcda report
	@rm -rf tests.info

test:
	@$(CC) $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

gcov_report: clean test
	lcov -t "Unit-tests" -o s21_container.info -c -d .
	genhtml -o $(REPORTDIR) s21_matrix_oop.info
	open -a "Safari" ./$(REPORTDIR)/index.html


style:
	clang-format -n --style=google s21_containers.h
	clang-format -n --style=google s21_containersplus.h
	clang-format -n --style=google list/*.h
	clang-format -n --style=google stack/*.h
	clang-format -n --style=google queue/*.h
	clang-format -n --style=google tree/*.h
	clang-format -n --style=google map/*.h
	clang-format -n --style=google set/*.h
	clang-format -n --style=google multiset/*.h
	clang-format -n --style=google array/*.h
	clang-format -n --style=google vector/*.h
	clang-format -n --style=google tests/*.cc

clang_format:
	clang-format -i --style=google s21_containers.h
	clang-format -i --style=google s21_containersplus.h
	clang-format -i --style=google list/*.h
	clang-format -i --style=google stack/*.h
	clang-format -i --style=google queue/*.h
	clang-format -i --style=google tree/*.h
	clang-format -i --style=google map/*.h
	clang-format -i --style=google set/*.h
	clang-format -i --style=google multiset/*.h
	clang-format -i --style=google array/*.h
	clang-format -i --style=google vector/*.h
	clang-format -i --style=google tests/*.cc

leaks_check: test
	@$(LEAKS) ./$(EXECUTABLE)


fsanitize_check:
	@$(CC) -fsanitize=address $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)


run:
	./$(EXECUTABLE)

.PHONY: all clean test gcov_report style clang_format leaks_check run