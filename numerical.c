#include <stdio.h>
#include <math.h>
#include "uthash.h"
#include "structures.h"
#include "data.h"
#include "misc.h"





void PlateCase_Unsteady() {
  
  char in[1];
  
  const char fnamem[] = {"APlatem.vtk"};
  
  //Function's variables
  int ct = 0;
  double t = 0.0;
  const double time = 30.0;
  const double dt = 0.00001;
  const double h = 500.0;
  const double Tamb = 293.0;
  
  //Time marching
  do {
    
    ct++; 
    t += dt;
    printf("\n*******************\n");
    printf("\nTime %lf\n", t);
    printf("\n*******************\n");
    PlateCase_Boundary(h, Tamb);
    Flux_Diffusive();
    Rate_Diffusive();
    Euler_Explicit_Scalar(dt);
    
    if(ct%(int)(1/dt) == 0) {
      Print_VTK(fnamem);
      Print_Screen_Scalar(t);
    }
    
  }
  while(t < time);
  
  Print_Screen_Scalar(t);

  
}



void Euler_Explicit_Scalar(const double dt) {
  
  //Function's variables
  volume_t *iter_volume, *tmp_volume;
  double source;
  
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume) {
    source = iter_volume->q*(iter_volume->area);
    iter_volume->phi[1] = iter_volume->phi[0] + dt*(iter_volume->rate[1] + source);
    iter_volume->phi[0] = iter_volume->phi[1];
  }
  
}


void Flux_Diffusive() {

  //Function's variables
  long int id_volume1, id_volume2;
  double Dphi, div, Mean_gama, delta[2], Gphi[2];
  edge_t *iter_edge, *tmp_edge;
  volume_t *ptr_volume1, *ptr_volume2;
  
  //Flux calculation
  HASH_ITER(hh, hedge, iter_edge, tmp_edge) {
    
    if(iter_edge->bndy == 0) {
 
      id_volume1 = iter_edge->volumes[0];
      id_volume2 = iter_edge->volumes[1];
      HASH_FIND(hh, hvolume, &id_volume1, sizeof(long int), ptr_volume1);
      HASH_FIND(hh, hvolume, &id_volume2, sizeof(long int), ptr_volume2);
      
      Dphi = fabs(ptr_volume1->phi[0] - ptr_volume2->phi[0]);
      
      delta[0] = fabs(ptr_volume1->centroid[0] - ptr_volume2->centroid[0]);
      delta[1] = fabs(ptr_volume1->centroid[1] - ptr_volume2->centroid[1]);
     
      if(delta[0] != 0)
	Gphi[0] = Dphi / delta[0];
      else
	Gphi[0] = 0;
      
      if(delta[1] != 0)
	Gphi[1] = Dphi / delta[1];
      else
	Gphi[1] = 0;
      
      div = Gphi[0]*(iter_edge->normal[0]) + Gphi[1]*(iter_edge->normal[1]);

      Mean_gama = 0.5*(ptr_volume1->gama + ptr_volume2->gama);
      iter_edge->flux[1] = fabs(Mean_gama*div);
      
    }
    
  }
  
}

void Rate_Diffusive() {
  
  //Function's variables
  long int id_edge1, id_edge2, id_edge3;
  double ds1, ds2, ds3;
  double *sign1, *sign2, *sign3;
  double vsign1 = 0.0, vsign2 = 0.0, vsign3 = 0.0;
  edge_t *ptr_edge1, *ptr_edge2, *ptr_edge3;
  volume_t *iter_volume, *tmp_volume;

  sign1 = &vsign1;
  sign2 = &vsign2;
  sign3 = &vsign3;
  
  //Rate calculation
  HASH_ITER(hh, hvolume, iter_volume, tmp_volume) {
       
    id_edge1 = iter_volume->edges[0];
    id_edge2 = iter_volume->edges[1];
    id_edge3 = iter_volume->edges[2];
    HASH_FIND(hh, hedge, &id_edge1, sizeof(long int), ptr_edge1);
    HASH_FIND(hh, hedge, &id_edge2, sizeof(long int), ptr_edge2);
    HASH_FIND(hh, hedge, &id_edge3, sizeof(long int), ptr_edge3);

    ds1 = sqrt(pow(ptr_edge1->vector[0], 2.0) + (pow(ptr_edge1->vector[1], 2.0)));
    ds2 = sqrt(pow(ptr_edge2->vector[0], 2.0) + (pow(ptr_edge2->vector[1], 2.0)));
    ds3 = sqrt(pow(ptr_edge3->vector[0], 2.0) + (pow(ptr_edge3->vector[1], 2.0)));

    
    if(ptr_edge1->bndy == 0) 
      Flux_Sign(ptr_edge1, iter_volume, sign1);    
    else
      *sign1 = 1.0;
    
    if(ptr_edge2->bndy == 0) 
      Flux_Sign(ptr_edge2, iter_volume, sign2);     
    else
      *sign2 = 1.0;
    
    if(ptr_edge3->bndy == 0) 
      Flux_Sign(ptr_edge3, iter_volume, sign3);     
    else
      *sign3 = 1.0;
  
    iter_volume->rate[1] = *sign1*(ptr_edge1->flux[1])*ds1 + *sign2*(ptr_edge2->flux[1])*ds2 + *sign3*(ptr_edge3->flux[1]*ds3);
    
  }
    
}

void Flux_Sign(const edge_t * const ptr_edge, const volume_t * const iter_volume, double *sign) {
  
  //Function's variables
  long int id_iter_volume, id_neigh_volume;
  double phi_iter_volume, phi_neigh_volume;
  volume_t *ptr_neigh_volume;
    
  //Set flux sign for each face
  id_iter_volume = iter_volume->id;
  phi_iter_volume = iter_volume->phi[0];
    
  if(ptr_edge->volumes[0] == id_iter_volume) 
    id_neigh_volume = ptr_edge->volumes[1];
  else
    id_neigh_volume = ptr_edge->volumes[0];
  
  HASH_FIND(hh, hvolume, &id_neigh_volume, sizeof(long int), ptr_neigh_volume);

  phi_neigh_volume = ptr_neigh_volume->phi[0];
  
  if(phi_neigh_volume > phi_iter_volume) 
    *sign = 1.0;
  
  if(phi_neigh_volume < phi_iter_volume) 
    *sign = -1.0;
  
    ptr_neigh_volume = NULL;
    
}

