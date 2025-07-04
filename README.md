# E-Commerce System

A C++ implementation of an e-commerce shopping cart system that handles different product types with expiration dates and shipping requirements.

## 🚀 Overview

This project implements a comprehensive e-commerce system featuring:
- Product management with inheritance-based design
- Shopping cart functionality
- Checkout process with payment handling
- Shipping service integration
- Error handling for various edge cases

## 🏗️ System Architecture

### Core Classes

#### `Product` (Base Class)
- **Properties**: name, price, quantity
- **Virtual Methods**: `isExpired()`, `isShippable()`, `getWeight()`
- **Purpose**: Base class for all product types

#### `PerishableProduct` (Derived Class)
- **Inherits**: Product
- **Additional Properties**: expiry date, weight
- **Features**: Expiration checking, conditional shipping based on weight

#### `ShippableProduct` (Derived Class)
- **Inherits**: Product
- **Additional Properties**: weight
- **Features**: Always shippable, weight-based shipping calculations

#### `Customer`
- **Properties**: name, balance
- **Methods**: payment processing, balance management

#### `Cart`
- **Features**: Add products, quantity validation, item management

## 🛠️ Features

### Product Management
- ✅ Different product types (perishable, shippable, digital)
- ✅ Expiration date checking
- ✅ Weight-based shipping calculations
- ✅ Stock quantity management

### Shopping Cart
- ✅ Add products with quantity limits
- ✅ Stock validation
- ✅ Multi-product support

### Checkout Process
- ✅ Subtotal calculation
- ✅ Shipping fee calculation (10 units per kg)
- ✅ Payment processing
- ✅ Receipt generation
- ✅ Inventory updates

### Error Handling
- ✅ Empty cart detection
- ✅ Insufficient balance warnings
- ✅ Out of stock validation
- ✅ Expired product filtering

## 📦 Example Usage

```cpp
// Create products
PerishableProduct* cheese = new PerishableProduct("Cheese", 100, 10, createDate(2025, 7, 10), 400);
ShippableProduct* tv = new ShippableProduct("TV", 600, 3, 7000);
Product* scratchCard = new Product("ScratchCard", 50, 20);

// Create customer and cart
Customer ahmed("Ahmed", 5000);
Cart ahmedCart;

// Add items to cart
ahmedCart.add(cheese, 2);
ahmedCart.add(tv, 1);
ahmedCart.add(scratchCard, 1);

// Checkout
checkout(ahmed, ahmedCart);
```

## 📋 Expected Output

```
** Shipment notice **
2x Cheese 400g
1x TV 7000g
Total package weight 7.4kg

** Checkout receipt **
2x Cheese 200
1x TV 600
1x ScratchCard 50
----------------------
Subtotal 850
Shipping 80
Total Paid 930
Remaining Balance: 4070
```

## 🔧 Compilation & Running

### Prerequisites
- C++11 or later
- Standard C++ compiler (g++, clang++, MSVC)

### Compilation
```bash
g++ -std=c++11 -o ecommerce main.cpp
```

### Running
```bash
./ecommerce
```

## 🧪 Test Cases

The system includes comprehensive test scenarios:

1. **Normal Purchase**: Multiple products with shipping
2. **Empty Cart**: Error handling for empty checkout
3. **Insufficient Balance**: Payment failure scenarios
4. **Expired Products**: Automatic filtering of expired items
5. **Stock Limitations**: Quantity validation

## 🚨 Known Issues & Limitations

### Critical Issues
- ⚠️ **Memory Management**: Uses raw pointers, potential memory leaks
- ⚠️ **Date Handling**: `const_cast` usage in date comparison
- ⚠️ **Cart Logic**: No inventory reservation during cart operations

### Suggested Improvements
- Use smart pointers (`std::unique_ptr`, `std::shared_ptr`)
- Implement proper exception handling
- Add input validation
- Use modern C++ features (auto, range-based loops)
- Add unit tests

## 🏆 Design Patterns Used

- **Inheritance**: Product hierarchy with base and derived classes
- **Polymorphism**: Virtual functions for different product behaviors
- **Composition**: Cart contains CartItem objects
- **Service Pattern**: ShippingService as standalone function

## 📝 Code Quality Assessment

### Strengths
- ✅ Clear class hierarchy
- ✅ Proper use of inheritance and polymorphism
- ✅ Readable and well-structured code
- ✅ Comprehensive feature coverage

### Areas for Improvement
- ❌ Memory management (raw pointers)
- ❌ Error handling (limited exception use)
- ❌ Input validation
- ❌ Thread safety considerations

## 🤝 Contributing

This project was developed as part of the Fawry Rise Journey Full Stack Development Internship Challenge.

### Development Guidelines
1. Follow C++ best practices
2. Add unit tests for new features
3. Use modern C++ features when possible
4. Maintain backward compatibility

## 📄 License

This project is developed for educational purposes as part of an internship challenge.

## 📞 Contact

For questions or suggestions regarding this implementation, please refer to the Fawry internship program documentation.

---

**Note**: This implementation serves as a foundation for an e-commerce system and requires additional security, performance, and reliability improvements for production use.
