# make the base classes

DEBUG = -g
TEST = -D TEST
OPTFLAGS = -D INLINE_PAIR
# $(DEBUG) -D INLINE_PAIR
EFFCPP = -Weffc++
AWARN = $(EFFCPP) -Waggregate-return -Wpadded -Wlarger-than-12
WARN = -W -Wall -ansi -pedantic -Wpointer-arith -Wcast-qual		\
-Wcast-align -Woverloaded-virtual -Wno-multichar -Wredundant-decls	\
-Wfloat-equal $(AWARN)

CXX = g++
CXXFLAGS = $(DEBUG) $(OPTFLAGS)

OPTSRC = sizeof.cpp
SRC =   						\
	assert.cpp							\
	priority.cpp input.cpp				\
	sprite.cpp image_file.cpp animation.cpp				\
	image.cpp graphics.cpp image_file_manager.cpp			\
	pair.cpp rectangle.cpp image_manager.cpp animating_sprite.cpp   \
	$(OPTSRC) ltimer.cpp

OBJ = $(SRC:.cpp=.o)
LIBS = -L/usr/lib/ -lSDL
INCL = -I/usr/include/

all: test test2

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCL)

test: $(OBJ) test.o
	$(CXX) $(CXXFLAGS) $(OBJ) test.o -o $@ $(LIBS) $(INCL) 

test2: $(OBJ) test2.o
	$(CXX) $(CXXFLAGS) $(OBJ) test2.o -o $@ $(LIBS) $(INCL) 

depend:
	makedepend -Y $(SRC)

clean:
	\rm $(OBJ) *~ test.exe src.tar

tar:
	tar cvf src.tar $(SRC)


#notes
#-Wstrict-prototypes -Wtraditional
#MAIN = test.cpp
#PROG = ${MAIN:.cpp=}
#OBJS = ${FILES:.cpp=.o}

# DO NOT DELETE

assert.o: assert.hpp
priority.o: priority.hpp
input.o: input.hpp
sprite.o: sprite.hpp unit.hpp priority.hpp pair.hpp rectangle.hpp image.hpp
sprite.o: image_file_manager.hpp extension.hpp assert.hpp graphics.hpp
sprite.o: animating_sprite.hpp
image_file.o: image_file.hpp extension.hpp image_file_manager.hpp
image_file.o: graphics.hpp rectangle.hpp pair.hpp unit.hpp
image_file.o: animating_sprite.hpp priority.hpp assert.hpp
animation.o: animation.hpp assert.hpp image.hpp rectangle.hpp pair.hpp
animation.o: unit.hpp image_manager.hpp
image.o: image.hpp rectangle.hpp pair.hpp unit.hpp graphics.hpp
image.o: animating_sprite.hpp priority.hpp image_file_manager.hpp
image.o: extension.hpp image_file.hpp assert.hpp
graphics.o: graphics.hpp rectangle.hpp pair.hpp unit.hpp animating_sprite.hpp
graphics.o: priority.hpp assert.hpp image_file_manager.hpp extension.hpp
graphics.o: image.hpp sprite.hpp
image_file_manager.o: image_file_manager.hpp extension.hpp image_file.hpp
image_file_manager.o: assert.hpp debug.hpp
pair.o: pair.hpp unit.hpp assert.hpp debug.hpp
rectangle.o: rectangle.hpp pair.hpp unit.hpp assert.hpp debug.hpp
image_manager.o: image_manager.hpp assert.hpp image.hpp rectangle.hpp
image_manager.o: pair.hpp unit.hpp debug.hpp
animating_sprite.o: animating_sprite.hpp priority.hpp pair.hpp unit.hpp
animating_sprite.o: image.hpp rectangle.hpp image_file_manager.hpp
animating_sprite.o: extension.hpp assert.hpp graphics.hpp animation.hpp
sizeof.o: sizeof.hpp animating_sprite.hpp priority.hpp pair.hpp unit.hpp
sizeof.o: animation.hpp assert.hpp ctimer.hpp timer.hpp direction.hpp
sizeof.o: extension.hpp graphics.hpp rectangle.hpp image.hpp image_file.hpp
sizeof.o: image_file_manager.hpp image_manager.hpp input.hpp sprite.hpp
ltimer.o: timer.hpp assert.hpp debug.hpp
