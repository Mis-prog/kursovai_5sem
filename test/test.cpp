#include "../googletest/googletest/include/gtest/gtest.h"
#include "../googletest/googlemock/include/gmock/gmock.h"
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

TEST(SuiteName, Test1) {

    vector<function<double(VectorXd &)>> foo_list;

    foo_list.emplace_back(foo_test_1);
    foo_list.emplace_back(foo_test_2);

    VectorXd y(2);
    get_y(foo_list, y);

    VectorXd x0(2);
    x0 << 1, 2;
    Function function(x0, x0.size());

    method_Neldera_and_Mida(function);

    VectorXd result(2);
    result << 0 ,0;


}

TEST(SuiteName, Test2) {

}

TEST(SuiteName, Test3) {

}