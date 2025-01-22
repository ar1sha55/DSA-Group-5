#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 100;

class Staff
{
    private:
        string staffID, password;
    public:
        Staff(){};
        Staff(string id, string pass)
        {
            staffID = id;
            password = pass;
        }
        string getStaffID(){return staffID;}
        string getStaffPassword(){return password;}
};

class CustOrder {
    
    private:
        string custName, contactNum, orderStatus;
        string orderID;
        int counter = 0;

        string itemName[MAX_SIZE];
        int itemPrice[MAX_SIZE];
        
    public:
        vector<string> items;
        CustOrder(string cust ="", string contact ="", string order ="Preparing", string o = "")
        {
            custName = cust;
            contactNum = contact;
            orderStatus = order;
            orderID = o;
        }
        string getCustName(){return custName;}
        string getContactNum(){return contactNum;}
        string getOrderStatus(){return orderStatus;}
        string getOrderID(){return orderID;}

        void setCustName() {
            cout << "Enter Name: ";
            getline(cin, custName);
        }

        void setContactNumber() {
            cout << "Enter Phone Number: ";
            getline(cin, contactNum);
        }

        void setOrderID(int o)
        {
            string ID = "OID";
            ID = ID + to_string(o);
            orderID = ID;
        }

        void setOrderStatus()
        {
            string status;
            cout << "Current Status: " << orderStatus << endl;
            cout << "New Status: ";
            getline(cin, status);
            orderStatus = status;
            cout << "\n\nStatus Has Been Changed!" << endl;
            system("pause");
        }

        void addToCart(string n, double p)
        {
            itemName[counter] = n;
            itemPrice[counter] = p;
            counter++;
        }

        void viewOrder()
        {
            for(int i=0; i<counter; i++)
            {
                cout << left;
                cout << i+1 << setw(2) << "." << setw(15) << itemName[i] << "RM " << itemPrice[i] << endl;
            }
        }
};

class Pizza
{
    private:
        string pizzaID, pizzaName;
        int price_personal, price_reg, price_large;
    public:
        Pizza(){};
        Pizza(string id, string name, int price_p, int price_r, int price_l)
        {
            pizzaID = id;
            pizzaName = name;
            price_personal = price_p;
            price_reg = price_r;
            price_large = price_l;
        }

        void setID()
        {
            cout << "Enter Pizza ID: ";
            getline(cin, pizzaID);
        }
        
        void setname()
        {
            cout << "Enter Pizza Name: ";
            getline(cin, pizzaName);
        }

        void setPersonal()
        {
            cout << "Enter Personal Price: RM ";
            cin >> price_personal;
        }

        void setRegular()
        {
            cout << "Enter Regular Price: RM ";
            cin >> price_reg;
        }

        void setLarge()
        {
            cout << "Enter Large Price: RM ";
            cin >> price_large;
        }

        string getPizzaID() {return pizzaID;}
        string getPizzaName() {return pizzaName;}
        int getPersonal() {return price_personal;}
        int getRegular() {return price_reg;}
        int getLarge() {return price_large;}

        void pizzaInfoCust()
        {
            cout << left;
            cout << setw(15) << pizzaName << "RM " << setw(8) << price_personal << "RM " << setw(8) << price_reg << "RM " << price_large << endl;
        }
        void pizzaInfoStaff()
        {
            cout << left;
            cout << setw(10) << pizzaID << setw(15) << pizzaName << "RM " << setw(8) << price_personal << "RM " << setw(8) << price_reg << "RM " << price_large << endl;
        }
        
        
};

class PizzaNode
{
    public:
        Pizza pizza;
        PizzaNode* next;
        PizzaNode* prev;
        PizzaNode(){};
        PizzaNode(Pizza p)
        {
            pizza = p;
            next = NULL;
            prev = NULL;
        }    

};

class DoublyLLPizza
{
    private:
        PizzaNode* head;
        PizzaNode* tail;

    public:
        DoublyLLPizza() {head = NULL; tail = NULL;}

        void displayAllPizza(int Usertype)
        {
            PizzaNode* currentPizza = head;
            if(head == NULL)
            {
                cout << "Currently No Pizza Available!" << endl;
                return;
            }

            int counter = 1;
            switch(Usertype)
            {
                case 1:
                    cout << "PIZZA" << endl;
                    cout << left;
                    cout << setw(4) << " " << setw(15) << "Name" << setw(11) << "Personal" << setw(11) << "Regular" << "Large" << endl;
                    while(currentPizza != NULL)
                    {
                        cout << "[" << counter++ << "] ";
                        currentPizza->pizza.pizzaInfoCust();
                        currentPizza = currentPizza->next;
                    }
                    break;
                case 2:
                    cout << left;
                    cout << setw(3) << " " << setw(10) << "PizzaID" << setw(15) << "Name" << setw(11) << "Personal" << setw(11) << "Regular" << "Large" << endl;
                    while(currentPizza != NULL)
                    {
                        cout << counter++ << ". ";
                        currentPizza->pizza.pizzaInfoStaff();
                        currentPizza = currentPizza->next;
                    }
            }
        }

        PizzaNode *getHead() {
            return head;
        }

        void addPizza()
        {
            Pizza p;
            p.setID();
            p.setname();
            p.setPersonal();
            p.setRegular();
            p.setLarge();

            PizzaNode* newPizza = new PizzaNode(p);
            
            if(head == NULL)
            {
                newPizza->next = NULL;
                newPizza->prev = NULL;
                head = tail = newPizza;
            }

            tail->next = newPizza;
            newPizza->next = NULL;
            newPizza->prev = tail;
            tail = newPizza;

            
            ofstream outFile("PizzaHistory.txt", ios::app); // Open in append mode
            if (outFile.is_open()) {
                 outFile << p.getPizzaID() << " " 
                << p.getPizzaName() << " " 
                << p.getPersonal() << " "
                << p.getRegular() << " " 
                << p.getLarge() << endl;

                 outFile.close();
                cout << "Pizza details saved to file." << endl;
            } else {
                cerr << "Error: Could not open file to save pizza details." << endl;
            }
        }

        void deletePizza()
        {
            int deleteNo;
            PizzaNode* delNode = head;
            int currentIndex = 1;

            displayAllPizza(2);
            
            if(head == NULL)
                return;

            cout << "Enter No: ";
            cin >> deleteNo;

            while(currentIndex != deleteNo)
            {
                currentIndex++;
                delNode = delNode->next;
            }

            //delete the only one item left in the list
            if(head == tail)
            {
                head = NULL;
                tail = NULL;
                return;
            }
            //delete the last item 
            else if(delNode->next == NULL)
            {
                delNode->prev->next = NULL;
                tail = delNode->prev;
            }
            //delete the first item with only 2 items in the list
            else if(head->next == tail)
            {
                head = tail;
                head->prev = NULL;
            }
            //delete the first item with few items in the list
            else if(delNode->prev == NULL && delNode->next != NULL)
            {
                head = delNode->next;
                head->prev = NULL;
            }
            //delete the item in the middle
            else
            {
                delNode->prev->next = delNode->next;
                delNode->next->prev = delNode->prev;
            }

            delete delNode;
            cout << endl;
            cout << "Pizza Deleted!" << endl;
        }

        void modifyPizza()
        {
            int modifyNo;
            PizzaNode* modifyNode = head;
            int currentIndex = 1;
            char ch;

            modify:
            displayAllPizza(2);

            if(head == NULL)
                return;

            cout << endl;
            cout << "Enter No (Press 0 to back) : ";
            cin >> modifyNo;

            if(modifyNo == 0)
                return;

            while(currentIndex != modifyNo)
            {
                currentIndex++;
                modifyNode = modifyNode->next;
            }

            system("cls");
            cout << "Selected Pizza: ";
            modifyNode->pizza.pizzaInfoStaff();
            cout << endl;

            cout << "Change Name? (Y/N): ";
            ch = getch();
            cout << ch;
            cin.ignore();

            if(toupper(ch) == 'Y')
            {
                cout << endl;
                modifyNode->pizza.setname();
            }
            
            cout << endl;
            cout << "Change Price? (Y/N): ";
            ch = getch();
            cout << ch;
            cin.ignore();

            if(toupper(ch) == 'Y')
            {
                modifyNode->pizza.setPersonal();
                modifyNode->pizza.setRegular();
                modifyNode->pizza.setLarge();
            }
            else
            {
                return;
            }

            cout << endl;
            cout << "Pizza Updated!" << endl;
            cout << "New: ";
            modifyNode->pizza.pizzaInfoStaff();
        }
};

class Drink
{
    private:
        string drinkID, drinkName;
        double price;
    public:
        Drink(){};
        Drink(string id, string name, double p)
        {
            drinkID = id;
            drinkName = name;
            price = p;
        }
        
        void setID()
        {
            cout << "Enter Drink ID: ";
            getline(cin, drinkID);
        }

        void setName()
        {
            cout << "Enter Drink Name: ";
            getline(cin,drinkName);
        }

        void setprice()
        {
            cout << "Enter Price: ";
            cin >> price;
        }

        string getDrinkID(){return drinkID;}
        string getDrinkName(){return drinkName;}
        double getDrinkPrice(){return price;}
        void drinkInfoCust()
        {
            cout << left;
            cout << setw(15) <<  drinkName << "RM " << price << endl;
        }

        void drinkInfoStaff()
        {
            cout << left;
            cout << setw(10) << drinkID << setw(15) <<  drinkName << "RM " << price << endl;
        }
};

class DrinkNode
{
    public:
        Drink drink;
        DrinkNode* next;
        DrinkNode* prev;
        DrinkNode(){};
        DrinkNode(Drink d)
        {
            drink = d;
            next = NULL;
            prev = NULL;
        }
};

class DoublyLLDrink
{
    private:
        DrinkNode* head;
        DrinkNode* tail;

    public:
        DoublyLLDrink() {head = NULL; tail = NULL;}

        void displayAllDrink(int Usertype)
        {
            DrinkNode* currentPizza = head;
            if(head == NULL)
            {
                cout << "Currently No Drink Available!" << endl;
                return;
            }

            int counter = 1;
            switch(Usertype)
            {
                case 1:
                    cout << left;
                    cout << "DRINKS" << endl;
                    cout << setw(4) << " " << setw(15) << "Name" << "Price" << endl;
                    while(currentPizza != NULL)
                    {
                        cout << "[" << counter++ << "] ";
                        currentPizza->drink.drinkInfoCust();
                        currentPizza = currentPizza->next;
                    }
                    break;
                case 2:
                    cout << left;
                    cout << setw(3) << " " << setw(10) << "DrinkID" << setw(15) << "Name" << "Price" << endl;
                    while(currentPizza != NULL)
                    {
                        cout << counter++ << ". ";
                        currentPizza->drink.drinkInfoStaff();
                        currentPizza = currentPizza->next;
                    }
            }
        }

        DrinkNode *getHead() {
            return head;
        }

        void addDrink()
        {
            Drink d;
            d.setID();
            d.setName();
            d.setprice();
            
            DrinkNode* newDrink = new DrinkNode(d);
            if(head == NULL)
            {
                newDrink->next = NULL;
                newDrink->prev = NULL;
                head = tail = newDrink;
            }

            tail->next = newDrink;
            newDrink->next = NULL;
            newDrink->prev = tail;
            tail = newDrink;

            ofstream outFile("DrinkHistory.txt", ios::app); // Open in append mode
            if (outFile.is_open()) {
                 outFile << d.getDrinkID() << " " 
                << d.getDrinkName() << " " 
                << d.getDrinkPrice() << endl;

                 outFile.close();
                cout << "Drink details saved to file." << endl;
            } else {
                cerr << "Error: Could not open file to save pizza details." << endl;
            }
        }

        void deleteDrink()
        {
            int deleteNo;
            DrinkNode* delNode = head;
            int currentIndex = 1;

            displayAllDrink(2);
            
            if(head == NULL)
                return;

            cout << "Enter No: ";
            cin >> deleteNo;

            while(currentIndex != deleteNo)
            {
                currentIndex++;
                delNode = delNode->next;
            }

            //delete the only one item left in the list
            if(head == tail)
            {
                head = NULL;
                tail = NULL;
                return;
            }
            //delete the last item 
            else if(delNode->next == NULL)
            {
                delNode->prev->next = NULL;
                tail = delNode->prev;
            }
            //delete the first item with only 2 items in the list
            else if(head->next == tail)
            {
                head = tail;
                head->prev = NULL;
            }
            //delete the first item with few items in the list
            else if(delNode->prev == NULL && delNode->next != NULL)
            {
                head = delNode->next;
                head->prev = NULL;
            }
            //delete the item in the middle
            else
            {
                delNode->prev->next = delNode->next;
                delNode->next->prev = delNode->prev;
            }

            delete delNode;
            cout << endl;
            cout << "Drink Deleted!" << endl;
        }

        void modifyDrink()
        {
            int modifyNo;
            DrinkNode* modifyNode = head;
            int currentIndex = 1;
            char ch;

            modify:
            displayAllDrink(2);

            if(head == NULL)
                return;

            cout << endl;
            cout << "Enter No (Press 0 to back) : ";
            cin >> modifyNo;

            if(modifyNo == 0)
                return;

            while(currentIndex != modifyNo)
            {
                currentIndex++;
                modifyNode = modifyNode->next;
            }

            system("cls");
            cout << "Selected Drink: ";
            modifyNode->drink.drinkInfoStaff();
            cout << endl;

            cout << "Change Name? (Y/N): ";
            ch = getch();
            cout << ch;

            if(toupper(ch) == 'Y')
            {
                cout << endl;
                cin.ignore();
                modifyNode->drink.setName();
            }
            
            cout << endl;
            cout << "Change Price? (Y/N): ";
            ch = getch();
            cout << ch;

            if(toupper(ch) == 'Y')
            {
                cin.ignore();
                modifyNode->drink.setprice();
            }
            else
            {
                return;
            }

            cout << endl;

            cout << "Drink Updated!" << endl;
            cout << "New: ";
            modifyNode->drink.drinkInfoStaff();
        }
};

class OrderNode
{
    public:
        CustOrder order;
        OrderNode* next;
        OrderNode(){};
        OrderNode(CustOrder o)
        {
            order = o;
            next = NULL;
        }
};

class QueueOrder
{
    private:
        OrderNode* front;
        OrderNode* back;
        int orderID = 1;
    public:
        QueueOrder() {front = NULL; back = NULL;}

        //check if queue empty
        bool isEmpty()
        {
            return (back == NULL && front == NULL);
        }

        //add order to queue
        void enqueue(CustOrder x)
        {
            CustOrder newCust;
            cin.ignore();
            newCust.setCustName();
            newCust.setContactNumber();

            OrderNode* newOrder = new OrderNode(newCust);
            newOrder->order.setOrderID(orderID++);

            if(isEmpty())
            {
                front = back = newOrder;
            }
            else
            {
                back->next = newOrder;
                back = newOrder;
                back->next = NULL;
            }
        }

        //order has been done and exit from the queue
        void dequeue()
        {
            OrderNode *curr = front;

            if(curr->next == NULL)
            {
                front = back = NULL;
            }
            else
                front = curr->next;

            cout << curr->order.getOrderID() << " Removed from Queue!" << endl;
            delete curr;

            if(!front) 
                back = NULL;
            
        }

        //display all order
        int displayOrder()
        {
            if(isEmpty())
            {
                cout << "No Order Currently Available!" << endl << endl;
                return 0;
            }

            OrderNode *curr = front;

            cout << "ORDERS"<< endl << endl;
            cout << left;
            cout << setw(20) << "Customer Name" << setw(15) << "OrderID" << "Status" << endl;
            while(curr != nullptr)
            {
                cout << setw(20) << curr->order.getCustName() << setw(15) << curr->order.getOrderID() << curr->order.getOrderStatus() << endl;
                curr = curr->next;
            }
            return 1;
        }

        OrderNode *getBack() {return back;}
        OrderNode *getFront() {return front;}
};

void customer_menu(int& custChoice)
{
    cout << "PIZZARIA RESTAURANT" << endl << endl;
    cout << "1. View All Menu" << endl;
    cout << "2. View Order Status" << endl<< endl;

    cout << "Enter choice (Press 0 to back): ";
    cin >> custChoice;
}

void staff_menu(int& staffChoice)
{
    cout << "PIZZARIA RESTAURANT" << endl << endl;
    cout << "1. Manage Menu" << endl;
    cout << "2. Manage Order" << endl;
    cout << "3. View All Running Order" << endl;
    cout << "4. Monthly Report" << endl << endl;

    cout << "Enter choice (Press 0 to back): ";
    cin >> staffChoice;
}

int manage_menu()
{
    int manage_choice;
    cout << "PIZZARIA RESTAURANT" << endl << endl;
    cout << "1. Add Pizza" << endl;
    cout << "2. Add Drink" << endl;
    cout << "3. Delete Pizza" << endl;
    cout << "4. Delete Drink" << endl;
    cout << "5. Modify Pizza" << endl;
    cout << "6. Modify Drink" << endl;
    cout << "7. Display All Pizza and Drink" << endl << endl;

    cout << "Enter choice (Press 0 to back): ";
    cin >> manage_choice;

    return manage_choice;
}

int StaffAuth(Staff arr[], int found)
{
    string staffID, password;
    int ch;
    cout << "PIZZARIA RESTAURANT" << endl << endl;

    cout << "Staff ID: ";
    getline(cin, staffID);
    cout << "Password: ";

    while (true) 
    {
        ch = getch(); // Reads a single character
        if (ch == 13) 
            break;
        else if (ch == 8) 
        { // Backspace key
            if (!password.empty()) 
            {
                password.pop_back(); // Remove the last character
                cout << "\b \b"; // Remove character from display
            }
        } 
        else 
        {
            password += ch; // Add the character to the string
            cout << '*'; // Print asterisk for masking
        }
    }
    
    for(int i=0; i<3; i++)
    {
        if(arr[i].getStaffID() == staffID && arr[i].getStaffPassword() == password)
            return found = 1;
    }
    return 0;
}

void dispTri() 
{
    cout << " \\    /  \\    /  \\    /  \\    /  \\    /  \\    /";
    cout << "\n  \\  /    \\  /    \\  /    \\  /    \\  /    \\  /";
    cout << "\n   \\/      \\/      \\/      \\/      \\/      \\/";
}

void dispLine() 
{
    cout << "------------------------------------------------" << endl;
}

int main()
{
    string choice;
    char ch; //biar semua function boleh pakai

     //Pizza Variables
    DoublyLLPizza pizzaList;

    //Drink Variables
    DoublyLLDrink drinkList;

    //Order Variables
    QueueOrder order;

    //Customer Variables
    CustOrder cust;

    //Staff Variables
    Staff staffArray[2] = { Staff("A23CS0111", "Staff123"),
                            Staff("A23CS0154", "Staff123")};
    int found = 0;
    int staffChoice, custChoice;
    int manage_choice;
    string custOID, newStatus;

    back:
    cout << "PIZZARIA RESTAURANT" << endl << endl;

    cout << "1. Staff \n2. Customer \n3. Exit" << endl << endl;
    cout << "Enter choice: ";
    cin >> choice;

    system("cls");
    cin.ignore();

    if(choice == "1")
        goto staff;
    else if(choice == "2")
        goto customer;
    else if(choice == "3")
    {
        cout << "Bye :>" << endl;
        return 0;
    }
    else
    {
        system("cls");
        cout << "Invalid Input!" << endl;
        goto back;
    }

    staff:
    found = StaffAuth(staffArray, found);
    
    if(!found)
    {
        system("cls");
        cout << "Invalid Staff ID or Password!" << endl;
        goto staff;
    }
    
    cout << "PIZZARIA RESTAURANT" << endl << endl;

    staffMenu:
    system("cls");
    staff_menu(staffChoice);

    system("cls");

    switch(staffChoice)
    {
        case 1: 
            manageMenu:
            system("cls");
            manage_choice = manage_menu();
            system("cls");

            switch(manage_choice)
            {
                case 1 :
                    do
                    {
                        system("cls");
                        pizzaList.displayAllPizza(2);
                        cout << endl;
                        cin.ignore();

                        pizzaList.addPizza();
                        system("cls");

                        pizzaList.displayAllPizza(2);
                        
                        cout << endl;
                        cout << "Add More? (Y/N): ";
                        cin >> ch;
                    } while(toupper(ch) == 'Y');

                    cout << endl;
                    system("pause");
                    goto manageMenu;
                    break;
                
                case 2 :
                    do
                    {
                        system("cls");
                        drinkList.displayAllDrink(2);
                        cout << endl;
                        cin.ignore();

                        drinkList.addDrink();
                        system("cls");

                        drinkList.displayAllDrink(2);
                        
                        cout << endl;
                        cout << "Add More? (Y/N): ";
                        cin >> ch;
                    } while(toupper(ch) == 'Y');

                    cout << endl;
                    system("pause");
                    goto manageMenu;
                    break;
                
                case 3 :
                    pizzaList.deletePizza();
                    cout << endl;
                    system("pause");
                    goto manageMenu;
                    break;
                
                case 4 :
                    drinkList.deleteDrink();
                    cout << endl;
                    system("pause");
                    goto manageMenu;
                    break;
                
                case 5 : 
                    pizzaList.modifyPizza();
                    cout << endl;
                    system("pause");
                    goto manageMenu;
                    break;

                case 6 :
                    drinkList.modifyDrink();
                    cout << endl;
                    system("pause");
                    goto manageMenu;
                    break;

                case 7 : 
                    cout << "PIZZA" << endl;
                    pizzaList.displayAllPizza(2);

                    cout << "\nDRINK" << endl;
                    drinkList.displayAllDrink(2);

                    cout << endl;
                    system("pause");
                    goto manageMenu;
                    break;

                default : 
                    goto staffMenu; 
                    break; 
            }
        
        case 2: 
        {
            OrderNode* currentNode = order.getFront();
            int exit;

            do
            {
                system("cls");
                cin.ignore();
                exit = order.displayOrder();
                cout << endl;
                cout << "Enter OrderID (Press 0 to back): ";
                getline(cin,custOID);

                if(custOID == "0" || exit == 0)
                    break;


                while(currentNode->order.getOrderID() != custOID)
                {
                    currentNode = currentNode->next;
                }

                system("cls");
                if(currentNode != NULL)
                {
                    cout << "Item Ordered" << endl;
                    currentNode->order.viewOrder();
                    currentNode->order.setOrderStatus();
                }
                else
                {
                    cout << "Invalid Input!";
                    system("pause");
                }

            } while(currentNode == NULL);

            system("cls");

            //check if front order dah "Delivered", then system akan dequeue 
            if((order.getFront() != NULL) && order.getFront()->order.getOrderStatus() == "Delivered")
            {
                //letak delivered order dekat dalam file dulu before dequeue so history tu ada
                ofstream outFile("OrderHistory.txt", ios::app); // Open in append mode
                if (outFile.is_open()) {
                    outFile << left << setw(20) << currentNode->order.getCustName() // Customer name
                            << setw(15) << currentNode->order.getOrderID()  // Order ID
                             << setw(15) << currentNode->order.getOrderStatus() << endl; // Order status
                    outFile.close();
                    cout << "Order details saved to file." << endl;
                } else {
                    cerr << "Error: Could not open file to save order details." << endl;
                }
                //lepas dah letak dalam file, baru dequeue
                order.dequeue();
            }

            goto staffMenu;
            break;
        }

        case 3 :
        {
            order.displayOrder();
            cout << endl;
            system("pause");
            goto staffMenu;
        }
        //buat reporting kat sini. read from file tunjuk semua info pasal order itu
        case 4 : 
        {
            ifstream inFile("OrderHistory.txt", ios::in);
            if(inFile.is_open()) 
            {
                string line;
                dispLine();
                cout << "\t\tMONTHLY ORDER REPORT" << endl;
                dispLine();
                cout << left << setw(20) << "Customer Name" << setw(15) << "OrderID" << setw(15) << "Status" << endl;
                while(getline(inFile, line)) 
                {
                    cout << line << endl;
                }

                dispLine();

                inFile.close();
            } else {
                cerr << "File failed to open. Unable to generate report" << endl;
            }
            system("pause");
            goto staffMenu;
        }
        
        default : 
            system("cls");
            goto back;       
    }

    customer: 
    system("cls");
    string itemName[MAX_SIZE];
    double itemPrice[MAX_SIZE]; //array to store orders
    string input;

    cout << "PIZZARIA RESTAURANT" << endl << endl;
    cout << "1. Make Order" << endl;
    cout << "2. View Existing Order" << endl << endl;
    cout << "Enter choice (Press 0 to back): ";
    cin >> input;

    if(input == "1")
    {
        system("cls");
        cout << "PIZZARIA RESTAURANT" << endl << endl;
        cout << "1. Buy in Ala-Carte" << endl;
        cout << "2. Buy in Combo" << endl << endl;
        cout << "Enter choice: ";
        cin >> input;
        goto menu_display;
    }
    else if(input == "2")
    {
        system("cls");
        cin.ignore();

        cout << "Enter OrderID: ";
        getline(cin, input);

        if(!order.isEmpty())
        {
            cout << endl;
            OrderNode *currentNode = order.getFront();
            while(currentNode->order.getOrderID() != input)
            {
                currentNode = currentNode->next; 
            }

            system("cls");
            if(currentNode != NULL)
            {
                cout << "Item Ordered" << endl;
                currentNode->order.viewOrder();
                cout << endl;
                cout << "Status: " << currentNode->order.getOrderStatus() << endl << endl;;

                system("pause");
            }
            else
            {
                cout << "OrderID not Found :(" << endl;
                system("pause");
            }
            goto customer;
        }
        else
        {
            cout << "OrderID not Found :(" << endl;
            system("pause");
            goto customer;
        }
    }
    else
    {
        system("cls");
        goto back;
    }
    
    menu_display:

    PizzaNode* currentPizza = pizzaList.getHead();
    DrinkNode* currentDrink = drinkList.getHead();

    if(currentPizza == NULL) 
    {
        system("cls");
        cout << "Sorry! All menus are unavailable :(" << endl;
        cout << "--COME AGAIN LATER--" << endl << endl;
        system("pause");
        goto customer;
    }

    system("cls");
    cout << "PIZZARIA RESTAURANT" << endl << endl;
    order.enqueue(cust);
    system("cls");

    OrderNode* newOrder = order.getBack();
    do
    {
        int currentIndex = 1;
        int pizzaNo, drinkNo;
        char size;

        string itemName;
        double itemPrice;

        pizzaList.displayAllPizza(1);
        cout << "\nSelect Pizza You Want (Enter Pizza No.): ";
        cin >> pizzaNo;
        cout << "Enter Size (P/R/L): ";
        cin >> size;

        while(currentIndex != pizzaNo)
        {
            currentPizza = currentPizza->next;
            currentIndex++;
        }

        itemName = currentPizza->pizza.getPizzaName();

        switch(toupper(size))
        {
            case 'P' :
                itemPrice = currentPizza->pizza.getPersonal();
                break;
            case 'R' :
                itemPrice = currentPizza->pizza.getRegular();
                break;
            case 'L' :
                itemPrice = currentPizza->pizza.getLarge();
                break;
        }

        newOrder->order.addToCart(itemName, itemPrice);
        newOrder->order.items.push_back(itemName);

        system("cls");
        if(input == "2")
        {
            system("cls");
            drinkList.displayAllDrink(1);
            cout << "\nSelect Drink You Want (Enter Drink No.): ";
            cin >> drinkNo;

            while(currentIndex != drinkNo)
            {
                currentDrink = currentDrink->next;
                currentIndex++;
            }

            itemName = currentDrink->drink.getDrinkName();
            itemPrice = currentDrink->drink.getDrinkPrice();

            newOrder->order.addToCart(itemName, itemPrice);
        }

        system("cls");
        cout << "Your Cart Currently: " << endl;
        newOrder->order.viewOrder();

        cout << "\nAdd More? (Y/N): ";
        cin >> ch;
        system ("cls");

    }while(toupper(ch) == 'Y');

    dispLine();
    cout << "|\t\tPIZZARIA RECEIPT\t\t|" << endl;
    dispLine();

    cout << left << setw(10) << "Name:" << newOrder->order.getCustName() << endl;
    cout << left << setw(10) << "OrderID:" << newOrder->order.getOrderID() << endl;

    dispLine();
    cout << "Items Ordered:" << endl;
    
    dispLine();
    newOrder->order.viewOrder(); 
    dispLine();

    cout << left << setw(20) << "Order Status:" << newOrder->order.getOrderStatus() << endl;

    dispLine();
    cout << "|\tThank You for Ordering at Pizzaria!\t|" << endl;
    dispLine();
    dispTri();
    cout << endl;
    system("pause");
    
    // Task 1
    // simpan semua data customer dalam file untuk guna dekat report
    // start simpan data dekat line 1043
    // start reporting dekat line 1058

    // Task 2
    // buat satu receipt yang tunjuk semua makanan and harga, cust name, phone no, order id, order status
    // kalau combo dapat discount sikit
    // kalau tak combo, harga normal
    // start dekat line 1225

    // contoh boleh guna ni dalam receipt
    // cout << endl;
    // cout << "Name: " << newOrder->order.getCustName() << endl;
    // cout << "OrderID: " << newOrder->order.getOrderID() << endl;
    // cout << "Order Status: " << newOrder->order.getOrderStatus() << endl;
    
    goto customer;

    return 0;
}