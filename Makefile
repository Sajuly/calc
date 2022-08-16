.PHONY: all test s21_SmartCalc.a check rebuild open gcov_report install uninstall dist clean
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
# LINUX=-lsubunit -lrt -lpthread -lm

LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
OBJ=$(patsubst %.c, %.o, $(SRC))  # добавляет для всех файлов .с файлы .о
MKF = makefile.qt # создаю файл чтоб читался как makefile для install

FLAGS_TEST_LIBS = -lcheck -lm -lpthread
NAME=s21_calc.a
SRC = parser.c rpn_executor.c simple_list.c simple_stack.c

all: build static tests

build:
	$(CC) $(CFLAGS) -c $(SRC)

static:
	@ar rc s21_calc.a $(OBJ)
	@ranlib s21_calc.a

tests: static
	$(CC) $(CFLAGS) -lcheck test.c s21_calc.a -o test
	./test

gcov_report: all
	$(CC) $(CFLAGS) --coverage test.c $(SRC) $(NAME) $(FLAGS_TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html


install:
	make clean
	mkdir build
	qmake -o $(MKF) && make -f $(MKF) && make clean -f $(MKF) && rm $(MKF) && mv supercalc.app build  

uninstall:
	rm -rf build*

dvi:
	open readme.md

dist:
	rm -rf Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/src
	mv ./build/Qt.app Archive_calc_v1.0/src/
	tar cvzf Archive_calc_v1.0.tgz Archive_calc_v1.0/
	rm -rf Archive_calc_v1.0/

clean:
	@rm -rf $(EXECUTABLE)
	@rm -rf *.{a,o,dSYM,out}
	@rm -rf gcov_report
	@rm -rf report
	@rm -rf CPPLINT.cfg
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf test
	@rm -rf Archive_calc_v1.0 
	@rm -rf *tgz
	@rm -rf build
	@rm -rf gcov_test

rebuild: clean all

check:
	cp ../../materials/linters/CPPLINT.cfg .
	python3 ../../materials/linters/cpplint.py --extensions=c *.c
	python3 ../../materials/linters/cpplint.py --extensions=c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	leaks --atExit -- test