#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720

int main ( int argc, char** argv ) {
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);

    float px = 0, py = 0;
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


    while(1){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_KEYDOWN){
                px += 10;
                py += 10;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        glColor3f(1, 1, 1);

        glBegin(GL_QUADS);
        {
            glVertex2d(w/3.0 + px, h/3.0 + py);
            glVertex2d(w/3.0 + px, 2*h/3.0 + py);
            glVertex2d(2*w/3.0 + px, 2*h/3.0 + py);
            glVertex2d(2*w/3.0 + px, h/3.0 + py);
        }
        glEnd();

        SDL_GL_SwapBuffers();
    }

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
