#include "main.h"
#include "parser.h"
#include <cstdlib>

Camera* camera = new Camera();
Group* group = new Group();
vector <Lights*> lights;

bool axis = true;

int first = 0;

const float CAMERA_SPEED = 10.0f;
float prev_y[3] = {0, 1, 0};
float tesselation = 100.0f;

GLuint buffers[1];
void buildRotMatrix(float* x, float* y, float* z, float* m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}
void normalize(float* a) {

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}
void multMatrixVector(float m[4][4], float* v, float* res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
        }
    }
}

void cross(float* a, float* b, float* res) {
    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}

void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv) {

    float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
                        { 1.0f, -2.5f,  2.0f, -0.5f},
                        {-0.5f,  0.0f,  0.5f,  0.0f},
                        { 0.0f,  1.0f,  0.0f,  0.0f} };

    for (int i = 0; i < 3; i++) {	 // i = x, y,
        float p[4] = { p0[i], p1[i], p2[i], p3[i] };
        float a[4];

        multMatrixVector(m, p, a);

        pos[i] = powf(t, 3.0) * a[0] + powf(t, 2.0) * a[1] + t * a[2] + a[3];
        deriv[i] = 3 * powf(t, 2.0) * a[0] + 2 * t * a[1] + a[2];
    }
}

void getGlobalCatmullRomPoint(Group* g, float gt, float* pos, float* deriv) {
    int pointCount = g->catPoints.size();

    float t = gt * pointCount; 
    int index = floor(t); 
    t = t - index;

    int indices[4];
    indices[0] = (index + pointCount - 1) % pointCount;
    indices[1] = (indices[0] + 1) % pointCount;
    indices[2] = (indices[1] + 1) % pointCount;
    indices[3] = (indices[2] + 1) % pointCount;

    getCatmullRomPoint(t, g->catPoints[indices[0]], g->catPoints[indices[1]], g->catPoints[indices[2]], g->catPoints[indices[3]], pos, deriv);
}

void renderCatmullRomCurve(Group* g) {
    float pos[3];
    float deriv[3];
    
    glBegin(GL_LINE_LOOP);
    float gt = 0;

    while (gt < 1) {
        getGlobalCatmullRomPoint(g, gt, pos, deriv);
        glVertex3f(pos[0], pos[1], pos[2]);
        gt += 1.0 / tesselation;
    }
    glEnd();
}

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

void renderGroup(Group* g) {
    glPushMatrix();

    for (int& code : g->torder) {
        float t;

        if (code == 3 || code == 4) {
            t = remainder(glutGet(GLUT_ELAPSED_TIME) / 1000.0f, g->tesselation);
            if (t < 0) {
                t = (t + g->tesselation) / g->tesselation;
            }
            else {
                t = t / g->tesselation;
            }
        }

        if (code == 0) {
            glTranslatef(g->tx, g->ty, g->tz);
        }
        else if (code == 1) {
            glRotatef(g->ralpha, g->rx, g->ry, g->rz);
        }
        else if (code == 2){
            glScalef(g->sx, g->sy, g->sz);
        }
        else if (code == 3) {
            renderCatmullRomCurve(g);
            float pos[3];
            float deriv[3];
            getGlobalCatmullRomPoint(g, t, pos, deriv);
            glTranslatef(pos[0], pos[1], pos[2]);

            float x[3] = { deriv[0], deriv[1], deriv[2] };
            normalize(x);
            float z[3];
            cross(x, prev_y, z);
            normalize(z);
            float y[3];
            cross(z, x, y);
            normalize(y);
            memcpy(prev_y, y, 3 * sizeof(float));
            float m[16];
            buildRotMatrix(x, y, z, m);
            glMultMatrixf(m);
        }
        else if (code == 4) {
            glRotatef(360 * t, g->timerx, g->timery, g->timerz);
        }
    }
    for (size_t  i = 0; i < g->model.size(); ++i) {
        Color* color = g->color[i];
        float diffuseColor[4] = { color->diffuseR, color->diffuseG, color->diffuseB, 1.0 };
        cout << color->diffuseR<<"\n";
        cout << color->diffuseG << "\n";
        cout << color->diffuseB << "\n";
        float ambientColor[4] = { color->ambientR, color->ambientG, color->ambientB, 1.0 };
        float specularColor[4] = { color->specularR, color->specularG, color->specularB, 1.0 };
        float emissiveColor[4] = { color->emissiveR,color->emissiveG,color->emissiveB,1.0 };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
        glMaterialfv(GL_FRONT, GL_EMISSION, emissiveColor);
        glMaterialf(GL_FRONT, GL_SHININESS, color->shininessValue);

        glDrawArrays(GL_TRIANGLES, first / 3, g->model[i] / 3);

        first += g->model[i];   
    }

    for (Group*& subgroup : g->groups) {
        renderGroup(subgroup);
    }
    glPopMatrix();
}

void renderScene(void) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // set the camera
    glLoadIdentity();
    gluLookAt(camera->pos[0] - camera->zoom, camera->pos[1] - camera->zoom, camera->pos[2] - camera->zoom,
        camera->lookAt[0], camera->lookAt[1], camera->lookAt[2],
        camera->up[0], camera->up[1], camera->up[2]);

    glRotatef(camera->rotate[0], 1.0f, 0.0f, 0.0f);
    glRotatef(camera->rotate[1], 0.0f, 1.0f, 0.0f);
    glRotatef(camera->rotate[2], 0.0f, 0.0f, 1.0f);

    first = 0;

    //draw instructions
    if (axis) drawAxis();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    renderGroup(group);

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
        camera->rotate[0] += CAMERA_SPEED;
        break;
    case 'S':
    case 's':
        camera->rotate[0] -= CAMERA_SPEED;
        break;
    case 'A':
    case 'a':
        camera->rotate[1] += CAMERA_SPEED;
        break;
    case 'D':
    case 'd':
        camera->rotate[1] -= CAMERA_SPEED;
        break;
    case 'Q':
    case 'q':
        camera->rotate[2] += CAMERA_SPEED;
        break;
    case 'E':
    case 'e':
        camera->rotate[2] -= CAMERA_SPEED;
        break;
    case '+':
        camera->zoom += CAMERA_SPEED;
        break;
    case '-':
        camera->zoom -= CAMERA_SPEED;
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

    vector<float> points;

    parser(argv[1], &lights, window, camera, group, &points);
    //Init
    glutInit(&argc, argv);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
    float white[4] = { 1.0, 1.0, 1.0, 1.0 };
    float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    int i = 0;
    for (Lights* l : lights) {
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, dark);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, white);

        float pos[4] = { l->posX, l->posY, l->posZ, 1.0f };
        float dir[4] = { l->dirX, l->dirY, l->dirZ, 0.0f };

        if (l->type == 2) {
            glLightfv(GL_LIGHT0 + i, GL_POSITION, dir);
        }
        else {
            glLightfv(GL_LIGHT0 + i, GL_POSITION, pos);
        }

        if (l->type == 3) {
            glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, dir);
            glLightfv(GL_LIGHT0 + i, GL_SPOT_CUTOFF, &l->cutoff);
        }
        i++;
    }
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window->height, window->width);
    glutCreateWindow("CG@DI-UM");

    glewInit();

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyboard);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);

    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

    glVertexPointer(3, GL_FLOAT, 0, 0);

    glutMainLoop();

    return 0;
}
