#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <fstream>

using namespace std;

template<typename T>

void print(T collection, int size) {
	for (int i = 0; i < size; i++) {
		cout << collection[i] << endl;
	}
}

template <typename T>
void print(T collection) {
	print(collection, collection.size());
}

void generateSphere() {
	//Remover ficheiro antigo de esfera talvez
	ofstream file("sphere.3d");
}

void generateBox() {
	ofstream file("box.3d");
}

void generateCone() {
	ofstream file("cone.3d");
}

void generatePlane() {
	ofstream file("plane.3d");
}

int main(int argc, char *argv[]) {

	/*
	cout << "argc : " << argc << endl;
	cout << "argv[zero]: " << argv[0] << endl;
	cout << "argv[1]: " << argv[1] << endl;
	cout << "argv[2]: " << argv[2] << endl;
	cout << "argv[3]: " << argv[3] << endl;
	cout << "argv[4]: " << argv[4] << endl;
	*/

	if (strcmp(argv[1],"generateSphere") == 0) {
		generateSphere();
	}
	else if (strcmp(argv[1], "generateBox") == 0) {
		generateBox();
	}
	else if (strcmp(argv[1], "generateCone") == 0) {
		generateCone();
	}
	else if (strcmp(argv[1], "generatePlane") == 0) {
		generatePlane();
	}
	else {
		cout << "ERROR: Não existe nenhuma funcao: " << argv[1] << endl;
	}

	return 0;
}