#define _WCHAR_T_DEFINED
#define _STDCALL_SUPPORTED
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


int i;
void circle(int x,int y,int x0,int y0)
{							//����1/8Բ������7���ԳƵ�
	glVertex2f(x0+x,y0+y);
	glVertex2f(x0+y,y0+x);
	glVertex2f(x0+y,y0-x);
	glVertex2f(x0+x,y0-y);
	glVertex2f(x0-x,y0-y);
	glVertex2f(x0-y,y0-x);
	glVertex2f(x0-y,y0+x);
	glVertex2f(x0-x,y0+y);
}
void Breseham(int x0,int y0,double r)//Bresham������Բ��
{
	int x=0;
	int y=(int)r;	//��һ��������
	int d=int(3-2*r);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_POINTS);
	while(y>=x)		//���Ƶ���1/8԰�������յ㴦x=y;
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
	int y=(int)r;	//��һ��������
	int d=1-r;
	glColor3f(0.0,1.0,0.0);	//�����׵�
	glBegin(GL_POINTS);
	while(y>=x)		//���Ƶ���1/8԰�������յ㴦x=y;
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

	Breseham(500,500,200.0);	//�ƶ�Բ�Ĵ�С
	glFlush();
}
void display1(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	midpoint_circle(500,500,200.0);	//�ƶ�Բ�Ĵ�С
	glFlush();
}
int main(int argc,char* argv[])
{
    printf("��ѡ��Բ������\n");
    printf("1.Bresham������Բ��\n");
    printf("2.�е㻭Բ�㷨\n");
    scanf("%d",&i);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(800,800);
	if(i==1)
    {
        glutCreateWindow("Bresham��");
        gluOrtho2D(0,1000,0,1000);
        glutDisplayFunc(display);
    }
    else if(i==2)
    {
        glutCreateWindow("�е㻭Բ��");
        gluOrtho2D(0,1000,0,1000);
        glutDisplayFunc(display1);
    }
	glutMainLoop();
	return 0;
}

/*
�˷�ԭ���ǱȽϺ�ѡ���ص㵽Բ�α߽�ľ��룬����ȡ�õĵ�;
��������8·�ԳƷ�ʵ�ּ��ٻ��ƣ�
���ƹ�ʽ��
	�׵㣺d[1]=3-2r;
	di>=0:d[i+1]=d[i]+4(x[i]-y[i])+10;
	di<0;d[i+1]=d[i]+4x[i]+6;
*/
