#include<GL/GLUT.H>  
#include <windows.h>      
#include <math.h>      
#include <gl/GL.h>  
#include <iostream>
using namespace std;

int flag = 0;//用来判断移动哪个控制点的标志
//初始化控制点的位置
GLfloat control[4][2] =
{
	{ -0.9f, 0.1f },{ -0.8f, 0.6f },{ 0.2f, 0.8f },{ 1.0f, 0.2f }
};

//检测鼠标移动消息
void motion(int x, int y)
{
	//将屏幕坐标转化为画图时的坐标
	float xx = x / 400.0f - 1.0f;
	float yy = -(y / 400.0f - 1.0f);
	//控制台输出位置信息
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
	//重绘窗口
	glutPostRedisplay();
}

//画贝塞尔曲线
void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	//绘制出四个控制点
	glPointSize(4);//控制点大小设为4
	glColor3f(1.0, 0.0, 0.0);//颜色设为红色
	for (int i = 0; i < 4; i++) {
		glBegin(GL_POINTS);
			glVertex2fv(&control[i][0]);
		glEnd();
	}

	//画出控制点之间的连线
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 4; i++) {
		glVertex2fv(&control[i][0]);
	}
	glEnd();


	GLfloat result[100][2];


	//计算坐标并存在result中
	//迭代100次
	int u = 0;
	for (double t = 0.0; t <= 1; t += 0.01)
	{
		//de Casteljau算法三阶递推公式
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

//键盘事件响应
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
	glutKeyboardFunc(keyboard);//响应键盘事件
	glutDisplayFunc(myDisplay);//画图
	glutMotionFunc(motion);//响应鼠标移动事件
	glutMainLoop();
	return 0;
}