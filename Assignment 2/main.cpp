#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;
class Node
{
typedef Node* NodePtr;
private:
    int data;
    NodePtr link;
public:
    Node();
    Node(const int &);
    Node(const Node &);
    int getData() const;
    NodePtr getLink() const;
    void setData(const int &);
    void setLink(const NodePtr &);
    friend ostream& operator << (ostream &, const Node &);
};
typedef Node* NodePtr;
Node::Node() : data(0), link(nullptr) {}
Node::Node(const int &d) : data(d), link(nullptr){}
Node::Node(const Node &n) : data(n.data), link(n.link){}
int Node::getData() const { return data; }
NodePtr Node::getLink() const { return link; }
void Node::setData(const int &d) { data = d; }
void Node::setLink(const NodePtr &p) { link = p; }
ostream& operator << (ostream& out, const Node& n)
{
    out << n.data;
    return out;
}
typedef Node* NodePtr;
class LinkedList
{
private:
    NodePtr head;
public:
    LinkedList(); //default constructor: assigns the head pointer member variable a nullptr value
    LinkedList(const LinkedList &); //copy constructor (deep copy)
    ~LinkedList(); //destructor (must delete all the nodes from the heap)
    LinkedList& operator= (const LinkedList &); //Assignment operator (deep copy)
    bool isEmpty() const; //return true if the length of the calling object is 0 and false otherwise
    NodePtr getHeadPtr() const; //return the head member variable of the calling object
    int getLength() const; //return the number of nodes in the calling object
    void head_insert(const int &); //as described in the supplementary material
    NodePtr search_node(const int &) const; //as described in the supplementary material
    void insert_after(const NodePtr &, const int &) cons(t); //as described in the supplementary material
    void remove_node(const NodePtr &); //as described in the supplementary material
    void remove_node(const int &); //as described in the supplementary material
    void remove_all(const int &); //as described in the supplementary material
    void tail_insert(const int &); //as described in the supplementary material
    void insert_before(const NodePtr &, const int &); //as described in the supplementary material
    friend ostream& operator << (ostream&, const LinkedList &); //Implemented for you
};

typedef Node* NodePtr;

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::LinkedList(const LinkedList& LL)
{
    NodePtr temp = LL.head;
    
    for(int i = 0; i < LL.getLength(); i++)
    {
        int a = temp->getData();
        
        this->tail_insert(a);
        
        temp = temp->getLink();
    }
}

LinkedList::~LinkedList()
{
    int length = this->getLength();
    
    for (int i = 0; i < length; i++)
    {
        NodePtr temp = head;
        head = head->getLink();
        delete temp;
    }
    head = nullptr;
}

LinkedList& LinkedList::operator=(const LinkedList& LL)
{
    this->~LinkedList();
    
    NodePtr temp = LL.head;
    
    for(int i = 0; i < LL.getLength(); i++)
    {
        int a = temp->getData();
        
        this->tail_insert(a);
        
        temp = temp->getLink();
    }
    
    return *this;
}

bool LinkedList::isEmpty() const
{
    if (head==nullptr)
    {
        return true;
    }
    return false;
}

NodePtr LinkedList::getHeadPtr() const
{
    return head;
}

int LinkedList::getLength() const
{
    int count = 0;
    NodePtr temp = head;
    
    while(temp != nullptr)
    {
        count++;
        temp = temp->getLink();
    }
    return count;
}

void LinkedList::head_insert(const int& a)
{
    NodePtr n = new Node(a);
    n->setLink(head);
    head = n;
}

NodePtr LinkedList::search_node(const int &a) const
{
    NodePtr temp = head;
    
    while(temp != nullptr)
    {
        if (temp->getData() == a)
            return temp;
        else
            temp = temp->getLink();
    }
    
    return nullptr;
}

void LinkedList::insert_after(const NodePtr& n, const int& value) const
{
    if (n == nullptr)
        return;
    else
    {
        NodePtr temp = new Node(value);
        temp->setLink(n->getLink());
        n->setLink(temp);
    }
}

void LinkedList::remove_node(const NodePtr& n)
{
    if (head == nullptr || n == nullptr)
        return;
    else if (head == n)
    {
        head = head->getLink();
        delete n;
        return;
    }
    else
    {
        NodePtr b = head;
        
        while (b != nullptr)
        {
            if (b->getLink() == n)
        {
            b->setLink(n->getLink());
            delete n;
            return;
        }
            b = b->getLink();
        }
    }
}

void LinkedList::remove_node(const int& value)
{
    NodePtr n = search_node(value);
    remove_node(n);
}

void LinkedList::remove_all(const int& value)
{
    NodePtr n;
    
    do
    {
        n = search_node(value);
        remove_node(n);
    }while (n != nullptr);
}

void LinkedList::tail_insert(const int& value)
{
    if (head == nullptr)
        head_insert(value);
    else
    {
        NodePtr b = head;
        
        while(b->getLink() != nullptr)
            b = b->getLink();
        
        insert_after(b, value);
    }
}

void LinkedList::insert_before(const NodePtr& n, const int& value)
{
    if (head == nullptr)
    {
        if (n == nullptr)
            head_insert(value);
        else
            cout << "Insertion failed. Bad node argument." << endl;
        return;
    }

    if (n == nullptr)
    {
        tail_insert(value);
        return;
    }

    if (head == n)
    {
        head_insert(value);
        return;
    }
    
    NodePtr b = head;
    
    while (b != nullptr)
    {
        if (b->getLink() == n)
            break;
        b = b->getLink();
    }
    if (b == nullptr)
        cout << "Insertion failed. Bad node argument." << endl;
    else
        insert_after(b, value);
}

ostream& operator << (ostream &out, const LinkedList &LL)
{
    if (LL.isEmpty())
        out << "EMPTY LINKED LIST";
    else
    {
        NodePtr temp = LL.head;
        while(temp != nullptr)
        {
            out << *temp << " ";
            temp = temp->getLink();
        }
    }
    return out;
}

/////////////////////////////////////////////////////////////////////////////

LinkedList computeUnsignedBinary(const int &num, const int &bit_pattern_size)
{
    /*
    This function first asserts that num is a non-negative integer and then computes and stores the unsigned binary representation of num in bit_pattern_size bits in a linked list object in such a way that the head node stores the most significant bit while the tail node stores the least significant bit. The function then returns the linked list object.
    */

    assert(num >= 0);

    //Put your remaining code here
    
    LinkedList answer;
    
    for(int i = 0; i < bit_pattern_size; i++)
    {
        int n = (num/(pow(2,i)));
            
        n = n%2;

        answer.head_insert(n);
    }
    return answer;
}

LinkedList computeSignAndMagnitudeBinary(const int &num, const int &bit_pattern_size)
{
    /*
    This function computes and stores the sign and magnitude binary representation of num in bit_pattern_size bits in a linked list object in such a way that the head node stores the most significant bit while the tail node stores the least significant bit. The function then returns then linked list object.
    */

    //Put your code here
    
    LinkedList s;

    int a = abs(num);
    
    for(int i = 0; i < bit_pattern_size-1; i++)
    {
        int n = (a/(pow(2,i)));
        
        n = n%2;
       
        s.head_insert(n);
    }

    if (num < 0)
        s.head_insert(1);
    if (num >= 0)
        s.head_insert(0);
    
    return s;
}

void flipBits(LinkedList &LL)
{
    /*
     This function flips the bits stored in the nodes of the linked list object parameter LL. Assume the data in each node of the linked list is a bit (0 or 1).
     */
    
    //Put your code here
    
    NodePtr temp = LL.getHeadPtr();
    
    for(int i = 0; i < LL.getLength(); i++)
    {
        if(temp->getData() == 0)
            temp->setData(1);
        else
            temp->setData(0);
        
        temp = temp->getLink();
    }
}

void reverse(LinkedList &LL)
{
    /*
    This function reverses the linked list object parameter LL. Reversing a linked list means the order of the nodes in the linked list is reversed.
    */

    //Put your code here
    
    if(LL.getHeadPtr() == nullptr)
        return;
    
    LinkedList temp;
    NodePtr t = LL.getHeadPtr();
    
    for(int i = 0; i < LL.getLength(); i++)
    {
        temp.head_insert(t->getData());
        t = t->getLink();
    }
    LL = temp;
}

LinkedList operator + (const LinkedList &LL1, const LinkedList &LL2)
{
    /*
    This function first asserts that the lengths of the linked list object parameters LL1 and LL2 are equal and then adds the bits in LL1 with the bits in LL2 the way we add binary numbers in mathematics. The function stores the sum in a linked list object and then returns the linked list object. Assume the data in each node of the linked lists is a bit (0 or 1).
    */

    assert(LL1.getLength() == LL2.getLength());

    //Put your remaining code here
    
    LinkedList s;
    int L = LL1.getLength();
    int carry = 0;
    
    NodePtr a = LL1.getHeadPtr();
    NodePtr b = LL2.getHeadPtr();
    
    LinkedList temp1;
    for(int i = 0; i < LL1.getLength();i++)
    {
        temp1.tail_insert(a->getData());
        a = a->getLink();
    }

    LinkedList temp2;
    for(int i =0; i < LL2.getLength(); i++)
    {
        temp2.tail_insert(b->getData());
        b = b->getLink();
    }
    
    reverse(temp1);
    reverse(temp2);
    
    NodePtr t1 = temp1.getHeadPtr();
    NodePtr t2 = temp2.getHeadPtr();
    
    for(int i = L-1; i >= 0; i--)
    {
    
                if(t1->getData()==1 && t2->getData()==1 && carry == 0)
                {
                    s.head_insert(0);
                    carry = 1;
                }
                
                else if(t1->getData()==1 && t2->getData()==1 && carry == 1)
                {
                    s.head_insert(1);
                    carry = 1;
                }
                
                else if(t1->getData()==1 && t2->getData()==0 && carry == 1)
                {
                    s.head_insert(0);
                    carry = 1;
                }
                
                else if(t1->getData()==1 && t2->getData()==0 && carry == 0)
                {
                    s.head_insert(1);
                    carry = 0;
                }
                
                else if(t1->getData()==0 && t2->getData()==1 && carry == 1)
                {
                    s.head_insert(0);
                    carry = 1;
                }
                
                else if(t1->getData()==0 && t2->getData()==1 && carry == 0)
                {
                    s.head_insert(1);
                    carry = 0;
                }
                
                else if(t1->getData()==0 && t2->getData()==0 && carry==1)
                {
                    s.head_insert(1);
                    carry = 0;
                }
                
                else if(t1->getData()==0 && t2->getData()==0 && carry==0)
                {
                    s.head_insert(0);
                    carry = 0;
                }
        t1 = t1->getLink();
        t2 = t2->getLink();
    }
    return s;
}

void addOne(LinkedList &LL)
{
    /*
    This function first asserts that the linked list object parameter LL is not empty and then adds 1 to the bits stored in the nodes of the linked list the way we add binary numbers in mathematics. Assume the data in each node of the linked list is a bit (0 or 1).
    */

    assert(!LL.isEmpty());

    //Put your remaining code here
    
    LinkedList t = LL;
    reverse(t);
    NodePtr temp = t.getHeadPtr();
    
    int carry = 1;
    for (int i = LL.getLength()-1; i >= 0; i--)
    {
        if (temp->getData() ==1 && carry == 1)
        {
            temp->setData(0);
            carry = 1;
        }
        
        else if (temp->getData() == 0 && carry == 1)
        {
            temp->setData(1);
            carry = 0;
        }
        temp = temp->getLink();
    }
    reverse(t);
    
    LL = t;
}

LinkedList computeTwosComplementBinary(const int &num, const int &bit_pattern_size)
{
    /*
    This function computes and stores the two's complement binary representation of num in bit_pattern_size bits in a linked list object in such a way that the head node stores the most significant bit while the tail node stores the least significant bit. The function then returns then linked list object.
    */

    //Put your code here
    
    LinkedList s;
    
    if(num >= 0)
        s = computeUnsignedBinary(num, bit_pattern_size);
    else
    {
        s = computeUnsignedBinary(abs(num), bit_pattern_size);
        flipBits(s);
        addOne(s);
    }
    return s;
}

int twosComplementBinaryToDecimal(const LinkedList &LL)
{
    /*
    This function first asserts that the linked list object parameter LL is not empty and then computes and returns the decimal value represented by the bits of the nodes of the linked list assuming two's complement binary representation. Assume the data in each node of the linked list is a bit (0 or 1).
    */

    assert(!LL.isEmpty());

    //Put your remaining code here
    
    int num = 0;
    int L = int (LL.getLength());
    
    NodePtr a = LL.getHeadPtr();
    
    LinkedList t;
    for(int i = 0; i < LL.getLength(); i++)
    {
        t.tail_insert(a->getData());
        a = a->getLink();
    }
    NodePtr temp = t.getHeadPtr();
    
    if (temp->getData()==0)
    {
        for(int i = 0,p = L-1; i<L; i++, p--)
        {
            int n = temp->getData();
            
            num += n*(pow(2,p));
            temp = temp->getLink();
        }
    }
    
    else
    {
        flipBits(t);
        addOne(t);
        
        temp = t.getHeadPtr();
        
        for(int i = 0,p = L-1; i<L; i++, p--)
        {
            int n = temp->getData();
            
            num += n*(pow(2,p));
            temp = temp->getLink();
        }
        num = -1*num;
    }
    return num;
}


int selectComputation()
{
    cout << "Select your computation" << endl;
    cout << "   1. Unsigned Binary Representation Computation" << endl;
    cout << "   2. Sign and Magnitude Representation Computation" << endl;
    cout << "   3. Two's Complement Representation Computation" << endl;
    cout << "   4. Exit Program" << endl;
    int selection;
    cout << "Enter your selection (1, 2, 3, or 4): ";
    cin >> selection;
    while (selection != 1 && selection != 2 && selection != 3 && selection != 4)
    {
        cout << "Please enter a correct choice: ";
        cin >> selection;
    }
    return selection;
}

int main()
{
    cout << "This program demonstrates the Linked List Data Structure in C++" << endl;
    cout << "Linked Lists will be used for numeric information representation using" << endl;
    cout << " *** Unsigned Binary Representation" << endl;
    cout << " *** Sign and Magnitude Binary Representation" << endl;
    cout << " *** Two's Complement Binary Representation" << endl << endl;
    cout << "In addition, the program demonstrates" << endl;
    cout << " *** Two's complement binary addition, and" << endl;
    cout << " *** Conversion from two's complement to decimal." << endl << endl;
    do
    {
        int selection = selectComputation();
        if (selection == 1)
        {
            int bit_pattern_size, num;
            cout << endl << "Enter a positive integer for the bit pattern size: ";
            cin >> bit_pattern_size;
            while (bit_pattern_size <= 0)
            {
                cout << "You must enter a positive integer. Enter again please: ";
                cin >> bit_pattern_size;
            }
            cout << "Enter a non-negative integer: ";
            cin >> num;
            while (num < 0)
            {
                cout << "You must enter a non-negative integer. Enter again please: ";
                cin >> num;
            }
            LinkedList LL = computeUnsignedBinary(num, bit_pattern_size);
            cout << "The unsigned binary representation of " << num << " in " << bit_pattern_size << " bit is " << LL << endl;
            cout << endl;
        }
        else if (selection == 2)
        {
            int bit_pattern_size, num;
            cout << endl << "Enter a positive integer for the bit pattern size: ";
            cin >> bit_pattern_size;
            while (bit_pattern_size <= 0)
            {
                cout << "You must enter a positive integer. Enter again please: ";
                cin >> bit_pattern_size;
            }
            cout << "Enter an integer: ";
            cin >> num;
            LinkedList LL = computeSignAndMagnitudeBinary(num, bit_pattern_size);
            cout << "The sign and magnitude binary representation of " << num << " in " << bit_pattern_size << " bit is " << LL << endl;
            cout << endl;
        }
        else if (selection == 3)
        {
            int bit_pattern_size, num1, num2;
            cout << endl << "Enter a positive integer for the bit pattern size: ";
            cin >> bit_pattern_size;
            while (bit_pattern_size <= 0)
            {
                cout << "You must enter a positive integer. Enter again please: ";
                cin >> bit_pattern_size;
            }
            cout << "Enter an integer: ";
            cin >> num1;
            LinkedList LL1 = computeTwosComplementBinary(num1, bit_pattern_size);
            cout << "The two's complement binary representation of " << num1 << " in " << bit_pattern_size << " bit is " << LL1 << endl;
            cout << endl;
            cout << "Enter a second integer: ";
            cin >> num2;
            LinkedList LL2 = computeTwosComplementBinary(num2, bit_pattern_size);
            cout << "The two's complement binary representation of " << num2 << " in " << bit_pattern_size << " bit is " << LL2 << endl;
            cout << endl;
            LinkedList LL3 = LL1 + LL2;
            cout << "The binary sum of " << LL1 << " and " << LL2 << " is " << LL3 << endl;
            int sum = twosComplementBinaryToDecimal(LL3);
            cout << "The integer value of the binary sum is " << sum << endl;
            if (sum == num1 + num2)
                cout << "This is a correct result." << endl;
            else
                cout << "This is not correct result because our bit pattern is too small to store the result." << endl;
        }
        else
            break;
        system("Pause");
        cout << endl << endl;
    }while (true);
    

    system("Pause");
    return 0;
}

