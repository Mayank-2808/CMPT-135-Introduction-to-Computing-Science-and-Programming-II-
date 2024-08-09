#include <iostream>
using namespace std;

class CMPT135_String
{
private:
    char *buffer;    //This will be the dynamic array to hold the characters
public:
    //static member function to compute the length of null terminated char arrays
    static int cstrlen(const char *cStr);

    //Default Constructor
    CMPT135_String();

    //Non-default Constructors
    CMPT135_String(const char &c);
    CMPT135_String(const char *cStr); //*cStr is a null terminated char array

    //Copy Constructor
    CMPT135_String(const CMPT135_String &s);

    //Destructor
    ~CMPT135_String();

    //Assignment operators
    CMPT135_String& operator = (const CMPT135_String &s);
    CMPT135_String& operator = (const char &c);
    CMPT135_String& operator = (const char *cStr); //*cStr is a null terminated char array

    //Getter member functions
    int length() const;
    char& operator[](const int &index) const;

    //Setter member functions
    void append(const CMPT135_String &s);
    void append(const char &c);
    void append(const char *cStr); //*cStr is a null terminated char array

    //Operator member functions
    CMPT135_String operator + (const CMPT135_String &s) const;
    CMPT135_String operator + (const char &c) const;
    CMPT135_String operator + (const char *cStr) const; //*cStr is a null terminated char array
    CMPT135_String& operator += (const CMPT135_String &s);
    CMPT135_String& operator += (const char &c);
    CMPT135_String& operator += (const char *cStr); //*cStr is a null terminated char array
    bool operator == (const CMPT135_String &s) const;
    bool operator == (const char *cStr) const; //*cStr is a null terminated char array
    bool operator != (const CMPT135_String &s) const;
    bool operator != (const char *cStr) const; //*cStr is a null terminated char array
    bool operator < (const CMPT135_String &s) const;
    bool operator < (const char *cStr) const; //*cStr is a null terminated char array
    bool operator > (const CMPT135_String &s) const;
    bool operator > (const char *cStr) const; //*cStr is a null terminated char array
    bool operator <= (const CMPT135_String &s) const;
    bool operator <= (const char *cStr) const; //*cStr is a null terminated char array
    bool operator >= (const CMPT135_String &s) const;
    bool operator >= (const char *cStr) const; //*cStr is a null terminated char array
    
    //Friend Functions (for operators)
    friend CMPT135_String operator + (const char &c, const CMPT135_String &s);
    friend CMPT135_String operator + (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
    friend bool operator == (const char *cStr, const CMPT135_String &s); //*cStr a null terminated char array
    friend bool operator != (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
    friend bool operator < (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
    friend bool operator > (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
    friend bool operator <= (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
    friend bool operator >= (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
    friend ostream& operator << (ostream& outputStream, const CMPT135_String &s);
    friend istream& operator >> (istream& inputStream, CMPT135_String &s);
};

//Explanation of the member and friend functions
int CMPT135_String::cstrlen(const char *cStr)
{
    /*
    This function returns the number of printable characters in the null terminated
    character array cStr. That is, it returns the number of characters in the
    array excluding the terminating null character.

    If the pointer cStr does not have any allocated memory but instead it is
    a nullptr, then this function returns 0.

    This means there are two different cases for which this function returns 0.
    The first case is if the cStr pointer has a nullptr value and the second case
    is when cStr is a dynamic array of size 1 with cStr[0] = '\0'

    This function is implemented by the instructor. MAKING ANY CHANGE TO IT IS NOT ALLOWED.
    */
    if (cStr == nullptr)
        return 0;
    else
    {
        int len = 0;
        while (cStr[len] != '\0')
            len++;
        return len;
    }
}
CMPT135_String::CMPT135_String()
{
    /*
    This function constructs a default CMPT135_String object whose pointer member
    variable is initialized to nullptr.

    This function is implemented by the instructor. MAKING ANY CHANGE TO IT IS NOT ALLOWED.
    */
    buffer = nullptr;
}
CMPT135_String::CMPT135_String(const char &c)
{
    /*
    This function constructs a non-default CMPT135_String that contains one printable
    character (which is the argument) and a null character at the end.

    This function is implemented by the instructor. MAKING ANY CHANGE TO IT IS NOT ALLOWED.
    */
    buffer = new char[2];
    buffer[0] = c;
    buffer[1] = '\0';

}
CMPT135_String::CMPT135_String(const char *cStr) //*cStr is a null terminated char array
{
    /*
    This function constructs a non-default CMPT135_String that contains all the printable
    characters of the argument and a null character at the end.

    This function is implemented by the instructor. MAKING ANY CHANGE TO IT IS NOT ALLOWED.
    */
    int len = CMPT135_String::cstrlen(cStr);
    if (len == 0)
        buffer = nullptr;
    else
    {
        buffer = new char[len+1];
        for (int i = 0; i < len; i++)
            buffer[i] = cStr[i];
        buffer[len] = '\0';
    }

}
CMPT135_String::CMPT135_String(const CMPT135_String &s)
{
    /*
    This function constructs a CMPT135_String object which is a copy of the argument s
    */
    int len = s.length();
    if (len == 0)
        buffer = nullptr;
    else
    {
        buffer = new char[len+1];
        for (int i = 0; i < len; i++)
            buffer[i] = s[i];
        buffer[len] = '\0';
    }
}
CMPT135_String::~CMPT135_String()
{
    /*
    This function destructs a CMPT135_String object. That is it deletes its buffer and
    assigns the buffer a nullptr value

    This function is implemented by the instructor. MAKING ANY CHANGE TO IT IS NOT ALLOWED.
    */
    if (buffer != nullptr)
    {
        delete[] buffer;
        buffer = nullptr;
    }
}
CMPT135_String& CMPT135_String::operator = (const CMPT135_String &s)
{
    /*
    This function assigns a copy of the value of the argument s to the calling object
    */
    if(this == &s)
        return *this;
    
    this->~CMPT135_String();
    
    int len = s.length();
    
    if ( len > 0)
    {
        this->buffer = new char[len + 1];
        
        for(int i = 0;i < len; i++)
        {
            this->buffer[i] = s[i];
        }
        this->buffer[len] = '\0';
    }
    return *this;
}
CMPT135_String& CMPT135_String::operator = (const char &c)
{
    /*
    This function assigns a copy of a CMPT135_string object constructed from the character argument
    to the calling object
    */
    CMPT135_String a = c;
    
    *this = a;
    
    return *this;
}
CMPT135_String& CMPT135_String::operator = (const char *cStr) //*cStr is a null terminated char array
{
    /*
    This function assigns a copy of a CMPT135_string object constructed from the null terminated
    character array argumentto the calling object
    */
    CMPT135_String a = cStr;
    
    *this = a;

    return *this;
}
int CMPT135_String::length() const
{
    /*
    This function returns the length of the buffer of the calling objects as computed by the static
    member function CMPT135_String::cstrlen

    This function is implemented by the instructor. MAKING ANY CHANGE TO IT IS NOT ALLOWED.
    */
    return CMPT135_String::cstrlen(buffer);
}
char& CMPT135_String::operator[](const int &index) const
{
    /*
    This function returns the PRINTABLE character at the given index of the calling object.
    If the index is out of the valid bounds, then error message should be printed.
    This function must crash the application using the abort built-in function
    if index out of bound error occurs.
    The valid bounds of the index are in the range [0,this->length()-1]
    */
    if(index < 0 || index > this->length())
    {
        cout << "ERROR! Index out of bounds. Exiting Program..." << endl;
        abort();
    }
    return this->buffer[index];
}
void CMPT135_String::append(const CMPT135_String &s)
{
    /*
    This function appends all the printable characters of the argument s to the calling object.
    */
    int len1 = this->length();
    int len2 = s.length();
    int len = len1+len2;
    
    CMPT135_String a = *this;
    
    this->~CMPT135_String();
    
    buffer = new char[len + 1];
    
    int i = 0;
    
    for (int j = 0; j < len1; j++,i++)
    {
        buffer[i] = a[j];
    }
    for(int j = 0; j < len2; j++,i++)
    {
        buffer[i] = s[j];
    }
    buffer[len] = '\0';
    
}
void CMPT135_String::append(const char &c)
{
    /*
    This function appends the character argument to the calling object
    */
    CMPT135_String a = c;
    
    this->append(a);
}
void CMPT135_String::append(const char *cStr) //*cStr is a null terminated char array
{
    /*
    This function appends all the printable characters of the argument cStr to the calling object.
    */
    CMPT135_String a = cStr;
    
    this->append(a);
}
CMPT135_String CMPT135_String::operator + (const CMPT135_String &s) const
{
    /*
    This function returns a CMPT135_String object constructed from all the characters of the
    calling object followed by the characters of the argument s
    */
    CMPT135_String answer;
    
    for(int i = 0; i < this->length(); i++)
        answer.append(this->buffer[i]);
    for(int i = 0; i < s.length(); i++)
        answer.append(s[i]);
    
    return answer;
}
CMPT135_String CMPT135_String::operator + (const char &c) const
{
    /*
    This function returns a CMPT135_String object constructed from all the characters of the
    calling object followed by the character argument c
    */
    CMPT135_String a = c;
    
    CMPT135_String answer = *this + a;
    
    return answer;
}
CMPT135_String CMPT135_String::operator + (const char *cStr) const//*cStr is a null terminated char array
{
    /*
    This function returns a CMPT135_String object constructed from all the characters of the
    calling object followed by the characters of the null terminated character array argument cStr
    */
    CMPT135_String a = cStr;
    
    CMPT135_String answer = *this + a;
    
    return answer;
}
CMPT135_String& CMPT135_String::operator += (const CMPT135_String &s)
{
    /*
    This function appends the characters of s to the calling object and then
    returns the calling object
    */
    CMPT135_String a = *this + s;
    
    *this = a;
    
    return *this;
}
CMPT135_String& CMPT135_String::operator += (const char &c)
{
    /*
    This function appends the character c to the calling object and then
    returns the calling object
    */
    CMPT135_String a = *this + c;
    
    *this = a;
    
    return *this;
}
CMPT135_String& CMPT135_String::operator += (const char *cStr) //*cStr is a null terminated char array
{
    /*
    This function appends the characters of the null terminated character array cStr
    to the calling object and then returns the calling object
    */
    CMPT135_String a = *this + cStr;
    
    *this = a;
    
    return *this;
}
bool CMPT135_String::operator == (const CMPT135_String &s) const
{
    /*
    This function tests if the calling object is equal to the argument s
    NOTE:- Two CMPT135_String are equal if they have the same length and characters of the
    calling object are equal to the characters of the argument s at corresponding indexes.

    This function is implemented by the instructor. MAKING ANY CHANGE TO IT IS NOT ALLOWED.
    */
    int len = this->length();
    if (len != s.length())
        return false;
    else
    {
        for (int i = 0; i<len; i++)
        {
            if (buffer[i] != s[i])
                return false;
        }
        return true;
    }
}
bool CMPT135_String::operator == (const char *cStr) const//*cStr is a null terminated char array
{
    /*
    This function tests if the calling object is equal to the null terminated character array cStr.
    In other words, this function tests if the calling object is equal to a CMPT135_String object
    constructed from the null terminated character array argument
    */
    CMPT135_String a = cStr;
    
    if (*this == a)
        return true;
    else
        return false;
}
bool CMPT135_String::operator != (const CMPT135_String &s) const
{
    /*
    This function tests if the calling object is not equal to the argument s
    */
    return !(*this == s);
}
bool CMPT135_String::operator != (const char *cStr) const//*cStr is a null terminated char array
{
    /*
    This function tests if the calling object is not equal to the null terminated character array
    cStr
    */
    return !(*this == cStr);
}
bool CMPT135_String::operator < (const CMPT135_String &s) const
{
    /*
    This function tests if the calling object is less than the argument s
    NOTE:- Given two CMPT135_String objects s1 and s2, we compare them as follows:
        Step 1. Find the smallest valid index k such that s1[k] IS NOT EQUAL TO s2[k]
        Step 2. If such an index k is found, then
            2.1 We say s1 < s2 if s1[k] < s2[k]
            2.2 Otherwise s1 > s2
        Step 3. If such an index k is not found, then
            3.1 We say s1 < s2 if the length of s1 is less than the length of s2
            3.2 We say s1 > s2 if the length of s1 is greater than the length of s2
            3.3 We say s1 == s2 if the length of s1 is equal to the length of s2.
    */
    int len = this->length() < s.length() ? this->length() : s.length();
    
    for (int i = 0; i < len; i++)
    {
        if(this->buffer[i] < s[i])
            return true;
        else if(this->buffer[i] > s[i])
            return false;
    }
    
    if (this->length() < s.length())
        return true;
    else if (this->length() > s.length())
        return false;
    else
        return false;
}
bool CMPT135_String::operator < (const char *cStr) const//*cStr is a null terminated char array
{
    /*
    This function tests if the calling object is less than the null terminated character array cStr
    */
    CMPT135_String a = cStr;
    
    return *this < a;
}
bool CMPT135_String::operator > (const CMPT135_String &s) const
{
    /*
    This function tests if the calling object is greater than the argument s
    */
    
    return (!(*this < s) && !(*this == s));
}
bool CMPT135_String::operator > (const char *cStr) const//*cStr is a null terminated char array
{
    /*
    This function tests if the calling object is greater than the null terminated character array
    cStr
    */
    CMPT135_String a = cStr;
    
    return *this > a;
}
bool CMPT135_String::operator <= (const CMPT135_String &s) const
{
    /*
    This function tests if the calling object is less than or equal to the argument s
    */
    
    return ((*this < s) || (*this == s));
}
bool CMPT135_String::operator <= (const char *cStr) const//*cStr is a null terminated char array
{
    /*
    This function tests if the calling object is less than or equal to the null terminated character
    array cStr
    */
    CMPT135_String a = cStr;
    
    return *this <= a;
}
bool CMPT135_String::operator >= (const CMPT135_String &s) const
{
    /*
    This function tests if the calling object is greater than or equal to the argument s
    */
    
    return ((*this > s) || (*this == s));
}
bool CMPT135_String::operator >= (const char *cStr) const//*cStr is a null terminated char array
{
    /*
    This function tests if the calling object is greater than or equal to the null terminated
    character array cStr
    */
    CMPT135_String a = cStr;
    
    return *this >= a;
}
CMPT135_String operator + (const char &c, const CMPT135_String &s)
{
    /*
    This function returns a CMPT135_String object constructed from thecharacter argument c followed
    by the characters of s
    */
    CMPT135_String a = c;
    
    CMPT135_String answer = a + s;
    
    return answer;
}
CMPT135_String operator + (const char *cStr, const CMPT135_String &s) //*cStr is a null terminated char array
{
    /*
    This function returns a CMPT135_String object constructed from thecharacters of the null
    terminated character array argument cStr followed by the characters of s
    */
    CMPT135_String a = cStr;
    
    CMPT135_String answer = a + s;
    
    return answer;
}
bool operator == (const char *cStr, const CMPT135_String &s) //*cStr a null terminated char array
{
    /*
    This function tests if the null terminated character array argument cStr is equal to s
    */
    CMPT135_String a = cStr;
    
    return a == s;
}
bool operator != (const char *cStr, const CMPT135_String &s) //*cStr is a null terminated char array
{
    /*
    This function tests if the null terminated character array argument cStr is not equal to s
    */
    CMPT135_String a = cStr;
    
    return a != s;
}
bool operator < (const char *cStr, const CMPT135_String &s) //*cStr is a null terminated char array
{
    /*
    This function tests if the null terminated character array argument cStr is less than s
    */
    CMPT135_String a = cStr;
    
    return a < s;
}
bool operator > (const char *cStr, const CMPT135_String &s) //*cStr is a null terminated char array
{
    /*
    This function tests if the null terminated character array argument cStr is greater than s
    */
    CMPT135_String a = cStr;
    
    return a > s;
}
bool operator <= (const char *cStr, const CMPT135_String &s) //*cStr is a null terminated char array
{
    /*
    This function tests if the null terminated character array argument cStr is less than or equal
    to s
    */
    CMPT135_String a = cStr;
    
    return a <= s;
}
bool operator >= (const char *cStr, const CMPT135_String &s) //*cStr is a null terminated char array
{
    /*
    This function tests if the null terminated character array argument cStr is greater than or
    equal to s
    */
    CMPT135_String a = cStr;
    
    return a >= s;
}
ostream& operator << (ostream& out, const CMPT135_String &s)
{
    /*
    This function prints the printable characters in the dynamic array member variable buffer.
    This function is implemented by the instructor. MAKING ANY CHANGE TO IT IS NOT ALLOWED.
    */
    for (int i = 0; i < s.length(); i++)
        out << s.buffer[i];
    return out;
}
istream& operator >> (istream& in, CMPT135_String &s)
{
    /*
    This function is designed to read ANY number of characters from the user.Reading will stop
    when the user presses the Enter Key. In order to achieve this, we will read one character at a
    time until end of line character ('\n') is read.
    This function is implemented by the instructor. MAKING ANY CHANGE TO IT IS NOT ALLOWED.
    */
    s.~CMPT135_String();
    char c;
    while (true)
    {
        in.get(c);
        if (c == '\n')
            break;
        else
            s.append(c);
    }
    return in;
}

int findCharIndex(const CMPT135_String &a, const char &c)
{
    int len = a.length();
    
    for(int i = 0; i < len; i++)
    {
        if(a[i] == c)
            return i;
    }
    return -1;
}

int reverseFindCharIndex(const CMPT135_String &a, const char &c)
{
    int len = a.length();
    
    for (int i = len-1; i >= 0; i--)
    {
        if (a[i] == c)
            return i;
    }
    return -1;
}

int countChar(const CMPT135_String &a, const char &c)
{
    int count = 0;
    
    int len = a.length();
    
    for(int i = 0; i < len; i++)
    {
        if(a[i] == c)
            count++;
    }
    return count;
}

CMPT135_String getSubString(const CMPT135_String &a, const int &start, const int &len)
{
    CMPT135_String answer;
    
    int j = start;
    
    for (int i = 0; i < len && j < a.length(); i++, j++)
        answer.append(a[start+i]);
    
    return answer;
}

bool isSubString(const CMPT135_String &a, const CMPT135_String &b)
{
    int len1 = a.length();
    int len2 = b.length();
    
    if (len1 > len2)
        return false;
    
    for (int i = 0; i < len2; i++)
    {
        CMPT135_String s = getSubString(b, i, len1);
        
        if(s==a)
            return true;
    }
    return false;
}

CMPT135_String getReversedString(const CMPT135_String &a)
{
    CMPT135_String answer;
    
    for (int i = a.length()-1; i >=0; i--)
        answer.append(a[i]);
    
    return answer;
}

CMPT135_String removeChar(CMPT135_String &a, const char &c)
{
    CMPT135_String answer;
    
    for (int i = 0; i < a.length(); i++)
    {
        if(a[i]==c)
            continue;
        else
            answer.append(a[i]);
    }

    a = answer;
    
    return answer;
}

CMPT135_String replaceChar(CMPT135_String &a, const char &b, const char &c)
{
    CMPT135_String answer;
    
    for (int i = 0; i < a.length(); i++)
    {
        if(a[i]==b)
            answer.append(c);
        else
            answer.append(a[i]);
    }

    a = answer;
    
    return answer;
}

//Test Program
int main()
{
    //Test the cstrlen static member function'
    cout << "The length of \"Yonas\" is " << CMPT135_String::cstrlen("Yonas") << endl;
    cout << "The length of \"\" is " << CMPT135_String::cstrlen("") << endl;
    cout << "The length of nullptr is " << CMPT135_String::cstrlen(nullptr) << endl;

    //Test default constructor and length member functions
    CMPT135_String s1;
    cout << "s1 is \"" << s1 << "\" and its length is " << s1.length() << endl;

    //Test non-default constructor and length member functions
    CMPT135_String s2 = 'Y';
    cout << "s2 is \"" << s2 << "\" and its length is " << s2.length() << endl;

    //Test non-default constructor and length member functions
    CMPT135_String s3 = "CMPT 135";
    cout << "s3 is \"" << s3 << "\" and its length is " << s3.length() << endl;

    //Test copy constructor and length member functions
    CMPT135_String s4 = s3;
    cout << "s4 is \"" << s4 << "\" and its length is " << s4.length() << endl;
    
    //Test destructor and length member functions
    s4.~CMPT135_String();
    cout << "s4 is \"" << s4 << "\" and its length is " << s4.length() << endl;

    //Test assignment operator and length member functions
    s4 = s2;
    cout << "s4 is \"" << s4 << "\" and its length is " << s4.length() << endl;

    //Test assignment operator and length member functions
    s4 = 'A';
    cout << "s4 is \"" << s4 << "\" and its length is " << s4.length() << endl;

    //Test assignment operator and length member functions
    s4 = "This is cool";
    cout << "s4 is \"" << s4 << "\" and its length is " << s4.length() << endl;

    //Test indexing operator member function
    cout << "s4[2] is " << s4[2] << endl;
    s4[2] = 'a';
    cout << "s4[2] is " << s4[2] << endl;
    s4[3] = 't';
    cout << "s4 is \"" << s4 << "\" and its length is " << s4.length() << endl;

    //Test append and length member functions
    s1.append(s4);
    cout << "s1 is \"" << s1 << "\" and its length is " << s1.length() << endl;

    //Test append and length member functions
    s3.append(' ');
    cout << "s3 is \"" << s3 << "\" and its length is " << s3.length() << endl;

    //Test append and length member functions
    s3.append("201901");
    cout << "s3 is \"" << s3 << "\" and its length is " << s3.length() << endl;

    //Test findCharIndex non-member function
    char ch = '1';
    int k = findCharIndex(s3, ch);
    cout << "The first index of '" << ch << "' in \"" << s3 << "\" is " << k << endl;
    ch = 'm';
    k = findCharIndex(s3, 'm');
    cout << "The first index of '" << ch << "' in \"" << s3 << "\" is " << k << endl;

    //Test reverseFindCharIndex non-member function
    ch = '1';
    k = reverseFindCharIndex(s3, ch);
    cout << "The last index of '" << ch << "' in \"" << s3 << "\" is " << k << endl;
    ch = 'm';
    k = reverseFindCharIndex(s3, 'm');
    cout << "The last index of '" << ch << "' in \"" << s3 << "\" is " << k << endl;
    
    //Test countChar non-member function
    ch = '1';
    k = countChar(s1, ch);
    cout <<  "'" << ch << "' appears " << k << " times in \"" << s1 << "\"" << endl;

    //Test getSubString non-member function
    s1 = getSubString(s3, 10, 3);
    cout << "s1 is \"" << s1 << "\" and its length is " << s1.length() << endl;
    s1 = getSubString(s3, 10, 5);
    cout << "s1 is \"" << s1 << "\" and its length is " << s1.length() << endl;
    s1 = getSubString(s3, 10, 8);
    cout << "s1 is \"" << s1 << "\" and its length is " << s1.length() << endl;
    
    //Test isSubString non-member function
    if (isSubString(s1, s3) == true)
        cout << "\"" << s1 << "\" is a substring of \"" << s3 << "\"" << endl;
    else
        cout << "\"" << s1 << "\" is not a substring of \"" << s3 << "\"" << endl;
    s2 = "01902029010190";
    if (isSubString(s1, s2) == true)
        cout << "\"" << s1 << "\" is a substring of \"" << s2 << "\"" << endl;
    else
        cout << "\"" << s1 << "\" is not a substring of \"" << s2 << "\"" << endl;
    char x[] = "01902019010190";
    if (isSubString(s1, x) == true)
        cout << "\"" << s1 << "\" is a substring of \"" << x << "\"" << endl;
    else
        cout << "\"" << s1 << "\" is not a substring of \"" << x << "\"" << endl;
    
    //Test getReversedString non-member function
    cout << "s1 is \"" << s1 << "\" and its length is " << s1.length() << endl;
    CMPT135_String rev = getReversedString(s1);
    cout << "The reverse of \"" << s1 << "\" is \"" << rev << "\"" << endl;
    
    //Test removeChar non-member function
    cout << "After removing all the '" << ch << "' characters from \"" << s1 << "\", we get ";
    removeChar(s1, ch);
    cout << "\"" << s1 << "\"" << endl;
    s3 = "11111111111";
    cout << "After removing all the '" << ch << "' characters from \"" << s3 << "\", we get ";
    removeChar(s3, ch);
    cout << "\"" << s3 << "\"" << endl;
    
    //Test replaceChar non-member function
    cout << "After replacing 1 by 5 from \"" << s2 << "\", we get ";
    replaceChar(s2, '1', '5');
    cout << s2 << endl;

    //Test + operator member function
    cout << "s1 is \"" << s1 << "\", s3 is \"" << s3 << "\" and s1 + s3 is \"" << s1 + s3 << "\"" << endl;
    cout << "s1 is \"" << s1 << " and s1 + \"yonas\" is \"" << s1 + "yonas" << endl;
    cout << "s1 is \"" << s1 << " and s1 + 'Y' is \"" << s1 + 'Y' << endl;

    //Test += operatror member function
    s2 = "Test";
    cout << "s1 is \"" << s1 <<"\", s2 is \"" << s2 << "\", and s3 is \"" << s3 << "\"" << endl;
    s3 = s1 += s2;
    cout << "After s3 = s1 += s2, we get s1 is " << s1 <<", s2 is " << s2 << ", and s3 is " << s3 << endl;

    cout << "s2 is \"" << s2 << "\". ";
    s2 += "FIC";
    cout << "After s2 += \"FIC\", we get \"" << s2 << "\"" << endl;
    cout << "s2 is \"" << s2 << "\". ";
    s2 += '!';
    cout << "After s2 += '!', we get \"" << s2 << "\"" << endl;

    //Test relational operators member functions
    s1 = "Test1";
    s2 = "";
    cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 == s2 is " << (s1 == s2) << endl;
    cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 != s2 is " << (s1 != s2) << endl;
    cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 > s2 is " << (s1 > s2) << endl;
    cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 < s2 is " << (s1 < s2) << endl;
    cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 >= s2 is " << (s1 >= s2) << endl;
    cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 <= s2 is " << (s1 <= s2) << endl;

    //Test + friend functions
    cout << "\"Yonas\" + \"" << s1 << "\" is \"" << "Yonas" + s1 << "\"" << endl;
    cout << "'y' + \"" << s1 << "\" is \"" << 'y' + s1 << "\"" << endl;

    //Test friend relational operators
    cout << "s1 is \"" << s1 << "\" and \"Test2\" == s1 is " << ("Test2" == s1) << endl;
    cout << "s1 is \"" << s1 << "\" and \"Test2\" != s1 is " << ("Test2" != s1) << endl;
    cout << "s1 is \"" << s1 << "\" and \"Test2\" < s1 is " << ("Test2" < s1) << endl;
    cout << "s1 is \"" << s1 << "\" and \"Test2\" > s1 is " << ("Test2" > s1) << endl;
    cout << "s1 is \"" << s1 << "\" and \"Test2\" <= s1 is " << ("Test2" <= s1) << endl;
    cout << "s1 is \"" << s1 << "\" and \"Test2\" >= s1 is " << ("Test2" >= s1) << endl;

    //Test input streaming operator
    cout << "Enter a string of any length you want (including spaces, punctuation marks, etc if you wish): ";
    cin >> s1;
    cout << "You entered \"" << s1 << "\"" << endl;

    system("pause");
    return 0;
}
