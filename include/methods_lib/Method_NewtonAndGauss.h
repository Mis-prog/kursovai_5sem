using namespace std;
using namespace Eigen;

const int max_iter = 300;
const double _dx = 0.1;

void method_Newton_and_Gauss(Function &function);

MatrixXd Jacobian(Function &function);

VectorXd calculation_r(Function &function);