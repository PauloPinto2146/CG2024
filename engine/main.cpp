#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
#include <fstream>
using namespace std;


float x1 = 20.0f, y1 = 20.0f, z1 = 20.0f; //coordenadas para o lookAt
float x2 = 0.0f, y2 = 0.0f, z2 = 0.0f; // coordenadas para a camara

// Camera position and rotation angles
GLfloat cameraX = 5.0f, cameraY = 5.0f, cameraZ = 5.0f, rotateX = 0.0f, rotateY = 0.0f, rotateZ = 0.0f, zoom = 1.0f;

void readFile(std::string fich) {
    ifstream file(fich);
    if (file.is_open()) {
        //
        //ler ficheiro
        //
        file.close();
			}
	else {
		cout << "File not found" << endl;
	}
	
}

void renderScene(void) {
    
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(x1, y1, z1, //todo: alterar aqui
        0.0, 0.0, 0.0,
        0.0f, 1.0f, 0.0f);

    //draw instructions
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glTranslatef(x2, y2, z2);
    glRotatef(0, 0.0, 1.0, 0.0);
    glRotatef(0, 1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);

    //
    //Desenhar os vertices lidos do ficheiro
    //

    glEnd();
    //End of frame
    glutSwapBuffers();
}

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);

	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        rotateX += 1.0f;
        break;
    case 'S':
    case 's':
        rotateX -= 1.0f;
        break;
    case 'A':
    case 'a':
        rotateY += 1.0f;
        break;
    case 'D':
    case 'd':
        rotateY -= 1.0f;
        break;
    case 'Q':
    case 'q':
        rotateZ += 1.0f;
        break;
    case 'E':
    case 'e':
        rotateZ -= 1.0f;
        break;
    case '+':
        zoom += 0.1f;
        break;
    case '-':
        zoom -= 0.1f;
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    //Init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");


    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glutMainLoop();

    return 0;
}

