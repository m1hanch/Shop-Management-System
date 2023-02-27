#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;
// Base classes(5)
class Person {
public:
    Person(string name, int age, string address)
            : name_(name), age_(age), address_(address) {}

    virtual ~Person()= default;


    string GetName() const { return name_; }
    int GetAge() const { return age_; }
    string GetAddress() const { return address_; }
    friend void PrintInfo(const Person& person);
    friend class Employee; //dla funkcji printInfo(Employee)
protected:
    string name_;
    int age_;
    string address_;

};

class Employee : public Person {
public:
    Employee(string name, int age, string address, string job_title,
             double salary)
            : Person(name, age, address), job_title_(job_title), salary_(salary) {}

    ~Employee() override = default;

    string GetJobTitle() const { return job_title_; }
    double GetSalary() const { return salary_; }
    friend void PrintInfo(const Employee& employee);
    friend class Manager; //dla funkcji PrintInfo
    friend class Salesperson; //dla funkcji PrintInfo
    friend class Technician; //dla funkcji PrintInfo

    bool operator==(const Employee& other) const {
        return this->name_==other.name_ && this->age_ == other.age_ && this->address_ == other.address_ &&
        this->job_title_ == other.job_title_ && this->salary_ ==  other.salary_;
    }
    bool operator!=(const Employee& other) const {
        return !(*this == other);
    }
private:
    string job_title_;
    double salary_;

};

class Customer : public Person {
public:
    Customer(string name, int age, string address,
             vector<string> purchase_history, int loyalty_points)
            : Person(name, age, address),
              purchase_history_(purchase_history),
              loyalty_points_(loyalty_points) {}

    ~Customer() override = default;

    vector<string> GetPurchaseHistory() const { return purchase_history_;}
    int GetLoyaltyPoints() const { return loyalty_points_; }
    friend void PrintInfo(const Customer& customer);
    bool operator==(const Customer& other) const {
        return this->loyalty_points_ == other.loyalty_points_ && this->name_ == other.name_ &&
        this->address_ == other.address_ && this->age_ == other.age_ && this->purchase_history_ == other.purchase_history_;
    }
    bool operator!=(const Customer& other) const {
        return !(*this == other);
    }

private:
    vector<string> purchase_history_;
    int loyalty_points_;

};

class Product {
public:
    Product(string name, double price, int stock_level)
            : name_(name), price_(price), stock_level_(stock_level) {}

    ~Product(){};

    string GetName() const { return name_; }
    double GetPrice() const { return price_; }
    int GetStockLevel() const { return stock_level_; }

    friend class Order; //dla przeciazenia *=
    friend void PrintInfo(const Product& product);
    bool operator==(const Product& other) const {
        return this->name_ == other.name_ && this->price_ == other.price_ && this->stock_level_ == other.stock_level_;
    }
    bool operator!=(const Product& other) const {
        return !(*this == other);
    }
private:
    string name_;
    double price_;
    int stock_level_;

};

class Order {
public:
    Order(int order_number, Customer* customer,
          vector<Product*> products)
            : order_number_(order_number),
              customer_(customer),
              products_(products) {}

    ~Order(){};
    int GetOrderNumber() const { return order_number_; }
    Customer* GetCustomer() const { return customer_; }
    vector<Product*> GetProducts() const { return products_; }

    void operator+=(Product* product) {
        products_.push_back(product);
    }

    void operator-=(Product* product) {
        auto it = find(products_.begin(), products_.end(), product);
        if (it != products_.end()) {
            products_.erase(it);
        }
    }

    void operator*=(int quantity) {
        for (Product* product : products_) {
            product->stock_level_ *= quantity;
        }
    }

    friend ostream& operator<<(ostream& os, const Order& order) {
        os << "Order #" << order.order_number_ << ": ";
        os << "\nCustomer: " << order.customer_->GetName() << " ";
        os << "\nProducts: ";
        for (Product* product : order.products_) {
            os << product->GetName() << ", ";
        }
        cout<<"\n";
        return os;
    }

    bool operator==(const Order& other) const {
        return order_number_ == other.order_number_ &&
               customer_ == other.customer_ &&
               products_ == other.products_;
    }
    bool operator!=(const Order& other) const {
        return !(*this == other);
    }

    friend void PrintInfo(const Order& order);
protected:
    int order_number_;
    Customer* customer_;
    vector<Product*> products_;
};

// Inherited classes(10)

class Manager : public Employee {
public:
    Manager(string name, int age, string address, string job_title,
            double salary, int team_size, double budget)
            : Employee(name, age, address, job_title, salary),
              team_size_(team_size),
              budget_(budget) {}

    ~Manager(){};
    int GetTeamSize() const { return team_size_; }
    double GetBudget() const { return budget_; }
    void PrintInfo() {
        cout << "Name: " << this->name_ << endl;
        cout << "Age: " << this->age_ << endl;
        cout << "Address: " << this->address_ << endl;
        cout << "Post: " << this->job_title_ << endl;
        cout << "Salary: " << this->salary_ << endl;
        cout << "Team Size: " << this->team_size_ << endl;
        cout << "Budget: " << this->budget_ << endl;
    }

private:
    int team_size_;
    double budget_;
};

class Salesperson : public Employee {
public:
    Salesperson(string name, int age, string address,
                string job_title, double salary, double sales_targets,
                double commission)
            : Employee(name, age, address, job_title, salary),
              sales_targets_(sales_targets),
              commission_(commission) {}

    ~Salesperson(){};
    double GetSalesTargets() const { return sales_targets_; }
    double GetCommission() const { return commission_; }

    void PrintInfo() {
        cout << "Name: " << this->name_ << endl;
        cout << "Age: " << this->age_ << endl;
        cout << "Address: " << this->address_ << endl;
        cout << "Post: " << this->job_title_ << endl;
        cout << "Salary: " << this->salary_ << endl;
        cout << "Sales Targets: " << this->sales_targets_ << endl;
        cout << "Commission: " << this->commission_*100<<"%"<< endl;
    }
private:
    double sales_targets_;
    double commission_;
};

class Technician : public Employee {
public:
    Technician(string name, int age, string address,
               string job_title, double salary,
               vector<string> skills,
               vector<string> certifications)
            : Employee(name, age, address, job_title, salary),
              skills_(skills),
              certifications_(certifications) {}

    ~Technician(){};
    vector<string> GetSkills() const { return skills_; }
    vector<string> GetCertifications() const {
        return certifications_;
    }

    void PrintInfo() {
        cout << "Name: " << this->name_ << endl;
        cout << "Age: " << this->age_ << endl;
        cout << "Address: " << this->address_ << endl;
        cout << "Post: " << this->job_title_ << endl;
        cout << "Salary: " << this->salary_ << endl;
        cout << "Skills: ";
        for (string skill : this->skills_) {
            cout << skill << ", ";
        }
        cout << endl;
        cout << "Certifications: ";
        for (string certification : this->certifications_) {
            cout << certification << ", ";
        }
        cout << endl;
    }

private:
    vector<string> skills_;
    vector<string> certifications_;
};

class Receptionist : public Employee {
public:
    Receptionist(string name, int age, string address,
                 string job_title, double salary,
                 vector<string> language_skills,
                 string customer_service_experience)
            : Employee(std::move(name), age, std::move(address), std::move(job_title), salary),
              language_skills_(std::move(language_skills)),
              customer_service_experience_(std::move(customer_service_experience)) {}

    ~Receptionist(){};
    vector<string> GetLanguageSkills() const {
        return this->language_skills_;
    }
    string GetCustomerServiceExperience() const {
        return this->customer_service_experience_;
    }

private:
    vector<string> language_skills_;
    string customer_service_experience_;
};

class Accountant : public Employee {
public:
    Accountant(string name, int age, string address, string job_title,
               double salary, double budget)
            : Employee(name, age, address, job_title, salary),
              budget_(budget) {}

    ~Accountant(){};
    double GetBudget() const { return this->budget_; }

private:
    double budget_;
};

class RegularCustomer : public Customer {
public:
    RegularCustomer(string name, int age, string address,
                    vector<string> purchase_history, int loyalty_points,
                    string preferred_payment_method)
            : Customer(name, age, address, purchase_history, loyalty_points),
              preferred_payment_method_(preferred_payment_method){}
    virtual ~RegularCustomer() {}

    string GetPreferredPaymentMethod() const { return this->preferred_payment_method_; }
    void SetPreferredPaymentMethod(string preferred_payment_method) { preferred_payment_method_ = preferred_payment_method; }
private:
    string preferred_payment_method_;
};

class VIPCustomer : public Customer {
public:
    VIPCustomer(string name, int age, string address,
                vector<string> purchase_history, int loyalty_points,
                double discount)
            : Customer(name, age, address, purchase_history, loyalty_points),
              discount_(discount) {}

    ~VIPCustomer(){};
    double GetDiscount() const { return this->discount_; }

private:
    double discount_;
};

class PhysicalProduct : public Product {
public:
    PhysicalProduct(string name, double price, int stock_level,
                    string location, bool fragile)
            : Product(name, price, stock_level),
              location_(location),
              fragile_(fragile) {}

    ~PhysicalProduct(){};
    string GetLocation() const { return this->location_; }
    bool IsFragile() const { return this->fragile_; }

private:
    string location_;
    bool fragile_;
};

class DigitalProduct : public Product {
public:
    DigitalProduct(string name, double price, int stock_level,
                   string file_type, int file_size)
            : Product(name, price, stock_level),
              file_type_(file_type),
              file_size_(file_size) {}

    virtual ~DigitalProduct(){};
    string GetFileType() const { return this->file_type_; }
    int GetFileSize() const { return this->file_size_; }

private:
    string file_type_;
    int file_size_;
};

class CustomProduct : public Product {
public:
    CustomProduct(string name, double price, int stock_level,
                  vector<string> materials, string production_time)
            : Product(name, price, stock_level),
              materials_(materials),
              production_time_(production_time) {}

    ~CustomProduct(){};
    vector<string> GetMaterials() const { return this->materials_; }
    string GetProductionTime() const { return this->production_time_; }
private:
    vector<string> materials_;
    string production_time_;
};

class Programmer : public Technician{
private:
    vector<string>languages;
    vector<string>frameworks;
public:
    Programmer(const string &name, int age, const string &address, const string &jobTitle, double salary,
               const vector<string> &skills, const vector<string> &certifications, const vector<string> &languages,
               const vector<string> &frameworks) : Technician(name, age, address, jobTitle, salary, skills,
                                                              certifications), languages(languages),
                                                   frameworks(frameworks) {}

    virtual ~Programmer() = default;

    const vector<string> &getLanguages() const {
        return languages;
    }

    void setLanguages(const vector<string> &languages) {
        Programmer::languages = languages;
    }

    const vector<string> &getFrameworks() const {
        return frameworks;
    }

    void setFrameworks(const vector<string> &frameworks) {
        Programmer::frameworks = frameworks;
    }

};



//Friend functions
void PrintInfo(const Person& person) {
    cout << "Name: " << person.name_ << endl;
    cout << "Age: " << person.age_ << endl;
    cout << "Address: " << person.address_ << endl;
}

void PrintInfo(const Employee& employee) {
    cout << "Name: " << employee.name_ << endl;
    cout << "Age: " << employee.age_ << endl;
    cout << "Address: " << employee.address_ << endl;
    cout << "Post: " << employee.job_title_ << endl;
    cout << "Salary: " << employee.salary_ << endl;
}

void PrintInfo(const Customer& customer) {
    cout << "Name: " << customer.name_ << endl;
    cout << "Age: " << customer.age_ << endl;
    cout << "Address: " << customer.address_ << endl;
    cout << "Purchase history: ";
    for (const string& purchase : customer.purchase_history_) {
        cout << purchase << " ";
    }
    cout << endl;
    cout << "Loyalty points: " << customer.loyalty_points_ << endl;
}

void PrintInfo(const Product& product) {
    cout << "Product name: " << product.name_ << endl;
    cout << "Price: " << product.price_ << endl;
    cout << "Stock level: " << product.stock_level_ << endl;
}

void PrintInfo(const Order& order) {
    cout << "Order number: " << order.order_number_ << endl;
    cout << "Client: " << endl;
    PrintInfo(*order.customer_);
    cout << "\nProducts: " << endl;
    for (const Product *product : order.products_) {
        PrintInfo(*product);
    }
}

//Generic classes
template <typename T>
class Inventory {
public:
    // Constructs an empty inventory.
    Inventory() : products_() {}

    // Adds a product to the inventory.
    void AddProduct(const T& product) { products_.push_back(product); }

    // Removes a product from the inventory. Returns true if the product was
    // found and removed, false otherwise.
    bool RemoveProduct(const T& product) {
        auto it = find(products_.begin(), products_.end(), product);
        if (it != products_.end()) {
            products_.erase(it);
            return true;
        }
        return false;
    }

    // Returns the number of products in the inventory.
    size_t GetSize() const { return products_.size(); }

    // Returns the product at the given index.
    const T& GetProduct(size_t index) const { return products_[index]; }

    void printProducts()
    {
        cout<<"Production:\n";
        for (int i = 0; i < products_.size(); ++i) {
            cout<<products_[i].GetName();
            if(i!=products_.size()-1)
                cout<<", ";
        }
        cout<<"\n";
    }
private:
    vector<T> products_;
};

template <typename T>
class OrderHistory {
public:
    // Constructs an empty order history.
    OrderHistory() : orders_() {}

    // Adds an order to the history.
    void AddOrder(const T& order) { orders_.push_back(order); }

    // Returns the number of orders in the history.
    size_t GetSize() const { return orders_.size(); }

    // Returns the order at the given index.
    const T& GetOrder(size_t index) const { return orders_[index]; }
    
    void printOrders()
    {
        for (T i: orders_) {
            cout<<i<<" ";
        }
    }
private:
    vector<T> orders_;
};

template <typename P, typename C>
class Store {
public:
    Store(string name, string location, vector<P*> products, vector<C*> customers)
            : name_(name), location_(location), products_(products), customers_(customers) {}

    string GetName() const { return name_; }
    string GetLocation() const { return location_; }
    vector<P*> GetProducts() const { return products_; }
    vector<C*> GetCustomers() const { return customers_; }

private:
    string name_;
    string location_;
    vector<P*> products_;
    vector<C*> customers_;
};

template <typename T>
class EmployeeDirectory {
public:
    // Constructs an empty employee directory.
    EmployeeDirectory() : employees_() {}

    // Adds an employee to the directory.
    void AddEmployee(const T& employee) { employees_.push_back(employee); }

    // Removes an employee from the directory. Returns true if the employee was
    // found and removed, false otherwise.
    bool RemoveEmployee(const T& employee) {
        auto it = find(employees_.begin(), employees_.end(), employee);
        if (it != employees_.end()) {
            employees_.erase(it);
            return true;
        }
        return false;
    }
    //void RemoveEmployee(size_t index) { employees_.erase(employees_.begin() + index); }

    // Returns the number of employees in the directory.
    size_t GetSize() const { return employees_.size(); }

    // Returns the employee at the given index.
    const T& GetEmployee(size_t index) const { return employees_[index]; }

    void printEmployees()
    {
        cout<<"Employees:\n";
        for (int i = 0; i < employees_.size(); ++i) {
            cout<<employees_[i].GetName()<<" - "<<employees_[i].GetJobTitle();
            if(i!=employees_.size()-1)
                cout<<",\n";
        }
        cout<<"\n";
    }
private:
    vector<T> employees_;
};

template <typename T>
class CustomerDatabase {
public:
    // Constructs an empty customer database.
    CustomerDatabase() : customers_() {}

    // Adds a customer to the database.
    void AddCustomer(const T& customer) { customers_.push_back(customer); }

    // Removes a customer from the database. Returns true if the customer was
    // found and removed, false otherwise.
    bool RemoveCustomer(const T& customer) {
        auto it = find(customers_.begin(), customers_.end(), customer);
        if (it != customers_.end()) {
            customers_.erase(it);
            return true;
        }
        return false;
    }

    // Returns the number of customers in the database.
    size_t GetSize() const { return customers_.size(); }

    // Returns the customer at the given index.
    const T& GetCustomer(size_t index) const { return customers_[index]; }

    void printCustomers()
    {
        cout<<"Clients:\n";
        for (int i = 0; i < customers_.size(); ++i) {
            cout<<customers_[i].GetName();
            if(i!=customers_.size()-1)
                cout<<", ";
        }
        cout<<"\n";
    }


private:
    vector<T> customers_;
};

//abstraction classes
class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;

    // Processes a payment using this payment method.
    virtual void ProcessPayment(double amount) = 0;

    // Returns the current balance for this payment method.
    virtual double CheckBalance() const = 0;
};

class ShippingMethod {
public:
    virtual ~ShippingMethod() = default;

    // Calculates the cost to ship using this shipping method.
    virtual double CalculateCost(double weight, double distance) = 0;

    // Tracks the shipment using this shipping method.
    virtual string TrackShipment() const = 0;
};

class Warranty {
public:
    virtual ~Warranty() = default;

    // Returns true if this warranty is currently valid.
    virtual bool IsValid() const = 0;

    // Submits a claim for this warranty.
    virtual void SubmitClaim() = 0;
};

class Promotion {
public:
    virtual ~Promotion() = default;

    // Applies a discount using this promotion.
    virtual void ApplyDiscount(double& price) = 0;

    // Returns true if the given item is eligible for this promotion.
    virtual bool CheckEligibility(const string& item) const = 0;
};

class CreditCardPayment : public PaymentMethod {
public:
    void ProcessPayment(double amount) override {
        cout << "Processing payment of $" << amount << " using credit card." << endl;
    }

    double CheckBalance() const override {
        return 1000.00;
    }
};

class FedExShipping : public ShippingMethod {
public:
    double CalculateCost(double weight, double distance) override {
        return (weight * 0.5) + (distance * 0.25);
    }

    string TrackShipment() const override {
        return "FDX123456789";
    }
};

class ExtendedWarranty : public Warranty {
public:
    bool IsValid() const override {
        return true;
    }

    void SubmitClaim() override {
        cout << "Submitting warranty claim." << endl;
    }
};

class DiscountPromotion : public Promotion {
public:
    void ApplyDiscount(double& price) override {
        price = price * 0.9;
    }

    bool CheckEligibility(const string& item) const override {
        return item == "product-123";
    }
};

#define N 1
int main() {
    //These are examples of using some methods of each class with sample data
#if N==1
    cout<<"\tClass Person:\n";
    Person person("Anna", 25, "ul. Kowalska 1");
    PrintInfo(person); //Other methods that can be used - GetAddress, GetName, GetAge

    cout<<"\n---------------------------------------------------------\n\n";
    cout<<"\tClass Employee:\n";
    Employee employee("Jan", 30, "ul. Nowak 2", "Manager", 10000.0);
    PrintInfo(employee); //GetJobTitle, GetSalary + metody persony
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass Customer:\n";
    Customer customer("Piotr", 40, "ul. Wisniewski 3", {"Zestaw kuchenny", "Lodowka"}, 100);
    PrintInfo(customer); //GetPurchaseHistory, GetLoyaltyPoints + person
    cout<<"\n---------------------------------------------------------\n\n";
    cout<<"\tClass Product:\n";
    Product product("Telewizor", 2000.0, 10);
    PrintInfo(product); //GetName, GetPrice, GetStockLevel
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass Order:\n";
    Order order(1, &customer, {&product});
    PrintInfo(order); //GetCustomer, GetOrderNumber, GetProducts + operatory *= += -= << ==
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass Manager:\n";
    Manager man("Jan",35,"ul.Kwiatowa 23","Manager",75000,10,100000);
    man.PrintInfo();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass Salesperson:\n";
    Salesperson sal("Kamil",20,"ul.Prosta 15","Salesperson",52000,100000,0.1);
    sal.PrintInfo(); //GetSalesTargets, GetComission + Employee
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass Technician:\n";
    vector<string>skills = {"JavaScript","HTML","CSS"};
    vector<string>certifications = {"Front end course", "Stopien naukowy w dziedzinie informatyki"};
    Technician tech("Mikolaj",23,"ul.Ciepla 11","Front-end junior developer",4000,skills, certifications);
    //GetSkills, GetCertifications + Employee
    tech.PrintInfo();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass Receptionist:\n";
    vector<string>languages = {"Hiszpanski","Niemiecki","Angielski","Polski"};
    Receptionist receptionist("Samantha Smith", 25, "321 Front Desk St", "Receptionist", 30000, languages,"5 lat w obsludze klienta");
    //GetCustomerServiceExperience, GetLanguageSkills + Employee
    cout<<"Name: "<<receptionist.GetName()<<"\nExperience: "<<receptionist.GetCustomerServiceExperience();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass Accountant:\n";
    Accountant accountant("Michael Williams", 45, "654 Accounting Ave", "Accountant", 80000, 100000.0);
    //GetBudget + Employee
    cout<<"Name: "<<accountant.GetName()<<"\nBudget: "<<accountant.GetBudget();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass RegularCustomer:\n";
    vector<string> purchase_history = {"ksiazka", "dlugopis", "notatnik"};
    RegularCustomer regular_customer("Anna Jones", 22, "159 Regular St", purchase_history, 50, "Cash");
    //GetPreferredPaymentMethod, SetPreferredPaymentMethod + Customer
    cout<<"Name: "<<regular_customer.GetName()<<"\nPayment method: "<<regular_customer.GetPreferredPaymentMethod();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass VIPCustomer:\n";
    VIPCustomer vip_customer("Jack Smith", 40, "753 VIP Ave", purchase_history, 100, 0.2);
    //GetDiscount + customer
    cout<<"Name: "<<vip_customer.GetName()<<"\nDiscount: "<<vip_customer.GetDiscount()*100<<"%";
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass PhysicalProduct:\n";
    PhysicalProduct physical_product("laptop", 1000, 10, "warehouse", false);
    //IsFragile, GetLocation + product
    cout<<"Name: "<<physical_product.GetName()<<"\nLocation: "<<physical_product.GetLocation();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass DigitalProduct:\n";
    DigitalProduct digital_product("ebook", 20, 50, "PDF", 1000);
    //GetFileSize, GetFileType + product
    cout<<"Name: "<<digital_product.GetName()<<"\nFile size: "<<digital_product.GetFileSize();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tClass CustomProduct:\n";
    vector<string> materials = {"Skora", "drewniana rama"};
    CustomProduct custom_product("krzeslo na zamowienie", 300, 5, materials, "4 tygodnie");
    //GetMaterials, GetProductionTime + product
    cout<<"Name: "<<custom_product.GetName()<<"\nProduction time: "<<custom_product.GetProductionTime();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tGeneric Class EmployeeDirectory:\n";
    EmployeeDirectory<Employee> directory; //GetEmployee, GetSize
    directory.AddEmployee(man);
    directory.AddEmployee(sal);
    directory.AddEmployee(accountant);
    directory.printEmployees();
    directory.RemoveEmployee(sal);
    cout<<"\nAfter deletion: \n";
    directory.printEmployees();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tGeneric Class Inventory:\n";
    Inventory<Product> inv; //GetProduct, GetSize
    inv.AddProduct(digital_product);
    inv.AddProduct(physical_product);
    inv.AddProduct(product);
    inv.printProducts();
    inv.RemoveProduct(physical_product);
    cout<<"\nAfter deletion: \n";
    inv.printProducts();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tGeneric Class OrderHistory:\n";
    OrderHistory<Order> history; //GetOrder, GetSize
    Order order1(2,&vip_customer, {&digital_product,&physical_product});
    history.AddOrder(order);
    history.AddOrder(order1);
    history.printOrders();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tGeneric Class Store:\n";
    vector<Customer*>customers{&vip_customer,&regular_customer};
    vector<Product*>products{&digital_product,&custom_product};
    Store<Product,Customer> store("Sklep","Warszawa",products,customers);
    cout<<"Name: "<<store.GetName(); //GetCustomers, GetLocation, GetProducts
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tGeneric Class CustomerDatabase:\n";
    CustomerDatabase<Customer> customer_db;
    customer_db.AddCustomer(vip_customer);
    customer_db.AddCustomer(regular_customer);
    customer_db.printCustomers();
    customer_db.RemoveCustomer(vip_customer);
    cout<<"\nAfter deletion: \n";
    customer_db.printCustomers();
    cout<<"\n---------------------------------------------------------\n\n";

    cout<<"\tUsing of abstract classes:\n";
    unique_ptr<PaymentMethod> paymentMethod = make_unique<CreditCardPayment>();
    double amount = 50.00;
    paymentMethod->ProcessPayment(amount);

    double balance = paymentMethod->CheckBalance();
    cout << "Balance: " << balance << endl;

    unique_ptr<ShippingMethod> shippingMethod = make_unique<FedExShipping>();

    double weight = 2.5, distance = 1000.0;
    double cost = shippingMethod->CalculateCost(weight, distance);
    cout << "Shipping cost: " << cost << endl;

    string tracking = shippingMethod->TrackShipment();
    cout << "Tracking number: " << tracking << endl;

    unique_ptr<Warranty> warranty = make_unique<ExtendedWarranty>();

    if (warranty->IsValid()) {
        cout << "Warranty is valid." << endl;
    } else {
        cout << "Warranty is not valid." << endl;
    }

    warranty->SubmitClaim();

    unique_ptr<Promotion> promotion = make_unique<DiscountPromotion>();

    string item = "product-123";
    if (promotion->CheckEligibility(item)) {
        cout << "Item is eligible for promotion." << endl;

        double price = 100.00;
        promotion->ApplyDiscount(price);
        cout << "Discounted price: " << price << endl;
    } else {
        cout << "Item is not eligible for promotion." << endl;
    }
#endif

    return 0;
}
