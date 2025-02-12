#include <iostream>
#include <string>
using namespace std;

#define MAX_ACCOUNTS 10
#define MAX_TRANSACTIONS 5

class TransactionStack {
private:
    string transactions[MAX_TRANSACTIONS];
    int top;
public:
    TransactionStack() { top = -1; }
    void push(string transaction) {
        if (top >= MAX_TRANSACTIONS - 1) return;
        transactions[++top] = transaction;
    }
    void showHistory() {
        for (int i = top; i >= 0; i--) cout << transactions[i] << endl;
    }
};

struct Account {
    int accountNumber;
    string name;
    double balance;
    TransactionStack history;
};

class Bank {
private:
    Account accounts[MAX_ACCOUNTS];
    int count;
public:
    Bank() { count = 0; }
    void createAccount() {
        if (count >= MAX_ACCOUNTS) return;
        int accNo;
        string accName;
        double initialBalance;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin, accName);
        cout << "Enter Initial Balance: ";
        cin >> initialBalance;
        accounts[count] = {accNo, accName, initialBalance};
        accounts[count].history.push("Account created with $" + to_string(initialBalance));
        count++;
    }
    int findAccount(int accNo) {
        for (int i = 0; i < count; i++)
            if (accounts[i].accountNumber == accNo) return i;
        return -1;
    }
    void deposit() {
        int accNo;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNo;
        int index = findAccount(accNo);
        if (index == -1) return;
        cout << "Enter Deposit Amount: ";
        cin >> amount;
        if (amount <= 0) return;
        accounts[index].balance += amount;
        accounts[index].history.push("Deposited $" + to_string(amount));
    }
    void withdraw() {
        int accNo;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNo;
        int index = findAccount(accNo);
        if (index == -1) return;
        cout << "Enter Withdrawal Amount: ";
        cin >> amount;
        if (amount <= 0 || amount > accounts[index].balance) return;
        accounts[index].balance -= amount;
        accounts[index].history.push("Withdrew $" + to_string(amount));
    }
    void showAccount() {
        int accNo;
        cout << "Enter Account Number: ";
        cin >> accNo;
        int index = findAccount(accNo);
        if (index == -1) return;
        cout << "Account: " << accounts[index].accountNumber << " | Name: " << accounts[index].name << " | Balance: $" << accounts[index].balance << endl;
    }
    void showHistory() {
        int accNo;
        cout << "Enter Account Number: ";
        cin >> accNo;
        int index = findAccount(accNo);
        if (index == -1) return;
        accounts[index].history.showHistory();
    }
};

int main() {
    Bank bank;
    int choice;
    do {
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Show Account\n5. Show History\n6. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.deposit(); break;
            case 3: bank.withdraw(); break;
            case 4: bank.showAccount(); break;
            case 5: bank.showHistory(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);
    return 0;
}
