#include<GL/GLUT.H>  
#include <windows.h>      
#include <math.h>      
#include <gl/GL.h>  
#include <iostream>
using namespace std;

int flag = 0;//�����ж��ƶ��ĸ����Ƶ�ı�־
//��ʼ�����Ƶ��λ��
GLfloat control[4][2] =
{
	{ -0.9f, 0.1f },{ -0.8f, 0.6f },{ 0.2f, 0.8f },{ 1.0f, 0.2f }
};

//�������ƶ���Ϣ
void motion(int x, int y)
{
	//����Ļ����ת��Ϊ��ͼʱ������
	float xx = x / 400.0f - 1.0f;
	float yy = -(y / 400.0f - 1.0f);
	//����̨���λ����Ϣ
	cout << "X: " << xx << "Y: " << yy <<  endl;
	if (flag == 0)
	{
		control[0][0] = xx;
		control[0][1] = yy;
	}
	else if (flag == 1)
	{
		control[1][0] = xx;
		control[1][1] = yy;
	}
	else if (flag == 2)
	{
		control[2][0] = xx;
		control[2][1] = yy;
	}
	else if (flag == 3)
	{
		control[3][0] = xx;
		control[3][1] = yy;
	}
	//�ػ洰��
	glutPostRedisplay();
}

//������������
void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	//���Ƴ��ĸ����Ƶ�
	glPointSize(4);//���Ƶ��С��Ϊ4
	glColor3f(1.0, 0.0, 0.0);//��ɫ��Ϊ��ɫ
	for (int i = 0; i < 4; i++) {
		glBegin(GL_POINTS);
			glVertex2fv(&control[i][0]);
		glEnd();
	}

	//�������Ƶ�֮�������
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 4; i++) {
		glVertex2fv(&control[i][0]);
	}
	glEnd();


	GLfloat result[100][2];


	//�������겢����result��
	//����100��
	int u = 0;
	for (double t = 0.0; t <= 1; t += 0.01)
	{
		//de Casteljau�㷨���׵��ƹ�ʽ
		result[u][0] = control[0][0]*(1-t)*(1 - t)*(1 - t)+ control[1][0] * 3*t*(1 - t)*(1 - t)+
			control[2][0] * 3 * t*t*(1 - t)+ control[3][0]*t*t*t;
		result[u][1] = control[0][1] * (1 - t)*(1 - t)*(1 - t) + control[1][1] * 3 * t*(1 - t)*(1 - t) +
			control[2][1] * 3 * t*t*(1 - t) + control[3][1] * t*t*t;
		u++;
	}


	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 100; i++)
	{
		glVertex2fv(result[i]);
	}
	glEnd();


	glFlush();
}

//�����¼���Ӧ
void keyboard(unsigned char key, int i, int j)
{
	if (key == '0')
	{
		flag = 0;
		cout << "flag: " << flag << endl;
	}
	else if (key == '1')
	{
		flag = 1;
		cout << "flag: " << flag << endl;
	}
	else if (key == '2')
	{
		flag = 2;
		cout << "flag: " << flag << endl;
	}
	else if (key == '3')
	{
		flag = 3;
		cout << "flag: " << flag << endl;
	}
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Bezier");
	glutKeyboardFunc(keyboard);//��Ӧ�����¼�
	glutDisplayFunc(myDisplay);//��ͼ
	glutMotionFunc(motion);//��Ӧ����ƶ��¼�
	glutMainLoop();
	return 0;
}