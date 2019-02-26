#ifndef boundaryH
#define boundaryH

void PlateCase_Temperature_Init();

void Rect_Scalar_Dirichlet(const double value[]);

double Distance_Edge_Centroid(const edge_t * const iter_edge, const double centroid[]);

void PlateCase_HeatSource_Init();

void PlateCase_Boundary(const double h, const double Tamb);

#endif
  