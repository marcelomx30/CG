# 🎨 RAY TRACING EM C++ - TRABALHO FINAL

## 📋 RESUMO

Ray Tracer completo com:
- ✅ Todos os obrigatórios
- ✅ Todos os bônus (+2.0 pontos)
- ✅ Texturas de imagem (madeira + vitral + parede)
- ✅ Interface OpenGL (WASD + Mouse Picking + Software Rendering)

## 🚀 COMO RODAR

### 1. Compilar:
```bash
make
```

### 2. Rodar programas:

**🎮 INTERFACE OPENGL - CAPELA COMPLETA (WASD + Mouse + Software Rendering):**
```bash
make run-opengl
```
**✓ USA SOFTWARE RENDERING (SEM GPU!)**

Controles:
- W/A/S/D - Mover câmera
- Q/E - Subir/Descer
- Setas - Rotacionar view
- Mouse - Click para PICKING de objetos
- ESC - Sair

Cena: Capela completa com texturas de madeira, vitral e paredes renderizadas em tempo real!

**📷 Cenas estáticas (render para arquivo PPM):**
```bash
make run                   # Textura xadrez
make run-capela-textured   # Capela com texturas de imagem
```

**🎯 Demos (requisitos do trabalho):**
```bash
make run-pick          # Demonstração de Picking
make run-projections   # Demonstração de Projeções
make run-transforms    # Demonstração de Transformações
```

## 📝 TROCAR TEXTURAS

1. Coloque imagens em `textures/`
2. Renomeie para:
   - `wood.jpg` (madeira - altar e bancos)
   - `stained_glass.jpg` (vitral)
   - `wall.jpg` (paredes)
3. Execute: `make run-opengl`

## ✅ REQUISITOS

### Obrigatórios (3/3):
- ✅ Textura em objeto (xadrez + imagens)
- ✅ Picking (terminal + SDL2 mouse)
- ✅ Rotação arbitrária (Matrix4x4)

### Bônus (+2.0 pontos):
- ✅ Cisalhamento (+0.5)
- ✅ Espelho em plano (+0.5)
- ✅ Projeção ortográfica (+0.5)
- ✅ Projeção oblíqua (+0.5)

## 📂 ARQUIVOS PRINCIPAIS

- `src/interactive_opengl.cpp` - **Interface OpenGL com SOFTWARE RENDERING (sem GPU) + mouse picking**
- `src/capela_textured.cpp` - Capela com texturas de imagem (renderização estática PPM)
- `src/pick_demo.cpp` - Demonstração da função de picking
- `include/Matrix4x4.h` - Transformações (rotação, escala, cisalhamento, reflexão)
- `include/Texture.h` - Carregamento de imagens JPG/PNG com stb_image
- `include/Camera.h` - Sistema de câmera com ray tracing
- `include/Objects.h` - Primitivas geométricas (esfera, plano, cilindro, cone)
- `include/Scene.h` - Sistema de cena com função `pick()` para picking
- `textures/` - Texturas trocáveis (wood.jpg, stained_glass.jpg, wall.jpg)

## 📚 DOCUMENTAÇÃO

- `FEATURES.md` - Documentação técnica
- `make help` - Lista de comandos

## 💡 SOBRE A IMPLEMENTAÇÃO

Este projeto implementa **OpenGL com Software Rendering (sem GPU)**:

- ✅ **Usa `LIBGL_ALWAYS_SOFTWARE=1` para forçar software rendering**
- ✅ OpenGL renderizado na CPU (sem aceleração de hardware)
- ✅ Mouse picking funcional com `gluUnProject`
- ✅ Três texturas: madeira (altar/bancos), vitral, paredes
- ✅ Iluminação com 2 luzes (principal + vela)
- ✅ Todos os objetos obrigatórios: ESFERA, CILINDRO, CONE, MALHA
- 🎮 **Controles WASD + Q/E + Setas + Mouse picking**

A versão OpenGL roda completamente na CPU através do llvmpipe (Mesa), garantindo funcionamento em qualquer sistema sem GPU!

**NOTA ESPERADA: BASE + 2.0 BÔNUS** 🏆
