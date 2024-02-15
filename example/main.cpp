#include "windows.h"
#include "../include/methods_lib/Methods.h"



int main() {
    SetConsoleOutputCP(CP_UTF8);


    cout << "\nНелдера Мида\n";
    RBF rbf =  RBF::ReadFile("rbf.txt");
    VectorXd param(3),y;
    param << 10.2,12.2,1.21;
    rbf.getValues(param,y);
    VectorXd x(3);
    x << 10,100,1;

    Function function1(x);
    function1.set(rbf,y);

    method_Neldera_and_Mida(function1);
    function1.getX();
    function1.getCountIter();
    function1.getTime();

    cout << "\nНьютона Гаусса\n";

    Function function2(x);
    function2.set(rbf,y);
    method_Newton_and_Gauss(function2);
    function2.getX();
    function2.getCountIter();
    function2.getTime();

    cout << "\nГибрид\n";

    Function function3(x);
    function3.set(rbf,y);
    function3.hybrid_mode(4000);
    function3.getX();
    function3.getCountIter();
    function3.getTime();

    return 0;
}
