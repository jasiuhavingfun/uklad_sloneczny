#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <string>
#define pi 3.1415926535
static bool spinning = true;

class Planeta {
public:
    double x;
    double y;
    int red;
    int green;
    int blue;
    double radius;
    GLfloat distanceTOsun;
    double vol;
    int state;
    double delta;

    Planeta(int red, int green, int blue, GLfloat radius, GLfloat distanceTOsun, double vol) {

        this->x = .0f;
        this->y = .0f;
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->radius = radius;
        this->distanceTOsun = distanceTOsun;
        this->vol = vol;
        this->state = -1;
        this->delta = 0;

    }

    void rysuj() {

        GLfloat twicePi = 2.0f * pi;
        int ilosc = 40;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(this->red, this->green, this->blue);
        glVertex2f(this->x, this->y);
        for (int i = 0; i <= ilosc; i++) {
            glVertex2f(
                this->x + (this->radius * cos(i * twicePi / ilosc)),
                this->y + (this->radius * sin(i * twicePi / ilosc))
            );
        }

        glEnd();
    }

    void orbita() {
        GLfloat twicePi = 2.0f * pi;
        int ilosc = 40;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(255, 255, 255);
        glVertex2f(0.0, 0.0);
        for (int i = 0; i <= ilosc; i++) {
            glVertex2f(
                0.0 + (this->distanceTOsun * cos(i * twicePi / ilosc)),
                0.0 + (this->distanceTOsun * sin(i * twicePi / ilosc))
            );
        }

        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(0, 0, 0);
        glVertex2f(0.0, 0.0);
        for (int i = 0; i <= ilosc; i++) {
            glVertex2f(
                0.0 + ((this->distanceTOsun - .004) * cos(i * twicePi / ilosc)),
                0.0 + ((this->distanceTOsun - .004) * sin(i * twicePi / ilosc))
            );
        }

        glEnd();
    }

    void ruch() {

        switch (this->state) {
        case 1:
            if (this->delta < 180)
                this->delta -= this->vol;
            else
                this->state = -1;
            break;
        case -1:
            if (this->delta > -180)
                this->delta += this->vol;
            else
                this->state = 1;
            break;
        }

        this->x = this->distanceTOsun * cos(this->delta);
        this->y = this->distanceTOsun * sin(this->delta);
    }

    void ruchksiazycowy(double x, double y) {

        switch (this->state) {
        case 1:
            if (this->delta < 180)
                this->delta -= this->vol;
            else
                this->state = -1;
            break;
        case -1:
            if (this->delta > -180)
                this->delta += this->vol;
            else
                this->state = 1;
            break;
        }

        this->x = x + this->distanceTOsun * cos(this->delta);
        this->y = y + this->distanceTOsun * sin(this->delta);
    }

    void pierscien() {
        GLfloat twicePi = 2.0f * pi;
        int ilosc = 40;

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(255, 255, 255);
        glVertex2f(this->x, this->y);
        for (int i = 0; i <= ilosc; i++) {
            glVertex2f(
                this->x + (this->radius * 1.6 * cos(i * twicePi / ilosc)),
                this->y + (this->radius * 1.6 * sin(i * twicePi / ilosc))
            );
        }

        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(0, 0, 0);
        glVertex2f(this->x, this->y);
        for (int i = 0; i <= ilosc; i++) {
            glVertex2f(
                this->x + ((this->radius * 1.6 - .004) * cos(i * twicePi / ilosc)),
                this->y + ((this->radius * 1.6 - .004) * sin(i * twicePi / ilosc))
            );
        }

        glEnd();
    }

};


Planeta Slonce(255, 232, 36, 0.055f, .0f, .0);  // R B G srednica odleglosc_od_slonca predkosc 
Planeta Merkury(202, 133, 7, 0.017f, 0.1f, 0.077);
Planeta Wenus(247, 198, 110, 0.025f, 0.2f, 0.05);
Planeta Ziemia(85, 215, 208, 0.03f, 0.3f, 0.03);
Planeta Mars(248, 76, 37, 0.02f, 0.4f, 0.024);
Planeta Jowisz(175, 147, 82, 0.042f, 0.5f, 0.017);
Planeta Saturn(188, 173, 60, 0.042f, 0.65f, 0.008);
Planeta Uran(154, 243, 245, 0.035f, .75f, 0.004);
Planeta Neptun(67, 140, 238, 0.035f, 0.88f, 0.0025);

Planeta ksiezyc(52, 73, 94, 0.013f, .06f, 0.05); // R B G srednica odleglosc_od_planety predkosc 


void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);

    if (spinning) {
        Merkury.ruch();
        Wenus.ruch();
        Ziemia.ruch();
        Mars.ruch();
        Jowisz.ruch();
        Saturn.ruch();
        Uran.ruch();
        Neptun.ruch();

        ksiezyc.ruchksiazycowy(Ziemia.x, Ziemia.y);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    Neptun.orbita();
    Uran.orbita();
    Saturn.orbita();
    Jowisz.orbita();
    Mars.orbita();
    Ziemia.orbita();
    Wenus.orbita();
    Merkury.orbita();

    Slonce.rysuj();
    Merkury.rysuj();
    Wenus.rysuj();
    Ziemia.rysuj();
    Mars.rysuj();

    Jowisz.rysuj();
    Saturn.pierscien(); //!!!!!!!!!!!!!!!!!!!!
    Saturn.rysuj();
    Uran.rysuj();
    Neptun.rysuj();

    ksiezyc.rysuj();


    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        spinning = true;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        spinning = false;
    }
}

void reshape(int width, int height)
{

    if (width > height)
    {
        glViewport((width - height) / 2, 0, height, height); // x, y, width, height
    }
    else
        glViewport(0, (height - width) / 2, width, width);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);


    glutInitWindowSize(650, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Uk³ad S³oneczny: Ziarkowski, Widuch, Wid³o");

    glutDisplayFunc(display);

    glutTimerFunc(100, timer, 0);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);

    glutMainLoop();
}