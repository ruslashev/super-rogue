#WARNINGS = -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Winline -Wuninitialized -Wconversion
WARNINGS = -Wall -Wextra -pedantic -Wshadow -Wwrite-strings -Winline
DEBUG = 
CFLAGS = $(WARNINGS) -std=c++0x
OBJS = $(patsubst %.cpp, objs/%.o, $(shell find . -type f -name "*.cpp"))
EXECNAME = super-rogue
LIBS = -lglfw -lGL -lGLEW

objs/%.o: %.cpp %.hpp
	@mkdir objs -p
	g++ -c -o $@ $< $(CFLAGS) $(DEBUG)

$(EXECNAME): $(OBJS)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
	@make execute > /dev/null 2>&1

clean:
	-rm -rf objs $(EXECNAME)

execute:
	./$(EXECNAME)