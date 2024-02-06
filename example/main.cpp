#include "windows.h"
#include "../include/methods_lib/Method_MelderaNida.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    VectorXd x0(2);
    x0 << 0, 1;

    Function function(x0, 2);
    function.set(foo);

    method_Neldera_and_Mida(function);
    return 0;
}
