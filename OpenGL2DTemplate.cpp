//  Includes
#include <stdio.h>
#include <math.h>
#include <random>
#include <glut.h>
#include <iostream>
using namespace std;
//-----------------

//  Methods Signatures
void drawRect(int x, int y, int w, int h);
void drawCircle(int x, int y, float r);
void Key(int key, int x, int y);
//void KeyUp(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Timer1(int value);
void Display();
void update(int value);
void update2(int value);
void update5(int value);
bool returnk = false;
int power = 250;

bool protect = false;
//-----------------
int herolife = 3;
//  Global Variables
int xreq = 715;
int xrandom = 0;
int yrandom = 0;
bool direction = true;
int yreq = 120;
int xcir1 = 725;
int ycir1 = 112;
int xcir2 = 805;
int ycir2 = 112;
int xenemy = 650;
int xenmeycir1 = 0;
int xenemycir2 = 0;
int yenmeycir1 = 0;
int yenemycir2 = 0;

int yenemy = 700;
vector<pair<int, int >> bullet_enemy;
vector<pair<int, int >> bullet_hero;

/*int xenemycir = 0;
int yenmeycir = 0;
int xenemycir = 0;
int yenmeycir = 0;
*/
int selectedBar = 0; // used to determine which bar has the mouse currently over it
int bar1Y = 0;       // holds the Y translation value of bar 1
int bar2Y = 0;       // holds the Y translation value of bar 2
int bar3Y = 0;       // holds the Y translation value of bar 3
int ballY = 0;       // holds the value of the Y coordinate of the ball
//-----------------
void print(int x, int y, char* string)
{
    int len, i;

    //set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x, y);

    //get the length of the string to display
    len = (int)strlen(string);

    //loop to display character by character
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}

void main(int argc, char** argr) {
    glutInit(&argc, argr);

    glutInitWindowSize(1500, 800);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("assingment");
    glutDisplayFunc(Display);
        // sets the Keyboard handler function; called when a key is pressed
    glutSpecialFunc(Key);  // sets the KeyboardUp handler function; called when a key is released
   // glutMouseFunc(Mouse);       // sets the Mouse handler function; called when a mouse button is clicked
    glutTimerFunc(0, Timer, 0); // sets the Timer handler function; which runs every `Threshold` milliseconds (1st argument)
  glutTimerFunc(0, Timer1, 0);
   glutTimerFunc(0, update, 0);
   glutTimerFunc(0, update5, 0);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(1, 1, 1, 0);
    gluOrtho2D(0, 1500, 0, 800);

    glutMainLoop();
}

// draws rectangles using the (x,y) of the bottom left vertex, width (w) and height (h)
void drawRect(int x, int y, int w, int h) {
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

// draws a circle using OpenGL's gluDisk, given (x,y) of its center and tis radius
void drawCircle(int x, int y, float r) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    GLUquadric* quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, 50, 50);
    glPopMatrix();
}

// Keyboard handler function
//   key: the key pressed on the keyboard
//   x  : the X coordinate of the mouse cursor at the moment of pressing the key
//   y  : the Y coordinate of the mouse cursor at the moment of pressing the key
void Key(int  key, int x, int y) {
    // pick a bar based on the X position of the mouse, assuming the window is divided into 3 vertical slices

    // check the selected bar, to decide which variable to control: bar1Y, bar2Y or bar3Y
    switch (key) {
    case  102:
    {
        xreq += 15;
        xcir1 += 15;
        xcir2 += 15;
        break;
    }
    case 100:
    {
        xreq -= 15;
        xcir1 -= 15;
        xcir2 -= 15;
        break;
    }
    case 101:
    {
        yreq += 15;
        ycir1 += 15;
        ycir2 += 15;
        break;

    }
    case 103:
    {
        yreq -= 15;
        ycir1 -= 15;
        ycir2 -= 15;
        break;
    }
    case 108: {
        pair<int, int> add;
        add.first = xreq+40;
        add.second = yreq+20;
        bullet_hero.push_back((add));
    }

    }

    // ask OpenGL to recall the display function to reflect the changes on the window
   // glutPostRedisplay();
}

// KeyboardUp handler function
//   similar to the Keyboard handler function except that it is called only when the key is released
void KeyUp(unsigned char key, int x, int y) {
    // reset the selectedBar value to 0 to unselect the selected bar
    selectedBar = 0;

    // ask OpenGL to recall the display function to reflect the changes on the window
    glutPostRedisplay();
}

// Mouse handler function
//   button: the mouse button clicked: left, right or middle
//   state:  the state of the button: clicked (down) or released (up)
//   x  : the X coordinate of the mouse cursor at the moment of clicking the mouse button
//   y  : the Y coordinate of the mouse cursor at the moment of clicking the mouse button


void Timer(int value) {
    int speed = 80;

    // set the ball's Y coordinate to a random number between 10 and 780 (since the window's height is 800)
    if (xenemy + speed > 1300) {
        direction = false;
    }
    if (xenemy - speed < 0) {
        direction = true;
    }
    if (direction) {
        xenemy += speed;
    }
    else {
        xenemy -= speed;
    }
    // ask OpenGL to recall the display function to reflect the changes on the window
    glutPostRedisplay();

    // recall the Timer function after 20 seconds (20,000 milliseconds)
    glutTimerFunc(.3 * 1000, Timer, 0);
}
void Timer1(int value) {
    pair<int, int> add;
    add.first = xenemy;
    add.second = 690;
    bullet_enemy.push_back((add));
    // ask OpenGL to recall the display function to reflect the changes on the window
    glutPostRedisplay();

    // recall the Timer function after 20 seconds (20,000 milliseconds)
    glutTimerFunc(5 * 1000, Timer1, 0);
}
void update(int value) {
    // set the ball's Y coordinate to a random number between 10 and 780 (since the window's height is 800)
    xrandom = rand() % 1400 + 10;
    yrandom = rand() % 600 + 10;
    // ask OpenGL to recall the display function to reflect the changes on the window
    glutPostRedisplay();
    protect = false;
    // recall the Timer function after 20 seconds (20,000 milliseconds)
    glutTimerFunc(10 * 1000, update, 0);
}
void update5(int value) {
    // set the ball's Y coordinate to a random number between 10 and 780 (since the window's height is 800)
   
    // ask OpenGL to recall the display function to reflect the changes on the window
    glutPostRedisplay();

    // recall the Timer function after 20 seconds (20,000 milliseconds)
    glutTimerFunc(.1 * 1000, update5, 0);
}
void update2(int value) {
    // set the ball's Y coordinate to a random number between 10 and 780 (since the window's height is 800)
    protect = false;
    // ask OpenGL to recall the display function to reflect the changes on the window
    glutPostRedisplay();

    // recall the Timer function after 20 seconds (20,000 milliseconds)
    
}



void Display() {
    glClear(GL_COLOR_BUFFER_BIT);



    //glPushMatrix();


    // if the mouse is over the 1st bar, color it yellow, otherwise black
    if (protect)
        glColor3f(1, 1, 0);
    else
        glColor3f(0, 0, 0);

    drawRect(xreq, yreq, 100, 30); // rectangle 1w
    glPushMatrix();
   

    glTranslatef(0, 0, 0);
    glPopMatrix();
    drawCircle(xcir1, ycir1, 10);
    drawCircle(xcir2, ycir2, 10);
    drawRect(xcir1, ycir1, 80, 3);

    glColor3f(1, 0, 0);
    if (xrandom > xreq && xrandom + 20 < xreq + 100 && yrandom > yreq && yrandom < yreq + 60||protect) {
        protect = true;
    }
    else {
        drawRect(xrandom, yrandom, 20, 20);
    }
   
   
    glColor3f(1, 0, 0);
    drawRect(20, 750, power, 20);

    glColor3f(0, 1, 0);
    drawRect(xenemy, yenemy, 200, 45);
    drawCircle(xenemy + 20, yenemy + 65, 15);
    drawCircle(xenemy + 180, yenemy + 65, 15);
    drawRect(xenemy + 20, yenemy + 65, 160, 5);
  
    glColor3f(0, .3, .3);
    for (auto i = bullet_enemy.begin(); i != bullet_enemy.end();) {
        pair<int, int> a = *i;
        if (a.second < 0) {
            i = bullet_enemy.erase(i);
            continue;
        }
        if (a.first > xreq && a.first + 20 < xreq + 100 && a.second > yreq && a.second < yreq + 60) {
            if (!protect)
            herolife--;
            if (herolife==0) {
                print(500, 500, "the game end and you lost");
                glutCreateWindow("assingment");
                exit(0);
            }
            i=bullet_enemy.erase(i);
        }
        else {

            drawRect(a.first, a.second, 20, 20);
            a.second -= 15;
            *i = a;
            i++;
        }
        
  }
    glColor3f(1, 1, 0);
    for (int i = 0;i < herolife;i++) {
        drawCircle(8+i * 20,  20,8 );
    }

 
    for (auto i = bullet_hero.begin(); i != bullet_hero.end();) {
        pair<int, int> a = *i;
        
        if (a.second > 800) {
            i = bullet_hero.erase(i);
            continue;
        }
        if ((a.first > xenemy && a.first+20  < xenemy + 200) && (a.second+30 >= yenemy )) {
            i = bullet_hero.erase(i);
            power -= 25;
            if (power == 0) {
                print(500, 500, "the game end and you win");
                glutCreateWindow("assingment");
                exit(0);
            }
           
        }
        
        else {

                drawRect(a.first, a.second, 20, 20);
                a.second += 30;
                *i = a;
                i++;
           
               
            
        }

    }


    /*glTranslatef(0, yreq, 0);
    glTranslatef(0, xcir1, 0);
    glTranslatef(0, xcir2, 0);
    glTranslatef(0, ycir1, 0);
    glTranslatef(0, ycir2, 0);




    // draw the 1st vertical rectangle, which is fixed and won't move



    /**
    * note:
    *   read the next comments from down to up, since we are dealing with stacks to handle transformations (LIFO).
    *   the comments are numbered to help you read them in the correct order
    *   3 nested stacks are used to handle the 3 parts of the arm, which look like that:
    *
    *
    *    Draw Rect 1
    *
    *    Stack 3 Push <-------------------.
    *      Translate Bar 1                |
    *      Draw Rect 2                    |
    *                                     |
    *      Stack 2 Push <-------------.   |
    *        Translate Bar 2          |   |
    *        Draw Rect 3 and 4        |   |
    *                                 |   |
    *        Stack 1 Push <-------.   |   |
    *          Translate Bar 3    |   |   |
    *          Draw Rect 5 and 6  |   |   |
    *                             |   |   |
    *        Stack 1 Pop  <------'    |   |
    *      Stack 2 Pop  <------------'    |
    *    Stack 3 Pop  <------------------'
    *
    * order of execution:
    *  1. Draw Rect 5 and 6
    *  2. Translate Bar 3
    *  3. Draw Rect 3 and 4
    *  4. Translate Bar 2
    *  5. Draw Rect 2
    *  6. Translate Bar 1
    */

    //===== 3. create a new stack to control the 1st part of the arm (rectangles 2 and 3)
    //         since this is a stack, rectangles 4, 5 and 6 will be already drawn and will translate with rectangles 2 and 3


    glFlush();
}
