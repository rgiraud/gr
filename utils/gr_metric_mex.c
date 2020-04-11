
#include<mex.h>
#include<matrix.h>
#include<math.h>
#include "./GR.h"



void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    
    int * S = (int*)mxGetPr(prhs[0]);
    int nRows=mxGetM(prhs[0]);
    int nCols=mxGetN(prhs[0]);
    
    //Reprocessing
    int max_sp = 0;
    for (int i = 0; i < nCols*nRows; i++) {
        if (S[i] > max_sp)
            max_sp = S[i];
    }
    
    int * S_r = (int *) malloc(nCols*nRows*sizeof(int));
    for (int i = 0; i < nCols*nRows; i++)
        S_r[i] = S[(int)(i/nCols) + (i%nCols)*nRows];
    
    max_sp = max_sp +1;
    int *spx_sizes = (int *)calloc(max_sp, sizeof(int));
    for (int i = 0; i < nCols*nRows; i++)
        spx_sizes[S_r[i]]++;
    
    int **spx = (int **) malloc(max_sp * sizeof(int *));
    
    for (int i = 0; i < max_sp; i++) {
        spx[i] = (int *) malloc(spx_sizes[i] * sizeof(int));
        spx_sizes[i] = 0;
    }
    
    for (int i = 0; i < nCols*nRows; i++)
        spx[ S_r[i] ][ spx_sizes[S_r[i]] ++ ] = i;
    
    
    
    double smf = 0;
    double src = 0;
    double gr = gr_metric(spx, spx_sizes, max_sp, nCols, nRows, &smf, &src);
    
    
    int dims[1];
    dims[0] = 1;
    plhs[0] = mxCreateNumericArray(1, dims, mxSINGLE_CLASS, mxREAL);
    float *gr_ptr = (float*) mxGetPr(plhs[0]);
    *gr_ptr = (float) gr;
    
    plhs[1] = mxCreateNumericArray(1, dims, mxSINGLE_CLASS, mxREAL);
    float *smf_ptr = (float*) mxGetPr(plhs[1]);
    *smf_ptr = (float) smf;
    
    plhs[2] = mxCreateNumericArray(1, dims, mxSINGLE_CLASS, mxREAL);
    float *src_ptr = (float*) mxGetPr(plhs[2]);
    *src_ptr = (float) src;
    
}
