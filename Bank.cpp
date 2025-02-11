#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Bank {
private:
    int accno;
    char name[50];
    float balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accno;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Initial Balance: ";
        cin >> balance;
        cout << "Account Created Successfully!\n";
    }

    void displayAccount() const {
        cout << left << setw(15) << "Account No:" << accno << endl;
        cout << left << setw(15) << "Name:" << name << endl;
        cout << left << setw(15) << "Balance:" << balance << endl;
        cout << "-----------------------------\n";
    }

    int getAccNo() const { return accno; }

    void deposit(float amount) {
        balance += amount;
        cout << "Amount Deposited Successfully!\n";
    }

    bool withdraw(float amount) {
        if (amount > balance) {
            cout << "Insufficient Funds!\n";
            return false;
        }
        balance -= amount;
        cout << "Amount Withdrawn Successfully!\n";
        return true;
    }

    void updateAccount() {
        cout << "Enter new name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Account Updated Successfully!\n";
    }

    // Save account details to file (for both ofstream and fstream)
    void saveToFile(ofstream &file) { file.write((char *)this, sizeof(*this)); }
    void saveToFile(fstream &file) { file.write((char *)this, sizeof(*this)); }

    // Load account details from file (for both ifstream and fstream)
    bool loadFromFile(ifstream &file) { return file.read((char *)this, sizeof(*this)); }
    bool loadFromFile(fstream &file) { return file.read((char *)this, sizeof(*this)); }
};

void addAccount() {
    Bank b;
    b.createAccount();
    ofstream file("bank.dat", ios::binary | ios::app);
    b.saveToFile(file);
    file.close();
}

void viewAccounts() {
    Bank b;
    ifstream file("bank.dat", ios::binary);
    if (!file) {
        cout << "No records found!\n";
        return;
    }
    while (b.loadFromFile(file)) {
        b.displayAccount();
    }
    file.close();
}

// Function to search an account
void searchAccount(int accno) {
    Bank b;
    ifstream file("bank.dat", ios::binary);
    bool found = false;
    while (b.loadFromFile(file)) {
        if (b.getAccNo() == accno) {
            cout << "Account Found!\n";
            b.displayAccount();
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Account not found!\n";
}

// Function to update account details
void updateAccount(int accno) {
    Bank b;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    
    while (b.loadFromFile(file)) {
        if (b.getAccNo() == accno) {
            cout << "Current Account Details:\n";
            b.displayAccount();
            b.updateAccount();
            file.seekp(-sizeof(Bank), ios::cur);
            b.saveToFile(file);
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Account not found!\n";
}

// Function to delete an account
void deleteAccount(int accno) {
    Bank b;
    ifstream file("bank.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    bool found = false;

    while (b.loadFromFile(file)) {
        if (b.getAccNo() == accno) {
            found = true;
        } else {
            b.saveToFile(temp);
        }
    }
    file.close();
    temp.close();
    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if (found) cout << "Account Deleted Successfully!\n";
    else cout << "Account not found!\n";
}

// Main function
int main() {
    int choice, acc;
    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Account";
        cout << "\n2. View Accounts";
        cout << "\n3. Search Account";
        cout << "\n4. Update Account";
        cout << "\n5. Delete Account";
        cout << "\n6. Exit";
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
                cout << "Enter Account Number to Search: ";
                cin >> acc;
                searchAccount(acc);
                break;
            case 4:
                cout << "Enter Account Number to Update: ";
                cin >> acc;
                updateAccount(acc);
                break;
            case 5:
                cout << "Enter Account Number to Delete: ";
                cin >> acc;
                deleteAccount(acc);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
