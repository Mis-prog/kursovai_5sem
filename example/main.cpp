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

void get_y(vector<function<double(VectorXd &)>> &foo_list, VectorXd &y) {
    VectorXd x_0(2);
    x_0 << 0, 0;
    for (int i = 0; i < y.size(); i++) {
        y[i] = foo_list[i](x_0);
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    VectorXd x0(2);
    x0 << 1, 2;

    vector<function<double(VectorXd &)>> foo_list;

    foo_list.emplace_back(foo_test_1);
    foo_list.emplace_back(foo_test_2);

    Function function1(x0, 2), function2(x0, 2);
    VectorXd y(2);
    get_y(foo_list, y);
    function1.set(foo_list, y);
    function2.set(foo_list, y);

    cout << "Метод Нелдера Мида\n";
    method_Neldera_and_Mida(function1);
    function1.getX();
    function1.getCountIter();
    function1.getTime();

    cout << endl;

    cout << "Метод Ньютона Гаусса\n";
    method_Newton_and_Gauss(function2);
    function2.getX();
    function2.getCountIter();
    function2.getTime();

    cout << endl;

    cout << "Метод Нелдера Мида + Метод Ньютона Гаусса\n";
    Function function3(x0, 2);
    function3.set(foo_list, y);
    function3.hybrid_mode(5);
    function3.getX();
    function3.getCountIter();
    function3.getTime();


    return 0;
}
