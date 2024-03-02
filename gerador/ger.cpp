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

void generateSphere(char* argv[]) {
	//Remover ficheiro antigo de esfera talvez
	ofstream file("sphere.3d");
	//generator sphere radius slices stacks sphere.3d
}

void generateBox(char* argv[]) {
	ofstream file("box.3d");
	//generator box length grid box.3d
}

void generateCone(char* argv[]) {
	ofstream file("cone.3d");
	//generator cone radius height slices stacks cone.3d
}

void generatePlane(char *argv[]) {
	ofstream file("plane.3d");
	//generator plane length divisions plane.3d
	
	file << "plane\n";

	float length = atoi(argv[3]);
	float divisions = atoi(argv[4]);
	float tr = length / divisions;

	printf("length : %f\n", length);
	printf("divisions : %f\n", divisions);
	printf("transitions : %f\n", tr);

	for (int i = 0; i < divisions; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
		for (int j = 0; j < divisions; j++) {
			//Cada quadrado é formado por 2 triângulos:
			//Triangulo 1 
			//P1
			file << float(j * tr - (length / 2)) << "\n"; 
			file << 0 << "\n"; 
			file << i * tr - (length / 2) << "\n";
			//P2
			file << (j+1) * tr - length / 2 << "\n"; file << 0 << "\n"; file << i * tr -length / 2 << "\n";
			//P3
			file << j * tr - length / 2 << "\n"; file << 0 << "\n"; file << (i+1) * tr - length / 2 << "\n";

			//Triangulo 2
			//P1
			file << (j + 1) * tr - length / 2 << "\n"; file << 0 << "\n"; file << (i+1) * tr - length / 2 << "\n";
			//P2
			file << (j + 1) * tr - length / 2 << "\n"; file << 0 << "\n"; file << i * tr - length / 2 << "\n";
			//P3
			file << j * tr - length / 2 << "\n"; file << 0 << "\n"; file << (i + 1) * tr - length / 2 << "\n";
		}
	}
	file.close();
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
		generateSphere(argv);
	}
	else if (strcmp(argv[1], "generateBox") == 0) {
		generateBox(argv);
	}
	else if (strcmp(argv[1], "generateCone") == 0) {
		generateCone(argv);
	}
	else if (strcmp(argv[1], "generatePlane") == 0) {
		generatePlane(argv);
	}
	else {
		cout << "ERROR: Não existe nenhuma funcao: " << argv[1] << endl;
	}

	return 0;
}