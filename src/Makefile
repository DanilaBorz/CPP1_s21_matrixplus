FLAGS = -Wall -Werror -Wextra -g -std=c++20
LIB_FLAGS = -lgtest 
CODE_FILES = s21_matrix_oop.cpp
TEST_FILES = tests.cpp

all: clean 
	g++ $(CODE_FILES) $(TEST_FILES) $(LIB_FLAGS) $(FLAGS) -o main
	./main

style:
	clang-format -n *.cpp *.h
	rm -f .clang-format

checks: style
	g++ $(FLAGS) $(CODE_FILES) $(TEST_FILES) $(LIB_FLAGS) -o check

clean:
	rm -rf report *.a *.o *.gcda *.gcno *.gcov *.info test *.out *.dSYM *.exe main check

test: clean s21_matrix_oop.a
	g++ $(TEST_FILES) -o test s21_matrix_oop.a $(LIB_FLAGS)
	./test

s21_matrix_oop.a: clean
	g++ -c $(CODE_FILES) $(FLAGS)
	ar rcs s21_matrix_oop.a s21_*.o
	ranlib s21_matrix_oop.a
	rm -f *.o

gcov_report: clean
	g++ --coverage $(FLAGS) $(CODE_FILES) $(TEST_FILES) $(LIB_FLAGS) -o test
	./test
	lcov --capture --directory . --output-file coverage.info --no-external --ignore-errors mismatch > /dev/null 2>&1
	genhtml coverage.info --output-directory report

valgrind: test
	valgrind --tool=memcheck --leak-check=full ./test