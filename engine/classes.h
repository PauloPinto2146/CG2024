#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#ifndef CLASSES_H
#define CLASSES_H
class Camera {
public:
    float pos[3] = { 3, 2, 1 };
    float lookAt[3] = { 0, 0, 0 };
    float up[3] = { 0, 1, 0 };
    float projection[3] = { 60, 1, 1000 };
    float rotate[3] = { 0, 0 ,0 };
    float zoom = 1.0f;
};


class Color {
public:
    float diffuseR = 0.78;
    float diffuseG = 0.78;
    float diffuseB = 0.78;
    float ambientR = 0.2;
    float ambientG = 0.2;
    float ambientB = 0.2;
    float specularR = 0.0;
    float specularG = 0.0;
    float specularB = 0.0;
    float emissiveR = 0.0;
    float emissiveG = 0.0;
    float emissiveB = 0.0;
    float shininessValue = 0.0;
};

class Group {
public:
    std::vector<float> model;
    std::vector<int> torder;
    std::vector<Color*> color;
    std::vector<GLuint> textures;

    float tx = 0.0;
    float ty = 0.0;
    float tz = 0.0;
    float ralpha = 0.0;
    float rx = 0.0;
    float ry = 0.0;
    float rz = 0.0;
    float timerx = 0.0;
    float timery = 0.0;
    float timerz = 0.0;
    float sx = 1.0;
    float sy = 1.0;
    float sz = 1.0;

    float tesselation = 0.0;
    int align = 0;
    std::vector<float*> catPoints;
    std::vector<Group*> groups;
};

class Lights {
public:
    int type = 0; // 1 - point // 2 - directional // 3 - spotlight
    float posX = 0.0;
    float posY = 0.0;
    float posZ = 0.0;
    float dirX = 0.0;
    float dirY = 0.0;
    float dirZ = 0.0;
    float cutoff = 0.0;
};

class Window {
public:
    int width = 512;
    int height = 512;
};
#endif
