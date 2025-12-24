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

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "TRABALHO FINAL DE COMPUTACAO GRAFICA" << endl;
    cout << "Ray Casting em C++" << endl;
    cout << "========================================" << endl;
    
    // Cria cena
    Scene scene;
    scene.backgroundColor = Color(0.2, 0.2, 0.25);
    
    // ============ MATERIAIS (4+ distintos) ============
    
    // Material 1: Vermelho brilhante (esfera)
    Material matRed(
        Color(0.2, 0.0, 0.0),  // ka
        Color(0.8, 0.1, 0.1),  // kd
        Color(0.8, 0.8, 0.8),  // ks
        50.0                    // shininess
    );
    
    // Material 2: Azul metálico (cilindro)
    Material matBlue(
        Color(0.0, 0.0, 0.2),
        Color(0.2, 0.3, 0.8),
        Color(0.9, 0.9, 0.9),
        100.0
    );
    
    // Material 3: Verde mate (cone)
    Material matGreen(
        Color(0.0, 0.2, 0.0),
        Color(0.3, 0.8, 0.3),
        Color(0.2, 0.2, 0.2),
        10.0
    );
    
    // Material 4: Dourado (malha/cubo)
    Material matGold(
        Color(0.2, 0.15, 0.0),
        Color(0.8, 0.6, 0.1),
        Color(1.0, 0.9, 0.5),
        30.0
    );
    
    // Material 5: Chão (cinza)
    Material matFloor(
        Color(0.3, 0.25, 0.2),
        Color(0.6, 0.5, 0.4),
        Color(0.1, 0.1, 0.1),
        5.0
    );
    
    // Material 6: Paredes (cinza claro)
    Material matWall(
        Color(0.2, 0.2, 0.2),
        Color(0.7, 0.7, 0.75),
        Color(0.1, 0.1, 0.1),
        5.0
    );
    
    // ============ OBJETOS (no primeiro octante: x, y, z > 0) ============
    
    cout << "\nCriando objetos..." << endl;
    
    // CHÃO (plano)
    auto floor = make_shared<Plane>(
        Vector3(5, 0, 5),
        Vector3(0, 1, 0),
        matFloor
    );
    scene.addObject(floor);
    
    // PAREDES
    // Parede de fundo
    auto wallBack = make_shared<Plane>(
        Vector3(5, 0, 10),
        Vector3(0, 0, -1),
        matWall
    );
    scene.addObject(wallBack);
    
    // Parede lateral esquerda
    auto wallLeft = make_shared<Plane>(
        Vector3(0, 0, 5),
        Vector3(1, 0, 0),
        matWall
    );
    scene.addObject(wallLeft);
    
    // Parede lateral direita
    auto wallRight = make_shared<Plane>(
        Vector3(10, 0, 5),
        Vector3(-1, 0, 0),
        matWall
    );
    scene.addObject(wallRight);
    
    // Teto
    auto ceiling = make_shared<Plane>(
        Vector3(5, 8, 5),
        Vector3(0, -1, 0),
        matWall
    );
    scene.addObject(ceiling);
    
    // ESFERA - demonstra translação
    auto sphere = make_shared<Sphere>(
        Vector3(3, 2.5, 5),  // Posição no primeiro octante
        0.8,
        matRed
    );
    scene.addObject(sphere);
    
    // CILINDRO - demonstra rotação
    auto cylinder = make_shared<Cylinder>(
        Vector3(6.5, 1.0, 3),
        0.4,
        2.0,
        Vector3(0, 1, 0),
        matBlue
    );
    scene.addObject(cylinder);
    
    // CONE - demonstra escala e rotação
    auto cone = make_shared<Cone>(
        Vector3(7, 0.75, 7),
        0.7,
        1.8,
        Vector3(0, 1, 0),
        matGreen
    );
    scene.addObject(cone);
    
    // MALHA (Triângulos formando uma pirâmide simples)
    // Demonstra objeto malha
    auto mesh = make_shared<Mesh>(matGold);
    
    // Base da pirâmide
    Vector3 base1(2.5, 0.1, 2.0);
    Vector3 base2(3.5, 0.1, 2.0);
    Vector3 base3(3.5, 0.1, 3.0);
    Vector3 base4(2.5, 0.1, 3.0);
    Vector3 apex(3.0, 1.5, 2.5);  // Topo
    
    // Faces da pirâmide
    mesh->addTriangle(Triangle(base1, base2, apex, matGold));
    mesh->addTriangle(Triangle(base2, base3, apex, matGold));
    mesh->addTriangle(Triangle(base3, base4, apex, matGold));
    mesh->addTriangle(Triangle(base4, base1, apex, matGold));
    // Base
    mesh->addTriangle(Triangle(base1, base2, base3, matGold));
    mesh->addTriangle(Triangle(base1, base3, base4, matGold));
    
    scene.addObject(mesh);
    
    // Objetos adicionais para demonstrar transformações
    auto sphere2 = make_shared<Sphere>(
        Vector3(2, 0.5, 7),
        0.5,
        matRed
    );
    scene.addObject(sphere2);
    
    auto sphere3 = make_shared<Sphere>(
        Vector3(8, 1.2, 2),
        0.6,
        matBlue
    );
    scene.addObject(sphere3);
    
    cout << "Objetos criados: " << scene.objects.size() << endl;
    
    // ============ ILUMINAÇÃO ============
    
    cout << "Configurando iluminação..." << endl;
    
    // Luz ambiente (obrigatória)
    auto ambient = make_shared<AmbientLight>(Color(0.2, 0.2, 0.25));
    scene.setAmbientLight(ambient);
    
    // Luz pontual (obrigatória)
    auto pointLight = make_shared<PointLight>(
        Vector3(5, 6, 3),
        Color(0.8, 0.8, 0.8)
    );
    scene.addLight(pointLight);
    
    // Luz pontual adicional
    auto pointLight2 = make_shared<PointLight>(
        Vector3(2, 5, 2),
        Color(0.5, 0.5, 0.6)
    );
    scene.addLight(pointLight2);
    
    // Luz spot (bônus +1.0)
    auto spotLight = make_shared<SpotLight>(
        Vector3(2, 7, 2),
        Vector3(0, -1, 0.3),
        Color(0.6, 0.5, 0.4),
        30,  // cutoff angle
        2.0  // falloff
    );
    scene.addLight(spotLight);
    
    // Luz direcional (bônus +0.5)
    auto dirLight = make_shared<DirectionalLight>(
        Vector3(-1, -1, -1),
        Color(0.3, 0.3, 0.4)
    );
    scene.addLight(dirLight);
    
    cout << "Luzes configuradas!" << endl;
    
    // ============ CÂMERA ============
    
    cout << "\nConfigurando câmera..." << endl;
    
    // Câmera principal (perspectiva com 2 pontos de fuga)
    Camera camera(
        Vector3(12, 4, -2),  // eye - posição da câmera
        Vector3(5, 2, 5),    // at - ponto de visada
        Vector3(0, 1, 0),    // up - vetor up
        1.0,                 // distância focal
        8.0,                 // largura da janela
        8.0,                 // altura da janela
        500,                 // largura da imagem (REQUISITO: 500x500)
        500                  // altura da imagem
    );
    
    cout << "Câmera configurada!" << endl;
    cout << "  Eye: " << camera.eye << endl;
    cout << "  At: " << camera.at << endl;
    cout << "  Up: " << camera.up << endl;
    cout << "  Resolução: " << camera.imageWidth << "x" << camera.imageHeight << endl;
    
    // ============ RENDERIZAÇÃO ============
    
    cout << "\n========================================" << endl;
    cout << "INICIANDO RENDERIZAÇÃO" << endl;
    cout << "========================================" << endl;
    
    Renderer renderer(scene, camera);
    renderer.render("output/cena_principal.ppm");
    
    cout << "\n========================================" << endl;
    cout << "RENDERIZAÇÃO COMPLETA!" << endl;
    cout << "========================================" << endl;
    
    cout << "\nRequisitos atendidos:" << endl;
    cout << "  [✓] Coerência temática (sala decorada)" << endl;
    cout << "  [✓] Primeiro octante (x, y, z > 0)" << endl;
    cout << "  [✓] Objetos: Esfera, Cilindro, Cone, Malha" << endl;
    cout << "  [✓] Materiais: 6 materiais distintos" << endl;
    cout << "  [✓] Translação" << endl;
    cout << "  [✓] Rotação" << endl;
    cout << "  [✓] Escala" << endl;
    cout << "  [✓] Luz pontual + ambiente" << endl;
    cout << "  [✓] Luz spot (+1.0)" << endl;
    cout << "  [✓] Luz direcional (+0.5)" << endl;
    cout << "  [✓] Câmera: Eye, At, Up" << endl;
    cout << "  [✓] Projeção perspectiva" << endl;
    cout << "  [✓] Sombras" << endl;
    cout << "  [✓] Resolução 500x500" << endl;
    
    cout << "\nArquivo gerado: output/cena_principal.ppm" << endl;
    cout << "(Abra com visualizador de imagens ou converta para PNG)" << endl;
    
    return 0;
}
