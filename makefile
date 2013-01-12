#WARNINGS = -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Winline -Wuninitialized -Wconversion
WARNINGS = -Wall -Wextra -pedantic -Wshadow -Wwrite-strings -Winline
DEBUG = 
CFLAGS = $(WARNINGS) -std=c++0x
OBJS = $(patsubst src/%.cpp, objs/%.o, $(shell find src -type f -name "*.cpp" ))
EXECNAME = super-rogue
LIBS = -lglfw -lGL -lGLEW

objs/%.o: src/%.cpp src/%.hpp
	@mkdir objs -p
	g++ -c -o $@ $< $(CFLAGS) $(DEBUG)

bin/$(EXECNAME): $(OBJS)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
	@make execute > /dev/null 2>&1

clean:
	-rm -rf objs bin/$(EXECNAME)

execute:
	cd bin && ./$(EXECNAME)