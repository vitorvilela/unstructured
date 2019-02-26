#include <stdio.h>
#include <math.h>
#include "uthash.h"
#include "structures.h"
#include "boundary.h"
#include "data.h"


void PlateCase_HeatSource_Init() {
    
  //Function's variables  
  volume_t *iter_volume, *tmp_volume;
  
  //Set HeatSource 
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume) { 
    
    if(iter_volume->centroid[0] > 0.009 && iter_volume->centroid[0] < 0.018 && iter_volume->centroid[1] > 0.009) 
      iter_volume->q = 1E7;      
    
  }
  
  
}


void PlateCase_Temperature_Init() {

  //Function's variables  
  volume_t *iter_volume, *tmp_volume;
  
  //Set initial temperature
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume) {   
    iter_volume->phi[0] = 293;
    iter_volume->phi[1] = 293;    
  }
    
}


double Distance_Edge_Centroid(const edge_t * const iter_edge, const double centroid[]) {
  
  //Function's variables
  double dist, x, y;
  long int id_vertex1, id_vertex2;
  vertex_t *ptr_vertex1, *ptr_vertex2;
  
  id_vertex1 = iter_edge->vertices[0];
  id_vertex2 = iter_edge->vertices[1];
  HASH_FIND(hh, hvertex, &id_vertex1, sizeof(long int), ptr_vertex1);
  HASH_FIND(hh, hvertex, &id_vertex2, sizeof(long int), ptr_vertex2);

  x = fabs(centroid[0] - ptr_vertex1->x);
  y = fabs(centroid[1] - ptr_vertex1->y);
  dist = sqrt(pow(x,2.0) + pow(y,2.0));
    
  ptr_vertex1 = NULL;
  ptr_vertex2 = NULL;
  
  return dist; 
  
}



void Rect_Scalar_Dirichlet(const double value[]) {
  
  //Function's variables
  long int id_volume;
  double diff, dist;
  edge_t *iter_edge, *tmp_edge;
  volume_t *ptr_volume;
    
  //Set Scalar Value to the Boundary by Calculating its Flux
  HASH_ITER(hh, hedge, iter_edge, tmp_edge) {
    
    id_volume = max(iter_edge->volumes[0],iter_edge->volumes[1]);
    HASH_FIND(hh, hvolume, &id_volume, sizeof(long int), ptr_volume);
    
    switch(iter_edge->bndy) {
      
      case 1:
	diff = value[0] - ptr_volume->phi[0];
	dist = Distance_Edge_Centroid(iter_edge, ptr_volume->centroid);
	iter_edge->flux[1] = diff/dist;
	break;
      case 2:
	diff = value[1] - ptr_volume->phi[0];
	dist = Distance_Edge_Centroid(iter_edge, ptr_volume->centroid);
	iter_edge->flux[1] = diff/dist;
	break;
      case 3:
	diff = value[2] - ptr_volume->phi[0];
	dist = Distance_Edge_Centroid(iter_edge, ptr_volume->centroid);
	iter_edge->flux[1] = diff/dist;
	break;
      case 4:
	diff = value[3] - ptr_volume->phi[0];
	dist = Distance_Edge_Centroid(iter_edge, ptr_volume->centroid);
	iter_edge->flux[1] = diff/dist;
	break;
      default:
	break;
          
    }
    
    ptr_volume = NULL;   
    
  }   
  
}


void PlateCase_Boundary(const double h, const double Tamb) {
  
  //Function's variables
  long int id_volume;
  edge_t *iter_edge, *tmp_edge;
  volume_t *ptr_volume;
    
  //Set Scalar Value to the Boundary by Calculating its Flux
  HASH_ITER(hh, hedge, iter_edge, tmp_edge) {
    
    id_volume = max(iter_edge->volumes[0], iter_edge->volumes[1]);
    HASH_FIND(hh, hvolume, &id_volume, sizeof(long int), ptr_volume);
    
    switch(iter_edge->bndy) {
      
      case 1:	
	iter_edge->flux[1] = h*(Tamb - ptr_volume->phi[1]);
	break;
      case 2:	
	iter_edge->flux[1] = 0.0;
	break;
      case 3:
	iter_edge->flux[1] = 0.0;
	break;
      case 4:
	iter_edge->flux[1] = 0.0;
	break;
      default:
	break;
          
    }
    
    ptr_volume = NULL;   
    
  }   
  
}

