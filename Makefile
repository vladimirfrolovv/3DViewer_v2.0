CC = g++ -std=c++17 -g
CFLAGS = -Wall -Werror -Wextra
TESTSFLAGS_MAC = -lgtest -lgtest_main

UNAME = $(shell uname)

OPEN :=

ifeq ($(UNAME), Linux)
	OPEN += xdg-open
endif

ifeq ($(UNAME), Darwin)
	OPEN += open
endif

all: install

clang-format:
	clang-format -style=google -i tests/*.cc Model/*.cc Model/*.h Controller/*.cc Controller/*.h View/*.cc View/*.h *.cc *.h

style:
	clang-format -style=google -n tests/*.cc Model/*.cc Model/*.h Controller/*.cc Controller/*.h View/*.cc View/*.h *.cc *.h

dvi:
	doxygen
	@$(OPEN) html/index.html

install:
	@mkdir Qmake
	@cd Qmake/ && qmake ../Viewer.pro && make

open:
	@$(OPEN) Qmake/Viewer.app/Contents/MacOS/./Viewer

uninstall:
	@rm -rf Viewer.app
	@rm -rf Qmake

dist:
	mkdir Viewer
	@cp -r Model/*.cc Model/*.h Controller/*.cc Controller/*.h View/*.cc View/*.h *.cc *.h View/*.ui *.pro Makefile tests/ Doxyfile Viewer
	tar -cvzf dist.tar.gz Viewer
	@-rm -rf Viewer

SOURCE = ./Model/*.cc ./Controller/*.cc

tests:
	$(CC) $(CFLAGS) tests/tests_model.cc $(SOURCE) $(TESTSFLAGS_MAC) -o test
	@./test

clean:
	@rm -rf *.o test *.a *.gcno *.gcda *.gcov *.html *.css *.out *.info report Qmake html dist.tar.gz Viewer test.dSYM

rebuild: clean all

.PHONY: tests clang-format
