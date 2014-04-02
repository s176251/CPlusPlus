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


class_custom.o: class_custom.cpp class_cloud.h class_sun.h class_circle.h class_square.h class_animation_canvas.h 
	$(CC) $(CFLAGS) class_custom.cpp

custom: class_custom.o class_circle.o class_has_color.o class_animation_canvas.o class_square.o class_sun.o class_cloud.o 
	$(CC) class_custom.o class_cloud.o class_circle.o class_square.o class_has_color.o class_animation_canvas.o class_sun.o $(LFLAGS) -o custom
	
	
class_cloud.o: class_cloud.cpp class_cloud.h class_circle.h
	$(CC) $(CFLAGS) class_cloud.cpp
	
class_sun.o: class_sun.cpp class_sun.h class_circle.h
	$(CC) $(CFLAGS) $(LFLAGS) class_sun.cpp
	
class_circle.o: class_circle.cpp class_circle.h
	$(CC) $(CFLAGS) $(LFLAGS) class_circle.cpp
	
class_square.o: class_square.cpp class_square.h
	$(CC) $(CFLAGS) class_square.cpp