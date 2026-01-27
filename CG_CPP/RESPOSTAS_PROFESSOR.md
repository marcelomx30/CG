# 📝 PERGUNTAS E RESPOSTAS PARA O PROFESSOR

## 🎯 GUIA COMPLETO PARA A APRESENTAÇÃO

---

## 1️⃣ "ONDE ESTÁ A ORIGEM?"

### **Resposta:**
A origem está em **(0, 0, 0)** no **canto frontal esquerdo do chão** da capela.

### **Explicação detalhada:**
- **Eixo X:** 0 a 12 (largura da capela - 12 metros)
- **Eixo Y:** 0 a 8 (altura da capela - 8 metros)
- **Eixo Z:** 0 a 20 (profundidade da capela - 20 metros)
- **Sistema:** Mão direita (X direita, Y cima, Z profundidade)

### **Onde está no código:**
```
Arquivo: src/interactive_opengl.cpp
Linhas: 119-123

const float CHAPEL_WIDTH = 12.0f;   // Largura (eixo X)
const float CHAPEL_HEIGHT = 8.0f;   // Altura (eixo Y)
const float CHAPEL_DEPTH = 20.0f;   // Profundidade (eixo Z)
```

### **Demonstração visual:**
Aponte para o chão na entrada da capela (onde seria a porta).

---

## 2️⃣ "TODAS AS COORDENADAS SÃO POSITIVAS?"

### **Resposta:**
✅ **SIM!** Todas as coordenadas são positivas (X ≥ 0, Y ≥ 0, Z ≥ 0).

### **Explicação detalhada:**
Durante o desenvolvimento, corrigimos todos os valores negativos:
- Camera.cpp: `at` era (0,0,-1) → agora é (0,0,1)
- projection_demo.cpp: câmera era (10,4,-2) → agora é (10,4,2)
- Todos os objetos da cena estão dentro do volume da capela: X[0,12], Y[0,8], Z[0,20]

### **Onde está no código:**
```
Arquivo: src/Camera.cpp
Linha: 5

Camera() : eye(0, 0, 0), at(0, 0, 1), up(0, 1, 0)  // at positivo em Z
```

```
Arquivo: src/interactive_opengl.cpp
Exemplos de objetos:
- Chão: Y=0, X[0,12], Z[0,20] (linha ~645)
- Altar: X[4.5,7.5], Y[0,0.8], Z[17.5,18.5] (linha ~785)
- Ostensório: (6, 1.4, 18) - tudo positivo (linha ~864)
```

### **Commits relacionados:**
Veja o commit "Corrigir coordenadas negativas para positivas" no git log.

---

## 3️⃣ "MOSTRE A CÂMERA (Position, LookAt, Up)"

### **Resposta:**
A câmera está implementada com **Position, LookAt e Up**.

### **Valores atuais:**
```cpp
Position: (6, 1.8, 2)      // Centro horizontal, altura do olho, perto da entrada
LookAt:   (6, 1.5, 10)     // Olhando para o centro da capela
Up:       (0, 1, 0)        // Vetor "para cima" (eixo Y)
FOV:      60 graus         // Campo de visão
```

### **Onde está no código:**
```
Arquivo: src/interactive_opengl.cpp
Linhas: 34-56

const Vector3 CAMERA_POSITION(6, 1.8, 2);     // ← Position
const Vector3 CAMERA_LOOKAT(6, 1.5, 10);      // ← LookAt
const Vector3 CAMERA_UP(0, 1, 0);             // ← Up
const float CAMERA_FOV = 60.0f;               // ← FOV
```

### **Como funciona:**
```cpp
// Linhas 127-145: Estrutura Camera
struct Camera {
    Vector3 position;  // Onde a câmera está
    Vector3 lookAt;    // Para onde ela olha
    Vector3 up;        // Orientação vertical
    float fov;         // Campo de visão

    Ray generateRay(float px, float py, float aspectRatio) const {
        Vector3 forward = (lookAt - position).normalized();
        Vector3 right = forward.cross(up).normalized();
        Vector3 newUp = right.cross(forward);
        // ... gera raio para ray tracing
    }
};
```

---

## 4️⃣ "ALTERE A POSIÇÃO DA CÂMERA"

### **Resposta:**
Vou alterar a posição da câmera no código e recompilar.

### **Passo a passo:**

1. **Abrir arquivo:**
```
src/interactive_opengl.cpp
```

2. **Ir para linha 37** (ou procurar "1️⃣ CÂMERA"):

3. **Estado atual:**
```cpp
const Vector3 CAMERA_POSITION(6, 1.8, 2);     // ← ALTERE AQUI
```

4. **Alterar para (exemplo):**
```cpp
const Vector3 CAMERA_POSITION(10, 3, 5);      // ← ALTERE AQUI
// Câmera mais longe, mais alta, mais à direita
```

5. **Salvar e recompilar:**
```bash
make clean && make
./interactive_opengl
```

6. **Mostrar resultado:** Câmera agora está em posição diferente!

### **Outros exemplos para testar:**
```cpp
// Vista de trás
const Vector3 CAMERA_POSITION(6, 1.8, 25);

// Vista lateral esquerda
const Vector3 CAMERA_POSITION(-2, 2, 10);

// Vista de cima (olho de Deus)
const Vector3 CAMERA_POSITION(6, 15, 10);
const Vector3 CAMERA_LOOKAT(6, 0, 10);  // Olhando para baixo
```

---

## 5️⃣ "FAÇA TRANSLAÇÃO DE OBJETOS"

### **Resposta:**
Vou transladar o altar modificando os valores no código.

### **Passo a passo:**

1. **Abrir arquivo:**
```
src/interactive_opengl.cpp
```

2. **Ir para linha 64** (ou procurar "2️⃣ TRANSFORMAÇÕES"):

3. **Estado atual:**
```cpp
Vector3 altarTranslation(0, 0, 0);        // ← ALTERE AQUI
```

4. **Alterar para (exemplo - mover para direita):**
```cpp
Vector3 altarTranslation(2, 0, 0);        // ← ALTERE AQUI
// Move 2 unidades para DIREITA (X+)
```

5. **Salvar e recompilar:**
```bash
make clean && make
./interactive_opengl
```

6. **Mostrar resultado:** Altar deslocado 2 unidades para direita!

### **Explicação técnica:**
```
Arquivo: src/interactive_opengl.cpp
Linhas: 801-816 (aplicação da transformação)

// Cria matriz de transformação
Matrix4x4 transform = Matrix4x4::translation(altarTranslation) *
                     Matrix4x4::translation(altarCenter) *
                     Matrix4x4::rotationY(altarRotationY) *
                     Matrix4x4::translation(altarCenter * -1.0f);

// Aplica transformação usando Matrix4x4
Vector3 altarMin = transform.transformPoint(baseMin);
Vector3 altarMax = transform.transformPoint(baseMax);
```

### **Outros exemplos para testar:**
```cpp
// Mover para cima
Vector3 altarTranslation(0, 1, 0);

// Mover para frente
Vector3 altarTranslation(0, 0, 3);

// Combinação: direita + cima + frente
Vector3 altarTranslation(2, 1, 3);

// Mover para esquerda (negativo)
Vector3 altarTranslation(-2, 0, 0);
```

### **Implementação de Matrix4x4:**
```
Arquivo: include/Matrix4x4.h
Linhas: 70-76

static Matrix4x4 translation(double tx, double ty, double tz) {
    Matrix4x4 result;
    result.m[0][3] = tx;
    result.m[1][3] = ty;
    result.m[2][3] = tz;
    return result;
}
```

---

## 6️⃣ "FAÇA ROTAÇÃO DE OBJETOS"

### **Resposta:**
Vou rotacionar o altar em torno do eixo Y.

### **Passo a passo:**

1. **Abrir arquivo:**
```
src/interactive_opengl.cpp
```

2. **Ir para linha 75** (ou procurar "altarRotationY"):

3. **Estado atual:**
```cpp
float altarRotationY = 0.0f;              // ← ALTERE AQUI
```

4. **Alterar para (exemplo - 90 graus):**
```cpp
float altarRotationY = 1.57f;             // ← ALTERE AQUI
// 1.57 radianos = ~90 graus
```

5. **Salvar e recompilar:**
```bash
make clean && make
./interactive_opengl
```

6. **Mostrar resultado:** Altar rotacionado 90 graus!

### **Conversão graus → radianos:**
```
30°  = 0.52 rad
45°  = 0.79 rad
60°  = 1.05 rad
90°  = 1.57 rad
180° = 3.14 rad
270° = 4.71 rad
360° = 6.28 rad

Fórmula: radianos = graus × π / 180
```

### **Outros exemplos para testar:**
```cpp
// 45 graus
float altarRotationY = 0.79f;

// 180 graus (virado de costas)
float altarRotationY = 3.14f;

// -90 graus (sentido oposto)
float altarRotationY = -1.57f;
```

### **Implementação de Matrix4x4 (rotação em Y):**
```
Arquivo: include/Matrix4x4.h
Linhas: 110-119

static Matrix4x4 rotationY(double angle) {
    Matrix4x4 result;
    double c = cos(angle);
    double s = sin(angle);
    result.m[0][0] = c;
    result.m[0][2] = s;
    result.m[2][0] = -s;
    result.m[2][2] = c;
    return result;
}
```

### **Como a rotação é aplicada:**
```
src/interactive_opengl.cpp
Linhas: 801-816

// Rotaciona em torno do centro do altar
Matrix4x4 transform = Matrix4x4::translation(altarTranslation) *
                     Matrix4x4::translation(altarCenter) *        // Move para origem
                     Matrix4x4::rotationY(altarRotationY) *       // Rotaciona
                     Matrix4x4::translation(altarCenter * -1.0f); // Move de volta
```

---

## 7️⃣ "ALTERE AS LUZES"

### **Resposta:**
Vou alterar a posição e/ou cor das luzes.

### **Sistema de iluminação:**
- **3 fontes de luz:**
  1. Luz da hóstia (divina) - branca/azulada
  2. Luz da vela (quente) - vermelha/laranja
  3. Luz ambiente (global) - azul escuro

### **Passo a passo:**

1. **Abrir arquivo:**
```
src/interactive_opengl.cpp
```

2. **Ir para linha 80** (ou procurar "3️⃣ ILUMINAÇÃO"):

3. **Estado atual:**
```cpp
const Vector3 LIGHT_HOSTIA_POS(6, 1.4, 18);           // ← Posição
const Color LIGHT_HOSTIA_COLOR(0.7f, 0.7f, 0.8f);     // ← Cor RGB
```

4. **Exemplo 1 - Alterar posição (luz mais alta):**
```cpp
const Vector3 LIGHT_HOSTIA_POS(6, 5, 15);             // ← ALTERE AQUI
// Luz 3.6m mais alta, 3m mais para frente
```

5. **Exemplo 2 - Alterar cor (luz mais rosada):**
```cpp
const Color LIGHT_HOSTIA_COLOR(1.0f, 0.5f, 0.5f);     // ← ALTERE AQUI
// R=1.0 (vermelho total), G=0.5 (verde médio), B=0.5 (azul médio)
```

6. **Salvar e recompilar:**
```bash
make clean && make
./interactive_opengl
```

### **Onde as luzes são usadas:**
```
src/interactive_opengl.cpp
Linhas: 1073-1077

vector<Light> lights;
lights.push_back(Light(LIGHT_HOSTIA_POS, LIGHT_HOSTIA_COLOR));
lights.push_back(Light(LIGHT_CANDLE_POS, LIGHT_CANDLE_COLOR, candleLit));
Color ambient = AMBIENT_LIGHT;
```

### **Modelo de iluminação Phong:**
```
src/interactive_opengl.cpp
Linhas: 539-577

Color phongShading(...) {
    Color result = baseColor * ambient * 0.3f;  // Componente ambiente

    for (const auto& light : lights) {
        Vector3 lightDir = (light.position - point).normalized();

        // Componente difusa (Lambert)
        float diff = max(0.0f, normal.dot(lightDir));
        Color diffuse = baseColor * light.intensity * diff;

        // Componente especular (Phong)
        Vector3 reflectDir = ...;
        float spec = pow(..., shininess);
        Color specular = light.intensity * spec * 0.5f;

        result = result + diffuse + specular;
    }
    return result;
}
```

### **Outros exemplos para testar:**
```cpp
// Ambiente mais claro
const Color AMBIENT_LIGHT(0.3f, 0.3f, 0.3f);

// Luz da vela mais forte
const Color LIGHT_CANDLE_COLOR(1.0f, 0.3f, 0.1f);

// Luz branca pura
const Color LIGHT_HOSTIA_COLOR(1.0f, 1.0f, 1.0f);
```

---

## 8️⃣ "APRESENTE 3 PLANOS DE FUGA E EXPLIQUE"

### **Resposta:**
Implementamos 3 tipos de projeção (planos de fuga) **diretamente na cena principal interativa**.

### **1. Projeção Perspectiva:**
- **O que é:** Simula visão humana - objetos distantes ficam menores
- **Pontos de fuga:** 1, 2 ou 3 (dependendo da orientação)
- **Uso:** Realismo, jogos, visualizações arquitetônicas

### **2. Projeção Ortográfica:**
- **O que é:** Sem distorção de profundidade - tamanho preservado
- **Pontos de fuga:** Nenhum (linhas paralelas permanecem paralelas)
- **Uso:** Plantas arquitetônicas, desenhos técnicos, CAD

### **3. Projeção Oblíqua:**
- **O que é:** Mantém uma face sem distorção, profundidade em ângulo
- **Tipos implementados:**
  - **Cavalier:** Ângulo 45°, fator 1.0 (profundidade real)
  - **Cabinet:** Ângulo 63.4°, fator 0.5 (profundidade reduzida)
- **Pontos de fuga:** Infinito em uma direção
- **Uso:** Ilustrações técnicas, diagramas

### **Como demonstrar - OPÇÃO 1 (RECOMENDADO):**
**Na cena principal interativa:**
```bash
./interactive_opengl
```
**Durante execução, pressione:**
- **Tecla 1** → Perspectiva
- **Tecla 2** → Ortográfica
- **Tecla 3** → Oblíqua Cavalier
- **Tecla 4** → Oblíqua Cabinet

O título da janela mostra qual projeção está ativa.

### **Como demonstrar - OPÇÃO 2:**
**Gerar imagens PPM:**
```bash
./projection_demo
```
Gera 4 arquivos em `output/`:
- `projecao_perspectiva.ppm`
- `projecao_ortografica.ppm`
- `projecao_obliqua_cavalier.ppm`
- `projecao_obliqua_cabinet.ppm`

### **Onde está no código (cena principal):**
```
Arquivo: src/interactive_opengl.cpp

Linhas 161-174: ENUM E CONFIGURAÇÃO
enum ProjectionType {
    PROJECTION_PERSPECTIVE,   // Tecla 1
    PROJECTION_ORTHOGRAPHIC,  // Tecla 2
    PROJECTION_OBLIQUE_CAV,   // Tecla 3: Cavalier (45°, fator 1.0)
    PROJECTION_OBLIQUE_CAB    // Tecla 4: Cabinet (63.4°, fator 0.5)
};

ProjectionType currentProjection = PROJECTION_PERSPECTIVE;

Linhas 197-246: GERAÇÃO DE RAIOS POR PROJEÇÃO
Ray generateRay(float px, float py, float aspectRatio) const {
    switch(currentProjection) {
        case PROJECTION_PERSPECTIVE: {
            // Perspectiva: raios convergem para posição da câmera
            float tanFov = tan(fov * 0.5f * M_PI / 180.0f);
            rayDir = forward + right * (px * tanFov * aspectRatio) + newUp * (py * tanFov);
            break;
        }
        case PROJECTION_ORTHOGRAPHIC: {
            // Ortográfica: raios paralelos
            float scale = 5.0f;
            rayOrigin = position + right * (px * scale * aspectRatio) + newUp * (py * scale);
            rayDir = forward;
            break;
        }
        case PROJECTION_OBLIQUE_CAV: {
            // Cavalier: 45°, fator 1.0
            Vector3 oblique = right * (cos(45° * π/180) * 1.0) + newUp * (sin(45° * π/180) * 1.0);
            rayDir = forward + oblique;
            break;
        }
        case PROJECTION_OBLIQUE_CAB: {
            // Cabinet: 63.4°, fator 0.5
            Vector3 oblique = right * (cos(63.4° * π/180) * 0.5) + newUp * (sin(63.4° * π/180) * 0.5);
            rayDir = forward + oblique;
            break;
        }
    }
}

Linhas 1368-1389: TECLAS PARA ALTERNAR PROJEÇÕES
case SDLK_1:
    currentProjection = PROJECTION_PERSPECTIVE;
    SDL_SetWindowTitle(window, "Capela Ray Tracing - Projecao: Perspectiva");
    break;
case SDLK_2:
    currentProjection = PROJECTION_ORTHOGRAPHIC;
    SDL_SetWindowTitle(window, "Capela Ray Tracing - Projecao: Ortografica");
    break;
case SDLK_3:
    currentProjection = PROJECTION_OBLIQUE_CAV;
    SDL_SetWindowTitle(window, "Capela Ray Tracing - Projecao: Obliqua Cavalier");
    break;
case SDLK_4:
    currentProjection = PROJECTION_OBLIQUE_CAB;
    SDL_SetWindowTitle(window, "Capela Ray Tracing - Projecao: Obliqua Cabinet");
    break;
```

### **Vantagem da implementação:**
✅ **Interativa**: Alterna entre projeções em tempo real sem recompilar
✅ **Visual**: Título da janela mostra projeção ativa
✅ **Completa**: Todas as 3 projeções na mesma cena com todas as funcionalidades

---

## 9️⃣ "EXPLIQUE AS TEXTURAS"

### **Resposta:**
Implementamos 4 texturas com mapeamento UV.

### **Texturas do projeto:**
1. **wood.jpg** - Madeira (bancos, altar, porta)
2. **wall.jpg** - Paredes (4 paredes da capela)
3. **stained_glass.jpg** - Vitral colorido (atrás do ostensório)
4. **ceiling.jpg** - Teto (uma única imagem esticada)

### **Sistema de carregamento:**
```
Arquivo: src/interactive_opengl.cpp
Linhas: 1117-1141

// Carrega texturas com stb_image
if (!woodTexture.load("textures/wood.jpg")) {
    cout << "Aviso: Nao foi possivel carregar textura de madeira" << endl;
} else {
    cout << "✓ Textura de madeira carregada" << endl;
}
```

### **Mapeamento UV:**

**Para planos (paredes, chão, teto):**
```
Linhas: 293-327

bool intersectPlane(...) {
    // Calcula UV baseado na orientação do plano
    if (fabs(normal.y) > 0.9f) {
        // Plano horizontal (chão/teto)
        rec.u = fmod(rec.point.x * uvScale, 1.0);
        rec.v = fmod(rec.point.z * uvScale, 1.0);
    } else if (fabs(normal.z) > 0.5f) {
        // Plano frontal/traseiro
        rec.u = fmod(rec.point.z * uvScale, 1.0);
        rec.v = fmod(rec.point.y * uvScale, 1.0);
    } else {
        // Plano lateral
        rec.u = fmod(rec.point.x * uvScale, 1.0);
        rec.v = fmod(rec.point.y * uvScale, 1.0);
    }

    // Garante [0,1]
    if (rec.u < 0) rec.u += 1.0;
    if (rec.v < 0) rec.v += 1.0;
}
```

**Para caixas (altar, bancos, porta):**
```
Linhas: 354-395

bool intersectBox(...) {
    // Calcula UV baseado na face atingida
    Vector3 size = max - min;

    if (fabs(rec.normal.y) > 0.9f) {
        // Face horizontal
        rec.u = (rec.point.x - min.x) / size.x;
        rec.v = (rec.point.z - min.z) / size.z;
    } else if (fabs(rec.normal.z) > 0.5f) {
        // Face frontal/traseira
        rec.u = (rec.point.z - min.z) / size.z;
        rec.v = (rec.point.y - min.y) / size.y;
    } else {
        // Face lateral
        rec.u = (rec.point.x - min.x) / size.x;
        rec.v = (rec.point.y - min.y) / size.y;
    }
}
```

**Teto especial (uma única imagem esticada):**
```
Linhas: 838-843

rec.objectName = "Teto";
// UMA ÚNICA imagem para todo o teto (não repete)
rec.u = p.x / CHAPEL_WIDTH;   // 0 a 1 ao longo da largura
rec.v = p.z / CHAPEL_DEPTH;   // 0 a 1 ao longo do comprimento
```

### **Aplicação da textura no Phong:**
```
Linhas: 551-556

Color phongShading(...) {
    Color baseColor = albedo;
    if (useTexture && texture && texture->isLoaded()) {
        baseColor = texture->sample(u, v);  // Amostra cor da textura
    }
    // ... continua com cálculo Phong usando baseColor
}
```

---

## 🔟 "E AS SOMBRAS, TEM?"

### **Resposta:**
✅ **SIM!** Implementamos sombras usando **shadow rays**.

### **Como funciona:**
1. Para cada ponto iluminado, traçamos um raio até a fonte de luz
2. Se o raio intersecta um objeto, o ponto está na sombra
3. A intensidade da sombra é configurável (quanto de luz chega)

### **Objetos que projetam sombras:**
- Altar (com transformações aplicadas)
- Bancos (8 unidades)
- Ostensório (base + hóstia)
- Vela

### **Configuração:**
```
Arquivo: src/interactive_opengl.cpp
Linhas: 110-120

const bool ENABLE_SHADOWS = true;         // ← Liga/desliga
const float SHADOW_INTENSITY = 0.3f;      // ← 0.0=preto, 1.0=sem sombra
const float SHADOW_BIAS = 0.001f;         // ← Anti-acne
```

### **Implementação do shadow ray:**
```
Linhas: 400-475 (função isInShadow)

bool isInShadow(const Vector3& point, const Vector3& lightPos, const Vector3& normal) {
    if (!ENABLE_SHADOWS) return false;

    Vector3 toLight = lightPos - point;
    float distanceToLight = toLight.length();
    Vector3 lightDir = toLight.normalized();

    // Cria raio de sombra com offset para evitar "shadow acne"
    Ray shadowRay(point + normal * SHADOW_BIAS, lightDir);

    // Testa interseção com objetos principais
    // Se intersecta antes de chegar na luz, está na sombra
    if (intersectBox(shadowRay, altarMin, altarMax, shadowHit)) {
        if (shadowHit.t > 0.0f && shadowHit.t < distanceToLight) {
            return true;  // Na sombra!
        }
    }

    // ... testa outros objetos (bancos, ostensório, vela)

    return false;  // Não está na sombra
}
```

### **Aplicação no Phong:**
```
Linhas: 565-571

for (const auto& light : lights) {
    Vector3 lightDir = (light.position - point).normalized();

    // Verifica se está na sombra
    bool inShadow = isInShadow(point, light.position, normal);
    float shadowFactor = inShadow ? SHADOW_INTENSITY : 1.0f;

    // Aplica fator de sombra na iluminação
    Color diffuse = baseColor * light.intensity * diff * shadowFactor;
    Color specular = light.intensity * spec * 0.5f * shadowFactor;

    result = result + diffuse + specular;
}
```

### **Para demonstrar - Desligar sombras:**
```cpp
// src/interactive_opengl.cpp linha 110
const bool ENABLE_SHADOWS = false;        // ← ALTERE AQUI

// Recompile: make clean && make
// Compare: com e sem sombras
```

### **Para demonstrar - Sombras mais escuras:**
```cpp
// src/interactive_opengl.cpp linha 120
const float SHADOW_INTENSITY = 0.1f;      // ← ALTERE AQUI
// 0.1 = apenas 10% da luz chega (sombra 90% escura)

// Recompile: make clean && make
```

---

## 📊 RESUMO RÁPIDO - LOCALIZAÇÃO NO CÓDIGO

```
src/interactive_opengl.cpp
├── Linhas 21-135   ⚙️  SEÇÃO DE CONFIGURAÇÕES
│   ├── 34-56       📷  Câmera (position, lookAt, up, FOV)
│   ├── 64-75       🔄  Transformações (translação, rotação)
│   ├── 80-97       💡  Iluminação (3 luzes)
│   ├── 102-108     ✨  Emissividade (6 objetos)
│   ├── 110-120     🌑  Sombras (shadow rays)
│   └── 119-123     📐  Dimensões (capela)
│
├── Linhas 400-475  🌑  Função isInShadow (shadow rays)
├── Linhas 539-577  💡  Função phongShading (iluminação)
├── Linhas 801-816  🔄  Aplicação de transformações (altar)
└── Linhas 1073-1077 💡  Criação das luzes

include/Matrix4x4.h
├── Linhas 70-76    📍  Matrix4x4::translation()
├── Linhas 110-119  🔄  Matrix4x4::rotationY()
└── Linhas 136-159  🔄  Matrix4x4::rotation() (arbitrária)

src/projection_demo.cpp
├── Linhas 59-66    📐  Projeção Perspectiva
├── Linhas 68-75    📐  Projeção Ortográfica
└── Linhas 77-94    📐  Projeção Oblíqua (Cavalier + Cabinet)
```

---

## 🎯 DICA FINAL

**Tenha este arquivo aberto durante a apresentação!**

Para cada pergunta:
1. Leia a resposta
2. Mostre a linha de código correspondente
3. Se for alterar, use os exemplos fornecidos
4. Explique o que está fazendo

**Boa sorte! 🍀**
