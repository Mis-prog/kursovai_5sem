#include "Method_NewtonAndGauss.h"


void print_point(VectorXd &x_i);

double foo(VectorXd &b, VectorXd &ak, VectorXd &sk, MatrixXd &bk) {
    double res = 0;
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        res += ak[i] * exp(static_cast<double>(-((b - bk.col(i)).norm() * (b - bk.col(i)).norm()) / sk[i]));
    }
    res += (rand() % 10) / 8.0;
    return res;
}

void print_node(const MatrixXd &node_x);

void method_NewtonandGauss() {
    MatrixXd B(50, 3);
    B.col(0) = VectorXd::LinSpaced(50, 1, 3);
    B.col(1) = VectorXd::LinSpaced(50, 3, 5);
    B.col(2) = VectorXd::LinSpaced(50, 2, 4);
    VectorXd ak = VectorXd::Random(4);
    VectorXd sk = VectorXd::Random(4);
    MatrixXd bk = MatrixXd::Random(3, 4);
    VectorXd y = InitialPointY(B, ak, sk, bk);
    VectorXd old(3), _new(3);
    old << 1, 1, 1;
    _new << 1, 1, 1;
    for (int i = 0; i < maxIter; i++) {
        old = _new;
        MatrixXd J = Jacobian(B, ak, sk, bk);
        VectorXd dy = y.array() - foo(old, ak, sk, bk);
        _new = old + (J.transpose() * J).inverse() * J.transpose() * dy;
        if ((old - _new).norm() < epsil) {
            break;
        }
    }
}

VectorXd InitialPointY(MatrixXd &B, VectorXd &ak, VectorXd &sk, MatrixXd &bk) {
    VectorXd y(50);
    for (int i = 0; i < 50; i++) {
        VectorXd cur = B.row(i);
        y(i) = foo(cur, ak, sk, bk);
    }
    return y;
}


MatrixXd Jacobian(MatrixXd &b, VectorXd &ak, VectorXd &sk, MatrixXd &bk) {
    MatrixXd Jacobian(b.rows(), b.cols());
    Jacobian.setZero();
    VectorXd t(b.cols()), res_v(b.cols());
    for (int i = 0; i < b.rows(); i++) {
        res_v.setZero();
        for (int j = 0; j < b.cols(); j++) {
            t.setZero();
            t[i] = t[i] + epsil;
            VectorXd grad_a = b.row(i) + t, grad_b = b.row(i) - t;
            double res = (foo(grad_a, ak, sk, bk) - foo(grad_b, ak, sk, bk)) / (2 * epsil);
            res_v(j) = res;
        }
        Jacobian.row(i) = res_v.transpose();
    }
    return Jacobian;
}

void write_file(char *a) {
    ofstream out;
    out.open(a);
    out.close();
}


