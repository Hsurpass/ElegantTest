// #include <eigen3/Eigen/src/Core/Matrix.h>
#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <eigen3/Eigen/Dense>

using namespace std;

void cal_two_matrix_or_array_product()
{
    Eigen::Matrix3d matA, matB;
    Eigen::Array33d arrA, arrB;

    matA << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    matB = Eigen::Matrix3d::Identity(3, 3);
    cout << "matA:" << '\n' << matA << endl;
    cout << "matB:" << '\n' << matB << endl;

    arrA = matA.array();
    arrB = matB.array();
    cout << "arrA:" << '\n' << arrA << endl;
    cout << "arrB:" << '\n' << arrB << endl;

    /*
    1 2 3
    4 5 6
    7 8 9
    */
    cout << "matA * matB: "
         << "\n"
         << matA * matB << endl;
    // cout << "matA * arrB: " << matA * arrB << endl; // matrix 不能乘 数组
    /*
     1 2 3   1 0 0    1 0 0
     4 5 6 * 0 1 0 =  0 5 0
     7 8 9   0 0 1    0 0 9
    */
    cout << "arrA * arrB: "
         << "\n"
         << arrA * arrB << endl;
}

void cal_vector_transform()
{
    Eigen::Matrix3i mat;
    mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << mat << endl;

    Eigen::Vector3i vectorA, vectorB;
    vectorA << 1, 2, 3;
    cout << vectorA << endl;
    // vectorB << mat * vectorA;
    vectorB = mat * vectorA;
    /*
    [         [          [          [         [     [            [
      1 2 3     1         1          2         3      1+4+9       14
      4 5 6  *  2  =  1 * 4  +  2 *  5  + 3 *  6  =   4+10+18  =  32
      7 8 9     3         7          8         9      7+16+27     50
    ]         ]          ]          ]         ]     ]             ]
    */
    cout << vectorB << endl;
     // cout << mat * vectorA << endl;
}

void cal_vector_dot_product()
{
    Eigen::Matrix3i mat;
    mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;

    //  = {{1, 2, 3}, {4, 5, 6}, {}};
}

int main()
{
    cal_two_matrix_or_array_product();
    // cal_vector_transform();

    return 0;
}