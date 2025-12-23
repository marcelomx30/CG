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

// ===== TEXTURAS PROCEDURAIS =====

Color woodTexture(const Vector3& point) {
    // Textura de madeira com contraste MÁXIMO
    double frequency = 1.0;  // Listras BEM GROSSAS
    double grain = sin(point.y * frequency) * 0.5 + 0.5;
    
    // CONTRASTE MÁXIMO: OU LARANJA BRILHANTE OU MARROM ESCURO
    if (grain > 0.5) {
        return Color(1.0, 0.8, 0.3);  // LARANJA MUITO BRILHANTE
    } else {
        return Color(0.3, 0.15, 0.05);  // MARROM BEM ESCURO
    }
}

Color stainedGlassTexture(const Vector3& point) {
    // Vitral com cores PURAS e MÁXIMAS
    double u = (point.x - 5.4) / 1.2;
    double v = (point.y - 3.0) / 2.8;
    
    double cx = 0.5, cy = 0.5;
    double dx = u - cx;
    double dy = v - cy;
    double dist = sqrt(dx*dx + dy*dy);
    
    // CRUZ DOURADA SUPER GROSSA
    double crossWidth = 0.15;
    if (fabs(dx) < crossWidth || fabs(dy) < crossWidth) {
        return Color(1.0, 1.0, 0.0);  // AMARELO PURO MÁXIMO
    }
    
    // CÍRCULO CENTRAL BRANCO
    if (dist < 0.15) {
        return Color(1.0, 1.0, 1.0);  // BRANCO MÁXIMO
    }
    
    // ANÉIS COLORIDOS
    if (dist < 0.25) {
        return Color(1.0, 0.0, 0.0);  // VERMELHO MÁXIMO
    }
    if (dist < 0.35) {
        return Color(0.0, 0.5, 1.0);  // AZUL MÁXIMO
    }
    
    // QUADRANTES COM CORES PURAS
    if (dx > 0 && dy > 0) {
        return Color(0.0, 1.0, 0.0);  // VERDE MÁXIMO
    } else if (dx < 0 && dy > 0) {
        return Color(1.0, 0.8, 0.0);  // AMARELO/OURO
    } else if (dx < 0 && dy < 0) {
        return Color(1.0, 0.0, 1.0);  // MAGENTA MÁXIMO
    } else {
        return Color(1.0, 0.5, 0.0);  // LARANJA MÁXIMO
    }
}

int main() {
    cout << "========================================" << endl;
    cout << "   CAPELA COM TEXTURAS - VERSAO FINAL" << endl;
    cout << "========================================" << endl;
    
    Scene scene;
    scene.backgroundColor = Color(0.3, 0.35, 0.4);
    
    Material matAltar(Color(0.6,0.6,0.6), Color(0.9,0.9,0.9), Color(0.5,0.5,0.5), 30.0);
    Material matGold(Color(0.3,0.25,0.1), Color(0.9,0.75,0.3), Color(1.0,0.95,0.7), 100.0);
    Material matWall(Color(0.35,0.33,0.30), Color(0.7,0.68,0.65), Color(0.2,0.2,0.2), 10.0);
    Material matFloor(Color(0.3,0.25,0.18), Color(0.6,0.5,0.4), Color(0.3,0.25,0.2), 20.0);
    Material matFrame(Color(0.2,0.2,0.2), Color(0.4,0.4,0.4), Color(0.3,0.3,0.3), 20.0);
    Material matCandle(Color(0.4,0.1,0.1), Color(0.8,0.2,0.15), Color(1.0,0.4,0.3), 60.0);
    Material matSkin(Color(0.6,0.45,0.35), Color(0.85,0.7,0.6), Color(0.5,0.4,0.3), 20.0);
    Material matCandleBase(Color(0.15,0.1,0.05), Color(0.4,0.25,0.15), Color(0.3,0.2,0.1), 35.0);
    
    // MATERIAIS COM ka MUITO ALTO (para ver texturas com luz ambiente)
    Material matWood(Color(0.9,0.7,0.5), Color(0.9,0.7,0.5), Color(0.3,0.3,0.3), 20.0, woodTexture);
    Material matVitral(Color(1.0,1.0,1.0), Color(1.0,1.0,1.0), Color(0.5,0.5,0.5), 50.0, stainedGlassTexture);
    
    cout << "Criando capela..." << endl;
    
    scene.addObject(make_shared<Plane>(Vector3(6,0,10), Vector3(0,1,0), matFloor));
    scene.addObject(make_shared<Plane>(Vector3(6,0,20), Vector3(0,0,-1), matWall));
    scene.addObject(make_shared<Plane>(Vector3(0,0,10), Vector3(1,0,0), matWall));
    scene.addObject(make_shared<Plane>(Vector3(12,0,10), Vector3(-1,0,0), matWall));
    scene.addObject(make_shared<Plane>(Vector3(6,8,10), Vector3(0,-1,0), matWall));
    scene.addObject(make_shared<Plane>(Vector3(6,0,0), Vector3(0,0,1), matWall));
    
    auto altarBase = make_shared<Mesh>(matWood);
    double aW=1.5, aH=0.8, aD=0.5;
    Vector3 aC(6,0,18);
    Vector3 ab1(aC.x-aW,aC.y,aC.z-aD), ab2(aC.x+aW,aC.y,aC.z-aD);
    Vector3 ab3(aC.x+aW,aC.y,aC.z+aD), ab4(aC.x-aW,aC.y,aC.z+aD);
    Vector3 ab5(aC.x-aW,aC.y+aH,aC.z-aD), ab6(aC.x+aW,aC.y+aH,aC.z-aD);
    Vector3 ab7(aC.x+aW,aC.y+aH,aC.z+aD), ab8(aC.x-aW,aC.y+aH,aC.z+aD);
    altarBase->addTriangle(Triangle(ab1,ab2,ab6,matWood)); altarBase->addTriangle(Triangle(ab1,ab6,ab5,matWood));
    altarBase->addTriangle(Triangle(ab4,ab3,ab7,matWood)); altarBase->addTriangle(Triangle(ab4,ab7,ab8,matWood));
    altarBase->addTriangle(Triangle(ab1,ab4,ab8,matWood)); altarBase->addTriangle(Triangle(ab1,ab8,ab5,matWood));
    altarBase->addTriangle(Triangle(ab2,ab3,ab7,matWood)); altarBase->addTriangle(Triangle(ab2,ab7,ab6,matWood));
    altarBase->addTriangle(Triangle(ab5,ab6,ab7,matWood)); altarBase->addTriangle(Triangle(ab5,ab7,ab8,matWood));
    scene.addObject(altarBase);
    
    auto cloth = make_shared<Mesh>(matAltar);
    double cW=1.8, cD=0.7;
    Vector3 cC(6,aH+0.01,18);
    Vector3 c1(cC.x-cW,cC.y,cC.z-cD), c2(cC.x+cW,cC.y,cC.z-cD);
    Vector3 c3(cC.x+cW,cC.y,cC.z+cD), c4(cC.x-cW,cC.y,cC.z+cD);
    cloth->addTriangle(Triangle(c1,c2,c3,matAltar));
    cloth->addTriangle(Triangle(c1,c3,c4,matAltar));
    scene.addObject(cloth);
    
    cout << "Criando ostensorio..." << endl;
    Vector3 ostCenter(6, aH + 0.6, 18);
    
    scene.addObject(make_shared<Cone>(Vector3(6, aH, 18), 0.2, 0.3, Vector3(0, 1, 0), matGold));
    
    for(int i=1; i<=12; i++) {
        scene.addObject(make_shared<Sphere>(Vector3(6, aH + 0.3 + i*0.025, 18), 0.025, matGold));
    }
    
    scene.addObject(make_shared<Sphere>(ostCenter, 0.14, matSkin));
    
    for(int i=0; i<24; i++) {
        double angle = i * 2*M_PI/24;
        scene.addObject(make_shared<Sphere>(
            Vector3(ostCenter.x + 0.16*cos(angle), ostCenter.y + 0.16*sin(angle), ostCenter.z),
            0.012, matGold
        ));
    }
    
    for(int i=0; i<7; i++) {
        double angle = i * 2*M_PI/7;
        for(int j=0; j<=6; j++) {
            double r = 0.18 + j*0.03;
            double size = 0.032 - j*0.003;
            scene.addObject(make_shared<Sphere>(
                Vector3(ostCenter.x + r*cos(angle), ostCenter.y + r*sin(angle), ostCenter.z),
                size, matGold
            ));
        }
    }
    
    for(int i=0; i<7; i++) {
        double angle = i * 2*M_PI/7;
        scene.addObject(make_shared<Sphere>(
            Vector3(ostCenter.x + 0.36*cos(angle), ostCenter.y + 0.36*sin(angle), ostCenter.z),
            0.038, matGold
        ));
    }
    
    cout << "Criando bancos..." << endl;
    
    for(int fila=0; fila<8; fila++) {
        double zPos = 3 + fila*2.2;
        
        for(int banco=0; banco<3; banco++) {
            double xPos = 1.8 + banco*0.5;
            auto b = make_shared<Mesh>(matWood);
            double bW=1.0, bH=0.45, bD=0.25;
            Vector3 bC(xPos,0,zPos);
            Vector3 v1(bC.x-bW,bC.y,bC.z-bD), v2(bC.x+bW,bC.y,bC.z-bD);
            Vector3 v3(bC.x+bW,bC.y,bC.z+bD), v4(bC.x-bW,bC.y,bC.z+bD);
            Vector3 v5(bC.x-bW,bC.y+bH,bC.z-bD), v6(bC.x+bW,bC.y+bH,bC.z-bD);
            Vector3 v7(bC.x+bW,bC.y+bH,bC.z+bD), v8(bC.x-bW,bC.y+bH,bC.z+bD);
            b->addTriangle(Triangle(v1,v2,v6,matWood)); b->addTriangle(Triangle(v1,v6,v5,matWood));
            b->addTriangle(Triangle(v4,v3,v7,matWood)); b->addTriangle(Triangle(v4,v7,v8,matWood));
            b->addTriangle(Triangle(v1,v4,v8,matWood)); b->addTriangle(Triangle(v1,v8,v5,matWood));
            b->addTriangle(Triangle(v2,v3,v7,matWood)); b->addTriangle(Triangle(v2,v7,v6,matWood));
            b->addTriangle(Triangle(v5,v6,v7,matWood)); b->addTriangle(Triangle(v5,v7,v8,matWood));
            scene.addObject(b);
        }
        
        for(int banco=0; banco<3; banco++) {
            double xPos = 9.2 + banco*0.5;
            auto b = make_shared<Mesh>(matWood);
            double bW=1.0, bH=0.45, bD=0.25;
            Vector3 bC(xPos,0,zPos);
            Vector3 v1(bC.x-bW,bC.y,bC.z-bD), v2(bC.x+bW,bC.y,bC.z-bD);
            Vector3 v3(bC.x+bW,bC.y,bC.z+bD), v4(bC.x-bW,bC.y,bC.z+bD);
            Vector3 v5(bC.x-bW,bC.y+bH,bC.z-bD), v6(bC.x+bW,bC.y+bH,bC.z-bD);
            Vector3 v7(bC.x+bW,bC.y+bH,bC.z+bD), v8(bC.x-bW,bC.y+bH,bC.z+bD);
            b->addTriangle(Triangle(v1,v2,v6,matWood)); b->addTriangle(Triangle(v1,v6,v5,matWood));
            b->addTriangle(Triangle(v4,v3,v7,matWood)); b->addTriangle(Triangle(v4,v7,v8,matWood));
            b->addTriangle(Triangle(v1,v4,v8,matWood)); b->addTriangle(Triangle(v1,v8,v5,matWood));
            b->addTriangle(Triangle(v2,v3,v7,matWood)); b->addTriangle(Triangle(v2,v7,v6,matWood));
            b->addTriangle(Triangle(v5,v6,v7,matWood)); b->addTriangle(Triangle(v5,v7,v8,matWood));
            scene.addObject(b);
        }
    }
    
    // JANELA - SEM MOLDURA (moldura estava bloqueando!)
    cout << "Criando janela..." << endl;
    // Moldura REMOVIDA para não bloquear o vitral!
    
    cout << "Criando vitral com textura..." << endl;
    auto vitral = make_shared<Mesh>(matVitral);
    Vector3 vb1(5.4, 3.0, 19.5), vb2(6.6, 3.0, 19.5);  // z=19.5 (mais visível!)
    Vector3 vb3(6.6, 5.0, 19.5), vb4(5.4, 5.0, 19.5);
    Vector3 vtop(6.0, 5.8, 19.5);
    vitral->addTriangle(Triangle(vb1, vb2, vb3, matVitral));
    vitral->addTriangle(Triangle(vb1, vb3, vb4, matVitral));
    vitral->addTriangle(Triangle(vb4, vb3, vtop, matVitral));
    scene.addObject(vitral);
    
    // TESTE: QUADRADO GIGANTE VERMELHO para verificar se texturas funcionam
    auto teste = make_shared<Mesh>(matVitral);
    Vector3 t1(4, 6, 19.4), t2(5, 6, 19.4);
    Vector3 t3(5, 7, 19.4), t4(4, 7, 19.4);
    teste->addTriangle(Triangle(t1, t2, t3, matVitral));
    teste->addTriangle(Triangle(t1, t3, t4, matVitral));
    scene.addObject(teste);
    
    cout << "Criando vela..." << endl;
    scene.addObject(make_shared<Cylinder>(Vector3(8,0,17.5), 0.15, 0.15, Vector3(0,1,0), matCandleBase));
    scene.addObject(make_shared<Cylinder>(Vector3(8,0.15,17.5), 0.12, 0.15, Vector3(0,1,0), matCandleBase));
    scene.addObject(make_shared<Cylinder>(Vector3(8,0.30,17.5), 0.09, 0.15, Vector3(0,1,0), matCandleBase));
    scene.addObject(make_shared<Cylinder>(Vector3(8,0.45,17.5), 0.05, 0.6, Vector3(0,1,0), matCandleBase));
    scene.addObject(make_shared<Cylinder>(Vector3(8,1.05,17.5), 0.08, 0.05, Vector3(0,1,0), matCandleBase));
    scene.addObject(make_shared<Cylinder>(Vector3(8,1.1,17.5), 0.12, 0.3, Vector3(0,1,0), matCandle));
    scene.addObject(make_shared<Sphere>(Vector3(8,1.25,17.5), 0.08, matCandle));
    scene.addObject(make_shared<Sphere>(Vector3(8,1.4,17.5), 0.12, matCandle));
    
    cout << "Objetos: " << scene.objects.size() << endl;
    
    scene.setAmbientLight(make_shared<AmbientLight>(Color(0.7,0.7,0.7)));  // LUZ AMBIENTE MAXIMA!
    scene.addLight(make_shared<DirectionalLight>(Vector3(0,-0.6,0.4), Color(0.3,0.3,0.3)));  // Reduzida
    scene.addLight(make_shared<PointLight>(Vector3(6,5,17), Color(0.3,0.3,0.3)));
    scene.addLight(make_shared<PointLight>(Vector3(8,1.25,17.5), Color(0.9,0.2,0.15)));
    scene.addLight(make_shared<PointLight>(Vector3(6,6,10), Color(0.2,0.2,0.2)));
    
    // Luzes suaves nos bancos
    scene.addLight(make_shared<PointLight>(Vector3(3,2,8), Color(0.3,0.3,0.3)));
    scene.addLight(make_shared<PointLight>(Vector3(9,2,8), Color(0.3,0.3,0.3)));
    
    // LUZ NO VITRAL (suave, sem spotlight)
    scene.addLight(make_shared<PointLight>(Vector3(6, 4, 19), Color(0.4,0.4,0.4)));
    
    cout << "Luzes: 8 (extra para iluminar texturas)" << endl;
    
    Camera camera(Vector3(6,1.8,12), Vector3(6,1.5,18), Vector3(0,1,0), 1.0, 6.0, 4.5, 800, 600);
    cout << "Camera configurada" << endl;
    
    cout << "\n========================================" << endl;
    cout << "RENDERIZANDO..." << endl;
    cout << "Texturas: Madeira + Vitral" << endl;
    cout << "Cone + Sombras + Spotlight" << endl;
    cout << "========================================" << endl;
    
    Renderer renderer(scene, camera);
    renderer.render("output/capela.ppm");
    
    cout << "\nCOMPLETO!" << endl;
    cout << "Arquivo: output/capela.ppm" << endl;
    cout << "\nRECURSOS:" << endl;
    cout << "- Textura de madeira (listras)" << endl;
    cout << "- Textura de vitral (cruz + cores)" << endl;
    cout << "- Cone na base do ostensorio" << endl;
    cout << "- Sombras ativas" << endl;
    cout << "- Spotlight no vitral" << endl;
    
    return 0;
}
