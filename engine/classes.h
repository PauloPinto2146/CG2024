#include <vector>

#ifndef CAMERA_H
#define CAMERA_H
class Camera {
    public:
        float pos[3] = { 3, 2, 1};
        float lookAt[3] = { 0, 0, 0 };
        float up[3] = { 0, 1, 0 };
        float projection[3] = { 60, 1, 1000 };
        float rotate[3] = { 0, 0, 0 };
        float zoom = 1;
};
#endif

#ifndef GROUP_H
#define GROUP_H
class Group {
    public:
        std::vector<float> model;
};
#endif

#ifndef WINDOW_H
#define WINDOW_H
class Window {
    public:
        int width = 512;
        int height = 512;
};
#endif
