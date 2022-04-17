/*********make interfaces easy to use********/
class Date{
public:
    Date(int m,int d,int y);
    ...
}

==>
struct Day{
    explicit Day(int d):val(d){}
    int val;
};

struct Month{
    explicit Month(int m):val(m){}
    int val;
};

struct Year{
    explicit Year(int y):val(y){}
    int val;
};

class Date{
public:
    Date(const Month& m,const Day& d,const Year& y);
    ...
};

Date d(30,3,1995);    //type error
Date d(Day(30),Month(3),Year(1995));  //type error
Date d(Month(3),Day(30),Year(1995));   //good

/******pass-by-reference-to-const instead pass-by-value*****/
class Person{
public:
    Person();
    virtual ~Person();
    ...

private:
    std::string name;
    std::string address;
}


class Student:public Person{
public:
    Student();
    ~Student();
    ...

private:
    std::string schoolName;
    std::string schoolAddress;

}

bool validateStudent(Student s);   //pass-by-value

Student plato;
bool platoIsOK=validateStudent(plato);   //1 Student copy constructor, init by plato;
                                        //1 Person copy constructor
                                        //4 string copy constructor
                                        //6 destructor
==>
bool validateStudent(const Student& s);
//in fact, pass-by-reference pass ptr

/******return an object instead a reference****/
class Rational{
public:
    Rational(int numerator=0,int denominator=1);
    ...
private:
    int n,d;
friend const Rational operator*(const Rational& lhs,const Rational& rhs);
}

Rational a(1,2);
Rational b(3,5);
Rational c=a*b;   
//except exsit c =3/10 originally,is not right

==>   //bad code
const Rational& operator*(const Rational& lhs,const Rational& rhs){
    Rational result(lhs.n*rhs.n,lhs.d*rhs.d);
    return result;
}
//try to return a reference to a local object is bad

==>   //worse code
const Rational& operator*(const Rational& lhs,const Rational& rhs){
    Rational* result=new Rational(lhs.n*rhs.n,lhs.d*rhs.d);
    return *result;
}

==>  //good code
const Rational operator*(const Rational& lhs,const Rational& rhs){
    return Rational(lhs.n*rhs.n,lhs.d*rhs.d);
}

/****declare data members private*****/
class AccessLevels{
public:
    ...
    int getReadOnly()const{
        return readOnly;
    }

    void setReadWrite(int value){
        readWrite=value;
    }

    int getReadWrite()const{
        return readWrite;
    }

    void setWriteOnly(int value){
        writeOnly=value;
    }
private:
    int noAccess;
    int readOnly;
    int readWrite;
    int writeOnly;

}


class SpeedDataCollection{
public:
    void addValue(int speed);
    double averageSoFar()const;           //real time  or small memory
}

/*******perfer non-member ono-friend to member functions******/
class WebBrowser{
public:
    ...

    void clearCahche();
    void clearHistory();
    void removeCookies();
}

1==>
class WebBrowser{
public:
    ...

    void clearEverything();   //call clearCache,clearHistory,removeCookies
}

2==>
void clearBrowser(WebBrowser& wb){    //flexible package
    wb.clearCache();
    wb.clearHistory();
    wb.removeCookies();
}
//only member function and friend function can access data member

3==>
namespace WebBrowserStuff{
    class WebBrowser{...}
    void clearBrowser(WebBrowser& wb);
    ...
}

/******non-member using when type conversions apply to all parameters*******/


/******swap function non-thowing*****/
namespace std{
    template<typename T>   //type T support copy constructor and copy assignment
    void swap(T& a,T& b){
        T temp(a);
        a=b;
        b=temp;
    }
}


class WidgetImpl{
public:
    ...
private:
    int a,b,c;
    std::vector<double> v;      //long copy time

}

class Widget{
public:
    Widget(const Widget& rhs);
    Widget& operator=(const Widget& rhs){
        ...
        *pImpl=*(rhs.pImpl);
        ...
    }
private:
    WidgetImpl* pImpl;    //swap is too bad

}

==>
class Widget{
public:
    ...
    void swap(Widget& other){
        using std::swap;
        swap(pImpl,other.pImpl);
    }

    ...
}

namespace std{
    template<>
    void swap<Widget>(Widget& a,Widget&b){
        a.swap(b);
    }
}













