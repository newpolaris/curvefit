// https://himbopsa.tistory.com/13

#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/LU>

using namespace std;
using namespace Eigen;

int main() {
	float N; // the number of dataes
	ifstream file("data_150.txt");
	file >> N;
	float* data_x = new float[(int)N];
	float* data_y = new float[(int)N];
	for (int i = 0; i < N; i++) {
		file >> data_x[i] >> data_y[i];
		cout << data_x[i];
		cout << " " << data_y[i] << endl;
	}
	float Nx = 0, Nx2 = 0, Nx3 = 0, Nx4 = 0, Nx5 = 0, Nx6 = 0, y = 0, yx = 0, yx2 = 0, yx3 = 0;
	Matrix4d X;
	Matrix4d XI;
	Vector4d Y;
	Vector4d O;
	for (int i = 0; i < N; i++) {
		Nx += data_x[i];
		Nx2 += data_x[i] * data_x[i];
		Nx3 += data_x[i] * data_x[i] * data_x[i];
		Nx4 += data_x[i] * data_x[i] * data_x[i] * data_x[i];
		Nx5 += data_x[i] * data_x[i] * data_x[i] * data_x[i] * data_x[i];
		Nx6 += data_x[i] * data_x[i] * data_x[i] * data_x[i] * data_x[i] * data_x[i];
		y += data_y[i];
		yx +=  data_y[i] * data_x[i];
		yx2 += data_y[i] * data_x[i] * data_x[i];
		yx3 += data_y[i] * data_x[i] * data_x[i] * data_x[i];
	}
	X(0, 0) = Nx3; X(0, 1) = Nx2; X(0, 2) = Nx; X(0, 3) = N;
	X(1, 0) = Nx4; X(1, 1) = Nx3; X(1, 2) = Nx2; X(1, 3) = Nx;
	X(2, 0) = Nx5; X(2, 1) = Nx4; X(2, 2) = Nx3; X(2, 3) = Nx2;
	X(3, 0) = Nx6; X(3, 1) = Nx5; X(3, 2) = Nx4; X(3, 3) = Nx3;

	XI = X.inverse();

	Y[0] = y; Y[1] = yx; Y[2] = yx2; Y[3] = yx3;
	cout << X << endl;
	cout << Y << endl;
	O = XI * Y;

	cout << O[0] << "x3" << " + "   << O[1] << "x2"<< " + " << O[2] << "x1"<< " + " << O[3] << endl;
	file.close();
	ofstream result("3-dgree-regression_results.txt");
	for (int i = 0; i < N; i++) 
		result << round(0.033 * i * 1000) / 1000 << "\t" << O[0] * round(0.033 * i * 1000) / 1000 * round(0.033 * i * 1000) / 1000* round(0.033 * i * 1000) / 1000 +
			O[1] * round(0.033 * i * 1000) / 1000 * round(0.033 * i * 1000) / 1000 + O[2] * round(0.033 * i * 1000) / 1000+ O[3];
		result << endl;
	}
	result.close();
	return 0;
}
