#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include"object.h"
#include"linkedlist.h"
#define pi 3.1415

int s=0;
int s_start=0;
int click_count=0;
int x_initial,y_initial,x_final,y_final;
shape shpe;
void init()
{
    // For displaying the window color
    glClearColor(0, 0, 0, 0);
    glColor3f(1,1,1);
    glPointSize(3);
    // Choosing the type of projection
    glMatrixMode(GL_PROJECTION);
    // for setting the transformation which here is 2D
    gluOrtho2D(0,640,480,0);
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
  //  printf("%d %d\n",s, s_start);

    linkedlist::display();
    if(s==1 && s_start == 1 && click_count%2==1){
        printf("Outer %d %d\t%d %d\n",x_initial,y_initial,x_final,y_final);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if(shpe==RECTANGLE){
            glBegin(GL_POLYGON);
                glVertex2f(x_initial,y_initial);
                glVertex2f(x_initial,y_final);
                glVertex2f(x_final,y_final);
                glVertex2f(x_final,y_initial);
            glEnd();
        }else if(shpe==LINE){
            glBegin(GL_LINES);
                glVertex2f(x_initial,y_initial);
                glVertex2f(x_final,y_final);
            glEnd();
        }else if(shpe==CIRCLE){
            int r = getDistance(x_initial,y_initial,x_final,y_final);
            circle(r,x_initial,y_initial);
        }

    }
    glFlush();

   // Process all OpenGL routine s as quickly as possible
}
void mouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON){
        if(state==GLUT_DOWN){
            click_count++;
            if(click_count%2==0){
                printf("Inner %d %d\t%d %d\n",x_initial,y_initial,x_final,y_final);
                linkedlist::insertfromend(shpe,x_initial,y_initial,x_final,y_final);
            }
            printf("clicked");
            s=0;
            s_start = 1;
            x_initial =x;
            y_initial=y;

        }
    }
}
void passiveMotion(int x, int y)
{
    if(s_start ==1){
        s = 1;
        x_final = x;
        y_final = y;
    }
}

void keyboard(unsigned char key,int x, int y){
    if(key>=65 && key<=90 || key>=97 || key<=122){
        switch (key){
        case 'l':
            shpe = LINE;
            break;
        case 'r':
            shpe = RECTANGLE;
            break;
        case 'c':
            shpe = CIRCLE;
            break;
        default:
            break;
        }
    }
}
void timer(int)
{
    glutPostRedisplay();
    glutPassiveMotionFunc(passiveMotion);
    glutTimerFunc(1000/25,timer,0);
}
int main(int agrc, char ** argv)
{
    // Initialize GLUT
    glutInit(&agrc, argv);
    // Set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Set top - left display window position.
    glutInitWindowPosition(100, 100);
    // Set display window width and height
    glutInitWindowSize(640, 480);
    // Create display window with the given title
    glutCreateWindow("Mini Computer Aided Design");
    // Execute initialization procedure
    init();
    // Send graphics to display window
    glutDisplayFunc(display);
    glutTimerFunc(0,timer,0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    // Display everything and wait.
    glutMainLoop();
}
