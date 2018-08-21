#include "CSCIx229.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
int mode=1;
int lick = 0;
int fly=1;
int Th=0,Ph=30;
int    light=1;
int tongue = 1;
int b = 3.1459/2;
int    th=0;     //  Azimuth of view angle
int    ph=0;     //  Elevation of view angle
int    zh=0;     //  Azimuth of light
double Yl=2;     //  Elevation of light
int    fov=55;   //  Field of view (for perspective)
double asp=1;    //  Aspect ratio
double dim=20.0;  //  Size of world
int    box=1;    //  Draw sky
double X  = 0;   //  Location
double Y  = 0;   //  Location
double Z  = 0;   //  Location
double Dx = 1;   //  Direction
double Dy = 0;   //  Direction
double Dz = 0;   //  Direction
double Sx = 1;   //  Sideways
double Sy = 0;   //  Sideways
double Sz = 0;   //  Sideways
double Ux = 1;   //  Up
double Uy = 0;   //  Up
double Uz = 0;   //  Up
double Ox = 0;   //  LookAt
double Oy = 0;   //  LookAt
double Oz = 0;   //  LookAt
double Ex = 1;   //  Eye
double Ey = 1;   //  Eye
double Ez = 1;   //  Eye
int skybox[6];
/*Citations/Thanks:
https://www.khronos.org - I owe you the world
https://braintrekking.wordpress.com/2012/09/10/how-to-map-texture-maintaining-its-aspect-ratio-on-a-elliptic-cylinder/
https://www.opengl.org/resources
And all the class examples, every last one of 'em
*/

unsigned int sun, eye, cotton;
int smooth    =   1;  // Smooth/Flat shading


void mealworm(GLfloat x, GLfloat y, GLfloat  angle, GLfloat radius, GLfloat height)
{
    //This really just ended up being the wings of the fly
    //poor guy never had a chance
     float PI = 3.14159265359/2;
        glDisable(GL_CULL_FACE);

        glBegin(GL_QUAD_STRIP);
        angle = 0.0;
        GLfloat angle_stepsize = 0.1;
        //going to pi/2 because we want a half circle as the base
            glBegin(GL_QUAD_STRIP);
            angle = 0.0;
                while( angle < 2*PI ) {
                    x = radius * cos(angle);
                    y = radius * sin(angle);
                    glVertex3f(x, y , height);
                    glVertex3f(x, y , 0.0);
                    angle = angle + angle_stepsize;
                }
                glVertex3f(radius, 0.0, height);
                glVertex3f(radius, 0.0, 0.0);
            glEnd();
            glTranslated(0,0,0);
            glRotated(90,0,0,0);
            glRectd(0-(radius/2),0,x,y);
                    glBegin(GL_QUAD_STRIP);
                    angle = 0.0;
                        glBegin(GL_QUAD_STRIP);
                        angle = 0.0;
                            while( angle < 2*PI ) {
                                x = radius * cos(angle);
                                y = radius * sin(angle);
                                glVertex3f(x, y , height);
                                glVertex3f(x, y , 0.0);
                                angle = angle + angle_stepsize;
                                if(tongue){
                                 b = b - angle_stepsize;
                                }
                            }
                        glVertex3f(radius, 0.0, height);
                        glVertex3f(radius, 0.0, 0.0);
                        glEnd();
                        glTranslated(0,0,0);
                        glRotated(90,0,0,0);
                        glRectd(0-(radius/2),0,x,y);
           //none of this even matter
            glBegin(GL_POLYGON);
            angle = 0.0;
                while( angle < 2*PI ) {
                    x = radius * cos(angle);
                    y = radius * sin(angle);
                    glVertex3f(x, y , height);
                    angle = angle + angle_stepsize;
                }
                glVertex3f(radius, 0.0, height);
            glEnd();
            //glColor3ub(R,G,B);
            glBegin(GL_POLYGON);
            angle = 0.0;
                while( angle < 2*PI ) {
                    x = radius * cos(angle);
                    y = radius * sin(angle);
                    glVertex3f(x, y , 0);
                    angle = angle + angle_stepsize;
                }
            //nothing matters
                glVertex3f(radius, 0.0, height);
            glEnd();
        }

void draw_fly(){
      //awwwww you are useless RIP
       GLUquadric* fly = gluNewQuadric();
       gluQuadricNormals(fly, GLU_SMOOTH);

       glColor3f(1.00,0.77,0.36);
       glPushMatrix();
       glTranslated(0,0,-19);
       gluSphere(fly, 2.0, 20, 20);
       glPopMatrix();

       glPushMatrix();
       glColor3f(0.00,0.00,0.88);
       glTranslated(0,0,-22);
       gluSphere(fly, 1.5, 20, 20);
       glPopMatrix();

       glPushMatrix();
       glColor3f(1.00,0.00,0.36);
       glTranslated(-1.5,.75, -22.5);
       gluSphere(fly, .65, 6, 6);
       glPopMatrix();

       glPushMatrix();
       glTranslated(1.5,0.75, -22.5);
       gluSphere(fly, .65, 6, 6);
       glPopMatrix();

       glPushMatrix();
       glTranslated(0,0,-18.5);
       glRotated(90, 1,0,0);
       glRotated(180, 0,0,1);
       mealworm(0,0,0, 3, .45);
       glPopMatrix();

}
void fly_fly(float x, float y, float z){
    //I got a little fly to move around but it made the tongue disappear
    //It was v cute though
    //And was fun to play with other parametric equations for movement
    glPushMatrix();
    glTranslatef(x,y,z);
    draw_fly();
    glPopMatrix();
}

void draw_tongue_flat(GLfloat x, GLfloat y, GLfloat  angle, GLfloat radius, GLfloat height){
              //jk jk this is almost the fun part
              double i = 0;
              float PI = (3.1415926535897939);    //a much better estimation of pi
              angle = 0.0;
              GLfloat angle_stepsize = 0.0001;
              //
              //glDisable(GL_LIGHTING)
              glEnable(GL_TEXTURE_2D);
              glEnable(GL_CULL_FACE);
              glEnable(GL_NORMALIZE);



              glBindTexture(GL_TEXTURE_2D,cotton);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
              glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
              glBegin(GL_QUAD_STRIP);
                 while( angle < 2*PI ) {
                     glNormal3f(0,0,-angle);
                     x = (radius * 2*cos(angle));
                     y = (radius * .75*sin(angle));
                     glVertex3f(x,y,0);
                     glVertex3f(x,0,height ); //closed tip (it looks cooler, like it's really stretched )
                     angle = angle + angle_stepsize;
                 }
                  glBindTexture(GL_TEXTURE_2D, cotton); //add texture to cylinder
                  glNormal3f(0,0,-angle);

                  for (i = 0; i <= 2 * PI; i += angle_stepsize)
                                 {
                                     const float tc = ( i / (float)( 2 * PI ));
                                     glTexCoord2f( tc, 0.0 );
                                     glVertex3f(radius * 2*cos(i), radius * .75*sin(i), 0);
                                     glTexCoord2f( tc, 1.0 );
                                     glVertex3f(radius *2*cos(i), .001*sin(i),height);
                                 } //very important to specify the texture coordinates
                                   //if not it would wrap a pink blur, gross

                 glVertex3f(0.0,height, radius);
                 glTranslatef( -1.1, 10.0, 0.0);
                 glDisable(GL_TEXTURE_2D);
                 glEnd();

                  glDisable(GL_TEXTURE_2D);
                  glDisable(GL_CULL_FACE);
                  glDisable(GL_NORMALIZE);




}



void draw_tongue(GLfloat b, GLfloat x, GLfloat y, GLfloat  angle, GLfloat radius, GLfloat height) //cylinder  function better than previous
{
    //The tongue is either a spiral or stretched out
    //basic parametric equations for spiral
    double i = 0;
    //glEnable(GL_CULL_FACE);
    GLfloat angle_stepsize = 0.0001;

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);

    float PI = (3.1415926535897939);    //a much better estimation of pi
    float z;
    float x2 = 0;
    float y2 = .3;
    float z2 = 0;
    angle = 0.0;

    glBindTexture(GL_TEXTURE_2D,cotton);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    if(tongue){ //yay spiral time
        glBegin(GL_QUAD_STRIP);
        while( angle < 3.25*PI ) {
            glNormal3f(0,0,-angle);
            for (angle = 0; angle <= 3.25 * PI; angle += angle_stepsize)
               {
                   const float tc = ( angle / (float)( 3.25 * PI ) );
                   glTexCoord2f( tc, 0.0 ); //again, even more important to specify coordinates
                   glVertex3f(height, (b*angle) * .5*sin(b+angle), (b*angle) * .5*cos(b+angle));
     //0xy
                   glTexCoord2f( tc, 1.0 );
                   glVertex3f(0,(b*angle) * .5*sin(b+angle),  (b*angle) * .5*cos(b+angle));


                   glTexCoord2f( tc, 2.0 );
                   glVertex3f(height, (b*angle) * .35*sin(b+angle), (b*angle) * .35*cos(b+angle));

                   glTexCoord2f( tc, 3.0 );
                   glVertex3f(0,(b*angle) * .35*sin(b+angle),  (b*angle) * .35*cos(b+angle));
               }
            glNormal3f(0,0,-angle);
            glBindTexture(GL_TEXTURE_2D, eye); //add texture to cylinder */
            glNormal3f(0,0,-angle);
            y= ((b*angle) * .5*cos(b+angle));
            x = ((b*angle) * .5*sin(b+angle));
            y2 = ((b*angle) * .35*cos(b+angle));
            x2 = ((b*angle) * .35*sin(b+angle));
            glVertex3f(height, x,y);
            glVertex3f((0.0),x,y );
            glVertex3f(height, x2,y2);
            glVertex3f((0.0),x2,y2);
            angle = angle + angle_stepsize;
            }
            glVertex3f(0.0,height, radius);
            glTranslatef( -1.1, 10.0, 0.0);
            glDisable(GL_TEXTURE_2D);
            glEnd();
     }
     else{
     glPushMatrix();
     glDisable(GL_TEXTURE_2D);
     glTranslated(-1.25,-4.5,2);
     draw_tongue_flat(x, y, angle, radius-.5, -25);
     glEnd();
     glPopMatrix();
     }
    glDisable(GL_TEXTURE_2D);
}

void color_tongue(){
   //helper function to make it easier to move everything
    glPushMatrix();
    glTranslated(8.75,12,-6);
    draw_tongue(b,0,0,0,1.3, -3);
    glPopMatrix();
}
void draw_finger(GLdouble height, GLint slices, GLint stacks,GLdouble radius)
{
     //oooo sticky lil finger
     GLUquadric* sun1 = gluNewQuadric();
     gluQuadricNormals(sun1, GLU_SMOOTH);
     gluSphere(sun1, radius, slices, stacks);
     gluCylinder(sun1,radius - .1,radius, height, slices, stacks);

}
void draw_front_leg(GLfloat x, GLfloat y, GLfloat z)
{
    //cleary skips arm day
    GLUquadric* leg = gluNewQuadric();
    gluQuadricNormals(leg, GLU_SMOOTH);
    gluQuadricTexture(leg, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,sun);
    glRotatef(105, 1.0f, 0.0f, 0.0f);
    glTranslatef(x+3.0f, y+5.0f, z-2.5f);
    //glTranslatef(0.0f, 0.0f, 3.0f);
    gluCylinder(leg, .75,1.25,4,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( x+3.0f, y+5.5f, z+6.0f);
    gluSphere(leg, 1, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( x+3.0f, y+5.5f, z+6.0f);
    glRotatef(155, 1.0f, 1.0f, 1.0f);
    gluCylinder(leg, .75,2,3,10,10);
    glPopMatrix();


    glPushMatrix();
    glTranslatef( x+5.0f, y+6.5f, z+5.0f);
    gluSphere(leg, 1, 10, 10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void draw_back_leg(GLfloat x, GLfloat y, GLfloat z){
       //but he thicc tho
    GLUquadric* leg = gluNewQuadric();
    gluQuadricNormals(leg, GLU_SMOOTH);
    gluQuadricTexture(leg, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,sun);
    glTranslatef( x+3.0f, y+5.5f, z-1.0f);
    gluSphere(leg, 3, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( x+3.0f, y+7.0f, z+5.0f);
    gluSphere(leg, 4, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( x+3.0f, y+5.5f, z-1.0f);
    glRotatef(-15, 1.0f, 0.0f, 0.0f);
    gluCylinder(leg, 3,4,6,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( x+3.0f, y+3.5f, z-1.0f);
    glRotatef(35, 1.0f, 0.0f, 1.0f);
    gluCylinder(leg, .75,1.75,7,10,10);
    glPopMatrix();



    glPushMatrix();
    glTranslatef( x+3.5f, y+0.5f, z+6.0f);
    gluSphere(leg, 2, 10, 10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_eye(float x, float y, float z){
    //okay the annoying part about this was wrapping the texture
    //so the iris was in the right spot
    //and not demonically rolled into his eyelids
    GLUquadric* eyes = gluNewQuadric();
    gluQuadricNormals(eyes, GLU_SMOOTH);
    gluQuadricTexture(eyes, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    //and I wanted to just draw one eye and call the function twice
    //but the wrapping made that too difficult
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,eye);
    glTranslatef(x,y,z);
    glRotated(-100,0,0,1);
    glRotated(25,1,0,0);
    glRotated(90,0,1,0);
    gluQuadricTexture(eyes,GL_TRUE);
    glNormal3f(x,y,z);
    gluSphere(eyes, 2, 20,20);
    glPopMatrix();


    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,eye);
    glTranslatef(x+7,y,z);
    glRotated(-100,0,0,1);
    glRotated(180,1,0,0);
    glRotated(90,0,1,0);
    glRotated(-30,0,0,1);
    gluQuadricTexture(eyes,GL_TRUE);
    gluSphere(eyes, 2, 20,20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void draw_head(){
    glEnable(GL_NORMALIZE);
    GLUquadric* body = gluNewQuadric();
    gluQuadricNormals(body, GLU_SMOOTH);
    gluQuadricTexture(body, GL_TRUE);
    glEnable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef( 7.5f, 9.0f, 0.0f);
    gluCylinder(body, 6,8,10,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.5f, 9.0f, 2.0f);
    gluSphere(body, 6, 20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( 7.5f, 7.5f, -5.0f);
    glRotatef(-15, 1.0f, 0.0f, 1.0f);
    gluCylinder(body, 1,6.2,6,20,20);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_NORMALIZE);
}


void draw_body(){
    draw_head();
    GLUquadric* body = gluNewQuadric();
    glEnable(GL_NORMALIZE);
    gluQuadricNormals(body, GLU_SMOOTH);
    gluQuadricTexture(body, GL_TRUE);
    glEnable(GL_TEXTURE_2D);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,sun);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glNormal3f(-.456,-.481,1);
    glTranslatef( 3.0f, 10.0f, 20.0f);
    gluSphere(body, 10, 100, 100);

    glPopMatrix();


    glPushMatrix();
    glNormal3f(0,0,-1);
    glTranslatef( 12.0f, 10.0f, 20.0f);
    gluSphere(body, 10, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glNormal3f(-.1,-.481,-1);
    glTranslatef( 7.5f, 10.0f, 15.0f);
    gluSphere(body, 10, 100, 100);
    glPopMatrix();


    //lumps and warts from texture
    glDisable(GL_NORMALIZE);
    glDisable(GL_TEXTURE_2D);

}

void draw_front_hand(GLfloat x, GLfloat y, GLfloat z)
{
     GLUquadric* hand = gluNewQuadric();
     gluQuadricNormals(hand, GLU_SMOOTH);
     gluQuadricTexture(hand, GL_TRUE);
     glEnable(GL_TEXTURE_2D);
     glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
     glDisable(GL_CULL_FACE);
    //Toad hands with grippy fingers
    glPushMatrix();
   glBindTexture(GL_TEXTURE_2D,sun);
    glTranslatef(x+1,y+2,z+1);
    //glRotatef(-15, 0,1,0);
    draw_finger(2, 10, 10,.25);
    glPopMatrix();
 //sooo many fingers
    glPushMatrix();
    glTranslatef(x+2,y+2,z - 1);
    draw_finger(2, 10, 10,.25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+3,y+2,z - 2);
    draw_finger(2, 10, 10,.25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+4,y + 2,z - 1);
    draw_finger(2, 10, 10,.25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+5,y+2,z+1);
    draw_finger(2, 10, 10,.25);
    glPopMatrix();

    //metacarpals

    glPushMatrix();
    glTranslatef(x+1,y+2,z+2);
    gluCylinder(hand, .15,  .4, 1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+2,y+2,z+0);
    gluCylinder(hand, .15,  .4, 1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+3,y+2,z-1);
    gluCylinder(hand, .15,  .4, 1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+4,y+2,z+0);
    gluCylinder(hand, .15,  .4, 1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+5,y+2,z+2);
    gluCylinder(hand, .15,  .4, 1, 16, 16);
    glPopMatrix();
    //palm
    glPushMatrix();
    glTranslatef(x+1,y+2,z+3);
    gluCylinder(hand, .4,  .6, 1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+2,y+2,z+1);
    gluCylinder(hand, .4,  .6, 1.4, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+3,y+2,z+0);
    gluCylinder(hand, .4,  .6, 1, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+4,y+2,z+1);
    gluCylinder(hand, .4,  .6, 2, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+5,y+2,z+3);
    gluCylinder(hand, .4,  .6, 1, 16, 16);
    glPopMatrix();

    //ends
    glPushMatrix();
    glTranslatef(x+1,y+2,z+4);
    gluSphere(hand, .8, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+2,y+2,z+2.5);
    gluSphere(hand, .8, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+3,y+2,z+1);
    gluSphere(hand, .8, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+4,y+2,z+3);
    gluSphere(hand, .8, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+5,y+2,z+4);
    gluSphere(hand, .8, 10, 10);
    glPopMatrix();

    //hand edge
    glPushMatrix();
    glRotated(25, 0,1,0);
    glTranslatef(x+0,y+2,z+4);
    gluCylinder(hand, .4,  .6, 3.5, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glRotated(-25, 0,1,0);
    glTranslatef(x+5.5,y+2,z+3);
    gluCylinder(hand, .4,  .6, 3.75, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef( x+3.0f, y+2.0f, z+8.5f);
    gluSphere(hand, 1, 10, 10);
    glPopMatrix();


    glPushMatrix();
    glBegin( GL_TRIANGLES );
    glVertex3f( x+3.0f, y+2.0f, z+1.0f );
    glVertex3f( x+1.0f, y+2.0f, z+4.0f );
    glVertex3f( x+5.0f, y+2.0f, z+4.0f);

    glVertex3f( x+3.0f, y+1.5f, z+1.0f );
    glVertex3f( x+1.0f, y+1.5f, z+4.0f );
    glVertex3f( x+5.0f, y+1.5f, z+4.0f);
    glEnd();

    glBegin( GL_TRIANGLES );
    glVertex3f( x+1.0f, y+2.0f, z+4.0f );
    glVertex3f( x+5.0f, y+2.0f, z+4.0f);
    glVertex3f( x+3.0f, y+2.0f, z+8.0f );

    //glBegin( GL_TRIANGLES );
    glVertex3f( x+1.0f, y+1.5f, z+4.0f );
    glVertex3f( x+5.0f, y+1.5f, z+4.0f );
    glVertex3f( x+3.0f, y+1.5f, z+8.0f);
    glEnd();


    glBegin( GL_QUADS);
    glVertex3f( x+5.0f, y+2.0f, z+4.0f );
    glVertex3f( x+1.0f, y+2.0f, z+4.0f );
    glVertex3f( x+1.0f, y+1.5f, z+4.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void draw_toad(){
   //he's here, he's finally here!!
   if (lick){
   color_tongue();
   }//glDisable(GL_COLOR_MATERIAL);
   glPushMatrix();
   glTranslatef(0,0,0);
   draw_front_hand(-2,-2,-2);
   glPopMatrix();

   glPushMatrix();
   draw_eye(4.0,12.0,0.0);
   glPopMatrix();


   glPushMatrix();
   glBindTexture(GL_TEXTURE_2D, sun);
   glTranslated(12,0,-1);
   draw_front_hand(-2,-2,-2);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-5,0,20);
   draw_front_hand(-2,-2,-2);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(22,0,20);
   draw_front_hand(-2,-2,-2);
   glPopMatrix();

   glPushMatrix();
   glTranslated(0,0,0);
   draw_front_leg(-2.0,-2.0,-2.0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(14,-1.5,5);
   glRotated(180, 0,1,0);
   glRotated(-20, 1,0,0);
   glRotated(20, 0,0,1);
   glTranslated(0,0,0);
   draw_front_leg(-2.0,-2.0,-2.0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(22,+3.0,20);
   draw_back_leg(-2.0,-2.0,-2.0);
   glPopMatrix();

   glPushMatrix();
   glTranslated(-6,+3.0,20);
   draw_back_leg(-2.0,-2.0,-2.0);
   glPopMatrix();

   draw_body();


}
void  initSkybox(void)
{
    //a google search of 'easy rider skybox' yielded no usable results
    //so I guess this will have to do
    skybox[1] = LoadTexBMP("front.bmp"); //addfilename
    skybox[0] = LoadTexBMP("right.bmp");
    skybox[2] = LoadTexBMP("left.bmp");
    skybox[3] = LoadTexBMP("back.bmp");
    skybox[4] = LoadTexBMP("up.bmp");
    skybox[5] = LoadTexBMP("down.bmp");
}
/* 
 *  Draw sky box
 */

void drawSkybox(double D){
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, skybox[0]);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(-D, -D, -D);
        glTexCoord2f(1,0); glVertex3f(+D, -D, -D);
        glTexCoord2f(1,1); glVertex3f(+D, +D, -D);
        glTexCoord2f(0,1); glVertex3f(-D, +D, -D);
        glDisable(GL_TEXTURE_2D);
        glEnd();
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, skybox[1]);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(+D, -D, -D);
        glTexCoord2f(1,0); glVertex3f(+D, -D, +D);
        glTexCoord2f(1,1); glVertex3f(+D, +D, +D);
        glTexCoord2f(0,1); glVertex3f(+D, +D, -D);
        glDisable(GL_TEXTURE_2D);
        glEnd();
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, skybox[2]);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(+D, -D, +D);
        glTexCoord2f(1,0); glVertex3f(-D, -D, +D);
        glTexCoord2f(1,1); glVertex3f(-D, +D, +D);
        glTexCoord2f(0,1); glVertex3f(+D, +D, +D);
        glDisable(GL_TEXTURE_2D);
        glEnd();
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, skybox[3]);
        glBegin(GL_QUADS);;
        glTexCoord2f(0,0); glVertex3f(-D, -D, +D);
        glTexCoord2f(1,0); glVertex3f(-D, -D, -D);
        glTexCoord2f(1,1); glVertex3f(-D, +D, -D);
        glTexCoord2f(0,1); glVertex3f(-D, +D, +D);
        glDisable(GL_TEXTURE_2D);
        glEnd();
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, skybox[4]);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(-D, +D, -D);
        glTexCoord2f(1,0); glVertex3f(+D, +D, -D);
        glTexCoord2f(1,1); glVertex3f(+D, +D, +D);
        glTexCoord2f(0,1); glVertex3f(-D, +D, +D);
        glDisable(GL_TEXTURE_2D);
        glEnd();
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, skybox[5]);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(+D, -D, -D);
        glTexCoord2f(1,0); glVertex3f(-D, -D, -D);
        glTexCoord2f(1,1); glVertex3f(-D, -D, +D);
        glTexCoord2f(0,1); glVertex3f(+D, -D, +D);
        glDisable(GL_TEXTURE_2D);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    glNormal3f(0,0,0);

}

void drawScene()
{
    drawSkybox(6.5*dim);
}
/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */

static void ball(double x,double y,double z)
{

   //  This is jus to mark where the light comes from
   //Which lines up with the sun to be *cough* realistic
   int r=5;
    GLUquadric* ball = gluNewQuadric();
    gluQuadricNormals(ball, GLU_SMOOTH);
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   gluSphere(ball, 1.0,16,16);

   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   const double len=2.5;  //  Length of axes
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
      //  Enable Z-buffering in OpenGL
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_CULL_FACE);
      double Ex = Ox-2*dim*Sin(th)*Cos(ph);
      double Ey = Oy+2*dim        *Sin(ph);
      double Ez = Oz+2*dim*Cos(th)*Cos(ph);
      int mx = 0;
      int my = 0;
      int mz = 0;
      float Position[] = {0,60,40};
      //  Undo previous transformations
      glLoadIdentity();
      //  Perspective - set eye position
      gluLookAt(Ex,Ey,Ez , 0,0,0, 0,1,0);
      glDisable(GL_LIGHTING);
      drawSkybox(3.5*dim);

      glShadeModel(smooth?GL_SMOOTH:GL_FLAT);
       //  Light switch
       if (light)
       {
          //  Translate intensity to color vectors
          float Ambient[]   = {0,0,0,1.0};
          float Diffuse[]   = {1,1,1,1};
          float Specular[]  = {1,1,1,1};

          float white[] = {1.0,1.0,1.0,1.0};
          float Direction[] = {Cos(Th)*Sin(Ph),Sin(Th)*Sin(Ph),-Cos(Ph),0};
          ball(Position[0], Position[1], Position[2]);

          //  Enable lighting
          glEnable(GL_LIGHTING);
          glEnable(GL_NORMALIZE);
          glEnable(GL_COLOR_MATERIAL);

         // glColorMaterial(GL_COLOR_MATERIAL,GL_AMBIENT_AND_DIFFUSE);
          //  Set specular colors
          glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,2.0f);
          glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
          glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

          //  Enable light 0
          glEnable(GL_LIGHT0);
          //  Set ambient, diffuse, specular components and position of light 0
          glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
          glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
          glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
          glLightfv(GL_LIGHT0,GL_POSITION,Position);
       }
       else
          glDisable(GL_LIGHTING);
         draw_toad();
   //fly_fly(Position[0],Position[1],Position[2]); rip lil guy
   glWindowPos2i(5,5);
   //Print("Dennis Hopper: Toad King");
   if (light)
   glFlush();
   SDL_GL_SwapBuffers();
   }



/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void windowSpecial(int key,int x,int y) //because they are special snowflakes
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;

   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(fov,asp,dim);
}
/*
 *  GLUT calls this routine when a key is pressed
 */
int key()
{
   //  Exit on ESC
   Uint8* keys = SDL_GetKeyState(NULL);
   int shift = SDL_GetModState()&KMOD_SHIFT;
  //  Exit on ESC
   if (keys[SDLK_ESCAPE])
     return 0;
      //  Reset view angle
   else if (keys[SDLK_0])
         X = Y = th = ph = 0;
   else if (keys[SDLK_t])
         tongue = !(tongue);
   else if (keys[SDLK_l])
        light = !(light);
   else if (keys[SDLK_m])
           lick = !(lick);

   else if (keys[SDLK_RIGHT])
        th += 5;
     else if (keys[SDLK_LEFT])
        th -= 5;
     //  Increase/decrease elevation
     else if (keys[SDLK_UP])
        ph += 5;
     else if (keys[SDLK_DOWN])
        ph -= 5;
     //  PageUp key - increase dim
     else if (keys[SDLK_PAGEDOWN])
        dim += 0.1;
     //  PageDown key - decrease dim
     else if (keys[SDLK_PAGEUP] && dim>1)
        dim -= 0.1;
   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Update state
   return 1;
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(fov,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
    int run=1;
       double t0=0;
       Mix_Music* music;
       SDL_Surface* screen;

       //  Initialize SDL
       SDL_Init(SDL_INIT_VIDEO);
       //  Set size, resizable and double buffering
       screen = SDL_SetVideoMode(600,600,0,SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);
       if (!screen ) Fatal("Cannot set SDL video mode\n");
       //  Set window and icon labels
       SDL_WM_SetCaption("More Lighting - SDL","sdl20");
       //  Set screen size
       reshape(screen->w,screen->h);

       //  Load textures
       initSkybox(); //The textures coincidentally are what I plan to name my first three children
       sun = LoadTexBMP("sun.bmp");
       eye = LoadTexBMP("eye.bmp");
       cotton = LoadTexBMP("cotton.bmp");

       //  Initialize audio
       if (Mix_OpenAudio(44100,AUDIO_S16SYS,2,4096)) Fatal("Cannot initialize audio\n");
       //  Load "The Wall"
       //Original Music by JohnFatherJohn
       //Which is the coolest part of the whole thing
       //and I wish could be put to better use
       music = Mix_LoadMUS("toad.wav");
       if (!music) Fatal("Cannot load toad.wav\n");
       //  Play (looping)
       Mix_PlayMusic(music,-1);

       //  SDL event loop
       ErrCheck("init");
       while (run)
       {
          //  Elapsed time in seconds
          double t = SDL_GetTicks()/1000.0;
          //  Process all pending events
          SDL_Event event;
          while (SDL_PollEvent(&event))
             switch (event.type)
             {
                case SDL_VIDEORESIZE:
                   screen = SDL_SetVideoMode(event.resize.w,event.resize.h,0,SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);
                   reshape(screen->w,screen->h);
                   break;
                case SDL_QUIT:
                   run = 0;
                   break;
                case SDL_KEYDOWN:
                   run = key();
                   t0 = t+0.5;  // Wait 1/2 s before repeating
                   break;
                default:
                   //  Do nothing
                   break;
             }
          //  Repeat key every 50 ms
          if (t-t0>0.05)
          {
             run = key();
             t0 = t;
          }
          //  Display
          Th = fmod(90*t,360.0);
          display();
          //  Slow down display rate to about 100 fps by sleeping 5ms
          SDL_Delay(5);
       }
       //  Shut down SDL
       Mix_CloseAudio();
       SDL_Quit();
       return 0;

}