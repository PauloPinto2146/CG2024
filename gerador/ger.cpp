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

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <tuple>

void multMatrixVector(float* m[4][4], float* v, float *res) {
		for (int j = 0; j < 4; ++j) {
			res[j] = 0;
			for (int k = 0; k < 4; ++k) {
				res[j] += v[k] * m[j][k];
			}
		}
}

tuple<float, float, float> B(float u, float v, vector<vector<float>> controlPoints, vector<vector<float>> patchIndexs, int patch) {
	float M[4][4] = { {-1,3,-3,1},{3,-6,3,0},{-3,3,0,0},{1,0,0,0} }; // M = Mt
	float u[4] = { pow(u,3),pow(u,2),u,1};
	float v[4] = { pow(v,3),pow(v,2),v,1 };
	float P[4][4] = { {patchIndexs[patch][0],patchIndexs[patch][1],patchIndexs[patch][2],patchIndexs[patch][3]},
					{patchIndexs[patch][4],patchIndexs[patch][5],patchIndexs[patch][6],patchIndexs[patch][7]},
					{patchIndexs[patch][8],patchIndexs[patch][9],patchIndexs[patch][10],patchIndexs[patch][11]},
					{patchIndexs[patch][12],patchIndexs[patch][13],patchIndexs[patch][14],patchIndexs[patch][15]} };
	float MV[4];
	multMatrixVector(M, v, MV);
	float PMV[4];
	multMatrixVector(P, MV, PMV);
	float MPMV[4];
	multMatrixVector(M, PMV, MPMV);
	float UMPMV[4];
	multMatrixVector(U, MPMV, UMPMV);
	return make_tuple(UMPMV[0], UMPMV[1], UMPMV[2]);
}

tuple<int, int> readPatchFile(char* ficheiroPatch, vector<vector<float>>* controlPoints, vector<vector<float>>* patchIndexs) {
	int nPatches;
	int nControlPoints;

	ifstream file;
	file.open(ficheiroPatch, ios::in);

	file >> nPatches;

	while (getline(file, line)) {
		vector<float> patchIndicesRow;
		stringstream ss(line);
		string value;

		size_t commaCount = count(line.begin(), line.end(), ',');
		if (commaCount < 1) {
			file >> nControlPoints;
			break;
		}

		while (getline(ss, value, ',')) {
			patchIndicesRow.push_back(stof(value));
		}

		patchIndexs.push_back(patchIndicesRow);
	}
	while (getline(file, line)) {
		vector<float> controlPointRow;
		stringstream ss(line);
		string value;

		while (getline(ss, value, ',')) {
			controlPointsRow.push_back(stof(value));
		}
		controlPoint.push_back(controlPointRow);
	}
	file.close();

	return make_tuple(nPatches, nControlPoints);
}

void generatePatch(char* argv[]) {
	ofstream file(argv[4], ios::binary | ios::out);
	//generator patch teapot.patch 10 bezier_10.3d

	char* ficheiroPatch = argv[2];
	vector<float>* controlPoints;
	vector<float>* patchIndexs;
	auto res = readPatchFile(ficheiroPatch, &controlPoints, &patchIndexs);

	int nPatches = get<0>(res);
	int nControlPoints = get<1>(res);

	float tessellation = atoi(argv[3]);

	int patchesSize = nPatches * 16;
	int controlPointsSize = nControlPoints * 3;
	int u, v;

	vector<float> pontos;
	tuple<float, float, float> pontoTriangulo;

	for(int patch = 0; patch<patchIndexs.size(); patch++){
		for (u = 0; u < tessellation; u++){
			for (v = 0; v < tessellation; v++){
				//Triangulo 1
				pontoTriangulo = B(u / tesselation, v / tesselation, patchIndexs, controlPoints,patch);
				pontos.push_back(get<0>(pontoTriangulo)); //px
				pontos.push_back(get<1>(pontoTriangulo)); //py
				pontos.push_back(get<2>(pontoTriangulo)); //pz
				pontoTriangulo = B((u + 1) / tesselation, v / tesselation, patchIndexs, controlPoints, patch);
				pontos.push_back(get<0>(pontoTriangulo));
				pontos.push_back(get<1>(pontoTriangulo));
				pontos.push_back(get<2>(pontoTriangulo));
				pontoTriangulo = B((u + 1) / tesselation, (v+1) / tesselation, patchIndexs, controlPoints, patch);
				pontos.push_back(get<0>(pontoTriangulo));
				pontos.push_back(get<1>(pontoTriangulo));
				pontos.push_back(get<2>(pontoTriangulo));
				//Triangulo 2 
				pontoTriangulo = B((u + 1) / tesselation, v / tesselation, patchIndexs, controlPoints, patch);
				pontos.push_back(get<0>(pontoTriangulo)); //px
				pontos.push_back(get<1>(pontoTriangulo)); //py
				pontos.push_back(get<2>(pontoTriangulo)); //pz
				pontoTriangulo = B((u + 1) / tesselation, (v + 1) / tesselation, patchIndexs, controlPoints, patch);
				pontos.push_back(get<0>(pontoTriangulo));
				pontos.push_back(get<1>(pontoTriangulo));
				pontos.push_back(get<2>(pontoTriangulo));
				pontoTriangulo = B(u / tesselation, (v + 1) / tesselation, patchIndexs, controlPoints, patch);
				pontos.push_back(get<0>(pontoTriangulo));
				pontos.push_back(get<1>(pontoTriangulo));
				pontos.push_back(get<2>(pontoTriangulo));
			}
		}
	}
	file.write((char*)&N, sizeof(int));
	file.write((char*)pontos.data(), sizeof(float) * N);
	file.close();
}

void generateSphere(char* argv[]) {
	ofstream file(argv[5],ios::binary | ios::out);
	//generator generateSphere radius slices stacks sphere.3d

	float radius = atoi(argv[2]);
	float slices = atoi(argv[3]);
	float stacks = atoi(argv[4]);

	int N = (stacks * slices * 9) + (stacks * slices * 18); //Número de pontos
	vector<float> pontos(N);
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
			//Triangulo1
			//P1
			pontos[p] = radius * cos(theta) * sin(phi); p++; //x0
			pontos[p] = radius * cos(phi); p++; //y0
			pontos[p] = radius * sin(theta) * sin(phi); p++; //z0
			//P2
			pontos[p] = radius * cos(theta1) * sin(phi); p++; //x2
			pontos[p] = radius * cos(phi); p++; //y2
			pontos[p] = radius * sin(theta1) * sin(phi); p++; //z2
			//P3
			pontos[p] = radius * cos(theta) * sin(phi1); p++; //x1
			pontos[p] = radius * cos(phi1); p++; //y1
			pontos[p] = radius * sin(theta) * sin(phi1); p++; //z1
			//Triangulo2
			//P1
			pontos[p] = radius * cos(theta1) * sin(phi); p++; //x2
			pontos[p] = radius * cos(phi); p++; //y2
			pontos[p] = radius * sin(theta1) * sin(phi); p++; //z2
			//P2
			pontos[p] = radius * cos(theta1) * sin(phi1); p++;
			pontos[p] = radius * cos(phi1); p++;
			pontos[p] = radius * sin(theta1) * sin(phi1); p++;
			//P3
			pontos[p] = radius * cos(theta) * sin(phi1); p++; //x1
			pontos[p] = radius * cos(phi1); p++; //y1
			pontos[p] = radius * sin(theta) * sin(phi1); p++; //z1
		}
	}
	file.write((char*)&N, sizeof(int));
	file.write((char*)pontos.data(), sizeof(float) * N);
	file.close();
}

void generateBox(char* argv[]) {
	ofstream file(argv[4], ios::binary|ios::out);
	//generator box length grid box.3d
	float length = atoi(argv[2]);
	float grid = atoi(argv[3]);
	float half = length / 2;
	float portion = length / grid;
	int N = grid * grid * 18 * 6; //Número de pontos
	vector<float> pontos(N);
	int p = 0;

	//plano de baixo e de cima (y estável)
	for (int i = 0; i < grid; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
		for (int j = 0; j < grid; j++) {
			float x = i * portion - half;
			float z = j * portion - half;
			//BAIXO
			//Triangulo 1 
			//P1
			pontos[p] = x; p++;
			pontos[p] = -half; p++;
			pontos[p] = z; p++;
			//P2
			pontos[p] = x + portion; p++;
			pontos[p] = -half; p++;
			pontos[p] = z; p++;
			//P3
			pontos[p] = x + portion; p++;
			pontos[p] = -half; p++;
			pontos[p] = z + portion; p++;
			//Triangulo 2
			//P1
			pontos[p] = x + portion; p++;
			pontos[p] = -half; p++;
			pontos[p] = z + portion; p++;
			//P2
			pontos[p] = x; p++;
			pontos[p] = -half; p++;
			pontos[p] = z + portion; p++;
			//P3
			pontos[p] = x; p++;
			pontos[p] = -half; p++;
			pontos[p] = z; p++;
			// CIMA
			pontos[p] = x + portion; p++;
			pontos[p] = half; p++;
			pontos[p] = z + portion; p++;
			//P2
			pontos[p] = x + portion; p++;
			pontos[p] = half; p++;
			pontos[p] = z; p++;
			//P3
			pontos[p] = x; p++;
			pontos[p] = half; p++;
			pontos[p] = z; p++;
			//Triangulo 2
			//P1
			pontos[p] = x; p++;
			pontos[p] = half; p++;
			pontos[p] = z; p++;
			//P2
			pontos[p] = x; p++;
			pontos[p] = half; p++;
			pontos[p] = z + portion; p++;
			//P3
			pontos[p] = x + portion; p++;
			pontos[p] = half; p++;
			pontos[p] = z + portion; p++;
		}
	}
	//plano da trás e de frente (x estável)
	for (int i = 0; i < grid; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
		for (int j = 0; j < grid; j++) {
				float y = i * portion - half;
				float z = j * portion - half;
				//FRENTE
				//Triangulo 1 
				//P1
				pontos[p] = half; p++;
				pontos[p] = y; p++;
				pontos[p] = z; p++;
				//P2
				pontos[p] = half; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = z + portion; p++;
				//P3
				pontos[p] = half; p++;
				pontos[p] = y; p++;
				pontos[p] = z + portion; p++;

				//Triangulo 2
				//P1
				pontos[p] = half; p++;
				pontos[p] = y; p++;
				pontos[p] = z; p++;
				//P2
				pontos[p] = half; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = z; p++;
				//P3
				pontos[p] = half; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = z + portion; p++;

				//TRAS
				//Triangulo 1 
				//P1
				pontos[p] = -half; p++;
				pontos[p] = y; p++;
				pontos[p] = z + portion; p++;
				//P2
				pontos[p] = -half; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = z + portion; p++;
				//P3
				pontos[p] = -half; p++;
				pontos[p] = y; p++;
				pontos[p] = z; p++;

				//Triangulo 2
				//P1
				pontos[p] = -half; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = z + portion; p++;
				//P2
				pontos[p] = -half; p++;
				pontos[p] = y + portion; p++;
				pontos[p] = z; p++;
				//P3
				pontos[p] = -half; p++;
				pontos[p] = y; p++;
				pontos[p] = z; p++;
		}
	}
	//plano da direita e da esquerda (z estável)
	for (int i = 0; i < grid; i++) { // Começar pelo menor z e menor x e iterando pela linha dos x até length/2
		for (int j = 0; j < grid; j++) {
			float x = i * portion - half;
			float y = j * portion - half;
			//DIREITA
			//Triangulo 1 
			//P1
			pontos[p] = x + portion; p++;
			pontos[p] = y + portion; p++;
			pontos[p] = -half; p++;
			//P2
			pontos[p] = x + portion; p++;
			pontos[p] = y; p++;
			pontos[p] = -half; p++;
			//P3
			pontos[p] = x; p++;
			pontos[p] = y; p++;
			pontos[p] = -half; p++;
			//Triangulo 2
			//P1
			pontos[p] = x + portion; p++;
			pontos[p] = y; p++;
			pontos[p] = -half; p++;
			//P2
			pontos[p] = x; p++;
			pontos[p] = y + portion; p++;
			pontos[p] = -half; p++;
			//P3
			pontos[p] = x + portion; p++;
			pontos[p] = y + portion; p++;
			pontos[p] = -half; p++;
			//ESQUERDA
			//Triangulo 1 
			//P1
			pontos[p] = x; p++;
			pontos[p] = y; p++;;
			pontos[p] = half; p++;
			//P2
			pontos[p] = x + portion; p++;
			pontos[p] = y; p++;
			pontos[p] = half; p++;
			//P3
			pontos[p] = x + portion; p++;
			pontos[p] = y + portion; p++;
			pontos[p] = half; p++;
			//Triangulo 2
			//P1
			pontos[p] = x + portion; p++;
			pontos[p] = y + portion; p++;
			pontos[p] = half; p++;
			//P2
			pontos[p] = x; p++;
			pontos[p] = y + portion; p++;
			pontos[p] = half; p++;
			//P3
			pontos[p] = x; p++;
			pontos[p] = y; p++;
			pontos[p] = half; p++;
		}
	}
	file.write((char*)&N, sizeof(int));
	file.write((char*)pontos.data(), sizeof(float)* N);
	file.close();
}

void generateCone(char* argv[]) {
	ofstream file(argv[6], ios::binary|ios::out);
	//generator cone radius height slices stacks cone.3d

	float radius = atoi(argv[2]);
	float height = atoi(argv[3]);
	float slices = atoi(argv[4]);
	float stacks = atoi(argv[5]);

	int N = (slices * 9)*(stacks * slices * 18);
	vector<float> pontos(N);
	int p = 0;
	float alpha = 2 * M_PI / slices;
	float rinc = (radius / stacks);
	float hinc = (height / stacks);

	//Base
	for (int i = 0; i < slices; i++) {
		pontos[p] = radius * sin(alpha*i); p++;
		pontos[p] = 0; p++;
		pontos[p] = radius * cos(alpha*i); p++;

		pontos[p] = 0; p++;
		pontos[p] = 0; p++;
		pontos[p] = 0; p++;

		pontos[p] = radius * sin(alpha * (i+1)); p++;
		pontos[p] = 0; p++;
		pontos[p] = radius * cos(alpha * (i + 1)); p++;
	}

	//Laterais
	for (int i = 0; i < stacks; i++) {
		for (int j = 0; j < slices; j++) {
			float raio = radius - i * rinc;
			float nextraio = raio - rinc;
			float altura = i * hinc;
			float nextaltura = altura + hinc;
			//Triangulo 1
			pontos[p] = nextraio * sin(alpha*j); p++;
			pontos[p] = nextaltura; p++;
			pontos[p] = nextraio * cos(alpha*j); p++;

			pontos[p] = raio * sin(alpha * j); p++;
			pontos[p] = altura; p++;
			pontos[p] = raio *  cos(alpha * j); p++;

			pontos[p] = raio *  sin(alpha * (j+1)); p++;
			pontos[p] = altura; p++;
			pontos[p] = raio *  cos(alpha * (j + 1)); p++;
			//Triangulo 2
			pontos[p] = nextraio * sin(alpha * (j + 1)); p++;
			pontos[p] = nextaltura; p++;
			pontos[p] = nextraio * cos(alpha * (j + 1)); p++;

			pontos[p] = nextraio * sin(alpha * j); p++;
			pontos[p] = nextaltura; p++;
			pontos[p] = nextraio * cos(alpha * j); p++;

			pontos[p] = raio * sin(alpha * (j + 1)); p++;
			pontos[p] = altura; p++;
			pontos[p] = raio * cos(alpha * (j + 1)); p++;
		}
	}

	file.write((char*)&N, sizeof(int));
	file.write((char*)pontos.data(),sizeof(float)*N);
	file.close();
}

void generatePlane(char* argv[]) {
	ofstream file(argv[4], ios::binary | ios::out);
	//generator plane length divisions plane.3d

	float length = atoi(argv[2]);
	float divisions = atoi(argv[3]);
	float tr = length / divisions;
	int N = divisions * divisions * 18;
	vector<float> pontos(N);
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
	file.write((char*)&N, sizeof(int));
	file.write((char*)pontos.data(), sizeof(float) * N);

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
	else if (strcmp(argv[1], "patch") == 0) {
		generatePatch(argv);
	}
	else {
		cout << "ERROR: Nao existe nenhuma funcao: " << argv[1] << endl;
	}

	return 0;
}