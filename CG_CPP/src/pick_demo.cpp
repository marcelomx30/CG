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

int main() {
    cout << "========================================" << endl;
    cout << "DEMONSTRACAO DE PICKING" << endl;
    cout << "========================================\n" << endl;

    // Cria cena simples
    Scene scene;

    // Materiais
    Material matRed(
        Color(0.2, 0.0, 0.0),
        Color(0.8, 0.1, 0.1),
        Color(0.8, 0.8, 0.8),
        50.0
    );

    Material matBlue(
        Color(0.0, 0.0, 0.2),
        Color(0.2, 0.3, 0.8),
        Color(0.9, 0.9, 0.9),
        100.0
    );

    Material matGreen(
        Color(0.0, 0.2, 0.0),
        Color(0.3, 0.8, 0.3),
        Color(0.2, 0.2, 0.2),
        10.0
    );

    Material matFloor(
        Color(0.3, 0.3, 0.3),
        Color(0.6, 0.6, 0.6),
        Color(0.1, 0.1, 0.1),
        5.0
    );

    // Objetos com NOMES para picking
    auto sphere1 = make_shared<Sphere>(
        Vector3(5, 2, 5),
        1.0,
        matRed,
        "Esfera Vermelha"
    );
    scene.addObject(sphere1);

    auto sphere2 = make_shared<Sphere>(
        Vector3(3, 1, 7),
        0.8,
        matBlue,
        "Esfera Azul"
    );
    scene.addObject(sphere2);

    auto cylinder = make_shared<Cylinder>(
        Vector3(7, 0, 6),
        0.5,
        2.5,
        Vector3(0, 1, 0),
        matGreen,
        "Cilindro Verde"
    );
    scene.addObject(cylinder);

    auto floor = make_shared<Plane>(
        Vector3(0, 0, 0),
        Vector3(0, 1, 0),
        matFloor,
        "Chao"
    );
    scene.addObject(floor);

    // Configura câmera
    Camera camera(
        Vector3(10, 4, 2),    // eye
        Vector3(5, 2, 5),      // at
        Vector3(0, 1, 0),      // up
        3.0,                   // d
        4.0,                   // viewWidth
        4.0,                   // viewHeight
        500,                   // imageWidth
        500                    // imageHeight
    );

    cout << "Cena configurada com " << scene.objects.size() << " objetos:" << endl;
    for (const auto& obj : scene.objects) {
        cout << "  - " << obj->name << " (" << obj->getType() << ")" << endl;
    }
    cout << "\n========================================" << endl;
    cout << "TESTANDO PICKING EM VARIOS PIXELS" << endl;
    cout << "========================================\n" << endl;

    // Testa picking em várias coordenadas
    struct TestCase {
        int x, y;
        string description;
    };

    TestCase tests[] = {
        {250, 250, "Centro da imagem"},
        {200, 200, "Quadrante superior esquerdo"},
        {300, 300, "Quadrante inferior direito"},
        {400, 100, "Lateral direita superior"},
        {100, 400, "Lateral esquerda inferior"},
        {250, 400, "Centro inferior"},
        {0, 0, "Canto superior esquerdo"},
        {499, 499, "Canto inferior direito"}
    };

    for (const auto& test : tests) {
        cout << "\nTeste: " << test.description << endl;
        cout << "  Pixel: (" << test.x << ", " << test.y << ")" << endl;

        PickResult result = scene.pick(camera, test.x, test.y);

        if (result.hit) {
            cout << "  ✓ OBJETO ATINGIDO!" << endl;
            cout << "    Nome: " << result.objectName << endl;
            cout << "    Tipo: " << result.objectType << endl;
            cout << "    Ponto 3D: (" << result.hitPoint.x << ", "
                 << result.hitPoint.y << ", " << result.hitPoint.z << ")" << endl;
            cout << "    Distancia: " << result.distance << endl;
        } else {
            cout << "  ✗ Nenhum objeto atingido (background)" << endl;
        }
    }

    cout << "\n========================================" << endl;
    cout << "DEMONSTRACAO DE PICKING CONCLUIDA!" << endl;
    cout << "========================================" << endl;

    return 0;
}
