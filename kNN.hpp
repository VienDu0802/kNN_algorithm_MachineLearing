#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

struct DistanceLabelPair
{
    double distance;
    int label;
    DistanceLabelPair(double dist, int lbl) : distance(dist), label(lbl) {}
};

struct LabelCount
{
    int label;
    int count;
    LabelCount(int l, int c) : label(l), count(c) {}
};

// void updateLabelCounts(DLinkedList<LabelCount> &labelCounts, int label);
// int findMostFrequentLabel(const DLinkedList<LabelCount> &labelCounts);

template <typename T>
class Node;
template<typename T>
class List {
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
};

template<typename T>
class DLinkedList : public List<T> {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;
public:
    DLinkedList();
    DLinkedList(const DLinkedList<T> &other);
    ~DLinkedList();

    void push_back(T value);
    void push_front(T value);
    void insert(int index, T value);
    string toString(int index) const;
    void remove(int index);
    T &get(int index) const;
    int size();
    int length() const;
    void clear();
    void print() const;
    void reverse();
    void sort();
};

class Point
{
private:
    DLinkedList<int> features;

public:
    Point(const DLinkedList<int> &features);
    int getFeature(int dimension) const;
    double distanceTo(const Point &other) const;
    int getDimensions() const;
};
class Dataset {
private:
    List<List<int>*>* data;
    List<string> *columnHeaders;
    //You may need to define more
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    List<string> *getColumnHeaders() const { return columnHeaders; }
    bool drop(int axis = 0, int index = 0, string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    List<List<int>*>* getData() const;
};

class kNN {
private:
    int k;
    //You may need to define more
    Dataset X_train, y_train;
    DLinkedList<Point> points;
    DLinkedList<int> labels;

public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    // void findKNearestPoints(const Point &point, DLinkedList<Point> &kNearestPoints);

    int predictLabelForPoint(const Point &point);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};

void train_test_split(Dataset& X, Dataset& y, double test_size, 
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed

template <typename T>
class Node
{
private:
    T value;
    Node *prev;
    Node *next;

public:
    Node(T val, Node *prev, Node *next);
    Node(T val);

    friend class DLinkedList<T>;
};
