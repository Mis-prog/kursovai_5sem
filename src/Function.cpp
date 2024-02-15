#include "../include/methods_lib/Function.h"
#include "Method_MelderaNida.h"
#include "Method_NewtonAndGauss.h"


void Function::write_data_file(char *name) {
    std::ofstream data_file;
    data_file.open(name, std::ios::out);
    data_file.close();
}

Function::Function(VectorXd &x, int size) {
    this->size = size;
    this->x0 = x;
    res.resize(size);
    res = x;
}

Function::~Function() {
    x0.resize(0);
    y.resize(0);
}

double Function::mnk(VectorXd &x) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (y[i] - foo_list[i](x)) * (y[i] - foo_list[i](x));
    }
    return sum;
}

void Function::print_result() {
    cout << "Начальные данные:\n";
    cout << y.transpose() << endl;

    cout << "Параметры x\n";
    cout << x0.transpose() << endl;
}

void Function::set(vector<function<double(VectorXd &)>> &foo_list, VectorXd &y) {
    srand(time(NULL));

    this->foo_list = foo_list;
    y.resize(size);
    this->y = y;
//    VectorXd x_0(2);
//    x_0 << 0, 0;
//    for (int i = 0; i < size; i++) {
//        y[i] = foo_list[i](x_0);
//    }
}

int Function::getCountIter() const {
    cout << "count_iter: " << count_iter << endl;
    return count_iter;
}

const VectorXd &Function::getX() const {
    cout << "Parametr: " << res.transpose() << endl;
    return res;
}

double Function::getTime() const {
    cout << setprecision(10) << "time: " << _time << endl;
    return _time;
}

void Function::hybrid_mode(int count_iter) {
    this->count_step = count_iter;
    this->on_hybrid = true;
    method_Neldera_and_Mida(*this);
    method_Newton_and_Gauss(*this);
}
