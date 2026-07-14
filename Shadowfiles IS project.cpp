#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

//=========================
// Convert to Uppercase
//=========================
string toUpper(string str)
{
    for(int i=0;i<str.size();i++)
        str[i]=toupper(str[i]);

    return str;
}

//=========================
// Password Strength
//=========================
void checkStrength(string pass)
{
    int len=pass.length();

    if(len<=4)
        cout<<"Weak Password\n";
    else if(len<=6)
        cout<<"Medium Password\n";
    else
        cout<<"Strong Password\n";
}

//=========================
// Generate Key
//=========================
string generateKey(string text,string key)
{
    string newKey;
    int j=0;

    for(int i=0;i<text.size();i++)
    {
        if(isalpha(text[i]))
        {
            newKey.push_back(toupper(key[j%key.size()]));
            j++;
        }
        else
            newKey.push_back(text[i]);
    }

    return newKey;
}

//=========================
// Encrypt
//=========================
string encrypt(string text,string key)
{
    string cipher;

    for(int i=0;i<text.size();i++)
    {
        if(isalpha(text[i]))
        {
            char x = ((toupper(text[i]) - 'A') +
                      (toupper(key[i]) - 'A')) % 26 + 'A';

            cipher.push_back(x);
        }
        else
            cipher.push_back(text[i]);
    }

    return cipher;
}

//=========================
// Decrypt
//=========================
string decrypt(string cipher,string key)
{
    string text;

    for(int i=0;i<cipher.size();i++)
    {
        if(isalpha(cipher[i]))
        {
            char x = ((toupper(cipher[i]) - 'A') -
                      (toupper(key[i]) - 'A') + 26) % 26 + 'A';

            text.push_back(x);
        }
        else
            text.push_back(cipher[i]);
    }

    return text;
}

//=========================
// Add Record
//=========================
void addRecord()
{
    string title,status;
    string name;
    string crime;
    string reason;
    string evidence;
    string place;
    string notes;

    string key="SECURE";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout<<"\nCase Title: ";
    getline(cin,title);

    cout<<"Case Status: ";
    getline(cin,status);

    cout<<"Enter Criminal Name: ";
    getline(cin,name);

    cout<<"Enter Crime: ";
    getline(cin,crime);

    cout<<"Reason of Crime: ";
    getline(cin,reason);

    cout<<"Evidence Found: ";
    getline(cin,evidence);

    cout<<"Arrest Location: ";
    getline(cin,place);

    cout<<"Investigation Notes: ";
    getline(cin,notes);

    // Save EVERYTHING
    string data=
    toUpper(title)+"|"+
    toUpper(status)+"|"+
    toUpper(name)+"|"+
    toUpper(crime)+"|"+
    toUpper(reason)+"|"+
    toUpper(evidence)+"|"+
    toUpper(place)+"|"+
    toUpper(notes);

    string newKey=generateKey(data,key);

    string encrypted=encrypt(data,newKey);

    ofstream file("records.txt",ios::app);

    file<<encrypted<<endl;

    file.close();

    cout<<"\nData Encrypted & Saved Successfully!\n";
}//=========================
// View Records
//=========================
void viewRecords()
{
    string key = "SECURE";

    ifstream file("records.txt");

    if(!file)
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    string line;

    cout << "\n=========================================================\n";
    cout << "              SHADOW FILES SECURE DATABASE\n";
    cout << "            Crime Investigation Department\n";
    cout << "=========================================================\n";

    while(getline(file, line))
    {
        // Skip blank lines
        if(line.empty())
            continue;

        string newKey = generateKey(line, key);
        string d = decrypt(line, newKey);

        int p1 = d.find("|");
        int p2 = d.find("|", p1 + 1);
        int p3 = d.find("|", p2 + 1);
        int p4 = d.find("|", p3 + 1);
        int p5 = d.find("|", p4 + 1);
        int p6 = d.find("|", p5 + 1);
        int p7 = d.find("|", p6 + 1);

        if(p1 == string::npos || p2 == string::npos || p3 == string::npos ||
           p4 == string::npos || p5 == string::npos || p6 == string::npos ||
           p7 == string::npos)
        {
            continue;
        }

        string title    = d.substr(0, p1);
        string status   = d.substr(p1+1, p2-p1-1);
        string name     = d.substr(p2+1, p3-p2-1);
        string crime    = d.substr(p3+1, p4-p3-1);
        string reason   = d.substr(p4+1, p5-p4-1);
        string evidence = d.substr(p5+1, p6-p5-1);
        string place    = d.substr(p6+1, p7-p6-1);
        string notes    = d.substr(p7+1);

        cout << "\n=========================================================\n";
        cout << "Case Title  : " << title << endl;
        cout << "Case Status : " << status << endl;
        cout << "---------------------------------------------------------\n";
        cout << "Criminal Name : " << name << endl;
        cout << "Crime         : " << crime << endl;
        cout << "Reason        : " << reason << endl;
        cout << "Evidence      : " << evidence << endl;
        cout << "Arrest Place  : " << place << endl;
        cout << "Notes         : " << notes << endl;
        cout << "=========================================================\n";
    }

    file.close();
}
//=========================
// Search Record
//=========================
void searchRecord()
{
    string key = "SECURE";
    ifstream file("records.txt");

    if(!file)
    {
        cout<<"\nNo Records Found!\n";
        return;
    }

    string search;
    string line;
    bool found = false;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout<<"\nEnter Criminal Name OR Case Title: ";
    getline(cin,search);

    search = toUpper(search);

    while(getline(file,line))
    {
    	if(line.empty())
    continue;
        string newKey = generateKey(line,key);

        string d = decrypt(line,newKey);

        int p1=d.find("|");
        int p2=d.find("|",p1+1);
        int p3=d.find("|",p2+1);
        int p4=d.find("|",p3+1);
        int p5=d.find("|",p4+1);
        int p6=d.find("|",p5+1);
        int p7=d.find("|",p6+1);

        if(p7==string::npos)
            continue;

        string title=d.substr(0,p1);
        string status=d.substr(p1+1,p2-p1-1);
        string name=d.substr(p2+1,p3-p2-1);
        string crime=d.substr(p3+1,p4-p3-1);
        string reason=d.substr(p4+1,p5-p4-1);
        string evidence=d.substr(p5+1,p6-p5-1);
        string place=d.substr(p6+1,p7-p6-1);
        string notes=d.substr(p7+1);

        if(title.find(search)!=string::npos || name.find(search)!=string::npos)
        {
            found = true;

            cout<<"\n=========================================================\n";

            cout<<"Case Title  : "<<title<<endl;
            cout<<"Case Status : "<<status<<endl;

            cout<<"---------------------------------------------------------\n";

            cout<<"Criminal Name : "<<name<<endl;
            cout<<"Crime         : "<<crime<<endl;
            cout<<"Reason        : "<<reason<<endl;
            cout<<"Evidence      : "<<evidence<<endl;
            cout<<"Arrest Place  : "<<place<<endl;
            cout<<"Notes         : "<<notes<<endl;

            cout<<"=========================================================\n";
        }
    }

    if(!found)
    {
        cout<<"\nRecord Not Found!\n";
    }

    file.close();
}//=========================
// Main Function
//=========================
int main()
{
    // Header (ONLY ONCE)
    cout << "=========================================================\n";
    cout << "              SHADOW FILES SECURE DATABASE\n";
    cout << "            Crime Investigation Department\n";
    cout << "=========================================================\n\n";

    string password;
    int attempts = 0;

    while (attempts < 3)
    {
        cout << "Enter System Password: ";
        cin >> password;

        checkStrength(password);

        if (password == "SH@16ww&")
        {
            cout << "\nAccess Granted!\n";
            break;
        }
        else
        {
            cout << "\nWrong Password!\n";
            attempts++;
        }
    }

    if (attempts == 3)
    {
        cout << "\nSystem Locked! Too many wrong attempts.\n";
        return 0;
    }

    int choice;

    do
    {
        cout << "\n";
        cout << "=============== SHADOW FILES MENU ===============\n";
        cout << "1. Add Record\n";
        cout << "2. View Records\n";
        cout << "3. Search Record\n";
        cout << "4. Exit\n";
        cout << "=================================================\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addRecord();
                break;

            case 2:
                viewRecords();
                break;

            case 3:
                searchRecord();
                break;

            case 4:
                cout << "\nThank you for using Shadow Files.\n";
                cout << "System Closed Successfully.\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    }while(choice!=4);

    return 0;
}