#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "rapidxml.hpp"
#include <vector>
#include "classes.h"

using namespace std;
using namespace rapidxml;

void parse_window(xml_node<>* window_node, Window* window);
void parse_camera(xml_node<>* camera_node, Camera* camera);
void parse_group(xml_node<>* group_node, Group* group, vector<float>* points);
void parse_lights(xml_node<>* lights_node, Lights* lights);

void parser(char* fileName, Window* window, Camera* camera, Group* group, vector<float>* points);