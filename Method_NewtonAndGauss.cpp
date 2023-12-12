#include "Method_NewtonAndGauss.h"


void print_point(VectorXd &x_i);

VectorXd foo(VectorXd &x, VectorXd &b) {//y=f(x,a,b) y=b1*x/(b2+x)
    VectorXd cur = x.array() + b[1];
    VectorXd res = (b[0] * x.array()) / cur.array();
    return res;
}

void method_NewtonandGauss() {
    VectorXd x = VectorXd::LinSpaced(50, 0, 5);
    VectorXd b{{2, 3}};
    VectorXd y = InitialPointY(x, b);
    ofstream out1;
    out1.open("Point.txt");
    for (int i = 0; i < x.size(); i++) {
        out1 << x[i] << " " << y[i] << endl;
    }
    out1.close();
    VectorXd old(b.size()), _new(b.size());
    old << 5, 1;
    _new << 5, 1;
    for (int i = 0; i < maxIter; i++) {
        old = _new;
        MatrixXd J = Jacobian(x, old);
        VectorXd dy = y - foo(x, old);
        _new = old + (J.transpose() * J).inverse() * J.transpose() * dy;
        if ((old - _new).norm() < epsil) {
            break;
        }
    }
    VectorXd y_res = foo(x, _new);
    ofstream out2;
    out2.open("Line.txt");
    for (int i = 0; i < x.size(); i++) {
        out2 << x[i] << " " << y_res[i] << endl;
    }
    out2.close();

}

VectorXd InitialPointY(VectorXd &x, VectorXd &b) {
    srand(time(0));
    VectorXd y = foo(x, b);
    for (int i = 0; i < y.size(); i++) {
        y[i] = y[i] + (rand() % 10) / 50.0;
    }
    return y;
}


MatrixXd Jacobian(VectorXd &x, VectorXd &b) {
    MatrixXd Jacobian(x.size(), b.size());
    Jacobian.setZero();
    VectorXd t(b.size());
    for (int i = 0; i < b.size(); i++) {
        t.setZero();
        t[i] = t[i] + epsil;
        VectorXd grad_a = b + t, grad_b = b - t;
        VectorXd res = (foo(x, grad_a) - foo(x, grad_b)).array() / (2 * epsil);
        Jacobian.col(i) = res;
    }
    return Jacobian;
}

void write_file(char *a) {
    ofstream out;
    out.open(a);
    out.close();
}


