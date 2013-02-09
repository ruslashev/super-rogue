WARNINGS = -Wall
DEBUG = 
CFLAGS = -std=c++0x -I/usr/local/include
OBJS = $(patsubst ./%.cpp, ../objs/%.o, $(shell find . -type f -name "*.cpp" ))
EXECNAME = super-rogue
LIBS = -lglfw -lGLEW -lGL

../objs/%.o: ./%.cpp ./%.hpp
	@mkdir ../objs -p
	g++ -c -o $@ $< $(WARNINGS) $(CFLAGS) $(DEBUG)

../$(EXECNAME): $(OBJS)
	g++ -o $@ $^ $(WARNINGS) $(CFLAGS) $(LIBS)
	cd .. && ./super-rogue

clean:
	-rm -rf ../objs ../$(EXECNAME)
