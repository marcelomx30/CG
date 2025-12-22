# 🏛️ CENA DA CAPELA - Documentação

## 📋 Sobre a Cena

Esta é uma cena especial de uma **capela religiosa** com iluminação realista:

- ✨ **Luz do sol** entrando pelas janelas laterais (luz direcional)
- 🕯️ **Luz vermelha** da vela ao lado do altar (luz pontual)
- ⛪ **Altar** com ostensório dourado brilhante
- 🪑 **Bancos** de madeira dispostos em fileiras
- 🪟 **Janelas** laterais altas
- 🎨 **Materiais** realistas (madeira, ouro, vidro)

---

## 🚀 Como Renderizar

### Opção 1: Usando o executável direto

```bash
cd CG_CPP

# Compilar (se ainda não compilou)
make

# Executar
./capela
```

### Opção 2: Usando o Makefile

```bash
make run-capela
```

**Tempo de renderização**: ~5-8 minutos (resolução 800x600)

---

## 🎨 Elementos da Cena

### 1. Estrutura

| Elemento | Descrição |
|----------|-----------|
| **Dimensões** | 12m largura × 8m altura × 20m profundidade |
| **Chão** | Madeira clara com brilho suave |
| **Paredes** | Bege claro (cor de capela) |
| **Teto** | Mesmo material das paredes |

### 2. Altar

- **Posição**: Centralizado na frente da capela
- **Material**: Madeira clara polida
- **Dimensões**: 3m × 1.2m × 1m
- **Ostensório**: Esfera dourada brilhante no topo
  - Raios dourados irradiando (8 cilindros)
  - Material com alto shininess (80)

### 3. Bancos

- **Quantidade**: 6 bancos (3 fileiras de cada lado)
- **Material**: Madeira escura
- **Disposição**: Corredor central livre
- **Dimensões**: 1m × 0.5m × 3m cada

### 4. Janelas

- **Posição**: Laterais altas (5m de altura)
- **Simuladas** com esferas translúcidas azuladas
- **Função**: Indicam de onde vem a luz do sol

### 5. Vela Vermelha

- **Posição**: Ao lado direito do altar
- **Suporte**: Cilindro de madeira (1.2m altura)
- **Chama**: Esfera vermelha brilhante
- **Luz emitida**: Vermelha intensa

---

## 💡 Sistema de Iluminação

### 1. Luz Ambiente
```cpp
Color(0.25, 0.25, 0.28)  // Suave e azulada
```
Iluminação base da capela.

### 2. Luz do Sol (Direcional 1)
```cpp
Direção: Vector3(-0.3, -0.6, 0.2)
Cor: Color(0.9, 0.85, 0.7)  // Amarelada
```
Simula raios de sol entrando pela janela esquerda.

### 3. Luz do Sol (Direcional 2)
```cpp
Direção: Vector3(0.3, -0.6, 0.2)
Cor: Color(0.6, 0.55, 0.45)  // Mais suave
```
Simula raios de sol entrando pela janela direita.

### 4. Luz da Vela (Pontual Vermelha)
```cpp
Posição: Vector3(8, 1.3, 16.5)
Cor: Color(1.2, 0.15, 0.1)  // Vermelho intenso
```
Luz vermelha concentrada ao lado do altar.

### 5. Luz Geral do Altar
```cpp
Posição: Vector3(6, 6, 17)
Cor: Color(0.4, 0.4, 0.45)
```
Ilumina suavemente a área do altar.

---

## 🎥 Câmera

**Posição**: Entrada da capela
```cpp
Eye: Vector3(6, 2, 1)      // Na entrada, altura dos olhos
At: Vector3(6, 2, 17)      // Olhando para o altar
Up: Vector3(0, 1, 0)       // Orientação vertical
```

**Perspectiva**: Vista frontal central
- Ângulo perfeito para ver todo o altar
- Bancos nas laterais
- Profundidade da capela

**Resolução**: 800×600 pixels
- Maior que o padrão (500×500)
- Mais detalhes visíveis
- Proporção widescreen

---

## 🎨 Materiais Utilizados

### 1. Madeira dos Bancos
```cpp
Ambiente: Color(0.15, 0.10, 0.05)   // Escuro
Difuso: Color(0.45, 0.30, 0.15)
Especular: Color(0.3, 0.2, 0.1)
Shininess: 20
```

### 2. Madeira do Altar
```cpp
Ambiente: Color(0.25, 0.20, 0.15)   // Mais claro
Difuso: Color(0.65, 0.55, 0.45)
Especular: Color(0.4, 0.3, 0.2)
Shininess: 30
```

### 3. Ouro do Ostensório
```cpp
Ambiente: Color(0.3, 0.25, 0.0)
Difuso: Color(0.9, 0.75, 0.2)       // Dourado
Especular: Color(1.0, 0.95, 0.6)    // Brilho intenso
Shininess: 80  // Muito brilhante!
```

### 4. Paredes (Bege)
```cpp
Ambiente: Color(0.35, 0.33, 0.30)
Difuso: Color(0.85, 0.82, 0.78)     // Bege claro
Especular: Color(0.2, 0.2, 0.2)
Shininess: 10
```

### 5. Chão (Madeira Clara)
```cpp
Ambiente: Color(0.25, 0.20, 0.15)
Difuso: Color(0.60, 0.50, 0.40)
Especular: Color(0.25, 0.20, 0.15)
Shininess: 15
```

### 6. Janelas (Vidro Azulado)
```cpp
Ambiente: Color(0.4, 0.5, 0.6)
Difuso: Color(0.6, 0.7, 0.8)        // Azul claro
Especular: Color(0.8, 0.9, 1.0)
Shininess: 50
```

### 7. Vela (Vermelho Emissor)
```cpp
Ambiente: Color(0.3, 0.05, 0.05)
Difuso: Color(0.9, 0.1, 0.1)        // Vermelho intenso
Especular: Color(1.0, 0.3, 0.3)
Shininess: 60
```

---

## 📸 Visualizando o Resultado

Após renderizar:

```bash
# Converter PPM para PNG
convert output/capela.ppm output/capela.png

# Visualizar
xdg-open output/capela.png
```

---

## 🎯 O que Você Verá na Imagem

1. **Entrada da Capela**
   - Visão da entrada olhando para o altar
   - Corredor central livre

2. **Bancos**
   - 3 fileiras de cada lado
   - Madeira escura
   - Sombras projetadas

3. **Altar**
   - Centralizado ao fundo
   - Madeira clara polida
   - Ostensório dourado brilhante no topo

4. **Iluminação**
   - **Luz do sol**: Feixes de luz entrando pelas janelas
   - **Luz vermelha**: Brilho vermelho ao lado do altar
   - **Sombras**: Realistas dos objetos

5. **Atmosfera**
   - Ambiente tranquilo e sagrado
   - Contraste entre luz quente (sol) e fria (ambiente)
   - Destaque no ostensório dourado

---

## 💡 Efeitos Especiais Implementados

### 1. Luz Direcional Múltipla
Dois feixes de luz solar de ângulos diferentes criam:
- Iluminação mais natural
- Sombras suaves
- Volume na cena

### 2. Luz Pontual Colorida
A vela vermelha cria:
- Ponto focal lateral
- Atmosfera mística
- Contraste de temperatura de cor

### 3. Materiais Realistas
- **Ouro**: Alto brilho especular (shininess 80)
- **Madeira**: Brilho médio natural
- **Vidro**: Translúcido com reflexos

### 4. Geometria Complexa
- Ostensório com 8 raios radiais
- 6 bancos modelados como malhas
- Estrutura completa da capela

---

## 🎓 Para a Apresentação

### Destaque estes pontos:

1. **Coerência Temática** ⭐
   - Capela religiosa completa
   - Todos elementos fazem sentido

2. **Iluminação Avançada** ⭐⭐
   - 2 tipos de luz diferentes:
     - Direcional (sol)
     - Pontual (vela)
   - Cores diferentes de luz
   - Efeito dramático

3. **Materiais Variados** ⭐
   - 7 materiais distintos
   - Ouro, madeira, vidro
   - Propriedades realistas

4. **Geometria** ⭐
   - Malhas complexas (bancos, altar)
   - Primitivas (esferas, cilindros)
   - Ostensório decorativo

5. **Sombras** ⭐
   - Calculadas por ray tracing
   - Realistas e suaves

---

## 🔧 Modificações Possíveis

Se quiser ajustar a cena, edite `src/capela.cpp`:

### Mudar intensidade do sol:
```cpp
// Linha ~240
Color(0.9, 0.85, 0.7)  // Mais claro
// ou
Color(0.5, 0.45, 0.35)  // Mais escuro
```

### Mudar cor da vela:
```cpp
// Linha ~266
Color(1.2, 0.15, 0.1)  // Vermelho
// ou
Color(0.1, 0.15, 1.2)  // Azul
```

### Mudar posição da câmera:
```cpp
// Linha ~283
Vector3(6, 2, 1)   // Eye - entrada
// ou
Vector3(6, 5, 10)  // Eye - visão aérea
```

---

## ✅ Requisitos Atendidos

- ✅ Coerência temática
- ✅ Primeiro octante (x, y, z > 0)
- ✅ Esfera (ostensório, janelas, vela)
- ✅ Cilindro (raios, suporte da vela)
- ✅ Malha (altar, bancos)
- ✅ 7 materiais distintos
- ✅ Transformações
- ✅ Luz direcional (+0.5)
- ✅ Luz pontual
- ✅ Luz ambiente
- ✅ Sombras
- ✅ Câmera perspectiva
- ✅ Resolução 800×600

---

## 🎉 Resultado Esperado

Uma bela cena de capela com:
- ✨ Luz dourada do sol
- 🕯️ Brilho vermelho da vela
- ⛪ Atmosfera sagrada e tranquila
- 🎨 Iluminação dramática e realista

**Perfeito para demonstrar capacidades avançadas de ray tracing!** 🚀
