#include <math.h>
#include "vtk_output.h"
#define DIM_X 10
#define DIM_Y 20
int main() {
    double ux_2d[DIM_X][DIM_Y];
    double uy_2d[DIM_X][DIM_Y];
    // Prepare example data.
    for (int iy = 0; iy < DIM_Y; ++iy) {
        for (int ix = 0; ix < DIM_X; ++ix) {
            ux_2d[ix][iy] = sqrt(ix * iy);
            uy_2d[ix][iy] = ix * iy;
        }
    }

    // Get 1D array
    double ux_1d[DIM_X*DIM_Y];
    double uy_1d[DIM_X*DIM_Y];
    for (int iy = 0; iy < DIM_Y; ++iy) {
        for (int ix = 0; ix < DIM_X; ++ix) {
            ux_1d[DIM_X * iy + ix] = ux_2d[ix][iy];
            uy_1d[DIM_X * iy + ix] = uy_2d[ix] [iy];
        }
    }

    // 
    struct Data2D output_data;
    output_data.ux = ux_1d;
    output_data.uy = uy_1d;
    output_data.nx = DIM_X;
    output_data.ny = DIM_Y;
    output_data.dl = 1.0; // mesh length
    CreateVTKUnstructuredGrid2d(output_data, "output.vtk");
    return 0;
}
