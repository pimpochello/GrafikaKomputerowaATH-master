#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "math.h"

// Definiujemy sta³¹ o wartoœci liczby PI
#define GL_PI 3.1415f
// Wielkoœæ obrotów
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// Wywo³ywana w celu przerysowania sceny

void RenderScene(void)
{
	GLfloat x, y, z, angle; // Zmienne przechowuj¹ce wspó³rzêdne i k¹ty
	GLfloat sizes[2]; // Do zapisania dopuszczalnego zakresu wielkoœci
	GLfloat step; // Zapamiêtuje obs³ugiwany przyrost rozmiaru
	GLfloat curSize; // Zapamêituje aktualny rozmiar
					 // Wyczyszczenie okna aktualnym kolorem czyszcz¹cym
	glClear(GL_COLOR_BUFFER_BIT);
	// Zapisanie stanu macierzy i wykonanie obrotu
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	// Pobranie dopuszczalnych rozmiarów punktów
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	// Ustalenie pocz¹tkowego rozmiaru punktu
	curSize = sizes[0];
	// Ustalenie pocztkowej wspó³rzêdnej z
	y = -80.0f;
	// Obracamy siê w kó³ko trzy razy
	for (angle = 0.0f; angle <= (2.0f*3.1415f)*6.0f; angle += 0.1f)
	{
		// Wyliczenie wartoœci x i y na kole
		z = 50.0f*sin(angle);
		x = 50.0f*cos(angle);
		// Zdefiniowanie rozmiaru punktu przed utworzeniem obiektu podstawowego
		glPointSize(curSize);
		// Rysowanie punktu
		glBegin(GL_POINTS);
		glVertex3f(x, y, z);
		glEnd();
		// Powiêkszenie wspó³rzêdnej z i rozmiaru punktu
		y += 0.6f;
		curSize += step;
	}
	// Odtworzenie macierzy przekszta³ceñ
	glPopMatrix();
	// Wykonanie poleceñ rysowania
	glutSwapBuffers();
}
// Ta funkcja wykonuje wszystkie konieczne inicjalizacje kontekstu renderowania
void SetupRC()
{
	// Czarne t³o
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Bêdziemy rysowaæ kolorem zielonym
	glColor3f(1.0f, 1.0f, 0.0f);
}
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	if (key > 356.0f)
		xRot = 0.0f;
	if (key < -1.0f)
		xRot = 355.0f;
	if (key > 356.0f)
		yRot = 0.0f;
	if (key < -1.0f)
		yRot = 355.0f;
	// Odœwie¿enie zawartoœci okna
	glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;
	// Ustalenie wymiarów widoku na zgodnych z wymiarami okna
	glViewport(0, 0, w, h);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Utworzenie przestrzeni ograniczaj¹cej (lewo, prawo, dó³, góra, blisko, daleko)
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Points Size Example");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	return 0;
}