#include <iostream>
#include <string>
#include <ctime>
#include <cassert>

using namespace std;

template <class T>
class SmarterArray
{
private:
    T *A;
    int size;

public:
    //Constructors
    SmarterArray();
    SmarterArray(const T *A, const int &size);
    SmarterArray(const SmarterArray<T> &L); //Copy constructor
    //Assignment operator
    SmarterArray<T>& operator = (const SmarterArray<T> &L);
    //Destructor
    ~SmarterArray();
    //Getters, Setters, operators and other functions
    int getSize() const;
    T& operator[](const int &index) const;
    int find(const T &e) const;
    void append(const T &e);
    bool remove(const T &e);
    SmarterArray<T> operator - (const SmarterArray<T> &L) const;
    //Friend functions need to be explicitely shown as templated even inside the class declaration
    template<class T1> //Some compilers require a different template name
    friend ostream& operator << (ostream &cout, const SmarterArray<T1> &L);
};

template <class T>
SmarterArray<T>::SmarterArray()
{
    this->size = 0;
}

template <class T>
SmarterArray<T>::SmarterArray(const T *A, const int &size)
{
    if (size > 0)
    {
        this->size = size;
        this->A = new T[this->getSize()];
        for (int i = 0; i < this->getSize(); i++)
            this->A[i] = A[i];
    }
    else
        this->size = 0;
}

template <class T>
SmarterArray<T>::SmarterArray(const SmarterArray<T> &L) //Copy constructor
{
    this->size = L.getSize();
    if (this->getSize() > 0)
    {
        this->A = new T[this->getSize()];
        for (int i = 0; i < this->getSize(); i++)
            this->A[i] = L[i];
    }
}

template <class T>
SmarterArray<T>& SmarterArray<T> :: operator = (const SmarterArray<T> &L)
{
    //Check for self asssignment. If so, do  nothing.
    if (this == &L)
        return *this;
    //Delete the left hand side object's memory
    this->~SmarterArray();
    //Now copy the right hand side to the left
    this->size = L.getSize();
    if (this->getSize() > 0)
    {
        this->A = new T[this->getSize()];
        for (int i = 0; i < this->getSize(); i++)
            this->A[i] = L[i];
    }
    return *this;
}

template <class T>
SmarterArray<T>::~SmarterArray()
{
    if (this->getSize() > 0)
    {
        delete[] this->A;
        this->size= 0;
    }
}

template <class T>
int SmarterArray<T>::getSize() const
{
    return this->size;
}

template <class T>
T& SmarterArray<T>::operator[](const int &index) const
{
    if (index < 0 && index >= this->getSize())
    {
        cout << "ERROR! Index out of bounds." << endl;
        abort();
    }
    return this->A[index];
}

template <class T>
int SmarterArray<T>::find(const T &e) const
{
    for (int i = 0; i < this->getSize(); i++)
        if (this->A[i] == e)
            return i;    //return index if found
    return -1;    //return -1 to mean not found
}

template <class T>
void SmarterArray<T>::append(const T &e)
{
    //First create a temporary array whose size is this->size+1
    T *temp = new T[this->getSize() + 1];

    //Copy the elements of this->A to temp
    for (int i = 0; i < this->getSize(); i++)
        temp[i] = this->A[i];

    //Copy the element to be appended to temp
    temp[this->getSize()] = e;

    //Delete the existing array this->A
    if (this->getSize() > 0)
        delete[] this->A;

    //Make the array this->A to point to temp and increment the size
    this->A = temp;
    this->size += 1;
}

template <class T>
bool SmarterArray<T>::remove(const T &e)
{
    int index = this->find(e);
    if (index == -1)
        return false;
    else if (this->getSize() == 1)//only one element in the *this object
    {
        delete[] this->A;
        this->size = 0;
        return true;
    }
    else
    {
        //First create a temporary array whose size is this->size-1
        T *temp = new T[this->getSize() - 1];
        //Copy the elements of this->A to temp except the element at index
        for (int i = 0; i < index; i++)
            temp[i] = this->A[i];
        for (int i = index+1; i < this->getSize(); i++)
            temp[i-1] = this->A[i];
        //Delete the existing array this->A
        delete[] this->A;
        //Make the array this->A to point to temp and decrement the size
        this->A = temp;
        this->size -= 1;
        return true;
    }
}

template <class T>
SmarterArray<T> SmarterArray<T>::operator - (const SmarterArray<T> &L) const
{
    //Returns the elements of this that are not found in L
    SmarterArray<T> A;
    for (int i = 0; i < this->getSize(); i++)
    {
        int index = L.find(this->A[i]);
        if (index == -1)
            A.append(this->A[i]);
    }
    return A;
}

template <class T1>
ostream& operator << (ostream &cout, const SmarterArray<T1> &L)
{
    cout << "[";
    for (int i = 0; i < L.getSize() - 1; i++)
        cout << L[i] << ", ";
    if (L.getSize() > 0)
        cout << L[L.getSize() - 1];
    cout << "]";
    return cout;
}

template <class K, class V>
class Map
{
private:
    SmarterArray<K> A1;    //The keys of the map
    SmarterArray<V> A2;    //The values of the map
    
public:
    //Constructors
    Map(); //Default constructor
    Map(const Map<K, V>&); //Copy constructor. Deep copy.

    //Assignment operator
    Map<K, V>& operator = (const Map<K, V>&); //Assignment operator. Memory clean up and deep copy.

    //Destructor
    ~Map(); //Destructor.

    //Getters, Setters, operators and other functions
    int getSize() const; //Return the size of the map
    int findKey(const K&) const; //Return the index of the first element of the Keys array == the argument. Return -1 if not found.
    int findValue(const V&) const; //Return the index of the first element of the Values array == the argument. Return -1 if not found.
    K getKey(const V&) const; //Assert the argument is found in the Values array and then return the first key with the given value
    V getValue(const K&) const; //Assert the argument is found in the Keys array and then return the first value with the given key
    K getKeyAtIndex(const int&) const; //Assert the index argument and then return the key at the given index
    V getValueAtIndex(const int&) const; //Assert the index argument and then return the value at the given index
    void setKeyAtIndex(const int&, const K&); //Assert the index argument and then set the key at the given index
    void setValueAtIndex(const int&, const V&); //Assert the index argument and then set the value at the given index
    void append(const K&, const V&); //Append the key-value pair to the calling object

    template <class K1, class V1>
    friend ostream& operator << (ostream&, const Map<K1, V1>&); //Output streaming operator
};

template <class K, class V>
Map<K, V>::Map()
{
    //No code is needed here.
    //The member variables will automatically be initialized as default objects
}

template <class K, class V>
Map<K, V>::Map(const Map<K, V>& M)
{
    A1 = M.A1;
    A2 = M.A2;
}
template <class K, class V>
Map<K, V>& Map<K, V>::operator = (const Map<K, V>& M)
{
    A1 = M.A1;
    A2 = M.A2;
    return *this;
}
template <class K, class V>
Map<K, V>::~Map()
{
    A1.~SmarterArray();
    A2.~SmarterArray();
}
template <class K, class V>
int Map<K, V>::getSize() const
{
    return A1.getSize();
}
template <class K, class V>
int Map<K, V>::findKey(const K& key) const
{
    return A1.find(key);
}
template <class K, class V>
int Map<K, V>::findValue(const V& value) const
{
    return A2.find(value);
}
template <class K, class V>
K Map<K, V>::getKey(const V& value) const
{
    int index = A2.find(value);
    assert(index != -1);
    return A1[index];
}
template <class K, class V>
V Map<K, V>::getValue(const K& key) const
{
    int index = A1.find(key);
    assert(index != -1);
    return A2[index];
}
template <class K, class V>
K Map<K, V>::getKeyAtIndex(const int& index) const
{
    assert(index >= 0 && index < A1.getSize());
    return A1[index];
}
template <class K, class V>
V Map<K, V>::getValueAtIndex(const int& index) const
{
    assert(index >= 0 && index < A2.getSize());
    return A2[index];
}
template <class K, class V>
void Map<K, V>::setKeyAtIndex(const int& index, const K& key)
{
    assert(index >= 0 && index < A1.getSize());
    A1[index] = key;
}
template <class K, class V>
void Map<K, V>::setValueAtIndex(const int& index, const V& value)
{
    assert(index >= 0 && index < A2.getSize());
    A2[index] = value;
}
template <class K, class V>
void Map<K, V>::append(const K& key, const V& value)
{
    A1.append(key);
    A2.append(value);
}
template <class K1, class V1>
ostream& operator << (ostream& cout, const Map<K1, V1>& m)
{
    if (m.getSize() == 0)
        cout << "[Empty Map]" << endl;
    else
    {
        cout << endl;
        cout << "Keys \t\t Values" << endl;
        cout << "==== \t\t ======" << endl;
        for (int i = 0; i < m.getSize(); i++)
            cout << m.A1[i] << "\t\t" << m.A2[i] << endl;
    }
    return cout;
}

template <class T>
int getCount(const SmarterArray<T>& A, const T& a)
{
    int count = 0;
    
    for (int i = 0; i < A.getSize(); i++)
        if(A[i] == a)
            count++;
    
    return count;
}

Map<char, int> distinctCharsFrequencyMap(const SmarterArray<char>& A)
{
    Map<char, int> answer;
    int index = 0;
    
    for (int i = 0; i < A.getSize(); i++)
    {
        if(answer.findKey(A[i])== -1)
        {
            answer.append(A[i], 0);
            index++;
        }
    }
    
    for(int i = 0; i < answer.getSize(); i++)
    {
        answer.setValueAtIndex(i, getCount(A, answer.getKeyAtIndex(i)));
    }
    
    return answer;
}


int main()
{
    srand(time(0));
    SmarterArray<char> A;
    for (int i = 0; i < 100; i++)
    {
        char ch = rand() % 10 + 'a';
        A.append(ch);
    }
    cout << "The elements of the array are " << A << endl;
    Map<char, int> M;
    M = distinctCharsFrequencyMap(A);
    cout << "The map is " << M << endl;
    system("Pause");
    return 0;
}
