# 🎓 GUIA PARA APRESENTAÇÃO AO PROFESSOR

## 📍 ONDE ALTERAR O CÓDIGO PARA DEMONSTRAÇÕES

Todas as configurações estão no **início** do arquivo `src/interactive_opengl.cpp` nas **LINHAS 21-78**.

---

## 1️⃣ CÂMERA (Position, LookAt, Up, FOV)

**Arquivo:** `src/interactive_opengl.cpp`
**Linhas:** 33-42

```cpp
// Posição da câmera (onde está)
const Vector3 CAMERA_POSITION(6, 1.8, 2);

// Para onde a câmera olha
const Vector3 CAMERA_LOOKAT(6, 1.5, 10);

// Vetor "up" da câmera (orientação)
const Vector3 CAMERA_UP(0, 1, 0);

// Campo de visão (FOV) em graus
const float CAMERA_FOV = 60.0f;
```

### Exemplos de alteração:
```cpp
// Mover câmera mais para trás
const Vector3 CAMERA_POSITION(6, 1.8, -5);

// Olhar para outro ponto
const Vector3 CAMERA_LOOKAT(6, 1.5, 15);

// Aumentar FOV (visão mais ampla)
const float CAMERA_FOV = 90.0f;
```

---

## 2️⃣ TRANSFORMAÇÕES DE OBJETOS (Translação + Rotação)

**Arquivo:** `src/interactive_opengl.cpp`
**Linhas:** 47-55

```cpp
// Translação do altar (X, Y, Z)
Vector3 altarTranslation(0, 0, 0);

// Rotação do altar em torno do eixo Y (em radianos)
float altarRotationY = 0.0f;
```

### Exemplos de alteração:
```cpp
// Mover altar 2 unidades para direita
Vector3 altarTranslation(2, 0, 0);

// Mover altar 1 unidade para cima e 3 para frente
Vector3 altarTranslation(0, 1, 3);

// Rotacionar altar 90 graus (π/2 radianos)
float altarRotationY = 1.57f;

// Rotacionar altar 180 graus (π radianos)
float altarRotationY = 3.14f;
```

**Conversão graus → radianos:**
- 30° = 0.52 rad
- 45° = 0.79 rad
- 90° = 1.57 rad
- 180° = 3.14 rad

---

## 3️⃣ ILUMINAÇÃO (Posição e Cor das Luzes)

**Arquivo:** `src/interactive_opengl.cpp`
**Linhas:** 60-71

```cpp
// Luz 1: Hóstia (luz divina/sagrada)
const Vector3 LIGHT_HOSTIA_POS(6, 1.4, 18);
const Color LIGHT_HOSTIA_COLOR(0.7f, 0.7f, 0.8f);  // RGB

// Luz 2: Vela (luz quente)
const Vector3 LIGHT_CANDLE_POS(8, 1.1f, 17.5f);
const Color LIGHT_CANDLE_COLOR(0.5f, 0.15f, 0.075f);  // RGB

// Luz ambiente
const Color AMBIENT_LIGHT(0.15f, 0.15f, 0.18f);  // RGB
```

### Exemplos de alteração:
```cpp
// Luz mais intensa
const Color LIGHT_HOSTIA_COLOR(1.0f, 1.0f, 1.0f);

// Luz mais vermelha
const Color LIGHT_CANDLE_COLOR(1.0f, 0.2f, 0.1f);

// Ambiente mais claro
const Color AMBIENT_LIGHT(0.3f, 0.3f, 0.3f);

// Mover luz da hóstia para outro lugar
const Vector3 LIGHT_HOSTIA_POS(6, 5, 10);
```

---

## 4️⃣ OBJETOS EMISSIVOS (Brilho Próprio)

**Arquivo:** `src/interactive_opengl.cpp`
**Linhas:** 73-78

```cpp
const float EMISSIVE_HOSTIA = 2.0f;      // 200%
const float EMISSIVE_VITRAL = 0.9f;      // 90%
const float EMISSIVE_CANDLE = 1.3f;      // 130%
const float EMISSIVE_WALLS = 0.36f;      // 36%
const float EMISSIVE_CEILING = 0.36f;    // 36%
const float EMISSIVE_FLOOR = 0.08f;      // 8%
```

### Exemplos de alteração:
```cpp
// Hóstia mais brilhante
const float EMISSIVE_HOSTIA = 3.0f;

// Vitral mais fraco
const float EMISSIVE_VITRAL = 0.5f;

// Paredes muito brilhantes
const float EMISSIVE_WALLS = 0.9f;

// Chão brilhando igual paredes
const float EMISSIVE_FLOOR = 0.36f;
```

---

## 5️⃣ SOMBRAS (Shadow Rays)

**Arquivo:** `src/interactive_opengl.cpp`
**Linhas:** 95-99

```cpp
// Sombras ativadas/desativadas
const bool ENABLE_SHADOWS = true;

// Intensidade da sombra (0.0 = totalmente escuro, 1.0 = sem sombra)
const float SHADOW_INTENSITY = 0.3f;

// Pequeno offset para evitar "shadow acne"
const float SHADOW_BIAS = 0.001f;
```

### Exemplos de alteração:
```cpp
// Desativar sombras
const bool ENABLE_SHADOWS = false;

// Sombras mais escuras
const float SHADOW_INTENSITY = 0.1f;

// Sombras mais suaves
const float SHADOW_INTENSITY = 0.6f;

// Sem sombra (totalmente iluminado mesmo na sombra)
const float SHADOW_INTENSITY = 1.0f;
```

### Como funciona:
- **Shadow Rays**: Para cada ponto iluminado, traça um raio até a fonte de luz
- **Oclusão**: Se o raio encontrar um objeto, o ponto está na sombra
- **Objetos que projetam sombra**: Altar, bancos, ostensório, vela
- **Intensidade**: Controla o quanto a sombra escurece (0.3 = 30% da luz chega)

---

## 6️⃣ DIMENSÕES DA CAPELA

**Arquivo:** `src/interactive_opengl.cpp`
**Linhas:** 102-106

```cpp
const float CHAPEL_WIDTH = 12.0f;   // Largura (X)
const float CHAPEL_HEIGHT = 8.0f;   // Altura (Y)
const float CHAPEL_DEPTH = 20.0f;   // Profundidade (Z)
```

### Exemplos de alteração:
```cpp
// Capela mais larga
const float CHAPEL_WIDTH = 15.0f;

// Capela mais alta
const float CHAPEL_HEIGHT = 10.0f;

// Capela mais profunda
const float CHAPEL_DEPTH = 25.0f;
```

---

## 🔄 COMO APLICAR AS ALTERAÇÕES

1. Abra o arquivo: `src/interactive_opengl.cpp`
2. Vá para as **linhas 21-106** (seção de configurações)
3. Altere os valores desejados
4. Salve o arquivo
5. Recompile: `make clean && make`
6. Execute: `./interactive_opengl`

---

## 💡 RESPOSTAS PARA O PROFESSOR

### "Onde está a origem?"
**Resposta:** Na linha 81: Origem em `(0, 0, 0)` no canto frontal esquerdo do chão.

### "Todas coordenadas são positivas?"
**Resposta:** SIM! Capela vai de X[0,12], Y[0,8], Z[0,20]. Tudo positivo.

### "Mostre a câmera (position, lookAt, up)"
**Resposta:** Linhas 33-39. Atualmente:
- Position: `(6, 1.8, 2)`
- LookAt: `(6, 1.5, 10)`
- Up: `(0, 1, 0)`

### "Altere a posição da câmera"
**Ação:** Mude linha 34:
```cpp
const Vector3 CAMERA_POSITION(10, 3, 5);  // Nova posição
```
Depois: `make clean && make && ./interactive_opengl`

### "Faça translação do altar"
**Ação:** Mude linha 48:
```cpp
Vector3 altarTranslation(3, 0, 0);  // Move 3 unidades para direita
```
Depois: `make clean && make && ./interactive_opengl`

### "Faça rotação do altar"
**Ação:** Mude linha 52:
```cpp
float altarRotationY = 1.57f;  // Rotaciona 90 graus
```
Depois: `make clean && make && ./interactive_opengl`

### "Altere as luzes"
**Ação:** Mude linhas 61-62:
```cpp
const Vector3 LIGHT_HOSTIA_POS(6, 5, 15);  // Nova posição
const Color LIGHT_HOSTIA_COLOR(1.0f, 0.5f, 0.5f);  // Luz rosada
```
Depois: `make clean && make && ./interactive_opengl`

### "E as sombras, tem?"
**Resposta:** SIM! Sistema de shadow rays implementado (linhas 95-99 e 383-457).
- Sombras duras (hard shadows)
- Altar, bancos, ostensório e vela projetam sombras
- Configurável: pode ativar/desativar e ajustar intensidade

**Para desativar sombras:**
```cpp
const bool ENABLE_SHADOWS = false;  // Linha 95
```

**Para ajustar intensidade:**
```cpp
const float SHADOW_INTENSITY = 0.1f;  // Mais escuro (linha 96)
const float SHADOW_INTENSITY = 0.6f;  // Mais claro
```
Depois: `make clean && make && ./interactive_opengl`

---

## 📋 PROGRAMAS DISPONÍVEIS

### **Cena Principal** (TUDO ESTÁ AQUI):
```bash
./interactive_opengl
```
- ✅ Câmera interativa
- ✅ Transformações do altar (I/K/J/L/U/O/N/M/R)
- ✅ Picking com mouse
- ✅ Iluminação configurável
- ✅ Texturas (4)
- ✅ Sombras (shadow rays)
- ✅ Emissividade
- ✅ Vela interativa

### **Demo de Projeções** (NECESSÁRIO PARA PROFESSOR):
```bash
./projection_demo
```
- Gera 4 arquivos PPM em `output/`
- 3 tipos de projeção (planos de fuga):
  1. Perspectiva
  2. Ortográfica
  3. Oblíqua (Cavalier + Cabinet)

---

## 📋 COMMITS FINAIS

```bash
# Commit 1
git add src/Camera.cpp src/projection_demo.cpp
git commit -m "Corrigir coordenadas negativas para positivas"

# Commit 2
git add src/interactive_opengl.cpp Makefile textures/ceiling.jpg
git commit -m "Implementar ray tracing completo com todas funcionalidades"

# Commit 3
git add README.md GUIA_APRESENTACAO.md
git commit -m "Adicionar documentação completa"
```

---

## 🎯 ATALHO RÁPIDO

**Arquivo principal:** `src/interactive_opengl.cpp`
**Seção de configurações:** Linhas 21-106
**Comando para rodar:** `make clean && make && ./interactive_opengl`

## 📊 RECURSOS IMPLEMENTADOS

✅ **Câmera** - Position, LookAt, Up, FOV (configurável)
✅ **Transformações** - Translação e rotação do altar (Matrix4x4)
✅ **Iluminação** - 3 fontes de luz (hóstia, vela, ambiente)
✅ **Texturas** - 4 texturas (madeira, parede, vitral, teto)
✅ **Picking** - Identifica objetos ao clicar
✅ **Emissividade** - 6 objetos com brilho próprio
✅ **Sombras** - Shadow rays com intensidade configurável
✅ **Projeções** - Perspectiva, ortográfica, oblíqua (projection_demo)
✅ **Coordenadas positivas** - Todo sistema em X,Y,Z ≥ 0

✅ Tudo está parametrizado e comentado!
