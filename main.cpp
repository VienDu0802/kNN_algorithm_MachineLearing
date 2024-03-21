#include "kNN.hpp"

void tc1(){
    // Dataset dataset;
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
    // row->insert(0, 1);
    // row->print();

    // Dataset dataset;
    // dataset.loadFromCSV("mnist.csv");
    // int nRows, nCols;

    // kNN knn;
    // Dataset feature = dataset.extract(0, -1, 1, -1);
    // Dataset label = dataset.extract(0, -1, 0, 0);
    // feature.getShape(nRows, nCols);
    // cout << "Feature shape: " << nRows << "x" << nCols << endl;
    // label.getShape(nRows, nCols);
    // cout << "Label shape: " << nRows << "x" << nCols << endl;

    // Dataset dataset;
    // dataset.loadFromCSV("mnist.csv");
    // int nRows, nCols;

    // kNN knn;
    // Dataset X_train, X_test, y_train, y_test;
    // Dataset feature = dataset.extract(0, -1, 1, -1);
    // Dataset label = dataset.extract(0, -1, 0, 0);

    // train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    // X_train.getShape(nRows, nCols);
    // cout << "X_train shape: " << nRows << "x" << nCols << endl;
    // X_test.getShape(nRows, nCols);
    // cout << "X_test shape: " << nRows << "x" << nCols << endl;
    // y_train.getShape(nRows, nCols);
    // cout << "y_train shape: " << nRows << "x" << nCols << endl;
    // y_test.getShape(nRows, nCols);
    // cout << "y_test shape: " << nRows << "x" << nCols << endl;

    //tc5 sai
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;

    //extra tc
    // int nRows, nCols;
    // Dataset dataset;
    // dataset.loadFromCSV("mnist.csv");
    // Dataset dataset2 = Dataset(dataset);
    // bool result = dataset2.drop(0, 4);
    // cout << "Drop(0, 4) result: " << result << endl;
}

int main() {
    tc1();
    return 0;
}