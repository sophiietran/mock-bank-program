/*MOCK-BANK-PROGRAM*/

#include <iostream>
#include <iomanip>

using namespace std;

struct Owner
{
    string name;
    string DOB;
    string address;
};

class Account
{
    private: 
        double balance;
        int accountNumber;
        int numOwners;
        Owner * ownerPtr;
    public:
        Account(int numOwners_, double amount, int accCounter)
        {
            accountNumber = accCounter + 1000;
            balance = amount;
            numOwners = numOwners_;
            ownerPtr = new Owner[numOwners_]; //dynamic allocation of array of owners
        }
        ~Account();
        void setOwner(int index, Owner person)
        {
            ownerPtr[index].name = person.name;
            ownerPtr[index].address = person.address;
            ownerPtr[index].DOB = person.DOB;
        }
        Owner getOwner(int) const;
        double getBalance() const
        {
            return balance;
        }
        int getAccountNumber() const
        {
            return accountNumber;
        }
        void deposit(double amount)
        {
            balance += amount;
        }
        void withdraw(double amount)
        {
            balance -= amount;
        }
        void print()
        {
            cout << endl;
            cout << "Account Number: " << accountNumber << endl;
            cout << "---------------------" << endl;
            for(int i = 0; i < numOwners; i++)
            {
                cout << "Owner #" << i+1 << ": " << endl;
                cout << right << setw(5) << "Name: " << ownerPtr[i].name << endl;
                cout << right << setw(5) << "DOB: " << ownerPtr[i].DOB << endl;
                cout << right << setw(5) << "Address: " << ownerPtr[i].address << endl;
                cout << endl;
            }
            cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
        }

};


const int MAX_ACCOUNTS = 10;
Account * accArray[MAX_ACCOUNTS]; // an array of pointers to Account objects

int main()
{
    int menuChoice, numOwners, accCounter = 0, accNumDeposit, accIndex;
    int accNumWithdraw;
    double amount, depositAmt, withdrawAmt;
    bool depositValue = false, depositAccFound = false;
    bool withdrawValue = false, withdrawAccFound = false;
    string name, DOB, address;

    // assign all the pointers in accArray with nullptr
    for(int i = 0; i < MAX_ACCOUNTS; i++)
    {
        accArray[i] = nullptr;
    }

    // display menu
    do
    {
        cout << "*****************************************" << endl;
        cout << right << setw(23) << "MENU:" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Display information for account" << endl;
        cout << "5. Quit" << endl;
        cout << "*****************************************" << endl;
        cout << endl;
        cout << "Enter menu selection: ";
        cin >> menuChoice;
        cout << endl;

        // 1. Create account
        if(menuChoice == 1)
        {
            if(accCounter == 10) 
            {
                cout << "Error: Max number of accounts already created." << endl;
                cout << "Exiting." << endl;
                exit(EXIT_FAILURE);
            }

            else
            {
                cout << "***** [ Choice 1: Create Account ] *****" << endl;
                cout << "Max number of accounts allowed: 10" << endl;
                cout << endl;

                // get number of owners for account and info for each owner
                cout << "Enter the number of owners for this account: ";
                cin >> numOwners;

                while(numOwners < 1) // input validation on number of owners
                {
                    cout << "Invalid entry: Number of owners must be at least 1" << endl;
                    cout << "Enter the number of owners for this account: ";
                    cin >> numOwners;
                }

                cout << "Enter amount: ";
                cin >> amount;

                while(amount < 1)
                {
                    cout << "Error: Invalid input, amount must be greater than 0" << endl;
                    cout << "Enter amount: ";
                    cin >> amount;
                }
                cin.ignore();


                accArray[accCounter] = new Account(numOwners, amount, accCounter);


                for(int i = 0; i < numOwners; i++)
                {
                    cout << "For owner #" << i+1 << ", fill out the following: " << endl;
                    cout << "Enter name: ";
                    getline(cin, name);
                    cout << "Enter the date of birth [MM/DD/YYYY]: ";
                    cin >> DOB;
                    cout << "Enter address: ";
                    cin.ignore();
                    getline(cin, address);

                    Owner ownerInfo; // temporary structure variable

                    ownerInfo.name = name;
                    ownerInfo.address = address;
                    ownerInfo.DOB = DOB;

                    accArray[accCounter]->setOwner(i, ownerInfo);
                }
                cout << endl;
                cout << "Account #" << accArray[accCounter]->getAccountNumber() << " has been created!" << endl;
                accCounter++;
            }


        }

        // 2. Deposit
        if(menuChoice == 2)
        {
            depositAccFound = false;

            cout << "********* [ Choice 2: Deposit ] *********" << endl;
            cout << endl;

            cout << "Enter account number: ";
            cin >> accNumDeposit;

            for(int i = 0; i < accCounter; i++)
            {
                if(accNumDeposit == accArray[i]->getAccountNumber())
                {    
                    depositAccFound = true;
                    accIndex = i;
                }
            }

            while(depositAccFound == false)
            {
                cout << "Error: No account exists with that account number. Try again." << endl;
                cout << "Enter account number: ";
                cin >> accNumDeposit;

                for(int i = 0; i < accCounter; i++)
                {
                    if(accNumDeposit == accArray[i]->getAccountNumber())
                    {    
                        depositAccFound = true;
                        accIndex = i;
                    }
                }
            }
                

            cout << "Enter amount to deposit: ";
            cin >> depositAmt;
            
            depositValue = false;
            while(depositValue == false)
            {
                if(depositAmt > 0)
                    depositValue = true;
                else
                {
                    cout << "Error: Minimum amount to deposit is $1.00" << endl;
                    cout << "Enter amount to deposit: ";
                    cin >> depositAmt;
                }
                
            }

            accArray[accIndex]->deposit(depositAmt);

            cout << endl;
            cout << "Deposit was completed successfully! You deposited $" << fixed << setprecision(2) << depositAmt << " into account #" << accNumDeposit << "." << endl;
            cout << "Your new balance is: $" << accArray[accIndex]->getBalance() << endl; 

            
        }

        // 3. Withdraw
        if(menuChoice == 3)
        {
            withdrawAccFound = false;
            withdrawValue = false;

            cout << "******** [ Choice 3: Withdraw ] ********" << endl;
            cout << endl;

            cout << "Enter account number: ";
            cin >> accNumWithdraw;

            for(int i = 0; i < accCounter; i++)
            {
                if(accNumWithdraw == accArray[i]->getAccountNumber())
                {
                    withdrawAccFound = true;
                    accIndex = i;
                }
            }

            while(withdrawAccFound == false)
            {
                cout << "Error: Could not find account number. Try again." << endl;
                cout << "Enter account number: ";
                cin >> accNumWithdraw;
                for(int i = 0; i < accCounter; i++)
                {
                    if(accArray[i]->getAccountNumber() == accNumWithdraw)
                    {
                        withdrawAccFound = true;
                        accIndex = i;
                    }
                }
            }
                

            cout << "Enter amount to withdraw: ";
            cin >> withdrawAmt;
            

            while(withdrawValue == false)
            {
                if(withdrawAmt > 0) // valid (greater than 0)
                {
                    if(withdrawAmt > accArray[accIndex]->getBalance()) // if amount is greater than current balance
                    {
                        cout << "Error: Withdrawal amount cannot exceed current balance" << endl;
                        cout << "Enter amount to withdraw: ";
                        cin >> withdrawAmt;
                    }
                    else
                        withdrawValue = true;
                }
                else if(withdrawAmt < 0)
                {
                    cout << "Error: Minimum amount to withdraw is $1.00" << endl;
                    cout << "Enter amount to withdraw: ";
                    cin >> withdrawAmt;
                }
                
            }

            accArray[accIndex]->withdraw(withdrawAmt);
            cout << endl;
            cout << "Withdrawal was completed successfully! You withdrew $" << fixed << setprecision(2) << withdrawAmt << " from account #" << accNumWithdraw << "." << endl;
            cout << "Your new balance is: $" << accArray[accIndex]->getBalance() << endl;
        }

        // 4. Display information for account
        int menuDisplay, displayAccNum, accDisplayInd;
        bool accDisplayFound;

        if(menuChoice == 4)
        {
    
            cout << "[ Choice 4: Display information for account ]" << endl;
            cout << endl;
            cout << "Enter 1 to display specific account, 2 to display all accounts: ";
            cin >> menuDisplay;

            if(menuDisplay == 1)
            {
                accDisplayFound = false;

                cout << "Enter account number: ";
                cin >> displayAccNum;
                for (int i = 0; i < accCounter; i++)
                {
                    if(displayAccNum == accArray[i]->getAccountNumber())
                    {
                        accDisplayFound = true;
                        accDisplayInd = i;
                    }
                      
                }
                while(accDisplayFound == false)
                {
                    cout << "Error: Could not find account number. Try again." << endl;
                    cout << "Enter account number: ";
                    cin >> displayAccNum;

                    for (int i = 0; i < accCounter; i++)
                    {   
                        if(displayAccNum == accArray[i]->getAccountNumber())
                        {
                                accDisplayFound = true;
                                accDisplayInd = i;
                        }
                    }   
                }

                accArray[accDisplayInd]->print();
            }
            else if (menuDisplay == 2)
            {
                for(int i = 0; i < accCounter; i++)
                {
                    accArray[i]->print();
                }
            }
        }

        cout << endl;
    } while (menuChoice != 5);
    

    
    return 0;
}