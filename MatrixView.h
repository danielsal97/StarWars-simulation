//
// Created by daniel salame on 11/04/2024.
//

#ifndef FINELCPP_PROJECT_MATRIXVIEW_H
#define FINELCPP_PROJECT_MATRIXVIEW_H
#include <vector>
#include <string>

using namespace std;
class MatrixView {
public:
    static MatrixView& getInstance();
    void initialize(int rows, int cols) ;
    void printMatrix() ;
    void changeOrigin(double x, double y);
    void changeScale(int x);
    void changeSize(int x);
    void defaultView();

    MatrixView(const MatrixView&) = delete;
    MatrixView& operator=(const MatrixView&) = delete;


private:
    int scale;
    double originX, originY;
    std::vector<std::string> grid;
    MatrixView();  // Private constructor
    std::vector<std::vector<std::string>> matrix;
    int rows, cols, temp_x, temp_y;

};

#endif //FINELCPP_PROJECT_MATRIXVIEW_H
