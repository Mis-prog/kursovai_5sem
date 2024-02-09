#include "../Eigen/Dense"
#include <random>
#include <ctime>
#include "Methods.h"

using namespace std;
using namespace Eigen;

//void method_Newton_and_Gauss(double (*foo)(VectorXd &x), Function &function);

MatrixXd Jacobian(Function &function);