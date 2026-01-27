# 🎨 RAY TRACING EM C++ - TRABALHO FINAL

## 📋 RESUMO

Ray Tracer completo implementado 100% na CPU com:
- ✅ Todos os obrigatórios
- ✅ Todos os bônus (+2.0 pontos)
- ✅ Texturas de imagem (madeira + vitral + parede + teto)
- ✅ Interface interativa SDL2 + OpenGL (WASD + Mouse Picking + Ray Tracing na CPU)
- ✅ Sistema de iluminação Phong com objetos emissivos
- ✅ Capela 3D realista com todas as coordenadas positivas

## 🚀 COMO RODAR

### 1. Compilar:
```bash
make clean && make
```

### 2. Rodar programas:

**🎮 RAY TRACER INTERATIVO - CAPELA COMPLETA (Renderização na CPU):**
```bash
./interactive_opengl
# OU
make run
```

**Controles:**
- **W/A/S/D** - Mover câmera
- **Q/E** - Subir/Descer
- **Setas** - Rotacionar câmera
- **Mouse (clique)** - Picking de objetos (mostra nome e distância)
  - Clique na vela para **ligar/desligar** a luz
- **ESC** - Sair

**Para alterar transformações, câmera, luzes, sombras, etc:**
- Edite: `src/interactive_opengl.cpp` (linhas 21-135)
- Recompile: `make clean && make`
- Todos os parâmetros têm comentários explicativos e exemplos

**Cena:** Capela 3D realista (12m × 20m × 8m) com:
- Altar com ostensório e hóstia (raios dourados)
- Bancos de madeira
- Janela de vitral atrás do altar (emissiva)
- Vela interativa ao lado do altar
- Porta de entrada
- Texturas em paredes, teto, bancos e porta
- Sistema de iluminação Phong + objetos emissivos
- **Todas coordenadas positivas (X,Y,Z ≥ 0)**

**🎯 Demonstração para o professor (3 planos de fuga):**
```bash
./projection_demo      # Gera 4 imagens PPM com 3 projeções diferentes
                       # - Perspectiva
                       # - Ortográfica
                       # - Oblíqua (Cavalier e Cabinet)
```

**Nota:** Transformações e picking já estão integrados na cena principal (`./interactive_opengl`)

## 📝 TEXTURAS

O projeto usa 4 texturas localizadas em `textures/`:
- **`wood.jpg`** - Madeira (bancos, altar, porta)
- **`stained_glass.jpg`** - Vitral colorido (atrás do ostensório)
- **`wall.jpg`** - Paredes (4 paredes da capela)
- **`ceiling.jpg`** - Teto (uma única imagem esticada)

Para trocar texturas:
1. Substitua os arquivos em `textures/`
2. Mantenha os mesmos nomes de arquivo
3. Execute: `make clean && make && ./interactive_opengl`

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

### Executáveis:
- **`src/interactive_opengl.cpp`** - Ray tracer interativo na CPU (principal, 1100+ linhas)
  - Sistema completo de ray tracing (interseções, iluminação Phong, texturas)
  - Câmera interativa (position, lookAt, up, FOV)
  - Picking de objetos com mouse
  - Multi-threading para renderização eficiente
  - Vela interativa (liga/desliga ao clicar)
- **`src/transform_demo.cpp`** - Demonstração de transformações (translação, rotação, escala, cisalhamento)
- **`src/projection_demo.cpp`** - Demonstração de projeções (perspectiva, ortográfica, oblíqua Cavalier/Cabinet)
- **`src/pick_demo.cpp`** - Demonstração de picking

### Bibliotecas (include/):
- **`Matrix4x4.h`** - Transformações 4x4 (translação, rotação X/Y/Z/arbitrária, escala, cisalhamento, reflexão)
- **`Texture.h`** - Carregamento de texturas JPG/PNG usando stb_image
- **`Camera.h`** - Sistema de câmera (perspectiva, ortográfica, oblíqua)
- **`Objects.h`** - Primitivas geométricas (esfera, plano, cilindro, cone)
- **`Scene.h`** - Sistema de cena com picking
- **`Vector3.h`** - Vetores 3D com operações
- **`Color.h`** - Cores RGB
- **`Ray.h`** - Raios para ray tracing
- **`Material.h`** - Materiais com propriedades Phong
- **`Lights.h`** - Sistema de iluminação

### Recursos:
- **`textures/`** - Texturas (wood.jpg, stained_glass.jpg, wall.jpg, ceiling.jpg)
- **`Makefile`** - Sistema de build

## 💡 SOBRE A IMPLEMENTAÇÃO

### Arquitetura:
Este projeto implementa um **ray tracer completo na CPU** com interface interativa usando SDL2 e OpenGL:

- **Ray Tracing na CPU**: Todo o rendering é feito por ray tracing (sem rasterização GPU)
- **SDL2 + OpenGL**: Apenas para exibir o framebuffer na tela (texture upload)
- **Multi-threading**: Renderização em tiles paralelos para performance
- **Sistema de coordenadas**: Todas coordenadas positivas (X,Y,Z ≥ 0)
  - Origem: `(0, 0, 0)` no canto frontal esquerdo do chão
  - Capela: X[0,12], Y[0,8], Z[0,20] (12m × 8m × 20m)

### Características técnicas:

#### 🎨 Ray Tracing:
- Interseções: esfera, plano finito, cilindro, cone, caixa (AABB)
- Iluminação Phong: ambiente + difusa + especular
- **Sombras**: Shadow rays com intensidade configurável (hard shadows)
- Objetos emissivos: hóstia (200%), vitral (90%), chama da vela (130%)
- Emissão ambiente: paredes e teto (36%), chão (8%)

#### 📷 Câmera:
- Position/LookAt/Up: `(6, 1.8, 2)` / `(6, 1.5, 10)` / `(0, 1, 0)`
- FOV: 60°
- Rotação: yaw (horizontal) e pitch (vertical) com limitação

#### 💡 Iluminação:
- **Luz 1 (Hóstia)**: `(6, 1.4, 18)` - branca/azulada suave `RGB(0.7, 0.7, 0.8)`
- **Luz 2 (Vela)**: `(8, 1.1, 17.5)` - vermelha/laranja `RGB(0.5, 0.15, 0.075)` (controlável)
- **Ambiente**: azulado escuro `RGB(0.15, 0.15, 0.18)`

#### 🖼️ Texturas:
- Mapeamento UV automático por tipo de superfície
- Teto: uma única imagem esticada (não repetida)
- Paredes/Chão: tiled com escala configurável
- 4 texturas carregadas: madeira, vitral, parede, teto

#### 🎯 Picking:
- Ray casting através do pixel clicado
- Identifica objeto, distância e posição 3D
- Vela: interatividade (liga/desliga luz ao clicar)

### Objetos da cena:
- **Chão**: plano Y=0, textura procedural ou cor sólida
- **4 Paredes**: finitas com textura de parede
- **Teto**: plano Y=8 com textura de teto esticada
- **Porta**: caixa com textura de madeira em Z=0
- **Altar**: caixa com textura de madeira (com transformações aplicadas)
- **Bancos**: 8 bancos (4 esquerda, 4 direita) com textura de madeira (projetam sombras)
- **Ostensório**: cilindro dourado + hóstia (esfera branca) + 8 raios com esferas nas pontas (projeta sombras)
- **Vitral**: plano emissivo atrás do ostensório com textura colorida
- **Vela**: cilindro vermelho com cone amarelo (chama) quando acesa (projeta sombras)

## 🏆 REQUISITOS ATENDIDOS

**NOTA ESPERADA: BASE (10.0) + BÔNUS (+2.0) = 12.0** 🏆
