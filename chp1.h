/******c++ characters****/
blocks;
statements;
preprocessor;
built-in types;
arrays;
pointers;
templates;
exceptions;
overloading;
class: encapsulation;inheritance;polymorphism;virtual;
STL:containers;iterators;algorithms;function objects;


/****using const,enum,inline, instead #define****/
#define ASPECT_PATIO 1.653
==>  
const double AspectRatio=1.653;

const char* const authorName="Scott Meyers";  
==> const std::string authorName("Scott Meyers");

class Gameplayer{
private：
    static const int NumTurns=5;
    int scores[NumTurns];
    
}
const int Gameplayer::NumTurns;   //defination of Numturns

==>
class GamePlayer{
private:
    enum{NumTurns=5};
    int scores[NumTurns];
}


#define CALL_WITH_MAX(a,b) f((a)>(b)?(a):(b))  //too long

int a=5,b=0;
CALL_WITH_MAX(++a,b);      //a add 2 times
CALL_WITH_MAX(++a,b+10);   //a add 1 time

==>

template<typename T>
inline void callWithMax(const T& a,const T& b){
    f(a>b?a:b);
}


/*******use const whenever possible*****/
char greeting[]="hello";

char* p=greeting;    //non-const pointer, non-const data

const char* p=greeting;   //non-const pointer, const data

char* const p=greeting;   //const pointer, non-const data

const char* const p=greeting;   //const pointer, const data

//const at left of *: const data
//const at right of *: const pointer
//const at both side of *: const pointer,const data

void f1(Widget const * pw);  <==> void f2(const Widget * pw);

std::vector<int> vec;
...
const std::vector<int>::iterator iter=vec.begin();   
//iter like T* const, can't point to other different type

*iter=10;   //iter can change the value

++iter;    //error, iter is const

std::vector<int>::const_iterator cIter=vec.begin();
//iter like const T*, can't change the value

*cIter=10;   //error, *cIter is const

++cIter;   //no problem, cIter can point to other 

/*****const in function declaration*****/
class Rational{
    ...
}

const Rational operator* (const Rational& lhs, const Rational& rhs);


/*****const member function*****/
class TextBlock{
public:
    ...
    const char& operator[](std::size_t position) const{
        return text[position];    //operator[] for const object
    }

    char& operator[](std::size_t position){
        return text[position];     //operator[] for non-const object
    }

private:
    std::string text;
    
}

TextBlock tb("hello");
std::cout<<tb[0];      //call non-const operator[]

const TextBlock ctb("World");
std::cout<<ctb[0];    //call const operator[]


void print(const TextBlock& ctb){
    std::cout<<ctb[0];    //call const operator[]
}

std::cout<<tb[0];    //no problem, read non-const TextBlock
tb[0]='x';      //no problem, write non-const TextBlock
// if operator[] return char rather than char&, tb[0]='x' can't compile.

std::cout<<ctb[0];  //no problem, read const TextBlock
ctb[0]='x';   //error, write const TextBlock


class CTextBlock{
public:
    ...
    char& operator[](std::size_t position) const{
        return pText[position];    
    }

private:
    char* pText;
}

const CTextBlock cctb("Hello");
char* pc=&cctb[0];    //call const operator[]  ,pc point to cctb[0]

*pc='J';   //cctb="Jello"

/*******ensure initialize object befor using******/
int x;   //maybe x=0; maybe not
==>
int x=0;
const char* text="A C-style string";

double d;
std::cin>>d;
class Point{
    int x,y;
    ...
}

Point p;   //maybe x,y=0; maybe not

/******assignment and initialize****/
class PhoneNumber{...};

class ABEntry{
public:
    
    ABEntry(const std::string& name,const std::string& address,
           const std::list<PhoneNumber>& phones);
private:
    std::string theName;
    std::string theAddress;
    std::list<PhoneNumber> thePhones;
    int numTimesConsulted;

}

ABEntry::ABEntry(const std::string& name,const std::string& address,
           const std::list<PhoneNumber>& phones){
        theName=name;   //assignment
        theAddress=address;
        thePhones=phones;
        numTimesConsulted=0;   
}

==> //member initialization list

ABEntry::ABEntry(const std::string& name,const std::string& address,
           const std::list<PhoneNumber>& phones)
           :theName(name),   //initializations
           theAddress(address),
           thePhones(phones),
           numTimesConsulted(0){
}















