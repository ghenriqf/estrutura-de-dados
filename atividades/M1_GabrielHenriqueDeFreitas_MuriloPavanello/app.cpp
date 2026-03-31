#include "./Sensor/TAD_SensoresListaEstatica.h"
#include "./Carga/TAD_CargaListaEncadeada.h"
#include "./Nave/TAD_NaveListaDuplamenteEncadeada.h"
#include "./Camera/TAD_CameraListaCircular.h"
#include "./Log/TAD_LogPilha.h"
#include "./Hangar/TAD_HangarFila.h"
#include <iostream>
#include "raylib.h"     
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>

const int SW = 900;
const int SH = 600;

const Color FUNDO = {20, 20, 35, 255};
const Color CAIXA = {35, 35, 60, 255};
const Color BORDA = {80, 160, 255, 255};
const Color TEXTO = {220, 220, 255, 255};
const Color DIMM = {100, 100, 140, 255};
const Color VERDE = {60, 200, 100, 255};
const Color VERMELHO = {220, 60, 60, 255};
const Color AMARELO = {240, 200, 50, 255};

enum Tela
{
  MENU = 0,
  TELA_SENSOR,
  TELA_CARGA,
  TELA_NAVE,
  TELA_CAMERA,
  TELA_LOG,
  TELA_HANGAR
};

enum Modo
{
  MODO_NENHUM,
  MODO_INSERIR,
  MODO_REMOVER
};

struct Status
{
  std::string msg = "Use as setas e ENTER para navegar.";
  Color cor = DIMM;
  float timer = 0;

  void set(const char *m, Color c = VERDE)
  {
    msg = m;
    cor = c;
    timer = 3.5f;
  }

  void update(float dt)
  {
    if (timer > 0)
    {
      timer -= dt;
      if (timer <= 0)
        msg = "";
    }
  }
};

struct Campo
{
  char buf[32] = {};
  int len = 0;
  bool ativo = false;

  void ativar()
  {
    ativo = true;
    len = 0;
    buf[0] = '\0';
  }
  void limpar()
  {
    ativo = false;
    len = 0;
    buf[0] = '\0';
  }

  void handle()
  {
    if (!ativo)
      return;
    if (IsKeyPressed(KEY_BACKSPACE) && len > 0)
      buf[--len] = '\0';
    int k = GetCharPressed();
    while (k > 0)
    {
      if (k >= 32 && len < 30)
      {
        buf[len++] = (char)k;
        buf[len] = '\0';
      }
      k = GetCharPressed();
    }
  }

  bool toInt(int &out) const
  {
    if (len == 0)
      return false;
    char *end;
    out = (int)strtol(buf, &end, 10);
    return end != buf && *end == '\0';
  }

  std::string str() const { return std::string(buf); }
};

static void drawCentrado(const char *txt, int y, int tam, Color c)
{
  DrawText(txt, (SW - MeasureText(txt, tam)) / 2, y, tam, c);
}

static void drawNo(int x, int y, int w, int h, const char *label, Color borda)
{
  DrawRectangle(x, y, w, h, CAIXA);
  DrawRectangleLines(x, y, w, h, borda);
  int tw = MeasureText(label, 16);
  DrawText(label, x + (w - tw) / 2, y + (h - 16) / 2, 16, TEXTO);
}

static void drawSetaDir(int x, int y, Color c)
{
  DrawLine(x, y, x + 24, y, c);
  DrawTriangle({(float)x + 24, (float)y - 5}, {(float)x + 24, (float)y + 5}, {(float)x + 32, (float)y}, c);
}

static void drawStatus(const Status &s)
{
  DrawRectangle(0, SH - 36, SW, 36, {10, 10, 20, 255});
  DrawLine(0, SH - 36, SW, SH - 36, DIMM);
  if (!s.msg.empty())
    DrawText(s.msg.c_str(), 16, SH - 24, 16, s.cor);
}

static void drawCampo(int x, int y, const Campo &c, const char *dica)
{
  DrawText(dica, x, y - 20, 15, DIMM);
  DrawRectangle(x, y, 260, 32, CAIXA);
  DrawRectangleLines(x, y, 260, 32, c.ativo ? BORDA : DIMM);
  DrawText(c.buf, x + 8, y + 8, 16, TEXTO);
  if (c.ativo && (int)(GetTime() * 2) % 2 == 0)
  {
    int cx = x + 8 + MeasureText(c.buf, 16);
    DrawLine(cx, y + 5, cx, y + 27, BORDA);
  }
}

static void drawHint(int x, int y, const char *key, const char *desc)
{
  char tmp[64];
  snprintf(tmp, sizeof(tmp), "[%s] %s", key, desc);
  DrawText(tmp, x, y, 15, DIMM);
}

static void drawCabecalho(const char *titulo, const char *estrutura)
{
  drawCentrado(titulo, 16, 20, BORDA);
  drawCentrado(estrutura, 42, 14, DIMM);
  DrawLine(20, 62, SW - 20, 62, DIMM);
}

static const char *MENU_ITENS[] = {
    "1. Sensores        (Lista Estatica)",
    "2. Cargas          (Lista Encadeada)",
    "3. Naves           (Lista Duplamente Encadeada)",
    "4. Cameras         (Lista Circular)",
    "5. Logs            (Pilha / Stack)",
    "6. Hangar          (Fila / Queue)"};

static void updateMenu(int &sel, Tela &tela)
{
  if (IsKeyPressed(KEY_UP))
    sel = (sel - 1 + 6) % 6;
  if (IsKeyPressed(KEY_DOWN))
    sel = (sel + 1) % 6;
  if (IsKeyPressed(KEY_ENTER))
    tela = (Tela)(TELA_SENSOR + sel);
  for (int i = 0; i < 6; i++)
    if (IsKeyPressed(KEY_ONE + i))
      tela = (Tela)(TELA_SENSOR + i);
}

static void drawMenu(int sel)
{
  drawCentrado("=== SIMULADOR DE LOGISTICA ESTELAR ===", 30, 22, BORDA);
  drawCentrado("Selecione um modulo", 60, 16, DIMM);
  DrawLine(80, 84, SW - 80, 84, DIMM);

  for (int i = 0; i < 6; i++)
  {
    int y = 100 + i * 62;
    bool cur = (i == sel);
    Color bg = cur ? Color{30, 50, 90, 255} : CAIXA;
    Color bd = cur ? BORDA : DIMM;
    DrawRectangle(80, y, SW - 160, 52, bg);
    DrawRectangleLines(80, y, SW - 160, 52, bd);
    DrawText(cur ? "> " : "  ", 90, y + 16, 18, BORDA);
    DrawText(MENU_ITENS[i], 116, y + 16, 18, cur ? TEXTO : DIMM);
  }

  drawHint(80, 480, "Setas", "navegar");
  drawHint(220, 480, "ENTER ou 1-6", "entrar");
}

static void drawSensores(SensoresListaEstatica *lista, const Campo &campo,
                         bool digitando, Modo modo)
{
  drawCabecalho("SENSORES", "Lista Estatica (array fixo de int)");
  drawHint(20, 70, "I", "inserir");
  drawHint(110, 70, "R", "remover");
  drawHint(210, 70, "ESC", "voltar");

  if (digitando)
  {
    const char *dica = (modo == MODO_INSERIR) ? "Valor a inserir (int):"
                                              : "Valor a remover (int):";
    drawCampo(20, 100, campo, dica);
  }

  // Caixas do array
  int boxW = 80, boxH = 54;
  int totalW = CAPACIDADE * boxW + (CAPACIDADE - 1) * 10;
  int sx = (SW - totalW) / 2;
  int sy = 200;

  DrawText("indice:", sx - 64, sy + 4, 14, DIMM);
  DrawText("valor:", sx - 64, sy + 26, 14, DIMM);

  for (int i = 0; i < CAPACIDADE; i++)
  {
    int x = sx + i * (boxW + 10);
    bool cheio = (i < lista->quantidadeElementos);
    Color borda = cheio ? VERDE : DIMM;

    DrawRectangle(x, sy, boxW, boxH, CAIXA);
    DrawRectangleLines(x, sy, boxW, boxH, borda);

    // índice no topo
    char idx[8];
    snprintf(idx, sizeof(idx), "[%d]", i);
    DrawText(idx, x + 4, sy + 4, 13, DIMM);

    // valor
    if (cheio)
    {
      char val[16];
      snprintf(val, sizeof(val), "%d", lista->sensores[i]);
      DrawText(val, x + (boxW - MeasureText(val, 18)) / 2, sy + 24, 18, TEXTO);
    }
    else
    {
      DrawText("-", x + boxW / 2 - 5, sy + 24, 18, DIMM);
    }
  }

  char info[64];
  snprintf(info, sizeof(info), "Ocupados: %d / %d slots", lista->quantidadeElementos, CAPACIDADE);
  DrawText(info, sx, sy + 70, 15, DIMM);

  // barra de uso
  int barW = totalW;
  DrawRectangle(sx, sy + 92, barW, 10, CAIXA);
  int fill = (CAPACIDADE > 0) ? (lista->quantidadeElementos * barW / CAPACIDADE) : 0;
  DrawRectangle(sx, sy + 92, fill, 10, VERDE);
  DrawRectangleLines(sx, sy + 92, barW, 10, DIMM);
}

static int contarCargas(CargaListaEncadeada *l)
{
  int n = 0;
  NoCarga *p = l->cabeca;
  while (p)
  {
    n++;
    p = p->proximo;
  }
  return n;
}

static void drawCargas(CargaListaEncadeada *lista, const Campo &campo,
                       bool digitando, Modo modo)
{
  drawCabecalho("CARGAS", "Lista Simplesmente Encadeada (int)");
  drawHint(20, 70, "I", "inserir");
  drawHint(110, 70, "R", "remover");
  drawHint(210, 70, "ESC", "voltar");

  if (digitando)
  {
    const char *dica = (modo == MODO_INSERIR) ? "Valor a inserir (int):" : "Valor a remover (int):";
    drawCampo(20, 100, campo, dica);
  }

  int nodeW = 74, nodeH = 50, gap = 36;
  int x = 30, y = 220;

  DrawText("HEAD", x, y + 16, 14, DIMM);
  x += 56;

  NoCarga *p = lista->cabeca;
  if (!p)
  {
    DrawText("-> [ lista vazia ]", x, y + 16, 16, DIMM);
    return;
  }

  while (p)
  {
    // seta →
    DrawLine(x, y + nodeH / 2, x + 28, y + nodeH / 2, BORDA);
    DrawTriangle({(float)x + 28, (float)y + nodeH / 2 - 5},
                 {(float)x + 28, (float)y + nodeH / 2 + 5},
                 {(float)x + 36, (float)y + nodeH / 2}, BORDA);
    x += 38;

    char val[16];
    snprintf(val, sizeof(val), "%d", p->carga);
    drawNo(x, y, nodeW, nodeH, val, BORDA);
    x += nodeW + 4;
    p = p->proximo;

    // quebra de linha se passar da borda
    if (x + nodeW + gap > SW - 20)
    {
      x = 30;
      y += nodeH + 40;
    }
  }

  // NULL final
  DrawLine(x, y + nodeH / 2, x + 28, y + nodeH / 2, DIMM);
  DrawText("NULL", x + 32, y + nodeH / 2 - 8, 15, DIMM);

  char info[32];
  snprintf(info, sizeof(info), "Total de nos: %d", contarCargas(lista));
  DrawText(info, 30, 420, 15, DIMM);
}

static int contarNaves(NaveListaDuplamenteEncadeada *l)
{
  int n = 0;
  NoNave *p = l->cabeca;
  while (p)
  {
    n++;
    p = p->proximo;
  }
  return n;
}

static void drawNaves(NaveListaDuplamenteEncadeada *lista, const Campo &campo,
                      bool digitando, Modo modo)
{
  drawCabecalho("NAVES", "Lista Duplamente Encadeada (string)");
  drawHint(20, 70, "I", "inserir");
  drawHint(110, 70, "R", "remover");
  drawHint(210, 70, "ESC", "voltar");

  if (digitando)
  {
    const char *dica = (modo == MODO_INSERIR) ? "Nome da nave:" : "Nome a remover:";
    drawCampo(20, 100, campo, dica);
  }

  int nodeW = 100, nodeH = 52;
  int x = 20, y = 220;

  // NULL esquerdo
  DrawText("NULL", x, y + 18, 14, DIMM);
  x += 46;

  NoNave *p = lista->cabeca;
  if (!p)
  {
    DrawText("<-> [ lista vazia ]", x, y + 18, 16, DIMM);
    return;
  }

  while (p)
  {
    // seta dupla
    int ax = x;
    // →  (linha de cima)
    DrawLine(ax, y + nodeH / 2 - 7, ax + 28, y + nodeH / 2 - 7, AMARELO);
    DrawTriangle({(float)ax + 24, (float)y + nodeH / 2 - 12},
                 {(float)ax + 24, (float)y + nodeH / 2 - 2},
                 {(float)ax + 32, (float)y + nodeH / 2 - 7}, AMARELO);
    // ←  (linha de baixo)
    DrawLine(ax, y + nodeH / 2 + 7, ax + 28, y + nodeH / 2 + 7, DIMM);
    DrawTriangle({(float)ax + 8, (float)y + nodeH / 2 + 2},
                 {(float)ax + 8, (float)y + nodeH / 2 + 12},
                 {(float)ax, (float)y + nodeH / 2 + 7}, DIMM);
    x += 34;

    drawNo(x, y, nodeW, nodeH, p->nome.c_str(), AMARELO);
    x += nodeW + 4;
    p = p->proximo;

    if (x + nodeW + 40 > SW - 20)
    {
      x = 20;
      y += nodeH + 50;
    }
  }

  // NULL direito
  DrawLine(x, y + nodeH / 2, x + 28, y + nodeH / 2, DIMM);
  DrawText("NULL", x + 32, y + nodeH / 2 - 8, 14, DIMM);

  char info[32];
  snprintf(info, sizeof(info), "Total de naves: %d", contarNaves(lista));
  DrawText(info, 20, 430, 15, DIMM);
}

static int contarCameras(CameraListaCircular *l)
{
  if (!l->cabeca)
    return 0;
  int n = 1;
  NoCamera *p = l->cabeca->proximo;
  while (p && p != l->cabeca)
  {
    n++;
    p = p->proximo;
  }
  return n;
}

static void drawCameras(CameraListaCircular *lista, const Campo &campo,
                        bool digitando, Modo modo)
{
  drawCabecalho("CAMERAS", "Lista Circular (int) — ultimo no aponta para cabeca");
  drawHint(20, 70, "I", "inserir");
  drawHint(110, 70, "R", "remover");
  drawHint(210, 70, "ESC", "voltar");

  if (digitando)
  {
    const char *dica = (modo == MODO_INSERIR) ? "ID da camera (int):" : "ID a remover (int):";
    drawCampo(20, 100, campo, dica);
  }

  int n = contarCameras(lista);
  if (n == 0)
  {
    drawCentrado("[ lista circular vazia ]", 320, 18, DIMM);
    return;
  }

  int cx = SW / 2, cy = 340, raio = 160, nw = 64, nh = 38;
  float pi = 3.14159265f;

  NoCamera *p = lista->cabeca;
  for (int i = 0; i < n; i++)
  {
    float ang = (2 * pi * i / n) - pi / 2;
    float angProx = (2 * pi * ((i + 1) % n) / n) - pi / 2;

    int nx = cx + (int)(cosf(ang) * raio);
    int ny = cy + (int)(sinf(ang) * raio);
    int nx2 = cx + (int)(cosf(angProx) * raio);
    int ny2 = cy + (int)(sinf(angProx) * raio);

    // linha para próximo
    DrawLine(nx, ny, nx2, ny2, DIMM);

    // seta no meio do arco
    float mx = (nx + nx2) / 2.0f, my = (ny + ny2) / 2.0f;
    float dx = nx2 - nx, dy = ny2 - ny;
    float len = sqrtf(dx * dx + dy * dy);
    if (len > 0)
    {
      dx /= len;
      dy /= len;
    }
    DrawTriangle({mx + dx * 8 - dy * 5, my + dy * 8 + dx * 5},
                 {mx + dx * 8 + dy * 5, my + dy * 8 - dx * 5},
                 {mx + dx * 16, my + dy * 16}, DIMM);

    // caixa do nó
    Color borda = (i == 0) ? VERDE : BORDA;
    char val[16];
    snprintf(val, sizeof(val), "%d", p->camera);
    drawNo(nx - nw / 2, ny - nh / 2, nw, nh, val, borda);
    if (i == 0)
      DrawText("HEAD", nx - MeasureText("HEAD", 13) / 2, ny - nh / 2 - 18, 13, VERDE);

    p = p->proximo;
    if (p == lista->cabeca)
      break;
  }

  char info[32];
  snprintf(info, sizeof(info), "Total: %d cameras", n);
  DrawText(info, 20, 510, 15, DIMM);
}

static void drawLogs(LogPilha *pilha, const Campo &campo, bool digitando, Modo modo)
{
  drawCabecalho("LOGS", "Pilha / Stack (string)  —  LIFO");
  drawHint(20, 70, "P", "push");
  drawHint(100, 70, "O", "pop");
  drawHint(175, 70, "ESC", "voltar");

  if (digitando)
    drawCampo(20, 100, campo, "Mensagem de log:");

  // Coleta itens do topo para base
  std::vector<std::string> itens;
  NoPilha *p = pilha->topo;
  while (p)
  {
    itens.push_back(p->log);
    p = p->proximo;
  }

  int blockW = 320, blockH = 44, maxVis = 7;
  int x = (SW - blockW) / 2;
  int baseY = 470;

  // Plataforma base
  DrawRectangle(x - 8, baseY + blockH, blockW + 16, 8, DIMM);

  if (itens.empty())
  {
    DrawRectangle(x, baseY, blockW, blockH, CAIXA);
    DrawRectangleLines(x, baseY, blockW, blockH, DIMM);
    drawCentrado("[ pilha vazia ]", baseY + 14, 16, DIMM);
    return;
  }

  // Desenha da base para o topo
  for (int i = (int)itens.size() - 1; i >= 0 && (int)itens.size() - 1 - i < maxVis; i--)
  {
    int slot = (int)itens.size() - 1 - i; // 0 = mais antigo (base)
    int y = baseY - slot * (blockH + 2);
    bool eh_topo = (i == 0);

    Color bg = eh_topo ? Color{30, 55, 90, 255} : CAIXA;
    Color bord = eh_topo ? BORDA : DIMM;
    DrawRectangle(x, y, blockW, blockH, bg);
    DrawRectangleLines(x, y, blockW, blockH, bord);

    int tw = MeasureText(itens[i].c_str(), 16);
    DrawText(itens[i].c_str(), x + (blockW - tw) / 2, y + 14, 16, eh_topo ? TEXTO : DIMM);
    if (eh_topo)
      DrawText("<-- TOPO", x + blockW + 10, y + 14, 14, BORDA);
  }

  char info[32];
  snprintf(info, sizeof(info), "Tamanho: %d", (int)itens.size());
  DrawText(info, x, baseY + blockH + 20, 15, DIMM);
}

static int contarFila(HangarFila *f)
{
  int n = 0;
  NoHangar *p = f->frente;
  while (p)
  {
    n++;
    p = p->proximo;
  }
  return n;
}

static void drawHangar(HangarFila *fila, const Campo &campo, bool digitando, Modo modo)
{
  drawCabecalho("HANGAR", "Fila / Queue (int)  —  FIFO");
  drawHint(20, 70, "E", "enqueue");
  drawHint(120, 70, "D", "dequeue");
  drawHint(220, 70, "ESC", "voltar");

  if (digitando)
    drawCampo(20, 100, campo, "ID do shuttle (int):");

  int nodeW = 80, nodeH = 54;
  int y = 280;

  // Rótulos de entrada/saída
  DrawText("<-- sai (dequeue)", 20, y + nodeH + 10, 14, VERMELHO);
  DrawText("entra (enqueue) -->", SW - MeasureText("entra (enqueue) -->", 14) - 20,
           y + nodeH + 10, 14, VERDE);

  // Canal
  DrawRectangleLines(30, y - 8, SW - 60, nodeH + 16, DIMM);

  NoHangar *p = fila->frente;
  if (!p)
  {
    drawCentrado("[ fila vazia ]", y + 18, 18, DIMM);
    return;
  }

  int x = 40;
  bool primeiro = true;
  while (p && x + nodeW < SW - 50)
  {
    char val[16];
    snprintf(val, sizeof(val), "%d", p->valor);
    Color borda = primeiro ? VERDE : BORDA;
    drawNo(x, y, nodeW, nodeH, val, borda);
    if (primeiro)
    {
      DrawText("FRENTE", x + (nodeW - MeasureText("FRENTE", 12)) / 2, y - 18, 12, VERDE);
    }
    x += nodeW;
    if (p->proximo)
    {
      drawSetaDir(x + 2, y + nodeH / 2, DIMM);
      x += 38;
    }
    p = p->proximo;
    primeiro = false;
  }

  char info[32];
  snprintf(info, sizeof(info), "Shuttles na fila: %d", contarFila(fila));
  DrawText(info, 30, y + nodeH + 40, 15, DIMM);
}

int main()
{
  InitWindow(SW, SH, "Simulador de Logistica Estelar");
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);

  // Inicializa os TADs
  SensoresListaEstatica *sensores = inicializarListaEstatica();
  CargaListaEncadeada *cargas = inicializarListaEncadeada();
  NaveListaDuplamenteEncadeada *naves = inicializarListaDuplamenteEncadeada();
  CameraListaCircular *cameras = inicializarListaCircular();
  LogPilha *logs = inicializarPilha();
  HangarFila *hangar = inicializarFila();

  Tela tela = MENU;
  int menuSel = 0;
  Status status;
  Campo campo;
  bool digitando = false;
  Modo modo = MODO_NENHUM;

  while (!WindowShouldClose())
  {
    float dt = GetFrameTime();
    status.update(dt);
    campo.handle();

    // ESC: cancela campo ou volta ao menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
      if (digitando)
      {
        digitando = false;
        modo = MODO_NENHUM;
        campo.limpar();
      }
      else if (tela != MENU)
        tela = MENU;
    }

    if (tela == MENU)
    {
      updateMenu(menuSel, tela);
    }
    else if (!digitando)
    {
      // Teclas de ação disponíveis quando não está digitando
      switch (tela)
      {

      case TELA_SENSOR:
        if (IsKeyPressed(KEY_I))
        {
          modo = MODO_INSERIR;
          digitando = true;
          campo.ativar();
        }
        if (IsKeyPressed(KEY_R))
        {
          modo = MODO_REMOVER;
          digitando = true;
          campo.ativar();
        }
        break;

      case TELA_CARGA:
        if (IsKeyPressed(KEY_I))
        {
          modo = MODO_INSERIR;
          digitando = true;
          campo.ativar();
        }
        if (IsKeyPressed(KEY_R))
        {
          modo = MODO_REMOVER;
          digitando = true;
          campo.ativar();
        }
        break;

      case TELA_NAVE:
        if (IsKeyPressed(KEY_I))
        {
          modo = MODO_INSERIR;
          digitando = true;
          campo.ativar();
        }
        if (IsKeyPressed(KEY_R))
        {
          modo = MODO_REMOVER;
          digitando = true;
          campo.ativar();
        }
        break;

      case TELA_CAMERA:
        if (IsKeyPressed(KEY_I))
        {
          modo = MODO_INSERIR;
          digitando = true;
          campo.ativar();
        }
        if (IsKeyPressed(KEY_R))
        {
          modo = MODO_REMOVER;
          digitando = true;
          campo.ativar();
        }
        break;

      case TELA_LOG:
        if (IsKeyPressed(KEY_P))
        {
          modo = MODO_INSERIR;
          digitando = true;
          campo.ativar();
        }
        if (IsKeyPressed(KEY_O))
        {
          std::string rem = pop(logs);
          if (!rem.empty())
          {
            char buf[64];
            snprintf(buf, sizeof(buf), "POP: \"%s\"", rem.c_str());
            status.set(buf, VERDE);
          }
          else
            status.set("Pilha vazia!", VERMELHO);
        }
        break;

      case TELA_HANGAR:
        if (IsKeyPressed(KEY_E))
        {
          modo = MODO_INSERIR;
          digitando = true;
          campo.ativar();
        }
        if (IsKeyPressed(KEY_D))
        {
          if (hangar->frente)
          {
            dequeue(hangar);
            status.set("Shuttle saiu — DEQUEUE!", VERDE);
          }
          else
            status.set("Fila vazia!", VERMELHO);
        }
        break;

      default:
        break;
      }
    }
    else if (IsKeyPressed(KEY_ENTER))
    {
      // Confirma entrada
      int ival = 0;
      bool ok = false;

      switch (tela)
      {

      case TELA_SENSOR:
        if (campo.toInt(ival))
        {
          if (modo == MODO_INSERIR)
          {
            ok = inserirSensor(ival, sensores);
            status.set(ok ? "Sensor inserido!" : "Lista cheia!", ok ? VERDE : VERMELHO);
          }
          else
          {
            ok = removerSensor(ival, sensores);
            status.set(ok ? "Sensor removido!" : "Valor nao encontrado!", ok ? VERDE : VERMELHO);
          }
        }
        else
          status.set("Digite um numero inteiro valido.", VERMELHO);
        break;

      case TELA_CARGA:
        if (campo.toInt(ival))
        {
          if (modo == MODO_INSERIR)
          {
            inserirCarga(ival, cargas);
            status.set("Carga inserida!", VERDE);
          }
          else
          {
            ok = removerCarga(ival, cargas);
            status.set(ok ? "Carga removida!" : "Carga nao encontrada!", ok ? VERDE : VERMELHO);
          }
        }
        else
          status.set("Digite um numero inteiro valido.", VERMELHO);
        break;

      case TELA_NAVE:
        if (campo.len > 0)
        {
          if (modo == MODO_INSERIR)
          {
            inserirNave(campo.str(), naves);
            status.set("Nave inserida!", VERDE);
          }
          else
          {
            ok = removerNave(campo.str(), naves);
            status.set(ok ? "Nave removida!" : "Nave nao encontrada!", ok ? VERDE : VERMELHO);
          }
        }
        else
          status.set("Nome nao pode ser vazio.", VERMELHO);
        break;

      case TELA_CAMERA:
        if (campo.toInt(ival))
        {
          if (modo == MODO_INSERIR)
          {
            inserirCamera(ival, cameras);
            status.set("Camera inserida!", VERDE);
          }
          else
          {
            ok = removerCamera(ival, cameras);
            status.set(ok ? "Camera removida!" : "Camera nao encontrada!", ok ? VERDE : VERMELHO);
          }
        }
        else
          status.set("Digite um numero inteiro valido.", VERMELHO);
        break;

      case TELA_LOG:
        if (campo.len > 0)
        {
          push(campo.str(), logs);
          status.set("Log empilhado — PUSH!", VERDE);
        }
        else
          status.set("Mensagem nao pode ser vazia.", VERMELHO);
        break;

      case TELA_HANGAR:
        if (campo.toInt(ival))
        {
          enqueue(ival, hangar);
          status.set("Shuttle na fila — ENQUEUE!", VERDE);
        }
        else
          status.set("Digite um numero inteiro valido.", VERMELHO);
        break;

      default:
        break;
      }

      digitando = false;
      modo = MODO_NENHUM;
      campo.limpar();
    }

    BeginDrawing();
    ClearBackground(FUNDO);

    switch (tela)
    {
    case MENU:
      drawMenu(menuSel);
      break;
    case TELA_SENSOR:
      drawSensores(sensores, campo, digitando, modo);
      break;
    case TELA_CARGA:
      drawCargas(cargas, campo, digitando, modo);
      break;
    case TELA_NAVE:
      drawNaves(naves, campo, digitando, modo);
      break;
    case TELA_CAMERA:
      drawCameras(cameras, campo, digitando, modo);
      break;
    case TELA_LOG:
      drawLogs(logs, campo, digitando, modo);
      break;
    case TELA_HANGAR:
      drawHangar(hangar, campo, digitando, modo);
      break;
    }

    drawStatus(status);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}