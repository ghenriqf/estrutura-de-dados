#ifndef TAD_CAMERA_LISTA_CIRCULAR_H
#define TAD_CAMERA_LISTA_CIRCULAR_H

struct No
{
  int camera;
  No *proximo;
};

struct CameraListaCircular
{
  No *cabeca;
};

void inserirCamera(int valor, CameraListaCircular *lista);
bool removerCamera(int valor, CameraListaCircular *lista);
CameraListaCircular *inicializarListaCircular();

#endif