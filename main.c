#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 60
#define HEIGHT 20
#define MAX_OBJS 50

// Enums and Structs to manage our objects
typedef enum { NONE, LINE, RECTANGLE, CIRCLE, TRIANGLE } ShapeType;

typedef struct {
    int id;
    ShapeType type;
    int x1, y1, x2, y2, x3, y3; // Holds coordinates for all shapes
    int r;                      // Holds radius for circles
} Object;

// Global State
Object objects[MAX_OBJS];
int obj_count = 0;
int next_id = 1;
char canvas[HEIGHT][WIDTH];

// --- 1. LOW-LEVEL DRAWING FUNCTIONS ---

// Safely place a pixel on the canvas
void put_pixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '*';
    }
}

