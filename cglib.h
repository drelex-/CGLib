#include "color.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <X11/Xlib.h>
#define true 1
#define false 0

#define MAXIMOX 700
#define MAXIMOY 700

typedef struct {
	float x;
	float y;
} Point;

typedef struct {
	Point p1;
	Point p2;
} Line;

typedef struct {
	Point* points;
	int pointCount;
	int closed;
} Polyline;

Point newPoint(float x, float y);
Point negative(Point point);
Polyline newPolyline(int pointCount, int closed);
Polyline newRegularPolygon(int sides, Point center, int radius);
Polyline newRectangle(Point p1, Point p2);

void rotateCCW(Polyline* polyline, int degrees, Point origin);
void rotateCW(Polyline* polyline, int degrees, Point origin);
void move(Polyline* polyline, Point delta);
void scale(Polyline* polyline, float scaleFactor, Point origin);

Polyline clone(Polyline original);
Point centerOf(Polyline polyline);
void freePolyline(Polyline polyline);

typedef struct {
	Point pMin;
	Point pMax;
} Universe;

typedef struct {
	int *buffer;
	int height;
	int width;
	Point pMin;
	Point pMax;
	Point pMinSRD;
	Point pMaxSRD;
	Universe* universe;
} ViewPort;

/*
 Entradas:
 pMin: menor ponto do viewport
 pMax: maior ponto do viewport
 u: Universo do viewport

 Saída:
 um ponteiro para ViewPort, mas esse ViewPort não tem um buffer allocado e
 os campos height e width não preenchidos.
 Em caso de falha é retornado um ponteiro nulo
 */
ViewPort* createViewPort(Point pMin, Point pMax, Universe* u);

/*
 Entrads:
 vp: O ViewPort no qual sera alocado o buffer e preenchido os campos
 height and width
 screenMaxWidth: largura do dispositivo
 screenMaxHeight: altura do dispositivo

 Saída:
 retorna 0 em caso de falha de alocação; 1 caso contrário
 */
char allocateViewPortBuffer(ViewPort* vp, int screenMaxWidth,
		int screenMaxHeight);

/*
 Entradas:
 pSru: ponto a ser convertido
 pMin: ponto inferior esquerdo do limite do SRU
 pMax: ponto superior direito do limite do SRU

 Saída:
 o ponto convertido para o SRN

 */
Point sru2srn(Point pSRU, Point pMin, Point pMax);

/*
 Entradas:
 pSRN: ponto a ser convertido
 width: largura do ViewPort
 height: altura do ViewPort


 Saída:
 o ponto convertido para o SRD
 */
Point srn2srd(Point pSRN, int width, int height);

void drawPolyLine(Polyline polyline, ViewPort* viewPort, int color);

/*
 Entradas:
 line: linha a ser desenhada, a mesma deve estar no SRD
 viewPort: matriz aonde sera desenhada a linha
 width: largura do viewPort
 height: altura do viewPort

 */
void drawLine(Line line, ViewPort* viewPort, int color);
// void drawLine(Line line, ViewPort* viewPort, int width, int height);

/*
 Desenha uma linha usando o algoritimo do ponto médio

 Entradas:
 line: linha a ser desenhada, a mesma deve estar no SRD
 viewPort: matriz aonde sera desenhada a linha
 width: largura do viewPort
 height: altura do viewPort
 */
void drawLineMidPoint(Line line, ViewPort* viewPort, int color);

/*
 Entradas:
 p: ponto a ser desenhado
 viewPort: matriz aonde sera desenhado o ponto
 color: cor do ponto
 */
void drawPoint(Point* p, ViewPort* viewPort, int color);

/*
 Entradas:
 viewPort: imagem a ser mostrada
 width: largura do viewPort
 height: altura do viewPort
 */
void show(ViewPort* viewPort, ColorMap* colorMap);
