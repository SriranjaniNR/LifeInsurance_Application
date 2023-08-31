#include<iostream>
#include"Policy_Dashboard.h"
using namespace std;
//Base class of Dashboard   Sub class of Policy dashboard
class Client_Dashboard :public Policy_Dashboard
{
public:
	int c;
	char e;
	string cid;
	void print_details(string username)// To see Client details and choose
	{
		do {
			system("cls");
			client_db(1,username);
			cout << "**************************************************************************************" << endl;
			cout << "1.Choose to create a policy\n2.Choose to Cancel policy\n3.Choose to see the policies" << endl;
			cout << "4.Policy_Menu" << endl << "5.Client_Menu" << endl << "6.To exit" << endl;
			cin >> c;
			cout << "**************************************************************************************" << endl;
			switch (c)
			{
			case 1:
				generate_cid(username);
				create_policy(cid);
				client_db(0,username);
				break;
			case 2:
				cancel_policy();
				break;
			case 3:
				list_of_policies();
				break;
			case 4:
				policy_menu(cid);
				break;
			case 5:
				print_details(username);
			case 6:
				break;
			}
			if (s != 1&&c!=6) 
			{
				cout << "Do you want see the Client menu" << endl;
				cin >> e;
			}
		} while (e == 'y' || e == 'Y');
	}
	void cancel_policy()//Option to Cancel Policy
	{
		string pid;
		cout << "Enter the policy_id" << endl;
		cin >> pid;
		connect_db(2, pid);
		//client_db(2, " ");
		cout << "Policy_Cancelled" << endl;
	}
	void list_of_policies()//To view the List of Policy
	{
		
		connect_db(1,cid);
		
	}
	void refund()
	{
		//to initaite a refund request
	}
	void generate_cid(string username)
	{
		int k = rand() % 100;
		string str1 = to_string(k);
		cid = 'C' + username.substr(0, 2)+str1;
	}
	void client_db(int i=0,string u=" ")
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
		if (i == 0) {
			try {//To insert Client details
				pstmt = con->prepareStatement("INSERT INTO Client VALUES(?,?,?,?,?,?,?)");
				pstmt->setString(1, cid);
				pstmt->setString(2, fname);
				pstmt->setString(3, lname);
				pstmt->setString(4, email_id);
				pstmt->setInt(5, 0);
				pstmt->setString(6,"Paid");
				pstmt->setString(7, u);
				pstmt->execute();
				delete pstmt;
			}
			catch (sql::SQLException e)
			{
				cout << "Could not connect to server. Error message: " << e.what() << endl;
				system("pause");
				exit(1);
			}
		}
		else if (i == 1)
		{
			string query = "Select * from client where Username='" + u + "'";
			result = stmt->executeQuery(query);
			int numColumns = result->getMetaData()->getColumnCount();
			if (result->next()) {
				cid = result->getString(1);
				do {
					for (int i = 1; i <= numColumns; ++i)
					{
						if (result->getString(i) != "Policy_Nos")
						{
							cout << result->getMetaData()->getColumnName(i) << ": " << result->getString(i) << endl;
						}
					}
					cout << endl;
				} while (result->next());
			}
			else
			{
				cout << "Welcome " << u << endl;
			}
			delete stmt;
			delete result;
		}
		/*else if (i == 2)
		{
			string uquery2 = "UPDATE Client SET Policy_Nos = 0 where Client_ID = '" + cid + "'";
			int r2 = stmt->executeUpdate(uquery2);
		}*/
		
		
	}
};