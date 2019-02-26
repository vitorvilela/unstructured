#include <stdio.h>
#include <math.h>
#include "uthash.h"
#include "structures.h"

void Print_VTK(const char *fname) {
  
  //Variables and pointers
  vertex_t *iter_vertex, *tmp_vertex;
  volume_t *iter_volume, *tmp_volume;
  int i;
  
  FILE *fptr;
  fptr = fopen(fname, "w");
  if(fptr == NULL)
    printf("\n\nError during file opening.\n\n");
   
  //Node coordinates
  int nvertex = HASH_COUNT(hvertex);
  int nvolume = HASH_COUNT(hvolume);
  
  fprintf(fptr, "# vtk DataFile Version 2.0\n");
  fprintf(fptr,"Written Unstructured Mesh\n");
  fprintf(fptr,"ASCII\n");
  fprintf(fptr,"DATASET UNSTRUCTURED_GRID\n");
  fprintf(fptr,"POINTS %i float\n", nvertex); 
  
  i = 0;
  HASH_ITER(hh, hvertex, iter_vertex, tmp_vertex) {    
    fprintf(fptr, "  %1.12e   %1.12e   %1.12e ", iter_vertex->x, iter_vertex->y, 0.0);
    i++;
    if((i % 3) == 0) 
      fprintf(fptr, "\n");
  } 
    
  fprintf(fptr, "\nCELLS %i %i\n", nvolume, nvolume*4);
  
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume)
    fprintf(fptr,"%i %i %i %i\n", 3, iter_volume->vertices[0]-1, iter_volume->vertices[1]-1, iter_volume->vertices[2]-1);

  
  fprintf(fptr, "CELL_TYPES %i\n", nvolume);
  for(i=0; i<nvolume; i++)
    fprintf(fptr, "%i\n", 5);
  
  fprintf(fptr, "CELL_DATA %i\n", nvolume);
  fprintf(fptr, "SCALARS Temperature float 1\n");
  fprintf(fptr, "LOOKUP_TABLE default\n"); 
  fprintf(fptr, "  ");
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume)
    fprintf(fptr, "%1.12e   ", iter_volume->phi[1]);
 
  fprintf(fptr,"\n\n\n");
    
  fclose(fptr);
  
}


void Print_K_VTK(const char *fname) {
  
  //Variables and pointers
  vertex_t *iter_vertex, *tmp_vertex;
  volume_t *iter_volume, *tmp_volume;
  int i;
  
  FILE *fptr;
  fptr = fopen(fname, "w");
  if(fptr == NULL)
    printf("\n\nError during file opening.\n\n");
   
  //Node coordinates
  int nvertex = HASH_COUNT(hvertex);
  int nvolume = HASH_COUNT(hvolume);
  
  fprintf(fptr, "# vtk DataFile Version 2.0\n");
  fprintf(fptr,"Written Unstructured Mesh\n");
  fprintf(fptr,"ASCII\n");
  fprintf(fptr,"DATASET UNSTRUCTURED_GRID\n");
  fprintf(fptr,"POINTS %i float\n", nvertex); 
  
  i = 0;
  HASH_ITER(hh, hvertex, iter_vertex, tmp_vertex) {    
    fprintf(fptr, "  %1.12e   %1.12e   %1.12e ", iter_vertex->x, iter_vertex->y, 0.0);
    i++;
    if((i % 3) == 0) 
      fprintf(fptr, "\n");
  } 
    
  fprintf(fptr, "\nCELLS %i %i\n", nvolume, nvolume*4);
  
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume)
    fprintf(fptr,"%i %i %i %i\n", 3, iter_volume->vertices[0]-1, iter_volume->vertices[1]-1, iter_volume->vertices[2]-1);

  
  fprintf(fptr, "CELL_TYPES %i\n", nvolume);
  for(i=0; i<nvolume; i++)
    fprintf(fptr, "%i\n", 5);
    
  fprintf(fptr, "\nCELL_DATA %i\n", nvolume);
  fprintf(fptr, "SCALARS Diffusivity float 1\n");
  fprintf(fptr, "LOOKUP_TABLE default\n"); 
  fprintf(fptr, "  ");
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume)
    fprintf(fptr, "%1.12e   ", iter_volume->gama);  
 
  fprintf(fptr,"\n\n\n");
    
  fclose(fptr);
  
}



void Print_Screen_Scalar(const double t) {
  
  //Function's variables
  volume_t *iter_volume, *tmp_volume;
  
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume)    
    printf("\nvolume->id: %ld\nvolume->phi: %lf\n", iter_volume->id, iter_volume->phi[1]);
  
  
  printf("\n");
  
}

void Print_Screen_Flux(const double t) {
  
  //Function's variables
  edge_t *iter_edge, *tmp_edge;
    
  HASH_ITER(hh, hedge, iter_edge, tmp_edge)    
    printf("\nedge->id: %ld\nedge->flux[1]: %lf\n", iter_edge->id, iter_edge->flux[1]);
    
  printf("\n");
  
}

void Print_Screen_Rate(const double t) {
  
  //Function's variables
  volume_t *iter_volume, *tmp_volume;
      
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume)     
    printf("\nvolume->id: %ld\nvolume->phi: %lf\n", iter_volume->id, iter_volume->rate[1]);
    
  printf("\n");
  
}


