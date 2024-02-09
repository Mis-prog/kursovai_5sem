#include "windows.h"
//#include "../include/methods_lib/Method_MelderaNida.h"
#include "../include/methods_lib/Method_NewtonAndGauss.h"

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
    x0 << 0, 1;

    vector<function<double(VectorXd &)>> foo_list;

    foo_list.push_back(foo_test_1);
    foo_list.push_back(foo_test_2);

    Function function(x0, 2);
    function.set(foo_list);

//    method_Neldera_and_Mida(function);
    method_Newton_and_Gauss(function);
    function.getX();
    function.getCountIter();

    return 0;
}
