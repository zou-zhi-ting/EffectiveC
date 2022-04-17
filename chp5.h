/*******postpone variable defination******/
std::string encryptPassword(const std::string& password){
    using namespace std;
    string encrypted;      //definition is too early
    if(password.length()<MinimumPasswordLength){
        throw logic_error("Password is too short");    //exit without using encrypted, 
        //while need pay for the destructor and constructor
    }
    ...
    return encrypted;
}

==>
void encrypt(std::string& s)    //code password
std::string encryPassword(const std::string& password){
    ...      //check length
    std::string encrypted(password);    //copy constructor

    encrypt(encrypted);
    return encrypted;
}

/*****avoid return handles to object internels*****/
class Point{
public:
    Point(int x,int y);
    ...
    void setX(int newVal);
    void setY(int newVal);
}

struct RectData{
    Point ulhc;    //up-left corner
    Point lrhc;     //low-right corner
}

class Rectangle{
    ...
private:
    std::shared_ptr<RectData> pData;

}


class Rectangle{
public:
    Point& upperLeft()const{     //error!
        return pData->ulhc;
    }

    Point& lowerRight()const {    //error!
        return pData->lrhc;
    }
    ...   //in fact, ulhc and lrhc are public not private 
}

==>
class Rectangle{
public:
    const Point& upperLeft()const{     //error!
        return pData->ulhc;
    }

    const Point& lowerRight()const {    //error!
        return pData->lrhc;
    }
}     //add const 


/*****using inline*****/
// enlarge object code, lead to extra paging
//a please to compiler

class Person{
public:
    ...
    int age() const{     // inexplicit an inline please
        return theAge;
    }

private:
    int theAge;
}

template<typename T>
inline const T& std::max(const T& a,const T& b){   //explicit inline please
    return a<b?a:b;
}
// using inline for small,frequency functions
