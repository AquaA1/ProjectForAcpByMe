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


void put_pixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '*';
    }
}

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

void draw_rectangle(int x, int y, int w, int h) {
    draw_line(x, y, x + w, y);             
    draw_line(x, y + h, x + w, y + h);     
    draw_line(x, y, x, y + h);             
    draw_line(x + w, y, x + w, y + h);     
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line(x1, y1, x2, y2);
    draw_line(x2, y2, x3, y3);
    draw_line(x3, y3, x1, y1);
}

void draw_circle(int cx, int cy, int r) {
    // Loop through a bounding box and calculate distance
    for (int y = cy - r; y <= cy + r; y++) {
        for (int x = cx - r; x <= cx + r; x++) {
            int dx = x - cx;
            int dy = y - cy;
            int dist_sq = dx * dx + dy * dy;
            int r_sq = r * r;
            // Add a small threshold to make the text circle look connected
            if (dist_sq >= r_sq - r && dist_sq <= r_sq + r) {
                put_pixel(x, y);
            }
        }
    }
}

void display_picture() {
    // 1. Clear the canvas
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            canvas[y][x] = '_';
        }
    }

    // 2. Render objects
    for (int i = 0; i < MAX_OBJS; i++) {
        if (objects[i].type == LINE) {
            draw_line(objects[i].x1, objects[i].y1, objects[i].x2, objects[i].y2);
        } else if (objects[i].type == RECTANGLE) {
            draw_rectangle(objects[i].x1, objects[i].y1, objects[i].x2, objects[i].y2);
        } 
    }

    // 3. Print the canvas
    printf("\n=== CANVAS ===\n");
    for (int x = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", canvas[y][x]);
        }
        printf("\n");
    }
    printf("==============\n");
}