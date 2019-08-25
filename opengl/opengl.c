
/* Note : be sure to compile with -lGL -lglut -lGLU */
#include <GL/glut.h>

/* Initialize OpenGL Graphics */
void initGL() {
   /* Set the clearing or background color black and opaque */
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
 
/* Handler for window-repaint event.
   Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   /* clear the color buffer */
   glClear(GL_COLOR_BUFFER_BIT);
   /* operate on Model-View matrix */
   glMatrixMode(GL_MODELVIEW);
   /* use the identity model-view matrix */
   glLoadIdentity();
 
   /* first quad will translate left -0.5 and up 0.4 */
   glTranslatef(-0.5f, 0.4f, 0.0f);
   /* the call to set color can be inside the glBegin() or 
    * previous .. doesn't matter to the state machine */
   glColor3f(1.0f, 0.0f, 0.0f);
   /* vertices in counter clockwise order */
   glBegin(GL_QUADS);
      glVertex2f(-0.3f, -0.3f);
      glVertex2f( 0.3f, -0.3f);
      glVertex2f( 0.3f,  0.3f);
      glVertex2f(-0.3f,  0.3f);
   glEnd();
 
   glTranslatef(0.1f, -0.7f, 0.0f);
   glColor3f(0.0f, 1.0f, 0.0f);
   glBegin(GL_QUADS);
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex2f(-0.3f, -0.3f);
      glVertex2f( 0.3f, -0.3f);
      glVertex2f( 0.3f,  0.3f);
      glVertex2f(-0.3f,  0.3f);
   glEnd();
 
   glTranslatef(-0.3f, -0.2f, 0.0f);
   /* for the sake of logic we will put the glColor3f calls
    * inside the glBegin phrase simply because we are
    * going for some color interpolation between the four
    * vertices */
   glBegin(GL_QUADS);
      glColor3f(0.2f, 0.2f, 0.2f);
      glVertex2f(-0.2f, -0.2f);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f( 0.2f, -0.2f);
      glColor3f(0.2f, 0.2f, 0.2f);
      glVertex2f( 0.2f,  0.2f);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex2f(-0.2f,  0.2f);
   glEnd();
 
   glTranslatef(1.1f, 0.2f, 0.0f);
   glColor3f(0.0f, 0.0f, 1.0f);
   glBegin(GL_TRIANGLES);
      glVertex2f(-0.3f, -0.2f);
      glVertex2f( 0.3f, -0.2f);
      glVertex2f( 0.0f,  0.3f);
   glEnd();
 

   /* this triangle will be translated right 0.2 and down -0.3 
    * then rotated by 180 degrees 
    *
    * Rotation is done via glRotatef function:
    *
    * void glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
    *
    * where angle specifies the rotation in degrees and then the 
    * vector (x, y, z) forms the axis of rotation.
    *  
    * So here we translate within the x-y plane since z=0 and
    * then rotate about the z-axis normal vector which is by
    * definition normal to the x-y plane.
    */
   glTranslatef(0.2f, -0.3f, 0.0f);
   glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
   glBegin(GL_TRIANGLES);
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex2f(-0.3f, -0.2f);
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex2f( 0.3f, -0.2f);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex2f( 0.0f,  0.3f);
   glEnd();
 
   /* OpenGL is a state machine and we need to undo previous rotate */
   glRotatef(-180.0f, 0.0f, 0.0f, 1.0f);
   glTranslatef(-0.1f, 1.0f, 0.0f);
   glColor3f(1.0f, 1.0f, 0.0f); // Yellow
   glBegin(GL_POLYGON);
      glVertex2f(-0.1f, -0.2f);
      glVertex2f( 0.1f, -0.2f);
      glVertex2f( 0.2f,  0.0f);
      glVertex2f( 0.1f,  0.2f);
      glVertex2f(-0.1f,  0.2f);
      glVertex2f(-0.2f,  0.0f);
   glEnd();
 
   /* render all the above */
   glFlush();
}
 
/* Handler for window re-size event.
 * Called back when the window first appears and
 * whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {
   /* note that we accept GLsizei non-negative parameters */

   /* Compute aspect ratio of the new window and prevent
    * a possible divide by zero with an assumption. */
   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   /* Set the viewport to cover the new window */
   glViewport(0, 0, width, height);
 
   /* Set the aspect ratio of the clipping area to match the viewport */
   glMatrixMode(GL_PROJECTION);  /* operate on the Projection matrix */
   glLoadIdentity();
   if (width >= height) {
     /* aspect >= 1, set the height from -1 to 1, with larger width */
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      /* aspect < 1, set the width to -1 to 1, with larger height */
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);                // Initialize GLUT
   glutInitWindowSize(640, 480);         // Set the window's initial width and height - non-square
   glutInitWindowPosition(50, 50);       // Position the window's initial top-left corner
   glutCreateWindow("Model Transform");  // Create window with the given title
   glutDisplayFunc(display);             // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);             // Register callback handler for window re-size event
   initGL();                             // Our own OpenGL initialization
   glutMainLoop();                       // Enter the infinite event-processing loop
   return 0;
}

