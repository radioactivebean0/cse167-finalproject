# CSE 167 Final Project: Shadow Mapping

# About the Project
This repo contains code that implements shadows using the shadow mapping
technique in OpenGL. Most of the core design around the OpenGL pipeline and
interfaces are from HW3.

Implemented based on guidelines and instructions from [Albert Chern's CSE 167 Fall section](https://cseweb.ucsd.edu/~alchern/teaching/cse167_fa21/project-shadowmap.pdf).

See the attached writeup in the writeups folder for detailed final writeup.

# Building and Running
## System
The system this project was developed on was macOS Big Sur using the built in OpenGL drivers.
GNU make and GCC compilers were installed using Brew.

## Building
You can easily build this project with the help of GNU make.
The makefile contained is a copy of the makefile from HW3 with a few
modifications.

Run `make` in the main directory to build the SceneViewer and main dependencies.
Run `make clean` to delete the executable SceneViewer and .o files

# Running
To run the program first `chmod +x SceneViewer` to make sure that it is set as executable. Then `./SceneViewer` should run the executable.

Running the program should open a window with a scene in it. There should be some helpful commands printed out to the console
```
Available commands:
    press 'H' to print this message again.
    press Esc to quit.
    press 'O' to save a screenshot.
    press the arrow keys to rotate camera.
    press 'A'/'Z' to zoom.
    press 'R' to reset camera.
    press 'L' to toggle shadows.
    press 'D' to shade based on depth map.

    press Spacebar to generate images for hw3 submission.
```