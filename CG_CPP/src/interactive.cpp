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
#include <string>
#include <limits>

using namespace std;

// Estrutura para guardar parâmetros da cena
struct SceneParameters {
    // Câmera
    Vector3 cameraEye;
    Vector3 cameraAt;
    Vector3 cameraUp;
    
    // Luzes
    Vector3 pointLight1Pos;
    Color pointLight1Intensity;
    Vector3 pointLight2Pos;
    Color pointLight2Intensity;
    Vector3 spotLightPos;
    Vector3 spotLightDir;
    Color spotLightIntensity;
    
    // Objetos (posições)
    Vector3 sphere1Pos;
    Vector3 sphere2Pos;
    Vector3 sphere3Pos;
    Vector3 cylinderPos;
    Vector3 conePos;
    
    // Resolução
    int width;
    int height;
    
    // Construtor com valores padrão
    SceneParameters() {
        // Câmera padrão
        cameraEye = Vector3(12, 4, -2);
        cameraAt = Vector3(5, 2, 5);
        cameraUp = Vector3(0, 1, 0);
        
        // Luzes padrão
        pointLight1Pos = Vector3(5, 6, 3);
        pointLight1Intensity = Color(0.8, 0.8, 0.8);
        pointLight2Pos = Vector3(2, 5, 2);
        pointLight2Intensity = Color(0.5, 0.5, 0.6);
        spotLightPos = Vector3(2, 7, 2);
        spotLightDir = Vector3(0, -1, 0.3);
        spotLightIntensity = Color(0.6, 0.5, 0.4);
        
        // Objetos padrão
        sphere1Pos = Vector3(3, 2.5, 5);
        sphere2Pos = Vector3(2, 0.5, 7);
        sphere3Pos = Vector3(8, 1.2, 2);
        cylinderPos = Vector3(6.5, 1.0, 3);
        conePos = Vector3(7, 0.75, 7);
        
        // Resolução
        width = 500;
        height = 500;
    }
};

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    cout << "\nPressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void showMenu() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "   INTERFACE DE PARAMETRIZACAO" << endl;
    cout << "   Trabalho Final de CG" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "MENU PRINCIPAL:" << endl;
    cout << "1. Configurar Camera" << endl;
    cout << "2. Configurar Luzes" << endl;
    cout << "3. Configurar Objetos" << endl;
    cout << "4. Configurar Resolucao" << endl;
    cout << "5. Ver Configuracoes Atuais" << endl;
    cout << "6. Renderizar Cena" << endl;
    cout << "7. Presets Rapidos" << endl;
    cout << "0. Sair" << endl;
    cout << endl;
    cout << "Escolha uma opcao: ";
}

void configureCamera(SceneParameters& params) {
    clearScreen();
    cout << "=== CONFIGURACAO DE CAMERA ===" << endl;
    cout << endl;
    cout << "Camera atual:" << endl;
    cout << "  Eye (posicao): " << params.cameraEye << endl;
    cout << "  At (visada): " << params.cameraAt << endl;
    cout << "  Up: " << params.cameraUp << endl;
    cout << endl;
    
    int choice;
    cout << "1. Modificar Eye (posicao da camera)" << endl;
    cout << "2. Modificar At (ponto de visada)" << endl;
    cout << "3. Voltar" << endl;
    cout << "Escolha: ";
    cin >> choice;
    
    if (choice == 1) {
        cout << "\nNova posicao Eye:" << endl;
        cout << "  x: "; cin >> params.cameraEye.x;
        cout << "  y: "; cin >> params.cameraEye.y;
        cout << "  z: "; cin >> params.cameraEye.z;
        cout << "\nPosicao da camera atualizada!" << endl;
        waitForEnter();
    } else if (choice == 2) {
        cout << "\nNovo ponto At:" << endl;
        cout << "  x: "; cin >> params.cameraAt.x;
        cout << "  y: "; cin >> params.cameraAt.y;
        cout << "  z: "; cin >> params.cameraAt.z;
        cout << "\nPonto de visada atualizado!" << endl;
        waitForEnter();
    }
}

void configureLights(SceneParameters& params) {
    clearScreen();
    cout << "=== CONFIGURACAO DE LUZES ===" << endl;
    cout << endl;
    cout << "Luzes atuais:" << endl;
    cout << "1. Luz Pontual 1: " << params.pointLight1Pos << endl;
    cout << "2. Luz Pontual 2: " << params.pointLight2Pos << endl;
    cout << "3. Luz Spot: " << params.spotLightPos << endl;
    cout << "4. Voltar" << endl;
    cout << endl;
    cout << "Escolha uma luz para modificar: ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        cout << "\nNova posicao da Luz Pontual 1:" << endl;
        cout << "  x: "; cin >> params.pointLight1Pos.x;
        cout << "  y: "; cin >> params.pointLight1Pos.y;
        cout << "  z: "; cin >> params.pointLight1Pos.z;
        cout << "\nIntensidade (R G B, valores 0-1):" << endl;
        cout << "  R: "; cin >> params.pointLight1Intensity.r;
        cout << "  G: "; cin >> params.pointLight1Intensity.g;
        cout << "  B: "; cin >> params.pointLight1Intensity.b;
        cout << "\nLuz atualizada!" << endl;
        waitForEnter();
    } else if (choice == 2) {
        cout << "\nNova posicao da Luz Pontual 2:" << endl;
        cout << "  x: "; cin >> params.pointLight2Pos.x;
        cout << "  y: "; cin >> params.pointLight2Pos.y;
        cout << "  z: "; cin >> params.pointLight2Pos.z;
        cout << "\nIntensidade (R G B, valores 0-1):" << endl;
        cout << "  R: "; cin >> params.pointLight2Intensity.r;
        cout << "  G: "; cin >> params.pointLight2Intensity.g;
        cout << "  B: "; cin >> params.pointLight2Intensity.b;
        cout << "\nLuz atualizada!" << endl;
        waitForEnter();
    } else if (choice == 3) {
        cout << "\nNova posicao da Luz Spot:" << endl;
        cout << "  x: "; cin >> params.spotLightPos.x;
        cout << "  y: "; cin >> params.spotLightPos.y;
        cout << "  z: "; cin >> params.spotLightPos.z;
        cout << "\nNova direcao da Luz Spot:" << endl;
        cout << "  x: "; cin >> params.spotLightDir.x;
        cout << "  y: "; cin >> params.spotLightDir.y;
        cout << "  z: "; cin >> params.spotLightDir.z;
        cout << "\nLuz atualizada!" << endl;
        waitForEnter();
    }
}

void configureObjects(SceneParameters& params) {
    clearScreen();
    cout << "=== CONFIGURACAO DE OBJETOS ===" << endl;
    cout << endl;
    cout << "Objetos atuais:" << endl;
    cout << "1. Esfera Vermelha Principal: " << params.sphere1Pos << endl;
    cout << "2. Esfera Pequena: " << params.sphere2Pos << endl;
    cout << "3. Esfera Azul: " << params.sphere3Pos << endl;
    cout << "4. Cilindro: " << params.cylinderPos << endl;
    cout << "5. Cone: " << params.conePos << endl;
    cout << "6. Voltar" << endl;
    cout << endl;
    cout << "Escolha um objeto para modificar: ";
    
    int choice;
    cin >> choice;
    
    Vector3* targetPos = nullptr;
    string objName;
    
    switch(choice) {
        case 1: targetPos = &params.sphere1Pos; objName = "Esfera Vermelha"; break;
        case 2: targetPos = &params.sphere2Pos; objName = "Esfera Pequena"; break;
        case 3: targetPos = &params.sphere3Pos; objName = "Esfera Azul"; break;
        case 4: targetPos = &params.cylinderPos; objName = "Cilindro"; break;
        case 5: targetPos = &params.conePos; objName = "Cone"; break;
        default: return;
    }
    
    cout << "\nNova posicao do(a) " << objName << ":" << endl;
    cout << "  x: "; cin >> targetPos->x;
    cout << "  y: "; cin >> targetPos->y;
    cout << "  z: "; cin >> targetPos->z;
    cout << "\nObjeto atualizado!" << endl;
    waitForEnter();
}

void configureResolution(SceneParameters& params) {
    clearScreen();
    cout << "=== CONFIGURACAO DE RESOLUCAO ===" << endl;
    cout << endl;
    cout << "Resolucao atual: " << params.width << "x" << params.height << endl;
    cout << endl;
    cout << "Presets:" << endl;
    cout << "1. Teste rapido (200x200)" << endl;
    cout << "2. Media qualidade (400x400)" << endl;
    cout << "3. Alta qualidade (500x500) - PADRAO" << endl;
    cout << "4. Extra (800x800)" << endl;
    cout << "5. Personalizado" << endl;
    cout << "6. Voltar" << endl;
    cout << endl;
    cout << "Escolha: ";
    
    int choice;
    cin >> choice;
    
    switch(choice) {
        case 1: params.width = params.height = 200; break;
        case 2: params.width = params.height = 400; break;
        case 3: params.width = params.height = 500; break;
        case 4: params.width = params.height = 800; break;
        case 5:
            cout << "\nLargura: "; cin >> params.width;
            cout << "Altura: "; cin >> params.height;
            break;
        default: return;
    }
    
    if (choice >= 1 && choice <= 5) {
        cout << "\nResolucao atualizada para " << params.width << "x" << params.height << endl;
        waitForEnter();
    }
}

void showCurrentConfig(const SceneParameters& params) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "   CONFIGURACOES ATUAIS" << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    cout << "CAMERA:" << endl;
    cout << "  Eye: " << params.cameraEye << endl;
    cout << "  At: " << params.cameraAt << endl;
    cout << "  Up: " << params.cameraUp << endl;
    cout << endl;
    
    cout << "LUZES:" << endl;
    cout << "  Luz Pontual 1:" << endl;
    cout << "    Posicao: " << params.pointLight1Pos << endl;
    cout << "    Intensidade: RGB(" << params.pointLight1Intensity.r << ", " 
         << params.pointLight1Intensity.g << ", " << params.pointLight1Intensity.b << ")" << endl;
    cout << "  Luz Pontual 2:" << endl;
    cout << "    Posicao: " << params.pointLight2Pos << endl;
    cout << "  Luz Spot:" << endl;
    cout << "    Posicao: " << params.spotLightPos << endl;
    cout << "    Direcao: " << params.spotLightDir << endl;
    cout << endl;
    
    cout << "OBJETOS:" << endl;
    cout << "  Esfera Principal: " << params.sphere1Pos << endl;
    cout << "  Esfera Pequena: " << params.sphere2Pos << endl;
    cout << "  Esfera Azul: " << params.sphere3Pos << endl;
    cout << "  Cilindro: " << params.cylinderPos << endl;
    cout << "  Cone: " << params.conePos << endl;
    cout << endl;
    
    cout << "RESOLUCAO: " << params.width << "x" << params.height << endl;
    
    waitForEnter();
}

void applyPresets(SceneParameters& params) {
    clearScreen();
    cout << "=== PRESETS RAPIDOS ===" << endl;
    cout << endl;
    cout << "1. Visao Frontal (1 ponto de fuga)" << endl;
    cout << "2. Visao de Canto (2 pontos de fuga)" << endl;
    cout << "3. Visao Aerea (3 pontos de fuga)" << endl;
    cout << "4. Iluminacao Dramatica" << endl;
    cout << "5. Iluminacao Suave" << endl;
    cout << "6. Objetos Centralizados" << endl;
    cout << "7. Voltar" << endl;
    cout << endl;
    cout << "Escolha um preset: ";
    
    int choice;
    cin >> choice;
    
    switch(choice) {
        case 1: // Frontal
            params.cameraEye = Vector3(5, 4, -2);
            params.cameraAt = Vector3(5, 4, 5);
            cout << "\nPreset 'Visao Frontal' aplicado!" << endl;
            break;
        case 2: // Canto
            params.cameraEye = Vector3(12, 4, -2);
            params.cameraAt = Vector3(5, 2, 5);
            cout << "\nPreset 'Visao de Canto' aplicado!" << endl;
            break;
        case 3: // Aerea
            params.cameraEye = Vector3(12, 10, -2);
            params.cameraAt = Vector3(5, 0, 5);
            cout << "\nPreset 'Visao Aerea' aplicado!" << endl;
            break;
        case 4: // Dramatica
            params.pointLight1Intensity = Color(1.2, 1.0, 0.8);
            params.pointLight2Intensity = Color(0.3, 0.3, 0.5);
            params.spotLightIntensity = Color(1.0, 0.8, 0.6);
            cout << "\nPreset 'Iluminacao Dramatica' aplicado!" << endl;
            break;
        case 5: // Suave
            params.pointLight1Intensity = Color(0.5, 0.5, 0.5);
            params.pointLight2Intensity = Color(0.6, 0.6, 0.7);
            params.spotLightIntensity = Color(0.4, 0.4, 0.5);
            cout << "\nPreset 'Iluminacao Suave' aplicado!" << endl;
            break;
        case 6: // Centralizados
            params.sphere1Pos = Vector3(5, 2, 5);
            params.sphere2Pos = Vector3(4, 1, 4);
            params.sphere3Pos = Vector3(6, 1.5, 6);
            params.cylinderPos = Vector3(7, 1, 5);
            params.conePos = Vector3(3, 0.75, 5);
            cout << "\nPreset 'Objetos Centralizados' aplicado!" << endl;
            break;
        default:
            return;
    }
    
    if (choice >= 1 && choice <= 6) {
        waitForEnter();
    }
}

void renderScene(const SceneParameters& params) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "   RENDERIZANDO CENA" << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    // Criar cena
    Scene scene;
    scene.backgroundColor = Color(0.2, 0.2, 0.25);
    
    // Materiais
    Material matRed(Color(0.2, 0.0, 0.0), Color(0.8, 0.1, 0.1), Color(0.8, 0.8, 0.8), 50.0);
    Material matBlue(Color(0.0, 0.0, 0.2), Color(0.2, 0.3, 0.8), Color(0.9, 0.9, 0.9), 100.0);
    Material matGreen(Color(0.0, 0.2, 0.0), Color(0.3, 0.8, 0.3), Color(0.2, 0.2, 0.2), 10.0);
    Material matGold(Color(0.2, 0.15, 0.0), Color(0.8, 0.6, 0.1), Color(1.0, 0.9, 0.5), 30.0);
    Material matFloor(Color(0.3, 0.25, 0.2), Color(0.6, 0.5, 0.4), Color(0.1, 0.1, 0.1), 5.0);
    Material matWall(Color(0.2, 0.2, 0.2), Color(0.7, 0.7, 0.75), Color(0.1, 0.1, 0.1), 5.0);
    
    // Objetos fixos (paredes, chão, teto)
    scene.addObject(make_shared<Plane>(Vector3(5, 0, 5), Vector3(0, 1, 0), matFloor));
    scene.addObject(make_shared<Plane>(Vector3(5, 0, 10), Vector3(0, 0, -1), matWall));
    scene.addObject(make_shared<Plane>(Vector3(0, 0, 5), Vector3(1, 0, 0), matWall));
    scene.addObject(make_shared<Plane>(Vector3(10, 0, 5), Vector3(-1, 0, 0), matWall));
    scene.addObject(make_shared<Plane>(Vector3(5, 8, 5), Vector3(0, -1, 0), matWall));
    
    // Objetos parametrizáveis
    scene.addObject(make_shared<Sphere>(params.sphere1Pos, 0.8, matRed));
    scene.addObject(make_shared<Sphere>(params.sphere2Pos, 0.5, matRed));
    scene.addObject(make_shared<Sphere>(params.sphere3Pos, 0.6, matBlue));
    scene.addObject(make_shared<Cylinder>(params.cylinderPos, 0.4, 2.0, Vector3(0, 1, 0), matBlue));
    scene.addObject(make_shared<Cone>(params.conePos, 0.7, 1.8, Vector3(0, 1, 0), matGreen));
    
    // Malha (pirâmide)
    auto mesh = make_shared<Mesh>(matGold);
    Vector3 base1(2.5, 0.1, 2.0), base2(3.5, 0.1, 2.0);
    Vector3 base3(3.5, 0.1, 3.0), base4(2.5, 0.1, 3.0);
    Vector3 apex(3.0, 1.5, 2.5);
    mesh->addTriangle(Triangle(base1, base2, apex, matGold));
    mesh->addTriangle(Triangle(base2, base3, apex, matGold));
    mesh->addTriangle(Triangle(base3, base4, apex, matGold));
    mesh->addTriangle(Triangle(base4, base1, apex, matGold));
    mesh->addTriangle(Triangle(base1, base2, base3, matGold));
    mesh->addTriangle(Triangle(base1, base3, base4, matGold));
    scene.addObject(mesh);
    
    // Luzes
    scene.setAmbientLight(make_shared<AmbientLight>(Color(0.2, 0.2, 0.25)));
    scene.addLight(make_shared<PointLight>(params.pointLight1Pos, params.pointLight1Intensity));
    scene.addLight(make_shared<PointLight>(params.pointLight2Pos, params.pointLight2Intensity));
    scene.addLight(make_shared<SpotLight>(params.spotLightPos, params.spotLightDir, 
                                          params.spotLightIntensity, 30, 2.0));
    scene.addLight(make_shared<DirectionalLight>(Vector3(-1, -1, -1), Color(0.3, 0.3, 0.4)));
    
    // Câmera
    Camera camera(params.cameraEye, params.cameraAt, params.cameraUp,
                  1.0, 8.0, 8.0, params.width, params.height);
    
    // Renderizar
    Renderer renderer(scene, camera);
    renderer.render("output/cena_parametrizada.ppm");
    
    cout << "\n========================================" << endl;
    cout << "RENDERIZACAO COMPLETA!" << endl;
    cout << "========================================" << endl;
    cout << "\nArquivo salvo: output/cena_parametrizada.ppm" << endl;
    cout << "\nPara converter para PNG:" << endl;
    cout << "  convert output/cena_parametrizada.ppm output/cena_parametrizada.png" << endl;
    
    waitForEnter();
}

int main() {
    SceneParameters params;
    int choice;
    
    do {
        showMenu();
        cin >> choice;
        
        switch(choice) {
            case 1: configureCamera(params); break;
            case 2: configureLights(params); break;
            case 3: configureObjects(params); break;
            case 4: configureResolution(params); break;
            case 5: showCurrentConfig(params); break;
            case 6: renderScene(params); break;
            case 7: applyPresets(params); break;
            case 0: 
                cout << "\nSaindo..." << endl;
                break;
            default:
                cout << "\nOpcao invalida!" << endl;
                waitForEnter();
        }
    } while (choice != 0);
    
    return 0;
}
