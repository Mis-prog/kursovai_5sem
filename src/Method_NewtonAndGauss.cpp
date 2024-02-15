#include "../include/methods_lib/Methods.h"


void method_Newton_and_Gauss(Function &function) {
    clock_t start = clock();

    int count = function.x0.size();
    VectorXd old(count);

    for (int i = 0; i < max_iter; i++) {
        old = function.res;
        MatrixXd J = Jacobian(function);
        VectorXd dy = calculation_r(function);
        function.res = old - (J.transpose() * J).inverse() * J.transpose() * dy;
        if ((old - function.res).norm() < function.epsilon) {
            function.count_iter += i;
            break;
        }
    }

    clock_t end = clock();
    function._time = (double)(end - start)/CLOCKS_PER_SEC;
}


MatrixXd Jacobian(Function &function) {
    int row = function.size, col = function.res.size();

    MatrixXd Jacobian(row, col);
    Jacobian.setZero();


    VectorXd dx(col);
    VectorXd grad_l(col), grad_r(col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            dx.setZero();
            dx[j] = _dx;

            grad_l = function.res + dx;
            grad_r = function.res - dx;

            Jacobian(i, j) = (-function.foo_list[i](grad_l) + function.foo_list[i](grad_r)) / (2 * _dx);
        }
    }

    return Jacobian;

}

VectorXd calculation_r(Function &function) {
    int col = function.size;
    VectorXd r(col);

    for (int j = 0; j < col; j++) {
        r[j] = function.y[j] - function.foo_list[j](function.res);
    }
    return r;
}
