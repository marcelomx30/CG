#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "../include/Vector3.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

// Estado da vela
bool candleLit = true;

struct Camera {
    float x, y, z, yaw, pitch;
    Camera() : x(6.0f), y(1.8f), z(2.0f), yaw(0.0f), pitch(0.0f) {}

    void apply() {
        float tx = x + cosf(pitch) * sinf(yaw);
        float ty = y + sinf(pitch);
        float tz = z + cosf(pitch) * cosf(yaw);
        gluLookAt(x, y, z, tx, ty, tz, 0, 1, 0);
    }

    void move(float forward, float right, float up) {
        x += sinf(yaw) * forward + sinf(yaw + M_PI/2) * right;
        y += up;
        z += cosf(yaw) * forward + cosf(yaw + M_PI/2) * right;
    }

    void rotate(float dyaw, float dpitch) {
        yaw += dyaw;
        pitch = fmax(-1.47f, fmin(1.47f, pitch + dpitch));
    }
};

GLuint loadTexture(const char* file) {
    int w, h, ch;
    unsigned char* data = stbi_load(file, &w, &h, &ch, 4);
    if (!data) return 0;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    return tex;
}

void drawBox(float x, float y, float z, float w, float h, float d) {
    glPushMatrix();
    glTranslatef(x, y + h/2, z);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(-w,-h/2,d); glTexCoord2f(1,0); glVertex3f(w,-h/2,d);
    glTexCoord2f(1,1); glVertex3f(w,h/2,d); glTexCoord2f(0,1); glVertex3f(-w,h/2,d);
    glTexCoord2f(0,0); glVertex3f(w,-h/2,-d); glTexCoord2f(1,0); glVertex3f(-w,-h/2,-d);
    glTexCoord2f(1,1); glVertex3f(-w,h/2,-d); glTexCoord2f(0,1); glVertex3f(w,h/2,-d);
    glTexCoord2f(0,0); glVertex3f(-w,h/2,d); glTexCoord2f(1,0); glVertex3f(w,h/2,d);
    glTexCoord2f(1,1); glVertex3f(w,h/2,-d); glTexCoord2f(0,1); glVertex3f(-w,h/2,-d);
    glTexCoord2f(0,0); glVertex3f(-w,-h/2,-d); glTexCoord2f(1,0); glVertex3f(w,-h/2,-d);
    glTexCoord2f(1,1); glVertex3f(w,-h/2,d); glTexCoord2f(0,1); glVertex3f(-w,-h/2,d);
    glTexCoord2f(0,0); glVertex3f(-w,-h/2,-d); glTexCoord2f(1,0); glVertex3f(-w,-h/2,d);
    glTexCoord2f(1,1); glVertex3f(-w,h/2,d); glTexCoord2f(0,1); glVertex3f(-w,h/2,-d);
    glTexCoord2f(0,0); glVertex3f(w,-h/2,d); glTexCoord2f(1,0); glVertex3f(w,-h/2,-d);
    glTexCoord2f(1,1); glVertex3f(w,h/2,-d); glTexCoord2f(0,1); glVertex3f(w,h/2,d);
    glEnd();
    glPopMatrix();
}

void drawSphere(float x, float y, float z, float r) {
    glPushMatrix();
    glTranslatef(x, y, z);
    GLUquadric* q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);
    gluSphere(q, r, 16, 16);
    gluDeleteQuadric(q);
    glPopMatrix();
}

void drawCylinder(float x, float y, float z, float r, float h) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(-90, 1, 0, 0);
    GLUquadric* q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);
    gluCylinder(q, r, r, h, 16, 1);
    gluDeleteQuadric(q);
    glPopMatrix();
}

void drawCone(float x, float y, float z, float r, float h) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(-90, 1, 0, 0);
    GLUquadric* q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);
    gluCylinder(q, r, 0, h, 16, 1);
    gluDeleteQuadric(q);
    glPopMatrix();
}

void drawScene(GLuint wood, GLuint glass, GLuint wall) {
    // Chão (sem textura)
    glColor3f(0.6f, 0.5f, 0.4f);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0); glVertex3f(12,0,0); glVertex3f(12,0,20); glVertex3f(0,0,20);
    glEnd();

    // Paredes com textura própria
    glBindTexture(GL_TEXTURE_2D, wall);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Parede fundo (textura invertida verticalmente)
    glBegin(GL_QUADS);
    glTexCoord2f(0,2); glVertex3f(0,0,20);
    glTexCoord2f(3,2); glVertex3f(12,0,20);
    glTexCoord2f(3,0); glVertex3f(12,8,20);
    glTexCoord2f(0,0); glVertex3f(0,8,20);
    glEnd();

    // Parede esquerda (textura invertida verticalmente)
    glBegin(GL_QUADS);
    glTexCoord2f(0,2); glVertex3f(0,0,0);
    glTexCoord2f(5,2); glVertex3f(0,0,20);
    glTexCoord2f(5,0); glVertex3f(0,8,20);
    glTexCoord2f(0,0); glVertex3f(0,8,0);
    glEnd();

    // Parede direita (textura invertida verticalmente)
    glBegin(GL_QUADS);
    glTexCoord2f(0,2); glVertex3f(12,0,0);
    glTexCoord2f(5,2); glVertex3f(12,0,20);
    glTexCoord2f(5,0); glVertex3f(12,8,20);
    glTexCoord2f(0,0); glVertex3f(12,8,0);
    glEnd();

    // Teto (sem textura)
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(0.65f, 0.63f, 0.60f);
    glBegin(GL_QUADS);
    glVertex3f(0,8,0); glVertex3f(12,8,0); glVertex3f(12,8,20); glVertex3f(0,8,20);
    glEnd();

    // Altar com textura de madeira
    glBindTexture(GL_TEXTURE_2D, wood);
    glColor3f(1,1,1);
    drawBox(6, 0, 18, 1.5, 0.8, 0.5);

    // Bancos
    for(int i = 0; i < 4; i++) {
        float z = 5 + i * 3.0f;
        drawBox(2.5, 0, z, 1.2, 0.45, 0.25);
        drawBox(9.5, 0, z, 1.2, 0.45, 0.25);
    }

    // Vitral
    glBindTexture(GL_TEXTURE_2D, glass);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(5.4,3,19.9);
    glTexCoord2f(1,0); glVertex3f(6.6,3,19.9);
    glTexCoord2f(1,1); glVertex3f(6.6,5,19.9);
    glTexCoord2f(0,1); glVertex3f(5.4,5,19.9);
    glEnd();

    // Vitral topo triangular
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0,1); glVertex3f(5.4,5,19.9);
    glTexCoord2f(1,1); glVertex3f(6.6,5,19.9);
    glTexCoord2f(0.5,1.5); glVertex3f(6.0,5.8,19.9);
    glEnd();

    // Ostensório (ESFERA obrigatória - Hóstia)
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(0.95f, 0.95f, 0.9f);
    drawSphere(6, 1.4, 18, 0.14);

    // Base ostensório (CILINDRO obrigatório)
    glColor3f(0.9f, 0.75f, 0.3f);
    drawCylinder(6, 0.8, 18, 0.15, 0.3);

    // Raios dourados ao redor (no plano vertical XY - virado para frente)
    for(int i = 0; i < 8; i++) {
        float angle = i * 2 * M_PI / 8;
        float offsetX = 0.25f * cos(angle);  // Varia no eixo X (horizontal)
        float offsetY = 0.25f * sin(angle);  // Varia no eixo Y (vertical)
        drawSphere(6 + offsetX, 1.4 + offsetY, 18, 0.025);
    }

    // Vela (CILINDRO + CONE obrigatórios)
    if(candleLit) {
        glColor3f(0.8f, 0.2f, 0.15f);
    } else {
        glColor3f(0.3f, 0.3f, 0.3f); // Vela apagada (cinza)
    }
    drawCylinder(8, 0, 17.5, 0.12, 1.0);

    // Chama da vela (CONE obrigatório) - só aparece se acesa
    if(candleLit) {
        glColor3f(1.0f, 0.8f, 0.0f);
        drawCone(8, 1.0, 17.5, 0.08, 0.3);
    }
}

struct Pickable { string name; float x,y,z,r; };

string pick(int mx, int my, bool& toggleCandle) {
    vector<Pickable> objs = {
        {"Altar", 6,0.4f,18,2},
        {"Ostensório", 6,1.4f,18,0.3f},
        {"Vela", 8,0.5f,17.5,0.5f},
        {"Banco Esq 1", 2.5f,0.2f,5,1.5f},
        {"Banco Esq 2", 2.5f,0.2f,8,1.5f},
        {"Banco Esq 3", 2.5f,0.2f,11,1.5f},
        {"Banco Esq 4", 2.5f,0.2f,14,1.5f},
        {"Banco Dir 1", 9.5f,0.2f,5,1.5f},
        {"Banco Dir 2", 9.5f,0.2f,8,1.5f},
        {"Banco Dir 3", 9.5f,0.2f,11,1.5f},
        {"Banco Dir 4", 9.5f,0.2f,14,1.5f}
    };

    GLdouble mv[16], proj[16]; GLint vp[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, mv);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, vp);

    GLfloat z;
    glReadPixels(mx, HEIGHT-my, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

    GLdouble wx, wy, wz;
    gluUnProject(mx, HEIGHT-my, z, mv, proj, vp, &wx, &wy, &wz);

    Vector3 click(wx, wy, wz);
    float minDist = 999999;
    string closest = "";

    toggleCandle = false;
    for(auto& o : objs) {
        float d = (click - Vector3(o.x, o.y, o.z)).length();
        if(d < o.r * 1.5f && d < minDist) {
            minDist = d;
            closest = o.name;

            // Se clicou na vela, marca para alternar estado
            if(o.name == "Vela") {
                toggleCandle = true;
            }
        }
    }

    return closest.empty() ? "Nada" : closest;
}

int main() {
    cout << "CAPELA OPENGL - SOFTWARE RENDERING (SEM GPU)\n" << endl;
    cout << "Controles:" << endl;
    cout << "  W/A/S/D - Mover camera" << endl;
    cout << "  Q/E - Subir/Descer" << endl;
    cout << "  Setas - Rotacionar" << endl;
    cout << "  Mouse - Picking" << endl;
    cout << "  ESC - Sair\n" << endl;

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
    setenv("LIBGL_ALWAYS_SOFTWARE", "1", 1);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* win = SDL_CreateWindow("Capela OpenGL - Software Rendering",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GLContext ctx = SDL_GL_CreateContext(win);

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    cout << "OpenGL Renderer: " << renderer << endl;
    cout << "OpenGL Vendor: " << vendor << endl;

    string rstr = (const char*)renderer;
    if(rstr.find("llvmpipe") != string::npos ||
       rstr.find("Software") != string::npos ||
       rstr.find("Mesa") != string::npos) {
        cout << "✓ SOFTWARE RENDERING ATIVO (SEM GPU)\n" << endl;
    } else {
        cout << "⚠ Pode estar usando GPU!\n" << endl;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.3f, 0.35f, 0.4f, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (double)WIDTH/HEIGHT, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    // Luz principal
    GLfloat light0[] = {6, 6, 10, 1};
    GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1};
    GLfloat ambient[] = {0.3f, 0.3f, 0.3f, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    // Luz da vela
    GLfloat light1[] = {8, 1.1f, 17.5f, 1};
    GLfloat candle[] = {1.5f, 0.4f, 0.2f, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, light1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, candle);

    GLuint wood = loadTexture("textures/wood.jpg");
    GLuint glass = loadTexture("textures/stained_glass.jpg");
    GLuint wall = loadTexture("textures/wall.jpg");

    if(wood) cout << "✓ Textura madeira carregada" << endl;
    if(glass) cout << "✓ Textura vitral carregada" << endl;
    if(wall) cout << "✓ Textura parede carregada" << endl;
    cout << "\n✓ Cena possui: ESFERA + CILINDRO + CONE + MALHA (requisitos)\n" << endl;

    Camera cam;
    bool run = true;
    SDL_Event e;

    while(run) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) run = false;

            if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity();
                cam.apply();
                drawScene(wood, glass, wall);
                glFinish();

                bool shouldToggle = false;
                string pickedObj = pick(e.button.x, e.button.y, shouldToggle);
                cout << "🎯 PICKING: " << pickedObj;

                if(shouldToggle) {
                    candleLit = !candleLit;
                    if(candleLit) {
                        glEnable(GL_LIGHT1);
                        cout << " → 🕯️ Vela ACESA";
                    } else {
                        glDisable(GL_LIGHT1);
                        cout << " → 💨 Vela APAGADA";
                    }
                }
                cout << endl;
            }

            if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_ESCAPE: run = false; break;
                    case SDLK_w: cam.move(0.2f, 0, 0); break;
                    case SDLK_s: cam.move(-0.2f, 0, 0); break;
                    case SDLK_a: cam.move(0, -0.2f, 0); break;
                    case SDLK_d: cam.move(0, 0.2f, 0); break;
                    case SDLK_e: cam.move(0, 0, 0.2f); break;
                    case SDLK_q: cam.move(0, 0, -0.2f); break;
                    case SDLK_LEFT: cam.rotate(-0.03f, 0); break;
                    case SDLK_RIGHT: cam.rotate(0.03f, 0); break;
                    case SDLK_UP: cam.rotate(0, 0.03f); break;
                    case SDLK_DOWN: cam.rotate(0, -0.03f); break;
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        cam.apply();
        drawScene(wood, glass, wall);
        SDL_GL_SwapWindow(win);
    }

    glDeleteTextures(1, &wood);
    glDeleteTextures(1, &glass);
    glDeleteTextures(1, &wall);
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();

    cout << "\n✓ Programa encerrado." << endl;
    return 0;
}
