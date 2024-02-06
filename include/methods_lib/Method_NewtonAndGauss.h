#include <iostream>
#include "../Eigen/Dense"
#include <random>
#include <ctime>
#include "Methods.h"

using namespace std;
using namespace Eigen;

const double epsil = 1e-6;
const int maxIter = 100;
const int start = 0, _end = 5;
const int n_x = 1, b_n = 2, n_indication = 50;


VectorXd foo(VectorXd &x, VectorXd &b);

void method_NewtonandGauss();

VectorXd InitialPointY(VectorXd &x, VectorXd &b);

MatrixXd Jacobian(VectorXd &x, VectorXd &b);

void write_file(char *a);