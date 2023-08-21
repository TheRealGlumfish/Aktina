# Ακτίνα - Ray
Software ray-tracer written in C.
Inspired by, **The Ray Tracer Challenge** by Jamis Buck.

## Building
To build run `meson setup build`, then `meson compile -C build`.
To run the tests, run `meson test -C build`.

### Dependencies
- [**Criterion 2.4.2**](https://github.com/Snaipe/Criterion/releases/tag/v2.4.2) (*Optional*, only required for the tests)

## Project Structure
The project roughly follows the structure laid out by the book, deviating where deemed necessary.

### Directory Structure

Directory              | Use
:---------------------:|:------------------------------------------------
`src`                  | Source code and header files
`test`                 | Test source code
`subprojects`          | Meson subprojects (dependencies, e.g. Criterion)
`LSAN-suppresions.txt` | Clang LeakSanitizer suppressions file

### Modules

Module   | Files                                                          | Notes
:-------:|:---------------------------------------------------------------|:------------------------------------------------------------------------------
Tuples   | [`tuples.c`](src/tuples.c), [`tuples.h`](src/tuples.h)         | Chapter 1; Unused, merged into Vectors
Canvas   | [`canvas.c`](src/canvas.c), [`canvas.h`](src/canvas.h)         | Chapter 2
Matrices | [`matrices.c`](src/matrices.c), [`matrices.h`](src/matrices.h) | Chapter 3; Unused, merged into Vectors
Vectors  | [`vectors.c`](src/vectors.c), [`vectors.h`](src/vectors.h)     | Chapter 1, 3, 4
Rays     | [`rays.c`](src/rays.c), [`rays.h`](src/rays.h)                 | Chapter 5, 6, 7, 8, 9; Demo `sphere`, `lighting`, `camera`, `shadows`, `planes`

## Demos

### Sphere - Chapter 5
Source code for this demo is located in [`test/sphere.c`](test/sphere.c).
It shows two spheres in 3D space rendeded by casting rays on a canvas.
No shading or light simulation is done, thus the lack of "depth".
![sphere](https://github.com/TheRealGlumfish/Aktina/assets/65093316/e3610be6-2e87-4b61-a12a-f41c58947ca6)

### Lighting - Chapter 6
Source code for this demo is located in [`test/lighting.c`](test/lighting.c).
It shows a sphere that is lit by a point light.
![lighting](https://github.com/TheRealGlumfish/Aktina/assets/65093316/43125288-0ee3-4e0d-85ee-7eb062cc044a)

### Camera - Chapter 7
Source code for this demo is located in [`test/camera.c`](https://github.com/TheRealGlumfish/Aktina/blob/c1ba2b4a3516e15a9163b6924e3c0b607036cf44/test/camera.c) [(dd88842)](https://github.com/TheRealGlumfish/Aktina/tree/dd888426e94a6b25100cda4c4b0772b22b87249e).
It shows three spheres surrounded by two "walls" and a "floor".
![camera](https://github.com/TheRealGlumfish/Aktina/assets/65093316/42526543-5067-4e62-8738-454f26dc1827)

### Shadows - Chapter 8
Source code for this demo is located in [`test/shadows.c`](test/shadows.c).
It shows three spheres surrounded by two "walls" and a "floor", illuminated by two light sources.
![shadows](https://github.com/TheRealGlumfish/Aktina/assets/65093316/c8714682-d319-463e-bc97-fb089338d7eb)

### Planes - Chapter 9
Source code for this demo is located in [`test/planes.c`](test/planes.c).
It shows three spheres, sitting on a plane, illuminated by three colored lights.
![planes](https://github.com/TheRealGlumfish/Aktina/assets/65093316/f71a44f7-6f0c-49ce-be9d-22378763cf85)
