#include "../include/Vector3.h"
#include "../include/Color.h"
#include "../include/Material.h"
#include "../include/Objects.h"
#include "../include/Lights.h"
#include "../include/Camera.h"
#include "../include/Scene.h"
#include <iostream>
#include <memory>

using namespace std;

// Textura xadrez
Color checkerboardTexture(const Vector3& point) {
    double scale = 1.0;
    int xSquare = static_cast<int>(floor(point.x / scale));
    int zSquare = static_cast<int>(floor(point.z / scale));
    bool isEven = (xSquare + zSquare) % 2 == 0;
    return isEven ? Color(0.8, 0.8, 0.8) : Color(0.3, 0.3, 0.3);
}

Scene createDemoScene() {
    Scene scene;
    scene.backgroundColor = Color(0.2, 0.2, 0.25);

    // Materiais
    Material matRed(Color(0.2, 0.0, 0.0), Color(0.8, 0.1, 0.1), Color(0.8, 0.8, 0.8), 50.0);
    Material matBlue(Color(0.0, 0.0, 0.2), Color(0.2, 0.3, 0.8), Color(0.9, 0.9, 0.9), 100.0);
    Material matGreen(Color(0.0, 0.2, 0.0), Color(0.3, 0.8, 0.3), Color(0.2, 0.2, 0.2), 10.0);
    Material matFloor(Color(0.3, 0.25, 0.2), Color(0.6, 0.5, 0.4), Color(0.1, 0.1, 0.1), 5.0, checkerboardTexture);

    // Objetos
    scene.addObject(make_shared<Sphere>(Vector3(5, 2, 5), 1.0, matRed, "Esfera Central"));
    scene.addObject(make_shared<Sphere>(Vector3(3, 1, 7), 0.8, matBlue, "Esfera Azul"));
    scene.addObject(make_shared<Cylinder>(Vector3(7, 0, 6), 0.5, 2.5, Vector3(0, 1, 0), matGreen, "Cilindro"));
    scene.addObject(make_shared<Plane>(Vector3(0, 0, 0), Vector3(0, 1, 0), matFloor, "Chao"));

    // Luzes
    scene.setAmbientLight(make_shared<AmbientLight>(Color(0.3, 0.3, 0.3)));
    scene.addLight(make_shared<PointLight>(Vector3(5, 6, 3), Color(0.8, 0.8, 0.8)));

    return scene;
}

int main() {
    cout << "========================================" << endl;
    cout << "DEMONSTRACAO DE PROJECOES" << endl;
    cout << "Perspectiva, Ortografica e Obliqua" << endl;
    cout << "========================================\n" << endl;

    Scene scene = createDemoScene();

    // Configuração da câmera (mesma posição para todas as projeções)
    Vector3 eye(10, 4, 2);
    Vector3 at(5, 2, 5);
    Vector3 up(0, 1, 0);
    int resolution = 400;

    // ============ PROJEÇÃO PERSPECTIVA ============
    cout << "Renderizando: PROJECAO PERSPECTIVA..." << endl;
    Camera cameraPerspective(eye, at, up, 3.0, 8.0, 8.0, resolution, resolution);
    cameraPerspective.setPerspective();

    Renderer rendererPersp(scene, cameraPerspective);
    rendererPersp.render("output/projecao_perspectiva.ppm");
    cout << "  ✓ Salvo: output/projecao_perspectiva.ppm\n" << endl;

    // ============ PROJEÇÃO ORTOGRÁFICA ============
    cout << "Renderizando: PROJECAO ORTOGRAFICA..." << endl;
    Camera cameraOrtho(eye, at, up, 3.0, 8.0, 8.0, resolution, resolution);
    cameraOrtho.setOrthographic();

    Renderer rendererOrtho(scene, cameraOrtho);
    rendererOrtho.render("output/projecao_ortografica.ppm");
    cout << "  ✓ Salvo: output/projecao_ortografica.ppm\n" << endl;

    // ============ PROJEÇÃO OBLÍQUA CAVALIER ============
    cout << "Renderizando: PROJECAO OBLIQUA (Cavalier)..." << endl;
    Camera cameraObliqueCav(eye, at, up, 3.0, 8.0, 8.0, resolution, resolution);
    cameraObliqueCav.setOblique(45.0, 1.0);  // Cavalier: 45°, fator 1.0

    Renderer rendererObliqueCav(scene, cameraObliqueCav);
    rendererObliqueCav.render("output/projecao_obliqua_cavalier.ppm");
    cout << "  ✓ Salvo: output/projecao_obliqua_cavalier.ppm\n" << endl;

    // ============ PROJEÇÃO OBLÍQUA CABINET ============
    cout << "Renderizando: PROJECAO OBLIQUA (Cabinet)..." << endl;
    Camera cameraObliqueCab(eye, at, up, 3.0, 8.0, 8.0, resolution, resolution);
    cameraObliqueCab.setObliqueCabinet();  // Cabinet: 63.4°, fator 0.5

    Renderer rendererObliqueCab(scene, cameraObliqueCab);
    rendererObliqueCab.render("output/projecao_obliqua_cabinet.ppm");
    cout << "  ✓ Salvo: output/projecao_obliqua_cabinet.ppm\n" << endl;

    cout << "========================================" << endl;
    cout << "DEMONSTRACAO COMPLETA!" << endl;
    cout << "========================================" << endl;
    cout << "\nResumo das projecoes:" << endl;
    cout << "  1. PERSPECTIVA:     Ponto de fuga, objetos distantes menores" << endl;
    cout << "  2. ORTOGRAFICA:     Raios paralelos, sem distorcao de tamanho" << endl;
    cout << "  3. OBLIQUA CAVALIER: 45°, fator 1.0 (profundidade preservada)" << endl;
    cout << "  4. OBLIQUA CABINET:  63.4°, fator 0.5 (profundidade reduzida)" << endl;
    cout << "\nTodas as imagens salvas em output/" << endl;

    return 0;
}
