// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include"Approver_Dashboard.h"
#include <iostream>
#include<vector>
#include <regex>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include"Client.h"
using namespace std;
class Dashboard:public Client_Dashboard,public Approver{
public:
    int t,u=0,p=0;
    string username;
    string password;
    vector<string>ids;
    string c;
    int connect_db(int i=10)
    {
        const string server = "localhost:3306";
        const string un = "root";
        const string pwd = "1234";
        sql::Driver* driver;
        sql::Connection* con;
        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, un, pwd);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* result;
        con->setSchema("quickstartdb");
        stmt = con->createStatement();
        //SIGN UP
        if (i == 0) {
            try {

                pstmt = con->prepareStatement("INSERT INTO users VALUES(?,?,?)");
                pstmt->setString(1, username);
                pstmt->setString(2, password);
                pstmt->setString(3, c);
                pstmt->execute();
                delete pstmt;
                delete stmt;
            }
            catch (sql::SQLException e)
            {
                cout << "Could not connect to server. Error message: " << e.what() << endl;
                system("pause");
                exit(1);
            }
            return 2;
        }//Sign up
        //SIGN IN
        else if (i == 1)
        {
            string query = "Select username from users where username='" + username + "' and Passwordhash='" + password + "'and Typeof='" + c + "'";
            result = stmt->executeQuery(query);
            if (result->next()) return 1;
            else return 0;


        }
        //To Generate Policies
         else if (i==2)
        {
            stmt = con->createStatement();
            string query = "Select * from Policy where Policy_ID='" + policy_id + "'";
            result = stmt->executeQuery(query);
            int numColumns = result->getMetaData()->getColumnCount();

            if (result->next())
            {
                string file = "Report "+client_id+"_" + policy_id + ".txt";
                ofstream myfile(file);
                //cout << status << endl;
                if (myfile.is_open())
                {
                    do {
                        for (int i = 1; i <= numColumns; ++i) {
                            string col = result->getMetaData()->getColumnName(i);
                            string val = result->getString(i);
                            myfile << col << ": " << val << "\n";
                        }
                        
                    } while (result->next());
                    cout << "Report Generated" << endl;
                    myfile.close();

                }
                else cout << "Unable to open file";

            }
                    
            return 0;
        }
    }
    void print()
    {
        cout << "********************************************" << endl;
        cout << "\t \t Life Insurance Application" << endl;
        cout << "********************************************" << endl;

    }
    void enter()//Signin
    {
        cout << "Enter username" << endl;
        cin >> username;
        cout << "Enter password" << endl;
        cin >> password;
        cout << "Enter are u underwriter(U) or Client(C)" << endl;
        cin >> c;
      
    }
    int validate_username()//Username Validation
    {
        vector<string>::iterator it;
        it = find(ids.begin(), ids.end(), username);
        regex str_expr("^[A-Za-z][a-zA-Z0-9_]{7,26}$");
        if (regex_match(username, str_expr))
        {
            if (it != ids.end())
                return 0;
            else
                return 1;
        }
        else
        {
            return 0;
        }

    }
    int validate_password()//Paasword Validation
    {
        regex str_expr("[A-Z][A-Za-z0-9!@#$%^&*_()]{7,29}$");
        if (regex_match(password, str_expr))
            return 1;
        else
            return 0;
    }
    void form()//Signup form
    {
        do {
            cout << "Enter name" << endl;
            cin >> username;
            cout << "Enter password" << endl;
            cin >> password;
            u = validate_username();
            p = validate_password();
            if (!p && !u)
                cout << "The username exists or username is not valid and The pasword should contain a special character,capital letter and its length should be more than 7" << endl;
            else if (!u)
                cout << "The username exists or username is not valid\n";
            else if (!p)
                cout << "The pasword should contain a special character,capital letter and its length should be more than 7";
        } while (!u || !p);
        cout << "Enter are u underwriter(U) or Client(C)" << endl;
        cin >> c;

    }
    void Users()
    {
        cout << "Enter 1->sign in" << "\n" << "Enter 0 ->Sign up\n"<<"Enter -1 to Exit" << endl;
        cin >> t;
        if (t == 1)
        {
            enter();
            
        }
        else if (t == 0)
        {
            form();
            
            
        }
        else if (t == -1)
        {
            exit(0);
        }

        int k = connect_db(t);
        
        if (k == 0)
        {
            cout << "Wrong username or password" << endl;
        }
        else if ((k == 1 || k == 2) && c == "C")
        {
            print_details(username);
            policy_report();
            
        }
        else if ((k == 1 || k == 2) && c == "U")
        {
            Approver::print(username);
            int g = connect_db(2);
        }
       
        //
    }
    void policy_report()
    {
        string file = "Report_"+cid+"_"+id + ".txt";
        ofstream myfile(file);
        //cout << status << endl;
        if (myfile.is_open())
        {
            myfile << "Client_ID:" <<cid<< "\n";
            myfile << "Policy_ID:" << id << "\n";
            myfile << "FirstName: " << fname << "\n";
            myfile << "LastName: " << lname << "\n";
            myfile << "Email: " << email_id << "\n";
            myfile << "DOB: " << dob << "\n";
            myfile << "Address: " << address << "\n";
            myfile << "Product: Term Product" << "\n";
            myfile << "Life_amount: " <<life_amount << "\n";
            myfile << "Tobacco_Status: " << ts<< "\n";
            myfile << "Annual_Premium: " <<premium<< "\n";
            //myfile << "Payment_Mode: " << freq << "\n";
            myfile << "Payment_Method: " << pm << "\n";
            myfile << "Policy_Status " << status << "\n";
            cout << "Report Generated" << endl;
            myfile.close();
            
        }
        else cout << "Unable to open file";
        

    }

};


int main()
{  
    Dashboard d;
    char c;
    do {

        system("cls");
        d.print();
        d.Users();
        cout << "Login again(Y/N)?" << endl;
        cin >> c;
    } while (c == 'Y' || c == 'y');

    cout << "Exit";
}
