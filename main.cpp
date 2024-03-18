#include "kNN.hpp"

void tc1(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    dataset.printHead(10, 10);
    cout << endl;
    dataset.printTail(10, 10);
    cout << endl;
    int nRows, nCols;
    dataset.getShape(nRows, nCols);
    cout << "Shape: " << nRows << "x" << nCols << endl;

    //     Dataset dataset;
    // dataset.loadFromCSV("mnist.csv");
    // dataset.printHead(10, 10);
    // cout << endl;
    // dataset.printTail(10, 10);
    // cout << endl;
    // int nRows, nCols;
    // dataset.getShape(nRows, nCols);
    // cout << "Shape: " << nRows << "x" << nCols << endl;

    // Dataset dataset;
    // dataset.loadFromCSV("mnist.csv");
    // List<int> *row = dataset.getData()->get(0);
    // for (int j = 0; j < 35; j++)
    // {
    //     for (int i = 0; i < 10000000; i++)
    //     {
    //         row->insert(0, 1);
    //     }
    //     for (int i = 0; i < 10000000; i++)
    //     {
    //         row->remove(0);
    //     }
    // }
    // cout << row->length();
}

int main() {
    tc1();
    return 0;
}