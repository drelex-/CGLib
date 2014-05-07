#include "color.h"
Color* getColor(ColorMap* colorMap, int id) {
	int i;
	ColorMapEntry* aux;

	for (aux = (ColorMapEntry*) colorMap->colors; aux != NULL; aux = (ColorMapEntry*) aux->next) {
		if (aux->id == id) {
			return aux->color;
		}
	}

	return NULL;
}

ColorMap* createColorMap() {
	ColorMap* cm;

	cm = (ColorMap*) malloc(sizeof(ColorMap));
	if (cm == NULL) {
		return NULL;
	}

	cm->colors = NULL;
	cm->endColors = NULL;
	return cm;
}

int addColor(ColorMap* cm, int id, unsigned char red, unsigned char green,
		unsigned char blue, unsigned char alpha) {
	ColorMapEntry* newColor;

	newColor = (ColorMapEntry*) malloc(sizeof(ColorMapEntry));
	if (newColor == NULL) {
		return 0;
	}

	newColor->color = (Color*) malloc(sizeof(Color));
	if (newColor->color == NULL) {
		return 0;
	}

	newColor->color->red = red;
	newColor->color->green = green;
	newColor->color->blue = blue;
	newColor->color->alpha = alpha;

	newColor->id = id;
	newColor->next = NULL;

	if (cm->endColors != NULL) {
		cm->endColors->next = (struct ColorMapEntry*) newColor;
	}

	if (cm->colors == NULL) {
		cm->colors = newColor;
	}

	cm->endColors = newColor;
	return 1;
}
