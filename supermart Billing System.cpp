#include<iostream>
#include<fstream>
using namespace std;

class shopping {
    private:
        int pcode;
        float price;
        float dis;
        string pname;

    public:
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void rem();
        void list();
        void receipt();
};

void shopping::menu() {
m:
    int choice;
    string email;
    string password;

    cout << "\t\t\t\t______________________________________\n";
    cout << "\t\t\t\t          Supermarket Main Menu       \n";
    cout << "\t\t\t\t______________________________________\n";
    cout << "\t\t\t\t|  1) Administrator   |\n";
    cout << "\t\t\t\t|  2) Buyer           |\n";
    cout << "\t\t\t\t|  3) Exit            |\n";
    cout << "\n\t\t\t Please select: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\t\t\t Please Login \n";
            cout << "\t\t\t Enter Email: ";
            cin >> email;
            cout << "\t\t\t Password: ";
            cin >> password;
            if (email == "admin@gmail.com" && password == "admin123") {
                administrator();
            } else {
                cout << "Invalid email/password";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            exit(0);

        default:
            cout << "Please select from the given options\n";
    }
    goto m;
}

void shopping::administrator() {
m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator menu";
    cout << "\n\t\t\t|_____1) Add the product_____|";
    cout << "\n\t\t\t|_____2) Modify the product__|";
    cout << "\n\t\t\t|_____3) Delete the product__|";
    cout << "\n\t\t\t|_____4) Back to main menu___|";
    cout << "\n\t\t\t|_____5) Exit________________|";
    cout << "\n\n\t Please enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            rem();
            break;
        case 4:
            menu();
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice!";
    }
    goto m;
}

void shopping::buyer() {
m:
    int choice;
    cout << "\n\t\t\t  Buyer \n";
    cout << "\t\t\t_____________  \n";
    cout << "\t\t\t1) Buy product \n";
    cout << "\t\t\t2) Go back     \n";
    cout << "\t\t\t Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            receipt();
            break;
        case 2:
            menu();
            break;
        default:
            cout << "Invalid choice\n";
    }
    goto m;
}

void shopping::add() {
m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t Add new product";

    cout << "\n\n\t Product code of the product: ";
    while (!(cin >> pcode)) {
        cout << "\nWarning: Enter numbers only!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter product code again: ";
    }

    cout << "\n\n\t Name of the product: ";
    cin >> pname;

    cout << "\n\n\t Price of the product: ";
    while (!(cin >> price)) {
        cout << "\nWarning: Enter numbers only!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter price again: ";
    }

    cout << "\n\n\t Discount on product: ";
    while (!(cin >> dis)) {
        cout << "\nWarning: Enter numbers only!\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter discount again: ";
    }

    data.open("database.txt", ios::in);
    if (!data) {
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    } else {
        data >> c >> n >> p >> d;
        while (!data.eof()) {
            if (c == pcode) {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        if (token == 1) {
            cout << "\n\n Duplicate product code! Try again.\n";
            goto m;
        } else {
            data.open("database.txt", ios::app | ios::out);
            data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
        }
    }

    cout << "\n\n\t\t Record inserted!";
}

void shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t\t\t Modify the record";
    cout << "\n\t\t\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\nFile doesn't exist!";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> dis;
        while (!data.eof()) {
            if (pkey == pcode) {
                cout << "\n\t\t Product new code: ";
                while (!(cin >> c)) {
                    cout << "\nWarning: Enter numbers only!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                cout << "\n\t\t Name of the product: ";
                cin >> n;
                cout << "\n\t\t Price: ";
                while (!(cin >> p)) {
                    cout << "\nWarning: Enter numbers only!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                cout << "\n\t\t Discount: ";
                while (!(cin >> d)) {
                    cout << "\nWarning: Enter numbers only!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t Record edited";
                token++;
            } else {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n Record not found!";
        }
    }
}

void shopping::rem() {
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n\t Delete product";
    cout << "\n\n\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "File doesn't exist";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof()) {
            if (pcode == pkey) {
                cout << "\n\n\t Product deleted successfully";
                token++;
            } else {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n Record not found";
        }
    }
}

void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|___________________________________________________________\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "|___________________________________________________________\n";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof()) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::receipt() {
    system("cls");
    fstream data;

    int arrc[100], arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float total = 0;
    float disc = 0;

    cout << "\n\n\t\t\t Receipt ";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty database";
    } else {
        data.close();
        list();
        cout << "\n____________________________\n";
        cout << "\n|    Please place the order  |";
        cout << "\n|____________________________|\n";
        do {
        m:
            cout << "\n\n Product Code: ";
            while (!(cin >> arrc[c])) {
                cout << "\nWarning: Enter numbers only!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Enter product code again: ";
            }
            cout << " Product Quantity: ";
            while (!(cin >> arrq[c])) {
                cout << "\nWarning: Enter numbers only!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Enter quantity again: ";
            }

            for (int i = 0; i < c; i++) {
                if (arrc[c] == arrc[i]) {
                    cout << "\n\n Duplicate Product Code. Please try again!";
                    goto m;
                }
            }
            c++;
            cout << "\n\n Want to buy another product? Press 'y' for yes and 'n' for no: ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
        system("cls");

        cout << "\n\n\t\t\t__________RECEIPT______________\n";
        cout << "Product No.\tProduct Name\tQuantity\tPrice\tAmount\tDiscounted\n";

        for (int i = 0; i < c; i++) {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;
            while (!data.eof()) {
                if (pcode == arrc[i]) {
                    amount = price * arrq[i];
                    disc = amount - (amount * dis / 100);
                    total += disc;
                    cout << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t" << disc << "\n";
                }
                data >> pcode >> pname >> price >> dis;
            }
            data.close();
        }
        cout << "\n\n----------------------------------------";
        cout << "\n Total Amount: " << total;
    }
}

int main() {
    shopping s;
    s.menu();
}

