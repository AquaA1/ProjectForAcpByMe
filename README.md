# 2D Graphics Editor

## Description

A simple text-based 2D Graphics Editor written in C. The program allows users to add, modify, delete, and display geometric shapes on a canvas.

## Features

* Add Line
* Add Rectangle
* Add Circle
* Add Triangle
* Modify Existing Objects
* Delete Objects
* List Objects
* Display Canvas

## Canvas Specifications

* Width: 60
* Height: 20
* Maximum Objects: 50

## Compilation

```bash
gcc graphics.c -o graphics
```

## Execution

```bash
./graphics
```

## Menu

```text
1. Add Object
2. Delete Object
3. Modify Object
4. List Objects
5. Display Picture
6. Exit
```

## Supported Shapes

### Line

```text
x1 y1 x2 y2
```

### Rectangle

```text
x y width height
```

### Circle

```text
center_x center_y radius
```

### Triangle

```text
x1 y1 x2 y2 x3 y3
```

## Author

Anish
