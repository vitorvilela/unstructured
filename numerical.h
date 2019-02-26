#ifndef fluxH
#define fluxH

void Flux_Diffusive();

void Rate_Diffusive();

void Flux_Sign(const edge_t * const ptr_edge, const volume_t * const iter_volume, double *sign);

void Euler_Explicit_Scalar(const double dt);

void PlateCase_Unsteady();


#endif