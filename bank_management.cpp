#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class BankAccount
{
public:
    int accountNo;
    string name;
    double balance;
};

const string FILE_NAME = "accounts.txt";

// Load accounts from file
vector<BankAccount> loadAccounts()
{
    vector<BankAccount> accounts;
    ifstream file(FILE_NAME);

    BankAccount acc;

    while (file >> acc.accountNo)
    {
        file.ignore();
        getline(file, acc.name);

        file >> acc.balance;
        file.ignore();

        accounts.push_back(acc);
    }

    file.close();
    return accounts;
}

// Save accounts to file
void saveAccounts(vector<BankAccount>& accounts)
{
    ofstream file(FILE_NAME);

    for (const auto& acc : accounts)
    {
        file << acc.accountNo << endl;
        file << acc.name << endl;
        file << acc.balance << endl;
    }

    file.close();
}

// Check duplicate account number
bool accountExists(int accountNo, const vector<BankAccount>& accounts)
{
    for (const auto& acc : accounts)
    {
        if (acc.accountNo == accountNo)
            return true;
    }
    return false;
}

// Create Account
void createAccount()
{
    vector<BankAccount> accounts = loadAccounts();
    BankAccount acc;

    cout << "\nEnter Account Number: ";
    cin >> acc.accountNo;

    if (accountExists(acc.accountNo, accounts))
    {
        cout << "Account Number already exists!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Customer Name: ";
    getline(cin, acc.name);

    cout << "Enter Initial Balance: ";
    cin >> acc.balance;

    accounts.push_back(acc);
    saveAccounts(accounts);

    cout << "Account Created Successfully!\n";
}

// Deposit
void depositMoney()
{
    vector<BankAccount> accounts = loadAccounts();

    int accNo;
    double amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    for (auto& acc : accounts)
    {
        if (acc.accountNo == accNo)
        {
            cout << "Enter Deposit Amount: ";
            cin >> amount;

            acc.balance += amount;
            found = true;
            break;
        }
    }

    if (found)
    {
        saveAccounts(accounts);
        cout << "Amount Deposited Successfully!\n";
    }
    else
    {
        cout << "Account Not Found!\n";
    }
}

// Withdraw
void withdrawMoney()
{
    vector<BankAccount> accounts = loadAccounts();

    int accNo;
    double amount;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    for (auto& acc : accounts)
    {
        if (acc.accountNo == accNo)
        {
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            if (amount > acc.balance)
            {
                cout << "Insufficient Balance!\n";
                return;
            }

            acc.balance -= amount;
            found = true;
            break;
        }
    }

    if (found)
    {
        saveAccounts(accounts);
        cout << "Amount Withdrawn Successfully!\n";
    }
    else
    {
        cout << "Account Not Found!\n";
    }
}

// Check Balance
void checkBalance()
{
    vector<BankAccount> accounts = loadAccounts();

    int accNo;
    bool found = false;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    for (const auto& acc : accounts)
    {
        if (acc.accountNo == accNo)
        {
            cout << "\nAccount Number : " << acc.accountNo;
            cout << "\nCustomer Name  : " << acc.name;
            cout << "\nBalance        : " << acc.balance << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Account Not Found!\n";
    }
}

// Display All Accounts
void displayAccounts()
{
    vector<BankAccount> accounts = loadAccounts();

    if (accounts.empty())
    {
        cout << "\nNo Accounts Found!\n";
        return;
    }

    cout << "\n===== Account Records =====\n";

    for (const auto& acc : accounts)
    {
        cout << "\nAccount No : " << acc.accountNo;
        cout << "\nName       : " << acc.name;
        cout << "\nBalance    : " << acc.balance;
        cout << "\n--------------------------\n";
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                displayAccounts();
                break;

            case 6:
                cout << "Thank You!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}