#include "../include/methods_lib/Methods.h"


void Function::write_data_file(char *name) {
    std::ofstream data_file;
    data_file.open(name, std::ios::out);
    data_file.close();
}

void Function::set(double (*foo)(VectorXd &x)) {
    srand(time(NULL));
    y.resize(size);
    for (int i = 0; i < size; i++) {
        y(i) = foo(x0) + rand() % 10;
    }
}

Function::Function(VectorXd &x, int size) {
    this->size = size;
    this->x0 = x;
    x0.conservativeResize(x.size() + 1);
}

Function::~Function() {
    x0.resize(0);
    y.resize(0);
}

double Function::mnk(double (*foo)(VectorXd &), VectorXd &x) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (y[i] - foo(x)) * (y[i] - foo(x));
    }
    return sum;
}

void Function::print_result() {
    cout << "Начальные данные:\n";
    cout << y.transpose() << endl;

    cout << "Параметры x\n";
    cout << x0.transpose() << endl;
}
