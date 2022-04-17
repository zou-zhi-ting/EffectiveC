
/****declaration***/
extern int x;
std::size_t numDigits(int number);
class Widget;

template<typename T>
class GraphNode;

/*******definition******/
int x;
std::size_t numDigits(int number) {
	std::size_t digitsSoFar = 1;
	while ((number /= 10) != 0) ++digitsSoFar;
	return digitsSoFar;
}

class Widget {
public:
	Widget();
	~Widget();
	...
};

template<typename T>
class GraphNode {
public:
	GraphNode();
	~GraphNode();
	...
};


/*****initialization*****/
class A {
public:
	A();
};

class B {
public:
	explicit B(int x = 0, bool b = true);
};

/****copy construct function****/
class Widget {
public:
	Widget();  //default construt function
	Widget(const Widget& rhs);  //copy construct function
	Widget& operator=(const Widget& rhs);  //copy assignment

};

Widget w1;   //default
Widget w2(w1);  //call copy construct function
w1 = w2;    ///call copy assignment

Widget w3 = w2;   //call copy construct function


bool hasAcceptableQuality(Widget w);
...
Widget aWidget;
if(hasAcceptableQuality(aWidget))...   //call copy construct function


/******undefined behavior******/
int* p=0;    //p point to null
std::cout<<*p;    //get value from null, an undefined behavior

char name[]="Darla";
char c=name[10];      //valid index, an undefined behavior


/**********name conventions*******/
a*b   <=>  operator*(a,b)

const Rational operator*(const Rational& lhs,const Rational& rhs);   //left hand side: a; right hand side: b

/*****point to T****/
Widget* pw;   //pw="ptr to Widget"

class Airplane;
Airplane* pa; //pa="ptr to Airplane"

class GameCharacter;
GameCharacter* pgc;  //pgc="ptr to GameCharacter"

/*******reference to T*****/

class Airplane;
Airplane a;
Airplane& ra=a; //pa="reference to Airplane"




