#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "tools.h"
#include <limits>
#include <iomanip>
#include <cstring>
#include <conio.h>
using namespace std;
//using namespace colorlib;

struct Transfer
{
    int transferNumber;
    int from_user;
    int to_user;
    double amount;
    bool received = false;
    string get_time, show;
};

struct User
{
    string username;
    string password;
    string userType;
    string phoneNumber;
    bool isActive;
    string usertayp;
    int number;
    double balanc = 0.0;
    int puk;
};

struct Notice
{
    int balanc;
    string toid;
    string frid;
    int amount;
    short number;
};

/*
struct information
{
    Transfer info_trans;
    Notice info_notice;
    User info_users;
};
*/

vector<User> users;
vector<Transfer> trans;
vector<Notice> note;

/* LOAD FROM FILES */
void loadUsersFromFile(vector<User> &users);
void loadnoteFromFile(vector<Notice> &note);
void loadtransFromFile(vector<Transfer> &trans);
void loadtransFromFile(vector<Transfer> &trans);

/* SAVE TO FILES */
void savetrans(const vector<User> &users, const vector<Transfer> &trans);
void saveUsersToFile(const vector<User> &users);
void savenote(vector<User> &users, vector<Notice> &note);

/*CHECK ERRORS */
bool isValidPhoneNumber(const string &phoneNumber);
bool isValidNumber(const string &str);
short checkerror(int &numberr, int &neu);
void checkadmin(vector<User> &users);

/* EDIT & DATALIST */
void editUser(vector<User> &users);
void datelise(vector<User> &users, vector<Transfer> &trans, int numberuser);

/* DESPOSITS */
void depositmoney(vector<User> &users, vector<Transfer> &trans, vector<Notice> &note, int numberuser);
void deposit(vector<User> &users, vector<Transfer> &trans, vector<Notice> &note, int numberuser);

/* TRANSFERS */
int TransferNumber(vector<Transfer> &trans);
void transf(vector<User> &users, vector<Transfer> &trans, int numberuser);
void receiveTransfer(vector<User> &users, vector<Transfer> &trans, int numberuser);

/* FINDS INDEX */
int findUserIndex(const vector<User> &users, const double &number);
int findtransIndex(const vector<Transfer> &trans, const double &number);

/* DELETE */
void deleteUser(vector<User> &users);
void deletetrans(vector<Transfer> &trans);

/* SHOWS */
void displaytransfer(vector<Transfer> &trans);
void showadmin(vector<User> &users, vector<Transfer> &trans, int &numberr, int &neu, int numberuser, string usertype, vector<Notice> &note);
void displaynote(vector<Notice> &note, string name);

/* TOOLS */
string gettime();
void sleeps(int j);
int login();
void start_main();

/* ADD USER & SEARCH */
void addUser(vector<User> &users, const string &userType);
void searchtrans(vector<Transfer> &trans, int numbertrans);

/*start main*/
int main()
{
    loadUsersFromFile(users);
    loadtransFromFile(trans);
    loadnoteFromFile(note);
    checkadmin(users);
    start_main(); // <---- main
    return 0;
}
/* end main */

void savenote(vector<User> &users, vector<Notice> &note)
{
    ofstream file("note.csv");
    for (const auto &noti : note)
    {
        file << noti.frid << "," << noti.toid << "," << noti.balanc << " " << noti.amount << " " << noti.number << "\n";
    }
    file.close();
}

void loadnoteFromFile(vector<Notice> &note)
{
    ifstream file;
    file.open("note.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        Notice notis;
        getline(ss, notis.frid, ',');
        getline(ss, notis.toid, ',');
        ss >> notis.balanc >> notis.amount >> notis.number;
        note.push_back(notis);
    }
    file.close();
}

void displaynote(vector<Notice> &note, string name)
{
    //	type 1 depositmoney , 2 deposit to your id
    int num = 1;
    for (const auto no : note)
    {
        setcolor(7);
        if (no.number == 1)
        {
            if (no.toid == name)
            {
                cout << "  " << num << ")  Deposit / " << no.frid << "  to your account  {" << no.balanc << " $ }"
                     << " your balanc {" << no.amount << " $ } " << endl;
                num++;
            }
            else if (no.frid == name || no.toid == name)
            {
                cout << "  " << num << ")  " << no.frid << " deposit  "
                     << "to account " << no.toid << " amount {" << no.balanc << " $ }" << endl; //<< " your balanc {"<<no.amount<<"$} YER"<<endl;
                num++;
            }
        }
        if (no.number == 2 && no.frid == name)
        {
            cout << "  " << num << ")  Deposit / " << no.frid << " to your account  {" << no.balanc << " $"
                 << " }"
                 << " your balanc {" << no.amount << " $ }" << endl;
            num++;
        }
    }
    cin.ignore();
    cin.get();
}

void start_main()
{
    
    string s, phoneNumber;
    int numberr = 0, neu = 0, usernames;
    bool f = false;
    while (true)
    {
    redd:
        if (checkerror(numberr, neu) == -1)
        {
            break;
        }
        int chek = login();
        if (chek == 1)
        {
            cout << "\n";
            setcolor(3);
            cout << " -----------------" << endl;
            cout << "| Enter ID user: |\n";
            cout << " -----------------" << endl;
            usernames = chose3();
            cout << " -----------------" << endl;
            cout << "| Enter password: |\n";
            cout << "  -----------------" << endl;
            cin.ignore();
            getline(cin, s);
            cout << endl;
            User *loggedInUser = nullptr;
            for ( auto &user : users)
            {
                if (user.number == usernames && user.password == s)
                {
                    if (user.isActive != 1)
                    {
                        f = true;
                    }
                    if (user.isActive == 1)
                    {
                        loggedInUser = &user;
                        break;
                    }
                }
            }
            if (!loggedInUser && f == false)
            {
                system("cls");
                setcolor(4);
                cout << "\t\t\t + Invalid username or password +\n";
                s.clear();
                numberr++;
                goto redd;
            }
            if (!loggedInUser && f == true)
            {
                setcolor(4);
                cerr << "\t\t\t\t The user is not Active \n\n";
                goto redd;
            }
            numberr = 0;
            if (loggedInUser)
            {
                system("cls");
                cout << "\n\n\t  ";
                for (int i = 0; i < 12; i++)
                {
                    setcolor(31);
                    sleeps(6000000);
                    if (i)
                        cout << "     ";
                    if (i == 11)
                        setcolor(0);
                }
            }
            int numberuser = 0;
            if (loggedInUser->userType == "Admin" && loggedInUser->isActive == 1)
            {
                numberuser = loggedInUser->number;
                showadmin(users, trans, numberr, neu, numberuser, "Admin", note);
            }
            else if (loggedInUser->userType == "Employee" && loggedInUser->isActive == 1)
            {
                numberuser = loggedInUser->number;
                showadmin(users, trans, numberr, neu, numberuser, "Employee", note);
            }
            else if (loggedInUser->userType == "Customer" && loggedInUser->isActive == 1)
            {
                numberuser = loggedInUser->number;
                showadmin(users, trans, numberr, neu, numberuser, "Customer", note);
            }
        }

        else if (chek == 2)
        {
            addUser(users, "Customer");
        }
        else if (chek == 3)
        {
            string user_or_id, name_user;
            int id_user, code_user;
            User *check_user = nullptr;
            cout << "Forgot Id or Password ( 1 <-> Password , 2 <-> Id )\n";
            cin.ignore();
            getline(cin, user_or_id);
            setcolor(3);            
            if (user_or_id == "1")
            {
                cout << " Enter Your ID : ";
                id_user = chose3();
            }
            else if (user_or_id == "2")
            {
                cout << " Enter Username  : ";
                getline(cin, name_user);
            }
          cin.ignore();
        phones:
            setcolor(3);
            cout << " Enter Your Phone Number : ";
            getline(cin, phoneNumber,'\n');
            while (!isValidPhoneNumber(phoneNumber))
            {
                setcolor(4);
                goto phones;
            }
            cout << " Enter the PUK code : ";
            code_user = chose3();

            for (auto &code : users)
            {
                if (code.number == id_user && code.phoneNumber == phoneNumber)
                {
                    if (code.puk== code_user)
                    {
                        check_user = &code;
                        break;
                    }
                }
                else if (code.username == name_user && code.phoneNumber == phoneNumber)
                {
                    if (code.puk== code_user)
                    {
                        check_user = &code;
                        break;
                    }
                }
            }
            if (check_user)
            {
                setcolor(2);
                if (user_or_id == "1")
                {
                    cout << " \nYour Password is : --->  "
                         << check_user->password << endl;
                }
                else if (user_or_id == "2")
                {
                    cout << " \nYour Id is : --->  "
                         << check_user->number << endl;
                }
            }

            if (!check_user)
            {
                setcolor(4);
                cerr << "\nData error, please check the data entered" << endl;
            }
        }

        else if (chek == 4)
        {
            system("cls");
            setcolor(4);
            cout << "\n\n";
            cout << "\t\t  * * * * * * * * * * * * * * * * * * * * *" << endl;
            cout << "\t\t  *  C L O S E D   S Y S T E M   B A N K  *" << endl;
            cout << "\t\t  * * * * * * * * * * * * * * * * * * * * *" << endl;
            break;
        }
        else
        {
            setcolor(4);
            cerr << " Y O U R S   E N T E R   I S   N O T      C O R R E C T \n\n";
            break;
        }
    }
    cin.clear();
}

int login()
{
    setcolor(14);
    cout << "\n 1) L O G I N \n";
    cout << " 2) A D D    U S E R \n";
    cout << " 3) FORGOT YOUR PASSWORD OR ID ?\n";
    cout << " 4) C L O S E    S Y S T E M \n";
    return chose();
}

bool isValidPhoneNumber(const string &phone)
{
    for (int i = 0; i < phone.length(); i++)
    {
        if (!isdigit(phone.at(i)))
        {
            setcolor(4);
            cerr << "\n\t\t\t  Invalid number....  \n";
            return false;
        }
    }
    if (phone.length() != 9)
    {
        setcolor(4);
        if (phone.length() > 9)
        {
            cerr << "\n\t\t\t  Number is long....  \n";
        }
        if (phone.length() < 9)
        {
            cerr << "\n\t\t\t  Number is short....  \n";
        }
        return false;
    }
    string per = phone.substr(0, 2);
    if (per == "77" || per == "73" || per == "71" || per == "78")
    {
        return true;
    }
    setcolor(4);
    cerr << " \t\t\t Beginning phone number is vaild\n";
    return false;
}
void addUser(vector<User> &users, const string &userType)
{
    srand(time(0));
    User user;
    user.number = (rand() % 100000 + 10000);
    setcolor(2);
    setcolor(4);
    cout << "     YOUR ID USER  :";
    setcolor(2);
    cout << " | " << user.number << " |\n";
    setcolor(2);
run:
    setcolor(3);
    cout << "       -------------------" << endl;
    cout << "     | Enter username: |\n";
    cout << "       -------------------" << endl;
    cin.ignore();
    getline(cin, user.username);
    for (auto &existingUser : users)
    {
        if (existingUser.username == user.username)
        {
            setcolor(4);
            cerr << "\t| !! Username already added. ( Enter new username ) !! |" << endl;
            cin.clear();
            goto run;
        }
    }
    setcolor(3);
    cout << "       ------------------" << endl;
    cout << "     | Enter password: |\n";
    cout << "       ------------------" << endl;
    cout << " ";
    getline(cin, user.password);
    user.userType = userType;
so:
    string as;
    setcolor(3);
    cout << "      -----------------------" << endl;
    cout << "     | Enter male or famel |\n";
    cout << "       ----------------------" << endl;
    cout << "";
    cin >> as;
    if (as == "male" || as == "famel")
    {
        user.usertayp = as;
    }
    else
    {
        setcolor(4);
        cerr << "\nThe usertayp is error \n";
        goto so;
    }
phone:
    setcolor(3);
    cout << "      -----------------------" << endl;
    cout << "    | Enter phone number |\n";
    cout << "      -----------------------" << endl;
    cout << " ";
    cin >> user.phoneNumber;
    while (!isValidPhoneNumber(user.phoneNumber))
    {
        setcolor(4);
        goto phone;
    }
    setcolor(3);
    cout << "      -------------------------------" << endl;
    cout << "    | Is the user active? (1 , 0 ): |\n";
    cout << "      -------------------------------" << endl;
    cout << " ";
    cin >> user.isActive;

    double amount;
    setcolor(3);
    cout << "      -----------------------" << endl;
    cout << "    | Enter amount money |\n";
    cout << "      -----------------------" << endl;
    cout << " ";
    cin >> amount;
    user.balanc += amount;
    user.puk = (rand() % 999999 + 10000);
    users.push_back(user);
    saveUsersToFile(users);
    cout << endl;
    setcolor(2);
    cout << " * * * * * * * * * *" << endl;
    cout << " *  Users added  *" << endl;
    cout << " * * * * * * * * * *" << endl;
    cout << endl;
    cin.clear();
}

int findUserIndex(const vector<User> &users, const double &number)
{
    for (int i = 0; i < users.size(); ++i)
    {
        if (users[i].number == number)
        {
            return i;
        }
    }
    return -1;
}
void editUser(vector<User> &users)
{
    int username;
    setcolor(3);
    string editusername, edit;
    cout << "Enter ID to edit: ";
    cin >> username;
    int index = findUserIndex(users, username);
    if (index == -1)
    {
        setcolor(4);
        cout << "User not found.\n";
        return;
    }

    User &user = users[index];
    cout << "Editing user: " << username << endl;
    /*
   cout << "Enter new ID: ";
   user.number = chose3();
   */
    cin.ignore();
    cout << " What are you need editing ,,,,,,,,,,\n";
    cout << " [ name  ,  password  ,  phone  , active , code] \n";
    getline(cin, edit);
a:
    if (edit == "name")
    {
        cout << "\nEnter new name: ";
        cin.ignore();
        getline(cin, editusername);

        for (auto &existingUser : users)
        {
            if (existingUser.username == editusername)
            {
                setcolor(4);
                cerr << "\t| !! Username already added. ( Enter new username ) !! |" << endl;
                cin.clear();
                goto a;
            }
        }
        user.username = editusername;
    }
    else if (edit == "password")
    {
        cout << "Enter new password: ";
        cin >> user.password;
    }
    else if (edit == "phone")
    {
        cout << "Enter new phone number: ";
        cin >> user.phoneNumber;
    }
    else if (edit == "active")
    {
        cout << "Is the user active? (1 for yes, 0 for no): ";
        cin >> user.isActive;
    }
    else if (edit == "code")
    {
        cout << " Enter new code : ";
        cin >> user.puk;
    }
    saveUsersToFile(users);
    setcolor(2);
    cout << "\t\t * * * * * * * * * * *" << endl;
    cout << "\t\t *  Users edited   *" << endl;
    cout << "\t\t * * * * * * * * * * *" << endl;
    cout << endl;
}
void deleteUser(vector<User> &users)
{
    int username;
    setcolor(3);
    cout << "Enter ID to delete: ";
    cin >> username;

    int index = findUserIndex(users, username);
    if (index == -1)
    {
        setcolor(4);
        cerr << "User not found.\n";
        return;
    }
    users.erase(users.begin() + index);
    saveUsersToFile(users);
    cout << endl;
    setcolor(2);
    cout << "\t\t * * * * * * * * * * *" << endl;
    cout << "\t\t *  Users deleted   *" << endl;
    cout << "\t\t * * * * * * * * * * *" << endl;
    cout << endl;
}

void deletetrans(vector<Transfer> &trans)
{
    double number;
    setcolor(3);
    cout << "Enter number [ Transfer ] : ";
    cin >> number;
    int index = findtransIndex(trans, number);
    if (index == -1)
    {
        setcolor(4);
        cout << "Number not found.\n";
        return;
    }
    trans.erase(trans.begin() + index);
    savetrans(users, trans);
    cout << endl;
    setcolor(2);
    cout << "\t\t * * * * * * * * * * * * *" << endl;
    cout << "\t\t *  Transfer deleted    *" << endl;
    cout << "\t\t * * * * * * * * * * * * *" << endl;
    cout << endl;
}

void saveUsersToFile(const vector<User> &users)
{
    ofstream file;
    file.open("users.csv");
    for (const auto &user : users)
    {
        file << user.username << "," << user.password << "," << user.usertayp << "," << user.userType << ","
             << user.phoneNumber << "," << user.isActive << " " << user.number << " " << user.balanc << " " << user.puk << "\n";
    }
    file.close();
}

void savetrans(const vector<User> &users, const vector<Transfer> &trans)
{
    ofstream transfer;
    transfer.open("transfer.csv");
    for (const auto &tran : trans)
    {
        transfer << tran.get_time << "," << tran.show << "," << tran.transferNumber << " " << tran.from_user << " " << tran.to_user << " " << tran.amount << " " << tran.received << "\n";
    }
    transfer.close();
    saveUsersToFile(users);
}
void loadUsersFromFile(vector<User> &users)
{
    ifstream file;
    file.open("users.csv");
    string line;
    while (!file.eof() && getline(file, line))
    {
        stringstream ss(line);
        User user;
        getline(ss, user.username, ',');
        getline(ss, user.password, ',');
        getline(ss, user.usertayp, ',');
        getline(ss, user.userType, ',');
        getline(ss, user.phoneNumber, ',');
        ss >> user.isActive >> user.number >> user.balanc >> user.puk;
        users.push_back(user);
    }
    file.close();
}

void loadtransFromFile(vector<Transfer> &trans)
{
    ifstream file;
    file.open("transfer.csv");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        Transfer tran;
        getline(ss, tran.get_time, ',');
        getline(ss, tran.show, ',');
        ss >> tran.transferNumber >> tran.from_user >> tran.to_user >> tran.amount >> tran.received;
        trans.push_back(tran);
    }
    file.close();
}

string gettime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

void displaytransfer(vector<Transfer> &trans)
{
    cout << "\n";
    setcolor(135);
    cout << left;
    setcolor(5);
    cout << "|";
    setcolor(135);
    cout << setw(6) << " Number ";
    setcolor(5);
    cout << "|";
    setcolor(135);
    cout << setw(7) << " From ID ";
    setcolor(5);
    cout << "|";
    setcolor(135);
    cout << setw(5) << " To ID ";
    setcolor(5);
    cout << "|";
    setcolor(135);
    cout << setw(5) << " Amount ";
    setcolor(5);
    cout << "|";
    setcolor(135);
    cout << setw(6) << " Status ";
    setcolor(5);
    cout << "|";
    setcolor(135);
    cout << setw(10) << "   Data ";
    setcolor(5);
    cout << "| ";
    setcolor(135);
    cout << " Time  ";
    setcolor(5);
    cout << "|" << setw(6);
    setcolor(135);
    cout << " state ";
    setcolor(5);
    cout << "|" << endl;
    setcolor(5);
    cout << " ------------------------------------------------------------------------- " << endl;

    for (auto transfer : trans)
    {
        cout << left;
        setcolor(5);
        cout << "|";
        if (transfer.transferNumber == 0)
        {
            setcolor(9);
            cout << setw(8) << "Null";
        }
        else
        {
            setcolor(8);
            cout << setw(8) << transfer.transferNumber;
        }
        setcolor(5);
        cout << "|";
        setcolor(8);
        if (transfer.from_user == 0)
        {
            setcolor(9);
            cout << setw(8) << "Null";
        }
        else
        {
            setcolor(8);
            cout << setw(8) << transfer.from_user;
        }
        setcolor(5);
        cout << "|";
        setcolor(8);
        cout << setw(7) << transfer.to_user;
        setcolor(5);
        cout << "|";
        setcolor(8);
        cout << setw(8) << transfer.amount;
        setcolor(5);
        cout << "|";
        setcolor(8);
        cout << setw(6);
        if (transfer.received == 1)
        {
            setcolor(2);
            cout << "Received";
        }
        else
        {
            setcolor(71);
            cout << "Pending";
        }
        setcolor(5);
        cout << "|" << setw(10);
        setcolor(15);
        cout << transfer.get_time;
        setcolor(5);
        cout << "|" << setw(6);
        setcolor(15);
        cout << transfer.show;
        setcolor(5);
        cout << "|" << endl;
        cout << " ------------------------------------------------------------------------- " << endl;
        setcolor(2);
    }
    cin.ignore();
    cin.clear();
    cin.get();
    system("cls");
}

void displayUsers(vector<User> &users, const string &userType)
{
    bool found = false;
    setcolor(5);
    cout << left << "|" << setw(3) << "number"
         << "|" << setw(5) << " Username "
         << " |" << setw(5) << " Password "
         << "  |" << setw(5) << "Phonenumber "
         << "|" << setw(10) << "  Usertype "
         << " |" << setw(4) << " sex "
         << " |" << setw(3) << "active"
         << "|" << endl;
    cout << " ----------------------------------------------------------------------- " << endl;
    if (userType == "Admin")
    {
        found = true;
    }

    if (found)
    {
        for (auto &user : users)
        {
            cout << left;
            setcolor(6);
            cout << "| " << setw(5);
            setcolor(15);
            cout << user.number;
            setcolor(6);
            cout << "| " << setw(7);
            setcolor(15);
            cout << setw(10) << user.username;
            setcolor(6);
            cout << "|  ";
            setcolor(15);
            cout << setw(10) << user.password;
            setcolor(6);
            cout << "|  ";
            setcolor(15);
            cout << setw(10) << user.phoneNumber;
            setcolor(6);
            cout << "|  ";
            setcolor(15);
            cout << setw(10) << user.userType;
            setcolor(6);
            cout << "| ";
            setcolor(15);
            cout << setw(5) << user.usertayp;
            setcolor(6);
            cout << "|  ";
            setcolor(15);
            cout << setw(3) << user.isActive;
            setcolor(6);
            cout << " |\n";
            cout << " ----------------------------------------------------------------------- " << endl;
        }
    }

    if (!found)
    {
        for (auto user : users)
        {
            if (user.userType == "Customer")
            {
                cout << left;
                setcolor(6);
                cout << "| " << setw(5);
                setcolor(15);
                cout << user.number;
                setcolor(6);
                cout << "| " << setw(7);
                setcolor(15);
                cout << setw(10) << user.username;
                setcolor(6);
                cout << "|  ";
                setcolor(15);
                cout << setw(10) << user.password;
                setcolor(6);
                cout << "|  ";
                setcolor(15);
                cout << setw(10) << user.phoneNumber;
                setcolor(6);
                cout << "|  ";
                setcolor(15);
                cout << setw(10) << user.userType;
                setcolor(6);
                cout << "| ";
                setcolor(15);
                cout << setw(5) << user.usertayp;
                setcolor(6);
                cout << "|  ";
                setcolor(15);
                cout << setw(3) << user.isActive;
                setcolor(6);
                cout << " |\n";
                cout << " ----------------------------------------------------------------------- " << endl;
            }
        }
    }
    setcolor(5);
    cout << "\n\n";
    cout << left << " | " << setw(6) << " PUK"
         << " | " << setw(3) << "USER_ID"
         << " | " << setw(7) << "Balanc"
         << " |" << endl;
    cout << " - - - - - - - - - - - - - - - " << endl;

    if (found)
    {
        for (auto user : users)
        {
            setcolor(6);
            cout << left << " | ";
            setcolor(15);
            cout << setw(6) << user.puk;
            setcolor(6);
            cout << " | ";
            setcolor(15);
            cout << setw(7) << user.number;
            setcolor(6);
            cout << " | ";
            setcolor(15);
            cout << setw(7) << user.balanc;
            setcolor(6);
            cout << " | " << endl;
            cout << "  - - - - - - - - - - - - - - " << endl;
        }
    }
    if (!found)
    {
        for (auto user : users)
        {
            if (user.userType == "Customer")
            {
                setcolor(6);
                cout << left << " | ";
                setcolor(15);
                cout << setw(6) << user.puk;
                setcolor(6);
                cout << " | ";
                setcolor(15);
                cout << setw(7) << user.number;
                setcolor(6);
                cout << " | ";
                setcolor(15);
                cout << setw(7) << user.balanc;
                setcolor(6);
                cout << " | " << endl;
                cout << "  - - - - - - - - - - - - - - " << endl;
            }
        }
    }
    cin.ignore();
    cin.clear();
    cin.get();
    system("cls");
    setcolor(3);
}
void depositmoney(vector<User> &users, vector<Transfer> &trans, vector<Notice> &note, int numberuser)
{
    int from_id, to_id;
    int amount;
    Transfer tran;
    Notice notis;
    setcolor(3);
    from_id = numberuser;
    tran.from_user = from_id;
    int indexx = findUserIndex(users, from_id);
    User &use = users[indexx];
    if (use.userType == "Customer")
    {
        cout << "\nYour id user : " << from_id << "\n Your balans : " << use.balanc << "\n"
             << endl;
    }
    else
    {
        cout << "Enter Your Id\n";
        from_id = chose3();
    }
    indexx = findUserIndex(users, from_id);
    if (indexx == -1)
    {
        setcolor(4);
        cerr << "\n\t\t\t Not found ID \n"
             << endl;
        return;
    }
    if (indexx != -1)
    {
        if (use.balanc <= 0)
        {
            setcolor(4);
            cerr << " \n\t\t\tYour balance is ZERO OR  ( ENTER NEW ID USER )\n";
            return;
        }
        if (use.balanc > 0)
        {
            setcolor(3);
            cout << " Enter amount for trans.... " << endl;
            cin >> amount;
            tran.amount = amount;
            use.balanc -= amount;
        }
    }
    setcolor(3);
    cout << " To ID USER" << endl;
    to_id = chose3();
    tran.to_user = to_id;
    int indexxx = findUserIndex(users, to_id);
    User &usee = users[indexxx];

    if (indexxx == -1)
    {
        setcolor(4);
        cerr << " \n\t\t\tNot found ID " << endl;
        return;
    }

    if (numberuser == to_id)
    {
        setcolor(4);
        cerr << " The Recipient ID Same Your ID ";
        return;
    }

    if (indexxx != -1)
    {
        usee.balanc += amount;
    }
    setcolor(9);
    cout << "Succsessful, Desposit Money from ID";
    setcolor(11);
    cout << " [ " << from_id << " ]";
    string y = "------>";
    for (int i = 0; i < 7; i++)
    {
        setcolor(8);
        if (i == 6)
            setcolor(11);
        sleeps(15000000);
        if (i)
            cout << y[i] << " ";
    }
    cout << " [ " << to_id << " ]";

    notis.toid = usee.username;
    notis.balanc = amount;
    notis.frid = use.username;
    notis.amount = usee.balanc;
    notis.number = 1;
    tran.transferNumber = 0;
    tran.received = true;
    tran.get_time = gettime();
    tran.show = "Desposit";
    trans.push_back(tran);
    note.push_back(notis);
    savetrans(users, trans);
    savenote(users, note);
    cin.ignore();
    cin.get();
}

/*
void loadnoteFromFile(vector<Notice> &note)
{
	ifstream file("transfer.csv");
	string line;
	while (getline(file, line))
	{
		stringstream ss(line);
		Transfer tran;
		getline(ss, tran.get_time, ',');
		getline(ss, tran.show, ',');
		ss >> tran.transferNumber >> tran.from_user >> tran.to_user >> tran.amount >> tran.received;
		trans.push_back(tran);
	}
	file.close();
}
*/
void deposit(vector<User> &users, vector<Transfer> &trans, vector<Notice> &note, int numberuser)
{
    int to_id;
    double amount;
    Transfer tran;
    Notice noti;
    to_id = numberuser;
    tran.from_user = 0;
    tran.to_user = to_id;
    int indexxx = findUserIndex(users, to_id);
    User &usee = users[indexxx];
    if (usee.userType == "Customer")
    {
        cout << "\nYour id user : " << to_id << "\n Your balans : " << usee.balanc << "\n"
             << endl;
    }

    else
    {
        setcolor(3);
        cout << " Enter ID USER " << endl;
        to_id = chose3();
        tran.from_user = 0;
        tran.to_user = to_id;
        indexxx = findUserIndex(users, to_id);
        //     User &usee = users[indexxx];
    }
    if (indexxx == -1)
    {
        setcolor(4);
        cerr << "\t\t\t Not found ID " << endl;
        cin.ignore();
        cin.get();
        return;
    }
    else
    {
        //indexxx = findUserIndex(users, to_id);
        User &usee = users[indexxx];
        setcolor(3);
        cout << " Enter amount for .... " << endl;
        cin >> amount;
        usee.balanc += amount;
        tran.amount = amount;
        noti.amount = usee.balanc;
        noti.frid = usee.username;
    }

    cout << "Succsessful, Deposit Money To Id User [ " << to_id << " ]" << endl;
    tran.transferNumber = 0;
    tran.received = true;
    tran.get_time = gettime();
    tran.show = "Desposit";
    trans.push_back(tran);
    noti.toid = "0";
    noti.balanc = amount;
    noti.number = 2;
    note.push_back(noti);
    savetrans(users, trans);
    savenote(users, note);
    cin.ignore();
    cin.get();
}
void sleeps(int j)
{
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

int TransferNumber(vector<Transfer> &trans)
{
    srand(time(0));
    int num = rand() % 10000 + 1000;
    for (int i = 0; i < trans.size(); ++i)
    {
        if (trans[i].transferNumber == num)
        {
            return (num + 1);
        }
    }
    return num;
}

void transf(vector<User> &users, vector<Transfer> &trans, int numberuser)
{
    Transfer tran;
    setcolor(3);
    tran.from_user = numberuser;
    int index = findUserIndex(users, tran.from_user);
    User &user = users[index];
    if (user.userType == "Customer")
    {
        cout << "\n Your id user : " << tran.from_user << "\n Your balans : " << user.balanc << "\n"
             << endl;
    }
    else
    {
        cout << "Enter your ID number: ";
        tran.from_user = chose3();
    }

    index = findUserIndex(users, tran.from_user);
    cout << "Enter recipient ID number: ";
    tran.to_user = chose3();
    int indexx = findUserIndex(users, tran.to_user);

    if (numberuser == tran.to_user)
    {
        setcolor(4);
        cerr << " The Recipient ID Same Your ID ";
        return;
    }
    if ((index != -1 && indexx != -1))
    {
        setcolor(3);
        cout << "Enter transfer amount: $";
        cin >> tran.amount;

        if (user.balanc >= tran.amount)
        {
            tran.transferNumber = TransferNumber(trans);
            tran.received = false;
            user.balanc -= tran.amount;
            tran.get_time = gettime();
            tran.show = "Transfer";
            trans.push_back(tran);
            savetrans(users, trans);
            setcolor(2);
            cout << "Transfer successful ! Transfer Number: [ " << tran.transferNumber << " ]\n";
        }
        else
        {
            setcolor(4);
            cerr << "\n\t\t\tInsufficient balance!\n";
            return;
        }
    }
    else
    {
        setcolor(4);
        cerr << "\n\t\t\tInvalid account(s)!\n";
        return;
    }
    cin.ignore();
    cin.get();
}

int findtransIndex(const vector<Transfer> &trans, const double &number)
{
    for (int i = 0; i < trans.size(); ++i)
    {
        if (trans[i].transferNumber == number)
        {
            return i;
        }
    }
    return -1;
}

void receiveTransfer(vector<User> &users, vector<Transfer> &trans, int numberuser)
{
    int numbertransfer, id;
    setcolor(3);
    cout << "Enter transfer number to receive: ";
    cin >> numbertransfer;
    int index = findtransIndex(trans, numbertransfer);
    Transfer &tr = trans[index];
    if (index == -1)
    {
        setcolor(4);
        cerr << " \n\t\t\tNot found transfer number " << endl;
        return;
    }
    if (index != -1)
    {
        setcolor(3);
        int from_user = numberuser;
        int index = findUserIndex(users, from_user);
        User &user = users[index];
        if (user.userType == "Customer")
        {
            id = numberuser;
        }
        else
        {
            cout << "Enter your ID user " << endl;
            id = chose3();
        }
        if (id == tr.to_user && tr.received == false)
        {
            int indexx = findUserIndex(users, id);
            User &user = users[indexx];
            user.balanc += tr.amount;
            tr.received = true;
        }
        else
        {
            setcolor(4);
            cerr << " Your ID is error or number transfer is received" << endl;
            return;
        }
        setcolor(2);
        cout << " Your Transfer received , successful " << endl;
        savetrans(users, trans);
    }
    cin.ignore();
 cin.get();
}

void checkadmin(vector<User> &users)
{
    cout << "\n\n\n\n\n\t";
    string x = " WELLCOM TO OUR BANk SYSTEM ";
    setcolor(9);
    for (int i = 0; i < 28; i++)
    {
        setcolor(8);
        if (i >= 11 && i <= 20)
            setcolor(14);
        sleeps(10000000);

        if (i)
            cout << x[i] << " ";

        if (i == 27)
            sleeps(90000000);
    }
    cout << endl;
    bool managerexit = false;
    for (const auto &user : users)
    {
        if (user.userType == "Admin")
        {
            managerexit = true;
            break;
        }
    }
    if (!managerexit)
    {
        setcolor(4);
        cerr << "\n\t\t\tNo admin found. Adding admin...\n";
        addUser(users, "Admin");
    }
}
void showadmin(vector<User> &users, vector<Transfer> &trans, int &numberr, int &neu, int numberuser, string usertype, vector<Notice> &note)
{
    int indexs = findUserIndex(users, numberuser);
    int num;
    User &use = users[indexs];
    system("cls");
    setcolor(2);
    cout << endl;
    cout << "\t\t * * * * * * * * * * * * * * * * * * * " << endl;
    cout << "\t\t *  Login successful! Welcome, * " << endl;
    cout << "\t\t * * * * * * * * * * * * * * * * * * * " << endl;
    cout << endl;
    int choice;
    while (true)
    {
        if (usertype == "Admin")
        {
            system("cls");
            setcolor(2);
            printf("\nAdmin Menu:");
            cout << endl;
            cout << "1) Add an account\n2) View user accounts\n3) Edit user accounts\n4) Delete User\n5) Desposit beween user accounts\n6) Deposit to user accounts\n7) Send transfers  \n8) Receive Transfer\n9) View the transfers\n10) Delete transfer\n11) Search transfer\n12) Logout\n";
            cout << "\t\t\t";
        }

        else if (usertype == "Employee")
        {
            system("cls");
            setcolor(2);
            printf("\nEmployee Menu:");
            cout << endl;
            cout << "1) Add customer\n2) Display customer\n3) Desposit beween customer accounts\n4) Deposit to customer account\n5) Send transfers \n6) receive transfers\n7) Display transfers & Deposit\n8) Delete transfer\n9) Edit user accounts\n10) Notifications\n11) Search transfer\n12) Logout\n";
            cout << "\t\t\t";
        }

        else if (usertype == "Customer")
        {
            system("cls");
            setcolor(2);
            printf("\nCustomer Menu:");
            cout << endl;
            cout << "1) Deposit to another account\n2) Deposit to my account\n3) Transfer to another account \n4) Receive transfer\n5) Account information\n6) Notifications "
                 << "6\n7) Logout\n";
            cout << "\t\t\t";
        }
        choice = chose();
        if (choice == 1)
        {
            if (usertype == "Admin")
            {
                try
                {
                    addUser(users, "Employee");
                }
                catch (const char *s)
                {
                    setcolor(4);
                    cout << s << endl;
                }
            }
            else if (usertype == "Employee")
            {
                try
                {
                    addUser(users, "Customer");
                }
                catch (const char *s)
                {
                    setcolor(4);
                    cout << s << endl;
                }
            }
            else if (usertype == "Customer")
            {
                depositmoney(users, trans, note, numberuser);
            }
        }

        else if (choice == 2)
        {
            if (usertype == "Admin")
            {
                displayUsers(users, "Admin");
            }
            else if (usertype == "Employee")
            {
                displayUsers(users, "Employee");
            }

            else if (usertype == "Customer")
            {
                deposit(users, trans, note, numberuser);
            }
        }
        else if (choice == 3)
        {
            if (usertype == "Admin")
            {
                editUser(users);
            }

            else if (usertype == "Employee")
            {
                depositmoney(users, trans, note, numberuser);
            }

            else if (usertype == "Customer")
            {
                transf(users, trans, numberuser);
            }
        }
        else if (choice == 4)
        {
            if (usertype == "Admin")
            {
                deleteUser(users);
            }

            else if (usertype == "Employee")
            {
                deposit(users, trans, note, numberuser);
            }

            else if (usertype == "Customer")
            {
                receiveTransfer(users, trans, numberuser);
            }
        }
        else if (choice == 5)
        {
            /*
                cout<<" Enter from id "<<endl;
                numberuser=chose3();
             ;*/
            if (usertype == "Admin")
            {
                depositmoney(users, trans, note, numberuser);
            }

            else if (usertype == "Employee")
            {
                transf(users, trans, numberuser);
            }

            else if (usertype == "Customer")
            {
                datelise(users, trans, numberuser);
            }
        }

        else if (choice == 6)
        {
            if (usertype == "Admin")
            {
                deposit(users, trans, note, numberuser);
            }

            else if (usertype == "Employee")
            {
                receiveTransfer(users, trans, numberuser);
            }
            else if (usertype == "Customer")
            {
                displaynote(note, use.username);
            }
        }

        else if (choice == 7)
        {
            if (usertype == "Admin")
            {
                transf(users, trans, numberuser);
            }

            else if (usertype == "Employee")
            {
                displaytransfer(trans);
            }
            else if (usertype == "Customer")
            {
                cout << "1) Exite \n2) close system \n";
                short cho = chose();
                if (cho == 1)
                    break;
                if (cho == 2)
                {
                    numberr = 3;
                    neu = 2;
                    break;
                }
            }
        }
        else if (choice == 8)
        {
            if (usertype == "Admin")
            {
                receiveTransfer(users, trans, numberuser);
            }
            else if (usertype == "Employee")
            {
                deletetrans(trans);
            }
            else if (usertype == "Customer")
            {
                setcolor(2);
                cerr << "Your Choice Incorrect !!!" << endl;
            }
        }
        else if (choice == 9)
        {
            if (usertype == "Admin")
            {
                displaytransfer(trans);
            }
            else if (usertype == "Employee")
            {
                editUser(users);
            }
            else
            {
                setcolor(2);
                cerr << "Your Choice Incorrect !!!" << endl;
            }
        }

        else if (choice == 10)
        {
            if (usertype == "Admin")
            {
                deletetrans(trans);
            }
            else if (usertype == "Employee")
            {
                displaynote(note, use.username);
            }
            else if (usertype == "Customer")
            {
                setcolor(4);
                cerr << "\nYour Choice Incorrect !!!" << endl;
            }
        }
        else if ((choice == 11 && (usertype == "Admin" || usertype == "Employee")))
        {
            setcolor(3);
            cout << "\n Enter number transfer :\n";
            cin >> num;
            searchtrans(trans, num);
        }
        else if (choice == 12 && (usertype == "Admin" || (choice == 12 && usertype == "Employee")))
        {
            cout << "1) Exite \n2) close system \n";
            short cho = chose();
            if (cho == 1)
                break;
            if (cho == 2)
            {
                numberr = 3;
                neu = 2;
                break;
            }
        }
    }
}
void datelise(vector<User> &users, vector<Transfer> &trans, int numberuser)
{
    int index = findUserIndex(users, numberuser);
    User &datuser = users[index];
    setcolor(5);
    cout << left << "|" << setw(3) << "number"
         << "|" << setw(5) << " Username "
         << " |" << setw(5) << " Password "
         << "  |" << setw(5) << "Phonenumber "
         << "|" << setw(10) << "  Usertype "
         << " |" << setw(4) << " sex "
         << " |" << setw(3) << "active"
         << "|" << endl;
    cout << " ----------------------------------------------------------------------- " << endl;
    cout << left;
    setcolor(6);
    cout << "| " << setw(5);
    setcolor(15);
    cout << datuser.number;
    setcolor(6);
    cout << "| " << setw(7);
    setcolor(15);
    cout << setw(10) << datuser.username;
    setcolor(6);
    cout << "|  ";
    setcolor(15);
    cout << setw(10) << datuser.password;
    setcolor(6);
    cout << "|  ";
    setcolor(15);
    cout << setw(10) << datuser.phoneNumber;
    setcolor(6);
    cout << "|  ";
    setcolor(15);
    cout << setw(10) << datuser.userType;
    setcolor(6);
    cout << "| ";
    setcolor(15);
    cout << setw(5) << datuser.usertayp;
    setcolor(6);
    cout << "|  ";
    setcolor(15);
    cout << setw(3) << datuser.isActive;
    setcolor(6);
    cout << " |\n";
    cout << " ----------------------------------------------------------------------- " << endl;
    setcolor(5);
    cout << "\n";
    cout << left << " | " << setw(6) << "Code"
         << " | " << setw(7) << "Balanc"
         << " |" << endl;
    cout << " - - - - - - - - - - - - - - - " << endl;

    setcolor(6);
    cout << left << " | ";
    setcolor(15);
    cout << setw(6) << datuser.puk;
    setcolor(6);
    cout << " | ";
    setcolor(15);
    cout << setw(7) << datuser.balanc;
    setcolor(6);
    cout << " | " << endl;
    cout << "  - - - - - - - - - - - - - - " << endl;
    cin.ignore();
    cin.get();
    
}
short checkerror(int &numberr, int &neu)
{
    if (numberr == 3)
    {
        neu++;
        if (neu == 1)
        {
            setcolor(14);
            cerr << " three try agien enter correct password or id " << endl;
            numberr = 1;
        }
        if (neu == 2)
        {
            setcolor(14);
            cerr << " one try agien and will closes bank " << endl;
            numberr = 2;
        }
        if (neu == 3)
        {
            system("cls");
            setcolor(4);
            cout << "\n\n";
            cout << "\t\t  * * * * * * * * * * * * * * * * * * * * * *" << endl;
            cout << "\t\t  *  C L O S E D   S Y S T E M   B A N K   *" << endl;
            cout << "\t\t  * * * * * * * * * * * * * * * * * * * * * *" << endl;
            return -1;
        }
        cout << "\tPlease, Loeading  befor try agein ....\n";
        for (int d = 9; d >= 1; d--)
        {
            setcolor(2);
            cout << "\t\t\t\t\t" << d << "\r" << flush;
            sleeps(599999000);
        }
        system("cls");
    }
    return 0;
}
void searchtrans(vector<Transfer> &trans, int numbertrans)
{
    bool found = false;
    for (auto search : trans)
    {
        if (search.transferNumber == numbertrans)
        {
            cout << "\n";
            setcolor(135);
            cout << left;
            setcolor(5);
            cout << "|";
            setcolor(135);
            cout << setw(6) << " Number ";
            setcolor(5);
            cout << "|";
            setcolor(135);
            cout << setw(7) << " From ID ";
            setcolor(5);
            cout << "|";
            setcolor(135);
            cout << setw(5) << " To ID ";
            setcolor(5);
            cout << "|";
            setcolor(135);
            cout << setw(5) << " Amount ";
            setcolor(5);
            cout << "|";
            setcolor(135);
            cout << setw(6) << " Status ";
            setcolor(5);
            cout << "|";
            setcolor(135);
            cout << setw(10) << "   Data ";
            setcolor(5);
            cout << "| ";
            setcolor(135);
            cout << " Time  ";
            setcolor(5);
            cout << "|" << setw(6);
            setcolor(135);
            cout << " state ";
            setcolor(5);
            cout << "|" << endl;
            setcolor(5);
            cout << " ------------------------------------------------------------------------- " << endl;
            cout << left;
            break;
        }
    }

    for (auto search : trans)
    {
        if (search.transferNumber == numbertrans)
        {
            setcolor(5);
            cout << "|";
            if (search.transferNumber == 0)
            {
                setcolor(9);
                cout << setw(8) << "Null";
            }
            else
            {
                setcolor(8);
                cout << setw(8) << search.transferNumber;
            }
            setcolor(5);
            cout << "|";
            setcolor(8);
            if (search.from_user == 0)
            {
                setcolor(9);
                cout << setw(8) << "Null";
            }
            else
            {
                setcolor(8);
                cout << setw(8) << search.from_user;
            }
            setcolor(5);
            cout << "|";
            setcolor(8);
            cout << setw(7) << search.to_user;
            setcolor(5);
            cout << "|";
            setcolor(8);
            cout << setw(8) << search.amount;
            setcolor(5);
            cout << "|";
            setcolor(8);
            cout << setw(6);
            if (search.received == 1)
            {
                setcolor(2);
                cout << "Received";
            }
            else
            {
                setcolor(71);
                cout << "Pending";
            }
            setcolor(5);
            cout << "|" << setw(10);
            setcolor(15);
            cout << search.get_time;
            setcolor(5);
            cout << "|" << setw(6);
            setcolor(15);
            cout << search.show;
            setcolor(5);
            cout << "|" << endl;
            cout << " ------------------------------------------------------------------------- " << endl;
            found = true;
        }
    }

    if (found == false)
    {
        setcolor(4);
        cerr << "\n  Not found number transfer" << endl;
    }
    cin.ignore();
    cin.clear();
    cin.get();
}