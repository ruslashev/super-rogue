#WARNINGS = -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Winline -Wuninitialized -Wconversion
WARNINGS = -Wall -Wextra -pedantic -Wshadow -Wwrite-strings -Winline
DEBUG = 
DEBUGGER = 
CFLAGS = $(WARNINGS) -std=c++0x
OBJS = $(patsubst src/%.cpp, objs/%.o, $(shell find src -type f -name "*.cpp" ))
EXECNAME = super-rogue
LIBS = -lglfw -lGL -lGLEW

objs/%.o: src/%.cpp src/%.hpp
	@mkdir objs -p
	g++ -c -o $@ $< $(CFLAGS) $(DEBUG)

bin/$(EXECNAME): $(OBJS)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	-rm -rf objs bin/$(EXECNAME)

execute:
	cd bin && $(DEBUGGER) ./$(EXECNAME)