#include "../include/Vector3.h"
#include "../include/Matrix4x4.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void printVector(const string& label, const Vector3& v) {
    cout << label << ": (" << fixed << setprecision(3)
         << v.x << ", " << v.y << ", " << v.z << ")" << endl;
}

void printSeparator() {
    cout << "----------------------------------------" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "DEMONSTRACAO DE TRANSFORMACOES" << endl;
    cout << "Usando Matrix4x4" << endl;
    cout << "========================================\n" << endl;

    // Ponto de teste
    Vector3 point(2, 1, 3);
    Vector3 direction(1, 0, 0);

    cout << "Ponto original: (" << point.x << ", " << point.y << ", " << point.z << ")" << endl;
    cout << "Direcao original: (" << direction.x << ", " << direction.y << ", " << direction.z << ")" << endl;
    printSeparator();

    // ============ TRANSLAÇÃO ============
    cout << "\n1. TRANSLACAO" << endl;
    cout << "   Mover por (5, 2, 1)" << endl;
    Matrix4x4 translation = Matrix4x4::translation(5, 2, 1);
    Vector3 translated = translation.transformPoint(point);
    printVector("   Resultado", translated);
    printSeparator();

    // ============ ESCALA ============
    cout << "\n2. ESCALA" << endl;
    cout << "   Escalar por (2, 3, 0.5)" << endl;
    Matrix4x4 scale = Matrix4x4::scale(2, 3, 0.5);
    Vector3 scaled = scale.transformPoint(point);
    printVector("   Resultado", scaled);
    printSeparator();

    // ============ ROTAÇÃO EM TORNO DOS EIXOS ============
    cout << "\n3. ROTACAO EM TORNO DOS EIXOS" << endl;

    cout << "\n   a) Rotacao 90° em torno do eixo Y" << endl;
    Matrix4x4 rotY = Matrix4x4::rotationY(M_PI / 2);
    Vector3 rotatedY = rotY.transformPoint(point);
    printVector("      Resultado", rotatedY);

    cout << "\n   b) Rotacao 45° em torno do eixo X" << endl;
    Matrix4x4 rotX = Matrix4x4::rotationX(M_PI / 4);
    Vector3 rotatedX = rotX.transformPoint(point);
    printVector("      Resultado", rotatedX);

    cout << "\n   c) Rotacao 30° em torno do eixo Z" << endl;
    Matrix4x4 rotZ = Matrix4x4::rotationZ(M_PI / 6);
    Vector3 rotatedZ = rotZ.transformPoint(point);
    printVector("      Resultado", rotatedZ);
    printSeparator();

    // ============ ROTAÇÃO ARBITRÁRIA ============
    cout << "\n4. ROTACAO ARBITRARIA (BONUS +0.5 se implementada)" << endl;
    cout << "   Rotacao 60° em torno do eixo (1, 1, 1)" << endl;
    Vector3 axis(1, 1, 1);
    Matrix4x4 rotArbitrary = Matrix4x4::rotation(M_PI / 3, axis);
    Vector3 rotatedArbitrary = rotArbitrary.transformPoint(point);
    printVector("   Eixo (normalizado)", axis.normalized());
    printVector("   Resultado", rotatedArbitrary);
    printSeparator();

    // ============ CISALHAMENTO ============
    cout << "\n5. CISALHAMENTO / SHEARING (BONUS +0.5)" << endl;
    cout << "   Cisalhamento no plano XY" << endl;
    cout << "   shx = 0.5 (X afeta Y), shy = 0.3 (Y afeta X)" << endl;
    Matrix4x4 shear = Matrix4x4::shearingXY(0.5, 0.3);
    Vector3 sheared = shear.transformPoint(point);
    printVector("   Resultado", sheared);
    cout << "\n   Nota: Cisalhamento preserva area/volume mas distorce angulos" << endl;
    printSeparator();

    // ============ REFLEXÃO/ESPELHO ============
    cout << "\n6. REFLEXAO / ESPELHO (BONUS +0.5)" << endl;

    cout << "\n   a) Espelho no plano XY (normal = (0, 0, 1))" << endl;
    Matrix4x4 reflectXY = Matrix4x4::reflectionXY();
    Vector3 reflectedXY = reflectXY.transformPoint(point);
    printVector("      Original", point);
    printVector("      Refletido", reflectedXY);
    cout << "      Note: Z invertido" << endl;

    cout << "\n   b) Espelho no plano XZ (normal = (0, 1, 0))" << endl;
    Matrix4x4 reflectXZ = Matrix4x4::reflectionXZ();
    Vector3 reflectedXZ = reflectXZ.transformPoint(point);
    printVector("      Original", point);
    printVector("      Refletido", reflectedXZ);
    cout << "      Note: Y invertido" << endl;

    cout << "\n   c) Espelho em plano arbitrario" << endl;
    cout << "      Plano: ponto (0, 0, 0), normal (1, 1, 0)" << endl;
    Vector3 planeNormal(1, 1, 0);
    Vector3 planePoint(0, 0, 0);
    Matrix4x4 reflectArbitrary = Matrix4x4::reflectionPlane(planePoint, planeNormal);
    Vector3 reflectedArbitrary = reflectArbitrary.transformPoint(point);
    printVector("      Original", point);
    printVector("      Refletido", reflectedArbitrary);
    printSeparator();

    // ============ COMPOSIÇÃO DE TRANSFORMAÇÕES ============
    cout << "\n7. COMPOSICAO DE TRANSFORMACOES" << endl;
    cout << "   Sequencia: Rotacao 90° (Y) -> Translacao (5, 0, 0) -> Escala (2)" << endl;
    Matrix4x4 composite = Matrix4x4::translation(5, 0, 0) *
                          Matrix4x4::rotationY(M_PI / 2) *
                          Matrix4x4::scale(2.0);
    Vector3 composited = composite.transformPoint(point);
    printVector("   Resultado final", composited);
    cout << "\n   Nota: Ordem importa! Multiplicacao da DIREITA para ESQUERDA" << endl;
    printSeparator();

    // ============ TRANSFORMAÇÃO DE VETORES VS PONTOS ============
    cout << "\n8. DIFERENCAO: PONTOS VS DIRECOES" << endl;
    Vector3 testPoint(1, 2, 3);
    Vector3 testDirection(1, 0, 0);
    Matrix4x4 testTranslation = Matrix4x4::translation(10, 20, 30);

    cout << "\n   Translacao (10, 20, 30):" << endl;
    printVector("   Ponto original", testPoint);
    printVector("   Ponto transformado", testTranslation.transformPoint(testPoint));
    printVector("   Direcao original", testDirection);
    printVector("   Direcao transformada", testTranslation.transformDirection(testDirection));
    cout << "   Nota: Direcoes NAO sao afetadas por translacao!" << endl;
    printSeparator();

    cout << "\n========================================" << endl;
    cout << "RESUMO DAS TRANSFORMACOES IMPLEMENTADAS" << endl;
    cout << "========================================" << endl;
    cout << "\nObrigatorias:" << endl;
    cout << "  [✓] Translacao" << endl;
    cout << "  [✓] Rotacao (eixos X, Y, Z)" << endl;
    cout << "  [✓] Escala" << endl;
    cout << "\nBonus (+2.0 pontos no total):" << endl;
    cout << "  [✓] Rotacao Arbitraria (+0.0 - parte do requisito basico)" << endl;
    cout << "  [✓] Cisalhamento/Shearing (+0.5)" << endl;
    cout << "  [✓] Reflexao/Espelho em Plano (+0.5)" << endl;
    cout << "  [✓] Projecao Ortografica (+0.5)" << endl;
    cout << "  [✓] Projecao Obliqua (+0.5)" << endl;
    cout << "\nTodos os bônus implementados!" << endl;

    return 0;
}
