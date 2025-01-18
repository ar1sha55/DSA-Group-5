#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <vector>

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
        int orderID;
        int counter = 0;

        string itemName[MAX_SIZE];
        int itemPrice[MAX_SIZE];
        

    public:
        vector<string> items;
        CustOrder(){};
        CustOrder(string cust, string contact, string order)
        {
            custName = cust;
            contactNum = contact;
            orderStatus = order;
        }
        string getCustName(){return custName;}
        string getContactNum(){return contactNum;}
        string getOrderStatus(){return orderStatus;}

        void setCustName() {
            cout << "Enter customer name: ";
            getline(cin, custName);
        }

        void setContactNumber() {
            cout << "Enter customer number: ";
            getline(cin, custName);
        }

        void addToCart(string n, double p)
        {
            itemName[counter] = n;
            itemPrice[counter] = p;
            counter++;
        }

        void viewCart()
        {
            cout << "Your cart right now: \n";
            for(int i=0; i<counter; i++)
            {
                cout << i+1 << ". " << itemName[i] << "  RM" << itemPrice[i] << endl;
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
            cout << pizzaName << " RM " << price_personal << " RM " << price_reg << " RM " << price_large << endl;
        }
        void pizzaInfoStaff()
        {
            cout << pizzaID << " " << pizzaName << " RM " << price_personal << " RM " << price_reg << " RM " << price_large << endl;
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
            }

            int counter = 1;
            switch(Usertype)
            {
                case 1:
                    cout << "Pizza available for today: \n\n";
                    while(currentPizza != NULL)
                    {
                        cout << "[" << counter++ << "] ";
                        currentPizza->pizza.pizzaInfoCust();
                        currentPizza = currentPizza->next;
                    }
                    break;
                case 2:
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
            cout << drinkName << " RM " << price << endl;
        }

        void drinkInfoStaff()
        {
            cout << drinkID << " " <<  drinkName << " RM " << price << endl;
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
            }

            int counter = 1;
            switch(Usertype)
            {
                case 1:
                    cout << "Drinks available for today: \n\n";
                    while(currentPizza != NULL)
                    {
                        cout << "[" << counter++ << "] ";
                        currentPizza->drink.drinkInfoCust();
                        currentPizza = currentPizza->next;
                    }
                    break;
                case 2:
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
        OrderNode(){}
        OrderNode(CustOrder o)
        {
            order = o;
            next = nullptr;
        }
};

class QueueOrder
{
    private:
        OrderNode* front;
        OrderNode* back;

    public:
        QueueOrder() {front = nullptr; back = nullptr;}

      
        //delete all order
        void deleteAll()
        {
            OrderNode* curr = front;
            
            while(curr)
            {
                front = curr->next;
                delete curr;
                curr = front;
            }

            cout << "== ALL ORDERS HAVE BEEN DELETED ==\n\n";
        }

        //check if queue empty
        bool isEmpty()
        {
            return (back == nullptr && front == nullptr);
        }

        //add order to queue
        void enqueue(CustOrder x)
        {
            OrderNode* newOrder = new OrderNode(x);

            if(isEmpty())
            {
                front = back = newOrder;
            }
            else
            {
                back->next = newOrder;
                back = newOrder;
            }
        }

        //order has been done and exit from the queue
        void dequeue()
        {
            OrderNode *curr = front;

            front = curr->next;
            curr->next = NULL;
            delete curr;

            if(!front) 
            back = NULL;
            
        }

        //display all order
        void displayOrder()
        {
            if(isEmpty())
            {
                cout << "You have not submitted any order.\n\n";
                return;
            }

            OrderNode *curr = front;

            cout << "ORDERS: \n";

            while(curr != nullptr)
            {
                curr->order.viewCart();

                curr = curr->next;
            }

        }

        OrderNode *getFront() {
            return front;
        }


};

int viewMenu()
{
    DoublyLLDrink drink;
    DoublyLLPizza pizza;

    int x = 1;
    int y;

    cout << "MENU FOR TODAY:\nDRINKS:";
    drink.displayAllDrink(x);

    cout << "MENU FOR TODAY:\nPIZZA:";
    pizza.displayAllPizza(x);

    cout << "1. Add Order" << endl;
    cout << "2. View Cart" << endl;

    cout << "Enter choice: \n[ ]\b\b";
    cin >> y;

    return y;
    
}

void addToCart()
{
    string item;

    //tunjuk list menu
    DoublyLLPizza pizza;
    DoublyLLDrink drink;
    pizza.displayAllPizza(1);
    drink.displayAllDrink(1);

    cout << "Insert the name of the ITEM ID you want to add.\n";
    cout << "ITEM ID => [   ]\b\b";
    cin >> item;

    //tanya a la carte ke set
    /*a la carte
    nampak pizza
    drink optional
    */

   /*combo
   pizza
   drink mandatory
   */

  //tanya nak add lagi tak, kalu add tunjuk balik 

  //view cart = tunjuk
}


void customer_menu(int& custChoice)
{
    cout << "PIZZARIA RESTAURANT" << endl << endl;
    cout << "1. View All Menu" << endl;
    cout << "2. View Order Status" << endl<< endl;

    cout << "Enter choice: ";
    cin >> custChoice;
}

void staff_menu(int& staffChoice)
{
    cout << "PIZZARIA RESTAURANT" << endl << endl;
    cout << "1. Manage Menu" << endl;
    cout << "2. Manage Order Status" << endl;
    cout << "3. View All Order" << endl;
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

void StaffAuth(Staff arr[], int& found)
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
            found = 1;
    }
}


int main()
{
    string choice;
    char ch; //biar semua function boleh pakai

     //Pizza Variables
    DoublyLLPizza pizzaList;

    //Drink Variables
    DoublyLLDrink drinkList;

    //Customer Variables
    CustOrder cust;

    //Order Variables
    QueueOrder order;

    //Staff Variables
    Staff staffArray[3] = { Staff("A23CS0111", "Staff123"),
                            Staff("A23CS0154", "Staff123")};
    int found = 0;
    int staffChoice, custChoice;
    int manage_choice;

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
    StaffAuth(staffArray, found);
    
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
                        ch = getch();
                        cout << ch;
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
                        ch = getch();
                        cout << ch;
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

        default : 
            system("cls");
            goto back;
            
    }

    customer: 
    string itemName[MAX_SIZE];
    double itemPrice[MAX_SIZE]; //array to store orders

    menu_display:
    customer_menu(custChoice);

    system("cls");

    switch (custChoice)
    {
    case 1:

            do
            {
            int pizzaNo, drinkNo;
            char size;

            string itemName;
            double itemPrice;


            PizzaNode* currentPizza = pizzaList.getHead();
            DrinkNode* currentDrink = drinkList.getHead();

            if(currentPizza == NULL) 
            {
                system("cls");
                cout << "Sorry! All menus are unavailable :(" << endl;
                cout << "--COME AGAIN LATER--" << endl << endl;
                goto back;
            }

            int currentIndex = 1;

            pizzaList.displayAllPizza(1);
            cout << "\nEnter no. pizza you want: ";
            cin >> pizzaNo;
            cout << "Enter Size(P/R/L): ";
            size = getch();
            cout << size;

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

            cust.addToCart(itemName, itemPrice);
            cust.items.push_back(itemName);


                system("cls");
                cout << "\nDo you wish to add drinks? (Y/N)" << endl;
                ch = getch();
                cout << ch;

                system("cls");

                drinkList.displayAllDrink(1);
                cout << "\nEnter no. of drinks you want: ";
                cin >> drinkNo;

                while(currentIndex != drinkNo)
                {
                    currentDrink = currentDrink->next;
                    currentIndex++;
                }

                itemName = currentDrink->drink.getDrinkName();
                itemPrice = currentDrink->drink.getDrinkPrice();

                cust.addToCart(itemName, itemPrice);
                order.enqueue(cust);

            system("cls");

            cust.viewCart();

            cout << endl;

            cout << "Add More? (Y/N): ";
                    ch = getch();
                    cout << ch << endl;
                    system ("cls");
            } while(toupper(ch) == 'Y');        
            
            goto menu_display;
    break;

    case 2:

        if(pizzaList.getHead() != NULL) 
        {
            cout << "Here is your cart." << endl;
            cust.viewCart();

            if(order.getFront() == NULL) 
            {
                cout << "Delivered! Enjoy Da Mealz." << endl; //takda order dalam queue, staff dah dequeue
            } else {
                cout << "Cooking NYUM NYUM." << endl;//order still in queue
            }

        } else {
            cout << "No items added in the cart yet." << endl; 
        }
        //system("cls");

        goto menu_display;
    
    default:
        system("cls");
        goto back;
    }


}

//saya nak sync!!