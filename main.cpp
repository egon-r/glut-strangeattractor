#include <iostream>
#include <math.h>
#include <GL/freeglut.h>

using std::cout;
using std::endl;

void initFunc();
void displayFunc();
void keyboardFunc(unsigned char key, int x, int y);

// strange attractor
float x = 0.1;
float y = 0.1;
float a = -0.966918; // ?
float b = 2.879879; // ?!
float c = 0.765145; // ??
float d = 0.744728; // ??!
int initialIterations = 100; // ???
int iterations = 1000000;

void attractor_iteration() {
    float xnew = sin(y*b) + c*sin(x*b);
    float ynew = sin(x*a) + d*sin(y*a);
    x = xnew;
    y = ynew;
}


int main(int argc, char const *argv[])
{
    cout << "main" << endl;

    glutInit(&argc, (char**)argv);
    // set up our display mode for color with alpha and double buffering
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    // create a 400px x 400px window
    glutInitWindowSize(400, 400);
    glutCreateWindow("Strange Attractors in C++ and OpenGL");

    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);

    initFunc();

    glutMainLoop();
    return 0;
}

void initFunc() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // background
    glColor4f(1.0f, 1.0f, 1.0f, 0.02f); // foreground (pen) color

    glViewport(0, 0, 400, 400);

    // blending (transparency)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // point smoothing
    glEnable(GL_POINT_SMOOTH);
    glPointSize(1.0f);

    // setup projection matrix (camera)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0f, 2.0f, -2.0f, 2.0f);

    // setup model matrix (objects)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // strange attractor initial iterations to settle into an orbit (?)
    for (int i = 0; i < initialIterations; i++) {
        attractor_iteration();
    }
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT); // clear screen

    glBegin(GL_POINTS);
    for(int i = 0; i < iterations; i++) {
        attractor_iteration();
        glVertex2f(x, y);
    }
    glEnd();

    glutSwapBuffers(); 
}

void keyboardFunc(unsigned char key, int x, int y) {
    cout << "pressed '" << key << "'" << endl;
    if(key == 27) { //esc
        exit(0);
    }  
}