#include "../Eigen/Dense"
#include <iostream>
#include <fstream>

using namespace Eigen;
using namespace std;


class Function {
public:
    VectorXd x0, y;
    int size;

    Function(VectorXd &x,int size);

    void set(double (*foo)(VectorXd &x));

    double mnk(double (*foo)(VectorXd &x),VectorXd &x);

    void print_result();

    void write_data_file(char *name);

    ~Function();
};