# Write legacy VTK format from 2D mesh Data
## Overview
 This program provides a simple function to write VTK file with legacy format from 2D mesh vector data. The vector data has to use constant lenght between nodes.
## Data format
Note that 2D array format should be converted to 1d array with column major.
e.g.
If the below 2D array is given,
```
u[0][0] = 1
u[1][0] = 2
u[0][1] = 3
u[1][1] = 4

v[0][0] = 10
v[1][0] = 11
v[0][1] = 12
v[1][1] = 13
```
you have to convert it to 1D array like this.
```
u_1d[0] = 1
u_1d[1] = 2
u_1d[2] = 3
u_1d[3] = 4

v_1d[0] = 10
v_1d[1] = 11
v_1d[2] = 12
v_1d[3] = 13
```

## Usage
```c
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
```

<img src=output_vtk.png>  

Fig. example data in Paraview.