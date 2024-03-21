#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
std::ostream &operator<<(std::ostream &os, const DistanceLabelPair &dlp)
{
    return os << "Distance: " << dlp.distance << ", Label: " << dlp.label;
}

std::ostream &operator<<(std::ostream &os, const Point &point)
{
    os << "Point(";
    for (int i = 0; i < point.getDimensions(); ++i)
    {
        if (i > 0)
            os << ", ";
        os << point.getFeature(i);
    }
    os << ")";
    return os;
}

////////////////////////////////////////////////////////////////
//                        Class Point                         //
////////////////////////////////////////////////////////////////

Point::Point(const DLinkedList<int> &features) : features(features) {}

// Hiện thực phương thức getFeature
int Point::getFeature(int dimension) const
{
    if (dimension < 0 || dimension >= features.length())
    {
        throw out_of_range("Dimension out of range");
    }
    return features.get(dimension);
}

// Hiện thực phương thức distanceTo
double Point::distanceTo(const Point &other) const
{
    if (features.length() != other.features.length())
    {
        throw invalid_argument("Points must have the same number of dimensions");
    }
    double sumOfSquares = 0.0;
    for (int i = 0; i < features.length(); ++i)
    {
        int diff = features.get(i) - other.features.get(i);
        sumOfSquares += diff * diff;
    }
    return sqrt(sumOfSquares);
}

// Hiện thực phương thức getDimensions
int Point::getDimensions() const
{
    return features.length();
}

////////////////////////////////////////////////////////////////
//                        Class Node                          //
////////////////////////////////////////////////////////////////

template <typename T>
Node<T>::Node(T val) : value(val), prev(nullptr), next(nullptr) {}

template <typename T>
Node<T>::Node(T val, Node<T> *prevNode, Node<T> *nextNode) : value(val), prev(prevNode), next(nextNode) {}


////////////////////////////////////////////////////////////////
//                     Class DLinkedList                      //
////////////////////////////////////////////////////////////////

template <typename T>
DLinkedList<T>::DLinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &other) : List<T>(), head(nullptr), tail(nullptr), count(0)
{
    Node<T> *current = other.head;
    while (current != nullptr)
    {
        push_back(current->value);
        current = current->next;
    }
}

template <typename T>
DLinkedList<T>::~DLinkedList()
{
    clear();
}

template <typename T>
void DLinkedList<T>::push_back(T value) {
    Node<T>* newNode =new Node<T>(value);
    if (tail)
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = tail->next;
    }
    else
    {
        head = tail = newNode;
    }

    count++;
}

template <typename T>
void DLinkedList<T>::push_front(T value){
    Node<T>* newNode = new Node<T>(value);
    if(head){
        head->prev = newNode;
        newNode->next = head;
    }else{
        tail = newNode;
    }
    head = newNode;
    count++;
}

template <typename T>
void DLinkedList<T>::insert(int index, T value)
{
    if (index < 0 || index > count)
    {
        return;
    }
    else if (index == 0)
    {
        push_front(value);
    }
    else if (index == count)
    {
        push_back(value);
    }
    else
    {
        Node<T> *curr = head;
        Node<T> *newNode = new Node<T>(value);
        for (int i = 0; i < index - 1; i++)
        {
            curr = curr->next;
        }
        newNode->next = curr->next;
        newNode->prev = curr;
        curr->next = newNode;
        curr->next->prev = newNode;
        count++;
    }
}

template <typename T>
string DLinkedList<T>::toString(int index) const
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("Index out of range");
    }

    Node<T> *current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    std::stringstream ss;
    ss << current->value;
    return ss.str();
}

template <typename T>
void DLinkedList<T>::remove(int index)
{
    if (index < 0 || index >= count)
    {
        return;
    }

    Node<T> *curr = head;
    if (index == 0)
    {
        head = head->next;
        if (head)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }
    }
    else if (index == count - 1)
    {
        if (tail)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
    }
    else
    {
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        if (curr->next)
        {
            curr->next->prev = curr->prev;
        }
        else
        {
            tail = curr->prev;
        }
    }
    delete curr;
    count--;
}

template <typename T>
T &DLinkedList<T>::get(int index) const
{
    if(index < 0 || index >= count){
        throw out_of_range("get(): Out of range");
    }

    Node<T> *curr = head;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr->value;
}

template<typename T>
int DLinkedList<T>::size(){
    return count;
}

template <typename T>
int DLinkedList<T>::length() const {
    return count;
}

template <typename T>
void DLinkedList<T>::clear(){
    Node<T> *curr = head;
    while(curr != nullptr){
        Node<T> *next = curr->next;
        delete curr;
        curr = next;
    }
    head = tail = nullptr;
    count = 0;
}

template <typename T>
void DLinkedList<T>::print() const
{
    Node<T> *curr = head;
    while (curr != nullptr)
    {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;
}

template <typename T>
void DLinkedList<T>::reverse(){
    Node<T> *current = head;
    Node<T> *temp = nullptr;
    while (current != nullptr)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != nullptr)
    {
        head = temp->prev;
    }
}

template <typename T>
void DLinkedList<T>::sort()
{
    if (head == nullptr || head->next == nullptr)
        return;

    bool swapped;
    do
    {
        swapped = false;
        Node<T> *current = head;
        while (current->next != nullptr)
        {
            if (current->value.distance > current->next->value.distance)
            {
                std::swap(current->value, current->next->value);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

template <>
DLinkedList<Point>::~DLinkedList()
{
    clear();
}

////////////////////////////////////////////////////////////////
//                      Class Dataset                         //
////////////////////////////////////////////////////////////////

Dataset::Dataset() : data(new DLinkedList<List<int> *>()), columnHeaders(new DLinkedList<string>()) {}

Dataset::~Dataset()
{
    if (data)
    {
        data->clear();
        delete data;
    }
    if (columnHeaders)
    {
        columnHeaders->clear();
        delete columnHeaders;
    }
}

Dataset::Dataset(const Dataset &other) : data(new DLinkedList<List<int> *>())
{
    for (int i = 0; i < other.data->length(); ++i)
    {
        auto *otherRow = dynamic_cast<DLinkedList<int> *>(other.data->get(i));
        if (otherRow)
        {
            List<int> *newRow = new DLinkedList<int>(*otherRow); //Copy Constructor of DLinkedList
            data->push_back(newRow);
        }
    }
}

Dataset &Dataset::operator=(const Dataset &other)
{
    if (this != &other)
    {
        // delete curr data
        if (data)
        {
            data->clear();
            delete data;
            data = nullptr;
        }

        // copy data from other
        data = new DLinkedList<List<int> *>();
        for (int i = 0; i < other.data->length(); ++i)
        {
            auto *otherRow = dynamic_cast<DLinkedList<int> *>(other.data->get(i));
            if (otherRow)
            {
                List<int> *newRow = new DLinkedList<int>(*otherRow);
                data->push_back(newRow);
            }
        }
    }
    return *this;
}

bool Dataset::loadFromCSV(const char *fileName) {
    ifstream file(fileName);
    string line;
    bool isFirstRow = true;

    if (!file.is_open()) {
        return false;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string value;

        if (isFirstRow) {
            //
            while (getline(ss, value, ',')) {
                columnHeaders->push_back(value);
            }
            isFirstRow = false;
            continue; 
        }

        //handle data
        List<int> *row = new DLinkedList<int>();
        while (getline(ss, value, ',')) {
            try {
                int num = stoi(value);
                row->push_back(num);
            } catch (...) {
                //
            }
        }
        data->push_back(row);
    }
    return true;
}


void Dataset::printHead(int nRows, int nCols) const
{
    if (nRows < 0 || nCols < 0)
        return;

    // header label
    for (int i = 0; i < columnHeaders->length() && i < nCols; i++)
    {
        if (i > 0)
            cout << " ";
        cout << columnHeaders->get(i);
    }
    cout << endl; 

    // print data
    int rowsToPrint = std::min(nRows, data->length());
    for (int i = 0; i < rowsToPrint; i++)
    {
        List<int> *row = data->get(i);
        for (int j = 0; j < row->length() && j < nCols; j++)
        {
            if (j > 0)
                cout << " "; 
            cout << row->get(j);
        }
        if (i < rowsToPrint - 1)
            cout << endl;
    }
}

void Dataset::printTail(int nRows, int nCols) const
{
    int totalRows = data->length();
    int startRow = max(0, totalRows - nRows);

    // header label
    for (int j = max(0, columnHeaders->length() - nCols); j < columnHeaders->length(); ++j)
    {
        if (j > max(0, columnHeaders->length() - nCols))
            cout << " ";
        cout << columnHeaders->get(j);
    }
    cout << endl;

    for (int i = startRow; i < totalRows; ++i)
    {
        List<int> *row = data->get(i);
        for (int j = max(0, row->length() - nCols); j < row->length(); ++j)
        {
            if (j > max(0, row->length() - nCols))
                cout << " ";
            cout << row->get(j);
        }
        if (i < totalRows - 1)
            cout << endl;
    }
}

void Dataset::getShape(int &nRows, int &nCols) const
{
    nRows = data->length();                          
    nCols = (nRows > 0) ? data->get(0)->length() : 0; 
}

void Dataset::columns() const
{
    if (data->length() > 0)
    {
        DLinkedList<int> *header = dynamic_cast<DLinkedList<int> *>(data->get(0));
        if (header)
        {
            for (int i = 0; i < header->length(); i++)
            {
                if (i > 0)
                    cout << " ";
                cout << header->get(i); 
            }
            cout << endl;
        }
    }
}

void Dataset::addColumnHeader(string& headerName)
{
    this->columnHeaders->push_back(headerName);
}

DLinkedList<string> *Dataset::getColumnHeaders() const
{
    return columnHeaders;
}

bool Dataset::drop(int axis, int index, std::string columnName)
{
    if (axis == 0)
    {
        if (index < 0 || index >= data->length())
        {
            return false;
        }
        List<int> *row = data->get(index);
        delete row;
        data->remove(index);
        return true;
    }
    else if (axis == 1)
    {
        int colIndex = -1;
        for (int i = 0; i < columnHeaders->length(); ++i)
        {
            if (columnHeaders->get(i) == columnName)
            {
                colIndex = i;
                break;
            }
        }

        if (colIndex == -1)
        {
            return false;
        }

        for (int i = 0; i < data->length(); ++i)
        {
            DLinkedList<int> *row = dynamic_cast<DLinkedList<int> *>(data->get(i));
            if (row->length() > colIndex)
            {
                row->remove(colIndex);
            }
        }

        columnHeaders->remove(colIndex);
        return true;
    }
    return false;
}

//ver 1.0
// Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
// {
//     Dataset result;

//     for (int i = 0; i < this->columnHeaders->length(); ++i)
//     {
//         result.columnHeaders->push_back(this->columnHeaders->get(i));
//     }

//     if (endRow == -1)
//     {
//         endRow = data->length() - 1;
//     }
//     if (endCol == -1 && data->length() > 0)
//     {
//         endCol = data->get(0)->length() - 1;
//     }

//     for (int i = startRow; i <= endRow && i < data->length(); i++)
//     {
//         DLinkedList<int>* currentRow = static_cast<DLinkedList<int>*>(data->get(i));
//         DLinkedList<int> *newRow = new DLinkedList<int>();

//         for (int j = startCol; j <= endCol && j < currentRow->length(); j++)
//         {
//             newRow->push_back(currentRow->get(j));
//         }

//         result.data->push_back(newRow);
//     }

//     return result;
// }

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
{
    Dataset result;

    if (endRow == -1)
    {
        endRow = data->length() - 1;
    }
    if (endCol == -1)
    {
        endCol = data->get(0)->length() - 1;
    }

    for (int i = startRow; i <= endRow && i < data->length(); i++)
    {
        DLinkedList<int> *currentRow = static_cast<DLinkedList<int> *>(data->get(i));
        DLinkedList<int> *newRow = new DLinkedList<int>();

        for (int j = startCol; j <= endCol && j < currentRow->length(); j++)
        {
            newRow->push_back(currentRow->get(j));
        }

        result.data->push_back(newRow);
    }
    // Chỉ thêm tiêu đề cột khi trích xuất cột nhãn.
    if (startCol == 0 && endCol == 0)
    {
        result.columnHeaders->push_back("label");
    }
    return result;
}

List<List<int> *> *Dataset::getData() const
{
    return data;
}

////////////////////////////////////////////////////////////////
//                        Class kNN                           //
////////////////////////////////////////////////////////////////
kNN::kNN(int k) : k(k){}
void kNN::fit(const Dataset &X_train, const Dataset &y_train)
{
    // chuyen X_train va y_train ve DLinkedList dang string va int
    for (int i = 0; i < X_train.getData()->length(); ++i)
    {
        DLinkedList<int> *features = dynamic_cast<DLinkedList<int> *>(X_train.getData()->get(i));
        Point p(*features);
        points.push_back(p); // luu tru cac diem data

        int label = y_train.getData()->get(i)->get(0);
        labels.push_back(label); // luu nhan tuong ung
    }
}

Dataset kNN::predict(const Dataset &X_test)
{
    Dataset y_pred;
    
    for (int i = 0; i < X_test.getData()->length(); ++i)
    {
        DLinkedList<int> *testFeatures = dynamic_cast<DLinkedList<int> *>(X_test.getData()->get(i));
        Point testPoint(*testFeatures);
        int predictedLabel = predictLabelForPoint(testPoint);

        DLinkedList<int> *predictedRow = new DLinkedList<int>();
        predictedRow->push_back(predictedLabel);
        y_pred.getData()->push_back(predictedRow);
    }

    y_pred.getColumnHeaders()->push_back("label");
    return y_pred;
}


int kNN::predictLabelForPoint(const Point &point)
{
    DLinkedList<DistanceLabelPair> distanceLabelPairs;

    // cal distance and add to list
    for (int i = 0; i < points.length(); i++)
    {
        double dist = point.distanceTo(points.get(i));
        int label = labels.get(i);
        distanceLabelPairs.push_back(DistanceLabelPair(dist, label));
    }

    // re-arrange by distance 
    distanceLabelPairs.sort();

    int labelCounts[10] = {0}; // suppose has 10 diff labels
    for (int i = 0; i < k && i < distanceLabelPairs.length(); i++)
    {
        int lbl = distanceLabelPairs.get(i).label;
        labelCounts[lbl]++;
    }

    int maxCount = 0, mostFrequentLabel = -1;
    for (int i = 0; i < 10; i++)
    {
        if (labelCounts[i] > maxCount)
        {
            maxCount = labelCounts[i];
            mostFrequentLabel = i;
        }
    }

    return mostFrequentLabel;
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    // So sanh du doan voi thuc te de tinh do chinh xac........
    int correctPredictions = 0;
    for (int i = 0; i < y_test.getData()->length(); ++i)
    {
        int trueLabel = y_test.getData()->get(i)->get(0);
        int predictedLabel = y_pred.getData()->get(i)->get(0);
        if (trueLabel == predictedLabel)
        {
            correctPredictions++;
        }
    }
    return static_cast<double>(correctPredictions) / y_test.getData()->length();
}

//////////////////////////////////////////
//////////////////////////////////////////
void train_test_split(Dataset &X, Dataset &y, double test_size, Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test)
{
    int totalRows = X.getData()->length();

    int testRows = static_cast<int>(ceil(totalRows * test_size));
    int trainRows = totalRows - testRows;

    X_train = X.extract(0, trainRows - 1);
    X_test = X.extract(trainRows, totalRows - 1);
    y_train = y.extract(0, trainRows - 1);
    y_test = y.extract(trainRows, totalRows - 1);
    y_test.getColumnHeaders()->push_back("label");
}