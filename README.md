# MyLinealAlgebraMEX
MEX library for using with MatLab.

  This project is an example about how to configure a project in Visual Studio to generate a MEX library for usign in MatLab.

#Content
  `myla` function that has as input a square matrix and returns the determinant of the matrix (calling MKL from C++) and if two parameters are requested also returns the inverse of matrix.
  
#Usage
  D = myla(A) Returns determinant of matrix A.
  [D,I] = myla(A) Returns determinant and inverse matrix of matrix A.

#Requirements
Using in MatLab 32bits under Windows

#Screenshot
![alt tag](https://raw.githubusercontent.com/LauraLaureus/MyLinealAlgebraMEX/master/MyLinealAlgebra.png)
