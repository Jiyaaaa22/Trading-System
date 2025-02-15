#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <regex>
using namespace std;

class TradingSystem
{
    string name;
    string number;
    vector<pair<string, int>> stocks;
    double totalBalance = 0.0;       

public:
    void personalDetails()
    {
        long long adharNumber;
        long long pancardNumber;
        while (true)
        {
            cout << "Enter your Aadhar number (12 digits): ";
            cin >> adharNumber;
            if (to_string(adharNumber).length() == 12)
            {
                break;
            }
            cout << "Error: Aadhar number must be 12 digits long." << endl;
        }
        while (true)
        {
            cout << "Enter your phone number: ";
            cin >> number;
            if (regex_match(number, regex("\\d{10}")))
            {
                break; 
            }
            cout << "Error: Phone number must be 10 digits long." << endl;
        }
        cout << "Enter your PancardNumber: ";
        cin >> pancardNumber;
        ofstream outfile("user_details.txt", ios::app);
        if (outfile.is_open())
        {
            outfile << "Name: " << name << ", Number: " << number << ", Adhar: " << adharNumber << ", Pancard: " << pancardNumber << endl;
            outfile.close();
        }
        else
        {
            cout << "Error: Unable to open file for writing!" << endl;
        }
        cout << "Your account has been created" << endl;
    }

    void details()
    {
        cout << "Enter your name: ";
        cin >> name;
        cout << "Welcome " << name << "! An OTP has been sent to your Number +91xyz...." << endl;
        int randomNumber = rand() % 9000 + 1000;
        cout << "OTP: " << randomNumber << endl;
        int userChoice;
        cout << "Enter OTP: ";
        cin >> userChoice;
        if (randomNumber == userChoice)
        {
            cout << "OK, " << name << "! Proceeding to the next verification process." << endl;
            personalDetails();
        }
        else
        {
            cout << "Wrong OTP. Please try again." << endl;
            details();
        }
    }

    void checkBalances()
    {
        ifstream infile("user_balances.txt");
        if (infile.is_open())
        {
            string line;
            while (getline(infile, line))
            {
                cout << line << endl;
            }
            infile.close();
        }
        else
        {
            cout << "Error: Unable to open file for reading!" << endl;
        }

        cout << "Stock Holdings:" << endl;
        for (const auto &stock : stocks)
        {
            cout << stock.first << ": " << stock.second << " units" << endl;
        }

        cout << "Total Balance (including stocks and deposited money): $" << fixed << setprecision(2) << totalBalance << endl;
    }

    void depositMoney()
    {
        double amount;
        cout << "Enter the amount you want to deposit: $";
        cin >> amount;

        ofstream outfile("user_balances.txt", ios::app);
        if (outfile.is_open())
        {
            outfile << "Deposit: $" << amount << endl;
            outfile.close();
            cout << "Deposit of $" << amount << " successfully processed." << endl;

            totalBalance += amount;
        }
        else
        {
            cout << "Error: Unable to open file for writing!" << endl;
        }
    }

    void buyStock()
    {
        string stockName;
        int quantity;

        cout << "Enter the stock name: ";
        cin >> stockName;
        cout << "Enter the quantity: ";
        cin >> quantity;

        ofstream outfile("user_transactions.txt", ios::app);
        if (outfile.is_open())
        {
            outfile << "Buy: " << quantity << " units of " << stockName << endl;
            outfile.close();
            cout << "Purchase of " << quantity << " units of " << stockName << " successfully processed." << endl;
            stocks.push_back(make_pair(stockName, quantity));
        }
        else
        {
            cout << "Error: Unable to open file for writing!" << endl;
        }
    }
    void sellStock()
    {
        string stockName;
        int quantity;
        cout << "Enter the stock name: ";
        cin >> stockName;
        cout << "Enter the quantity: ";
        cin >> quantity;
        double totalAmount = quantity * 12.0;
        ofstream outfile("user_transactions.txt", ios::app);
        if (outfile.is_open())
        {
            outfile << "Sell: " << quantity << " units of " << stockName << " for $" << totalAmount << endl;
            outfile.close();
            cout << "Sale of " << quantity << " units of " << stockName << " for $" << totalAmount << " successfully processed." << endl;
            totalBalance -= totalAmount;
        }
        else
        {
            cout << "Error: Unable to open file for writing!" << endl;
        }
    }

    void connectToTradingWebsite()
    {
        cout << "Connecting to the trading website..." << endl;
        cout << "Successfully connected to the trading website!" << endl;
    }

    void showTransactionHistory()
    {
        ifstream infile("user_transactions.txt");
        if (infile.is_open())
        {
            string line;
            cout << "Transaction History:" << endl;
            while (getline(infile, line))
            {
                cout << line << endl;
            }
            infile.close();
        }
        else
        {
            cout << "Error: Unable to open file for reading!" << endl;
        }
    }
};

int main()
{
    TradingSystem t;
    t.details();

    int n;
    do
    {
        cout << "\nPress 1 to check balances" << endl;
        cout << "Press 2 to deposit money" << endl;
        cout << "Press 3 to buy stock" << endl;
        cout << "Press 4 to sell stock" << endl;
        cout << "Press 5 to show transaction history" << endl;
        cout << "Press 6 to connect to trading website" << endl;
        cout << "Press 7 to exit" << endl;
        cout << "Enter your choice: ";
        cin >> n;
        switch (n)
        {
        case 1:
            t.checkBalances();
            break;
        case 2:
            t.depositMoney();
            break;
        case 3:
            t.buyStock();
            break;
        case 4:
            t.sellStock();
            break;
        case 5:
            t.showTransactionHistory();
            break;
        case 6:
            t.connectToTradingWebsite();
            break;
        case 7:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (n != 7);

    return 0;
}