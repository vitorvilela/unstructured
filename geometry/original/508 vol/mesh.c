#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "uthash.h"
#include "mesh.h"

/************* STACK FUNCTIONS *************/


stack_t * createStack(unsigned long MAX) {
  
  stack_t *S;
  S = malloc(MAX*sizeof(unsigned long));
  S->size = 0;
  S->capacity = MAX;
  
  return S;
  
}


void pop(stack_t *S) {
  
  if(S->size == 0)
    printf("Stack is Empty");

  else {    
    S->size--;
    return S->id[S->size+1];    
  }
  
}


unsigned long top(stack_t *S) {
  
  if(S->size == 0)
    printf("Stack is Empty");

  else {    
    return S->id[S->size-1];    
  }
  
}


void push(stack_t *S, unsigned long id) {
  
  if(S->size == S->capacity) 
    printf("Stack is Full");
  
  else 
    S->id[S->size++] = id;
   
}


/************* STARTUP FUNCTIONS *************/


void vertex_startup() {
  
  int i, j;
  vertex_t *ptr_vertex;    
  int id = 1;
  
  for(j=1; j<=3; j++) {
    for(i=1; i<=3; i++) {
      ptr_vertex = malloc(sizeof(vertex_t));      
      ptr_vertex->id = id;
      HASH_ADD(hh, hvertex, id, sizeof(int), ptr_vertex);
      ptr_vertex->x = 0.5*(i-1);
      ptr_vertex->y = 0.5*(j-1);      
      id++;      
    }
  } 
  
}


void face_startup() {
  
  int id;
  const int NFACES = 16;
  face_t *ptr_face;    
  
  for(id=1; id<=NFACES; id++) {
    ptr_face = malloc(sizeof(face_t));      
    ptr_face->id = id;
    HASH_ADD(hh, hface, id, sizeof(int), ptr_face);
    ptr_face->vector[0] = 0.0;
    ptr_face->vector[1] = 0.0;
    ptr_face->normal[0] = 0.0;
    ptr_face->normal[1] = 0.0;
    ptr_face->flux[0] = 0.0;
    ptr_face->flux[1] = 0.0;    
    switch(id) {
      case 1:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 2:  
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 3:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 4:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 5:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 6: 
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 7:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 8:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 9:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 10: 
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 11:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 12:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 13:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 14:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 15:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
      case 16:
	ptr_face->bc = ;
	ptr_face->vertices[0] = ;
	ptr_face->vertices[1] = ;
	ptr_face->volumes[0] = ;
	ptr_face->volumes[1] = ;
    }        
  } 
  
}


void volume_startup() {
  
  int id;
  const int NVOLUMES = 8;
  face_t *ptr_volume;    
  
  for(id=1; id<=NVOLUMES; id++) {
    ptr_volume = malloc(sizeof(face_t));      
    ptr_volume->id = id;
    HASH_ADD(hh, hvolume, id, sizeof(int), ptr_volume);
    ptr_volume->rho = 0.0;
    ptr_volume->phi = 0.0;
    ptr_volume->gama = 0.0;
    ptr_volume->vel[0] = 0.0;
    ptr_volume->vel[1] = 0.0;
    ptr_volume->rate[0] = 0.0;
    ptr_volume->rate[1] = 0.0;
    ptr_volume->centroid[0] = 0.0;
    ptr_volume->centroid[1] = 0.0;   
    switch(id) {
      case 1:
	ptr_volume->faces[0] = ;
	ptr_volume->faces[1] = ;
	ptr_volume->faces[2] = ;
      case 2:  
	ptr_volume->faces[0] = ;
	ptr_volume->faces[1] = ;
	ptr_volume->faces[2] = ;
      case 3:
	ptr_volume->faces[0] = ;
	ptr_volume->faces[1] = ;
	ptr_volume->faces[2] = ;
      case 4:
	ptr_volume->faces[0] = ;
	ptr_volume->faces[1] = ;
	ptr_volume->faces[2] = ;
      case 5:
	ptr_volume->faces[0] = ;
	ptr_volume->faces[1] = ;
	ptr_volume->faces[2] = ;
      case 6: 
	ptr_volume->faces[0] = ;
	ptr_volume->faces[1] = ;
	ptr_volume->faces[2] = ;
      case 7:
	ptr_volume->faces[0] = ;
	ptr_volume->faces[1] = ;
	ptr_volume->faces[2] = ;
      case 8:
	ptr_volume->faces[0] = ;
	ptr_volume->faces[1] = ;
	ptr_volume->faces[2] = ;      
    }        
  } 
  
}








