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

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "    CAPELA - Seguindo Esboco" << endl;
    cout << "========================================" << endl;
    
    Scene scene;
    scene.backgroundColor = Color(0.3, 0.35, 0.4);
    
    // MATERIAIS
    Material matBench(Color(0.15,0.10,0.05), Color(0.4,0.25,0.15), Color(0.2,0.15,0.1), 15.0);
    Material matAltar(Color(0.6,0.6,0.6), Color(0.9,0.9,0.9), Color(0.5,0.5,0.5), 30.0);
    Material matGold(Color(0.3,0.25,0.1), Color(0.9,0.75,0.3), Color(1.0,0.95,0.7), 100.0);
    Material matWall(Color(0.35,0.33,0.30), Color(0.7,0.68,0.65), Color(0.2,0.2,0.2), 10.0);
    Material matFloor(Color(0.3,0.25,0.18), Color(0.6,0.5,0.4), Color(0.3,0.25,0.2), 20.0);
    Material matWindow(Color(0.5,0.5,0.4), Color(0.8,0.8,0.6), Color(0.9,0.9,0.8), 50.0);
    Material matFrame(Color(0.2,0.2,0.2), Color(0.4,0.4,0.4), Color(0.3,0.3,0.3), 20.0);
    Material matCandle(Color(0.4,0.1,0.1), Color(0.8,0.2,0.15), Color(1.0,0.4,0.3), 60.0);
    Material matSkin(Color(0.6,0.45,0.35), Color(0.85,0.7,0.6), Color(0.5,0.4,0.3), 20.0); // Cor de pele
    Material matCandleBase(Color(0.1,0.05,0.02), Color(0.3,0.15,0.08), Color(0.2,0.1,0.05), 30.0); // Base escura
    
    cout << "Criando capela..." << endl;
    
    // ESTRUTURA
    scene.addObject(make_shared<Plane>(Vector3(6,0,10), Vector3(0,1,0), matFloor));
    scene.addObject(make_shared<Plane>(Vector3(6,0,20), Vector3(0,0,-1), matWall));
    scene.addObject(make_shared<Plane>(Vector3(0,0,10), Vector3(1,0,0), matWall));
    scene.addObject(make_shared<Plane>(Vector3(12,0,10), Vector3(-1,0,0), matWall));
    scene.addObject(make_shared<Plane>(Vector3(6,8,10), Vector3(0,-1,0), matWall));
    scene.addObject(make_shared<Plane>(Vector3(6,0,0), Vector3(0,0,1), matWall));
    
    // ALTAR
    auto altarBase = make_shared<Mesh>(matWall);
    double aW=1.5, aH=0.8, aD=0.5;
    Vector3 aC(6,0,18);
    Vector3 ab1(aC.x-aW,aC.y,aC.z-aD), ab2(aC.x+aW,aC.y,aC.z-aD);
    Vector3 ab3(aC.x+aW,aC.y,aC.z+aD), ab4(aC.x-aW,aC.y,aC.z+aD);
    Vector3 ab5(aC.x-aW,aC.y+aH,aC.z-aD), ab6(aC.x+aW,aC.y+aH,aC.z-aD);
    Vector3 ab7(aC.x+aW,aC.y+aH,aC.z+aD), ab8(aC.x-aW,aC.y+aH,aC.z+aD);
    altarBase->addTriangle(Triangle(ab1,ab2,ab6,matWall)); altarBase->addTriangle(Triangle(ab1,ab6,ab5,matWall));
    altarBase->addTriangle(Triangle(ab4,ab3,ab7,matWall)); altarBase->addTriangle(Triangle(ab4,ab7,ab8,matWall));
    altarBase->addTriangle(Triangle(ab1,ab4,ab8,matWall)); altarBase->addTriangle(Triangle(ab1,ab8,ab5,matWall));
    altarBase->addTriangle(Triangle(ab2,ab3,ab7,matWall)); altarBase->addTriangle(Triangle(ab2,ab7,ab6,matWall));
    altarBase->addTriangle(Triangle(ab5,ab6,ab7,matWall)); altarBase->addTriangle(Triangle(ab5,ab7,ab8,matWall));
    scene.addObject(altarBase);
    
    // TOALHA
    auto cloth = make_shared<Mesh>(matAltar);
    double cW=1.8, cD=0.7;
    Vector3 cC(6,aH+0.01,18);
    Vector3 c1(cC.x-cW,cC.y,cC.z-cD), c2(cC.x+cW,cC.y,cC.z-cD);
    Vector3 c3(cC.x+cW,cC.y,cC.z+cD), c4(cC.x-cW,cC.y,cC.z+cD);
    cloth->addTriangle(Triangle(c1,c2,c3,matAltar));
    cloth->addTriangle(Triangle(c1,c3,c4,matAltar));
    scene.addObject(cloth);
    
    // OSTENSORIO SIMPLES E VISÍVEL
    cout << "Criando ostensorio..." << endl;
    
    // Posição: em cima do altar, centralizado
    Vector3 ostBase(6, aH + 0.01, 18);
    Vector3 ostCenter(6, aH + 0.5, 18);
    
    // BASE DO OSTENSÓRIO
    scene.addObject(make_shared<Sphere>(ostBase, 0.15, matGold));
    
    // HASTE (esferas empilhadas)
    for(int i=1; i<=10; i++) {
        scene.addObject(make_shared<Sphere>(
            Vector3(6, aH + i*0.05, 18), 0.03, matGold
        ));
    }
    
    // DISCO CENTRAL (HÓSTIA) - COR DE PELE
    scene.addObject(make_shared<Sphere>(ostCenter, 0.14, matSkin));
    
    // ANEL DOURADO bem próximo da hóstia (PLANO XY - VERTICAL!)
    for(int i=0; i<20; i++) {
        double angle = i * 2*M_PI/20;
        scene.addObject(make_shared<Sphere>(
            Vector3(ostCenter.x + 0.16*cos(angle), ostCenter.y + 0.16*sin(angle), ostCenter.z),
            0.01, matGold
        ));
    }
    
    // 7 RAIOS formando heptágono VERTICAL (plano XY)
    for(int i=0; i<7; i++) {
        double angle = i * 2*M_PI/7;
        
        // Raios começam após o anel e vão até 0.35
        for(int j=0; j<=4; j++) {
            double r = 0.18 + j*0.04;
            double size = 0.022 - j*0.003;
            scene.addObject(make_shared<Sphere>(
                Vector3(ostCenter.x + r*cos(angle), ostCenter.y + r*sin(angle), ostCenter.z),
                size, matGold
            ));
        }
    }
    
    // Esferas maiores nos vértices do heptágono VERTICAL
    for(int i=0; i<7; i++) {
        double angle = i * 2*M_PI/7;
        scene.addObject(make_shared<Sphere>(
            Vector3(ostCenter.x + 0.34*cos(angle), ostCenter.y + 0.34*sin(angle), ostCenter.z),
            0.025, matGold
        ));
    }
    
    // BANCOS INDIVIDUAIS - MAIS FILEIRAS
    cout << "Criando bancos..." << endl;
    for(int fila=0; fila<8; fila++) {  // 8 fileiras agora
        double zPos = 3 + fila*2.2;  // Começando mais perto
        // LADO ESQUERDO
        for(int banco=0; banco<3; banco++) {  // 3 bancos por lado
            double xPos = 1.8 + banco*0.5;
            auto b = make_shared<Mesh>(matBench);
            double bW=1.0, bH=0.45, bD=0.25;  // Mais fino (bD menor)
            Vector3 bC(xPos,0,zPos);
            Vector3 v1(bC.x-bW,bC.y,bC.z-bD), v2(bC.x+bW,bC.y,bC.z-bD);
            Vector3 v3(bC.x+bW,bC.y,bC.z+bD), v4(bC.x-bW,bC.y,bC.z+bD);
            Vector3 v5(bC.x-bW,bC.y+bH,bC.z-bD), v6(bC.x+bW,bC.y+bH,bC.z-bD);
            Vector3 v7(bC.x+bW,bC.y+bH,bC.z+bD), v8(bC.x-bW,bC.y+bH,bC.z+bD);
            b->addTriangle(Triangle(v1,v2,v6,matBench)); b->addTriangle(Triangle(v1,v6,v5,matBench));
            b->addTriangle(Triangle(v4,v3,v7,matBench)); b->addTriangle(Triangle(v4,v7,v8,matBench));
            b->addTriangle(Triangle(v1,v4,v8,matBench)); b->addTriangle(Triangle(v1,v8,v5,matBench));
            b->addTriangle(Triangle(v2,v3,v7,matBench)); b->addTriangle(Triangle(v2,v7,v6,matBench));
            b->addTriangle(Triangle(v5,v6,v7,matBench)); b->addTriangle(Triangle(v5,v7,v8,matBench));
            scene.addObject(b);
        }
        // LADO DIREITO
        for(int banco=0; banco<3; banco++) {
            double xPos = 9.2 + banco*0.5;
            auto b = make_shared<Mesh>(matBench);
            double bW=1.0, bH=0.45, bD=0.25;
            Vector3 bC(xPos,0,zPos);
            Vector3 v1(bC.x-bW,bC.y,bC.z-bD), v2(bC.x+bW,bC.y,bC.z-bD);
            Vector3 v3(bC.x+bW,bC.y,bC.z+bD), v4(bC.x-bW,bC.y,bC.z+bD);
            Vector3 v5(bC.x-bW,bC.y+bH,bC.z-bD), v6(bC.x+bW,bC.y+bH,bC.z-bD);
            Vector3 v7(bC.x+bW,bC.y+bH,bC.z+bD), v8(bC.x-bW,bC.y+bH,bC.z+bD);
            b->addTriangle(Triangle(v1,v2,v6,matBench)); b->addTriangle(Triangle(v1,v6,v5,matBench));
            b->addTriangle(Triangle(v4,v3,v7,matBench)); b->addTriangle(Triangle(v4,v7,v8,matBench));
            b->addTriangle(Triangle(v1,v4,v8,matBench)); b->addTriangle(Triangle(v1,v8,v5,matBench));
            b->addTriangle(Triangle(v2,v3,v7,matBench)); b->addTriangle(Triangle(v2,v7,v6,matBench));
            b->addTriangle(Triangle(v5,v6,v7,matBench)); b->addTriangle(Triangle(v5,v7,v8,matBench));
            scene.addObject(b);
        }
    }
    
    // JANELA EM ARCO GOTICO (não esfera!)
    cout << "Criando janela..." << endl;
    
    // Moldura esquerda
    scene.addObject(make_shared<Cylinder>(
        Vector3(5.3,3,19.8), 0.08, 2.5,
        Vector3(0,1,0), matFrame
    ));
    
    // Moldura direita
    scene.addObject(make_shared<Cylinder>(
        Vector3(6.7,3,19.8), 0.08, 2.5,
        Vector3(0,1,0), matFrame
    ));
    
    // Base da janela
    scene.addObject(make_shared<Cylinder>(
        Vector3(6,2.8,19.8), 0.08, 0.7,
        Vector3(1,0,0), matFrame
    ));
    
    // Arco gótico (dois cilindros inclinados formando ponta)
    scene.addObject(make_shared<Cylinder>(
        Vector3(5.5,5.2,19.8), 0.08, 1.0,
        Vector3(0.5,0.866,0), matFrame  // 60 graus
    ));
    scene.addObject(make_shared<Cylinder>(
        Vector3(6.5,5.2,19.8), 0.08, 1.0,
        Vector3(-0.5,0.866,0), matFrame  // -60 graus
    ));
    
    // Vitral (planos coloridos dentro da janela)
    auto vitral = make_shared<Mesh>(matWindow);
    Vector3 vb1(5.4, 3.0, 19.75), vb2(6.6, 3.0, 19.75);
    Vector3 vb3(6.6, 5.0, 19.75), vb4(5.4, 5.0, 19.75);
    Vector3 vtop(6.0, 5.8, 19.75);
    
    vitral->addTriangle(Triangle(vb1, vb2, vb3, matWindow));
    vitral->addTriangle(Triangle(vb1, vb3, vb4, matWindow));
    vitral->addTriangle(Triangle(vb4, vb3, vtop, matWindow));
    scene.addObject(vitral);
    
    // VELA VERMELHA DETALHADA
    cout << "Criando vela..." << endl;
    
    // Base tripla da vela (3 níveis)
    scene.addObject(make_shared<Cylinder>(Vector3(8,0,17.5), 0.15, 0.15, Vector3(0,1,0), matCandleBase));
    scene.addObject(make_shared<Cylinder>(Vector3(8,0.15,17.5), 0.12, 0.15, Vector3(0,1,0), matCandleBase));
    scene.addObject(make_shared<Cylinder>(Vector3(8,0.30,17.5), 0.09, 0.15, Vector3(0,1,0), matCandleBase));
    
    // Haste central
    scene.addObject(make_shared<Cylinder>(Vector3(8,0.45,17.5), 0.05, 0.6, Vector3(0,1,0), matCandleBase));
    
    // Suporte do vidro
    scene.addObject(make_shared<Cylinder>(Vector3(8,1.05,17.5), 0.08, 0.05, Vector3(0,1,0), matCandleBase));
    
    // Vidro protetor (cilindro transparente vermelho)
    scene.addObject(make_shared<Cylinder>(Vector3(8,1.1,17.5), 0.12, 0.3, Vector3(0,1,0), matCandle));
    
    // Chama vermelha (esfera brilhante)
    scene.addObject(make_shared<Sphere>(Vector3(8,1.25,17.5), 0.08, matCandle));
    
    // Topo do vidro
    scene.addObject(make_shared<Sphere>(Vector3(8,1.4,17.5), 0.12, matCandle));
    
    cout << "Objetos: " << scene.objects.size() << endl;
    
    // ILUMINACAO
    scene.setAmbientLight(make_shared<AmbientLight>(Color(0.15,0.15,0.18)));
    scene.addLight(make_shared<DirectionalLight>(Vector3(0,-0.6,0.4), Color(0.7,0.65,0.5)));
    scene.addLight(make_shared<PointLight>(Vector3(6,5,17), Color(0.5,0.5,0.55)));
    scene.addLight(make_shared<PointLight>(Vector3(8,1.25,17.5), Color(0.8,0.15,0.1))); // Luz da vela
    scene.addLight(make_shared<PointLight>(Vector3(6,6,10), Color(0.3,0.3,0.35)));
    
    cout << "Luzes: 5" << endl;
    
    // CAMERA
    Camera camera(Vector3(6,1.8,12), Vector3(6,1.5,18), Vector3(0,1,0), 1.0, 6.0, 4.5, 800, 600);
    cout << "Camera proxima do altar" << endl;
    
    // RENDERIZAR
    cout << "\n========================================" << endl;
    cout << "RENDERIZANDO..." << endl;
    cout << "========================================" << endl;
    
    Renderer renderer(scene, camera);
    renderer.render("output/capela.ppm");
    
    cout << "\nCOMPLETO!" << endl;
    cout << "Arquivo: output/capela.ppm" << endl;
    cout << "Converter: magick output/capela.ppm output/capela.png" << endl;
    
    return 0;
}
