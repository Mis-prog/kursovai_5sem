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
#include "../data/rbfreader.h"

using namespace Eigen;
using namespace std;


class Function {
public:
    RBF rbf;
    double _time = 0.0;
    int count_iter = 0;
    const double epsilon = 1e-3;
    VectorXd x0, y, res;
    int size = 0;
    int count_step = 0;
    bool on_hybrid = 0;

    Function(VectorXd &x);

    void set(RBF &rbf, VectorXd &y);

    double mnk(VectorXd &x);

    void print_result();

    void write_data_file(char *name);

    int getCountIter() const;

    double getTime() const;

    const VectorXd &getX() const;

    void hybrid_mode(int count_iter);

    ~Function();
};