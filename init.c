#include <stdio.h>
#include <math.h>
#include "uthash.h"
#include "structures.h"
#include "init.h"
#include "data.h"


void Edge_Geom() {
  
  //Function's variables
  long int id_vertex1, id_vertex2;
  double norm;
  vertex_t *ptr_vertex1, *ptr_vertex2;
  edge_t *iter_edge, *tmp_edge;
  
  //Set edges' geometric properties
  HASH_ITER(hh, hedge, iter_edge, tmp_edge) {
        
    id_vertex1 = iter_edge->vertices[0];
    id_vertex2 = iter_edge->vertices[1];    
    HASH_FIND(hh, hvertex, &id_vertex1, sizeof(long int), ptr_vertex1);
    HASH_FIND(hh, hvertex, &id_vertex2, sizeof(long int), ptr_vertex2);    
        
    iter_edge->vector[0] = ptr_vertex2->x - ptr_vertex1->x;
    iter_edge->vector[1] = ptr_vertex2->y - ptr_vertex1->y;
        
    norm = sqrt(pow(iter_edge->vector[0],2.0)+pow(iter_edge->vector[1],2.0));
    
    iter_edge->normal[0] = -iter_edge->vector[1]/norm;
    iter_edge->normal[1] = iter_edge->vector[0]/norm;
        
    ptr_vertex1 = NULL;
    ptr_vertex2 = NULL;
       
  }
  
}


void Edge_Vol_Assign() {
  
  //Function's variables  
  volume_t *iter_volume, *tmp_volume;
  edge_t *iter_edge, *tmp_edge;
  
  //Edge Volume Assignment
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume) {
    
    HASH_ITER(hh, hedge, iter_edge, tmp_edge) {
      
      if((iter_edge->volumes[0]==0) || (iter_edge->volumes[1] == 0)) {
	
	if( ( (iter_edge->vertices[0]==iter_volume->vertices[0]) || 
	      (iter_edge->vertices[0]==iter_volume->vertices[1]) ||
	      (iter_edge->vertices[0]==iter_volume->vertices[2]) ) &&
	    ( (iter_edge->vertices[1]==iter_volume->vertices[0]) || 
	      (iter_edge->vertices[1]==iter_volume->vertices[1]) ||
	      (iter_edge->vertices[1]==iter_volume->vertices[2]) ) 
	  ) {
	  
	  if(iter_edge->volumes[0] == 0) iter_edge->volumes[0] = iter_volume->id;
	  else iter_edge->volumes[1] = iter_volume->id;
	  
	  if(iter_volume->edges[0] == 0) iter_volume->edges[0] = iter_edge->id;
	  else if(iter_volume->edges[1] == 0) iter_volume->edges[1] = iter_edge->id;
	  else iter_volume->edges[2] = iter_edge->id;
	  
	}
	
      }  
      
    }    
      
  } 
  
}


void PlateCase_Gama_Init() {
  
  //Function's variables  
  long int id_vertex1, id_vertex2, id_vertex3;
  volume_t *iter_volume, *tmp_volume;
  vertex_t *ptr_vertex1, *ptr_vertex2, *ptr_vertex3;
  
  //Edge Volume Assignment
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume) {
  
    id_vertex1 = iter_volume->vertices[0];
    id_vertex2 = iter_volume->vertices[1];
    id_vertex3 = iter_volume->vertices[2];
    
    HASH_FIND(hh, hvertex, &id_vertex1, sizeof(long int), ptr_vertex1);
    HASH_FIND(hh, hvertex, &id_vertex2, sizeof(long int), ptr_vertex2);
    HASH_FIND(hh, hvertex, &id_vertex3, sizeof(long int), ptr_vertex3);
    
    if((ptr_vertex1->g) == (ptr_vertex2->g) == (ptr_vertex3->g))
      iter_volume->gama = ptr_vertex1->g;    
    else
      iter_volume->gama = min(ptr_vertex1->g, min(ptr_vertex2->g, ptr_vertex3->g));
           
  }
  
}


void Edge_Lenght_Init() {
  
  //Function's variables  
  edge_t *iter_edge, *tmp_edge;
  long int id_vertex1, id_vertex2;
  vertex_t *ptr_vertex1, *ptr_vertex2;
  double lx, ly;
  
  HASH_ITER(hh, hedge, iter_edge, tmp_edge) {
    
    id_vertex1 = iter_edge->vertices[0];
    id_vertex2 = iter_edge->vertices[1];   
    
    HASH_FIND(hh, hvertex, &id_vertex1, sizeof(long int), ptr_vertex1);
    HASH_FIND(hh, hvertex, &id_vertex2, sizeof(long int), ptr_vertex2);
    
    lx = fabs(ptr_vertex1->x - ptr_vertex2->x);
    ly = fabs(ptr_vertex1->y - ptr_vertex2->y);
    iter_edge->lenght = sqrt(lx*lx + ly*ly);
    
  }
  
}

void Volume_Area_Init() {
  
  //Function's variables  
  long int id_edge1, id_edge2, id_edge3;
  volume_t *iter_volume, *tmp_volume;
  edge_t *ptr_edge1, *ptr_edge2, *ptr_edge3;
  double l1, l2, l3, b, h;
  
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume) { 
    
    id_edge1 = iter_volume->edges[0];
    id_edge2 = iter_volume->edges[1];
    id_edge3 = iter_volume->edges[2];
    
    HASH_FIND(hh, hedge, &id_edge1, sizeof(long int), ptr_edge1);
    HASH_FIND(hh, hedge, &id_edge2, sizeof(long int), ptr_edge2);
    HASH_FIND(hh, hedge, &id_edge3, sizeof(long int), ptr_edge3);

    l1 = ptr_edge1->lenght;
    l2 = ptr_edge2->lenght;
    l3 = ptr_edge3->lenght;
    
    
    
    h = min(min(l1,l2), l3);
    b = max(max(min(l1,l2), min(l1,l3)), max(min(l2,l3), min(l1,l2)));
    
    iter_volume->area = 0.5*(b*h);  
    
//     printf("\niter_volume->area: %lf", iter_volume->area);
    
  }
  
  
  
}


void Volume_Centroid_Init() {

  //Function's variables  
  long int id_vertex1, id_vertex2, id_vertex3;
  volume_t *iter_volume, *tmp_volume;
  vertex_t *ptr_vertex1, *ptr_vertex2, *ptr_vertex3;
  
  //Edge Volume Assignment
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume) {
  
    id_vertex1 = iter_volume->vertices[0];
    id_vertex2 = iter_volume->vertices[1];
    id_vertex3 = iter_volume->vertices[2];
    
    HASH_FIND(hh, hvertex, &id_vertex1, sizeof(long int), ptr_vertex1);
    HASH_FIND(hh, hvertex, &id_vertex2, sizeof(long int), ptr_vertex2);
    HASH_FIND(hh, hvertex, &id_vertex3, sizeof(long int), ptr_vertex3);
   
    iter_volume->centroid[0] = (1.0/3.0)*(ptr_vertex1->x + ptr_vertex2->x + ptr_vertex3->x);
    iter_volume->centroid[1] = (1.0/3.0)*(ptr_vertex1->y + ptr_vertex2->y + ptr_vertex3->y);
       
  }
    
}

void Volume_Init(const char *fname) {
  
  //Function's variables
  int i;  
  long int offset, nvolumes, id, trash;
  long int vertices[3];
  volume_t *ptr_volume;
  
  //Open file - variable: const char *fname
  FILE *fptr;
  fptr = fopen(fname, "r");
  if(fptr == NULL)
    printf("\n\nError during file opening.\n\n");

  //Read the number of volumes - variable: long int nvolumes
  fscanf(fptr, "%ld", &nvolumes);
  printf("\nnvolumes %ld\n", nvolumes);
  
  for(i=1; i<=2; i++) {
    fscanf(fptr, "%ld", &trash);
    printf("\ntrash %ld\n", trash);
  }
  
  //Read volumes' data
  for(i=1; i<=nvolumes; i++) {

    //Read volume's id
    fscanf(fptr, "%ld", &id);
    printf("\nid %ld\n", id);

    //Read volume's first vertex
    fscanf(fptr, "%ld", &vertices[0]);
    printf("\nvertices[0] %ld\n", vertices[0]);
       
    //Read volume's second vertex
    fscanf(fptr, "%ld", &vertices[1]);
    printf("\nvertices[1] %ld\n", vertices[1]);
    
    //Read volume's third vertex
    fscanf(fptr, "%ld", &vertices[2]);
    printf("\nvertices[2] %ld\n", vertices[2]);  
    
    //Allocate volume in hash table - hvolume
    ptr_volume = malloc(sizeof(volume_t));      
    ptr_volume->id = id;
    ptr_volume->vertices[0] = vertices[0];
    ptr_volume->vertices[1] = vertices[1];
    ptr_volume->vertices[2] = vertices[2];
    ptr_volume->edges[0] = 0;
    ptr_volume->edges[1] = 0;
    ptr_volume->edges[2] = 0;
    ptr_volume->rho = 0.0;
    ptr_volume->phi[0] = 0.0;
    ptr_volume->phi[1] = 0.0;
    ptr_volume->gama = 0.0;
    ptr_volume->q = 0.0;
    ptr_volume->vel[0] = 0.0;
    ptr_volume->vel[1] = 0.0;
    ptr_volume->rate[0] = 0.0;
    ptr_volume->rate[1] = 0.0;
    ptr_volume->centroid[0] = 0.0;
    ptr_volume->centroid[1] = 0.0;
    HASH_ADD(hh, hvolume, id, sizeof(long int), ptr_volume);
        
  }  
    
  fclose(fptr);  
  
}





void Edge_Init(const char *fname) {
  
  //Function's variables
  int i, bndy;  
  long int offset, nedges, id, trash;
  long int vertices[2];
  edge_t *ptr_edge;    
  
  //Open file - variable: const char *fname
  FILE *fptr;
  fptr = fopen(fname, "r");
  if(fptr == NULL)
    printf("\n\nError during file opening.\n\n");
  
  //Read the number of edges - variable: long int nedges
  fscanf(fptr, "%ld", &nedges);
  printf("\nnedges %ld\n", nedges);

  fscanf(fptr, "%ld", &trash);
  printf("\ntrash %ld\n", trash);
  
  //Read edges' data
  for(i=1; i<=nedges; i++) {
  
    //Read edge's id
    fscanf(fptr, "%ld", &id);
    printf("\nid %ld\n", id);
    
    //Read edge's first vertex
    fscanf(fptr, "%ld", &vertices[0]);
    printf("\nvertices[0] %ld\n", vertices[0]);   
    
    //Read edge's second vertex
    fscanf(fptr, "%ld", &vertices[1]);
    printf("\nvertices[1] %ld\n", vertices[1]);
    
    //Read edge's bndy marker
    fscanf(fptr, "%d", &bndy);
    printf("\nbndy %ld\n", bndy);   
    
    //Allocate edge in hash table - hedge
    ptr_edge = malloc(sizeof(edge_t));      
    ptr_edge->id = id;
    ptr_edge->bndy = bndy;
    ptr_edge->vertices[0] = vertices[0];
    ptr_edge->vertices[1] = vertices[1];
    ptr_edge->vector[0] = 0.0;
    ptr_edge->vector[1] = 0.0;    
    ptr_edge->normal[0] = 0.0;
    ptr_edge->normal[1] = 0.0;   
    ptr_edge->flux[0] = 0.0;
    ptr_edge->flux[1] = 0.0;
    ptr_edge->volumes[0] = 0;
    ptr_edge->volumes[1] = 0; 
    ptr_edge->lenght = 0.0;
    HASH_ADD(hh, hedge, id, sizeof(long int), ptr_edge);
        
  }  
  
   
  fclose(fptr);  
  
}


void Vertex_Init(const char *fname) {
  
  //Function's variables
  int i, bndy;  
  long int offset, nvertices, id, trash;
  double x, y, g;
  vertex_t *ptr_vertex;    

  //Open file - variable: const char *fname
  FILE *fptr;
  fptr = fopen(fname, "r");
  if(fptr == NULL)
    printf("\n\nError during file opening.\n\n");

  //Read the number of vertices - variable: long int nvertices
  fscanf(fptr, "%ld", &nvertices);
  printf("\nnvertices %ld\n", nvertices);
  
  for(i=1; i<=3; i++) {
    fscanf(fptr, "%ld", &trash);
    printf("\ntrash %ld\n", trash);
  }
  

  //Read vertices' data
  for(i=1; i<=nvertices; i++) {
       
    //Read vertex's id
    fscanf(fptr, "%ld", &id);
    printf("\nid %ld\n", id);

    //Read vertex's x position
    fscanf(fptr, "%lf", &x);
    printf("\nx %lf\n", x);
    
    //Read vertex's y position
    fscanf(fptr, "%lf", &y);
    printf("\ny %lf\n", y);
    
    //Read vertex g's property
    fscanf(fptr, "%lf", &g);
    printf("\ng %lf\n", g);
          
    //Read vertex bndy marker
    fscanf(fptr, "%d", &bndy);
    printf("\nbndy %ld\n", bndy);
           
    //Allocate vertex in hash table - hvertex
    ptr_vertex = malloc(sizeof(vertex_t));      
    ptr_vertex->id = id;
    ptr_vertex->x = x;
    ptr_vertex->y = y;
    ptr_vertex->g = g;
    ptr_vertex->bndy = bndy;
    HASH_ADD(hh, hvertex, id, sizeof(long int), ptr_vertex);
        
  }  
  
  
  fclose(fptr);
      
}