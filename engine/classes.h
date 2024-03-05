#include <vector>

class Camera {
public:
	float pos[3] = {3,2,1};
	float lookAt[3] = {0,0,0};
	float up[3] = { 0,1,0 };
	float projection[3] = { 60,1,1000 };
};

class Group {
public:
	std::vector<float> model;
};

class Window {
public:
	int width = 512;
	int height = 512;
};