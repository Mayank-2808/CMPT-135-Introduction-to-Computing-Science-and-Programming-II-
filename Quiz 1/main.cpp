#include <iostream>
#include <cmath>
using namespace std;

class Ellipse{
private:
    double minorAxis, majorAxis;
    
public:
    //Constructors
    Ellipse();
    Ellipse(const double&, const double&);
    Ellipse(const Ellipse&);
    
    //Getters
    double getMinorAxis() const;
    double getMajorAxis() const;
    
    //Setters
    void setMinorAxis(const double&);
    void setMajorAxis(const double&);
    
    //Additional member functions
    double getArea() const;
    double getPerimeter() const;
    void printInfo(ostream&) const;
    
    //Friend functions
    friend ostream& operator << (ostream&, const Ellipse&);
};

Ellipse::Ellipse() : majorAxis(1), minorAxis(0.5) {}
Ellipse::Ellipse(const double &_major, const double &_minor)
: majorAxis(_major), minorAxis(_minor) {}
Ellipse::Ellipse(const Ellipse &e) : majorAxis(e.majorAxis), minorAxis(e.minorAxis) {}

double Ellipse::getMinorAxis() const {return minorAxis;}
double Ellipse::getMajorAxis() const {return majorAxis;}

void Ellipse::setMinorAxis(const double &_minor) {minorAxis = _minor;}
void Ellipse::setMajorAxis(const double &_major) {majorAxis = _major;}

double Ellipse::getArea() const {return 3.14 * majorAxis * minorAxis;}
double Ellipse::getPerimeter() const {
    return 2 * 3.14 * sqrt((pow(minorAxis, 2) + pow(majorAxis, 2))/2);
}

void Ellipse::printInfo(ostream &out) const {
    out << "Ellipse object" << endl;
    out << "\tMajor axis = " << majorAxis << endl;
    out << "\tMinor axis = " << minorAxis << endl;
    out << "\tArea = " << getArea() << endl;
    out << "\tPerimeter = " << getPerimeter() << endl;
}

ostream& operator << (ostream &out, const Ellipse &e) {
    e.printInfo(out);
    return out;
}

class Circle : public Ellipse
{
public:
    Circle();
    Circle(const double&);
    Circle(const Circle&);
    
    double getRadius() const;
    
    void setRadius(const double&);
    void setMajorAxis(const double&);
    void setMinorAxis(const double&);
    
    void printInfo(ostream&) const;
    
    friend ostream& operator << (ostream&, const Circle&);
    };

Circle::Circle()
{
    Ellipse::setMajorAxis(1);
    Ellipse::setMinorAxis(1);
}

Circle::Circle(const double& r)
{
    setMinorAxis(r);
    setMajorAxis(r);
}

Circle::Circle(const Circle& c)
{
    setMinorAxis(c.getMinorAxis());
    setMajorAxis(c.getMajorAxis());
}

double Circle::getRadius() const
{
    if(getMinorAxis()==getMajorAxis())
        return getMinorAxis();
    else
        return 0;
}

void Circle::setRadius(const double &r)
{
    setMajorAxis(r);
    setMinorAxis(r);
}

void Circle::setMajorAxis(const double &r)
{
    Ellipse::setMajorAxis(r);
    Ellipse::setMinorAxis(r);
}

void Circle::setMinorAxis(const double &r)
{
    Ellipse::setMajorAxis(r);
    Ellipse::setMinorAxis(r);
}

void Circle::printInfo(ostream &out) const
{
    out << "Circle Object" <<endl;
    out << "\tRadius = " << getRadius() <<endl;
    out << "\tArea = " << getArea() <<endl;
    out << "\tPerimeter = " << getPerimeter() <<endl;
}

ostream& operator << (ostream& out, const Circle &c)
{
    c.printInfo(out);
    return out;
}

Ellipse getBiggestAreaObject(const Ellipse* E, const int size)
{
    Ellipse answer = E[0];
    
    for(int i = 1; i < size; i++)
    {
        if(E[i].getArea() > answer.getArea())
            answer = E[i];
    }
    
    return answer;
}

    


int main()
{
    Ellipse e1;
    const Ellipse e2(2.5, 1.5);

    cout << "e1 major axis is " << e1.getMajorAxis() << endl;
    cout << "e1 minor axis is " << e1.getMinorAxis() << endl;
    cout << "e1 area is " << e1.getArea() << endl;
    cout << "e1 perimeter is " << e1.getPerimeter() << endl;
    cout << endl;

    cout << "e2 is ";
    e2.printInfo(cout);
    cout << endl;

    e1.setMajorAxis(1.2);
    e1.setMinorAxis(0.4);
    cout << "After modification e1 is " << e1 << endl;

    Circle c1;
    const Circle c2(2.5);
    cout << "c1 radius is " << c1.getRadius() << endl;
    cout << "c1 major axis is " << c1.getMajorAxis() << endl;
    cout << "c1 minor axis is " << c1.getMinorAxis() << endl;
    cout << "c1 area is " << c1.getArea() << endl;
    cout << "c1 perimeter is "<< c1.getPerimeter() << endl;
    cout << endl;

    cout << "c2 is ";
    c2.printInfo(cout);
    cout << endl;

    c1.setRadius(1.2);
    cout << "After modification c1 is " << c1 << endl;

    c1.setMajorAxis(0.5);
    cout << "After modification c1 is " << c1 << endl;

    c1.setMinorAxis(0.8);
    cout << "After modification c1 is " << c1 << endl;

    const int SIZE = 10;
    Ellipse E[SIZE];
    srand(1);
    for (int i = 0; i < SIZE; i++)
    {
        if (rand() % 2 == 0)
            E[i] = Ellipse(1.0*rand()/RAND_MAX, 1.0*rand()/RAND_MAX);
        else
            E[i] = Circle(1.0*rand()/RAND_MAX);
    }

    cout << endl << "The elements of the array are..." << endl;
    for (int i = 0; i < SIZE; i++)
        cout << E[i] << endl;

    Ellipse m = getBiggestAreaObject(E, SIZE);
    cout << "The element of the array with the biggest area is " << m << endl;

    system("Pause");
    return 0;
}
