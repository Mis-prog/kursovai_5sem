#include "../Eigen/Dense"
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

using namespace Eigen;
using namespace std;


class Function {
public:
    const double epsilon = 1e-5;
    vector<function<double(VectorXd &)>> foo_list;
    VectorXd x0, y;
    int size;

    Function(VectorXd &x, int size);

    void set(vector<function<double(VectorXd &)>> &foo_list);

    double mnk(VectorXd &x);

    void print_result();

    void write_data_file(char *name);

    ~Function();
};