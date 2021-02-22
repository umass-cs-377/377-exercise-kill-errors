CXX=g++
CXXFLAGS += -g -Wall -Wextra -pthread
CPPFLAGS += -isystem src -std=c++11

MKDIR_P = mkdir -p
OBJ_DIR = obj

all: duality kill word pointer

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

obj/%.o: %.cpp ${OBJ_DIR}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

duality: obj/duality.o
	$(CXX) -o $@ $^

kill: obj/kill.o
	$(CXX) -o $@ $^

word: obj/word.o
	$(CXX) -o $@ $^

pointer: obj/pointer.o
	$(CXX) -o $@ $^

clean:
	rm -f *~ obj/*.o *.zip
	rm -f duality kill word pointer
