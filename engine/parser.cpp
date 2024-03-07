#include "parser.h"
#include "classes.h"

void parse_window(xml_node<>* window_node, Window* window) {
	xml_attribute<>* width = window_node->first_attribute("width");
	xml_attribute<>* height = window_node->first_attribute("height");
	if (width) {
		window->width = atoi(width->value());
	}
	if (height) {
		window->height = atoi(height->value());
	}
}

void parse_camera(xml_node<>* camera_node, Camera* camera) {
	xml_node<>* node;
	xml_attribute<>* p1, * p2, * p3, * l1, * l2, * l3, * u1, * u2, * u3, * pro1, * pro2, * pro3;

	xml_node<>* pos = camera_node->first_node("position");
	xml_node<>* lookat = camera_node->first_node("lookAt");
	xml_node<>* up = camera_node->first_node("up");
	xml_node<>* projection = camera_node->first_node("projection");

	if (pos) {
		if (node = camera_node->first_node("position")) {
			if (p1 = node->first_attribute("x")) {
				camera->pos[0] = atof(p1->value());
			}
			if (p2 = node->first_attribute("y")) {
				camera->pos[1] = atof(p2->value());
			}
			if (p3 = node->first_attribute("z")) {
				camera->pos[2] = atof(p3->value());
			}
		}
	}

	if (lookat) {
		if (node = camera_node->first_node("lookat")) {
			if (l1 = node->first_attribute("x")) {
				camera->lookAt[0] = atof(l1->value());
			}
			if (l2 = node->first_attribute("y")) {
				camera->lookAt[1] = atof(l2->value());
			}
			if (l3 = node->first_attribute("z")) {
				camera->lookAt[2] = atof(l3->value());
			}
		}
	}

	if (up) {
		if (node = camera_node->first_node("up")) {
			if (u1 = node->first_attribute("x")) {
				camera->up[0] = atof(u1->value());
			}
			if (u2 = node->first_attribute("y")) {
				camera->up[1] = atof(u2->value());
			}
			if (u3 = node->first_attribute("z")) {
				camera->up[2] = atof(u3->value());
			}
		}
	}

	if (projection) {
		if (node = camera_node->first_node("projection")) {
			if (pro1 = node->first_attribute("fov")) {
				camera->projection[0] = atof(pro1->value());
			}
			if (pro3 = node->first_attribute("near")) {
				camera->projection[1] = atof(pro3->value());
			}
			if (pro3 = node->first_attribute("far")) {
				camera->projection[2] = atof(pro3->value());
			}
		}
	}
}

void parse_group(xml_node<>* group_node, Group* group, vector<float>* points) {
	xml_node<>* models = group_node->first_node("models");

	if (models) {
		for(xml_node<>* model = models->first_node("model"); model; model = model->next_sibling()) {

			//Get file name and open it
			char* file = model->first_attribute("file")->value();
			ifstream fich;
			fich.open(file, ios::in | ios::binary);

			if (!fich) {
				std::cout << "Error opening file " << endl;
				exit(1);
			}

			char line[20];

			fich.getline(line, 20); // skip first line

			while (fich.getline(line, 20)) {
				points->push_back(atof(line));
			}

			group->model.push_back(points->size());

			fich.close();
		}
	}
}

void parser(char* fileName, Window* window, Camera* camera, Group* group, vector<float>* points) {
	xml_document<> doc;
	xml_node<>* root_node;

	ifstream theFile(fileName);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	root_node = doc.first_node("world");

	//Parse window
	xml_node<>* window_node = root_node->first_node("window");
	parse_window(window_node, window);

	//Parse camera
	xml_node<>* camera_node = root_node->first_node("camera");
	parse_camera(camera_node, camera);

	//Parse group
	xml_node<>* group_node = root_node->first_node("group");
	parse_group(group_node, group, points);
}