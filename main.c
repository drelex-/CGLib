/*
 Alexandre Saldanha Braga - 408484
 Helio Ossamu Nakayama - 408395
 Fernando Trevisan Donati - 489948
 Renan Lordello de Aguiar - 489867
 Renan Ferreira de Almeida - 489581
 */
#include "cglib.h"
#include <stdio.h>
#include <stdlib.h>

void readLine(Line *l) {
	printf("p1(x,y): ");
	scanf("%f", &(l->p1.x));
	scanf("%f", &(l->p1.y));
	printf("p2(x,y): ");
	scanf("%f", &(l->p2.x));
	scanf("%f", &(l->p2.y));
}

int main() {
	ViewPort *vp;
	// Line line;
	int i, j;
	Point pMin, pMax;
	Universe u;
	ColorMap* cm;

	pMin.x = -100;
	pMin.y = -100;
	pMax.x = 100;
	pMax.y = 100;

	u.pMin = pMin;
	u.pMax = pMax;

	vp = createViewPort(pMin, pMax, &u);
	if (vp == NULL) {
		printf("Erro de alocacao do veiwport\n");
		exit(0);
	}

	if (!allocateViewPortBuffer(vp, MAXIMOX, MAXIMOY)) {
		printf("Erro de alocacao do buffer do viewport\n");
		exit(0);
	}

	cm = createColorMap();
	if (cm == NULL) {
		printf("[ERRO] mapa de cores nao pode ser criado\n");
		exit(0);
	}

	if (!addColor(cm, 0, 0, 0, 0, 0)) {
		printf("[ERRO] cor '0' nao pode ser inserida no mapa de cores\n");
		exit(0);
	}

	if (!addColor(cm, 1, 255, 255, 255, 0)) {
		printf("[ERRO] cor '1' nao pode ser inserida no mapa de cores\n");
		exit(0);
	}

	/* readLine(&line);

	line.p1 = sru2srn(line.p1, pMin, pMax);
	line.p2 = sru2srn(line.p2, pMin, pMax);


	line.p1 = srn2srd(line.p1, MAXIMOX, MAXIMOY);
	line.p2 = srn2srd(line.p2, MAXIMOX, MAXIMOY);

	// drawLine(line,vp,1);

	drawLineMidPoint(line, vp, 1); */

	int polylineCount = 5;
	Polyline polylines[polylineCount];

	polylines[0] = newRectangle(newPoint(30, 30), newPoint(70, 0));
	polylines[1] = newRegularPolygon(50, newPoint(0, 0), 30);

	// move(&polylines[1], newPoint(99, -90));
	// scale(&(polylines[0]), 0.5, centerOf(polylines[0]));
	// scale(&(polylines[1]), 2, centerOf(polylines[1]));
	polylines[2] = newPolyline(3, false);
	polylines[2].points[0] = newPoint(30, 30);
	polylines[2].points[1] = newPoint(50, 45);
	polylines[2].points[2] = newPoint(70, 30);
	// move(&polylines[2], newPoint(30, 30));

	polylines[3] = clone(polylines[2]);
	polylines[4] = clone(polylines[0]);

	rotateCCW(&(polylines[0]), 90, newPoint(0, 0));
	rotateCCW(&(polylines[2]), 90, newPoint(0, 0));


	for (j = 0; j < polylineCount; j++) {
		for (i = 0; i < polylines[j].pointCount; i++) {
			polylines[j].points[i] = sru2srn(polylines[j].points[i], pMin, pMax);
		}
		for (i = 0; i < polylines[j].pointCount; i++) {
			polylines[j].points[i] = srn2srd(polylines[j].points[i], MAXIMOX, MAXIMOY);
		}
		drawPolyLine(polylines[j], vp, 1);
	}

	show(vp, cm);

	return 0;
}
