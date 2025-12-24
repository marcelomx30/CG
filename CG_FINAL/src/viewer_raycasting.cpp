// VISUALIZADOR INTERATIVO COM RAY CASTING
// Usa o próprio ray tracer do projeto, mas em tempo real!
// Controles: WASD (mover), Space (subir), Shift (descer), ESC (sair)

#include <SDL2/SDL.h>
#include "../include/Vector3.h"
#include "../include/Color.h"
#include "../include/Ray.h"
#include "../include/Material.h"
#include "../include/Objects.h"
#include "../include/Lights.h"
#include "../include/Camera.h"
#include "../include/Scene.h"
#include <iostream>
#include <memory>
#include <cmath>
#include <chrono>

using namespace std;

// Configuração (resolução baixa para ser rápido!)
const int RENDER_WIDTH = 400;
const int RENDER_HEIGHT = 300;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float MOVE_SPEED = 2.0f;      // metros/segundo
const float ROTATE_SPEED = 60.0f;   // graus/segundo
const float MOUSE_SENSITIVITY = 0.2f;

// Texturas procedurais (mesmas do projeto)
Color woodTexture(const Vector3& point) {
    double frequency = 1.0;
    double grain = sin(point.y * frequency) * 0.5 + 0.5;
    if (grain > 0.5) {
        return Color(1.0, 0.8, 0.3);
    } else {
        return Color(0.3, 0.15, 0.05);
    }
}

Color stainedGlassTexture(const Vector3& point) {
    double u = (point.x - 5.4) / 1.2;
    double v = (point.y - 3.0) / 2.8;
    double cx = 0.5, cy = 0.5;
    double dx = u - cx;
    double dy = v - cy;
    double dist = sqrt(dx*dx + dy*dy);
    
    double crossWidth = 0.15;
    if (fabs(dx) < crossWidth || fabs(dy) < crossWidth) {
        return Color(1.0, 1.0, 0.0);
    }
    if (dist < 0.15) return Color(1.0, 1.0, 1.0);
    if (dist < 0.25) return Color(1.0, 0.0, 0.0);
    if (dist < 0.35) return Color(0.0, 0.5, 1.0);
    
    if (dx > 0 && dy > 0) return Color(0.0, 1.0, 0.0);
    else if (dx < 0 && dy > 0) return Color(1.0, 0.8, 0.0);
    else if (dx < 0 && dy < 0) return Color(1.0, 0.0, 1.0);
    else return Color(1.0, 0.5, 0.0);
}

// Cria a cena (mesma da capela)
void createScene(Scene& scene) {
    scene.backgroundColor = Color(0.3, 0.35, 0.4);
    
    // Materiais
    Material matAltar(Color(0.6,0.6,0.6), Color(0.9,0.9,0.9), Color(0.5,0.5,0.5), 30.0);
    Material matGold(Color(0.3,0.25,0.1), Color(0.9,0.75,0.3), Color(1.0,0.95,0.7), 100.0);
    Material matWall(Color(0.35,0.33,0.30), Color(0.7,0.68,0.65), Color(0.2,0.2,0.2), 10.0);
    Material matFloor(Color(0.3,0.25,0.18), Color(0.6,0.5,0.4), Color(0.3,0.25,0.2), 20.0);
    Material matCandle(Color(0.4,0.1,0.1), Color(0.8,0.2,0.15), Color(1.0,0.4,0.3), 60.0);
    Material matWood(Color(0.9,0.7,0.5), Color(0.9,0.7,0.5), Color(0.3,0.3,0.3), 20.0, woodTexture);
    Material matVitral(Color(1.0,1.0,1.0), Color(1.0,1.0,1.0), Color(0.5,0.5,0.5), 50.0, stainedGlassTexture);
    
    // Estrutura
    scene.addObject(make_shared<Plane>(Vector3(6,0,10), Vector3(0,1,0), matFloor));
    scene.addObject(make_shared<Plane>(Vector3(6,0,20), Vector3(0,0,-1), matWall));
    scene.addObject(make_shared<Plane>(Vector3(0,0,10), Vector3(1,0,0), matWall));
    scene.addObject(make_shared<Plane>(Vector3(12,0,10), Vector3(-1,0,0), matWall));
    scene.addObject(make_shared<Plane>(Vector3(6,8,10), Vector3(0,-1,0), matWall));
    
    // Altar simplificado (só base)
    auto altarBase = make_shared<Mesh>(matWood);
    double aW=1.5, aH=0.8, aD=0.5;
    Vector3 aC(6,0,18);
    Vector3 ab1(aC.x-aW,aC.y,aC.z-aD), ab2(aC.x+aW,aC.y,aC.z-aD);
    Vector3 ab3(aC.x+aW,aC.y,aC.z+aD), ab4(aC.x-aW,aC.y,aC.z+aD);
    Vector3 ab5(aC.x-aW,aC.y+aH,aC.z-aD), ab6(aC.x+aW,aC.y+aH,aC.z-aD);
    Vector3 ab7(aC.x+aW,aC.y+aH,aC.z+aD), ab8(aC.x-aW,aC.y+aH,aC.z+aD);
    altarBase->addTriangle(Triangle(ab1,ab2,ab6,matWood)); 
    altarBase->addTriangle(Triangle(ab1,ab6,ab5,matWood));
    altarBase->addTriangle(Triangle(ab4,ab3,ab7,matWood)); 
    altarBase->addTriangle(Triangle(ab4,ab7,ab8,matWood));
    altarBase->addTriangle(Triangle(ab1,ab4,ab8,matWood)); 
    altarBase->addTriangle(Triangle(ab1,ab8,ab5,matWood));
    altarBase->addTriangle(Triangle(ab2,ab3,ab7,matWood)); 
    altarBase->addTriangle(Triangle(ab2,ab7,ab6,matWood));
    altarBase->addTriangle(Triangle(ab5,ab6,ab7,matWood)); 
    altarBase->addTriangle(Triangle(ab5,ab7,ab8,matWood));
    scene.addObject(altarBase);
    
    // Ostensório simplificado (só algumas esferas)
    Vector3 ostCenter(6, aH + 0.6, 18);
    scene.addObject(make_shared<Cone>(Vector3(6, aH, 18), 0.2, 0.3, Vector3(0, 1, 0), matGold));
    scene.addObject(make_shared<Sphere>(ostCenter, 0.14, matAltar));
    
    // Alguns raios
    for(int i=0; i<7; i++) {
        double angle = i * 2*M_PI/7;
        scene.addObject(make_shared<Sphere>(
            Vector3(ostCenter.x + 0.3*cos(angle), ostCenter.y + 0.3*sin(angle), ostCenter.z),
            0.03, matGold
        ));
    }
    
    // Vitral
    auto vitral = make_shared<Mesh>(matVitral);
    Vector3 vb1(5.4, 3.0, 19.5), vb2(6.6, 3.0, 19.5);
    Vector3 vb3(6.6, 5.0, 19.5), vb4(5.4, 5.0, 19.5);
    Vector3 vtop(6.0, 5.8, 19.5);
    vitral->addTriangle(Triangle(vb1, vb2, vb3, matVitral));
    vitral->addTriangle(Triangle(vb1, vb3, vb4, matVitral));
    vitral->addTriangle(Triangle(vb4, vb3, vtop, matVitral));
    scene.addObject(vitral);
    
    // Alguns bancos
    for(int fila=0; fila<4; fila++) {  // Menos bancos para ser mais rápido
        double zPos = 3 + fila*2.2;
        for(int lado=0; lado<2; lado++) {
            double xPos = (lado == 0) ? 2.0 : 10.0;
            auto b = make_shared<Mesh>(matWood);
            double bW=1.0, bH=0.45, bD=0.25;
            Vector3 bC(xPos,0,zPos);
            Vector3 v1(bC.x-bW,bC.y,bC.z-bD), v2(bC.x+bW,bC.y,bC.z-bD);
            Vector3 v3(bC.x+bW,bC.y,bC.z+bD), v4(bC.x-bW,bC.y,bC.z+bD);
            Vector3 v5(bC.x-bW,bC.y+bH,bC.z-bD), v6(bC.x+bW,bC.y+bH,bC.z-bD);
            Vector3 v7(bC.x+bW,bC.y+bH,bC.z+bD), v8(bC.x-bW,bC.y+bH,bC.z+bD);
            b->addTriangle(Triangle(v1,v2,v6,matWood)); 
            b->addTriangle(Triangle(v1,v6,v5,matWood));
            b->addTriangle(Triangle(v5,v6,v7,matWood)); 
            b->addTriangle(Triangle(v5,v7,v8,matWood));
            scene.addObject(b);
        }
    }
    
    // Vela
    scene.addObject(make_shared<Cylinder>(Vector3(8,1.1,17.5), 0.12, 0.3, Vector3(0,1,0), matCandle));
    
    // Luzes
    scene.setAmbientLight(make_shared<AmbientLight>(Color(0.3,0.3,0.3)));
    scene.addLight(make_shared<DirectionalLight>(Vector3(0,-0.6,0.4), Color(0.3,0.3,0.3)));
    scene.addLight(make_shared<PointLight>(Vector3(6,5,17), Color(0.3,0.3,0.3)));
    scene.addLight(make_shared<PointLight>(Vector3(8,1.25,17.5), Color(2.0,0.5,0.3)));
}

int main() {
    cout << "========================================" << endl;
    cout << "  VISUALIZADOR INTERATIVO - RAY CASTING" << endl;
    cout << "========================================" << endl;
    cout << "Controles:" << endl;
    cout << "  W/A/S/D - Mover (frente/esquerda/trás/direita)" << endl;
    cout << "  Space - Subir" << endl;
    cout << "  Shift - Descer" << endl;
    cout << "  Setas - Olhar ao redor" << endl;
    cout << "  ESC - Sair" << endl;
    cout << "========================================" << endl;
    
    // Inicializa SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Erro ao inicializar SDL: " << SDL_GetError() << endl;
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow(
        "Ray Casting Interativo - Capela",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    if (!window) {
        cerr << "Erro ao criar janela: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB888,
        SDL_TEXTUREACCESS_STREAMING,
        RENDER_WIDTH, RENDER_HEIGHT
    );
    
    // Cria cena
    Scene scene;
    createScene(scene);
    cout << "Cena criada com " << scene.objects.size() << " objetos" << endl;
    
    // Posição inicial da câmera
    Vector3 cameraPos(6, 1.8, 12);
    Vector3 cameraAt(6, 1.5, 18);
    Vector3 cameraUp(0, 1, 0);
    float yaw = 90.0f;    // Olhando para frente
    float pitch = 0.0f;
    
    // Buffer de pixels
    vector<Uint32> pixels(RENDER_WIDTH * RENDER_HEIGHT);
    
    bool running = true;
    SDL_Event event;
    
    auto lastTime = chrono::high_resolution_clock::now();
    int frameCount = 0;
    double fpsTime = 0.0;
    
    cout << "\nRenderizando..." << endl;
    
    while (running) {
        // Calcula delta time
        auto currentTime = chrono::high_resolution_clock::now();
        float deltaTime = chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        // FPS
        fpsTime += deltaTime;
        frameCount++;
        if (fpsTime >= 1.0) {
            cout << "FPS: " << frameCount << " | Pos: (" 
                 << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << ")" << endl;
            frameCount = 0;
            fpsTime = 0.0;
        }
        
        // Input
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || 
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }
        
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        
        // Calcula direção da câmera
        float radYaw = yaw * M_PI / 180.0f;
        float dirX = cos(radYaw);
        float dirZ = sin(radYaw);
        float rightX = cos(radYaw + M_PI/2);
        float rightZ = sin(radYaw + M_PI/2);
        
        // Movimento
        float speed = MOVE_SPEED * deltaTime;
        if (keys[SDL_SCANCODE_W]) {
            cameraPos.x += dirX * speed;
            cameraPos.z += dirZ * speed;
        }
        if (keys[SDL_SCANCODE_S]) {
            cameraPos.x -= dirX * speed;
            cameraPos.z -= dirZ * speed;
        }
        if (keys[SDL_SCANCODE_D]) {
            cameraPos.x += rightX * speed;
            cameraPos.z += rightZ * speed;
        }
        if (keys[SDL_SCANCODE_A]) {
            cameraPos.x -= rightX * speed;
            cameraPos.z -= rightZ * speed;
        }
        if (keys[SDL_SCANCODE_SPACE]) {
            cameraPos.y += speed;
        }
        if (keys[SDL_SCANCODE_LSHIFT]) {
            cameraPos.y -= speed;
        }
        
        // Rotação com setas
        float rotSpeed = ROTATE_SPEED * deltaTime;
        if (keys[SDL_SCANCODE_LEFT]) yaw -= rotSpeed;
        if (keys[SDL_SCANCODE_RIGHT]) yaw += rotSpeed;
        if (keys[SDL_SCANCODE_UP]) pitch += rotSpeed;
        if (keys[SDL_SCANCODE_DOWN]) pitch -= rotSpeed;
        
        // Limita pitch
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
        
        // Atualiza direção
        float radPitch = pitch * M_PI / 180.0f;
        dirX = cos(radPitch) * cos(radYaw);
        float dirY = sin(radPitch);
        dirZ = cos(radPitch) * sin(radYaw);
        
        cameraAt = Vector3(cameraPos.x + dirX, cameraPos.y + dirY, cameraPos.z + dirZ);
        
        // Cria câmera
        Camera camera(cameraPos, cameraAt, cameraUp, 1.0, 4.0, 3.0, RENDER_WIDTH, RENDER_HEIGHT);
        
        // RENDERIZA COM RAY CASTING!
        for (int j = 0; j < RENDER_HEIGHT; j++) {
            for (int i = 0; i < RENDER_WIDTH; i++) {
                Ray ray = camera.getRay(i, j);
                Color pixelColor = scene.traceRay(ray);
                
                int r = (int)(255.99 * pixelColor.r);
                int g = (int)(255.99 * pixelColor.g);
                int b = (int)(255.99 * pixelColor.b);
                
                // Clamp
                r = (r < 0) ? 0 : (r > 255) ? 255 : r;
                g = (g < 0) ? 0 : (g > 255) ? 255 : g;
                b = (b < 0) ? 0 : (b > 255) ? 255 : b;
                
                pixels[j * RENDER_WIDTH + i] = (r << 16) | (g << 8) | b;
            }
        }
        
        // Atualiza textura e desenha
        SDL_UpdateTexture(texture, NULL, pixels.data(), RENDER_WIDTH * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    
    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    cout << "\nEncerrando..." << endl;
    return 0;
}
