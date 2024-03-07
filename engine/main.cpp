#include "main.h"

Camera* camera = new Camera();

bool axis = true;

void drawAxis() {
	glBegin(GL_LINES);

	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);		

    // Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);

    // Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);

	glEnd();

}

void renderScene(void) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camera->pos[0], camera->pos[1], camera->pos[2],
        camera->lookAt[0], camera->lookAt[1], camera->lookAt[2],
        camera->up[0], camera->up[1], camera->up[2]);


    //draw instructions
    if (axis) drawAxis();

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
	gluPerspective(camera->projection[0], ratio, camera->projection[1], camera->projection[2]);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        camera->rotate[0] += 1.0f;
        break;
    case 'S':
    case 's':
        camera->rotate[0] -= 1.0f;
        break;
    case 'A':
    case 'a':
        camera->rotate[1] += 1.0f;
        break;
    case 'D':
    case 'd':
        camera->rotate[1] -= 1.0f;
        break;
    case 'Q':
    case 'q':
        camera->rotate[2] += 1.0f;
        break;
    case 'E':
    case 'e':
        camera->rotate[2] -= 1.0f;
        break;
    case '+':
        camera->zoom += 0.1f;
        break;
    case '-':
        camera->zoom -= 0.1f;
        break;
    case '1':
        axis = !axis;
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    Window* window = new Window();
    camera = new Camera();
    Group* group = new Group();
   
    //Init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window->height,window->width);
    glutCreateWindow("CG@DI-UM");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glutMainLoop();

    return 0;
}

