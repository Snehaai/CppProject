#include <iostream>
#include <fstream>
using namespace std;

class Bank {
public:
    int accno;
    char name[50];
    float balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accno;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Balance: ";
        cin >> balance;
    }

    void displayAccount() {
        cout << "Account Number: " << accno << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
    }
};

void addAccount() {
    Bank b;
    b.createAccount();
    ofstream file("bank.dat", ios::binary | ios::app);
    file.write((char*)&b, sizeof(b));
    file.close();
    cout << "Account added successfully!" << endl;
}

void viewAccounts() {
    Bank b;
    ifstream file("bank.dat", ios::binary);
    if (!file) {
        cout << "No records found!" << endl;
        return;
    }
    while (file.read((char*)&b, sizeof(b))) {
        b.displayAccount();
        cout << "-------------------------" << endl;
    }
    file.close();
}

void deleteAccount(int accno) {
    Bank b;
    ifstream file("bank.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    bool found = false;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.accno == accno) {
            found = true;
        } else {
            temp.write((char*)&b, sizeof(b));
        }
    }
    file.close();
    temp.close();
    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if (found)
        cout << "Account deleted successfully!" << endl;
    else
        cout << "Account not found!" << endl;
}

int main() {
    int choice, acc;
    do {
        cout << "\n1. Add Account";
        cout << "\n2. View Accounts";
        cout << "\n3. Delete Account";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                viewAccounts();
                break;
            case 3:
                cout << "Enter Account Number to Delete: ";
                cin >> acc;
                deleteAccount(acc);
                break;
            case 4:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice! Try again.";
        }
    } while (choice != 4);
    return 0;
}
