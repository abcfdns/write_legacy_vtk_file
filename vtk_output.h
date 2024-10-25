#ifndef VTK_OUTPUT_
#define VTK_OUTPUT_
struct Data2D{
    double *ux;
    double *uy;
    double dl;
    int nx;
    int ny;
};
void CreateVTKUnstructuredGrid2d(struct Data2D, char *);
#endif