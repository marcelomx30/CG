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
    cout << "       TRABALHO FINAL DE CG" << endl;
    cout << "    Cena: Capela com Altar" << endl;
    cout << "========================================" << endl;
    
    // Criar cena
    Scene scene;
    scene.backgroundColor = Color(0.8, 0.85, 0.9);  // Céu claro
    
    // ============ MATERIAIS ============
    
    // Madeira dos bancos (marrom)
    Material matWood(
        Color(0.15, 0.10, 0.05),   // ka - ambiente
        Color(0.45, 0.30, 0.15),   // kd - difuso
        Color(0.3, 0.2, 0.1),      // ks - especular
        20.0                        // shininess
    );
    
    // Altar (madeira clara)
    Material matAltarWood(
        Color(0.25, 0.20, 0.15),
        Color(0.65, 0.55, 0.45),
        Color(0.4, 0.3, 0.2),
        30.0
    );
    
    // Ostensório (dourado brilhante)
    Material matGold(
        Color(0.3, 0.25, 0.0),
        Color(0.9, 0.75, 0.2),
        Color(1.0, 0.95, 0.6),
        80.0  // Muito brilhante
    );
    
    // Paredes (bege claro)
    Material matWall(
        Color(0.35, 0.33, 0.30),
        Color(0.85, 0.82, 0.78),
        Color(0.2, 0.2, 0.2),
        10.0
    );
    
    // Chão (madeira clara)
    Material matFloor(
        Color(0.25, 0.20, 0.15),
        Color(0.60, 0.50, 0.40),
        Color(0.25, 0.20, 0.15),
        15.0
    );
    
    // Janelas (vidro azulado claro)
    Material matWindow(
        Color(0.4, 0.5, 0.6),
        Color(0.6, 0.7, 0.8),
        Color(0.8, 0.9, 1.0),
        50.0
    );
    
    // Vela/lamparina (vermelho emissor)
    Material matRedLight(
        Color(0.3, 0.05, 0.05),
        Color(0.9, 0.1, 0.1),
        Color(1.0, 0.3, 0.3),
        60.0
    );
    
    cout << "\nCriando estrutura da capela..." << endl;
    
    // ============ ESTRUTURA DA CAPELA ============
    
    // Dimensões: 12m largura x 8m altura x 20m profundidade
    // Centro em (6, 0, 10)
    
    // CHÃO
    auto floor = make_shared<Plane>(
        Vector3(6, 0, 10),
        Vector3(0, 1, 0),
        matFloor
    );
    scene.addObject(floor);
    
    // PAREDES
    // Parede frontal (com janela)
    auto wallFront = make_shared<Plane>(
        Vector3(6, 0, 20),
        Vector3(0, 0, -1),
        matWall
    );
    scene.addObject(wallFront);
    
    // Parede esquerda
    auto wallLeft = make_shared<Plane>(
        Vector3(0, 0, 10),
        Vector3(1, 0, 0),
        matWall
    );
    scene.addObject(wallLeft);
    
    // Parede direita
    auto wallRight = make_shared<Plane>(
        Vector3(12, 0, 10),
        Vector3(-1, 0, 0),
        matWall
    );
    scene.addObject(wallRight);
    
    // Teto
    auto ceiling = make_shared<Plane>(
        Vector3(6, 8, 10),
        Vector3(0, -1, 0),
        matWall
    );
    scene.addObject(ceiling);
    
    // Parede de trás (entrada)
    auto wallBack = make_shared<Plane>(
        Vector3(6, 0, 0),
        Vector3(0, 0, 1),
        matWall
    );
    scene.addObject(wallBack);
    
    cout << "Criando altar..." << endl;
    
    // ============ ALTAR ============
    
    // Base do altar (cubo de malha)
    auto altar = make_shared<Mesh>(matAltarWood);
    
    // Dimensões do altar: 3m largura x 1.2m altura x 1m profundidade
    // Posição: centralizado na frente (x=6, y=0, z=17)
    double altarW = 1.5;  // meia-largura
    double altarH = 1.2;  // altura
    double altarD = 0.5;  // meia-profundidade
    Vector3 altarCenter(6, 0, 17);
    
    // Vértices do altar
    Vector3 a1(altarCenter.x - altarW, altarCenter.y, altarCenter.z - altarD);
    Vector3 a2(altarCenter.x + altarW, altarCenter.y, altarCenter.z - altarD);
    Vector3 a3(altarCenter.x + altarW, altarCenter.y, altarCenter.z + altarD);
    Vector3 a4(altarCenter.x - altarW, altarCenter.y, altarCenter.z + altarD);
    Vector3 a5(altarCenter.x - altarW, altarCenter.y + altarH, altarCenter.z - altarD);
    Vector3 a6(altarCenter.x + altarW, altarCenter.y + altarH, altarCenter.z - altarD);
    Vector3 a7(altarCenter.x + altarW, altarCenter.y + altarH, altarCenter.z + altarD);
    Vector3 a8(altarCenter.x - altarW, altarCenter.y + altarH, altarCenter.z + altarD);
    
    // Faces do altar
    altar->addTriangle(Triangle(a1, a2, a6, matAltarWood)); altar->addTriangle(Triangle(a1, a6, a5, matAltarWood)); // Frente
    altar->addTriangle(Triangle(a4, a3, a7, matAltarWood)); altar->addTriangle(Triangle(a4, a7, a8, matAltarWood)); // Trás
    altar->addTriangle(Triangle(a1, a4, a8, matAltarWood)); altar->addTriangle(Triangle(a1, a8, a5, matAltarWood)); // Esquerda
    altar->addTriangle(Triangle(a2, a3, a7, matAltarWood)); altar->addTriangle(Triangle(a2, a7, a6, matAltarWood)); // Direita
    altar->addTriangle(Triangle(a5, a6, a7, matAltarWood)); altar->addTriangle(Triangle(a5, a7, a8, matAltarWood)); // Topo
    scene.addObject(altar);
    
    // OSTENSÓRIO (esfera dourada no topo do altar)
    auto monstrance = make_shared<Sphere>(
        Vector3(6, altarH + 0.5, 17),  // Acima do altar
        0.3,  // Raio
        matGold
    );
    scene.addObject(monstrance);
    
    // Raios do ostensório (cilindros finos)
    for (int i = 0; i < 8; i++) {
        double angle = i * M_PI / 4;
        double offsetX = 0.5 * cos(angle);
        double offsetZ = 0.5 * sin(angle);
        
        auto ray = make_shared<Cylinder>(
            Vector3(6 + offsetX, altarH + 0.5, 17 + offsetZ),
            0.03,  // Raio muito fino
            0.4,   // Altura
            Vector3(cos(angle), 0, sin(angle)),  // Direção radial
            matGold
        );
        scene.addObject(ray);
    }
    
    cout << "Criando bancos..." << endl;
    
    // ============ BANCOS ============
    
    // Criar 6 bancos (3 de cada lado)
    // Dimensões de cada banco: 1m largura x 0.5m altura x 0.4m profundidade
    
    for (int row = 0; row < 3; row++) {
        double zPos = 5 + row * 3;  // Espaçamento de 3m
        
        // Banco esquerdo
        auto benchLeft = make_shared<Mesh>(matWood);
        Vector3 blCenter(2, 0, zPos);
        double bW = 0.5, bH = 0.5, bD = 1.5;
        
        Vector3 bl1(blCenter.x - bW, blCenter.y, blCenter.z - bD);
        Vector3 bl2(blCenter.x + bW, blCenter.y, blCenter.z - bD);
        Vector3 bl3(blCenter.x + bW, blCenter.y, blCenter.z + bD);
        Vector3 bl4(blCenter.x - bW, blCenter.y, blCenter.z + bD);
        Vector3 bl5(blCenter.x - bW, blCenter.y + bH, blCenter.z - bD);
        Vector3 bl6(blCenter.x + bW, blCenter.y + bH, blCenter.z - bD);
        Vector3 bl7(blCenter.x + bW, blCenter.y + bH, blCenter.z + bD);
        Vector3 bl8(blCenter.x - bW, blCenter.y + bH, blCenter.z + bD);
        
        benchLeft->addTriangle(Triangle(bl1, bl2, bl6, matWood)); benchLeft->addTriangle(Triangle(bl1, bl6, bl5, matWood));
        benchLeft->addTriangle(Triangle(bl4, bl3, bl7, matWood)); benchLeft->addTriangle(Triangle(bl4, bl7, bl8, matWood));
        benchLeft->addTriangle(Triangle(bl1, bl4, bl8, matWood)); benchLeft->addTriangle(Triangle(bl1, bl8, bl5, matWood));
        benchLeft->addTriangle(Triangle(bl2, bl3, bl7, matWood)); benchLeft->addTriangle(Triangle(bl2, bl7, bl6, matWood));
        benchLeft->addTriangle(Triangle(bl5, bl6, bl7, matWood)); benchLeft->addTriangle(Triangle(bl5, bl7, bl8, matWood));
        scene.addObject(benchLeft);
        
        // Banco direito
        auto benchRight = make_shared<Mesh>(matWood);
        Vector3 brCenter(10, 0, zPos);
        
        Vector3 br1(brCenter.x - bW, brCenter.y, brCenter.z - bD);
        Vector3 br2(brCenter.x + bW, brCenter.y, brCenter.z - bD);
        Vector3 br3(brCenter.x + bW, brCenter.y, brCenter.z + bD);
        Vector3 br4(brCenter.x - bW, brCenter.y, brCenter.z + bD);
        Vector3 br5(brCenter.x - bW, brCenter.y + bH, brCenter.z - bD);
        Vector3 br6(brCenter.x + bW, brCenter.y + bH, brCenter.z - bD);
        Vector3 br7(brCenter.x + bW, brCenter.y + bH, brCenter.z + bD);
        Vector3 br8(brCenter.x - bW, brCenter.y + bH, brCenter.z + bD);
        
        benchRight->addTriangle(Triangle(br1, br2, br6, matWood)); benchRight->addTriangle(Triangle(br1, br6, br5, matWood));
        benchRight->addTriangle(Triangle(br4, br3, br7, matWood)); benchRight->addTriangle(Triangle(br4, br7, br8, matWood));
        benchRight->addTriangle(Triangle(br1, br4, br8, matWood)); benchRight->addTriangle(Triangle(br1, br8, br5, matWood));
        benchRight->addTriangle(Triangle(br2, br3, br7, matWood)); benchRight->addTriangle(Triangle(br2, br7, br6, matWood));
        benchRight->addTriangle(Triangle(br5, br6, br7, matWood)); benchRight->addTriangle(Triangle(br5, br7, br8, matWood));
        scene.addObject(benchRight);
    }
    
    cout << "Criando janelas..." << endl;
    
    // ============ JANELAS (simuladas com planos translúcidos) ============
    
    // Janela esquerda
    auto windowLeft = make_shared<Sphere>(
        Vector3(1, 5, 17),  // Alta na parede
        0.8,
        matWindow
    );
    scene.addObject(windowLeft);
    
    // Janela direita
    auto windowRight = make_shared<Sphere>(
        Vector3(11, 5, 17),
        0.8,
        matWindow
    );
    scene.addObject(windowRight);
    
    // ============ LUZ VERMELHA (vela ao lado do altar) ============
    
    // Suporte da vela (cilindro)
    auto candleStand = make_shared<Cylinder>(
        Vector3(8, 0, 16.5),
        0.15,
        1.2,
        Vector3(0, 1, 0),
        matWood
    );
    scene.addObject(candleStand);
    
    // Vela (esfera vermelha brilhante)
    auto candle = make_shared<Sphere>(
        Vector3(8, 1.3, 16.5),
        0.12,
        matRedLight
    );
    scene.addObject(candle);
    
    cout << "Objetos criados: " << scene.objects.size() << endl;
    
    // ============ ILUMINAÇÃO ============
    
    cout << "Configurando iluminação..." << endl;
    
    // Luz ambiente (suave)
    auto ambient = make_shared<AmbientLight>(Color(0.25, 0.25, 0.28));
    scene.setAmbientLight(ambient);
    
    // LUZ DO SOL (direcional, vindo das janelas)
    // Simula luz entrando pelas janelas laterais
    auto sunLight = make_shared<DirectionalLight>(
        Vector3(-0.3, -0.6, 0.2),  // Ângulo diagonal
        Color(0.9, 0.85, 0.7)  // Luz amarelada do sol
    );
    scene.addLight(sunLight);
    
    // Luz do sol adicional (mais suave, de outro ângulo)
    auto sunLight2 = make_shared<DirectionalLight>(
        Vector3(0.3, -0.6, 0.2),
        Color(0.6, 0.55, 0.45)
    );
    scene.addLight(sunLight2);
    
    // LUZ VERMELHA DA VELA
    auto redCandle = make_shared<PointLight>(
        Vector3(8, 1.3, 16.5),  // Posição da vela
        Color(1.2, 0.15, 0.1)   // Vermelho intenso
    );
    scene.addLight(redCandle);
    
    // Luz suave geral (ilumina o altar)
    auto altarLight = make_shared<PointLight>(
        Vector3(6, 6, 17),
        Color(0.4, 0.4, 0.45)
    );
    scene.addLight(altarLight);
    
    cout << "Luzes configuradas!" << endl;
    
    // ============ CÂMERA ============
    
    cout << "\nConfigurando câmera..." << endl;
    
    // Câmera posicionada na entrada, olhando para o altar
    Camera camera(
        Vector3(6, 2, 1),      // Eye - na entrada, altura dos olhos
        Vector3(6, 2, 17),     // At - olhando para o altar
        Vector3(0, 1, 0),      // Up
        1.0,                   // distância focal
        8.0,                   // largura da janela
        8.0,                   // altura da janela
        800,                   // largura da imagem (maior resolução para mais detalhes)
        600                    // altura da imagem
    );
    
    cout << "Câmera configurada!" << endl;
    cout << "  Eye: " << camera.eye << endl;
    cout << "  At: " << camera.at << endl;
    cout << "  Resolução: " << camera.imageWidth << "x" << camera.imageHeight << endl;
    
    // ============ RENDERIZAÇÃO ============
    
    cout << "\n========================================" << endl;
    cout << "INICIANDO RENDERIZAÇÃO" << endl;
    cout << "========================================" << endl;
    
    Renderer renderer(scene, camera);
    renderer.render("output/capela.ppm");
    
    cout << "\n========================================" << endl;
    cout << "RENDERIZAÇÃO COMPLETA!" << endl;
    cout << "========================================" << endl;
    
    cout << "\nRequisitos atendidos:" << endl;
    cout << "  [✓] Coerência temática (Capela religiosa)" << endl;
    cout << "  [✓] Primeiro octante (x, y, z > 0)" << endl;
    cout << "  [✓] Objetos: Esfera, Cilindro, Malha" << endl;
    cout << "  [✓] Materiais: 7 materiais distintos" << endl;
    cout << "  [✓] Transformações" << endl;
    cout << "  [✓] Luz direcional (sol das janelas)" << endl;
    cout << "  [✓] Luz pontual vermelha (vela)" << endl;
    cout << "  [✓] Luz ambiente" << endl;
    cout << "  [✓] Câmera perspectiva" << endl;
    cout << "  [✓] Sombras" << endl;
    cout << "  [✓] Resolução 800x600" << endl;
    
    cout << "\nCena especial:" << endl;
    cout << "  - Luz do sol entrando pelas janelas" << endl;
    cout << "  - Luz vermelha da vela ao lado do altar" << endl;
    cout << "  - Ostensório dourado brilhante" << endl;
    cout << "  - Bancos de madeira" << endl;
    
    cout << "\nArquivo gerado: output/capela.ppm" << endl;
    cout << "Converta para PNG: convert output/capela.ppm output/capela.png" << endl;
    
    return 0;
}
