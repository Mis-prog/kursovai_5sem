#include "../include/methods_lib/Function.h"


void Function::write_data_file(char *name) {
    std::ofstream data_file;
    data_file.open(name, std::ios::out);
    data_file.close();
}

Function::Function(VectorXd &x, int size) {
    this->size = size;
    this->x0 = x;
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

void Function::set(vector<function<double(VectorXd &)>> &foo_list) {
    srand(time(NULL));

    this->foo_list = foo_list;
    y.resize(size);
    VectorXd x_0(2);
    x_0 << 0, 0;
    for (int i = 0; i < size; i++) {
        y[i] = foo_list[i](x_0);
    }
}

int Function::getCountIter() const {
    cout << "count_iter: " << count_iter << endl;
    return count_iter;
}

const VectorXd &Function::getX() const {
    cout << "Parametr: " << x0.transpose() << endl;
    return x0;
}
