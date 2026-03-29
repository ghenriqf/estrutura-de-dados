#ifndef TAD_CAMERA_LISTA_CIRCULAR_H
#define TAD_CAMERA_LISTA_CIRCULAR_H

struct NoCamera
{
  int camera;
  NoCamera *proximo;
};

struct CameraListaCircular
{
  NoCamera *cabeca;
};

void inserirCamera(int valor, CameraListaCircular *lista);
bool removerCamera(int valor, CameraListaCircular *lista);
CameraListaCircular *inicializarListaCircular();

#endif