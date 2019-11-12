#include "texture.h"

using namespace std;

/** Constructors **/
Texture::Texture(){
  width = 0; height = 0;
  filename = NULL;
  textures = NULL;
}

Texture::Texture(char *fn) {
  width = 0; height = 0;
  filename = fn;
  textures = NULL;
}

Texture::~Texture(){}

// Return max power of 2 <= x
int Texture::allowedSize(int x) {
  int r = 1;
	while(r < x) r=(r<<1);
	if(r==x) return r;
	else return r>>1;
}

// Read the binary ppm file and store byte information in textures[][]
void Texture::readImage() {
  int w, h, max;
  int i, j;
  char ch;
  FILE *fp;
  unsigned char tmp[3];
  
  fp = fopen(filename,"rb");
  if (fp == NULL) {printf("texture file not found.\n"); exit(-1);}
  fscanf(fp, "P%c\n", &ch);
  if (ch != '6'){
    printf("invalid binary ppm file\n");
    exit(-1);
  } else {
    ch = getc(fp);
    while (ch == '#') {
      do { ch = getc(fp); } while (ch != '\n');
      ch = getc(fp);
    }
    ungetc(ch, fp);
    fscanf(fp,"%d",&w);
    fscanf(fp,"%d",&h);
    fscanf(fp,"%d",&max);
    width = allowedSize(w);
    height = allowedSize(h);
    
    textures = (Vec **)malloc(width*sizeof(Vec *));
    for (i=0; i<width; i++) textures[i] = (Vec *)malloc(height*sizeof(Vec));
    
    for (i=0; i<width; i++) {
      for (j=0; j<height; j++){
        fread(tmp, sizeof(unsigned char), 3, fp);
        textures[i][j].x = tmp[1];
        textures[i][j].y = tmp[2];
        textures[i][j].z = tmp[0];
      }
    }
  }
  
  fclose(fp);
}

// print color information
void Texture::print() {
  int i, j;
  printf("width = %d, height = %d\n", width, height);
  for (i=0; i<width; i++) {
    for (j=0; j<height; j++){
      printf("textures[%d][%d]: ", i, j);
      textures[i][j].print();
    }
  }
}
