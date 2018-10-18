#ifndef IMAGEM_H
#define IMAGEM_H


typedef struct{
  unsigned short imagic;
  unsigned short type;
  unsigned short dim;
  unsigned short sizeX, sizeY, sizeZ;
  char name[128];
  unsigned char *data;
} IMAGE;

IMAGE *ImageLoad(char *);

#endif // IMAGEM_H
