#include <iostream>

struct Product{
    char* product_name;
    double price;
};

class ShoppingCart{
private:
    Product* products;
    int* quantitydiffer;
    int currentsize;
    int capacity;
public:
    void clear() {
        delete[] products;
        delete[] quantitydiffer;
    }

    void copy(const ShoppingCart &other){
        currentsize = other.currentsize;
        capacity = other.capacity;
        quantitydiffer = other.quantitydiffer;
        products = new Product[capacity];
        for (int i = 0; i < currentsize; ++i){
            products[i] = other.products[i];
        }
    }

    ShoppingCart() : capacity(50), products(new Product[capacity]), quantitydiffer(new int[capacity]) {}

    ~ShoppingCart(){ clear(); }

    ShoppingCart(const ShoppingCart &other){
        copy(other);
    }

    ShoppingCart &operator=(const ShoppingCart &other){
        clear();
        copy(other);
    }

    bool empty() const{
        return currentsize == 0;
    }

    void addProduct(Product &prod, int quantity){
        if(!empty()){
            for (int i = 0; i < currentsize; ++i)
            {
                if(prod.product_name == products[i].product_name){
                    quantitydiffer[i] += quantity;
                }
                else{
                    products[i] = prod;
                    quantitydiffer[i] = quantity;
                }
            }
        }
    }

    void addProductQuantity(Product &prodToAdd, int quantity){
        if(!empty()){
            for (int i = 0; i < currentsize; ++i)
            {
                if(prodToAdd)
            }
            
        }
    }

    void removeProductQuantity(Product &prodToRemove, int quantity){
        if(!empty()){
            for (int i = 0; i < currentsize; ++i)
            {
                if (products[i].product_name == prodToRemove.product_name){
                    quantitydiffer[i] -= quantity;
                }
                else{
                    throw std::invalid_argument("There's not such product in the cart");
                }
            }
        }
    }


};