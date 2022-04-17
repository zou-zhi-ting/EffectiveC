/*********use objects to manage resources******/
class Investment{
	...   //root class
};

Investment* createInvestment();             //return a ptr to Investment object, must delete

void f(){
    Investment* pInv=createInvestment();  //call factory function
    ...      //maybe return at here, lead to memory leak
    delete pInv;     //release object
}

1==>  //put resource in class

void f(){
    std::auto_ptr<Investment> pInv(createInvestment());   //call factory function

    ...
}   // auto_ptr delete pInv by its destructor

//Resource Acquition Is Iintialization

std::auto_ptr<Investment> pInv1(createInvestment());    //pInv1 point to return of createInvestment

std::auto_ptr<Investment> pInv2(pInv1);    //pInv2 point to object, and pInv1=null

pInv1=pInv2;   //pInv1 point to object, and pInv2=null

//only one point to resource

==>
void f(){
    ...
    std::shared_ptr<Investment> pInv1(createInvestment());   //pInv1 point to object

    std::shared_ptr<Investment> pInv2(pInv1);      //pInv1 and pInv2 point to the same object

    pInv1=pInv2;   //no change
}   //pInv1 and pInv2 delete, resource released

// shared_ptr : the better choice


void lock(Mutex* pm);
void unlock(Mutex* pm);

==>
class Lock{
public:
    explicit Lock(Mutex* pm):mutexPtr(pm){
        lock(mutexPtr);    //get mutex resource
    }
    ~Lock(){
        unlock(mutexPtr);   //release mutex resource
    }
private:
    Mutex *mutexPtr;
}


Mutex m;
...
{
    Lock ml(&m);    //lock mutex;
}  //unlock mutex;

Lock ml1(&m);
Lock ml2(ml1);    //????


==>
class Lock{
public:
    explicit Lock(Mutex* pm):mutexPtr(pm,unlock){
        lock(mutexPtr.get());
    }
private:
    std::shared_ptr<Mutex> mutexPtr;
}


/***********provide access to raw resources******/
int daysHeld(const Investment* pi);    //retrun investment days

int days=daysHeld(pInv);    //error!   Investment* != shared_ptr<Investment>

1==>
int days=daysHeld(pInv.get());   //get origin ptr to daysHeld


class Font{
public:
    ...

    FontHandle get()const{    //expicit  transport
        return f;
    }
private:
    FontHandle f;
}

class Font{
public:
    ...

    operator FontHandle()const{          //inexpicit  transport
        return f;
    }
private:
    FontHandle f;
}


/********use  new and delete  in same form*****/
std::string* stringArray=new std::string[100];
...

delete stringArray;    //error,  99 elements may not be deleted


==>

std::string* stringPtr1=new std::string;
std::string* stringPtr2=new std::string[100];

...

delete stringPtr1;
delete [] stringPtr2;

//typedef

typedef std::string AddressLines[4];

std::string* pal=new AddressLines;    //return string*  <==>new string[4]

delete [] pal;




