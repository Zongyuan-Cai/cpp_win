#include <iostream>
#include <string>
using namespace std;
class Invoice
{
private:
    string id;
    string desciption;
    int quantity;
    double price;

public:
    Invoice(string id, string desciption, int quantity, double price) : id(id), desciption(desciption)
    {
        if (quantity < 0)
        {
            this->quantity = 0;
        }
        else
        {
            this->quantity = quantity;
        }
        if (price < 0)
        {
            this->price = 0.0;
        }
        else
        {
            this->price = price;
        }
    }
    void setid(string id)
    {
        this->id = id;
    }
    string getid()
    {
        return id;
    }
    void setdesciption(string desciption)
    {
        this->desciption = desciption;
    }
    string getdesciption()
    {
        return desciption;
    }
    void setquantity(int quantity)
    {
        if (quantity < 0)
        {
            this->quantity = 0;
        }
        else
        {
            this->quantity = quantity;
        }
    }
    int getquantity()
    {
        return quantity;
    }
    void setprice(double price)
    {
        if (price < 0)
        {
            this->price = 0.0;
        }
        else
        {
            this->price = price;
        }
    }
    double getprice()
    {
        return price;
    }
    double getInvoiceAmount()
    {
        return quantity * price;
    }
};
int main()
{
    Invoice invoice("001", "Laptop", 2, 1500.0);
    cout << "Invoice ID: " << invoice.getid() << endl;
    cout << "Description: " << invoice.getdesciption() << endl;
    cout << "Quantity: " << invoice.getquantity() << endl;
    cout << "Price per item: $" << invoice.getprice() << endl;
    cout << "Total Invoice Amount: $" << invoice.getInvoiceAmount() << endl;
    return 0;
}
