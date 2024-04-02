#include "main.h"
#include "parser.h"
#include <cstdlib>

Camera* camera = new Camera();
Group* group = new Group();

bool axis = true;

GLuint buffers[1];

void drawAxis() {
	glBegin(GL_LINES);

	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);

    // Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);

    // Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
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
    glPushMatrix();
    glTranslatef(group->tx, group->ty, group->tz);
    glPopMatrix();
    glPushMatrix();
    glRotatef(group->rotatealpha, group->rx, group->ry, group->rz);
    glPopMatrix();
    glPushMatrix();
    glScalef(group->sx, group->sy, group->sz);
    glPopMatrix();

    //draw instructions
    if (axis) drawAxis();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int first = 0;
    for (int i = 0; i < group->model.size(); i++) {
        glDrawArrays(GL_TRIANGLES, first, group->model[i]);
        first += group->model[i];
    }
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
    group = new Group();

    vector<float> temp_points;

    parser(argv[1], window, camera, group, &temp_points);

    float* points = (float*)malloc(temp_points.size()*sizeof(float));

    for (int i = 0; i < temp_points.size(); i++) {
        points[i] = temp_points[i];
    }
   
    //Init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window->height,window->width);
    glutCreateWindow("CG@DI-UM");

    glewInit();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);

    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, temp_points.size()*sizeof(float), points, GL_STATIC_DRAW);

    glVertexPointer(3, GL_FLOAT, 0, 0);

    glutMainLoop();

    return 0;
}

