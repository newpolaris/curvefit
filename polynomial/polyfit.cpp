#include <Eigen/Dense>
#include <Eigen/Dense>
#include <Eigen/LU>
#include <vector>
#include <stdio.h>
#include <math.h>

std::vector<float> polyfit(std::vector<float>& x, std::vector<float>& y, int order) {
    Eigen::MatrixXd A(x.size(), order+1);
    Eigen::VectorXd Y(y.size());

    Eigen::VectorXd coeff;

    assert(x.size() == y.size());
    assert(x.size() >= order+1);

    for (size_t i = 0; i < y.size(); i++)
        Y(i) = y[i];

    // create matrix
    for (size_t i = 0; i < x.size(); i++)
        for (size_t j = 0; j < order+1; j++)
            A(i, j) = pow(x[i], j);

    // solve for linear least squares fit
    coeff = A.householderQr().solve(Y);

    std::vector<float> result(order+1);
    for (size_t i = 0; i < order+1; i++)
        result[i] = coeff[i];
    return result;
}

float polyeval(std::vector<float>& coeffs, float x) {
    float result = 0.0;
    for (int i = 0; i < coeffs.size(); i++) {
        result += coeffs[i] * std::pow(x, i);
    }
    return result;
}

int main() {
    int num;
    FILE* input = fopen("data_150.txt", "r");
    fscanf(input, "%d", &num);
    std::vector<float> X(num);
    std::vector<float> Y(num);
    for (int i = 0; i < num; i++)
        fscanf(input, "%f %f", &X[i], &Y[i]);
    fclose(input);

    auto coeffs = polyfit(X, Y, 3);

    FILE* output = fopen("3-dgree-regression_results.txt", "w");
    for (float x = 0.f; x < 5.0; x += 0.1) {
        fprintf(output, "%f\t%f\n", x, polyeval(coeffs, x));
    }
    fclose(output);

    return 0;
}
