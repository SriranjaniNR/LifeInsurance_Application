#include<iostream>
using namespace std;
class Approver 
{
public :
    char r;
    int c;
    string uwid;
    string policy_id;
    string client_id;
    void generate(string username)
    {
        int k = rand() % 100;
        string str1 = to_string(k);
        uwid = 'C' + username.substr(0, 2) + str1;
    }
    void print(string username)
    {
        system("cls");
        generate(uwid);
        Approver_db(0, username);
        cout << "1.To see policy proposals\n 2.To exit"<< endl;
        cin >> c;
        switch (c)
        {
        
        case 1:
            Approver_db(1, " ");
            break;
        case 2:
            break;
        }
    }
    void Approver_db(int i=0,string username="")
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
            //To insert Approver Details
            if (i == 0)
            {
                try {
                    string q = "SELECT username from Approver where username='" +username+ "'";
                    result = stmt->executeQuery(q);
                    if (result->next()) 
                    {
                        cout << "Welcome:"<<username<< endl;
                    }
                    else
                    {
                    pstmt = con->prepareStatement("INSERT INTO Approver(UW_ID,username) VALUES(?,?)");
                    pstmt->setString(1, uwid);
                    pstmt->setString(2, username);
                    pstmt->execute();
                    }
                }
                catch (sql::SQLException e)
                {
                    cout << "Could not connect to server. Error message: " << e.what() << endl;
                    system("pause");
                    exit(1);
                }
            }
            //To see pending policies
            else if (i == 1)
            {
                string uquery = "", uquery2;
            try {
                string query = "Select * from Policy where Policy_Status='To be issued'";
                result = stmt->executeQuery(query);
                int numColumns = result->getMetaData()->getColumnCount();
                string col_name, val;
                while (result->next()) {
                    for (int i = 1; i <= numColumns; ++i) {
                        col_name = result->getMetaData()->getColumnName(i);
                        val = result->getString(i);
                        cout << col_name << ": " << val << endl;
                        if (col_name == "Policy_status")
                        {

                            cout << "Do you want to approve the the policy(A/R)?" << endl;
                            cin >> r;
                            policy_id = result->getString(1);
                            string cid = result->getString(20);
                            client_id = cid;
                            if (r == 'A' || r == 'a')
                            {

                                uquery = "UPDATE Policy SET Policy_status='Approved' where Policy_Id='" + policy_id + "'";
                                //uquery2 = "UPDATE Client SET Policy_Nos = 1 where Client_ID = '"+cid+"'";
                                //uquery2="UPDATE Approver SET Policy_ID='"+policy_id+"' Policy_status = 'Approved' where Policy_Id = '" + v + "'";
                                int r = stmt->executeUpdate(uquery);
                                break;

                            }
                            else if (r == 'R' || r == 'r')
                            {
                                uquery = "UPDATE Policy SET Policy_status='Rejected' where Policy_Id='" + policy_id + "'";
                                //uquery2 = "UPDATE Approver SET Policy_ID='" + v + "' Policy_status = 'Rejected' where Policy_Id = '" + v + "'";
                                int r = stmt->executeUpdate(uquery);
                                //int r2 = stmt->executeUpdate(uquery);
                                break;
                            }
                            else continue;

                        }
                    }
                    cout << endl;
                }
            }
            catch (sql::SQLException e)
            {
                cout << e.what() << endl;
                exit(1);
            }
            }
            
            
            
    }
    /*void give_pending()
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
       sql::Statement* chk;
       sql::PreparedStatement* pstmt;
       sql::ResultSet* result;
       con->setSchema("quickstartdb");
       stmt = con->createStatement();
       string uquery = "",uquery2="";


       try {
           string query = "Select * from Policy where Policy_Status='To be issued'";
           result = stmt->executeQuery(query);
           int numColumns = result->getMetaData()->getColumnCount();
           string col_name,val;
           while (result->next()) {
               for (int i = 1; i <= numColumns; ++i) {
                   col_name = result->getMetaData()->getColumnName(i);
                   val = result->getString(i);
                   cout <<col_name<< ": " <<val<< endl;
                   if (col_name == "Policy_status")
                   {

                       cout << "Do you want to approve the the policy(A/R)?"<< endl;
                       cin >> r;
                       string v = result->getString(1);
                       string cid= result->getString(20);
                       if (r == 'A' || r == 'a')
                       {

                           uquery = "UPDATE Policy SET Policy_status='Approved' where Policy_Id='" + v + "'";
                           //uquery2 = "UPDATE Client SET Policy_Nos = 1 where Client_ID = '"+cid+"'";
                           int r = stmt->executeUpdate(uquery);
                           break;

                       }
                       else if (r == 'R' || r == 'r')
                       {
                           uquery = "UPDATE Policy SET Policy_status='Rejected' where Policy_Id='" + v + "'";
                           int r = stmt->executeUpdate(uquery);
                           break;
                       }
                       else continue;

                   }
               }
               cout << endl;
           }
       }


       catch (sql::SQLException e)
       {
           cout << e.what() << endl;
           exit(1);
       }
   }*/
};
