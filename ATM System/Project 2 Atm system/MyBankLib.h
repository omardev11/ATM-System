#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;
struct Sclient
{
	string Accountnumber;
	string pincode;
	string name;
	string phone;
	double accountbalance;
	bool MarkToDelete = false;
};
struct Suser
{
    string UserName;
    string Passaword;
    int Permession;
    bool MarketToDelete = false;
    
};
Sclient CurrentClient;
enum EnShowMainMenuPermission
{
    eAll = -1, PclientListShow = 1, PaddClientShow = 2, PdeleteClientShow = 4, PupdateClientShow = 8,
    PfindClientShow = 16, PtranscationShow = 32, PmanageUser = 64
};


namespace BankExtension1
{
    Suser User;
    bool CheckPermission(EnShowMainMenuPermission Permission,Suser CurrentUser)
    {
        if (CurrentUser.Permession == EnShowMainMenuPermission::eAll)
        {
            return true;
        }

        if ((Permission & CurrentUser.Permession) == Permission)
        {
            return true;
        }
        else
        {
            return false;
        }


    }
    void AccessDenied()
    {
        system("cls");
        cout << "\n------------------------------------------------------------------------\n";
        cout << "Access Denied, \n You dont have permission to do this \n please contact whith your admin ";
        cout << "\n--------------------------------------------------------------------------\n";
    }



    vector <string> SplitString(string S1, string delim)
    {
        int pos = 0; string sword;
        vector <string> Vstring;
        while ((pos = S1.find(delim)) != string::npos)
        {
            sword = S1.substr(0, pos);
            if (sword != "")
            {
                Vstring.push_back(sword);
            }
            S1.erase(0, pos + delim.length());
        }
        if (S1 != "")
        {
            Vstring.push_back(S1);
        }
        return Vstring;


    }
    Sclient convertLineToRecord(string StclientRecord, string seperate)
    {
        vector <string> S2; Sclient client;
        S2 = SplitString(StclientRecord, seperate);


        client.Accountnumber = S2[0];
        client.pincode = S2[1];
        client.name = S2[2];
        client.phone = S2[3];
        client.accountbalance = stod(S2[4]);
        return client;



    }
    vector <Sclient> LoadClientDataFromFile(string filename)
    {
        fstream Myfile;
        vector <Sclient> Vclient;
        Myfile.open(filename, ios::in);
        if (Myfile.is_open())
        {
            Sclient client;
            string line;

            while (getline(Myfile, line) && line != "")
            {
                client = convertLineToRecord(line, "#//#");
                Vclient.push_back(client);

            }
            Myfile.close();
        }
        return Vclient;



    }
    void PrintClientRecord(Sclient client)
    {
        cout << "| " << left << setw(15) << client.Accountnumber;
        cout << "| " << left << setw(10) << client.pincode;
        cout << "| " << left << setw(40) << client.name;
        cout << "| " << left << setw(30) << client.phone;
        cout << "| " << left << setw(15) << client.accountbalance;



    }
    void PrintClientsList(vector <Sclient> Vclient)
    {

        cout << "\n\t\t\t\t\t\t\t\tClient list (" << Vclient.size() << ")   Client(s)\n\n";
        cout << "----------------------------------------------------------------------------";
        cout << "--------------------------------------------\n\n";
        cout << "| " << left << setw(15) << "Account number ";
        cout << "| " << left << setw(10) << "Pin code ";
        cout << "| " << left << setw(40) << "Client name ";
        cout << "| " << left << setw(30) << "phone ";
        cout << "| " << left << setw(15) << "Account balance ";
        cout << "\n---------------------------------------------------------------------------";
        cout << "--------------------------------------------\n\n";

        for (Sclient& client : Vclient)
        {
            PrintClientRecord(client);
            cout << endl;
        }
        cout << "\n-------------------------------------------------------------------------";
        cout << "-----------------------------------------------\n\n";


    }
    void ClientList(string filename, vector <Sclient> Vclient)
    {
       
        system("cls");
        Vclient = LoadClientDataFromFile(filename);
        PrintClientsList(Vclient);
        system("pause");


    }


    Sclient ReadNewClient()
    {
        Sclient Client;
        cin.ignore();
        cout << "\nEnter Account Number? ";
        getline(cin >> ws, Client.Accountnumber);
        cout << "Enter PinCode? ";
        getline(cin, Client.pincode);
        cout << "Enter Name? ";
        getline(cin, Client.name);
        cout << "Enter Phone? ";
        getline(cin, Client.phone);
        cout << "Enter AccountBalance? ";
        cin >> Client.accountbalance;
        return Client;
    }
    string convertRecordToLine(Sclient client, string seperate)
    {
        string StClientRecord = "";
        StClientRecord += client.Accountnumber + seperate;
        StClientRecord += client.pincode + seperate;
        StClientRecord += client.name + seperate;
        StClientRecord += client.phone + seperate;
        StClientRecord += to_string(client.accountbalance);
        return StClientRecord;
    }
    bool IsClientExist(vector <Sclient>& Vclient, string accouontName)
    {
        for (Sclient& C : Vclient)
        {

            if (C.Accountnumber == accouontName)
            {
                return true;
            }




        }
        return false;



    }

    vector <string> AddClient(string filename)
    {
        vector <Sclient> Vclient = LoadClientDataFromFile(filename);
        Sclient client;
        string clientNumber;
        vector <string> Vfile;
        char answer;


        do
        {
            system("cls");
            cout << "\n adding new client " << endl;

            cout << "\nEnter Account Number? ";
            getline(cin >> ws, client.Accountnumber);

                while (IsClientExist(Vclient,client.Accountnumber))
                {
                    cout << "\nthis account number is exist enter another one? \n";
                    cout << "\nEnter Account Number? ";
                    getline(cin >> ws, client.Accountnumber);
                }
                

            

            client = ReadNewClient();
            clientNumber = convertRecordToLine(client, "#//#");
            Vfile.push_back(clientNumber);

            cout << "\nClient added succesfully, do you want to add more client if yes 'y if no click 'n " << endl;
            cin >> answer;


        } while (answer == 'y');
        return Vfile;




    }
    void AddDataToFile(vector <string> Vfile, string filename)
    {

        fstream Myfile;
        Myfile.open(filename, ios::out | ios::app);

        if (Myfile.is_open())
        {
            for (string& s : Vfile)
            {
                Myfile << s << endl;
            }
            Myfile.close();
        }
    }
    void AddNewClient(string filename)
    {
       
        vector <string> Vclient;
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "Add New Clients Screen  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
        Vclient = AddClient(filename);
        AddDataToFile(Vclient, filename);
        system("pause");


    }


    void printLineRecord(Sclient Client)
    {
        cout << "\n\nThe following are the client details:\n";
        cout << "\nAccout Number: " << Client.Accountnumber;
        cout << "\nPin Code     : " << Client.pincode;
        cout << "\nName         : " << Client.name;
        cout << "\nPhone        : " << Client.phone;
        cout << "\nAccount Balance: " << Client.accountbalance;
    }
    bool FindClientByAccountNumber(vector <Sclient>& Vclient, string accouontName, Sclient& client)
    {
        for (Sclient& C : Vclient)
        {

            if (C.Accountnumber == accouontName)
            {
                client = C;
                return true;
            }




        }
        return false;



    }
    bool MarkClienToDeleteFromFileByAccountNumber(vector <Sclient>& Vclient, string accountname, string filename)
    {
        Vclient = LoadClientDataFromFile(filename);
        for (Sclient& C : Vclient)
        {
            if (C.Accountnumber == accountname)
            {
                C.MarkToDelete = true;
                return true;
            }
        }
        return false;
    }
    void SaveClientsDataTofile(vector <Sclient> Vclient, string filename)
    {
        fstream Myfile;
        string Dataline;
        Myfile.open(filename, ios::out);

        if (Myfile.is_open())
        {
            for (Sclient& C : Vclient)
            {
                if (C.MarkToDelete == false)
                {
                    Dataline = convertRecordToLine(C, "#//#");
                    Myfile << Dataline << endl;
                }
            }
            Myfile.close();
        }


    }
    bool DeleteClientByAccountNumber(vector <Sclient> Vclient, string accouontName, string filename)
    {
        Sclient client; char answer;
        if (FindClientByAccountNumber(Vclient, accouontName, client))
        {
            printLineRecord(client);
            cout << "\nAre you sure you want to deleter this client if yes click 'y' if no click 'n'\n";
            cin >> answer;
            if (answer == 'y')
            {
                MarkClienToDeleteFromFileByAccountNumber(Vclient, accouontName, filename);
                SaveClientsDataTofile(Vclient, filename);
                cout << "\nclient delete succesfully\n ";

                return true;
            }
            Vclient = LoadClientDataFromFile(filename);

        }
        else
        {
            cout << "Client whith account number (" << accouontName << ") NOT found " << endl;
        }
        return false;


    }
    void DeleteClientInfo(string filename, vector <Sclient> Vclient)
    {
      
        system("cls");
        Vclient = LoadClientDataFromFile(filename); string accountName;
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "Delete Client Screen  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
        cout << "Please Enter Account Number?  ";
        cin >> accountName;
        DeleteClientByAccountNumber(Vclient, accountName, filename);
        system("pause");
    }



    bool UpdateClienDataFromFileByAccountNumber(vector <Sclient>& Vclient, string accountname, string filename)
    {
        Vclient = LoadClientDataFromFile(filename);
        for (Sclient& C : Vclient)
        {
            if (C.Accountnumber == accountname)
            {
                cin.ignore();
                cout << "enter name? "; getline(cin, C.name);
                cout << "enter pin code? "; getline(cin, C.pincode);
                cout << "enter phone? "; getline(cin, C.phone);
                cout << "enter account balance? "; cin >> C.accountbalance;

                return true;
            }
        }
        return false;
    }
    bool UpdateClientByAccountNumber(vector <Sclient> Vclient, string accouontName, string filename)
    {
        Sclient client; char answer;
        if (FindClientByAccountNumber(Vclient, accouontName, client))
        {
            printLineRecord(client);
            cout << "\nAre you sure you want to update this client if yes click 'y' if no click 'n'\n";
            cin >> answer;
            if (answer == 'y')
            {
                UpdateClienDataFromFileByAccountNumber(Vclient, accouontName, filename);
                SaveClientsDataTofile(Vclient, filename);
                cout << "\nclient update succesfully\n ";
                return true;
            }
            Vclient = LoadClientDataFromFile(filename);

        }
        else
        {
            cout << "Client whith account number (" << accouontName << ") NOT found " << endl;
        }
        return false;


    }
    void UpdateClientDataInfo(string filename, vector <Sclient> Vclient)
    {
       
        system("cls");
        Vclient = LoadClientDataFromFile(filename); string accountName;
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "Delete Client Screen  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
        cout << "Please Enter Account Number?  ";
        cin >> accountName;
        UpdateClientByAccountNumber(Vclient, accountName, filename);
        system("pause");

    }


    void FindClientScreen(string filename, vector <Sclient> Vsclient)
    {
       
        system("cls");
        Vsclient = LoadClientDataFromFile(filename); string accountName; Sclient client;
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "Find Client Screen  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
        cout << "Please Enter Account Number?  ";
        cin >> accountName;
        if (FindClientByAccountNumber(Vsclient, accountName, client))
        {
            printLineRecord(client);
        }
        else
        {
            cout << "\nthe client does not found\n";
        }
        system("pause");
    }

    void Exit()
    {
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "Program ends  :  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
    }

    bool SearchClient(string filename, string accountName, vector <Sclient>& Vclient)
    {
        Sclient client;
        if (FindClientByAccountNumber(Vclient, accountName, client))
        {
            printLineRecord(client);
            return true;



        }
        else
        {
            cout << "\nthe client does not found\n";
            return false;
        }
    }

    bool AddMoneyToBalance(string filename, string accountName, vector <Sclient>& Vclient)
    {
        Sclient client;
        double DepositAmount; char comformation; 
        cout << "\n\n\nPlease Enter Deposit Amount";
        cin >> DepositAmount;
        cout << "\n\n\n Are you sure you want to perform this transcation y/n?";
        cin >> comformation;
        if (comformation == 'y' || comformation == 'Y')
        {
            for (Sclient& C : Vclient)
            {
                if (C.Accountnumber == accountName)
                {
                    C.accountbalance += DepositAmount;


                    SaveClientsDataTofile(Vclient, filename);
                    cout << "\n\nDone Succesfully New balance is   " << C.accountbalance << endl;
                    return true;
                }




            }
            return false;

        }

    }
    void DepositScreen(string filename, vector <Sclient>& Vclient)
    {
        system("cls");
        string accountName;
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "           Deposit Screen  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
        cout << "Please Enter Account Number?  ";
        cin >> accountName;
        if (SearchClient(filename, accountName, Vclient))
        {
            AddMoneyToBalance(filename, accountName, Vclient);

        }
        system("pause");
    }

    bool TakeMoneyFromBalance(string filename, string accountName, vector <Sclient>& Vclient)
    {
        Sclient client;
        double WhithdrawAmount; char comformation;
        cout << "\n\n\nPlease Enter Deposit Amount";
        cin >> WhithdrawAmount;
        for (Sclient& C : Vclient)
        {
            if (C.Accountnumber == accountName)
            {
                while (WhithdrawAmount > C.accountbalance)
                {
                    cout << "Whith Draw amount exceeds the balance, enter amounnt Up to: " << C.accountbalance << endl;
                    cin >> WhithdrawAmount;
                }
            }
        }

        cout << "\n\n\n Are you sure you want to perform this transcation y/n?";
        cin >> comformation;
        if (comformation == 'y' || comformation == 'Y')
        {
            for (Sclient& C : Vclient)
            {
                if (C.Accountnumber == accountName)
                {
                    C.accountbalance -= WhithdrawAmount;


                    SaveClientsDataTofile(Vclient, filename);
                    cout << "\n\nDone Succesfully New balance is   " << C.accountbalance << endl;
                    return true;
                }




            }
            return false;

        }
    }
    void WhithDrawScreen(string filename, vector <Sclient>& Vclient)
    {
        system("cls");
        string accountName; Sclient client;
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "           Whith Draw Screen  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
        cout << "Please Enter Account Number?  ";
        cin >> accountName;
        if (SearchClient(filename, accountName, Vclient))
        {
            TakeMoneyFromBalance(filename, accountName, Vclient);
        }
        system("pause");
    }



    void TotalBalance(vector <Sclient>& Vclient)
    {
        double totalBalance = 0;
        for (Sclient& C : Vclient)
        {
            totalBalance += C.accountbalance;
        }
        cout << "                                                                                 ";
        cout << "        TOTAL BALANCE = " << totalBalance << endl;
        cout << endl << endl;

    }
    void ShowtoTalBalance(string filename, vector <Sclient>& Vclient)
    {
        system("cls");
        PrintClientsList(Vclient);
        TotalBalance(Vclient);
        system("pause");
    }



}
namespace BankExtension2
{
    using namespace BankExtension1;
    void Login(string UserfileName, string filename);
    void PrintMainMenu(string UserfileName, string filename,Suser User);


    int ReadPermession()
    {
        char answer; int permisson = 0;
        cout << "Do you to give full access?  y/n";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            permisson = EnShowMainMenuPermission::eAll;
           
        }
        else
        {
            cout << "Do you want to give access to; \n\n";
            cout << "Show Client List:  ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                permisson += EnShowMainMenuPermission::PclientListShow;
            }
            cout << "\n Add Client show:  ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                permisson += EnShowMainMenuPermission::PaddClientShow;
            }
            cout << "\n Delete Client Show:  ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                permisson += EnShowMainMenuPermission::PdeleteClientShow;
            }
            cout << "\nUpdate Client Show:  ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                permisson += EnShowMainMenuPermission::PupdateClientShow;
            }
            cout << "\n find Client show:  ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                permisson += EnShowMainMenuPermission::PfindClientShow;
            }
            cout << "\n Transcation Show:  ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                permisson += EnShowMainMenuPermission::PtranscationShow;
            }
            cout << "\n Manage User Show:  ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                permisson += EnShowMainMenuPermission::PmanageUser;
            }
        }
       
        return permisson;

       

    }

    void PrintUserRecord(Suser User)
    {
        cout << "| " << left << setw(15) << User.UserName;
        cout << "| " << left << setw(10) << User.Passaword;
        cout << "| " << left << setw(40) << User.Permession;

    }
    Suser convertLineToRecord(string Line, string seperate)
    {
        vector <string> S2; Suser user;
        S2 = SplitString(Line, seperate);
    
        user.UserName = S2[0];
        user.Passaword = (S2[1]);
        user.Permession = stoi(S2[2]);
        
        return user;
    }
    vector <Suser> LoadUserDataFromFile(string UsersFilename)
    {
        fstream Myfile;
        vector <Suser> Vuser;
        Myfile.open(UsersFilename, ios::in);
        if (Myfile.is_open())
        {
            Suser User;
            string line;

            while (getline(Myfile, line) && line !=  "")
            {
                User = convertLineToRecord(line, "#//#");
                Vuser.push_back(User);

            }
            Myfile.close();
        }
        return Vuser;



    }
    bool CheckIfUserIsExist(Suser &User, string Userfilename,string UserName,string Passaword)
    {
        vector <Suser> Vuser = LoadUserDataFromFile(Userfilename);

        for (Suser& U : Vuser)
        {
            if ((U.UserName == UserName) && (U.Passaword == Passaword))
            {
                User = U;
                return true;
            }
        }
        return false;


    }
    Suser ReadUser()
    {
        Suser User1;
       
            cout << "\nEnter User Name:  ";
            getline(cin >> ws, User1.UserName);
            cout << "\nEnter Passaword:  ";
            cin >> User1.Passaword;
            
        
        return User1;
    }
    Suser ReadNewUser()
    {
        Suser User1;

        cout << "\nEnter User Name:  ";
        getline(cin >> ws, User1.UserName);
        cout << "\nEnter Passaword:  ";
        cin >> User1.Passaword;
        User1.Permession = ReadPermession();


        return User1;
    }






    void PrintUsersList(vector <Suser> Vuser)
    {

        cout << "\n\t\t\t\t\t\t\t\tUser list (" << Vuser.size() << ")   Client(s)\n\n";
        cout << "----------------------------------------------------------------------------";
        cout << "--------------------------------------------\n\n";
        cout << "| " << left << setw(15) << "User Name ";
        cout << "| " << left << setw(10) << "Passaword ";
        cout << "\n---------------------------------------------------------------------------";
        cout << "--------------------------------------------\n\n";

        for (Suser& User : Vuser)
        {
            PrintUserRecord(User);
            cout << endl;
        }
        cout << "\n-------------------------------------------------------------------------";
        cout << "-----------------------------------------------\n\n";


    }
    void ListUserShow(string filename, vector <Suser> Vuser)
    {

        system("cls");
        Vuser = LoadUserDataFromFile(filename);
        PrintUsersList(Vuser);
        system("pause");

    } 
    
    string convertRecorduserToLine(Suser user, string seperate)
    {
        string StClientRecord = "";
        StClientRecord += user.UserName + seperate;
        StClientRecord += user.Passaword + seperate;
        StClientRecord += to_string(user.Permession);
        return StClientRecord;
    }
    bool ToaddUsercheckUserExist(string Userfilename, string UserName, string Passaword)
    {
        vector <Suser> Vuser = LoadUserDataFromFile(Userfilename);

        for (Suser& U : Vuser)
        {
            if ((U.UserName == UserName) && (U.Passaword == Passaword))
            {
                return true;
            }
        }
        return false;


    }
    vector <string> AddUser(string Userfilename)
    {
        vector <Suser> Vuser = LoadUserDataFromFile(Userfilename);
        Suser User;
        string UserNumber;
        vector <string> vUserFile;
        char answer;


        do
        {
            system("cls");
            cout << "\n adding new User " << endl;

            User = ReadNewUser();

            while (ToaddUsercheckUserExist(Userfilename, User.UserName, User.Passaword))
            {
                cout << "\nthis User is exist enter another one? \n";
                User = ReadNewUser();
            }

            
             UserNumber = convertRecorduserToLine(User, "#//#");
               

            vUserFile.push_back(UserNumber);

            cout << "\nUser added succesfully, do you want to add more Users if yes 'y if no click 'n " << endl;
            cin >> answer;


        } while (answer == 'y');
        return vUserFile;




    }
    void AddUserDataToFile(vector <string> Vfile, string filename)
    {

        fstream Myfile;
        Myfile.open(filename, ios::out | ios::app);

        if (Myfile.is_open())
        {
            for (string& s : Vfile)
            {
                Myfile << s << endl;
            }
            Myfile.close();
        }
    }
    void AddNewUserScreen(string UserFilename)
    {
        vector <string> Vuser;
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "Add New Clients Screen  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
        Vuser = AddUser(UserFilename);
        AddUserDataToFile(Vuser, UserFilename);
        system("pause");
    }

    bool FindUserByUserName(vector <Suser> Vuser, string Userfilename, string UserName,Suser &User)
    {
        Vuser = LoadUserDataFromFile(Userfilename);

        for (Suser& U : Vuser)
        {
            if ((U.UserName == UserName))
            {
                User = U;
                return true;
            }
        }
        return false;


    }
    void printLineRecordUser(Suser User)
    {
        cout << "\n\nThe following are the User details:\n";
        cout << "\nUser Number        :" << User.UserName;
        cout << "\nPassaword          :" << User.Passaword;
        cout << "\nPermession         :" << User.Permession << endl;
       
    }
    bool MarkUserToDeleteFromFileByUserNumber(vector <Suser>& Vuser, string accountname, string Userfilename)
    {
        Vuser = LoadUserDataFromFile(Userfilename);
        for (Suser& C : Vuser)
        {
            if (C.UserName == accountname)
            {
                C.MarketToDelete = true;
                return true;
            }
        }
        return false;
    }
    void SaveUserDataTofile(vector <Suser> Vuser, string Userfilename)
    {
        fstream Myfile;
        string Dataline;
        Myfile.open(Userfilename, ios::out);

        if (Myfile.is_open())
        {
            for (Suser& C : Vuser)
            {
                if (C.MarketToDelete == false)
                {
                    Dataline = convertRecorduserToLine(C, "#//#");
                    Myfile << Dataline << endl;
                }
            }
            Myfile.close();
        }


    }
    bool DeleteUserByUserNumber(vector <Suser> Vuser, string UserName, string Userfilename)
    {
        Suser User; char answer;
        if (FindUserByUserName(Vuser, Userfilename, UserName,User))
        {
            printLineRecordUser(User);
            cout << "\nAre you sure you want to deleter this User if yes click 'y' if no click 'n'\n";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                MarkUserToDeleteFromFileByUserNumber(Vuser, UserName, Userfilename);
                SaveUserDataTofile(Vuser, Userfilename);
                cout << "\nUser delete succesfully\n ";

                return true;
            }
            Vuser = LoadUserDataFromFile(Userfilename);

        }
        else
        {
            cout << "Client whith account number (" << UserName << ") NOT found " << endl;
        }
        return false;


    }
    void DeleteUserInfo(string Userfilename)
    {
        system("cls");
        vector <Suser> Vuser;
        Vuser = LoadUserDataFromFile(Userfilename); string UserNumber;
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "Delete User Screen  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
        cout << "Please Enter User Number?  ";
        cin >> UserNumber;
        DeleteUserByUserNumber(Vuser, UserNumber, Userfilename);
        system("pause");
    }

    bool UpdateUserDataFromFileByUserNumber(vector <Suser>& Vuser, string UserName, string Userfilename)
    {
        Vuser = LoadUserDataFromFile(Userfilename);
        for (Suser& C : Vuser)
        {
            if (C.UserName == UserName)
            {
                cin.ignore();
                cout << "\n\nenter User Name? "; getline(cin ,C.UserName);
                cout << "enter passaword? "; getline(cin, C.Passaword);
                C.Permession = ReadPermession();
               

                return true;
            }
        }
        return false;
    }
    bool UpdateUserByUserNumber(vector <Suser> Vuser, string UserName, string Userfilename)
    {
        Suser User; char answer;
        if (FindUserByUserName(Vuser, Userfilename, UserName, User))
        {
            printLineRecordUser(User);
            cout << "\nAre you sure you want to Update this User if yes click 'y' if no click 'n'\n";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                UpdateUserDataFromFileByUserNumber(Vuser, UserName, Userfilename);
                SaveUserDataTofile(Vuser, Userfilename);
                cout << "\nUser Updated succesfully\n ";

                return true;
            }
            Vuser = LoadUserDataFromFile(Userfilename);

        }
        else
        {
            cout << "User whith User number (" << UserName << ") NOT found " << endl;
        }
        return false;


    }
    void UpdateUserInfo(string Userfilename)
    {
        system("cls");
        vector <Suser> Vuser;
        Vuser = LoadUserDataFromFile(Userfilename); string UserNumber;
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "Delete User Screen  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
        cout << "Please Enter User Number?  ";
        cin >> UserNumber;
        UpdateUserByUserNumber(Vuser, UserNumber, Userfilename);
        system("pause");
    }

    bool FindUserByUserName(vector <Suser> Vuser, string UserName, string Userfilename)
    {
        Suser User;
        if (FindUserByUserName(Vuser, Userfilename, UserName, User))
        {
            printLineRecordUser(User);
            return true;
        }
        else
        {
            cout << "User whith User number (" << UserName << ") NOT found " << endl;
            return false;
        }
    }
    void FindUserShowScreen(string Userfilename)
    {
        system("cls");
        vector <Suser> Vuser;
        Vuser = LoadUserDataFromFile(Userfilename); string UserNumber;
        cout << "-------------------------------------------------------------------\n\n";
        cout << left << setw(10) << "Find User Screen  \n\n";
        cout << "-------------------------------------------------------------------\n\n";
        cout << "Please Enter User Number?  ";
        cin >> UserNumber;
        FindUserByUserName(Vuser, UserNumber, Userfilename);
        system("pause");
        
    }

    void PrintManageUserScreen(string UserfileName,string filename,Suser User)
    {
       
        vector <Suser> Vuser;
        bool running = true;
        short choice;
        while (running)
        {
            system("cls");
            cout << "-------------------------------------------------------------------------------------------------\n";
            cout << "--------------------------------------------------------------------------------------------------\n\n";
            cout << left << setw(40) << "            Manage User  MENU  SCREEN" << endl << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            cout << "--------------------------------------------------------------------------------------------------\n\n";
            cout << left << setw(35) << " [1] List Users. " << endl;
            cout << left << setw(35) << " [2] Add New User. " << endl;
            cout << left << setw(35) << " [3] Delete  User. " << endl;
            cout << left << setw(35) << " [4] Update User. " << endl;
            cout << left << setw(35) << " [5] find User. " << endl;
            cout << left << setw(35) << " [6] Main Menu. " << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            cout << "--------------------------------------------------------------------------------------------------\n\n";
            cout << "Choose what Do You Want To Do?  [1 to 6]? ";
            cin >> choice;
            switch (choice) {
            case 1:
                system("cls");
                
                ListUserShow(UserfileName, Vuser);
                break;
            case 2:
                system("cls");
                AddNewUserScreen(UserfileName);
                break;
            case 3:
                system("cls");
                DeleteUserInfo(UserfileName);
                break;
            case 4:
                system("cls");
                UpdateUserInfo(UserfileName);
                break;
            case 5:
                system("cls");
                FindUserShowScreen(UserfileName);
                break;
            case 6:
                system("cls");
                PrintMainMenu(UserfileName, filename,User);
                running = false;
                break;
            default:
                cout << "Invalid choice.\n";
                break;
            }
        }



    } 


    void PrintTranscationMenu(string filename, vector <Sclient>& Vclient)
    {
        

        bool running = true;
        short choice;
        while (running)
        {
            system("cls");
            cout << "-------------------------------------------------------------------------------------------------\n";
            cout << "--------------------------------------------------------------------------------------------------\n\n";
            cout << left << setw(40) << "             TRANSCATION  MENU  SCREEN" << endl << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            cout << "--------------------------------------------------------------------------------------------------\n\n";
            cout << left << setw(35) << " [1] Deposit. " << endl;
            cout << left << setw(35) << " [2] Whith Draw. " << endl;
            cout << left << setw(35) << " [3] Total Balance. " << endl;
            cout << left << setw(35) << " [4] Main Menu. " << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            cout << "--------------------------------------------------------------------------------------------------\n\n";
            cout << "Choose what Do You Want To Do?  [1 to 4]? ";
            cin >> choice;
            switch (choice) {
            case 1:
                system("cls");
                DepositScreen(filename, Vclient);
                break;
            case 2:
                system("cls");
                WhithDrawScreen(filename, Vclient);
                break;
            case 3:
                system("cls");
                ShowtoTalBalance(filename, Vclient);
                break;
            case 4:
                system("cls");
                running = false;
                break;
            default:
                cout << "Invalid choice.\n";
                break;
            }

        }
    }
    void PrintMainMenu(string UserfileName , string filename,Suser User)
        {
            vector <Sclient> Vclient = LoadClientDataFromFile(filename);
            bool running = true;
            short choice;
            while (running)
            {
                system("cls");
                cout << "-------------------------------------------------------------------------------------------------\n";
                cout << "--------------------------------------------------------------------------------------------------\n\n";
                cout << left << setw(40) << "MAIN  MENU  SCREEN" << endl << endl;
                cout << "-------------------------------------------------------------------------------------------------\n";
                cout << "--------------------------------------------------------------------------------------------------\n\n";
                cout << left << setw(35) << " [1] Show Client List. " << endl;
                cout << left << setw(35) << " [2] Add New Client. " << endl;
                cout << left << setw(35) << " [3] Delete Client. " << endl;
                cout << left << setw(35) << " [4] Update Client Info. " << endl;
                cout << left << setw(35) << " [5] Find Client . " << endl;
                cout << left << setw(35) << " [6] Transcation Menu. " << endl;
                cout << left << setw(35) << " [7] Manage User Menu. " << endl;
                cout << left << setw(35) << " [8] Log out . " << endl;
                cout << "-------------------------------------------------------------------------------------------------\n";
                cout << "--------------------------------------------------------------------------------------------------\n\n";
                cout << "Choose what Do You Want To Do?  [1 to 6]? ";
                cin >> choice;
                switch (choice) {
                case 1:
                    system("cls");
                    if (!CheckPermission(EnShowMainMenuPermission::PclientListShow,User))
                    {
                        AccessDenied();
                        return;
                    }
                    ClientList(filename, Vclient);
                    break;
                case 2:
                    if (!CheckPermission(EnShowMainMenuPermission::PaddClientShow, User))
                    {
                        AccessDenied();
                        return;
                    }
                    system("cls");
                    AddNewClient(filename);

                    break;
                case 3:
                    if (!CheckPermission(EnShowMainMenuPermission::PdeleteClientShow, User))
                    {
                        AccessDenied();
                        return;
                    }
                    system("cls");
                    DeleteClientInfo(filename, Vclient);
                    break;
                case 4:
                    if (!CheckPermission(EnShowMainMenuPermission::PupdateClientShow, User))
                    {
                        AccessDenied();
                        return;
                    }
                    system("cls");
                    UpdateClientDataInfo(filename, Vclient);
                    break;
                case 5:
                    if (!CheckPermission(EnShowMainMenuPermission::PfindClientShow, User))
                    {
                        AccessDenied();
                        return;
                    }
                    system("cls");
                    FindClientScreen(filename, Vclient);
                    break;
                case 6:
                    if (!CheckPermission(EnShowMainMenuPermission::PtranscationShow, User))
                    {
                        AccessDenied();
                        return;
                    }
                    system("cls");
                    PrintTranscationMenu(filename, Vclient);
                    break;
                case 7:
                    if (!CheckPermission(EnShowMainMenuPermission::PmanageUser, User))
                    {
                        AccessDenied();
                        return;
                    }
                    system("cls");
                    PrintManageUserScreen(UserfileName,filename,User);
                case 8:
                    system("cls");
                    Login(UserfileName,filename);
                    running = false;
                    break;
                default:
                    cout << "Invalid choice.\n";
                    break;
                }

            }
        }

    void Login(string Usersfilename, string filename)
        {
            Suser User;
            cout << "-------------------------------------------------------------------\n\n";
            cout << left << setw(10) << "         Login Screen  \n\n";
            cout << "-------------------------------------------------------------------\n\n";
            User = ReadUser();

            while (!(CheckIfUserIsExist(User, Usersfilename,User.UserName,User.Passaword)))
            {
                system("cls");
                cout << "Invalid Username/Passaword ";
                User = ReadUser();
            }
            if (CheckIfUserIsExist(User, Usersfilename, User.UserName, User.Passaword))
            {
                PrintMainMenu(Usersfilename, filename,User);
                
            }
           

        }

    

}
namespace AtmSystem
{
    using namespace BankExtension1;
    using namespace BankExtension2;
    void LoginAtm(string filename);
    void AtmMainMenu(string filename, Sclient Client);
    bool CheckIfClientIsExist(Sclient& Client, string filename, string AccountNumber, string PinCode)
    {
        vector <Sclient> Vuser = LoadClientDataFromFile(filename);

        for (Sclient& U : Vuser)
        {
            if ((U.Accountnumber == AccountNumber) && (U.pincode == PinCode))
            {
                Client = U;
                return true;
            }
        }
        return false;


    }
    bool TakeMoneyFromClientBalance(string filename, string accountName, vector <Sclient>& Vclient)
    {
        Sclient client;
        int WhithdrawAmount; char comformation;
        cout << "Enter an Amount Multiple of 5  ";
        cin >> WhithdrawAmount;

        for (Sclient& C : Vclient)
        {
            if (C.Accountnumber == accountName)
            {
                while (!(((WhithdrawAmount % 5) == 0) && (WhithdrawAmount > client.accountbalance)))
                {
                    cout << "Enter an Amount Multiple of 5  ";
                    cin >> WhithdrawAmount;
                }
            }
        }

        cout << "\n\n\n Are you sure you want to perform this transcation y/n?";
        cin >> comformation;
        if (comformation == 'y' || comformation == 'Y')
        {
            for (Sclient& C : Vclient)
            {
                if (C.Accountnumber == accountName)
                {
                    C.accountbalance -= WhithdrawAmount;
                    CurrentClient.accountbalance = C.accountbalance;

                    SaveClientsDataTofile(Vclient, filename);
                    cout << "\n\nDone Succesfully New balance is   " << C.accountbalance << endl;
                    return true;
                }




            }
            CurrentClient.accountbalance -= WhithdrawAmount;
            return false;

        }
    }

    void CheckBalance(string filename, vector <Sclient>& Vclient,string accountName)
    {
        CurrentClient;
        system("cls");
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "--------------------------------------------------------------------------------------------------\n\n";
        cout << "\t\t\t Check Balance  SCREEN" << endl << endl;
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "--------------------------------------------------------------------------------------------------\n\n";
        cout << "Your Balance is:  " << CurrentClient.accountbalance << endl;


       
        system("pause");

    }

    bool TakeMoneyFromClientBalanceByQuickWhithDraw(string filename, string accountName, vector <Sclient>& Vclient,int WhithdrawAmount)
    {
        Sclient client;
       
        for (Sclient& C : Vclient)
        {
            if (C.Accountnumber == accountName)
            {
                if (WhithdrawAmount > C.accountbalance)
                {
                    cout << "Your Acount Balance is not enough please enter anothe one\n";
                    system("pause");
                }

                
            }
        }

      
            for (Sclient& C : Vclient)
            {
                if (C.Accountnumber == accountName)
                {
                    C.accountbalance -= WhithdrawAmount;
                    CurrentClient.accountbalance = C.accountbalance;

                    SaveClientsDataTofile(Vclient, filename);
                    cout << "\n\nDone Succesfully New balance is   " << C.accountbalance << endl;
                    return true;
                }




            }
            CurrentClient.accountbalance -= WhithdrawAmount;

            return false;

        
    }

    void QuickWhithDrawScreen(Sclient Client,string filename, vector <Sclient>& Vclient)
    {
        bool running = true;
        short choice; char answer;
        while (running)
        {
            system("cls");
            cout << "-------------------------------------------------------------------------------------------------\n";
            cout << "--------------------------------------------------------------------------------------------------\n\n";
            cout << " \t\t\t\t            Quick Whith Draw  SCREEN" << endl << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            cout << "--------------------------------------------------------------------------------------------------\n\n";
            cout << " \t\t[1] 20.  \t\t [2] 50 " << endl;
            cout << " \t\t[3] 100. \t\t [4] 200" << endl;
            cout << " \t\t[5] 400.  \t\t[6] 600" << endl;
            cout << " \t\t[7] 800. \t\t [8] 1000" << endl;
            cout << " \t\t[9] Exit." << endl;
            cout << "-------------------------------------------------------------------------------------------------\n";
            cout << "--------------------------------------------------------------------------------------------------\n\n";
            cout << "Your Balance is:  " << Client.accountbalance << endl;
            cout << "Choose what Do You Want To Do?  [1 to 4]? ";
            cin >> choice;
            cout << "are you sure to perform this action y/n?  ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {

                switch (choice) {
                case 1:
                    TakeMoneyFromClientBalanceByQuickWhithDraw(filename, Client.Accountnumber, Vclient, 20);
                    break;
                case 2:
                    TakeMoneyFromClientBalanceByQuickWhithDraw(filename, Client.Accountnumber, Vclient, 50);
                    break;
                case 3:
                    TakeMoneyFromClientBalanceByQuickWhithDraw(filename, Client.Accountnumber, Vclient, 100);
                    break;
                case 4:
                    TakeMoneyFromClientBalanceByQuickWhithDraw(filename, Client.Accountnumber, Vclient, 200);
                    break;
                case 5:
                    TakeMoneyFromClientBalanceByQuickWhithDraw(filename, Client.Accountnumber, Vclient, 400);
                    break;
                case 6:
                    TakeMoneyFromClientBalanceByQuickWhithDraw(filename, Client.Accountnumber, Vclient, 600);
                    break;
                case 7:
                    TakeMoneyFromClientBalanceByQuickWhithDraw(filename, Client.Accountnumber, Vclient, 800);
                    break;
                case 8:
                    TakeMoneyFromClientBalanceByQuickWhithDraw(filename, Client.Accountnumber, Vclient, 1000);
                    break;
                case 9:
                    AtmMainMenu(filename, Client);
                    running = false;
                    break;
                default:
                    cout << "Invalid choice.\n";
                    break;
                }
            }
            system("pause");

        }
    }


    void NormalWhithDraw(string filename,Sclient Client, vector <Sclient>& Vclient)
    {
        system("cls");
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "--------------------------------------------------------------------------------------------------\n\n";
        cout << " \t\t\t\t            Normal Whith Draw  SCREEN" << endl << endl;
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "--------------------------------------------------------------------------------------------------\n\n";
        TakeMoneyFromClientBalance(filename, Client.Accountnumber, Vclient);
      
        system("pause");
    }

    void SaveOneClientDataTofile(Sclient client, string filename)
    {
        fstream Myfile;
        string Dataline;
        Myfile.open(filename, ios::out);

        if (Myfile.is_open())
        {
         
            
                if (client.MarkToDelete == false)
                {
                    Dataline = convertRecordToLine(client, "#//#");
                    Myfile << Dataline << endl;
                }
            
            Myfile.close();
        }


    }


    bool AddMoneyFromClientBalance(string filename, string accountName, vector <Sclient>& Vclient)
    {
        Sclient client;
        int WhithdrawAmount; char comformation;
        cout << "Enter an Amount Multiple of 5  ";
        cin >> WhithdrawAmount;

        for (Sclient& C : Vclient)
        {
            if (C.Accountnumber == accountName)
            {
                while (!(((WhithdrawAmount % 5) == 0) && (WhithdrawAmount > client.accountbalance)))
                {
                    cout << "Enter an Amount Multiple of 5  ";
                    cin >> WhithdrawAmount;
                }
            }
        }

        cout << "\n\n\n Are you sure you want to perform this transcation y/n?";
        cin >> comformation;
        if (comformation == 'y' || comformation == 'Y')
        {
            for (Sclient& C : Vclient)
            {
                if (C.Accountnumber == accountName)
                {
                    C.accountbalance += WhithdrawAmount;
                    CurrentClient.accountbalance = C.accountbalance;

                    SaveClientsDataTofile(Vclient, filename);
                    cout << "\n\nDone Succesfully New balance is   " << C.accountbalance << endl;
                    return true;
                }




            }
            CurrentClient.accountbalance += WhithdrawAmount;
            return false;

        }
    }
    void DepositClientScreen(string filename, Sclient Client, vector <Sclient>& Vclient)
    {
        system("cls");
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "--------------------------------------------------------------------------------------------------\n\n";
        cout << " \t\t\t\t            Deposit  SCREEN" << endl << endl;
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "--------------------------------------------------------------------------------------------------\n\n";
        AddMoneyFromClientBalance(filename, Client.Accountnumber,Vclient);
        system("pause");
    }


    void AtmMainMenu(string filename, Sclient Client)
        {
            vector <Sclient> Vclient = LoadClientDataFromFile(filename);
            bool running = true;
            short choice;
            while (running)
            {
                system("cls");
                cout << "-------------------------------------------------------------------------------------------------\n";
                cout << "--------------------------------------------------------------------------------------------------\n\n";
                cout << "\t\t\tATM MAIN  MENU  SCREEN" << endl << endl;
                cout << "-------------------------------------------------------------------------------------------------\n";
                cout << "--------------------------------------------------------------------------------------------------\n\n";
                cout << " \t\t[1] Quick Whith Draw. " << endl;
                cout << " \t\t[2] Normal Whith Draw. " << endl;
                cout << " \t\t[3] Deposit . " << endl;
                cout << " \t\t[4] Check Balance. " << endl;
                cout << " \t\t[5] Log out . " << endl;
                cout << "-------------------------------------------------------------------------------------------------\n";
                cout << "--------------------------------------------------------------------------------------------------\n\n";
                cout << "Choose what Do You Want To Do?  [1 to 6]? ";
                cin >> choice;
                switch (choice) {
                case 1:
                    system("cls");
                    QuickWhithDrawScreen(Client, filename,Vclient);
                    break;
                case 2:
                    NormalWhithDraw(filename,Client,Vclient);
                    break;
                case 3:
                    DepositClientScreen(filename,Client,Vclient);
                    break;
                case 4:
                    CheckBalance(filename, Vclient,Client.Accountnumber);
                    break;
                case 5:
                    system("cls");
                    LoginAtm(filename);
                    running = false;
                    break;
                default:
                    cout << "Invalid choice.\n";
                    break;
                }

            }
        }
    void LoginAtm(string filename)
        {
            Sclient Client;
            cout << "-------------------------------------------------------------------\n\n";
            cout << left << setw(10) << "         Login Screen  \n\n";
            cout << "-------------------------------------------------------------------\n\n";
            cout << "\nEnter Account Number? ";
            getline(cin >> ws, Client.Accountnumber);
            cout << "Enter PinCode? ";
            getline(cin, Client.pincode);

            while (!(CheckIfClientIsExist(Client, filename, Client.Accountnumber, Client.pincode)))
            {
                system("cls");
                cout << "Invalid Account number/Pincode ";
                getline(cin >> ws, Client.Accountnumber);
                cout << "Enter PinCode? ";
                getline(cin, Client.pincode);
            }
            if (CheckIfClientIsExist(Client, filename, Client.Accountnumber, Client.pincode))
            {
                  CurrentClient = Client;
                AtmMainMenu(filename, Client);

            }


        }

    
}