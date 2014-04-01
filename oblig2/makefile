OBJS = class_fireworks.o class_dot.o class_has_color.o class_animation_canvas.o class_rocket.o
CC = g++
CFLAGS = -std=c++11 -c
LFLAGS = -L/usr/local/lib -lfltk -lm

all: custom fireworks

fireworks: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o fireworks
		
class_fireworks.o: class_fireworks.cpp class_fireworks.h class_rocket.h class_dot.h class_animation_canvas.h 
	$(CC) $(CFLAGS) class_fireworks.cpp
	
class_animation_canvas.o: class_animation_canvas.cpp class_animation_canvas.h class_dot.h
	$(CC) $(CFLAGS) $(LFLAGS) class_animation_canvas.cpp
	
class_rocket.o: class_rocket.cpp class_rocket.h class_dot.h
	$(CC) $(CFLAGS) $(LFLAGS) class_rocket.cpp
	
class_dot.o: class_dot.cpp class_dot.h
	$(CC) $(CFLAGS) class_dot.cpp
	
class_has_color.o: class_has_color.cpp class_has_color.h
	$(CC) $(CFLAGS) $(LFLAGS) class_has_color.cpp

clean:
	\rm *.o fireworks custom


class_custom.o: class_custom.cpp class_rocket.h class_dot.h class_animation_canvas.h 
	$(CC) $(CFLAGS) class_custom.cpp

custom: class_custom.o class_dot.o class_has_color.o class_animation_canvas.o class_rocket.o
	$(CC) class_custom.o class_dot.o class_has_color.o class_animation_canvas.o class_rocket.o $(LFLAGS) -o custom