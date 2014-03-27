OBJS = class_fireworks.o class_dot.o class_has_color.o class_animation_canvas.o
CC = g++
CFLAGS = -std=c++11 -c
LFLAGS = -L/usr/local/lib -lfltk -lm

all: fireworks

fireworks: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o fireworks
	
class_fireworks.o: class_fireworks.cpp class_fireworks.h class_dot.h class_animation_canvas.h
	$(CC) $(CFLAGS) class_fireworks.cpp
	
class_animation_canvas.o: class_animation_canvas.cpp class_animation_canvas.h class_dot.h
	$(CC) $(CFLAGS) $(LFLAGS) class_animation_canvas.cpp
	
class_dot.o: class_dot.cpp class_dot.h
	$(CC) $(CFLAGS) class_dot.cpp
	
class_has_color.o: class_has_color.cpp class_has_color.h
	$(CC) $(CFLAGS) $(LFLAGS) class_has_color.cpp

clean:
	\rm *.o fireworks