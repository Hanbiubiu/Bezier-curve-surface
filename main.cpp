#define _WCHAR_T_DEFINED
#define _STDCALL_SUPPORTED
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


int i;
void circle(int x,int y,int x0,int y0)
{							//绘制1/8圆和它的7个对称点
	glVertex2f(x0+x,y0+y);
	glVertex2f(x0+y,y0+x);
	glVertex2f(x0+y,y0-x);
	glVertex2f(x0+x,y0-y);
	glVertex2f(x0-x,y0-y);
	glVertex2f(x0-y,y0-x);
	glVertex2f(x0-y,y0+x);
	glVertex2f(x0-x,y0+y);
}
void Breseham(int x0,int y0,double r)//Bresham法绘制圆形
{
	int x=0;
	int y=(int)r;	//第一个点坐标
	int d=int(3-2*r);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POINTS);
	while(y>=x)		//绘制的是1/8园，所以终点处x=y;
	{
		circle(x,y,x0,y0);
		if(d<0)
			d+=4*x+6;
		else
		{
			d+=4*(x-y)+10;
			y--;
		}
		x++;
	}
	glEnd();
}
void midpoint_circle(int x0,int y0,double r)
{
	int x=0;
	int y=(int)r;	//第一个点坐标
	int d=1-r;
	glColor3f(0.0,1.0,0.0);	//绘制首点
	glBegin(GL_POINTS);
	while(y>=x)		//绘制的是1/8园，所以终点处x=y;
	{
		circle(x,y,x0,y0);
		if(d<0)
			d+=2*x+3;
		else
		{
			d+=2*(x-y)+5;
			y--;
		}
		x++;
	}
	glEnd();
}

void display(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	Breseham(500,500,200.0);	//制定圆的大小
	glFlush();
}
void display1(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	midpoint_circle(500,500,200.0);	//制定圆的大小
	glFlush();
}
int main(int argc,char* argv[])
{
    printf("请选择画圆方法：\n");
    printf("1.Bresham法绘制圆形\n");
    printf("2.中点画圆算法\n");
    scanf("%d",&i);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(800,800);
	if(i==1)
    {
        glutCreateWindow("Bresham法");
        gluOrtho2D(0,1000,0,1000);
        glutDisplayFunc(display);
    }
    else if(i==2)
    {
        glutCreateWindow("中点画圆法");
        gluOrtho2D(0,1000,0,1000);
        glutDisplayFunc(display1);
    }
	glutMainLoop();
	return 0;
}

/*
此法原理是比较候选像素点到圆形边界的距离，决定取得的点;
并且利用8路对称法实现加速绘制；
递推公式：
	首点：d[1]=3-2r;
	di>=0:d[i+1]=d[i]+4(x[i]-y[i])+10;
	di<0;d[i+1]=d[i]+4x[i]+6;
*/
