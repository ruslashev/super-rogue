CXX = clang++

OBJS = obj/renderer.o obj/utils.o obj/main.o obj/player.o obj/world.o obj/input.o

EXECNAME = super-rogue

default: objdir $(EXECNAME)
	./$(EXECNAME)

$(EXECNAME): $(OBJS)
	$(CXX) -o $@ $^ -lSDL2 -lSDL2_image

obj/%.o: source/%.cpp
	$(CXX) -c -o $@ $< -Wall -Wextra -g -std=c++0x

objdir:
	mkdir -p obj

clean:
	-rm -f $(OBJS) $(EXECNAME)

