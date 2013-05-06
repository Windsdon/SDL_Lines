#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720

int main ( int argc, char** argv ) {
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);

    float w = WIDTH;
    float h = HEIGHT;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    atexit(SDL_Quit);

    SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_OPENGL|SDL_GL_DOUBLEBUFFER);
    if ( !screen ) {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }


    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0f);

    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, WIDTH, HEIGHT, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);

    int running = 1;
    int mousepos[2];
    int numSlopes = 20;
    double amplitude = 20;
    double origin[] = {WIDTH/2, HEIGHT/2};
    while(running) {
        int i;
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                running = 0;
            }
            if(e.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(mousepos, mousepos+1);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

//        glColor3f(1, 0, 0);
//
//        glBegin(GL_LINES);
//        {
//            glVertex2d(origin[0], origin[1]);
//            glVertex2d(mousepos[0], mousepos[1]);
//        }
//        glEnd();


        double angle = atan((mousepos[1] - origin[1])/(mousepos[0] - origin[0]))*180/3.141592;
        int c = (mousepos[0] < origin[0])?1:-1;
        //printf("Angle: %g\n", angle);
        glTranslated(origin[0], origin[1], 0);
        glRotated(angle, 0, 0, 1);
        glScaled(c*sqrt(pow(origin[0] - mousepos[0], 2) + pow(origin[1] - mousepos[1], 2)), c, 1);
        glTranslated(-origin[0], -origin[1], 0);


        glColor3f(1, 1, 1);

        glBegin(GL_LINE_STRIP);
        {
            //double factor = (amplitude/sqrt(pow((origin[1] - mousepos[1])/(mousepos[1] - origin[0]), 2) + 1));
            //double vx = factor*(origin[1] - mousepos[1])/(mousepos[1] - origin[0]);
            //double vy = factor;
            int k = -1;
            for(i = 0; i < 2*numSlopes + 1; i++) {
                double px = -(i/(2.0*numSlopes));
                //glVertex2d(origin[0] + px, origin[1] + amplitude);
                //glVertex2d(origin[0] + px, origin[1] - amplitude);

                glVertex2d(origin[0] + px, origin[1] + (!(i%2) ? 0 : -(k = -k))*amplitude);
            }
        }
        glEnd();

        SDL_GL_SwapBuffers();
    }

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
