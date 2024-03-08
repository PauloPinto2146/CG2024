#include <iostream>
#include <cstring>
#include <array>
#include <vector>
#include <deque>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

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
	ofstream file(argv[5]);
	//generator generateSphere radius slices stacks sphere.3d

	float radius = atoi(argv[2]);
	float slices = atoi(argv[3]);
	float stacks = atoi(argv[4]);

	int N = (stacks * slices * 9) + (stacks * slices * 18); //Número de pontos
	std::vector<float> pontos(N);
	int p = 0;

	float const R = 1.0f / slices;
	float const S = 1.0f / stacks;

	//Bases das stacks (de baixo para cima)
	for (int i = 0; i < stacks; i++) {
		float const phi = M_PI * i * S;
		float const phi1 = M_PI * (i + 1) * S;
		for (int j = 0; j < slices; j++) {
			float const theta = 2.0f * M_PI * j * R;
			float const theta1 = 2.0f * M_PI * (j+1) * R;
			//P1
			pontos[p] = radius * cos(theta) * sin(phi); p++;
			pontos[p] = radius * cos(phi); p++;
			pontos[p] = radius * sin(theta) * sin(phi); p++;
			//P2
			pontos[p] = radius * cos(theta) * sin(phi1); p++;
			pontos[p] = radius * cos(phi1); p++;
			pontos[p] = radius * sin(theta) * sin(phi1); p++;
			//P3
			pontos[p] = radius * cos(theta1) * sin(phi); p++;
			pontos[p] = radius * cos(phi); p++;
			pontos[p] = radius * sin(theta1) * sin(phi); p++;
			//P4
			pontos[p] = radius * cos(theta1) * sin(phi1); p++;
			pontos[p] = radius * cos(phi1); p++;
			pontos[p] = radius * sin(theta1) * sin(phi1); p++;
		}
	}
	for (int i = 0; i < N; i++)
		file << pontos[i] << "\n";

	file.close();
}

void generateBox(char* argv[]) {
	ofstream file(argv[4]);
	//generator box length grid box.3d
	float length = atoi(argv[2]);
	float grid = atoi(argv[3]);
	float half = length / 2;
	float portion = length / grid;
	int N = grid * grid * 18 * 6; //Número de pontos
	std::vector<float> pontos(N);
	int p = 0;

	//plano de baixo e de cima (y estável)
	for (int a = -1; a < 2; a += 2) {
		for (int i = 0; i < grid; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
			for (int j = 0; j < grid; j++) {
				float x = i * portion - half;
				float z = j * portion - half;
				//Cada quadrado é formado por 2 triângulos:
				//Triangulo 1 
				//P1
				pontos[p] = x; p++;
				pontos[p] = a * half; p++;
				pontos[p] = z; p++;
				//P2
				pontos[p] = x + portion; p++;
				pontos[p] = a * half; p++;
				pontos[p] = z; p++;
				//P3
				pontos[p] = x + portion; p++;
				pontos[p] = a * half; p++;
				pontos[p] = z + portion; p++;

				//Triangulo 2
				//P1
				pontos[p] = x; p++;
				pontos[p] = a * half; p++;
				pontos[p] = z + portion; p++;
				//P2
				pontos[p] = x + portion; p++;
				pontos[p] = a * half; p++;
				pontos[p] = z + portion; p++;
				//P3
				pontos[p] = x; p++;
				pontos[p] = a * half; p++;
				pontos[p] = z; p++;
			}
		}
	}
	//plano da trás e de frente (x estável)
	for (int a = -1; a < 2; a += 2) {
		for (int i = 0; i < grid; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
			for (int j = 0; j < grid; j++) {
				float y = i * portion - half;
				float z = j * portion - half;
				//Cada quadrado é formado por 2 triângulos:
				//Triangulo 1 
				//P1
				pontos[p] = a * half; p++;
				pontos[p] = y; p++;
				pontos[p] = z; p++;
				//P2
				pontos[p] = a * half; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = z; p++;
				//P3
				pontos[p] = a * half; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = z + portion; p++;

				//Triangulo 2
				//P1
				pontos[p] = a * half; p++;
				pontos[p] = y; p++;
				pontos[p] = z; p++;
				//P2
				pontos[p] = a * half; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = z + portion; p++;
				//P3
				pontos[p] = a * half; p++;
				pontos[p] = y; p++;
				pontos[p] = z + portion; p++;
			}
		}
	}
	//plano da esquerda e da direita (z estável)
	for (int a = -1; a < 2; a += 2) {
		for (int i = 0; i < grid; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
			for (int j = 0; j < grid; j++) {
				float x = i * portion - half;
				float y = j * portion - half;
				//Cada quadrado é formado por 2 triângulos:
				//Triangulo 1 
				//P1
				pontos[p] = x + portion; p++;
				pontos[p] = y + portion; p++;;
				pontos[p] = a * half; p++;
				//P2
				pontos[p] = x + portion; p++;
				pontos[p] = y; p++;
				pontos[p] = a * half; p++;
				//P3
				pontos[p] = x; p++;
				pontos[p] = y; p++;
				pontos[p] = a * half; p++;

				//Triangulo 2
				//P1
				pontos[p] = x + portion; p++;
				pontos[p] = y; p++;
				pontos[p] = a * half; p++;
				//P2
				pontos[p] = x; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = a * half; p++;
				//P3
				pontos[p] = x + portion; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = a * half; p++;
			}
		}
	}
	for (int i = 0; i < N; i++)
		file << pontos[i] << "\n";
	file.close();
}

void generateCone(char* argv[]) {
	ofstream file(argv[6]);
	//generator cone radius height slices stacks cone.3d

	float radius = atoi(argv[2]);
	float height = atoi(argv[3]);
	float slices = atoi(argv[4]);
	float stacks = atoi(argv[5]);

	float angleStep = (2 * M_PI) / slices;
	float stackHeight = height / stacks;
	float currentRadius = radius;

	int N = (slices * 9) + (stacks * slices * 9) + (stacks * slices * 18);
	std::vector<float> pontos(N);
	int p = 0;

	for (int i = 0; i < slices; i++) {
		float nextRadius = radius * (1.0f - (float)(i + 1) / stacks);
		for (int j = 0; j < slices; ++j) {
			float angle1 = j * angleStep;
			float angle2 = (j + 1) * angleStep;

			// Vertices for the current stack
			pontos[p] = currentRadius * cos(angle1); p++; //x1
			pontos[p] = i * stackHeight; p++; //y1
			pontos[p] = currentRadius * sin(angle1); p++; //z1

			pontos[p] = nextRadius * cos(angle1); p++;//nx1
			pontos[p] = (i+1) * stackHeight; p++; //y2
			pontos[p] = nextRadius * sin(angle1); p++; //nz1

			pontos[p] = currentRadius * cos(angle2); p++;//x2
			pontos[p] = i * stackHeight; p++;//y1
			pontos[p] = currentRadius * sin(angle2); p++; //z2
			
			pontos[p] = currentRadius * cos(angle2); p++; //x2
			pontos[p] = i * stackHeight; p++; //y1
			pontos[p] = currentRadius * sin(angle2); p++;//z2

			pontos[p] = nextRadius * cos(angle1); p++;//nx1
			pontos[p] = (i + 1) * stackHeight; p++; //y2
			pontos[p] = nextRadius * sin(angle1); p++;//nz1

			pontos[p] = nextRadius * cos(angle2); p++; //nx2
			pontos[p] = (i + 1) * stackHeight; p++; //y2
			pontos[p] = nextRadius * sin(angle2); p++;

			// Vertices for the next stack
			pontos[p] = nextRadius * cos(angle2);
			float nz2 = nextRadius * sin(angle2);
		}
		currentRadius = nextRadius;
	}
	for (int i = 0; i < N; i++)
		file << pontos[i] << "\n";
	file.close();
}

void generatePlane(char* argv[]) {
	ofstream file(argv[4]);
	//generator plane length divisions plane.3d

	float length = atoi(argv[2]);
	float divisions = atoi(argv[3]);
	float tr = length / divisions;
	int N = divisions * divisions * 18;
	std::vector<float> pontos(N);
	int p = 0;

	for (int i = 0; i < divisions; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
		for (int j = 0; j < divisions; j++) {
			//Cada face é formado por 2 triângulos:
			//Triangulo 1 
			//P1
			pontos[p] = (j + 1) * tr - (length / 2); p++;
			pontos[p] = 0; p++;
			pontos[p] = (i + 1) * tr - (length / 2); p++;
			//P2
			pontos[p] = (j + 1) * tr - (length / 2); p++;
			pontos[p] = 0; p++;
			pontos[p] = i * tr - (length / 2); p++;
			//P3
			pontos[p] = j * tr - (length / 2); p++;
			pontos[p] = 0; p++;
			pontos[p] = i * tr - (length / 2); p++;

			//Triangulo 2
			//P1
			pontos[p] = j * tr - (length / 2); p++;
			pontos[p] = 0; p++;
			pontos[p] = (i + 1) * tr - (length / 2); p++;
			//P2
			pontos[p] = (j + 1) * tr - (length / 2); p++;
			pontos[p] = 0; p++;
			pontos[p] = (i + 1) * tr - (length / 2); p++;
			//P3
			pontos[p] = j * tr - (length / 2); p++;
			pontos[p] = 0; p++;
			pontos[p] = i * tr - (length / 2); p++;
		}
	}
	for (int i = 0; i < N; i++)
		file << pontos[i] << "\n";

	file.close();
}

int main(int argc, char* argv[]) {

	if (strcmp(argv[1], "sphere") == 0) {
		generateSphere(argv);
	}
	else if (strcmp(argv[1], "box") == 0) {
		generateBox(argv);
	}
	else if (strcmp(argv[1], "cone") == 0) {
		generateCone(argv);
	}
	else if (strcmp(argv[1], "plane") == 0) {
		generatePlane(argv);
	}
	else {
		cout << "ERROR: Nao existe nenhuma funcao: " << argv[1] << endl;
	}

	return 0;
}
