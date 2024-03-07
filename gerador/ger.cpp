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

	file << "sphere\n";

	float radius = atoi(argv[2]);
	float slices = atoi(argv[3]);
	float stacks = atoi(argv[4]);

	int N = (stacks*slices*9)+(stacks*slices*18); //Número de pontos
	std::vector<float> pontos(N);
	int p = 0;

	float altura = - radius;

	//Bases das stacks (de baixo para cima)
	for (int i = 0; i < stacks; i++) {
		altura += radius / stacks;
		float alpha = 2.0 * M_PI * i / slices;
		float next_alpha = 2.0f * M_PI * (i + 1) / slices;
		float beta = M_PI * i / slices;
		for (int j = 0; j < slices; j++) {
			//P1
			pontos[p] = radius * cos(beta) * sin(alpha); p++;
			pontos[p] = altura; p++;
			pontos[p] = radius * cos(beta) * cos(alpha); p++;
			//Centro
			pontos[p] = altura; p++;
			pontos[p] = altura; p++;
			pontos[p] = altura; p++;
			//P2
			pontos[p] = radius * cos(beta) * sin(next_alpha); p++;
			pontos[p] = altura; p++;
			pontos[p] = radius * cos(beta) * cos(next_alpha); p++;
		}
	}
	float altura_up = -radius;
	float altura_down = -radius + radius / stacks;
	//laterais (de baixo para cima)
	for (int i = 0; i < stacks; i++) {
		altura_up += radius / stacks;
		altura_down += radius / stacks;
		float beta = M_PI * i / slices;
		float next_beta = M_PI * (i+1) / slices; 
		for (int j = 0; j < slices; j++) {
			float alpha = 2.0 * M_PI * j / slices;
			float next_alpha = 2.0f * M_PI * (j + 1) / slices;
			//Cada face tem 2 tringulos
			//TRIANGULO 1
			//P1 (cima)
			pontos[p] = radius * cos(beta) * sin(alpha); p++;
			pontos[p] = altura; p++;
			pontos[p] = radius * cos(beta) * cos(alpha); p++;
			//P2 (baixo 1)
			pontos[p] = radius * cos(next_beta) * sin(alpha); p++;
			pontos[p] = altura; p++; 
			pontos[p] = radius * cos(next_beta) * cos(alpha); p++;
			//P3 (baixo 2)
			pontos[p] = radius * cos(next_beta) * sin(next_alpha); p++;
			pontos[p] = altura; p++;
			pontos[p] = radius * cos(next_beta) * cos(next_alpha); p++;

			//TRIANGULO 2
			//P1 (cima)
			pontos[p] = radius * cos(beta) * sin(next_alpha); p++;
			pontos[p] = altura; p++; 
			pontos[p] = radius * cos(beta) * cos(next_alpha); p++;
			//P2 (baixo 1)
			pontos[p] = radius * cos(next_beta) * sin(alpha); p++; 
			pontos[p] = altura; p++; 
			pontos[p] = radius * cos(next_beta) * cos(alpha); p++; 
			//P3 (baixo 2)
			pontos[p] = radius * cos(next_beta) * sin(next_alpha); p++; 
			pontos[p] = altura; p++; 
			pontos[p] = radius * cos(next_beta) * cos(next_alpha); p++; 
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
	float tr = length / 2;
	int N = grid * grid * 18 * 6; //Número de pontos
	std::vector<float> pontos(N);
	int p = 0;

	//plano de baixo e de cima (y estável)
	for (int a = -1; a < 2; a += 2) {
		for (int i = 0; i < grid; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
			for (int j = 0; j < grid; j++) {
				//Cada quadrado é formado por 2 triângulos:
				//Triangulo 1 
				//P1
				pontos[p] = j * tr - (length / 2); p++;
				pontos[p] = a * tr; p++;
				pontos[p] = i * tr - (length / 2); p++;
				//P2
				pontos[p] = (j + 1) * tr - length / 2; p++;
				pontos[p] = a * tr; p++;
				pontos[p] = i * tr - length / 2; p++;
				//P3
				pontos[p] = j * tr - length / 2; p++;
				pontos[p] = a * tr; p++;
				pontos[p] = (i + 1) * tr - length / 2; p++;

				//Triangulo 2
				//P1
				pontos[p] = (j + 1) * tr - length / 2; p++;
				pontos[p] = a * tr; p++;
				pontos[p] = (i + 1) * tr - length / 2; p++;
				//P2
				pontos[p] = (j + 1) * tr - length / 2; p++;
				pontos[p] = a * tr; p++;
				pontos[p] = i * tr - length / 2; p++;
				//P3
				pontos[p] = j * tr - length / 2; p++;
				pontos[p] = a * tr; p++;
				pontos[p] = (i + 1) * tr - length / 2; p++;
			}
		}
	}
	//plano da esquerda e da direita (z estável)
	for (int a = -1; a < 2; a += 2) {
		for (int i = 0; i < grid; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
			for (int j = 0; j < grid; j++) {
				//Cada quadrado é formado por 2 triângulos:
				//Triangulo 1 
				//P1
				pontos[p] = j * tr - (length / 2); p++;
				pontos[p] = i * tr - (length / 2); p++;
				pontos[p] = a * tr; p++;
				//P2
				pontos[p] = (j+1) * tr - length / 2; p++;
				pontos[p] = i * tr - length / 2; p++;
				pontos[p] = a * tr; p++;
				//P3
				pontos[p] = j * tr - length / 2; p++;
				pontos[p] = (i+1) * tr - length / 2; p++;
				pontos[p] = a * tr; p++;

				//Triangulo 2
				//P1
				pontos[p] = (j + 1) * tr - length / 2; p++;
				pontos[p] = (i + 1) * tr - length / 2; p++;
				pontos[p] = a * tr; p++;
				//P2
				pontos[p] = (j + 1) * tr - length / 2; p++;
				pontos[p] = i * tr - length / 2; p++;
				pontos[p] = a * tr; p++;
				//P3
				pontos[p] = j * tr - length / 2; p++;
				pontos[p] = (i + 1) * tr - length / 2; p++;
				pontos[p] = a * tr; p++;
			}
		}
	}
	//plano da frente e de trás (x estável)
	for (int a = -1; a < 2; a += 2) {
		for (int i = 0; i < grid; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
			for (int j = 0; j < grid; j++) {
				//Cada quadrado é formado por 2 triângulos:
				//Triangulo 1 
				//P1
				pontos[p] = a * tr; p++;
				pontos[p] = i * tr - (length / 2); p++;
				pontos[p] = j * tr - (length / 2); p++;
				//P2
				pontos[p] = a * tr; p++; 
				pontos[p] = i * tr - length / 2; p++;
				pontos[p] = (j + 1) * tr - length / 2; p++;
				//P3
				pontos[p] = a * tr; p++;
				pontos[p] = (i + 1) * tr - length / 2; p++;
				pontos[p] = j * tr - length / 2; p++;

				//Triangulo 2
				//P1
				pontos[p] = a * tr; p++;
				pontos[p] = (i + 1) * tr - length / 2; p++; 
				pontos[p] = (j + 1) * tr - length / 2; p++;
				//P2
				pontos[p] = a * tr; p++;
				pontos[p] = i * tr - length / 2; p++; 
				pontos[p] = (j + 1) * tr - length / 2; p++; 
				//P3
				pontos[p] = a * tr; p++;
				pontos[p] = (i + 1) * tr - length / 2; p++;
				pontos[p] = j * tr - length / 2; p++;
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

	file << "cone\n";

	float radius = atoi(argv[2]);
	float height = atoi(argv[3]);
	float slices = atoi(argv[4]);
	float stacks = atoi(argv[5]);
	float alpha = 2 * M_PI / slices;
	float next_alpha = alpha;

	int N = (slices * 9) + (stacks * slices * 9) + (stacks * slices * 18);
	std::vector<float> pontos(N);
	int p = 0;

	//Base de baixo
	for (int i = 0; i < slices; i++) {
		//centro (P1)
		pontos[p] = 0; p++;
		pontos[p] = 0; p++;
		pontos[p] = 0; p++;
		//P2
		pontos[p] = radius * sin(alpha * i); p++;
		pontos[p] = 0; p++;
		pontos[p] = radius * cos(alpha * i); p++;
		//P3
		pontos[p] = radius * sin(alpha * (i+1)); p++;
		pontos[p] = 0; p++;
		pontos[p] = radius * cos(alpha * (i+1)); p++;
	}
	//Bases de Stacks (Começar da ponta do cone até à base)
	float altura = height;
	float raio = 0.0;
	for (int i = 0; i < stacks; i++) {
		altura -= (height/stacks);
		for (int j = 0; j < slices; j++) {
			float new_alpha = 2.0f * M_PI * j / slices;
			float next_alpha = 2.0f * M_PI * (j + 1) / slices;
			raio += radius / stacks;
			//Centro da circunferência atual
			pontos[p] = 0; p++;
			pontos[p] = altura; p++;
			pontos[p] = 0; p++;
			//P1
			pontos[p] = raio * sin(new_alpha); p++;
			pontos[p] = altura; p++;
			pontos[p] = raio * cos(new_alpha); p++;
			//P2
			pontos[p] = raio * sin(next_alpha); p++;
			pontos[p] = altura; p++;
			pontos[p] = raio * cos(next_alpha); p++;
		}
	}
	//Laterais (baixo para cima)
	altura = 0;
	float next_altura = 0.0;
	for (int i = 0; i < stacks; i++) {
		altura = next_altura;
            	next_altura = altura + height / stacks;
		for (int j = 0; j < slices; j++) {
			float new_alpha = 2.0f * M_PI * j / slices;
			float next_alpha = 2.0f * M_PI * (j + 1) / slices;
			//Cada face 2 triângulos
			//Triangulo 1
			  // Ponto 1
			pontos[p] = raio * sin(new_alpha); p++;
			pontos[p] = altura; p++;
			pontos[p] = raio * cos(new_alpha); p++;
			  // Ponto 2
			pontos[p] = raio * sin(next_alpha); p++;
			pontos[p] = altura; p++;
			pontos[p] = raio * cos(next_alpha); p++;
			  // Ponto 3
			pontos[p] = raio * sin(new_alpha); p++;
			pontos[p] = next_altura; p++;
			pontos[p] = raio * cos(new_alpha); p++;
			//Triangulo 2
			  // Ponto 1
			pontos[p] = raio * sin(new_alpha); p++;
			pontos[p] = next_altura; p++;
			pontos[p] = raio * cos(new_alpha); p++;
			  // Ponto 2
			pontos[p] = raio * sin(next_alpha); p++;
			pontos[p] = altura; p++;
			pontos[p] = raio * cos(next_alpha); p++;
			  // Ponto 3
			pontos[p] = raio * sin(next_alpha); p++;
			pontos[p] = next_altura; p++;
			pontos[p] = raio * cos(next_alpha); p++;
		}
	}
	for (int i = 0; i < N; i++)
		file << pontos[i] << "\n";
	file.close();
}

void generatePlane(char *argv[]) {
	ofstream file(argv[4]);
	//generator plane length divisions plane.3d
	
	file << "plane\n";

	float length = atoi(argv[2]);
	float divisions = atoi(argv[3]);
	float tr = length / divisions;
	int N = divisions * divisions * 18;
	std::vector<float> pontos(N);
	int p = 0;

	for (int i = 0; i < divisions; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
		for (int j = 0; j < divisions; j++) {
			//Cada quadrado é formado por 2 triângulos:
			//Triangulo 1 
			//P1
			pontos[p] = j * tr - (length / 2); p++;
			pontos[p] = 0; p++;
			pontos[p] = i * tr - (length / 2); p++;
			//P2
			pontos[p] = (j + 1) * tr - length / 2; p++;
			pontos[p] = 0 ; p++;
			pontos[p] = i * tr -length / 2; p++;
			//P3
			pontos[p] = j * tr - length / 2; p++;
			pontos[p] = 0; p++;
			pontos[p] = (i+1) * tr - length / 2; p++;

			//Triangulo 2
			//P1
			pontos[p] = (j + 1) * tr - length / 2; p++;
			pontos[p] = 0; p++;
			pontos[p] = (i+1) * tr - length / 2; p++;
			//P2
			pontos[p] = (j + 1) * tr - length / 2; p++;
			pontos[p] = 0; p++;
			pontos[p] = i * tr - length / 2; p++;
			//P3
			pontos[p] = j * tr - length / 2; p++;
			pontos[p] = 0; p++;
			pontos[p] = (i + 1) * tr - length / 2; p++;
		}
	}
	for (int i = 0; i < N; i++)
		file << pontos[i] << "\n";

	file.close();
}

int main(int argc, char *argv[]) {

	if (strcmp(argv[1],"sphere") == 0) {
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
