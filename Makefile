CXX      = clang++
CXXFLAGS = -std=c++11 -g -o2 -Wall -Wextra
LDFLAGS  = -o2 -g

gerp: main.o Index.o DirNode.o FSTree.o 
	${CXX} ${LDFLAGS} -o gerp main.o Index.o DirNode.o FSTree.o

test: testmain.o Index.o DirNode.o FSTree.o 
	${CXX} ${LDFLAGS} -o gerp testmain.o Index.o DirNode.o FSTree.o

main.o: main.cpp Index.h 
Index.o : Index.cpp Index.h 
DirNode.o: DirNode.h
FSTree.o: FSTree.h

clean:
	rm -rf gerp *Index.o *.dSYM

provide:
	provide comp15 proj1 main.cpp README Makefile

