#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include<math.h>
#include<windows.h>
#include<GL/glu.h>
#include<GL/glut.h>
#define pi 3.1415
enum shape{LINE, RECTANGLE, CIRCLE};
float getDistance(int x1, int y1, int x2, int y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
void circle(int r, int xc, int yc){
    int x, y;
    glBegin(GL_POINTS);
    for(float i=0;i<2*pi;i+=.01){
        x = r*cos(i);
        y = r*sin(i);
        glVertex2i(x+xc,y+yc);
    }
    glEnd();
}

class object{
    int x_initial;
    int y_initial;
    int x_final;
    int y_final;
    shape s;
    object *next;
public:
    object(shape sp){
        this->s = sp;
    }
    void setInital(int x, int y)
    {
        x_initial = x;
        y_initial = y;
    }
    void setFinal(int x, int y)
    {
        x_final = x;
        y_final = y;
    }
    void drawObject(){
        if(s == LINE){
            glBegin(GL_LINES);
                glVertex2f(x_initial,y_initial);
                glVertex2f(x_final,y_final);
            glEnd();
        }else if(s== RECTANGLE){
            glBegin(GL_QUADS);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glVertex2f(x_initial,y_initial);
                glVertex2f(x_initial,y_final);
                glVertex2f(x_final,y_final);
                glVertex2f(x_final,y_initial);
            glEnd();
        }else if(s==CIRCLE){
            int r = getDistance(x_initial,y_initial,x_final,y_final);
            circle(r,x_initial,y_initial);
        }
        debugger();
    }
    void setNext(object *o)
    {
        this->next = o;
    }
    object* getNext()
    {
        return this->next;
    }
    void debugger(){
        printf("debugger %d %d %d %d %d\n",x_initial,y_initial,x_final,y_final,s);
    }
};

#endif // OBJECT_H_INCLUDED
