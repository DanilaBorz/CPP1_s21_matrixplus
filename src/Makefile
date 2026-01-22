# Определите компилятор и флаги
CC = g++
FLAGS = -Wall -Werror -Wextra -g -std=c++20
LIB_FLAGS = -lgtest -lgcov -lgtest_main -pthread
CODE_FILES = s21_matrix_oop.cpp
TEST_FILES = tests.cpp
OBJ_FILES = $(CODE_FILES:.cpp=.o)
GCOV_FLAGS = --coverage
ifeq ($(OS), Darwin) 	
	TEST_LIBS=$(shell pkg-config --cflags --libs gtest)  
endif 

# Сборка всех компонентов проекта
all: s21_matrix_oop.a main

# Сборка исполняемого файла main
main: $(CODE_FILES) $(TEST_FILES)
	$(CC) $(CODE_FILES) $(TEST_FILES) $(LIB_FLAGS) $(FLAGS) -o main

# Запуск программы main
run: main
	./main

# Проверка стиля кода
style:
	clang-format -n *.cpp *.h
	rm -f .clang-format

# Очистка временных файлов
clean:
	rm -rf report *.a *.o *.gcda *.gcno *.gcov *.info test *.out *.dSYM *.exe main

# Сборка и запуск тестов
test: clean s21_matrix_oop.a
	$(CC) $(TEST_LIBS) $(TEST_FILES) -o test s21_matrix_oop.a $(LIB_FLAGS)
	./test

# Сборка статической библиотеки
s21_matrix_oop.a: $(OBJ_FILES)
	ar rcs s21_matrix_oop.a $(OBJ_FILES)
	ranlib s21_matrix_oop.a

%.o: %.cpp
	$(CC) -c $(FLAGS) $< -o $@

# Генерация отчета покрытия кода с использованием gcov/lcov
gcov_report: clean
	# Компилируем с флагами покрытия
	$(CC) $(GCOV_FLAGS) $(FLAGS) -c $(CODE_FILES)
	$(CC) $(GCOV_FLAGS) $(FLAGS) $(OBJ_FILES) $(TEST_FILES) $(LIB_FLAGS) -o test
	
	# Запускаем тесты
	./test
	
	lcov --capture --directory . --output-file coverage.info --no-external \
	     --exclude "*tests.cpp" --ignore-errors mismatch
	genhtml coverage.info --output-directory report
	rm -f *.gcda *.gcno

# Проверка утечек памяти с помощью Valgrind
valgrind: test
	valgrind --tool=memcheck --leak-check=full ./test