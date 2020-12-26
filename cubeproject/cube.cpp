#include <stdlib.h>
#include <GL/glut.h>


static GLint axis = 0; //0은 x, 1은 y, 2는 z축
static GLfloat theta[] = { 0.0,0.0,0.0 };

static GLfloat from_p[] = { 0.0, 0.0, 5.0 };
static GLfloat at_p[] = { 0.0, 0.0, 0.0 };
static GLfloat up_p[] = { 0.0, 1.0, 0.0 };

float trans_point[3] = { 0.0, 0.0, 0.0 }; //translate할때 얼마만큼 이동할지.
float scale_value[3] = { 1.0,1.0,1.0 };

int change = 1; //어떤 변환을 할지

GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },
{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },{ -1.0,-1.0,1.0 },
{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } }; 

GLfloat colors[][3] = { { 0.0,0.0,0.0 },{ 1.0,0.0,0.0 },
{ 1.0,1.0,0.0 },{ 0.0,1.0,0.0 },{ 0.0,0.0,1.0 },
{ 1.0,0.0,1.0 },{ 1.0,1.0,1.0 },{ 0.0,1.0,1.0 } }; 

void polygon(int a, int b, int c, int d) 
{
	/* draw a polygon via list of vertices */

	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube()
{

	/* map vertices to faces */

	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* update viewer position in model-view matrix */

	glLoadIdentity();
	gluLookAt(from_p[0], from_p[1], from_p[2], at_p[0], at_p[1], at_p[2], up_p[0], up_p[1], up_p[2]);

	glTranslatef(trans_point[0], trans_point[1], trans_point[2]);
	/* rotate cube */
	glRotatef(theta[0], 1.0, 0.0, 0.0);//몇도 만큼 돌릴지, x,y,z축
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	glScalef(scale_value[0], scale_value[1], scale_value[2]);
	colorcube();

	glFlush();
	glutSwapBuffers();
}

void spinCube()
{

	/* idle callback, spin cube 2 degrees about selected axis */

	theta[axis] += 0.05; //
	if (theta[axis] > 360.0) theta[axis] -= 360.0; 
	/* display(); */
	glutPostRedisplay();
}


void keys(int key, int x, int y) //키보드
{
	if (change == 1) 
	{
		if (key == GLUT_KEY_RIGHT)
			trans_point[axis] += 0.2;
		else if (key == GLUT_KEY_LEFT)
			trans_point[axis] -= 0.2;
	}
	if (change == 2) 
	{
		if (key == GLUT_KEY_RIGHT)
			theta[axis] += 0.6;
		else if (key == GLUT_KEY_LEFT)
			theta[axis] -= 0.6;
	}
	if (change == 3) 
	{
		if (key == GLUT_KEY_RIGHT)
			scale_value[axis] *= 1.2;
		else if (key == GLUT_KEY_LEFT)
			scale_value[axis] /= 1.2;
	}
	if (change == 4) 
	{
		if (key == GLUT_KEY_RIGHT)
			from_p[axis] += 1.0;
		else if (key == GLUT_KEY_LEFT)
			from_p[axis] -= 1.0;
	}
	if (change == 5)
	{
		if (key == GLUT_KEY_RIGHT)
			at_p[axis] += 0.3;
		else if (key == GLUT_KEY_LEFT)
			at_p[axis] -= 0.3;
	}
	if (change == 6) 
	{
		if (key == GLUT_KEY_RIGHT)
			up_p[axis] += 0.5;
		else if (key == GLUT_KEY_LEFT)
			up_p[axis] -= 0.5;
	}

	display();
}

void translate(int id)
{
	change = 1;
	if (id == 1)
		axis = 0;
	else if (id == 2)
		axis = 1;
	else if (id == 3)
		axis = 2;
}
void rotate(int id)
{
	change = 2;
	if (id == 1)
		axis = 0;
	else if (id == 2)
		axis = 1;
	else if (id == 3)
		axis = 2;
}
void scale(int id)
{
	change = 3;
	if (id == 1)
		axis = 0;
	else if (id == 2)
		axis = 1;
	else if (id == 3)
		axis = 2;
}

void camera(int id)
{
}

void from(int id)
{
	change = 4;
	if (id == 1)
		axis = 0;
	else if (id == 2)
		axis = 1;
	else if (id == 3)
		axis = 2;
}
void at(int id)
{
	change = 5;
	if (id == 1)
		axis = 0;
	else if (id == 2)
		axis = 1;
	else if (id == 3)
		axis = 2;
}
void up(int id)
{
	change = 6;
	if (id == 1)
		axis = 0;
	else if (id == 2)
		axis = 1;
	else if (id == 3)
		axis = 2;
}

void middle_menu(int id)
{
	if (id == 1) exit(0);
}

void myReshape(int w, int h) //화면 크기가 바뀔 때
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) //작은 쪽에 맞춤. 너무 커지면 안보임.
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,  //glOrtho는 평행투형
			2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
			2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW); //transformation하게함
}

int main(int argc, char **argv)
{
	int translation, rotation, scaling, camera_view;
	int from1, at1, up1;

	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //버퍼 두개 사용. 움직이는 것은 버퍼 두개를 사용하는 것이 좋다.
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);

	translation = glutCreateMenu(translate);
	glutAddMenuEntry("x", 1);
	glutAddMenuEntry("y", 2);
	glutAddMenuEntry("z", 3);
	rotation = glutCreateMenu(rotate);
	glutAddMenuEntry("x", 1);
	glutAddMenuEntry("y", 2);
	glutAddMenuEntry("z", 3);
	scaling = glutCreateMenu(scale);
	glutAddMenuEntry("x", 1);
	glutAddMenuEntry("y", 2);
	glutAddMenuEntry("z", 3);

	from1 = glutCreateMenu(from);
	glutAddMenuEntry("x", 1);
	glutAddMenuEntry("y", 2);
	glutAddMenuEntry("z", 3);
	at1 = glutCreateMenu(at);
	glutAddMenuEntry("x", 1);
	glutAddMenuEntry("y", 2);
	glutAddMenuEntry("z", 3);
	up1 = glutCreateMenu(up);
	glutAddMenuEntry("x", 1);
	glutAddMenuEntry("y", 2);
	glutAddMenuEntry("z", 3);

	camera_view = glutCreateMenu(camera);
	glutAddSubMenu("from", from1);
	glutAddSubMenu("at", at1);
	glutAddSubMenu("up", up1);

	glutCreateMenu(middle_menu);
	glutAddSubMenu("translation", translation);
	glutAddSubMenu("rotation", rotation);
	glutAddSubMenu("scaling", scaling);
	glutAddSubMenu("camera", camera_view);
	glutAddMenuEntry("quit", 1);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	
	glEnable(GL_DEPTH_TEST); /* Enable hidden-surface removal*/
	glutSpecialFunc(keys);
	glutMainLoop();
}