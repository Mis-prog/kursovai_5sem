#include "../include/methods_lib/Methods.h"


void method_Newton_and_Gauss(Function &function) {
    int count = function.x0.size();
    VectorXd old(count);

    for (int i = 0; i < max_iter; i++) {
        old = function.x0;
        MatrixXd J = Jacobian(function);
        VectorXd dy = calculation_r(function);
        function.x0 = old - (J.transpose() * J).inverse() * J.transpose() * dy;
        if ((old - function.x0).norm() < function.epsilon) {
            function.count_iter = i;
            break;
        }
//        cout << function.x0.transpose() << endl;
    }
}


MatrixXd Jacobian(Function &function) {
    int row = function.size, col = function.x0.size();

    MatrixXd Jacobian(row, col);
    Jacobian.setZero();


    VectorXd dx(col);
    VectorXd grad_l(col), grad_r(col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            dx.setZero();
            dx[j] = _dx;

            grad_l = function.x0 + dx;
            grad_r = function.x0 - dx;

            Jacobian(i, j) = (-function.foo_list[i](grad_l) + function.foo_list[i](grad_r)) / (2 * function.epsilon);
        }
    }

    return Jacobian;
}

VectorXd calculation_r(Function &function) {
    int col = function.size;
    VectorXd r(col);

    for (int j = 0; j < col; j++) {
        r[j] = function.y[j] - function.foo_list[j](function.x0);
    }
    return r;
}
