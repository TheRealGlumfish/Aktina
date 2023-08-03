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
:-------:|:---------------------------------------------------------------|:--------------------------------------
Tuples   | [`tuples.c`](src/tuples.c), [`tuples.h`](src/tuples.h)         | Chapter 1; Unused, merged into Vectors
Canvas   | [`canvas.c`](src/canvas.c), [`canvas.h`](src/canvas.h)         | Chapter 2
Matrices | [`matrices.c`](src/matrices.c), [`matrices.h`](src/matrices.h) | Chapter 3; Unused, merged into Vectors
Vectors  | [`vectors.c`](src/vectors.c), [`vectors.h`](src/vectors.h)     | Chapter 1, 3, 4
Rays     | [`rays.c`](src/rays.c), [`rays.h`](src/rays.h)                 | Chapter 5; Demo `sphere`
