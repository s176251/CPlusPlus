#ifndef CLASS_CLOUD_H
#define CLASS_CLOUD_H

//Local includes
#include "class_is_vector.h"
#include "class_has_color.h"
#include "class_animated.h"
#include "class_circle.h"

class cloud : public animated, has_color, is_vector
{
	bool done;
	int x_max;
	int y_max;
	int itr;
	int itr_before_turn;
	std::vector<circle*> clouds;
	void draw() override;
  
	public:
		cloud(int _x_max, int _y_max, int r);
		void clear() override;
		void operator++() override;
		void reset() override;
		~cloud() override;
};

#endif
