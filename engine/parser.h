#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "rapidxml.hpp"
#include <vector>
#include <IL/il.h>
#include "classes.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


using namespace std;
using namespace rapidxml;

void parse_window(xml_node<>* window_node, Window* window);
void parse_camera(xml_node<>* camera_node, Camera* camera);
void parse_group(xml_node<>* group_node, Group* group, vector<float>* points,vector<float>* normals, vector<float>* textures);
void parse_lights(xml_node<>* lights_node, vector<Lights*>* lights);

void parser(char* fileName,vector<Lights*>* lights, Window* window, Camera* camera, 
	Group* group, vector<float>* points, vector<float>* normals, vector<float>* textures);