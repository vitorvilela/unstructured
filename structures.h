#ifndef structuresH
#define structuresH

#include "uthash.h"

typedef struct vertex {
  
  long int id;
  int bndy;
  double x, y, g;
  
  UT_hash_handle hh;
  
} vertex_t;


typedef struct edge {
  
  long int id;
  int bndy;
  long int vertices[2];
  double vector[2];
  double normal[2];
  double flux[2];  
  long int volumes[2];
  double lenght;
    
  UT_hash_handle hh;
  
} edge_t;


typedef struct volume {
  
  long int id;
  double rho, area, gama, q;
  double phi[2], vel[2], rate[2], centroid[2];
  long int vertices[3];
  long int edges[3];
    
  UT_hash_handle hh;
  
} volume_t;


extern edge_t *hedge;

extern vertex_t *hvertex;

extern volume_t *hvolume;




#endif