# 🎨 RAY TRACING EM C++ - TRABALHO FINAL

## 📋 RESUMO

Ray Tracer completo com:
- ✅ Todos os obrigatórios
- ✅ Todos os bônus (+2.0 pontos)
- ✅ Texturas de imagem (madeira + vitral)
- ✅ Interface SDL2 (WASD + Mouse Picking)

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

Cena: Capela completa com texturas de madeira e vitral renderizadas em tempo real!

**Alternativa SDL2 (também sem GPU):**
```bash
make run-sdl
```

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
2. Renomeie para `wood.jpg` e `stained_glass.jpg`
3. Execute: `make run-capela-textured`

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
- `src/interactive_sdl.cpp` - Interface SDL2 interativa com ray tracing CPU + mouse picking
- `src/capela_textured.cpp` - Capela com texturas de imagem (renderização estática PPM)
- `src/pick_demo.cpp` - Demonstração da função de picking
- `include/Matrix4x4.h` - Transformações (rotação, escala, cisalhamento, reflexão)
- `include/Texture.h` - Carregamento de imagens JPG/PNG com stb_image
- `include/Camera.h` - Sistema de câmera com ray tracing
- `include/Objects.h` - Primitivas geométricas (esfera, plano, etc.)
- `include/Scene.h` - Sistema de cena com função `pick()` para picking
- `textures/` - Texturas trocáveis (wood.jpg, stained_glass.jpg)

## 📚 DOCUMENTAÇÃO

- `FEATURES.md` - Documentação técnica
- `make help` - Lista de comandos

## 💡 SOBRE A IMPLEMENTAÇÃO

Este projeto implementa **duas versões sem GPU**:

### 1. OpenGL com Software Rendering (RECOMENDADO)
- ✅ **Usa `LIBGL_ALWAYS_SOFTWARE=1` para forçar software rendering**
- ✅ OpenGL renderizado na CPU (sem aceleração de hardware)
- ✅ Mouse picking funcional com `gluUnProject`
- ✅ Texturas de madeira e vitral
- ✅ Iluminação e suavização
- 🎮 **Controles WASD + Mouse picking**

### 2. SDL2 com Ray Tracing CPU
- ✅ Ray tracing completo implementado do zero
- ✅ Reflexões físicas, sombras e texturas
- ✅ Mouse picking via ray casting
- ✅ Renderização de alta qualidade

**Ambas as versões funcionam sem GPU!** A versão OpenGL é mais rápida devido à pipeline de rasterização, mesmo rodando em software.

**NOTA ESPERADA: BASE + 2.0 BÔNUS** 🏆
