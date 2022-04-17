/*********implicit interface and compile-time polymorphism****/
class Widget{
public:
    Widget();
    virtual ~Widget();
    virtual std::size_t size() cosnt;
    virtual void normalize();
    void swap(Widget& other);
    ...
}

void doProcessing(Widget& w){         //explicit interface
    if(w.size()>10&&w!=someNastyWidget){
        Widget temp(w);     
        temp.normalize();
        temp.swap(w);
    }
}


template<typename T>    //implicit interface
void doProcessing(T& w){
    if(w.size()>10&&w!=someNastyWidget){
         ...
    }
}








































