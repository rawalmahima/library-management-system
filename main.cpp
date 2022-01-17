#include <bits/stdc++.h>
using namespace std;
vector<string> v_username;                                          //vector for storing usernames from Textfile DataBase
vector<string> v_password;                                          //vector for storing passwords from Textfile DB
vector<string> v_names;                                             //vector for storing names from Textfile DB
vector<pair<string, string>> v_books;                               //vector for storing book names and book IDs
vector<vector<pair<string, string>>> books(23);                     //vector for storing book names and book IDs for 23 students
int result = -1;                                                    //global int variable for student verification
bool flaggy = false;                                                //global bool variable for book ID check
void vectorToText()                                                 //function to store new book names & IDs from the vector to user's textfile DB
{
    for (int i = 0; i < 23; i++)
    {
        string s = v_username[i] + ".txt";
        string x = "";
        for (int j = 0; j < books[i].size(); j++)
        {
            x += books[i][j].first + "-" + books[i][j].second;
            if (j < books[i].size() - 1)
            {
                x += ",";
            }
        }
        ofstream out(s);
        out << x;
    }
}
void vectorToBookText()                                                 //function to store new book names & IDs from the vector to all books textfile DB
{
    string s = "";
    for (int i = 0; i < v_books.size(); i++)
    {
        s += v_books[i].first + "-" + v_books[i].second;
        if (i < v_books.size() - 1)
        {
            s += ",";
        }
    }
    ofstream out("books.txt");
    out << s;
}
void delete_book()                                                      //function to remove (return) book from the user's textfile DB
{
    string id;
    cout << "\nEnter Book ID of the book to be returned" << endl;
    cin >> id;
    bool flag = false;
    for (int i = 0; i < (int)books[result].size(); i++)
    {
        if (books[result][i].first == id)
        {
            books[result].erase(books[result].begin() + i);
            flag = true;
            cout << "\nYour Book has been Returned" << endl;
            cout << "\n****************************************************" << endl;
            break;
        }
    }
    if (flag == false)
        {
            cout << "\nNo such Book ID found under your record" << endl;
            cout << "\n****************************************************" << endl;
        }
}

void addBooksToVector()                              //function to store the book names & IDs from the user's textfile DB to the vectors
{
    for (int k = 0; k < 23; k++)
    {
        string s = v_username[k] + ".txt";
        string s_book;
        ifstream inu(s);
        getline(inu, s_book);
        for (int i = 0; i < s_book.length(); i++)
        {
            if (s_book[i] == ',')
            {
                string x = s_book.substr(0, i);
                for (int j = 0; j < x.size(); j++)
                {
                    if (x[j] == '-')
                    {
                        string a, b;
                        a = x.substr(0, j);
                        b = x.substr(j + 1);
                        books[k].push_back({a, b});
                        break;
                    }
                }
                s_book = s_book.substr(i + 1);
                i = 0;
            }
        }
        string x = s_book;
        for (int j = 0; j < x.size(); j++)
        {
            if (x[j] == '-')
            {
                string a, b;
                a = x.substr(0, j);
                b = x.substr(j + 1);
                books[k].push_back({a, b});
                break;
            }
        }
    }
}
void texttonames()                              //function to store the names of users from the name textfile DB to the vectors
{
    string s_username;
    ifstream inu("names.txt");
    getline(inu, s_username);
    for (int i = 0; i < s_username.length(); i++)
    {
        if (s_username[i] == ',')
        {
            v_names.push_back(s_username.substr(0, i));
            s_username = s_username.substr(i + 1);
            i = 0;
        }
    }
    v_names.push_back(s_username);
}

void texttobooks()                              //function to store the book names from all the books textfile DB to the vectors
{
    string s_username;
    ifstream inu("books.txt");
    getline(inu, s_username);
    for (int i = 0; i < s_username.length(); i++)
    {
        if (s_username[i] == ',')
        {
            string x = s_username.substr(0, i);
            for (int j = 0; j < x.size(); j++)
            {
                if (x[j] == '-')
                {
                    string a, b;
                    a = x.substr(0, j);
                    b = x.substr(j + 1);
                    v_books.push_back({a, b});
                    break;
                }
            }
            s_username = s_username.substr(i + 1);
            i = 0;
        }
    }
    string x = s_username;
    for (int j = 0; j < x.size(); j++)
    {
        if (x[j] == '-')
        {
            string a, b;
            a = x.substr(0, j);
            b = x.substr(j + 1);
            v_books.push_back({a, b});
            break;
        }
    }
}

void texttouser()                              //function to store the usernames from the usernames textfile DB to the vectors
{
    string s_username;
    ifstream inu("username.txt");
    getline(inu, s_username);
    for (int i = 0; i < s_username.length(); i++)
    {
        if (s_username[i] == ',')
        {
            v_username.push_back(s_username.substr(0, i));
            s_username = s_username.substr(i + 1);
            i = 0;
        }
    }
    v_username.push_back(s_username);
}
void texttopass()                              //function to store the passwords of users from the password textfile DB to the vectors
{
    string s_password;
    ifstream inp("password.txt");
    getline(inp, s_password);
    for (int i = 0; i < s_password.length(); i++)
    {
        if (s_password[i] == ',')
        {
            v_password.push_back(s_password.substr(0, i));
            s_password = s_password.substr(i + 1);
            i = 0;
        }
    }
    v_password.push_back(s_password);
}

class TheLibrary
{
private:
    int verify(string user_name, string pass)
    {
        for (int i = 0; i < v_username.size(); i++)
        {

            if (v_username[i] == user_name && v_password[i] == pass)
            {
                return i;
            }
        }
        return -1;
    }

public:
    void get_id_and_password()
    {
        while (result < 0)
        {
            string username, password;
            cout << "Enter username" << endl;
            cin >> username;
            // getline(cin, username);
            cout << "Enter your password" << endl;
            cin >> password;
            // getline(cin, password);
            result = verify(username, password);
        }
    }
    void add_book()
    {
        cin.ignore();
        string name, id;
        cout << "Enter the name of new book issued: ";
        getline(cin, name);
        cout << "Enter the Book ID: ";
        cin >> id;
        books[result].push_back(make_pair(id, name));
    }
    bool librarianverification()
    {
        string username = "", password = "";
        while (username != "admin" && password != "admin")
        {
            cout << "------------------------------" << endl;
            cout << "Enter username" << endl;
            cin >> username;
            cout << "Enter your password" << endl;
            cin >> password;
            cout << "------------------------------" << endl;
        }
        return true;
    }
    void get_student_details()
    {
        cout << "\n*******************************" << endl;
        cout << "\nStudent ID:" << v_username[result] << endl;
        cout << "Name of Student:" << v_names[result] << endl;
        cout << "List of books issued by the student" << endl;
        cout << "------------------------------" << endl;
        cout << "|Book ID "
             << "-"
             << " Book Name|" << endl;
        for (auto p : books[result])
        {
            cout << "|" << p.first << " - " << p.second << "|" << endl;
        }
        cout << "------------------------------" << endl;
        cout << "\n*******************************" << endl;
    }
    int studentwindow()
    {
        cout << "\n***************** Student's Window *****************" << endl;
        cout << "\nWhat would you like to do?" << endl;
        cout << "1. Issue Book" << endl;
        cout << "2. Return Book" << endl;
        cout << "3. Display my issued books" << endl;
        cout << "4. Return to the Main Menu" << endl;
        cout << "0. Exit" << endl;
        cout << "\n****************************************************" << endl;
        int opt;
        cin >> opt;
        return opt;
    }

    // };

    int greeting()
    {
        cout << "\n******************************!!Welcome to The Library!!******************************" << endl;
        cout << "\n####################################!!Main Menu!!#####################################" << endl;
        cout << "\nSelect Options" << endl;
        cout << "1. Login as Student" << endl;
        cout << "2. Login as Librarian" << endl;
        cout << "0. Exit" << endl;
        cout << "\n######################################################################################" << endl;
        int key;
        cin >> key;
        return key;
    }

    // teacher
    int librarianwindow()
    {
        cout << "\n################ Librarian's Window ################" << endl;
        cout << "\nWhat would you like to do?" << endl;
        cout << "1. Add new book" << endl;
        cout << "2. Remove book" << endl;
        cout << "3. Display all books" << endl;
        cout << "4. Display list of books issued by students" << endl;
        cout << "5. Return to Main Menu" << endl;
        cout << "0. Exit" << endl;
        cout << "\n####################################################" << endl;
        int opt;
        cin >> opt;
        return opt;
    }

    void display_student_books()
    {
        cout << "------------------------------" << endl;
        cout << "Enter username of student: ";
        string usx;
        cin >> usx;
        int ind = -1;
        for (int i = 0; i < v_username.size(); i++)
        {
            if (v_username[i] == usx)
            {
                ind = i;
                break;
            }
        }
        if (ind == -1)
        {
            cout << "No such student username found" << endl;
            ;
        }
        else
        {
            result = ind;
            get_student_details();
        }
        cout << "------------------------------" << endl;
    }

    void display_library_books()
    {
        cout << "------------------------------" << endl;
        for (int i = 0; i < v_books.size(); i++)
        {
            cout <<"|" << v_books[i].first  << " - " << v_books[i].second<< "|" << endl;
            

        }
        int ind = -1;
        for (int i = 0; i < v_username.size(); i++)
        {
            
          for (auto p : books[i])
        {
            cout << "|" << p.first << " - " << p.second << "|" << endl;
        }
        }
        cout << "------------------------------" << endl;
    }

    void add_book_teacher()
    {
        string name, id;
        cin.ignore();
        cout << "------------------------------" << endl;
        cout << "Enter the name of book" << endl;
        getline(cin, name);
        cout << "Enter Book ID" << endl;
        cin >> id;
        v_books.push_back(make_pair(id, name));
        cout << "------------------------------" << endl;
    }

    bool remove_book_teacher()
    {
        string name, id;
        cin.ignore();
        cout << "\n*******************************" << endl;
        cout << "Enter the name of book" << endl;
        getline(cin, name);
        cout << "Enter Book ID" << endl;
        cin >> id;
        for (int i = 0; i < (int)v_books.size(); i++)
        {
            if (v_books[i].first == id)
            {
                v_books.erase(v_books.begin() + i);
                return true;
            }
        }
        return false;
    }
};

int main()
{
    texttonames();
    texttobooks();
    texttopass();
    texttouser();
    addBooksToVector();
    TheLibrary demo;
    int key = demo.greeting();
    while (key == 1 || key == 2)
    {
        if (key == 1)
        {
            demo.get_id_and_password();
            int opt = demo.studentwindow();
            if (opt == 0)
            {
                break;
            }
            else if (opt == 1)
            {
                demo.add_book();
                cout << "\nYour Book has been Issued" << endl;
                cout << "\n*******************************" << endl;
            }
            else if (opt == 2)
            {
                delete_book();
                // cout << "\nYour Book has been Returned" << endl;
                // cout << "\n*******************************" << endl;
            }

            else if (opt == 3)
            {
                demo.get_student_details();
            }
            else if (opt == 4)
            {
                key = demo.greeting();
                if (key == 1)
                {
                    result = -1;
                }
                else if (key == 2)
                {
                    flaggy = false;
                }
                else if (key == 0)
                    break;
            }
            else
            {
                cout << "\n Wrong choice, Try Again!" << endl;
            }
        }

        if (key == 2)
        {
            if (!flaggy)
            {
                flaggy = demo.librarianverification();
            }
            int opt = demo.librarianwindow();
            if (opt == 0)
            {
                break;
            }
            else if (opt == 1)
            {
                demo.add_book_teacher();
                cout << "\nThe Book has been added" << endl;
                cout << "\n*******************************" << endl;
            }
            else if (opt == 2)
            {
                if(demo.remove_book_teacher())
                {
                cout << "\nThe Book has been removed" << endl;
                cout << "\n*******************************" << endl;
                }
                else
                {
                 cout << "\nWrong Book details" << endl;
                cout << "\n*******************************" << endl;

                }
            }

            else if (opt == 3)
            {
                demo.display_library_books();
            }
            else if (opt == 4)
            {
                demo.display_student_books();
            }
            else if (opt == 5)
            {
                key = demo.greeting();
                if (key == 1)
                {
                    result = -1;
                }
                else if (key == 2)
                {
                    flaggy = false;
                }
                else if (key == 0)
                    break;
            }
            else
            {
                cout << "\n Wrong choice, Try Again!" << endl;
            }
        }
    }
    cout << "\n******************************************"<<endl;
    cout << endl<< "Good Bye!!\n" << endl;
    cout << "****************** (^__^) ****************\n" << endl;
    vectorToText();
    vectorToBookText();
    return 0;
}
