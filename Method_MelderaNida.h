#include <iostream>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

const double len_a = 0.5;

double foo(VectorXd x);

MatrixXd NodeFill(VectorXd x0);

void Method_Main();

VectorXd Center_Gravity(MatrixXd &node,int n);

MatrixXd Sort(MatrixXd& node,int n);