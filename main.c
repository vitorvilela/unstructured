#include "init.h"
#include "structures.h"



int main(int argc, char *argv[]) {    
  
  //Mesh Startup
  Vertex_Init("input.1.node");  
  Edge_Init("input.1.edge");  
  Volume_Init("input.1.ele");
    
  Edge_Vol_Assign();   
  Edge_Geom();
  
  Volume_Centroid_Init();
  Edge_Lenght_Init();
  Volume_Area_Init();
     
  //Initial Conditions
  PlateCase_Gama_Init();
  PlateCase_Temperature_Init();
  PlateCase_HeatSource_Init();
  
  const char fnamei[] = {"APlatei.vtk"};
   const char fnameKi[] = {"KPlatei.vtk"};
  
  Print_VTK(fnamei);  
  Print_K_VTK(fnameKi);
  
  //Simulation
  PlateCase_Unsteady(); 
  
  const char fnamef[] = {"APlatef.vtk"};
  
  Print_VTK(fnamef);
  
  
  return 0;  
  
}
