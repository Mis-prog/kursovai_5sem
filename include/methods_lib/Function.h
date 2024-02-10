#pragma once

#include "../Eigen/Dense"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <functional>
#include <iomanip>
#include <chrono>

using namespace Eigen;
using namespace std;


class Function {
public:
    double _time = 0.0;
    int count_iter = 0;
    const double epsilon = 1e-3;
    vector<function<double(VectorXd &)>> foo_list;
    VectorXd x0, y;
    int size;

    Function(VectorXd &x, int size);

    void set(vector<function<double(VectorXd &)>> &foo_list);

    double mnk(VectorXd &x);

    void print_result();

    void write_data_file(char *name);

    int getCountIter() const;

    double getTime() const;

    const VectorXd &getX() const;

    ~Function();
};