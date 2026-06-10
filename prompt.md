Write a C program for a text-based 2D Graphics Editor. You must follow these instructions exactly, using the precise variable names, logic, exact print strings, and exact spacing provided below. Do not add any extra features, includes, or error handling beyond what is specified. 

### 1. Includes and Macros
* Include `<stdio.h>`, `<stdlib.h>`, and `<math.h>`.
* Define `WIDTH` as 60, `HEIGHT` as 20, and `MAX_OBJS` as 50.

### 2. Enums and Structs
* Create a `typedef enum` named `ShapeType` with values: `NONE`, `LINE`, `RECTANGLE`, `CIRCLE`, `TRIANGLE`.
* Create a `typedef struct` named `Object`. It must contain:
  * `int id;`
  * `ShapeType type;`
  * `int x1, y1, x2, y2, x3, y3;` (comment this line with: `// Holds coordinates for all shapes`)
  * `int r;` (comment this line with: `// Holds radius for circles`)

### 3. Global Variables
* `Object objects[MAX_OBJS];`
* `int obj_count = 0;`
* `int next_id = 1;`
* `char canvas[HEIGHT][WIDTH];`

### 4. Drawing Functions
* **`void put_pixel(int x, int y)`**: Check if `x` is between 0 and WIDTH-1, and `y` is between 0 and HEIGHT-1. If true, set `canvas[y][x] = '*';`.
* **`void draw_line(int x0, int y0, int x1, int y1)`**: Implement Bresenham's line algorithm exactly as follows:
  * `int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;`
  * `int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;`
  * `int err = dx + dy, e2;`
  * Start an infinite `while (1)` loop. Inside: call `put_pixel(x0, y0);`. If `x0 == x1 && y0 == y1`, break. Set `e2 = 2 * err;`. If `e2 >= dy`, add `dy` to `err` and `sx` to `x0`. If `e2 <= dx`, add `dx` to `err` and `sy` to `y0`.
* **`void draw_rectangle(int x, int y, int w, int h)`**: Call `draw_line` four times to draw a box using `x, y`, `x+w, y`, `x+w, y+h`, and `x, y+h`.
* **`void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3)`**: Call `draw_line` three times connecting point 1 to 2, 2 to 3, and 3 to 1.
* **`void draw_circle(int cx, int cy, int r)`**: 
  * Comment: `// Loop through a bounding box and calculate distance`
  * Create a nested loop `for (int y = cy - r; y <= cy + r; y++)` and `for (int x = cx - r; x <= cx + r; x++)`.
  * Calculate `dx = x - cx`, `dy = y - cy`, `dist_sq = dx * dx + dy * dy`, and `r_sq = r * r`.
  * Comment: `// Add a small threshold to make the text circle look connected`
  * If `dist_sq >= r_sq - r && dist_sq <= r_sq + r`, call `put_pixel(x, y)`.

### 5. Display Function
* **`void display_picture()`**:
  * Comment: `// clear the canvs` (keep the typo 'canvs'). Loop through HEIGHT and WIDTH to set `canvas[y][x] = '_';`.
  * Comment: `//  render objcts` (keep the typo 'objcts'). Loop `i` from 0 to MAX_OBJS. If `objects[i].type` is LINE, call `draw_line` using `x1, y1, x2, y2`. Use `else if` for RECTANGLE (call `draw_rectangle` using `x1, y1, x2, y2`), TRIANGLE (call `draw_triangle` using `x1, y1, x2, y2, x3, y3`), and CIRCLE (call `draw_circle` using `x1, y1, r`).
  * Add exactly this block of commented-out code (preserve exact spacing):
    ```c
    // // print the canvas //may not use it
    // printf("\n=== CANVAS ===\n");
    // for (int y = 0; y < HEIGHT; y++) {
    //      for (int x = 0; x < WIDTH; x++) {
    //          printf("%c", canvas[y][x]);
    //      }
    //      printf("\n");
    // }
    // printf("==============\n");
    ```
  * Print `"\n=== CANVAS ===\n"`. Print an extra empty newline `"\n"`.
  * Loop `y` through HEIGHT. First print `"%2d ", y` (comment it `// y-axis label`), then loop `x` through WIDTH printing `canvas[y][x]`. Print a newline after each row.
  * After the loop, print exactly: `"   1====5====10====15====20====25====30====35====40====45====50\n"`.

### 6. Object Management Functions
* **`int find_free_slot()`**: Loop `i` to MAX_OBJS. If `objects[i].type == NONE` return `i`. Return `-1` at the end.
* **`void add_object()`**: 
  * Call `find_free_slot()`. If `-1`, print `"Canvas is full!\n"` and return.
  * Print `"\n1. Line  2. Rectangle  3. Circle  4. Triangle\nChoose shape to add: "` and `scanf` into `choice`.
  * Assign `objects[slot].id = next_id++;`.
  * If choice 1: set type LINE, print `"Enter x1 y1 x2 y2: "`, scanf into `x1, y1, x2, y2`.
  * Else if choice 2: set type RECTANGLE, print `"Enter x, y, width, height: "`, scanf into `x1, y1, x2, y2`.
  * Else if choice 3: set type CIRCLE, print `"Enter center x, center y, radius: "`, scanf into `x1, y1, r`.
  * Else if choice 4: set type TRIANGLE, print `"Enter x1 y1 x2 y2 x3 y3: "`, scanf into `x1, y1, x2, y2, x3, y3`.
  * Else print `"Invalid choice.\n"`.
  * Finally, print `"Object added with ID: %d\n"`.
* **`void delete_object()`**: Prompt `"Enter ID of object to delete: "`. Loop through MAX_OBJS. If type is not `NONE` and `id` matches, set type to `NONE`, add comment `// Simply mark it as NONE to delete it`, print `"Object %d deleted.\n"`, and return. If loop ends, print `"Object not found.\n"`.
* **`void modify_object()`**: Prompt `"Enter ID of object to modify: "`. Loop through MAX_OBJS. If type isn't `NONE` and `id` matches: print `"Modifying object %d.\n"`. Replicate the `if/else if` structure from `add_object()` to prompt and update the exact same variables for LINE, RECTANGLE, CIRCLE, and TRIANGLE. Then return. If loop ends, print `"Object not found.\n"`.
* **`void list_objects()`**: Print `"\n--- Active Objects ---\n"`. Track `count = 0`. Loop through objects. If not `NONE`, print `"ID: %d | Type: %d\n"`, increment count. If count == 0, print `"No objects on canvas.\n"`.

### 7. Main Function
* Comment `// Initialize empty object array`. Loop through MAX_OBJS and set `objects[i].type = NONE;`.
* Run a `while (1)` loop. Print `"\n=== 2D Graphics Editor ===\n"`, then lines for "1. Add Object", "2. Delete Object", "3. Modify Object", "4. List Objects", "5. Display Picture", "6. Exit". Prompt `"Choice: "`.
* Use a switch statement for `choice`: 1 -> `add_object()`, 2 -> `delete_object()`, 3 -> `modify_object()`, 4 -> `list_objects()`, 5 -> `display_picture()`, 6 -> `return 0`, default -> `printf("Invalid choice.\n");`. Return 0 at the end of `main`.
