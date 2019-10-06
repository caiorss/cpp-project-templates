#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void renderFunction();

int main(int argc, char ** argv){

	std::cerr << "[INFO] Starting OpenGL main loop." << std::endl;
	
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Window 1");
    // Display Callback Function 
    glutDisplayFunc(&renderFunction);
    // Start main loop 
    glutMainLoop();
	std::cerr << "[INFO] Exit OpenGL main loop." << std::endl;
    return 0;
}

void renderFunction(){
	std::cerr << "[INFO] Running loop." << std::endl;
    // Clear the current output buffer
    glClear(GL_COLOR_BUFFER_BIT);   

    // Rotate 10 degrees counterclockwise around z axis
    glRotated(10, 0, 0, 1);

    // Set the current color (RGB) drawing to blue
    glColor3f(0.0, 0.0, 1.0);

    // Start polygon 
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, 0);
    glVertex3f( 0.5, -0.5, 0);
    glVertex3f( 0.5,  0.5, 0);
    glVertex3f(-0.5,  0.5, 0);
    // End polygon 
    glEnd();

    glFlush();
}
