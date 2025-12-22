# 🎮 INTERFACE INTERATIVA - Guia de Uso

## 📋 Sobre

Este programa permite **parametrizar a cena** de forma interativa, conforme solicitado pelo professor! 

Você pode modificar:
- ✅ Posição da câmera (Eye, At)
- ✅ Posição das luzes (pontual, spot)
- ✅ Intensidade das luzes
- ✅ Posição dos objetos (esferas, cilindro, cone)
- ✅ Resolução da imagem
- ✅ Aplicar presets rápidos

---

## 🚀 Como Usar

### Compilar e Executar:

```bash
cd CG_CPP

# Compilar
make

# Executar interface interativa
./interactive
```

Ou diretamente:
```bash
make run-interactive
```

---

## 📱 Menu Principal

Ao executar, você verá:

```
========================================
   INTERFACE DE PARAMETRIZACAO
   Trabalho Final de CG
========================================

MENU PRINCIPAL:
1. Configurar Camera
2. Configurar Luzes
3. Configurar Objetos
4. Configurar Resolucao
5. Ver Configuracoes Atuais
6. Renderizar Cena
7. Presets Rapidos
0. Sair
```

---

## 🎥 1. Configurar Câmera

Permite modificar:
- **Eye**: Posição da câmera (x, y, z)
- **At**: Ponto para onde a câmera olha (x, y, z)

**Exemplo:**
```
Nova posicao Eye:
  x: 10
  y: 5
  z: -3
```

---

## 💡 2. Configurar Luzes

Você pode modificar 3 luzes:

### Luz Pontual 1
- Posição (x, y, z)
- Intensidade RGB (valores 0-1)

### Luz Pontual 2
- Posição (x, y, z)
- Intensidade RGB (valores 0-1)

### Luz Spot
- Posição (x, y, z)
- Direção (x, y, z)

**Exemplo:**
```
Nova posicao da Luz Pontual 1:
  x: 5
  y: 7
  z: 3

Intensidade (R G B, valores 0-1):
  R: 1.0
  G: 0.8
  B: 0.6
```

---

## 🎯 3. Configurar Objetos

Permite mover 5 objetos:
1. **Esfera Vermelha Principal**
2. **Esfera Pequena**
3. **Esfera Azul**
4. **Cilindro**
5. **Cone**

**Exemplo:**
```
Escolha um objeto: 1

Nova posicao do(a) Esfera Vermelha:
  x: 4
  y: 2
  z: 5
```

---

## 📐 4. Configurar Resolução

Presets disponíveis:
- **Teste rápido**: 200x200 (renderiza em ~30 segundos)
- **Média qualidade**: 400x400 (renderiza em ~2 minutos)
- **Alta qualidade**: 500x500 (renderiza em ~3 minutos) ← PADRÃO
- **Extra**: 800x800 (renderiza em ~8 minutos)
- **Personalizado**: Digite sua própria resolução

---

## 👀 5. Ver Configurações Atuais

Mostra um resumo de todas as configurações:
```
========================================
   CONFIGURACOES ATUAIS
========================================

CAMERA:
  Eye: Vector3(12, 4, -2)
  At: Vector3(5, 2, 5)
  Up: Vector3(0, 1, 0)

LUZES:
  Luz Pontual 1:
    Posicao: Vector3(5, 6, 3)
    Intensidade: RGB(0.8, 0.8, 0.8)
  ...

OBJETOS:
  Esfera Principal: Vector3(3, 2.5, 5)
  ...
```

---

## 🎨 6. Renderizar Cena

Gera a imagem com as configurações atuais!

**Saída**: `output/cena_parametrizada.ppm`

Após renderizar:
```bash
# Converter para PNG
convert output/cena_parametrizada.ppm output/cena_parametrizada.png
```

---

## ⚡ 7. Presets Rápidos

Configurações pré-definidas para testar rapidamente:

### 1. Visão Frontal (1 ponto de fuga)
```
Eye: (5, 4, -2)
At: (5, 4, 5)
```
Câmera frontal, paralela ao chão.

### 2. Visão de Canto (2 pontos de fuga)
```
Eye: (12, 4, -2)
At: (5, 2, 5)
```
Câmera no canto, ângulo oblíquo (PADRÃO).

### 3. Visão Aérea (3 pontos de fuga)
```
Eye: (12, 10, -2)
At: (5, 0, 5)
```
Câmera alta, olhando para baixo.

### 4. Iluminação Dramática
Aumenta contraste das luzes:
- Luz principal muito forte
- Luz secundária fraca
- Spot intenso

### 5. Iluminação Suave
Luzes balanceadas e suaves:
- Todas as luzes com intensidade média

### 6. Objetos Centralizados
Move todos os objetos para perto do centro da sala.

---

## 💡 Fluxo de Trabalho Recomendado

### Para Demonstração na Apresentação:

1. **Execute o programa**
   ```bash
   ./interactive
   ```

2. **Mostre as configurações atuais** (opção 5)
   - Mostre os valores padrão

3. **Aplique um preset** (opção 7)
   - Exemplo: "Visão Frontal"
   - Mostre como mudou

4. **Modifique uma luz** (opção 2)
   - Mova a Luz Pontual 1 para nova posição
   - Mostre como parametrizar

5. **Modifique um objeto** (opção 3)
   - Mova a Esfera Principal
   - Demonstre interatividade

6. **Renderize** (opção 6)
   - Gere a imagem com as mudanças
   - Mostre o resultado

7. **Compare**
   - Mostre a diferença entre renders

---

## 🎯 Exemplos de Uso

### Exemplo 1: Criar Iluminação Noturna

```
1. Execute: ./interactive
2. Menu: 2 (Configurar Luzes)
3. Escolha: 1 (Luz Pontual 1)
4. Intensidade:
   R: 0.3
   G: 0.3
   B: 0.5
5. Menu: 6 (Renderizar)
```

### Exemplo 2: Close-up em Objeto

```
1. Execute: ./interactive
2. Menu: 1 (Configurar Camera)
3. Eye:
   x: 4
   y: 2.5
   z: 3
4. At:
   x: 3
   y: 2.5
   z: 5
5. Menu: 6 (Renderizar)
```

### Exemplo 3: Teste Rápido

```
1. Execute: ./interactive
2. Menu: 4 (Resolução)
3. Escolha: 1 (200x200)
4. Menu: 7 (Presets)
5. Escolha: 4 (Iluminação Dramática)
6. Menu: 6 (Renderizar)
```

---

## 📸 Comparando Resultados

Você pode gerar múltiplas imagens e comparar:

```bash
# Renderizar com configuração 1
./interactive
# (fazer mudanças, renderizar)
mv output/cena_parametrizada.ppm output/config1.ppm

# Renderizar com configuração 2
./interactive
# (fazer outras mudanças, renderizar)
mv output/cena_parametrizada.ppm output/config2.ppm

# Converter ambas
convert output/config1.ppm output/config1.png
convert output/config2.ppm output/config2.png
```

---

## ⌨️ Dicas de Uso

1. **Valores razoáveis para posições**:
   - A sala vai de 0 a 10 em x e z
   - A altura vai de 0 a 8 em y
   - Mantenha objetos dentro desses limites

2. **Intensidade de luz**:
   - Valores 0.0 a 1.0 são normais
   - Valores > 1.0 criam overexposure (efeito dramático)
   - Valores < 0.3 criam cena escura

3. **Resolução**:
   - Use 200x200 para testes rápidos
   - Use 500x500 para apresentação final

4. **Presets são seu amigo**:
   - Comece com um preset
   - Ajuste detalhes depois

---

## 🎓 Para a Apresentação

**Demonstre parametrização assim:**

1. **Mostre o programa rodando**
   ```bash
   ./interactive
   ```

2. **Explique o menu**
   - "Aqui posso modificar câmera, luzes e objetos"

3. **Faça uma mudança ao vivo**
   - Mude posição de uma luz
   - Renderize
   - Mostre a diferença

4. **Explique a flexibilidade**
   - "Posso testar diferentes configurações sem recompilar"
   - "Isso atende o requisito de parametrização"

---

## ✅ Vantagens desta Implementação

- ✅ **Sem recompilação**: Muda parâmetros sem recompilar código
- ✅ **Interface intuitiva**: Menu simples de usar
- ✅ **Presets rápidos**: Testa configurações comuns rapidamente
- ✅ **Visualização clara**: Ver todas as configurações de uma vez
- ✅ **Múltiplas renderizações**: Gera várias imagens com configs diferentes

---

## 🚀 Comandos Rápidos

```bash
# Compilar
make

# Executar versão normal (cena pré-definida)
./raycaster

# Executar versão interativa (parametrizável)
./interactive

# Ou use shortcuts do Makefile
make run              # versão normal
make run-interactive  # versão interativa
```

---

**Pronto! Agora você tem uma interface completa para parametrizar a cena! 🎉**
