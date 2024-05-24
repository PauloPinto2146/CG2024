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
		if (node = camera_node->first_node("lookAt")) {
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

void parse_lights(xml_node<>* lights_node, vector <Lights*>* lights) {
	xml_attribute<>* type;
	xml_attribute<>* posX;
	xml_attribute<>* posY;
	xml_attribute<>* posZ;
	xml_attribute<>* dirX;
	xml_attribute<>* dirY;
	xml_attribute<>* dirZ;
	xml_attribute<>* cutoff;
	if (lights_node->first_node("light")) {
		for (xml_node<>* node = lights_node->first_node("light"); node; node = node->next_sibling()) {
			Lights* light = new Lights();
			if (node->first_attribute("light")) {
				if (strcmp(node->first_attribute("type")->value(), "point") == 0) {
					light->type = 1;
					light->posX = atof(node->first_attribute("posX")->value());
					light->posY = atof(node->first_attribute("posY")->value());
					light->posZ = atof(node->first_attribute("posZ")->value());
				}
				if (strcmp(node->first_attribute("type")->value(), "directional") == 0) {
					light->type = 2;
					light->dirX = atof(node->first_attribute("dirX")->value());
					light->dirY = atof(node->first_attribute("dirY")->value());
					light->dirZ = atof(node->first_attribute("dirZ")->value());
				}
				if (strcmp(node->first_attribute("type")->value(), "spotlight") == 0) {
					light->type = 3;
					light->posX = atof(node->first_attribute("posX")->value());
					light->posY = atof(node->first_attribute("posY")->value());
					light->posZ = atof(node->first_attribute("posZ")->value());
					light->dirX = atof(node->first_attribute("dirX")->value());
					light->dirY = atof(node->first_attribute("dirY")->value());
					light->dirZ = atof(node->first_attribute("dirZ")->value());
					light->cutoff = atof(node->first_attribute("cutoff")->value());
				}
			}
			lights->push_back(light);
		}
	}
}


void parse_group(xml_node<>* group_node, Group* group, vector<float>* points) {
	xml_node<>* models = group_node->first_node("models");
	xml_node<>* transform = group_node->first_node("transform");
	xml_node<>* texture = group_node->first_node("texture");

	if (models) {
		for (xml_node<>* model = models->first_node("model"); model; model = model->next_sibling()) {
			Color* color = new Color();
			xml_node <>* diffuseNode;
			xml_node <>* ambientNode;
			xml_node <>* specularNode;
			xml_node <>* emissiveNode;
			xml_node <>* shininessNode;
			xml_node <>* rgbNode;
			xml_node <>* color_node;
			if (color_node = model->first_node("color")) {
				if (diffuseNode = color_node->first_node("diffuse")) {
					color->diffuseR = atof(diffuseNode->first_attribute("R")->value()) / 255;
					cout << atof(diffuseNode->first_attribute("R")->value()) / 255<<"\n";
					color->diffuseG = atof(diffuseNode->first_attribute("G")->value()) / 255;
					cout << atof(diffuseNode->first_attribute("G")->value()) / 255 << "\n";
					color->diffuseB = atof(diffuseNode->first_attribute("B")->value()) / 255;
					cout << atof(diffuseNode->first_attribute("B")->value()) / 255 << "\n";
				}
				if (ambientNode = color_node->first_node("ambient")) {
					color->ambientR = atof(ambientNode->first_attribute("R")->value()) / 255;
					color->ambientG = atof(ambientNode->first_attribute("G")->value()) / 255;
					color->ambientB = atof(ambientNode->first_attribute("B")->value()) / 255;
				}
				if (specularNode = color_node->first_node("specular")) {
					color->specularR = atof(specularNode->first_attribute("R")->value()) / 255;
					color->specularG = atof(specularNode->first_attribute("G")->value()) / 255;
					color->specularB = atof(specularNode->first_attribute("B")->value()) / 255;
				}
				if (emissiveNode = color_node->first_node("emissive")) {
					color->emissiveR = atof(emissiveNode->first_attribute("R")->value()) / 255;
					color->emissiveG = atof(emissiveNode->first_attribute("G")->value()) / 255;
					color->emissiveB = atof(emissiveNode->first_attribute("B")->value()) / 255;
				}
				if (shininessNode = color_node->first_node("shininess")) {
					color->shininessValue = atof(shininessNode->first_attribute("value")->value());
				}
				group->color.push_back(color);
			}
			//Get file name and open it
			char* file = model->first_attribute("file")->value();
			ifstream fich;
			fich.open(file, ios::in | ios::binary);

			if (!fich) {
				std::cout << "Error opening file " << endl;
				exit(1);
			}

			int n;
			fich.read((char*)&n, sizeof(int));

			float* temp_points = (float*)malloc(n * sizeof(float));
			fich.read((char*)temp_points, n * sizeof(float));

			points->insert(points->end(), temp_points, temp_points + n);
			group->model.push_back(n);

			fich.close();
		}
		/*
		for (xml_node<>* texture = models->first_node("texture"); texture; texture = texture ->next_sibling()) {

			//Get texturefile name and open it
			char* texturefile = texture->first_attribute("file")->value();
			ifstream fich;
			fich.open(texturefile, ios::in | ios::binary);

			if (!fich) {
				std::cout << "Error opening texture file " << endl;
				exit(1);
			}

			int n;
			fich.read((char*)&n, sizeof(int));

			float* temp_points = (float*)malloc(n * sizeof(float));
			fich.read((char*)temp_points, n * sizeof(float));

			points->insert(points->end(), temp_points, temp_points + n);
			group->texture.push_back(n);

			fich.close();
		}*/

	}

	if (transform) {
		for (xml_node<>* node = transform->first_node(); node; node = node->next_sibling()) {
			int code = 2;

			if (strcmp(node->name(), "translate") == 0) {
				if (node->first_attribute("time"))
					code = 3;
				else
					code = 0;
			}
			else if (strcmp(node->name(), "rotate") == 0) {
				if (node->first_attribute("time"))
					code = 4;
				else
					code = 1;
			}
			else if (strcmp(node->name(), "scale") == 0) {
				code = 2;
			}

			group->torder.push_back(code);
		}

		xml_node<>* translate = transform->first_node("translate");
		xml_node<>* rotate = transform->first_node("rotate");
		xml_node<>* scale = transform->first_node("scale");
		xml_node<>* pointNode;

		xml_attribute<>* translatex;
		xml_attribute<>* translatey;
		xml_attribute<>* translatez;
		xml_attribute<>* tesselation;
		xml_attribute<>* align;

		xml_attribute<>* rotatealpha;
		xml_attribute<>* rotatex;
		xml_attribute<>* rotatey;
		xml_attribute<>* rotatez;

		xml_attribute<>* scalex;
		xml_attribute<>* scaley;
		xml_attribute<>* scalez;

		if (translate) {
			if (translate->first_attribute("time")) {
				if(tesselation = translate->first_attribute("time")) {
					group->tesselation = atof(tesselation->value());
				}
				if(strcmp(translate->first_attribute("align")->value(),"True") == 0) {
					group->align = 1;
				}
				else {
					group->align = 0;
				}

				for (pointNode = translate->first_node("point"); pointNode != NULL; pointNode = pointNode->next_sibling("point")) {
					float* points = (float*)malloc(sizeof(float) * 3);

					points[0] = atof(pointNode->first_attribute("x")->value());
					points[1] = atof(pointNode->first_attribute("y")->value());
					points[2] = atof(pointNode->first_attribute("z")->value());

					group->catPoints.push_back(points);
				}
			}
			else {
				if (translatex = translate->first_attribute("x")) {
					group->tx = atof(translatex->value());
				}
				if (translatey = translate->first_attribute("y")) {
					group->ty = atof(translatey->value());
				}
				if (translatez = translate->first_attribute("z")) {
					group->tz = atof(translatez->value());
				}
			}
		}

		if (rotate) {
			if (rotate->first_attribute("time")) {
				if (tesselation = rotate->first_attribute("time")) {
					group->tesselation = atof(tesselation->value());
				}
				if (rotatex = rotate->first_attribute("x")) {
					group->timerx = atof(rotatex->value());
				}

				if (rotatey = rotate->first_attribute("y")) {
					group->timery = atof(rotatey->value());
				}

				if (rotatez = rotate->first_attribute("z")) {
					group->timerz = atof(rotatez->value());
				}
			}
			else {
				if (rotatealpha = rotate->first_attribute("angle")) {
					group->ralpha = atof(rotatealpha->value());
				}
				if (rotatex = rotate->first_attribute("x")) {
					group->rx = atof(rotatex->value());
				}

				if (rotatey = rotate->first_attribute("y")) {
					group->ry = atof(rotatey->value());
				}

				if (rotatez = rotate->first_attribute("z")) {
					group->rz = atof(rotatez->value());
				}
			}
		}

		if (scale) {
			if (scalex = scale->first_attribute("x")) {
				group->sx = atof(scalex->value());
			}

			if (scaley = scale->first_attribute("y")) {
				group->sy = atof(scaley->value());
			}

			if (scalez = scale->first_attribute("z")) {
				group->sz = atof(scalez->value());
			}
		}
	}

	xml_node<>* node;

	for (node = group_node->first_node("group"); node != NULL; node = node->next_sibling("group")) {
		Group* subgroup = new Group();

		parse_group(node, subgroup, points);

		group->groups.push_back(subgroup);
	}
}

void parser(char* fileName, vector<Lights*>* lights, Window* window, Camera* camera, Group* group, vector<float>* points) {
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

	//Parse lights
	xml_node<>* lights_node = root_node->first_node("lights");
	parse_lights(lights_node, lights);

	//Parse camera
	xml_node<>* camera_node = root_node->first_node("camera");
	parse_camera(camera_node, camera);

	//Parse group
	xml_node<>* group_node = root_node->first_node("group");
	parse_group(group_node, group, points);
}
