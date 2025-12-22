#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"

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
};

#endif // CAMERA_H
