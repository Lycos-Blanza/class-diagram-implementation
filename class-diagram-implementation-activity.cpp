#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;

// UserAccount Class: This Class handles user registration, login, and logout
class UserAccount {
private:
    string username;
    string password;
    string email;
    string addressLine;
    string contactNo;
    bool loggedIn;

public:
    UserAccount(string uname, string pass, string mail, string address = "", string contact = "")
        : username(uname), password(pass), email(mail), addressLine(address), contactNo(contact), loggedIn(false) {}

    void Login(string uname, string pass) {
        if (username == uname && password == pass) {
            loggedIn = true;
            cout << "[" << username << "]" << " logged in successfully!\n";
        } else {
            cout << "Login failed. Invalid username or password.\n";
        }
    }

    void Logout() {
        loggedIn = false;
        cout << "\n---------------------------------------------" << endl;
        cout << "[" << username << "]" << " logged out.\n";
        cout << "---------------------------------------------" << endl;
        
    }

    bool isLoggedIn() {
        return loggedIn;
    }

    string getUsername() { return username; }
};

// Product Class: Represents a produc in the store
class Product {
private:
    string productID;
    string name;
    float price;
    string description;

public:
    Product(string id, string n, float p, string desc = "")
        : productID(id), name(n), price(p), description(desc) {}

    void displayProduct() {
        cout << setw(10) << productID << setw(20) << name << setw(10) << price << setw(15) << description << endl;
    }

    string getProductID() { return productID; }
    float getPrice() { return price; }
    string getName() { return name; }
};

// CartItem Class: Represents an item in the shopping cart
class CartItem {
private:
    Product product;
    int quantity;

public:
    CartItem(Product p, int q) : product(p), quantity(q) {}

	// To display the cart item details
    void displayCartItem() {
        cout << setw(10) << product.getProductID() << setw(20) << product.getName() 
             << setw(10) << product.getPrice() << setw(10) << quantity << endl;
    }

	// Calculation for the total price of the cart item
    float getItemTotal() { return product.getPrice() * quantity; }
};

// Order Class: Represents an order placed by a user
class Order {
private:
    int orderID;
    vector<CartItem> cartItems;
    float totalAmount;

public:
    Order(int id) : orderID(id), totalAmount(0.0) {}

	// Function to add a cart item to the order
    void addCartItem(CartItem item) {
        cartItems.push_back(item);
        totalAmount += item.getItemTotal();
    }

    float getTotalAmount() {
        return totalAmount;
    }
	
	// Function to display order details
    void displayOrder() {
        cout << "\nOrder ID: " << orderID << endl;
        cout << "Total Amount: " << totalAmount << endl;
        cout << "Order Details:\n";
        cout << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (CartItem item : cartItems) {
            item.displayCartItem();
        }
    }
};

// ShoppingCart Class: Manages the products in the cart
class ShoppingCart {
private:
    vector<CartItem> cartItems; // List of the items

public:
	// Function to add a product to the cart
    void addProduct(Product p, int quantity) {
        cartItems.push_back(CartItem(p, quantity));
        cout << "Product added successfully!" << endl;
    }

    void viewCart() {
        cout << setw(10) << "ProductID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (CartItem item : cartItems) {
            item.displayCartItem();
        }
    }

    float calculateTotal() {
        float total = 0;
        for (CartItem item : cartItems) {
            total += item.getItemTotal();
        }
        return total;
    }

    vector<CartItem> getCartItems() {
        return cartItems;
    }

	// Clearing the cart after checkout
    void clearCart() {
        cartItems.clear();
    }
};

// Payment Class: Handles payment processing
class Payment {
private:
    string paymentMethod;
    float amount;

public:
    Payment(string method, float amt)
        : paymentMethod(method), amount(amt) {}

    void processPayment() {
        cout << "\n---------------------------------------------";
        cout << "\nProcessing";
        sleep(1);
        cout << ".";
        sleep(1);
        cout << ".";
        sleep(1);
        cout << ".";
        sleep(1);
        cout << "\n\nProcessing payment of Php " << amount << " via " << paymentMethod << endl;
        cout << "Payment successful!" << endl;
    }
};

// Menu Class: Displays the various menus for user interaction
class Menu {
public:
    void showMainMenu() {
        cout << "1. Register\n2. Login\n3. Continue as Guest\n4. Logout\nChoose [1/2/3/4]: ";
    }

    void showProductMenu() {
        cout << "\n---------------------------------------------";
        cout << "\nAvailable Products:\n" << setw(10) << "ProductID" << setw(20) << "Name" << setw(10) << "Price" << endl;
    }

    void showCheckoutPrompt() {
        cout << "---------------------------------------------";
        cout << "\nDo you want to check out? [Y/N]: ";
    }

    void showShoppingMenu() {
    	cout << "---------------------------------------------";
        cout << "\nShopping Menu:\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "4. Return to Main Menu\n";
        cout << "Choose [1/2/3/4]: ";
    }
};

int main() {
    // Example products
    vector<Product> products = {
        Product("ORA", "Jotaro Figure", 175.0),
        Product("MUDA", "Dio Figure", 150.0),
        Product("DORA", "Josuke Figure", 125.0),
        Product("SYO", "Jonathan Figure", 150.0),
        Product("YARO", "Kira Figure", 150.0)
    };

    cout << "Welcome to JJBA Store!!\n" << endl;

    ShoppingCart cart;
    Menu menu;
    int option, orderID = 1;
    char checkout;
    UserAccount* loggedInUser = nullptr;
    UserAccount registeredUser("", "", "", "", "");

    vector<Order> orderHistory;

    do {
        menu.showMainMenu();
        cin >> option;

        if (option == 1) {
            string uname, pass, mail, address, contact;
            cout << "\nEnter Username: "; cin >> uname;
            cout << "Enter Password: "; cin >> pass;
            cout << "Enter Email: "; cin >> mail;
            cout << "Enter Address: "; cin >> address;
            cout << "Enter Contact No.: "; cin >> contact;

            registeredUser = UserAccount(uname, pass, mail, address, contact); // Register a new account
            cout << "\n---------------------------------------------";
            cout << "\nAccount registered successfully!\n";
            cout << "---------------------------------------------" << endl;

        } else if (option == 2) {
            string uname, pass;
            cout << "\nEnter Username: "; cin >> uname;
            cout << "Enter Password: "; cin >> pass;

            registeredUser.Login(uname, pass);
            if (registeredUser.isLoggedIn()) {
                loggedInUser = &registeredUser;

                // Enter shopping loop
                char shoppingMenuOption;
                do {
                    menu.showShoppingMenu();
                    cin >> shoppingMenuOption;

                    if (shoppingMenuOption == '1') {
                        // View Products
                        menu.showProductMenu();
                        for (Product p : products) { p.displayProduct(); }

                        string productID;
                        int quantity;
                        char addMore = 'N';

                        do {
                            cout << "\nEnter Product ID to add to cart: "; cin >> productID;
                            cout << "Enter quantity: "; cin >> quantity;

                            for (Product p : products) {
                                if (p.getProductID() == productID) {
                                    cart.addProduct(p, quantity); // Add item to the cart
                                }
                            }

                            cout << "\nAdd more products? [Y/N]: "; cin >> addMore;
                        } while (addMore == 'Y' || addMore == 'y');

                    } else if (shoppingMenuOption == '2') {
                        // View Shopping Cart
                        cart.viewCart();

                        char checkoutOption;
                        cout << "\nDo you want to check out all the products? [Y/N]: ";
                        cin >> checkoutOption;

                        if (checkoutOption == 'Y' || checkoutOption == 'y') {
                            Order order(orderID++);

                            // Move items from cart to order
                            for (CartItem item : cart.getCartItems()) {
                                order.addCartItem(item);
                            }

                            order.displayOrder(); // Display the order details
                            Payment payment("Credit Card", order.getTotalAmount());
                            payment.processPayment();
                            orderHistory.push_back(order);
                            cart.clearCart();

                            cout << "You have successfully checked out the products!" << endl;
                        }

                    } else if (shoppingMenuOption == '3') {
                        // View Orders
                        cout << "---------------------------------------------";
                        cout << "\nOrder History:\n";
                        for (Order ord : orderHistory) {
                            ord.displayOrder();
                        }

                    } else if (shoppingMenuOption == '4') {
                        // Log Out
                        loggedInUser->Logout();
                        loggedInUser = nullptr;
                    }

                } while (shoppingMenuOption != '4');

            }

        } else if (option == 3) {
            // Continue as guest logic
            char shoppingMenuOption;
            do {
                menu.showShoppingMenu();
                cin >> shoppingMenuOption;

                if (shoppingMenuOption == '1') {
                    // View Products
                    menu.showProductMenu();
                    for (Product p : products) { p.displayProduct(); }

                    string productID;
                    int quantity;
                    char addMore = 'N';

                    do {
                        cout << "\nEnter Product ID to add to cart: "; cin >> productID;
                        cout << "Enter quantity: "; cin >> quantity;

                        for (Product p : products) {
                            if (p.getProductID() == productID) {
                                cart.addProduct(p, quantity); // Add item to the cart
                                
                            }
                        }

                        cout << "\nAdd more products? [Y/N]: "; cin >> addMore;
                    } while (addMore == 'Y' || addMore == 'y');

                } else if (shoppingMenuOption == '2') {
                    // View Shopping Cart
                    cart.viewCart();

                    char checkoutOption;
                    cout << "\nDo you want to check out all the products? [Y/N]: ";
                    cin >> checkoutOption;

                    if (checkoutOption == 'Y' || checkoutOption == 'y') {
                        Order order(orderID++);

                        // Move items from cart to order
                        for (CartItem item : cart.getCartItems()) {
                            order.addCartItem(item);
                        }

                        order.displayOrder(); // Display the order details
                        Payment payment("Credit Card", order.getTotalAmount());
                        payment.processPayment();
                        orderHistory.push_back(order);
                        cart.clearCart();

                        cout << "You have successfully checked out the products!" << endl;
                    }

                } else if (shoppingMenuOption == '3') {
                    // View Orders
                    cout << "---------------------------------------------";
                    cout << "\nOrder History:\n";
                    for (Order ord : orderHistory) {
                        ord.displayOrder();
                    }

                } else if (shoppingMenuOption == '4') {
                    // Exit
                    cout << "---------------------------------------------";
                    cout << "\nExiting the system." << endl;
                    cout << "---------------------------------------------" << endl;
                }

            } while (shoppingMenuOption != '4');

        } else if (option == 4) {
            if (loggedInUser != nullptr) {
                loggedInUser->Logout();
                loggedInUser = nullptr;
            }
        }

    } while (option != 4);

    // Display order history (optional)
    cout << "\n\nThank you for shopping with us!" << endl;
    cout << "\n---------------------------------------------";
    cout << "\nAll Orders:\n";
    for (Order ord : orderHistory) {
        ord.displayOrder();
    }

    return 0;
}