#include <iostream>
#include <vector>
#include <functional>

class Agregator{
protected:
std::vector<double> seq;
public:
void add(double x){
    seq.push_back(x);
}

    virtual double result() const = 0;
};

class Sum : public Agregator{
public:
    double result() const override{
        double res = 0;
        for(double v : seq){
            res += v;
        }
        return res;
    }
};

class Avg : public Agregator{
public:
    double result() const override{
        double res = 0;
        for(double v : seq){
            res += v;
        }
        return res / seq.size();
    }
};

class Foldr : public Agregator{
std::function<double(double, double)> func;
public:
    Foldr(std::function<double(double, double)> _func) : func(_func) {}

    double result() const override{
        double res = 0;
        for(double v : seq){
            res = func(res, v);
        }
        return res;
    }
};

double reduce(std::vector<double> seq, Agregator *ag){
    for(double v : seq){
        ag->add(v);
    }
    return ag->result();
}

int main() {

    Foldr *maxer = 

  new Foldr([](double a,double b)->double{return std::max(a,b);});

std::cout << reduce({-5,-5,5},maxer); //->5 
std::cout << std::endl;


std::cout << reduce({-5,-5,5},new Sum); //->-5
std::cout << std::endl;

delete maxer;


    return 0;
}