#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>


using namespace std;


typedef struct cartoon{
    double flowers[2][4];
}carts;
carts cart[10]={{250.0,200.0,200.0,250.0,300.0,300.0,200.0,200.0},
                {250.0,300.0,300.0,250.0,200.0,200.0,300.0,300.0},
                {250.0,250.0,175.0,220.0,300.0,350.0,325.0,286.0},
                {220.0,175.0,150.0,210.0,286.0,325.0,250.0,250.0},
                {250.0,250.0,325.0,280.0,300.0,350.0,325.0,286.0},
                {280.0,325.0,350.0,290.0,286.0,325.0,250.0,250.0},
                {250.0,250.0,175.0,220.0,200.0,150.0,175.0,220.0},
                {220.0,175.0,150.0,210.0,220.0,175.0,250.0,250.0},
                {250.0,250.0,325.0,280.0,200.0,150.0,175.0,220.0},
                {280.0,325.0,350.0,290.0,220.0,175.0,250.0,250.0}
                };


int way;
double X1,Y1,X2,Y2;
double X3,Y3,X4,Y4;

vector<pair<GLfloat, GLfloat> > points;
//��������bool��������¼�Ƿ��Ѿ������ĸ���֮���ֱ�ߣ��Լ���ر���������
bool line = false;
bool curve = false;

//��ֱ��
void drawLine() {
    glColor3f(1.0f, 0, 0);
    glPointSize(1.0);
    for (int i = 0; i <= 2; i ++) {
        glBegin(GL_LINES);
            glVertex2f(points[i].first, points[i].second);
            glVertex2f(points[i+1].first, points[i+1].second);
        glEnd();
    }
}
GLfloat ctrlpoints[4][4][3] = {
{{-3, 0, 4.0}, {-2, 0, 2.0}, {-1, 0, 0.0}, {0, 0, 2.0}},
{{-3, 1, 1.0}, {-2, 1, 3.0}, {-1, 1, 6.0}, {0, 1, -1.0}},
{{-3, 2, 4.0}, {-2, 2, 0.0}, {-1, 2, 3.0}, {0, 2, 4.0}},
{{-3, 3, 0.0}, {-2, 3, 0.0}, {-1, 3, 0.0}, {0, 3, 0.0}}
};

GLfloat ctrlpoints1[4][4][3] = {
{{-3, 1, 4.0}, {-2, 1, 2.0}, {-1, 0, 0.0}, {0, 0, 2.0}},
{{-3, 1, 1.0}, {-2, 1, 3.0}, {-1, 0, 6.0}, {0, 1, 2.0}},
{{-3, 1, 4.0}, {-2, 1, 0.0}, {-1, 1, 3.0}, {0, 2, 4.0}},
{{-3, 1, 0.0}, {-2, 1, 0.0}, {-1, 1, 0.0}, {0, 3, 0.0}}
};
GLfloat ctrlpoints2[4][4][3] = {{{-3,0,0},{-1,1,0},{0,0,0},{1,-1,0}},
{{-3,0,-1},{-1,1,-1},{0,0,-1},{1,-1,-1}},
{{-3,0,-3},{-1,1,-3},{0,0,-3},{1,-1,-3}},
{{-3,0,-3},{-1,1,-3},{0,0,-3},{1,-1,-3}},
};


void drawCurved_surface(void)
{
    int i, j;
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix ();
    glRotatef(85.0, 1.0, 1.0, 1.0);
    for (j = 0; j <= 20; j++)
    {
        glBegin(GL_LINE_STRIP);
        for (i = 0; i <= 20; i++)
            glEvalCoord2f((GLfloat)i/20.0, (GLfloat)j/20.0); //������ֵ��
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (i = 0; i <= 20; i++)
            glEvalCoord2f((GLfloat)j/20.0, (GLfloat)i/20.0); //������ֵ��
        glEnd();
    }
    glPopMatrix ();

}
//����������
void drawCurve_flower() {
    glColor3f(0, 1.0f, 0);
    glPointSize(1.0);
    for(int i=0;i<10;i++)
    {
        for (GLfloat t = 0; t <= 1.0; t += 0.001) {
            double x = cart[i].flowers[0][0]*pow(1.0f-t, 3)+3*cart[i].flowers[0][1]*t*pow(1.0f-t, 2) + 3*cart[i].flowers[0][2]*t*t*(1.0f-t) + cart[i].flowers[0][3]*pow(t, 3);
            double y = cart[i].flowers[1][0]*pow(1.0f-t, 3)+3*cart[i].flowers[1][1]*t*pow(1.0f-t, 2) + 3*cart[i].flowers[1][2]*t*t*(1.0f-t) + cart[i].flowers[1][3]*pow(t, 3);
            glBegin(GL_POINTS);
                glVertex2f(x, y);
            glEnd();
        }
    }
}

void drawCurve_m() {
     glColor3f(0, 1.0f, 0);
      glPointSize(1.0);
      for (GLfloat t = 0; t <= 1.0; t += 0.001) {
        GLfloat x = points[0].first*pow(1.0f-t, 3) + 3*points[1].first*t*pow(1.0f-t, 2) + 3*points[2].first*t*t*(1.0f-t) + points[3].first*pow(t, 3);
        GLfloat y =  points[0].second*pow(1.0f-t, 3) + 3*points[1].second*t*pow(1.0f-t, 2) + 3*points[2].second*t*t*(1.0f-t) + points[3].second*pow(t, 3);
        glBegin(GL_POINTS);
              glVertex2f(x, y);
         glEnd();
      }
 }

void drawCurve(double X1,double Y1,double X2,double Y2,double X3,double Y3,double X4,double Y4) {
    glColor3f(0, 1.0f, 0);
    glPointSize(1.0);
    for (GLfloat t = 0; t <= 1.0; t += 0.001) {
        double x = X1*pow(1.0f-t, 3)+3*X2*t*pow(1.0f-t, 2) + 3*X3*t*t*(1.0f-t) + X4*pow(t, 3);
        double y = Y1*pow(1.0f-t, 3)+3*Y2*t*pow(1.0f-t, 2) + 3*Y3*t*t*(1.0f-t) + Y4*pow(t, 3);
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }
}

//��ʼ������
void myInit() {
    glClearColor(0, 0, 0, 0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);   //��������溯��
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);   //����ƽ��ͶӰ����
    glColor3f(1.0f, 0, 0);
    glPointSize(5.0);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);

}
void myMouse(int button, int state, int x, int y)
{

    //����������
     if(state==GLUT_DOWN)
     {
        //��4����
        if (points.size() < 4) {
            glBegin(GL_POINTS);
                glVertex2i(x, 500 - y);
            glEnd();
            points.push_back(make_pair(GLfloat(x), GLfloat(500 - y)));
        }
        //���Ѿ������ĸ��㣬��ʼ�������ɵ��߶�\����
        else if (points.size() == 4) {
            //�߶�
            if (line == false) {
                drawLine();
                line = true;
            }
            //����
            else if (line == true && curve == false) {
                drawCurve_m();
                curve = true;
            }
            //���
            else if (line == true && curve == true) {
                glClear(GL_COLOR_BUFFER_BIT);
                glColor3f(1.0f, 0, 0);
                glPointSize(5.0);
                line = false;
                curve = false;
                while(!points.empty()) {
                    points.pop_back();
                }
            }
        }
        glFlush();
     }
 }

 void menuOption(GLint option)
{
	switch (option)
	{
	  case 1:{

        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
        drawCurved_surface();
        glFlush();
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_STENCIL_BUFFER_BIT);

    } break;

	  case 2:{
	      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints1[0][0][0]);
        drawCurved_surface();
        glFlush();
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_STENCIL_BUFFER_BIT);
		 }
		  break;
	  case 3:{
	      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints2[0][0][0]);
        drawCurved_surface();
        glFlush();
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_STENCIL_BUFFER_BIT);
		 }
		  break;

	}
}
 void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(way==1)
    {
        glLoadIdentity();   //��λ����
        gluOrtho2D(0.0, 500, 0.0, 500);
        drawCurve(X1,Y1,X2,Y2,X3,Y3,X4,Y4);
        glFlush();
    }
    else if(way==2)
    {
        glLoadIdentity();
        gluOrtho2D(0.0, 500, 0.0, 500);
        drawCurve_flower();
        //���ľ�
        drawCurve(250.0,200.0,220.0,132.0,280.0,66.0,250.0,0.0);
        //��Ҷ
        drawCurve(245.0,132.0,245.0,152.0,170.0,152.0,150.0,132.0);
        drawCurve(245.0,132.0,245.0,112.0,170.0,112.0,150.0,132.0);
        drawCurve(255.0,66.0,255.0,86.0,320.0,86.0,340.0,66.0);
        drawCurve(255.0,66.0,255.0,46.0,320.0,46.0,340.0,66.0);
        glFlush();
    }
    else if(way==3)
    {
        glLoadIdentity();
        gluOrtho2D(0.0, 500, 0.0, 500);
        glClearColor(0, 0, 0, 0);
        glutMouseFunc(myMouse);

    }
    else if(way==4)
    {
        glutCreateMenu(menuOption);     //�����˵�
        glutAddMenuEntry("��һ������", 1);
        glutAddMenuEntry("�ڶ�������", 2);
        glutAddMenuEntry("����������", 3);
        glutAttachMenu(GLUT_LEFT_BUTTON);
        drawCurved_surface();
        glFlush();
        glClear(GL_COLOR_BUFFER_BIT);//�������
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_STENCIL_BUFFER_BIT);
    }
}


int main(int argc, char** argv) {


    cout<<"....................."<<endl;
    cout<<"      ��ӭʹ��       "<<endl;
    cout<<"1.���ױ��������߻��� "<<endl;
    cout<<"2.ʹ�����ױ��������߻��ƵĻ���"<<endl;
    cout<<"3.ʹ�����������ױ��������߻���"<<endl;
    cout<<"4.�������������"<<endl;
    cout<<"��������ţ�"<<endl;
    while(1)
    {
        scanf("%d",&way);
        if(way!=1&&way!=2&way!=3&&way!=4)
        {
            cout<<"ָ����������밴�˵���ʾ���룡"<<endl;
            continue;
        }
        break;
    }
    while(1)
    {
        if(way==1)
        {
            cout<<"�������ĸ�����(x��y���ֵΪ500����СֵΪ0)��"<<endl;
            scanf("%lf %lf %lf %lf",&X1,&Y1,&X2,&Y2);
            scanf("%lf %lf %lf %lf",&X3,&Y3,&X4,&Y4);
            if(X1<0||X2<0||X3<0||X4<0||Y1<0||Y2<0||Y3<0||Y4<0)
            {
                cout<<"�����������������"<<endl;
                continue;
            }
            break;

        }
        break;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    if(way==1)
        glutCreateWindow("���ױ��������߻���");
    else if(way==2)
        glutCreateWindow("���ƻ���");
    else if(way==3)
        glutCreateWindow("���ױ���������������");
    else if(way==4)
        glutCreateWindow("���ױ������������");
    myInit();
    glutDisplayFunc (myDisplay);
    glutMainLoop();


    return 0;
}
