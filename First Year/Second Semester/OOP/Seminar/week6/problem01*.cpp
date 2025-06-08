#include <iostream>
#include <cmath>

const float EPS = 0.0001;

class VectorN{
public:
    float *data;
    int size;

    VectorN(int N): size(N), data(new float[N]) {};

    ~VectorN(){ delete[] data; }

    VectorN(const VectorN &other) : size(other.size){
        data = new float[other.size];
        for (unsigned int i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    VectorN &operator=(const VectorN &other){
        if(this != &other){
            delete[] data;
            size = other.size;
            data = new float[size];
            for (unsigned int i = 0; i < size; ++i)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    VectorN operator+(const VectorN &other) {
        if(this->size != other.size) throw std::invalid_argument("Different n-measure");
        VectorN newVector(size);
        for (int i = 0; i < size; ++i)
        {
            newVector.data[i] = this->data[i] + other.data[i];
        }
        return newVector;
    }

    VectorN operator-(const VectorN &other) {
        if(this->size != other.size) throw std::invalid_argument("Different n-measure");
        VectorN newVector(size);
        for (int i = 0; i < size; ++i)
        {
            newVector.data[i] = this->data[i] - other.data[i];
        }
        return newVector;
    }

    VectorN operator*(const VectorN &other) {
        if(this->size != other.size) throw std::invalid_argument("Different n-measure");
        VectorN newVector(size);
        for (int i = 0; i < size; ++i)
        {
            newVector.data[i] = this->data[i] * other.data[i];
        }
        return newVector;
    }

    VectorN operator/(const VectorN &other) {
        if(this->size != other.size) throw std::invalid_argument("Different n-measure");
        VectorN newVector(size);
        for (int i = 0; i < size; ++i)
        {
            newVector.data[i] = this->data[i] / other.data[i];
        }
        return newVector;
    }

    VectorN operator*(float lambda) {
        VectorN newVector(size);
        for (int i = 0; i < size; ++i)
        {
            newVector.data[i] = this->data[i] * lambda;
        }
        return newVector;
    }

    VectorN operator/(float lambda) {
        VectorN newVector(size);
        for (int i = 0; i < size; ++i)
        {
            newVector.data[i] = this->data[i] / lambda;
        }
        return newVector;
    }

    VectorN &operator+=(float num) {
        //if(this->size != other.size) throw std::invalid_argument("Different n-measure");
        for (int i = 0; i < size; ++i)
        {
            data[i] += num;
        }
        return *this;
    }

    VectorN &operator-=(float num) {
        //if(this->size != other.size) throw std::invalid_argument("Different n-measure");
        for (int i = 0; i < size; ++i)
        {
            data[i] -= num;
        }
        return *this;
    }
    
    VectorN &operator*=(float num) {
        //if(this->size != other.size) throw std::invalid_argument("Different n-measure");
        for (int i = 0; i < size; ++i)
        {
            data[i] *= num;
        }
        return *this;
    }

    VectorN &operator/=(float num) {
        //if(this->size != other.size) throw std::invalid_argument("Different n-measure");
        for (int i = 0; i < size; ++i)
        {
            data[i] /= num;
        }
        return *this;
    }
    bool operator<(const VectorN &other) const{
        float l1 = lenSquared();
        float l2 = other.lenSquared();

        if(std::abs(l1 - l2) >= EPS) return l1 < l2;
        float phi1 = atan2(data[1], data[0]);
        float phi2 = atan2(other.data[1], other.data[0]);
        return phi1 < phi2;
    }

    bool operator>(const VectorN &other) const{
        float l1 = lenSquared();
        float l2 = other.lenSquared();

        if(std::abs(l2 - l1) >= EPS) return l2 < l1;
        float phi1 = atan2(data[1], data[0]);
        float phi2 = atan2(other.data[1], other.data[0]);
        return phi1 > phi2;
    }

    bool operator==(const VectorN &other) const{
        return std::abs(lenSquared() == other.lenSquared());
    }

    float lenSquared() const{return dot(*this, *this);}
    float len() const {return sqrt(lenSquared()); }

    static float dot(const VectorN &a, const VectorN &b){
        if(a.size != b.size) throw std::invalid_argument("Different n-measure");
        float sum = 0;
        for (int i = 0; i < a.size; ++i)
        {
            sum += a.data[i] + b.data[i];
        }
        return sum;
    }
};

int main() {

    return 0;
}