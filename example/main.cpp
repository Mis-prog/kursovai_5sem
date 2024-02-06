#include "windows.h"
#include "../include/methods_lib/Method_MelderaNida.h"

double foo_test(VectorXd &x) {
    return x[0] * x[0] + x[0] * x[1] + x[1] - 6 * x[0] - 9 * x[1];
}

double foo_test_2(VectorXd& x){
    return x[0];
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    VectorXd x0(1);
    x0 << 0;

    Function function(x0, 20);
    function.set(foo_test);

    method_Neldera_and_Mida(function);
    function.print_result();


    return 0;
}
