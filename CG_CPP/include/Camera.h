#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"

// Tipos de projeção suportados
enum class ProjectionType {
    PERSPECTIVE,   // Projeção perspectiva (padrão)
    ORTHOGRAPHIC,  // Projeção ortográfica (paralela)
    OBLIQUE        // Projeção oblíqua (cavalier/cabinet)
};

class Camera {
public:
    Vector3 eye;     // Posição da câmera
    Vector3 at;      // Ponto de visada
    Vector3 up;      // Vetor up
    double d;        // Distância focal
    double viewWidth;
    double viewHeight;
    int imageWidth;
    int imageHeight;

    // Tipo de projeção
    ProjectionType projectionType;

    // Parâmetros para projeção oblíqua
    double obliqueAngle;   // Ângulo em graus (tipicamente 45° ou 63.4°)
    double obliqueFactor;  // Fator de escala (0.5 para cabinet, 1.0 para cavalier)

    // Sistema de coordenadas da câmera
    Vector3 u, v, w;
    
    Camera();
    Camera(const Vector3& eye, const Vector3& at, const Vector3& up,
           double d, double viewWidth, double viewHeight,
           int imageWidth, int imageHeight);
    
    void computeCameraFrame();
    Ray getRay(int i, int j) const;
    void zoom(double factor);
    void setFOV(double fovDegrees);

    // Configuração de projeções
    void setPerspective();
    void setOrthographic();
    void setOblique(double angleDegrees = 45.0, double factor = 1.0);  // Cavalier por padrão
    void setObliqueCabinet();  // Atalho para projeção cabinet (angle=63.4°, factor=0.5)
};

#endif // CAMERA_H
