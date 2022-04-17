//*********call function in c++ back****/
class Empty{};          //your code

==>
class Empty{          //actually c++ compiler do in back
public:
    Empty(){...}     //default
    Empty(const Empty& rhs){...}       //copy construct
    ~Empty(){...}      //

    Empty& operator=(const Empty& rhs){...}        //copy assignment
}

/******disallow the use of compiler******/
class HomeForSale{...}              //shuold be only one

HomeForSale h1;
HomeForSale h2;
HomeForSale h3(h1);      //should not be compiled
h1=h2;        //should not be compiled

1==>
class HomeForSale{
public:
    ...
private:
    ...
    HomeForSale(const HomeForSale&);         //only declaration
    HomeForSale& operator=(const HomeForSale&);
}

2==>     //in base class
class Uncopyable{
protected:
    Uncopyable(){}
    ~Uncopyable(){}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
}

class HomeForSale:private Uncopyable{   //inherit Uncopyable, defend HomeForSale to be copied
    ...
}

/*******declare destructors virtual in polymorphic base classes*****/
class TimeKeeper{
public:
    TimeKeeper();
    ~TimeKeeper();
    ...
}

class AtomicClock:public TimeKeeper{...}     
class WaterClock:public TimeKeeper{...}
class WristWatch: public TimeKeeper{...}

TimeKeeper* ptk=getTimeKeeper();    //return a ptr to derived class
...
delete ptk;  //have problem, while the derived part can't be deleted

==>
class TimeKeeper{
public:
    TimeKeeper();
    virtual ~TimeKeeper();
    ...
}

//standard string has no virtual function
class SpecialString:public std::string{
    ...
}

SpecialString* pss=new SpecialString("Impending Doom");
std::string* ps;
...
ps=pss;      //SpecialString*  =>  std::string*
...
delete ps;   //SpecialString memory leak

//pure virtual
class AWOV{       //abstract class
public:
    virtual ~AWOV()=0;
}

AWOV::~AWOV(){}        //must be defined

//polymorphic base classes should declare a virtual destructor function


/**********leave exceptions in destructors*******/
class Widget{
public:
    ...
    ~Widget(){
        ...
    }
}


void doSomething(){
    std::vector<Widget> v;
    ...

}

//vector v delete all Widgets

==>
class DBConnection{
public:
    ...
    static DBConnection create();   

    void close();
}

//should add a manage class
class DBConn{
public:
    ...
    ~DBConn(){       //ensure DataBase connection be closed
        db.close();
    }
private:
    DBConnection db;
}

//we can write:
{
    DBConn dbc(DBConnection::create());   //in ideal condition

    ...
}

//if the program throw exceptions
1==>   //call abort()
DBConn::~DBConn(){
    try{
        db.close();
    }
    catch(...){
        std::abort();   
    }
}

2==>    //eat exception
DBConn::~DBConn(){
    try{
        db.close();
    }
    catch(...){

    }
}

3==>
class DBConn{
public:
    ...
    void close(){
        db.close();
        closed=true;
    }
    ~DBConn(){
        if(!closed){
            try{
                db.close();
            }
            catch(...){
                ...
            }
        }
    }
private:
    DBConnection db;
    bool closed;
}

//destructor should not throw out exceptions

/******never call virtual in constructor and destructor******/
class Transaction{
public:
    Transaction();
    virtual void logTransaction() const=0;
}

Transaction::Transaction(){
    ...
    logTransaction();
}

class BuyTransaction:public Transaction{
public:
    virtual void logTransaction() const;
}

class SellTransaction:public Transaction{
public:
    virtual void logTransaction() const;
}

BuyTransaction b;  //Transaction constructor call virtual logTransaction of Transaction jump over BuyTransaction,
//while the derived class BuyTransaction has not been initialized



/******operator= return reference to *this******/
int x,y,z;
x=y=z=15;     //x=(y=(z=15))

class Widget{
public:
    Widget& operator=(const Widget& rhs){
        ...
        return *this;    //return reference point to current object
    }

    Widget& operator+=(const Widget& rhs){
        ...
        return *this;
    }
}


/******operator= to self******/
class Widget{...}
Widget w;
...
w=w;
a[i]=a[j];
*px=*py;

class Bitmap{...}
class Widget{
    ...
private:
    Bitmap* pb;
}
Widget& Widget::operator=(const Widget& rhs){
    delete pb;
    pb=new Bitmap(*rhs.pb);
    return *this;      //point to a delete object
}

1==>
Widget& Widget::operator=(const Widget& rhs){
    if(this==&rhs) return *this;   //test = self

    delete pb;
    pb=new Bitmap(*rhs.pb);
    return *this;
}
2==>
WIdget& Widget::operator=(const Widget& rhs){
    Bitmap* pOrig=pb;    //remenber origin pb;
    pb=new Bitmap(*rhs.pb);   //pb point to another *pb
    delete pOrig;     //delete origin pb;
    return *this;
    
}

3==>
Widget& Widget::operator=(const Widget& rhs){
    Widget temp(rhs);   //copy rhs
    swap(temp);       //swap *this and temp
    return *this;
}



/*****copy all parts of object*****/

void logCall(const std::string& funcName);
class Customer{
public:
    ...
    Customer(const Customer& rhs);
    Customer& operator=(const Customer& rhs);
    ...
private:
    std::string name;
}

Customer::Customer(const Customer& rhs):name(rhs.name){
    logCall("Customer copy constructor");
}

Customer& Customer::operator=(const Customer& rhs){
    logCall("Customer copy assignment operator");
    name=rhs.name;
    return *this;
}

// add Date class
class Date{...}
class Customer{
public:
    ...
private:
    std::string name;
    Date lastTransaction;   //we need change the copy function at the asme time
}

class PriorityCustomer:public Customer{
public:
    ...
    PriorityCustomer(const PriorityCustomer& rhs);
    PriorityCustomer& operator=(const PriorityCustomer& rhs);
    ...
private:
    int priority;

};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
                :priority(rhs.priority){
    logCall("PriorityCustomer copy constructor");
}


PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs){
    logCall("PriorityCustomer copy assignment operaotr");
    priority=rhs.priority;
    return *this;
}     //this seems copy member value, while the base member value not

==>
PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
                :Customer(rhs),      //call base class copy constructor function
                priority(rhs.priority){
    logCall("PriorityCustomer copy constructor");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs){
    logCall("PriorityCustomer copy assignment operator");
    Customer::operator=(rhs);
    priority=rhs.priority;
    return *this;
    
}






































































































