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

// Draw a line using a simplified Bresenham's algorithm
void draw_line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;
    
    while (1) {
        put_pixel(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}