#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

void ShowMainMenu();
void GoBackToTransactionsMenu();
void Login();
void ShowManageUserMenu();

struct stClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double Balance = 0;
    bool MarkForDelete = false;
};

struct stUser
{
    string UserName = "";
    string Password = "";
    short Permisions = 0;
    bool MarkToDelete = false;
};

stUser ConverLineToUserRecord(string);
stUser LoggedInUser;
vector <stUser> LoadUserFileToVector(string);

enum enMainMenuChoice
{
    eClientList = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eTransactions = 6, eManageUsers = 7,
    eLougout = 8
};

enum enTransactionMenuChoice
{
    eDeposit = 1, eWithdraw = 2
    , eTotalBalances = 3, eMainMenu = 4
};

enum enManageUsersMenuChoice
{
    eLisUsers = 1 , eAddNewUser = 2 , eDeleteUser = 3,
    eUpdateUser = 4 , eFindUser = 5 , eBackToMainMenu = 6
};

enum enPermisions
{
    eFullAccess = -1, eShowClientListPermision = 1, eAddNewClientPermision = 2,
    eUpdateClientPermision = 4, eDeleteClientPermision = 8,
    eFindClientPermision = 16, eTransactionPermision = 32,
    eManageUsersPermision = 64
};

vector <string> SplitString(string UserString, string Delem)
{

    short Pos = 0;
    string Word = "";
    vector<string> vWords;

    while ((Pos = UserString.find(Delem)) != std::string::npos)
    {

        Word = UserString.substr(0, Pos);

        if (Word != "")
        {
            vWords.push_back(Word);
        }

        UserString.erase(0, Pos + Delem.length());

    }

    if (UserString != "")
    {
        vWords.push_back(UserString);
    }

    return vWords;

}

stClient ConvertLineToRecord(string Line)
{

    vector <string> vClients = SplitString(Line, "#//#");

    stClient Client;

    Client.AccountNumber = vClients[0];
    Client.PinCode = vClients[1];
    Client.Name = vClients[2];
    Client.Phone = vClients[3];
    Client.Balance = stod(vClients[4]);

    return Client;
}

vector <stClient> LoadFileDataToVector(string FileName)
{

    fstream MyFile;

    vector <stClient> vClients;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line = "";
        stClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }

        MyFile.close();
    }
    return vClients;

}

string ReadAccountNumber()
{
    string AccountNumber = "";
    cout << "Enter account number ?";
    cin >> AccountNumber;
    return AccountNumber;
}

short ReadMainMenuChoice()
{
    short Number;
    cout << "\nEnter a choice [1 - 8] ? \n";
    cin >> Number;
    return Number;
}

short ReadTransactionsMenuChoice()
{
    short Number;
    cout << "\nEnter a choice [1 - 4] ? \n";
    cin >> Number;
    return Number;
}

short ReadManageUsersMenuChoice()
{
    short Number;
    cout << "\nEnter a choice [1 - 6] ? \n";
    cin >> Number;
    return Number;
}

void GoBackToMainMenu()
{
    cout << "\nPress any key to go back to Maim Menu...";
    system("pause>0");
    system("cls");
    ShowMainMenu();
}

void PrintClient(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.Balance;

}

void PrintShortenClient(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Balance;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }

        MyFile.close();

    }
    return false;

}

stClient ReadNewClient()
{

    stClient Client;
    cout << "Enter Account Number? ";

    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.Balance;

    return Client;

}

void AddDataLineToFile(string FileName, string DataLine)
{

    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << DataLine << "\n";

        MyFile.close();
    }


}

string ConvertRecordToLine(stClient Client)
{

    string Line = "";

    Line += Client.AccountNumber + "#//#";
    Line += Client.PinCode + "#//#";
    Line += Client.Name + "#//#";
    Line += Client.Phone + "#//#";
    Line += to_string(Client.Balance) + "#//#";
    return Line;
}

void AddNewClient()
{

    stClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';

    do
    {
        cout << "\nAdding new client :\n";

        AddNewClient();

        cout << "\nClient added succsesfully, do you want to add more clients y/n ?\n";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');


}

void ShowAddNewClientScreen()
{

    cout << "\n------------------------------------\n";
    cout << "\tAdd New Client Screen";
    cout << "\n------------------------------------\n";

    AddNewClients();

}

void ShowAllClientsScreen()
{
    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (stClient Client : vClients)
        {

            PrintClient(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client)
{

    for (stClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }

    return false;
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.Balance;
    cout << "\n-----------------------------------\n";
}

void LoadDataToFile(string FileName, vector <stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (stClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

}

void MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

    for (stClient& Client : vClients)
    {

        if (Client.AccountNumber == AccountNumber)
        {
            Client.MarkForDelete = true;
        }

    }


}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            LoadDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadFileDataToVector(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}

void ShowDeleteClientScreen()
{

    cout << "\n--------------------------------\n";
    cout << "\tDetete Client Screen";
    cout << "\n--------------------------------\n";

    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

stClient ChangeClientRecord(string AccountNumber)
{

    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.Balance;

    return Client;


}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{

    stClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        char AskForUpdate = 'n';
        cout << "\nAre you sure you want to edit this client info y/n ?\n";
        cin >> AskForUpdate;

        if (AskForUpdate == 'y' || AskForUpdate == 'Y')
        {

            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }

            }
            LoadDataToFile(ClientsFileName, vClients);
        }

        cout << "Client updated succesfully\n";
        return true;
    }
    else
    {
        cout << "Client with account number [" << AccountNumber << "] is not exist\n";
        return false;
    }


}

void ShowUpdateClientScreen()
{
    cout << "\n--------------------------------\n";
    cout << "\tUpdate Client Screen";
    cout << "\n--------------------------------\n";

    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowFindClientScreen()
{

    cout << "\n--------------------------------\n";
    cout << "\Find Client Screen";
    cout << "\n--------------------------------\n";

    stClient Client;
    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);
    string AccountNumber = ReadAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nAccount with number [" << AccountNumber << "] is not found\n";
    }

}

bool DepositAmountToClientBalance(vector <stClient>& vClients, double Amount, string AccountNumber)
{

    char AskForDeposit = 'n';
    cout << "Are you sure you want to deposit to this account y/n ?\n";
    cin >> AskForDeposit;

    if (AskForDeposit == 'y' || AskForDeposit == 'Y')
    {

        for (stClient& Client : vClients)
        {

            if (Client.AccountNumber == AccountNumber)
            {

                Client.Balance += Amount;
                cout << "Done succsessfully. New balance = " << Client.Balance << "\n";
                LoadDataToFile(ClientsFileName, vClients);
                return true;

            }
        }
    }

    return false;

}

void ShowWitdrawScreen()
{

    cout << "\n------------------------------\n";
    cout << "\Withdraw Screen ";
    cout << "\n------------------------------\n";

    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);
    string AccountNumber = ReadAccountNumber();

    stClient Client;

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "Client with account number [" << AccountNumber << "] is not exist. ";
        AccountNumber = ReadAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "Enter withdrawal amount ?";
    cin >> Amount;

    while (Amount > Client.Balance)
    {
        cout << "Amount exceeds the balance. you can draw up to : " << Client.Balance << "\n";
        cout << "Enter withdrawal amount ?";
        cin >> Amount;
    }

    DepositAmountToClientBalance(vClients, Amount * -1, AccountNumber);

}

void ShowDepositScreen()
{
    cout << "\n------------------------------\n";
    cout << "\tDeposit Screen ";
    cout << "\n------------------------------\n";

    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);
    string AccountNumber = ReadAccountNumber();

    stClient Client;

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "Number with account number [" << AccountNumber << "] is not found. ";
        AccountNumber = ReadAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "Enter deposit amount? ";
    cin >> Amount;

    DepositAmountToClientBalance(vClients, Amount, AccountNumber);

}

void ShowTotalBalancesScreen()
{

    vector <stClient> vClients = LoadFileDataToVector(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stClient Client : vClients)
        {
            TotalBalances += Client.Balance;
            PrintShortenClient(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "\n\t\t\t\t\Total Balances = " << TotalBalances << " \n";

}

void PerformTransactionMenuOption(enTransactionMenuChoice Choice)
{

    switch (Choice)
    {
    case eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenu();
        break;
    case eWithdraw:
        system("cls");
        ShowWitdrawScreen();
        GoBackToTransactionsMenu();
        break;
    case eTotalBalances:
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenu();
        break;
    case eMainMenu:
        GoBackToMainMenu();
        break;
    }

}

void ShowTransactionsMenu()
{

    cout << "\n===================================\n";
    cout << right << setw(25) << "Transactions Menu";
    cout << "\n===================================\n";
    cout << right << setw(5) << "[1]" << "Deposit" << "\n";
    cout << right << setw(5) << "[2]" << " Withdraw." << "\n";
    cout << right << setw(5) << "[3]" << " Total Balances." << "\n";
    cout << right << setw(5) << "[4]" << " Main Menu." << "\n";

    cout << "\n===================================\n";

    PerformTransactionMenuOption((enTransactionMenuChoice)ReadTransactionsMenuChoice());

}

void PrintAccessDeniedMessage()
{
    cout << "---------------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You don't have permision to do this,\n";
    cout << "Please contact your admin\n";
    cout << "---------------------------------------\n";
}

void PerformMainMenuOption(enMainMenuChoice Choice , stUser LoggedInUser)
{

    switch (Choice)
    {
    case eClientList:
        if (LoggedInUser.Permisions == eFullAccess || LoggedInUser.Permisions & eShowClientListPermision)
        {
            system("cls");
            ShowAllClientsScreen();
            GoBackToMainMenu();
        }
        else
        {
            system("cls");
            PrintAccessDeniedMessage();
            GoBackToMainMenu();
        }
        break;
    case eAddNewClient:
        if (LoggedInUser.Permisions == eFullAccess || LoggedInUser.Permisions & eAddNewClientPermision)
        {
            system("cls");
            ShowAddNewClientScreen();
            GoBackToMainMenu();
        }
        else
        {
            system("cls");
            PrintAccessDeniedMessage();
            GoBackToMainMenu();
        }
        break;
    case eDeleteClient:
        if (LoggedInUser.Permisions == eFullAccess || LoggedInUser.Permisions & eDeleteClientPermision)
        {
            system("cls");
            ShowDeleteClientScreen();
            GoBackToMainMenu();
        }
        else
        {
            system("cls");
            PrintAccessDeniedMessage();
            GoBackToMainMenu();
        }
        break;
    case eUpdateClient:
        if (LoggedInUser.Permisions == eFullAccess || LoggedInUser.Permisions & eUpdateClientPermision)
        {
            system("cls");
            ShowUpdateClientScreen();
            GoBackToMainMenu();
        }
        else
        {
            system("cls");
            PrintAccessDeniedMessage();
            GoBackToMainMenu();
        }
        break;
    case eFindClient:
        if (LoggedInUser.Permisions == eFullAccess || LoggedInUser.Permisions & eFindClientPermision)
        {
            system("cls");
            ShowFindClientScreen();
            GoBackToMainMenu();
        }
        else
        {
            system("cls");
            PrintAccessDeniedMessage();
            GoBackToMainMenu();
        }
        break;
    case eTransactions:
        if (LoggedInUser.Permisions == eFullAccess || LoggedInUser.Permisions & eTransactionPermision)
        {
            system("cls");
            ShowTransactionsMenu();
        }
        else
        {
            system("cls");
            PrintAccessDeniedMessage();
            GoBackToMainMenu();
        }
        break;
    case eManageUsers:
        if (LoggedInUser.Permisions == eFullAccess || LoggedInUser.Permisions & eManageUsersPermision)
        {
            system("cls");
            ShowManageUserMenu();
        }
        else
        {
            system("cls");
            PrintAccessDeniedMessage();
            GoBackToMainMenu();
        }
        break;
    case eLougout:
        system("cls");
        Login();
        break;

    }

}

void GoBackToTransactionsMenu()
{
    cout << "Enter any key to go back to transaction menu...";
    system("pause>0");
    system("cls");
    ShowTransactionsMenu();
}

void ShowMainMenu()
{
    cout << "\n===================================\n";
    cout << right << setw(25) << "Main Menu Screen";
    cout << "\n===================================\n";
    cout << right << setw(5) << "[1]" << " Show Clients List." << "\n";
    cout << right << setw(5) << "[2]" << " Add New Client." << "\n";
    cout << right << setw(5) << "[3]" << " Delete Client." << "\n";
    cout << right << setw(5) << "[4]" << " Update Client Info." << "\n";
    cout << right << setw(5) << "[5]" << " Find Client." << "\n";
    cout << right << setw(5) << "[6]" << " Transactions" << "\n";
    cout << right << setw(5) << "[7]" << " Manage Users." << "\n";
    cout << right << setw(5) << "[8]" << " Lougout." << "\n";

    PerformMainMenuOption((enMainMenuChoice)ReadMainMenuChoice() , LoggedInUser);
}

bool IsUserExistByUserName(string UserName , stUser & User )
{

    vector <stUser> vUsers = LoadUserFileToVector(UsersFileName);

    for (stUser & U : vUsers)
    {
        if (UserName == U.UserName)
        {
            User = U;
            return true;
        }
    }
    return false;
}

string ConvertUserRecordToLine(stUser User)
{

    string Line = "";

    Line += User.UserName + "#//#";
    Line += User.Password + "#//#";
    Line += to_string(User.Permisions);

    return Line;
}

stUser ReadNewUser()
{
    stUser User;

    cout << "Enter UserName?";
    getline(cin >> ws , User.UserName);

    do
    {
        cout << "User with username ["<<User.UserName<<"] is already exist, enter another user name.\n";
        cout << "Enter UserName?";
        getline(cin >> ws, User.UserName);

    } while (IsUserExistByUserName(User.UserName, User));

    cout << "Enter Password?";
    getline(cin >> ws, User.Password);

    char FullAccess = 'n';
    cout << "Do you want to give the user full access y/n?";
    cin >> FullAccess;
    if (FullAccess == 'y' || FullAccess == 'Y')
    {
        User.Permisions = -1;
        return User;
    }
    else
    {
        char PermisionsConfirmation = 'n';

        cout << "Show Client List y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 1;

        cout << "Add new Client y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 2;

        cout << "Delete Client y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 4;

        cout << "Update Client y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 8;

        cout << "Find Client y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 16;

        cout << "Transactins y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 32;

        cout << "Manage User Menu y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 64;

        return User;
    }
    
    return User;
}

void AddUser()
{

    stUser User;
    User = ReadNewUser();

    string Line = ConvertUserRecordToLine(User);
    AddDataLineToFile(UsersFileName , Line);

    cout << "\nUser Added successfuly !\n";


}

void AddUsers()
{
    char AddMore = 'n';


    do
    {
        AddUser();

        cout << "Do you want to add more users y/n?";
        cin >> AddMore;

    } while (AddMore == 'Y' || AddMore == 'y');

}

void GoBackToManageUsersMenu()
{
    cout << "\nPress any key to go back to Manage Users Menu...";
    system("pause>0");
    system("cls");
    ShowManageUserMenu();
}

void PrintUser(stUser User)
{
    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.Permisions;
}

void ListUsers()
{
    vector <stUser> vUsers = LoadUserFileToVector(UsersFileName);

    cout << "\n\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "UserName";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(10) << "Permisions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";
    else

        for (stUser User : vUsers)
        {

            PrintUser(User);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void ShowAddNewUserScreen()
{
    cout << "===================================\n";
    cout << "\tAdd New User Screen";
    cout << "\n===================================\n";

    AddUsers();

}

string ReadUserName()
{
    string UserName = "";
    cout << "Enter username ?";
    getline(cin>> ws , UserName);
    return UserName;
}

vector <stUser> MarkUserToDelete(stUser User , string UserNameToDelete)
{
    vector <stUser> vUsers = LoadUserFileToVector(UserNameToDelete);

    for (stUser& U : vUsers)
    {
        if (U.UserName == UserNameToDelete)
        {
            U.MarkToDelete = true;
            return vUsers;
        }
    }
}

void LoadUsersVectorToFile(vector <stUser> & vUsers , string FileName)
{

    fstream MyFile;

    MyFile.open(FileName , ios::out);

    if (MyFile.is_open())
    {
        string Line = "";

        for (stUser & User : vUsers)
        {
            if (User.MarkToDelete == false)
            {
                Line = ConvertUserRecordToLine(User);
                MyFile << Line << "\n";
            }
             
        }

        MyFile.close();
    }


}

vector <stUser> LoadUserFileToVector(string FileName)
{
    fstream MyFile;

    vector <stUser> vUsers;

    MyFile.open(UsersFileName, ios::in);

    if (MyFile.is_open())
    {
        stUser User;
        string Line = "";

        while (getline(MyFile, Line))
        {
            User = ConverLineToUserRecord(Line);
            vUsers.push_back(User);
        }
    }
    MyFile.close();
    return vUsers;
}

void PrintUserCard(stUser User)
{
    cout << "-------------------\n";
    cout << "Username : " << User.UserName << "\n";
    cout << "Password : " << User.Password << "\n";
    cout << "Permisions : " << to_string(User.Permisions);
    cout << "\n-------------------\n";
}

void DeleteUser()
{
    string UserNameToDelete = ReadUserName();
    stUser User;
    if (UserNameToDelete == "Admin")
    {
        cout << "\n\nYou can not delete this user \n\n";
    }
    else
    {

        while (!IsUserExistByUserName(UserNameToDelete, User))
        {
            cout << "User name [" << UserNameToDelete << "] is not found enter another username!";
            UserNameToDelete = ReadUserName();
        }

        cout << "The following is the user information :\n";
        PrintUserCard(User);

        char DeleteConfirmation = 'n';
        cout << "Are you sure you want to delete this client y/n?";
        cin >> DeleteConfirmation;
        if (DeleteConfirmation == 'y' || DeleteConfirmation == 'Y')
        {
            vector <stUser> vUsers = MarkUserToDelete(User, UserNameToDelete);
            LoadUsersVectorToFile(vUsers, UsersFileName);
            cout << "Client Deleted successfully !\n";

        }

    }
   
   

}

void DeleteUsers()
{

    char DeleteMore = 'n';


    do
    {
        DeleteUser();

        cout << "Do you want to delete more users y/n?";
        cin >> DeleteMore;

    } while (DeleteMore == 'Y' || DeleteMore == 'y');

}

void ShowDeleteUserScreen()
{
    cout << "=========================\n";
    cout << "\tDelete Users Screen";
    cout << "\n=========================\n";
    DeleteUsers();
}

stUser ReadUserInfoToUpdate()
{
    stUser User;

    cout << "\nUpdating User Info:\n\n";

    cout << "Enter UserName?";
    getline(cin >> ws, User.UserName);

    cout << "Enter Password?";
    getline(cin >> ws, User.Password);

    char FullAccess = 'n';
    cout << "Do you want to give the user full access y/n?";
    cin >> FullAccess;
    if (FullAccess == 'y' || FullAccess == 'Y')
    {
        User.Permisions = -1;
        return User;
    }
    else
    {
        char PermisionsConfirmation = 'n';

        cout << "Show Client List y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 1;

        cout << "Add new Client y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 2;

        cout << "Delete Client y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 4;

        cout << "Update Client y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 8;

        cout << "Find Client y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 16;

        cout << "Transactins y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 32;

        cout << "Manage User Menu y/n?";
        cin >> PermisionsConfirmation;
        if (PermisionsConfirmation == 'y' || PermisionsConfirmation == 'Y')
            User.Permisions += 64;

        return User;
    }

    return User;
}

void UpdateUser()
{
    stUser User;
    string UserNameToUpdate = "";
    
    UserNameToUpdate = ReadUserName();

    while (!IsUserExistByUserName(UserNameToUpdate, User))
    {
        cout << "User with username [" << UserNameToUpdate << "] is not exist, enter another username.";
        UserNameToUpdate = ReadUserName();
    } 

    vector <stUser> vUsers = LoadUserFileToVector(UsersFileName);

    for (stUser & U : vUsers)
    {
        if (U.UserName == UserNameToUpdate)
        {
            U = ReadUserInfoToUpdate();
        }
    }

    LoadUsersVectorToFile(vUsers , UsersFileName);

    cout << "\n\nUser Updated Sucessfuy!\n\n";


}

void ShowUpdateUserSreen()
{
    cout << "=========================================\n";
    cout << "\tUpdate User Info Screen";
    cout << "\n=========================================\n";
    UpdateUser();
}

void ShowFindUserScreen()
{
    cout << "========================\n";
    cout << "\tFind User Screen";
    cout << "\n========================\n";

    string UserName = ReadUserName();
    stUser User;

    while (!IsUserExistByUserName(UserName , User))
    {
        cout << "UserName [" << UserName << "] is not found, enter another user name?\n";
        UserName = ReadUserName();
    } 

    cout << "\nUser found! this is user info : \n";
    PrintUserCard(User);
}

void PerformManageUsersMenuOption(enManageUsersMenuChoice Choice, stUser LoggedInUser)
{

    switch (Choice)
    {
    case eLisUsers:
       system("cls");
       ListUsers();
       GoBackToManageUsersMenu();
       system("cls");
        break;
    case eAddNewUser:
        system("cls");
        ShowAddNewUserScreen();
        GoBackToManageUsersMenu();
        break;
    case eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenu();
        break;
    case eUpdateUser:
        system("cls");
        ShowUpdateUserSreen();
        GoBackToManageUsersMenu();
        break;
    case eFindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenu();
        break;
    case eBackToMainMenu:
        GoBackToMainMenu();
        break;
    
    }

}

void ShowManageUserMenu()
{
    cout << "\n===================================\n";
    cout << right << setw(25) << "Manage Users Menu";
    cout << "\n===================================\n";
    cout << right << setw(5) << "[1]" << " List Users." << "\n";
    cout << right << setw(5) << "[2]" << " Add New User." << "\n";
    cout << right << setw(5) << "[3]" << " Delete User." << "\n";
    cout << right << setw(5) << "[4]" << " Update User Info." << "\n";
    cout << right << setw(5) << "[5]" << " Find User." << "\n";
    cout << right << setw(5) << "[6]" << " Main Menu." << "\n";
 

    PerformManageUsersMenuOption((enManageUsersMenuChoice)ReadManageUsersMenuChoice(), LoggedInUser);
}

stUser ConverLineToUserRecord(string Line)
{

    stUser User;

    vector <string> vUser;
    vUser = SplitString(Line , "#//#");

    User.UserName = vUser[0];
    User.Password = vUser[1];
    User.Permisions = stoi(vUser[2]);

    return User;

}

bool FindUserByUserNameAndPassword(string UserName , string Password , stUser & User)
{
    fstream MyFile;
    vector <stUser> vUsers = LoadUserFileToVector(UsersFileName);

    for (stUser & U : vUsers)
    {
        if (U.UserName == UserName && U.Password == Password)
        {
            User = U;
            MyFile.close();
            return true;
        }
    }

    MyFile.close();

    return false;
}

void ShowLoginScreen()
{
    cout << "=============================\n";
    cout << "\tLogin Screen";
    cout << "\n=============================\n";
}

void Login()
{
    stUser User;
    string UserName, Password;

    system("cls");
    ShowLoginScreen();

    cout << "Enter username?";
    getline(cin >> ws, UserName);

    cout << "Enter password?";
    getline(cin >> ws, Password);

    while (!FindUserByUserNameAndPassword(UserName, Password, User))
    {
        system("cls");
        ShowLoginScreen();
        cout << "Invalid UserName/Password try again:\n";
        cout << "Enter username?";
        getline(cin >> ws, UserName);

        cout << "Enter password?";
        getline(cin >> ws, Password);  
    } 

    system("cls");
    LoggedInUser = User; // Assign Found User To LoggedInUser General Variable

    ShowMainMenu();
}

int main()
{
    Login();
    return 0;
}