#include <GL/freeglut.h>
#include<GL/gl.h>
#include<GL/GLU.h>

#include <stdio.h>
#include <windows.h>
bool count_c = false;
double X1 = 0, Y1 = 0, Z1 = 0;
struct RGB {
	double R;
	double G;
	double B;
};
int count_t = 0;
RGB Colors[4] = { {0.0,0.0,0.0},{1,1,1},{0,0,1},{1,0,0} };
double c1 = 0, c2 = 0, c3 = 0;
int i = 0;

double teapod_s = 1.0;

// ������� ���������� ������ 20 ��
void Simulation(int value)
{
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();

	if (count_c == true)
	{
		count_t += 20;
		if (count_t == 1000)
		{
			count_t = 0;
			i++;
			c1 = Colors[i].R;
			c2 = Colors[i].G;
			c3 = Colors[i].B;
			if (i == 4)
				i = 0;
		}
	}

	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
	glutTimerFunc(20, Simulation, 0);

};



// �������, ���������� ��� ��������� �������� ����
void Reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void Display(void)
{
	// �������� ����� �����
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	// ������������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5 + X1, 5 + Y1, 7.5 + Z1, 0, 0, 0, 0 + X1, 1 + Y1, 0 + Z1);
	// ������� ������ ? ������� (1,0,0) ������
	glColor3f(c1, c2, c3);
	glutWireTeapot(teapod_s);
	glColor3f(0, 0, 1);
	glutWireTeacup(1.0);
	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

// ������� ��������� ������� ������
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);

	switch (key)
	{
	case 'p':
		exit(0);
		break;
	case 'q':
		X1 += 1;
		Y1 += 1;
		Z1 += 1;
		glutPostRedisplay();
		break;

	case 'e':
		Y1 -= 1;
		Z1 -= 1;
		X1 -= 1;
		glutPostRedisplay();
		break;
	case 'c':
		i++;
		c1 = Colors[i].R;
		c2 = Colors[i].G;
		c3 = Colors[i].B;
		glutPostRedisplay();
		if (i == 4)
			i = 0;
		break;
	case 'm':
		count_c = true;
		break;
	case 'n':
		count_c = false;
		count_t = 0;
		break;
	case 'z':
		teapod_s += 1.0;
		break;
	case 'x':
		teapod_s -= 1.0;
		break;
	}
};


void main(int argc, char** argv)
{
	// ������������� ���������� GLUT
	glutInit(&argc, argv);
	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// �������� ����:
	// 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 200);
	// 2. ������������� ������ ����
	glutInitWindowSize(600, 600);
	// 3. ������� ����
	glutCreateWindow("Lab 1");

	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(Display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(Reshape);
	// ������������� ������� ������� ����� ������� ����� 20 ��
	glutTimerFunc(20, Simulation, 0);
	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	glutKeyboardFunc(KeyboardFunc);


	// �������� ���� ��������� ��������� ��
	glutMainLoop();
}