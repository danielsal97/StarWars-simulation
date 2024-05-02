//
// Created by daniel salame on 11/04/2024.
//

#include "MatrixView.h"
#include <iostream>
#include <iomanip>
#include "Model.h"
MatrixView::MatrixView() : scale(2), originX(0.00), originY(0.00), rows(25), cols(25){
    initialize(rows, cols);
   temp_x= static_cast<int>(originX);
   temp_y= static_cast<int>(originY);
}

MatrixView& MatrixView::getInstance() {
    static MatrixView instance;
    return instance;
}

void MatrixView::initialize(int rowsNum, int colsNum)  {
    this->rows = rowsNum;
    this->cols = colsNum;
    matrix.resize(rows, std::vector<std::string>(cols, "."));

}


void MatrixView::changeOrigin(double x, double y){
    temp_x = x;
    temp_y = y;
}
void MatrixView::changeScale(int x) {
    scale = x;
}
void MatrixView::changeSize(int x){
    initialize(x,x);
}
void MatrixView::defaultView(){
    rows = 25;
    cols = 25;
    scale =2;
    temp_x =0;
    temp_y = 0;

}
void MatrixView::printMatrix()  {
    for (int i =0 ; i< rows;i++){
        for (int j=0; j< cols; j++){
            matrix[i][j] = '.';
        }
    }
    std::cout << "Display size: " << rows
              << ", scale: " << static_cast<double>(scale)
              << " , origin: (" << static_cast<double>(temp_x)
              << ", " << static_cast<double>(temp_y) << ")" << std::endl;
    Model &a = Model::getInstance();
    for (auto const &fortress : a.fortress){
        auto cords = fortress.second->getCords();
            if (cords.second >= temp_y && cords.first >= temp_x)
            matrix[static_cast<int>(cords.second- temp_y)/scale ][static_cast<int>(cords.first- temp_x)/scale ] = fortress.second->getName().substr(0, 2);

    }
    for(auto const &station: a.stations){
        auto cords = station.second->getCords();
        if (cords.second >= temp_y && cords.first >= temp_x)

            matrix[static_cast<int>(cords.second- temp_y)/scale ][static_cast<int>(cords.first- temp_x)/scale ] = station.second->getName().substr(0, 2);
    }
    for(auto const &shuttle: a.shuttles){
        auto cords = shuttle.second->getCords();
        if (cords.second >= temp_y && cords.first >= temp_x)

        matrix[static_cast<int>(cords.second- temp_y)/scale ][static_cast<int>(cords.first- temp_x)/scale ] = shuttle.second->getName().substr(0, 2);
    }
    for(auto const &bomber: a.bombers){
        auto cords = bomber.second->getCords();
        if (cords.second >= temp_y && cords.first >= temp_x)

        matrix[static_cast<int>(cords.second- temp_y)/scale ][static_cast<int>(cords.first- temp_x)/scale ] = bomber.second->getName().substr(0, 2);
    }
    for(auto const &destroyer: a.destroyers){
        auto cords = destroyer.second->getCords();
        if (cords.second >= temp_y && cords.first >= temp_x)

        matrix[static_cast<int>(cords.second- temp_y)/scale ][static_cast<int>(cords.first- temp_x)/scale ] = destroyer.second->getName().substr(0, 2);
    }
    for(auto const &falcon: a.falcons){
        auto cords = falcon.second->getCords();
        if (cords.second >= temp_y && cords.first >= temp_x)

            matrix[static_cast<int>(cords.second- temp_y)/scale ][static_cast<int>(cords.first- temp_x)/scale ] = falcon.second->getName().substr(0, 2);
    }
    // Assume maxElementWidth is the maximum width of elements in the matrix for alignment
    int maxElementWidth = 2; // This should be calculated based on actual matrix contents
    string id ="DS";

    // Print the matrix with row labels
    for (int y = rows - 1; y >= 0; --y) {
        if((y*scale)%3 == 0) {
            std::cout << std::setw(4) << y * scale + temp_y<< " ";
        }
        else{
            cout<<" "<<std::setw(4)<<" ";
        }

        for (int x = 0; x < cols; ++x) {
            std::cout << std::setw(maxElementWidth +1) << matrix[y][x];
        }
        std::cout << std::endl;
    }

    // Print the column labels
    std::cout << std::setw(5) << "";
    for (int x = 0; x < cols; ++x) {
        if((x*scale)%3 ==0) {
            std::cout<<" "<< std::setw(2) << x * scale + temp_x ;
        }
        else{
            cout<<" "<<std::setw(2)<<"";
        }
    }
    std::cout << std::endl;
}