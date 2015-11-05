#include <cstdio>
#include <cstring>
#include <cmath>
#include <mkl.h>

#ifdef _CHAR16T
#define CHAR16_T
#endif
#include <mex.h>

void mexFunction(int nlhs, mxArray *plhs[],
	int nrhs, const mxArray *prhs[]){

	/*Declarar las variables locales*/
	double *A, *B, determinante;
	int *pivot, info, Nfilas, Ncolumnas;

	if (nrhs != 1)
		mexErrMsgTxt("ERROR: myla, Debe tener un argumento de entrada");

	if (!mxIsNumeric(prhs[0]))
		mexErrMsgTxt("ERROR: myla, El argumento de entrada debe ser una matriz");
	Nfilas = mxGetM(prhs[0]);
	Ncolumnas = mxGetN(prhs[0]);

	if (Nfilas != Ncolumnas)
		mexErrMsgTxt("ERROR: myla, El argumento de entrada debe ser una matriz cuadrada");

	if (Nfilas == 0)
		mexErrMsgTxt("ERROR: myla, El argumento de entrada debe ser una matriz no ser nula");

	if (nlhs > 2)
			mexErrMsgTxt("ERROR: myla, Debe tener uno o dos argumentos de salida");

	A = mxGetPr(prhs[0]);
	B = (double *)mkl_malloc(Nfilas*Ncolumnas*sizeof(double), 64);
	memcpy(B, A, Nfilas*Ncolumnas*sizeof(double));

	pivot = (int*)mkl_malloc(Nfilas*sizeof(int), 32);

	info = LAPACKE_dgetrf(LAPACK_COL_MAJOR, Nfilas, Ncolumnas, B, Ncolumnas, pivot);
	determinante = 1.0;

	for (int i = 0; i < Nfilas; i++){
		if (pivot[i] != (i + 1))
			determinante *= -B[i*Ncolumnas + i];
		else
			determinante *= B[i*Ncolumnas + i];
	}

	plhs[0] = mxCreateDoubleScalar(determinante);
	if (nlhs == 2){
		if (fabs(determinante) < 1.0e-8)
			mexWarnMsgTxt("MATRIZ SINGULAR O CASI SINGULAR");
		LAPACKE_dgetri(LAPACK_COL_MAJOR, Nfilas, B, Ncolumnas, pivot);
		plhs[1] = mxCreateDoubleMatrix(Nfilas, Ncolumnas, mxREAL);
		double *C = mxGetPr(plhs[1]);
		memcpy(C, B, Nfilas*Ncolumnas*sizeof(double));
	}
	mkl_free(pivot);
	mkl_free(B);

}