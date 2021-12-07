#include <stdlib.h>
#include <iostream>
// OSX systems need their own headers
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
// Use of degrees is deprecated. Use radians for GLM functions
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Screenshot.h"
#include "Scene.h"


static const int width = 800;
static const int height = 600;
static const char* title = "Scene viewer";
static const glm::vec4 background(0.1f, 0.2f, 0.3f, 1.0f);
static Scene scene;

static GLuint depthMapFBO;
static const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
static GLuint depthMap;

#include "hw3AutoScreenshots.h"

void printHelp(){
    std::cout << R"(
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
    
)";
}

void initialize(void){
    printHelp();
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glClearColor(background[0], background[1], background[2], background[3]); // background color
    // shadow map frame buffer setup
    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT,
                 GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE); // Omitting color data
    glReadBuffer(GL_NONE); // Omitting color data
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    // Initialize scene
    scene.init();


    
}

void display(void){
    // draw to depth frame buffer
    glEnable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT );
    glViewport(0,0,SHADOW_WIDTH,SHADOW_HEIGHT);
    scene.drawDepth();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // draw to screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glViewport(0,0,width, height);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    scene.draw();
    
    // buffer swaps
    glutSwapBuffers();
    glFlush();
    
}

void saveScreenShot(const char* filename = "test.png"){
    int currentwidth = glutGet(GLUT_WINDOW_WIDTH);
    int currentheight = glutGet(GLUT_WINDOW_HEIGHT);
    Screenshot imag = Screenshot(currentwidth,currentheight);
    imag.save(filename);
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27: // Escape to quit
            exit(0);
            break;
        case 'h': // print help
            printHelp();
            break;
        case 'o': // save screenshot
            saveScreenShot();
            break;
        case 'r':
            scene.camera -> aspect_default = float(glutGet(GLUT_WINDOW_WIDTH))/float(glutGet(GLUT_WINDOW_HEIGHT));
            scene.camera -> reset();
            glutPostRedisplay();
            break;
        case 'a':
            scene.camera -> zoom(0.9f);
            glutPostRedisplay();
            break;
        case 'z':
            scene.camera -> zoom(1.1f);
            glutPostRedisplay();
            break;
        case 'l':
            scene.shader -> enablelighting = !(scene.shader -> enablelighting);
            scene.shader -> depthshade = false;
            glutPostRedisplay();
            break;
        case ' ':
            hw3AutoScreenshots();
            glutPostRedisplay();
            break;
        case 'd':
            scene.shader -> depthshade = !(scene.shader -> depthshade);
            scene.shader -> enablelighting = false;
        default:
            glutPostRedisplay();
            break;
    }
}
void specialKey(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP: // up
            scene.camera -> rotateUp(-10.0f);
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN: // down
            scene.camera -> rotateUp(10.0f);
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT: // right
            scene.camera -> rotateRight(-10.0f);
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT: // left
            scene.camera -> rotateRight(10.0f);
            glutPostRedisplay();
            break;
    }
}

int main(int argc, char** argv)
{
    // BEGIN CREATE WINDOW
    glutInit(&argc, argv);
    
#ifdef __APPLE__
    glutInitDisplayMode( GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#else
    glutInitContextVersion(3,1);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
#endif
    glutInitWindowSize(width, height);
    glutCreateWindow(title);
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    GLenum err = glewInit() ;
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    }
#endif
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    // END CREATE WINDOW
    
    initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    
    glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
