/****ensure public inheritance models is-a******/
class Person{...}
class Student:public Person{...}

class Rectangle{
public:
    virtual void setHeight(int h);
    virtual void setWidth(int w);
    virtual int height() const;
    virtual int width() const;
    ...
}

void makeBigger(Rectangle& r){
    int oh=r.height();
    r.setWidth(r.width()+10);
    assert(r.height()==oh);
}

class Square:public Rectangle{...}

Square s;
...
assert(s.width()==s.height());
makeBigger(s);         //pass-by-reference , change s self

assert(s.width()==s.height());

//other has-a, is-implemented-in-terms-of

/********difference between inheritance of interface and implementation*****/

class Shape{
public:
    virtual void draw()const=0;    //pure virtual interface inheritance without implement
    virtual void error(const std::string& msg);
    int objectID()const;
    ...
}

class Rectangle:public Shape{...}
class Ellipse:public shape{...}

Shape* ps=new Shape;   //error! Shape is abstract
Shape* ps1=new Rectangle;   //right
ps1->draw();      //call Rectangle::draw
Shape* ps2=new Ellipse;     //right
ps2->draw();    //call Ellipse::draw
ps1->Shape::draw();    //call Shape::draw
ps2->Shape::draw();


class Airport{...}
class Airplane{
public:
    virtual void fly(const Airport& dest);
    ...
}

void Airplane::fly(const Airport& dest){
    ...    //fly to dest
}

class ModelA:public Airplane{...}   //inheritance with implement
class ModelB:public Airplane{...}

class ModelC:public Airplane{
    ...
}   //not definition fly
Airport PDX(...);
Airplane* pa=new ModelC;
...
pa->fly(PDX);     //call Airplane::fly

==>
class Airplane{
public:
    virtual void fly(const Airport& dest)=0;
    ...
protected:
    void defaultFly(const Airport& dest);
}

void Airplane::defaultFly(const Airport& dest){
    ...
}

class ModelA:public Airplane{
public:
    virtual void fly(const Airport& dest){
        defaultFly(dest);
    }
}

class ModelB:public Airplane{
public:
    virtual void fly(const Airport& dest){
        defaultFly(dest);
    }
}

class ModelC:public Airplane{
public:
    virtual void fly(const Airport& dest);
}

void ModelC::fly(const Airport& dest){
    ...     //fly ModelC to dest
}


/******consider alternatives to virtual functions******/
class GameCharacter{
public:
    int healthValue()const{
        ...

        int retVal=doHealthValue();
        ...

        return retVal;
    }

private:
    virtual int doHealthValue() const{
        ...
    }
}


/*******never redefine inherited non-virtual function****/
class B{
public:
    void mf();
    ...
}

class D:public B{
public:
    void mf();
    ...
}

D x;
B* pB=&x;
pB->mf();   //call B::mf()


D* pD=&x;
pD->mf();   //call D::mf()


/********never redefine inherited default parameter value******/
class Shape{
public:
    enum ShapeColor{
        Red,Green,Blue
    };
    virtual void draw(ShapeColor color=Red) const =0;
    ...
            
}

class Rectangle:public Shape{
public:
    virtual void draw(ShapeColor color=Green)const;   //deferent default parameter value,badly
    ...
}

class Circle:public Shape{
public:
    virtual void draw(ShapeColor color)const;
}

Shape* ps;       //static type ==Shape*
Shape* pc=new Circle;    //static type ==Shape*
Shape* pr=new Rectangle;    //static type ==Shape*

ps=pc;     //ps dynamic type == Circle*
ps=pr;     //ps dynamic type == Rectangle*

pc->draw(Shape::Red);    //call Circle::draw(Shape::Red)
pr->draw(Shape::Red);    //call Rectangle::draw(Shape::Red)


pr->draw();   //  default parameter value :Red not Green
//default parameter value is static type

/*****model has-a through composition******/
class Address{...}
class PhoneNumber{...}

class Person{
public:
    ...
private:
    std::string name;
    Address address;
    PhoneNumber voiceNumber;
    PhoneNumber faxNumber;
}

/******multiple inheritance*****/
class BorrowableItem{
public:
    void checkOut();
    ...
}

class ElectronicGadget{
private:
    bool checkOut() const;
    ...
}

class MP3Player:public BorrowableItem,public ElectronicGadget{
    ...
}

MP3Player mp;
mp.checkOut();      //?? call for which checkOut

==>
mp.BorroeableItem::checkOut();


            File
           /    \
          /      \
    InputFile    OutputFile
          \      /
           \    /
           IOFile
class File{...}

class InputFile:public File{...}

class OutputFile:public File{...}

class IOFile:public InputFile,public OutputFile{
    ...
}

==>

                 File
                /    \
    (virtual)  /      \  (virtual)
        InputFile    OutputFile
               \      /
                \    /
                IOFile

class File{..}

class InputFile:virtual public File{...}

class OutputFile:virtual public File{...}

class IOFile:public InputFile,public OutputFile{
    ...
}












