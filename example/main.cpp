#include "windows.h"
#include "../include/methods_lib/Methods.h"

double foo_test_1(VectorXd &x) {
    return exp(-x[0] * x[0] - x[1] * x[1]);
}

double foo_test_2(VectorXd &x) {
    return exp(x[0] + x[1]);
}

double foo_test_3(VectorXd &x) {
    return 0;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    VectorXd x0(2);
    x0 << 0.9, 1;

    vector<function<double(VectorXd &)>> foo_list;

    foo_list.emplace_back(foo_test_1);
    foo_list.emplace_back(foo_test_2);

    Function function1(x0, 2), function2(x0, 2);
    function1.set(foo_list);
    function2.set(foo_list);

    method_Neldera_and_Mida(function1);
    function1.getX();
    function1.getCountIter();
    function1.getTime();

    cout << endl;

    method_Newton_and_Gauss(function2);
    function2.getX();
    function2.getCountIter();
    function2.getTime();


    return 0;
}
