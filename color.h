#include <stdlib.h>

typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
} Color;

typedef struct {
	Color* color;
	int id;
	struct ColorMapEntry* next;
} ColorMapEntry;

typedef struct {
	ColorMapEntry* colors;
	ColorMapEntry* endColors;
} ColorMap;

Color* getColor(ColorMap* colorMap, int id);
ColorMap* createColorMap();
int addColor(ColorMap* cm, int id, unsigned char red, unsigned char green,
		unsigned char blue, unsigned char alpha);
