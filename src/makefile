WARNINGS = -Wall
DEBUG = 
CFLAGS = $(WARNINGS) -std=c++0x -I/usr/local/include -L/usr/local/lib
OBJS = $(patsubst ./%.cpp, ../objs/%.o, $(shell find . -type f -name "*.cpp" ))
EXECNAME = super-rogue
LIBS = -lSDL_ttf -lSDL_image -lSDL

../objs/%.o: ./%.cpp
	@mkdir ../objs -p
	g++ -c -o $@ $< $(CFLAGS) $(DEBUG)

../$(EXECNAME): $(OBJS)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
	cd .. && ./super-rogue

clean:
	-rm -rf ../objs ../$(EXECNAME)
