
#include "Method_MelderaNida.h"

double foo(VectorXd x) {
    return 2.8 * x(1) * x(1) + 1.9 * x(0) + 2.7 * x(0) * x(0) + 1.6 - 1.9 * x(1);
}

void nodeFillCoef(const VectorXd &x0, int n, MatrixXd &node);

MatrixXd NodeFill(VectorXd x0) {
    int n = x0.size() - 1;
    MatrixXd node(n + 1, n + 1);
    node.setZero();
    x0(n) = foo(x0);
    node.row(0) = x0.transpose();
    nodeFillCoef(x0, n, node);
    return node;
}

void nodeFillCoef(const VectorXd &x0, int n, MatrixXd &node) {
    double a = ((sqrt(n + 1) - 1) / (n * sqrt(2))) * len_a;
    double b = ((sqrt(n + 1) + n - 1) / (n * sqrt(2))) * len_a;
    cout << "a=" << a << " b=" << b << endl;
    for (int i = 0; i < n; i++) {
        VectorXd x_cur(n + 1);
        x_cur.setZero();
        for (int j = 0; j < n; j++) {
            if (i == j) {
                x_cur(j) = x0(j) + a;
            } else {
                x_cur(j) = x0(j) + b;
            }
        }
        x_cur(n) = foo(x_cur);
        node.row(i + 1) = x_cur.transpose();
    }
}

VectorXd getMatrix(int n);

int set_n();

void Method_Main() {
    int n=set_n();
    VectorXd x0 = getMatrix(n);
    MatrixXd filledNode = NodeFill(x0);
    cout << "Матрица точек:\nx1\tx2\tf\n" << filledNode << "\n";
    cout << Center_Gravity(filledNode,n);
}

int set_n() {
    int n;
    cout << "Введите размерность пространства:";
    cin >> n;
    return n;
}

VectorXd Center_Gravity(MatrixXd &node,int n) {
    VectorXd cent_grav(n+1);
    cent_grav.setZero();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cent_grav(i) += node(j, i);
        }
        cent_grav(i) = cent_grav(i) / n;
    }
    cent_grav(n)=foo(cent_grav);
    return cent_grav;
}

MatrixXd Sort(MatrixXd &node,int n) {

}

VectorXd getMatrix(int n) {
    VectorXd x0(n + 1);
    x0.setZero();
    cout << "Введите координаты начальной точки:";
    for (int i = 0; i < n; i++) {
        cin >> x0(i);
    }
    return x0;
}

