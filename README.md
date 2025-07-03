# E-Commerce System 🛒

A comprehensive C++ implementation of an e-commerce shopping cart system featuring inheritance-based product management, expiration handling, and shipping calculations.

## 🚀 Key Features

- **Product Management** - Base class with specialized product types (Perishable, Shippable, Digital)
- **Smart Cart System** - Inventory validation and quantity management
- **Checkout Process** - Payment processing with shipping calculations
- **Error Handling** - Comprehensive validation for edge cases
- **Memory Management** - Proper cleanup with no memory leaks

## 🏗️ Architecture Overview

### Core Classes
- **`Product`** - Base class with name, price, quantity
- **`PerishableProduct`** - Extends Product with expiry dates and conditional shipping
- **`ShippableProduct`** - Extends Product with guaranteed shipping capabilities
- **`Customer`** - Handles payment processing and balance management
- **`Cart`** - Manages product selection and quantity validation

---

## 🧪 Test Cases & Results

### Test Case 1: Input Validation
**Scenario:** Testing invalid product creation with zero price

```cpp
try {
    Product* apples = new Product("Apples", 0, 10);  // Invalid price (0)
} catch(const invalid_argument& error) {
    cerr << error.what() << '\n';
}
```

**Output:**
```
Price and quantity must be positive value
```

---

### Test Case 2: Successful Purchase with Mixed Products
**Scenario:** Normal checkout with perishable, shippable, and digital products

```cpp
Customer ahmed("Ahmed", 5000);
Cart ahmedCart;
ahmedCart.add(cheese, 2);      // Perishable: 400g each
ahmedCart.add(tv, 3);          // Shippable: 7000g each  
ahmedCart.add(scratchCard, 1); // Digital: no shipping
checkout(ahmed, ahmedCart);
```

**Output:**
```
** Shipment Notice **
2x Cheese    800g
3x TV    21000g
Total package weight: 21.8kg

** Checkout Receipt **
2x Cheese    200
3x TV    1800
1x ScratchCard    50
----------------------
Subtotal:     2050
Shipping:     220
Total Paid:   2270
Remaining Balance: 2730
```

---

### Test Case 3: Empty Cart Handling
**Scenario:** Attempting checkout with an empty cart

```cpp
Customer mohamed("Mohamed", 10000);
Cart mohamedCart;
checkout(mohamed, mohamedCart);
```

**Output:**
```
Cart is empty!
```

---

### Test Case 4: Insufficient Balance
**Scenario:** Customer attempts purchase exceeding their balance

```cpp
Customer yasser("Yasser", 100);  // Low balance
Cart yasserCart;
yasserCart.add(biscuits, 2);     // Total cost: 300
checkout(yasser, yasserCart);
```

**Output:**
```
Insufficient balance!
```

---

### Test Case 5: Expired Product Detection
**Scenario:** Attempting to purchase expired perishable products

```cpp
PerishableProduct* ships = new PerishableProduct("ships", 20, 5, createDate(2025, 1, 1));
Customer anas("Anas", 10000);
Cart anasCart;
anasCart.add(ships, 5);
checkout(anas, anasCart);
```

**Output:**
```
Item expired: ships
```

---

### Test Case 6: Mixed Cart - Digital and Shippable
**Scenario:** Purchase combining digital products (no shipping) with shippable items

```cpp
Customer yassen("Yassen", 10000);
Cart yassenCart;
yassenCart.add(scratchCard, 1);  // Digital product
yassenCart.add(tv, 1);           // Shippable product
checkout(yassen, yassenCart);
```

**Output:**
```
** Shipment Notice **
1x TV    7000g
Total package weight: 7.0kg

** Checkout Receipt **
1x ScratchCard    50
1x TV    600
----------------------
Subtotal:     650
Shipping:     70
Total Paid:   720
Remaining Balance: 9280
```

---

## 📋 System Specifications

### Product Types
- **Digital Products** - No expiration, no shipping required
- **Perishable Products** - Have expiry dates, conditional shipping based on weight
- **Shippable Products** - Always require shipping, weight-based calculations

### Shipping Rules
- **Rate:** 10 units per kilogram
- **Calculation:** Rounded up to nearest kilogram
- **Scope:** Only applies to shippable products

### Error Handling
- ✅ Invalid product parameters (price/quantity ≤ 0)
- ✅ Empty cart detection
- ✅ Insufficient customer balance
- ✅ Expired product filtering
- ✅ Stock quantity validation

---

## 🛠️ Technical Implementation

### Memory Management
The system properly manages dynamic memory allocation with explicit cleanup:
```cpp
delete cheese;
delete biscuits;
delete tv;
delete scratchCard;
delete ships;
```

### Date Handling
Uses standard C++ `tm` structure for expiration date management:
```cpp
tm createDate(int year, int month, int day) {
    tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    return t;
}
```

### Polymorphism
Virtual functions enable different behavior for product types:
- `isExpired()` - Returns true only for expired perishable products
- `isShippable()` - Determines shipping requirements
- `getWeight()` - Calculates shipping weight

---

## 🎯 Usage Example

```cpp
// Create products
PerishableProduct* cheese = new PerishableProduct("Cheese", 100, 10, createDate(2025, 7, 10), 400);
ShippableProduct* tv = new ShippableProduct("TV", 600, 3, 7000);
Product* scratchCard = new Product("ScratchCard", 50, 20);

// Create customer and cart
Customer customer("John", 2000);
Cart cart;

// Add items to cart
cart.add(cheese, 2);
cart.add(tv, 1);

// Process checkout
checkout(customer, cart);
```

This system demonstrates object-oriented programming principles with real-world e-commerce functionality, complete error handling, and comprehensive test coverage.
