# Rope Simulator

Inspired by [Tsoding's Rope Simulator](https://github.com/tsoding/rope-jai).

## Description
The project simulates a rope with a little bit of physics. 
When you press the right mouse button, it adds a new knot. 
However, when the first knot is added, you need to right-click it to add another knot. You can add up to 16 knots and up to 4 neighbours per knot.

You can left-click a knot to drag it, and it changes the color to red,
so you know which knot you are dragging. The compute velocity function is tsoding's but converted to suit SDL2 and the draw thick line function uses the math from his draw_thicc_line function.

## Bugs
The repulsion of the knots crashes at certain positions.

## Dependencies
- [SDL2](https://www.libsdl.org/)

## How to Compile
Compile the project using the following commands:

```bash
g++ -std=c++17 -Iinclude -Llib -o rope.exe main.cpp -lmingw32 -lSDL2main -lSDL2
./rope.exe
