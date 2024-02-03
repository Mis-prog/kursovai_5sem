#include <iostream>
#include "Dense"
#include <random>
#include <ctime>
#include <fstream>

using namespace std;
using namespace Eigen;

const double epsil = 1e-6;
const int maxIter = 100;
const int start = 0, _end = 5;
const int n_x = 1, b_n = 2, n_indication = 50;


double foo(VectorXd &b,VectorXd &ak,VectorXd &sk, MatrixXd &bk);

void method_NewtonandGauss();

VectorXd InitialPointY(MatrixXd &B,VectorXd &ak,VectorXd &sk, MatrixXd &bk);

MatrixXd Jacobian(MatrixXd &b,VectorXd &ak,VectorXd &sk, MatrixXd &bk);

void write_file(char *a);