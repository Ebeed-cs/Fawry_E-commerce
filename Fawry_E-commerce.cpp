#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

// global variable for current date -> regardless the day comparison
static int currentYear = 2025; 
static int currentMonth = 7; 

// Product as the Base Class
class Product {
protected:
    string name;
    double price;
    int quantity;

public:
     Product(string n, double p, int q)
        : name(n), price(p), quantity(q) {
        if (price <= 0 || quantity <= 0) { // product validation
            throw invalid_argument("Price and quantity must be positive value");
        }
    }

    virtual bool isExpired() const { return false; }
    virtual bool isShippable() const { return false; }

    const string& getName() const { return name; }
    const double& getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void reduceQuantity(int amount) { quantity -= amount; }
    virtual double getWeight() const { return 0.0; }

};

// Perishable Product 
class PerishableProduct : public Product {
    tm expiryDate;
    double weight; // if weight is zero then not shippable

public:
    PerishableProduct(string n, double p, int q, tm exp, double w = 0)
        : Product(n, p, q), expiryDate(exp), weight(w) {}

    bool isExpired() const override {
        int expiryYear = expiryDate.tm_year + 1900;  
        int expiryMonth = expiryDate.tm_mon + 1;  
        
        if (currentYear > expiryYear) return true;  
        if (currentYear == expiryYear && currentMonth > expiryMonth) return true;  
        return false;  
}

    bool isShippable() const override { return weight > 0; } 
    double getWeight() const override { return weight; }    
};

// Shippable Product
class ShippableProduct : public Product {
    double weight;

public:
    ShippableProduct(string n, double p, int q, double w)
        : Product(n, p, q), weight(w) {}

    bool isShippable() const override { return true; }
    double getWeight() const override { return weight; }
};

// Customer
class Customer {
    string name;
    double balance;

public:
    Customer(string n, double b) : name(n), balance(b) {}

    double getBalance() const { return balance; }

    bool pay(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }

    string getName() const { return name; }
};

// Cart section

struct CartItem {
    Product* product;
    int quantity;
};

class Cart {
    vector<CartItem> items;
    
public:
    void add(Product* p, int qty) {
        if (qty > p->getQuantity()) {
            cout << "Insufficient stock for " << p->getName() << "!\n";
            return;
        }
        items.push_back({p, qty});
    }

    const vector<CartItem>& getItems() const { return items; }

    bool isEmpty() const { return items.empty(); }
};

// Shipping Service
void ShippingService(const vector<CartItem>& items) {
    double totalWeight = 0.0;
    cout << "\n** Shipment Notice **\n";
    for (const auto& item : items) {
        if (item.product->isShippable()) {
            double weight = item.product->getWeight() * item.quantity;
            cout << item.quantity << "x " << item.product->getName()
                 << "    " << fixed << setprecision(0) << weight << "g\n";
            totalWeight += weight;
        }
    }

    cout << "Total package weight: " << fixed << setprecision(1)
         << totalWeight / 1000 << "kg\n\n";
}

// Checkout Process
void checkout(Customer& customer, Cart& cart) {
    if (cart.isEmpty()) {
        cout << "Cart is empty!\n";
        return;
    }

    double subtotal = 0.0;
    double shipping = 0.0;
    double totalWeight = 0.0;
    vector<CartItem> shippables;

    for (const CartItem& item : cart.getItems()) {
        if (item.product->isExpired()) {
            cout << "Item expired: " << item.product->getName() << "\n";
            return;
        }

        subtotal += item.product->getPrice() * item.quantity;

        if (item.product->isShippable()) {
            shippables.push_back(item);
            totalWeight += item.product->getWeight() * item.quantity;
        }
    }

    if (totalWeight > 0)
        shipping = ceil(totalWeight / 1000.0) * 10.0; // foe example each 1 kg -> 10 pounds

    double total = subtotal + shipping;

    if (!customer.pay(total)) {
        cout << "Insufficient balance!\n";
        return;
    }

    for (auto& item : cart.getItems())
        item.product->reduceQuantity(item.quantity);

    if (!shippables.empty())
        ShippingService(shippables);

    // Receipt
    cout << "** Checkout Receipt **\n";
    for (const auto& item : cart.getItems()) {
        cout << item.quantity << "x " << item.product->getName()
             << "    " << item.product->getPrice() * item.quantity << "\n";
    }
    cout << "----------------------\n";
    cout << "Subtotal:     " << subtotal << "\n";
    cout << "Shipping:     " << shipping << "\n";
    cout << "Total Paid:   " << total << "\n";
    cout << "Remaining Balance: " << customer.getBalance() << "\n\n";
}

// helper function to Create tm
tm createDate(int year , int month , int day = 1) {
    tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    return t;
}

int main() {
        PerishableProduct* cheese = nullptr;
        PerishableProduct* biscuits = nullptr; 
        ShippableProduct* tv = nullptr;
        Product* scratchCard = nullptr;

    try
    {
        cheese = new PerishableProduct("Cheese", 100, 10, createDate(2025, 7, 10), 400);
        biscuits = new PerishableProduct("Biscuits", 150, 5, createDate(2026, 1, 1)); 
        tv = new ShippableProduct("TV", 600, 3, 7000);
        scratchCard = new Product("ScratchCard", 50, 20);

        // invalid price to a product 
        Product* apples = new Product("Apples" , 0 , 10);
    }
    catch(const invalid_argument& error)
    {
        cerr << error.what() << '\n';
    }
    


    // ahmed cart 
    Customer ahmed("Ahmed", 5000);
    Cart ahmedCart;
    ahmedCart.add(cheese, 2);
    ahmedCart.add(tv, 3);
    ahmedCart.add(scratchCard, 1);
    checkout(ahmed, ahmedCart);

    cout << "==================================================\n";
    // mohamed cart as empty
    Customer mohamed("Mohamed" , 10000);
    Cart mohamedCart;
    checkout(mohamed , mohamedCart);
    
    cout << "==================================================\n";
    
    // yasser cart as insufficient balance
    Customer yasser("Yasser" , 100);
    Cart yasserCart;
    yasserCart.add(biscuits , 2);
    checkout(yasser , yasserCart);
    
    cout << "==================================================\n";
    
    // anas cart as expire ships
    PerishableProduct* ships = new PerishableProduct("ships" , 20 , 5 ,createDate(2025, 1, 1) );
    
    Customer anas("Anas"  , 10000);
    Cart anasCart;
    anasCart.add(ships , 5);
    checkout(anas , anasCart);
    
    cout << "==================================================\n";
    
    // yassen cart as no avaliable the amount & no shippable product he took
    
    Customer yassen("Yassen"  , 10000);
    Cart yassenCart;
    yassenCart.add(scratchCard , 1);
    yassenCart.add(tv , 1);
    checkout(yassen , yassenCart);
    
    cout << "==================================================\n";
    
    


    // clean the heap memory -> no memory leak
    delete cheese;
    delete biscuits;
    delete tv;
    delete scratchCard;
    delete ships;

    cheese = nullptr;
    biscuits = nullptr;
    tv = nullptr;
    scratchCard = nullptr;
    ships = nullptr;
    return 0;
}
