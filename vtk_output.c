#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vtk_output.h"
#define threeD2oneD(ix, iy, iz, nx, ny, nz) ((nx) * (ny) * (iz) + (nx) * (iy) + (ix))

void CreateVTKUnstructuredGrid2d(struct Data2D data, char *filename) {
    printf("vtk name:%s\n",filename);
    int nx = data.nx;
    int ny = data.ny;
    double dl = data.dl;
    int n_cells = (nx-1) * (ny-1);
    int n_points = nx * ny;
    printf("nx:%d, ny:%d, number_of_cells:%d, number_of_points:%d dl:%.4f\n", nx, ny, n_cells, n_points, dl);

    FILE *fp_out;
    fp_out = fopen(filename, "w");
    fprintf(fp_out, "# vtk DataFile Version 2.0\n");
    fprintf(fp_out, "%s\n", filename);
    fprintf(fp_out, "ASCII\n");
    fprintf(fp_out, "DATASET UNSTRUCTURED_GRID\n");
    fprintf(fp_out, "POINTS %d FLOAT\n", n_points);
    for (int iy = 0; iy < ny; ++iy) {
        for (int ix = 0; ix < nx; ++ix){
            fprintf(fp_out, "%f %f %f\n", dl*ix, dl*iy, 0.0);
        }
    }
    fprintf(fp_out, "CELLS %d %d\n",n_cells, 5*n_cells);
    for (int iy = 0; iy < ny-1; ++iy) {
        for (int ix = 0; ix < nx-1; ++ix) {            
            fprintf(fp_out, "4 ");
            fprintf(fp_out, "%d %d %d %d\n",
                    threeD2oneD(ix, iy, 0, nx, ny, 1),
                    threeD2oneD(ix+1, iy, 0, nx, ny, 1),
                    threeD2oneD(ix+1, iy+1, 0, nx, ny, 1),
                    threeD2oneD(ix, iy+1, 0, nx, ny, 1));

        }
    }
    fprintf(fp_out, "CELL_TYPES %d\n", n_cells);
    for (int ix = 0; ix < nx-1; ++ix) {
        for (int iy = 0; iy < ny-1; ++iy) {
            fprintf(fp_out, "9\n");
        }
    }
    fprintf(fp_out, "POINT_DATA %d\n", n_points);
    fprintf(fp_out, "VECTORS velocity FLOAT\n");
    int index;
    double *ux = data.ux;
    double *uy = data.uy;
    for (int ix = 0; ix < nx; ++ix) {
        for (int iy = 0; iy < ny; ++iy) {
            index = nx * iy + ix;
            fprintf(fp_out, "%f %f %f\n", ux[index], uy[index], 0.0);
            //printf("%f %f %f\n", ux[index], uy[index], 0.0);

        }
    }
    fclose(fp_out);
}


