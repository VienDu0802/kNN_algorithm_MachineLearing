#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

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
        throw out_of_range("Invalid index");
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
        throw out_of_range("Invalid index");
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
void DLinkedList<T>::print() const {
    Node<T> *curr = head;
    bool isFisrt = true;
    while(curr!=nullptr){
        if(!isFisrt){
            cout<<" ";
        }else{
            isFisrt = false;
        }
        cout << curr->value;
        curr = curr->next;
    }
    // cout << endl;
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


////////////////////////////////////////////////////////////////
//                      Class Dataset                         //
////////////////////////////////////////////////////////////////

Dataset::Dataset()
{
    data = new DLinkedList<List<int> *>();
}

Dataset::~Dataset() {
    if(data) {
        data->clear();
        delete data;
        data = nullptr;
    } 
}

Dataset::Dataset(const Dataset &other) : data(new DLinkedList<List<int> *>())
{
    for (int i = 0; i < other.data->length(); ++i)
    {
        // Cần đảm bảo rằng other.data->get(i) trả về một DLinkedList<int>, không phải List<int>.
        auto *otherRow = dynamic_cast<DLinkedList<int> *>(other.data->get(i));
        if (otherRow)
        {
            List<int> *newRow = new DLinkedList<int>(*otherRow); // Sử dụng Copy Constructor của DLinkedList
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

bool Dataset::loadFromCSV(const char *fileName)
{
    ifstream file(fileName);
    if (!file)
        return false;

    string line;
    while (getline(file, line))
    {
        istringstream stream(line);
        List<int> *row = new DLinkedList<int>();
        string value;

        while (getline(stream, value, ','))
        {
            row->push_back(stoi(value));
        }

        data->push_back(row);
    }
    return true;
}

void Dataset::printHead(int nRows, int nCols) const
{
    int rowsToPrint = min(nRows, data->length());
    for (int i = 0; i < rowsToPrint; i++)
    {
        DLinkedList<int> *row = dynamic_cast<DLinkedList<int> *>(data->get(i));
        if (row != nullptr)
        {
            int colsToPrint = min(nCols, row->length());
            for (int j = 0; j < colsToPrint; j++)
            {
                if (j > 0)
                    cout << " ";
                cout << row->get(j);
            }
            cout << endl;
        }
    }
}

void Dataset::printTail(int nRows, int nCols) const
{
    int rowsToPrint = min(nRows, data->length());
    for (int i = data->length() - rowsToPrint; i < data->length(); i++)
    {
        DLinkedList<int> *row = dynamic_cast<DLinkedList<int> *>(data->get(i));
        if (row != nullptr)
        {
            int colsToPrint = min(nCols, row->length());
            for (int j = 0; j < colsToPrint; j++)
            {
                if (j > 0)
                    cout << " ";
                cout << row->get(j);
            }
            cout << endl;
        }
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

bool Dataset::drop(int axis, int index, std::string columnName)
{
    if (axis == 0)
    {
        if (index < 0 || index >= data->length())
            return false;

        List<int> *row = data->get(index);
        delete row;
        data->remove(index);
        return true;
    }
    else if (axis == 1)
    {
        int colIndex = -1;
        DLinkedList<int> *headerRow = dynamic_cast<DLinkedList<int> *>(data->get(0));
        for (int i = 0; i < headerRow->length(); ++i)
        {
            std::stringstream ss;
            ss << headerRow->get(i);
            if (ss.str() == columnName)
            {
                colIndex = i;
                break;
            }
        }

        if (colIndex == -1)
            return false;

        for (int i = 1; i < data->length(); ++i)
        {
            DLinkedList<int> *row = dynamic_cast<DLinkedList<int> *>(data->get(i));
            row->remove(colIndex);
        }
        headerRow->remove(colIndex);
        return true;
    }
    return false;
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
{
    Dataset result;

    if (endRow == -1)
    {
        endRow = data->length() - 1;
    }
    if (endCol == -1 && data->length() > 0)
    {
        endCol = data->get(0)->length() - 1;
    }

    for (int i = startRow; i <= endRow && i < data->length(); i++)
    {
        DLinkedList<int> *currentRow = dynamic_cast<DLinkedList<int> *>(data->get(i));
        DLinkedList<int> *newRow = new DLinkedList<int>();

        for (int j = startCol; j <= endCol && j < currentRow->length(); j++)
        {
            newRow->push_back(currentRow->get(j));
        }

        result.data->push_back(newRow);
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
void kNN::fit(const Dataset &X_train, const Dataset &y_train)
{
    this->X_train = X_train;
    this->y_train = y_train;
}

Dataset kNN::predict(const Dataset& X_test){
    Dataset y_pred;
    //tinh toan khoang cach va chon k gan nhat
    //
    //
    //
    return y_pred;
}