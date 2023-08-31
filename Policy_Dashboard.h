#include<iostream>
#include"Premium_Calculation.h"
#include"Payment.h"
#include <ctime>  
#include<map>
#include <unordered_map>
using namespace std;
//Base class of Client Dashboard    Subclass of Premium Calculation
class Policy_Dashboard :public Premium_Calculation {
public:
    string fname;
    string lname;
    string dob;
    char p;
    string ts;
    string g;
    string mobile_number;
    string email_id;
    string address;
    double life_amount;
    double life_term;
    int tenure;
    string ed;
    double premium;
    double premium_paid;
    string ocp;
    unordered_map<string, int>a;
    string freq;
    string pm;
    string id;
    string cid;
    string product;
    string status;
    int s;
    Policy_Dashboard()
    {
        a["ADB"] = 0;
        a["CC"] = 0;
        id = "SN001";
        s = 0;
    }
    string generate_id()
    {
        id = fname.substr(0, 1) + lname.substr(0, 1) + dob.substr(0, 2);
    }
    int get_age()
    {
        time_t now;
        tm newtime;
        time(&now);
        localtime_s(&newtime, &now);
        int year = newtime.tm_year + 1900;
        int yyyy = stoi(dob.substr(6, 10));
        int age = year - yyyy;
        return age;
    }
    void policy_menu(string cd)
    {
        char t;
        do
        {
            system("cls");
            cout << "**************************************************************************************" << endl;
            connect_db(1, cd);
            int c;
            cout << "1.Choose to create a policy\n2.Addons for existing policys\n3.To adjust the polices\n4.To cancel\n 5.To go back Client Dashboard" << endl;
            cin >> c;
            cout << "**************************************************************************************" << endl;
            switch (c)
            {
            case 1:
                create_policy(cd);
                break;
            case 2:
                add_ons();
                premium = final_calculation(life_amount, get_age(), a, ts);
                connect_db(3, id);
                break;
            case 3:
                adjust_amount();
                premium = final_calculation(life_amount, get_age(), a, ts);
                connect_db(4, id);
                break;
            case 4:
                cancel_policy();
                break;
            case 5:
                s = 1;
                break;
            }
            if (c != 5) {
                cout << "Do you want to see Policy Menu(Y/N)" << endl;
                cin >> t;
            }
            else
            {
               
                break;
            }
        } while (t == 'Y' || t == 'y');
    }
    void create_policy(string cid)// to create a policy proposal
    {
        cout << "Enter First Name" << endl;
        cin >> fname;
        cout << "Enter Last Name" << endl;
        cin >> lname;
        cout << "Enter your Date of Birth(dd/mm/yyyy)" << endl;
        cin >> dob;
        cout << "Enter your gender Female(F),Male(M),Other(O)" << endl;
        cin >> g;
        cout << "Enter your emailid" << endl;
        cin >> email_id;
        cout << "Do you chew tobaco or smoke?" << endl;
        cin >> ts;
        cout << "Choose your product\n1.Term Life Product(T)\n2.Whole Life(W)\n3.Endownment Policy(E)\n";
        cin >> p;
        cout << "Enter the life_amount" << endl;
        cin >> life_amount;
        if (life_amount > 30000000)
        {
            cout << "Enter life amount less than 3 crore" << endl;
            cin >> life_amount;
        }
        cout << "Enter the life_term" << endl;
        cin >> life_term;
        if (life_term > 100)
        {
            cout << "Enter life term less than 100 " << endl;
            cin >> life_amount;
        }
        int age = get_age();
        premium = base_calculation(life_amount, age,ts);
        system("cls");
        details();
        char choice;
        cout << "Do you want to add addons(Y/N)" << endl;
        cin >> choice;
        if (choice == 'Y') add_ons();
        cout << "Do you want to change life amount(Y/N)" << endl;
        cin >> choice;
        if (choice == 'Y') adjust_amount();
        premium = final_calculation(life_amount, age, a,ts);
        additional_details();
        system("cls");
        details('Y');
        Payment_Form();
        connect_db(0,cid);


    }
    void details(char choice = 'N')// to view the policy details
    {

        if (choice == 'Y')
        {
            cout << "Name: " << fname << " " << lname << endl;
            cout << "Email: " << email_id << endl;
            cout << "Dob: " << dob << endl;
            cout << "Gender: " << g << endl;
            cout << "Address: " << address << endl;
            cout << "Education: " << ed << endl;
            cout << "Occupation: " << ocp << endl;
            cout << "Product: " << "Term Life" << endl;
            cout << "Life Amount: " << life_amount << endl;
            cout << "Life_Term: " << life_term << endl;
            cout << "Riders_Coverage\n1:ADB: " << a["ADB"] << "\n2:CC: " << a["CC"] << endl;
            cout << "Payment Tenure" << tenure << endl;
            cout << "Premium : " << premium << endl;
        }
        else if (choice == 'N')
        {
            cout << "Name: " << fname << " " << lname << endl;
            cout << "Email: " << email_id << endl;
            cout << "Dob: " << dob << endl;
            cout << "Gender: " << g << endl;
            cout << "Product: " << "Term Life" << endl;
            cout << "Life Amount: " << life_amount << endl;
            cout << "Life_Term: " << life_term << endl;
            cout << "Expected Premium : " << premium << endl;
        }
        else 
        {
            id = generate_id();
            cout << "Name: " << fname << " " << lname << endl;
            cout << "Email: " << email_id << endl;
            cout << "Product: " << "Term Life" << endl;
            cout << "Annual Premium : " << premium << endl;
            cout << "Payment Frequency: " << freq << endl;
            cout << "Payment Method: " << pm << endl;
            cout << "Payment Amount: " << premium_paid << endl;
            cout << "Paid Sucessfully" << endl;
            cout << "Policy Proposal Generated: " << id << endl;//the id should be changed after connecting to db 
            cout << "Policy Status: To be issued" << endl;
        }
        
    }
    void add_ons()// to add covers and riders to existing policy
    {
        //Call Final Premium Calculation ,if Life Policy  is altered ,if need to adjust life amount call
        double adb, cc;
        cout << "If you want ADB enter the rider amount>25k" << endl;
        cin >> adb;
        cout << "If you want Comprehensive care enter the coverage amount>2L>" << endl;
        cin >> cc;
        a["ADB"] = adb;
        a["CC"] = cc;
    }
    void adjust_amount()//To adjust the life cover;
    {
        cout << "Do you want to adjust life amount" << endl;
        cin >> life_amount;

    }
    void additional_details()
    {
        //payment tenure,educational qualifications and beneficiary if needed
        //Call Payment module
        cout << "Enter the Payment tenure" << endl;
        cin >> tenure;
        cout << "Enter your address" << endl;
        cin >> address;
        cout << "Enter your educational qualifications" << endl;
        cin >> ed;
        cout << "Enter your occupation" << endl;
        cin >> ocp;
    }
    void refund_process()
    {
        //refund process
    }
    void Payment_Form()//Choose Payment method and payment frequency
    {
        char f=' ';
        double fr = 1/12;
        cout << "**************************************" << endl;
        cout << "Enter the payment Frequency:\n1.Monthly(M)\n2.Quarterly(Q)\n3.Half-Yearly(H)\n4.Yearly(Y)" << endl;
        cin >> f;
        if (f == 'M') 
        {
            premium_paid = premium * fr;
            freq = "Monthly";
        }
        else if (f == 'Y') 
        {
            premium -= (premium * 0.15);
            premium_paid = premium;
            freq = "Yearly";
        }
        else if (f == 'Q') 
        {
            premium_paid = premium * 0.25;
            freq = "Quarterly";
        }
        else if(f=='H')
        {
            premium -= (premium * 0.1);
            premium_paid = premium * 0.5;
            freq = "Half-Yearly";
        }
        cout << "Enter the payment method(UPI,Cash,Debit,Credit)" << endl;
        cin >> pm;
        
        cout << "Payment Amount " << premium_paid << endl;
        system("cls");
        details('P');
    }
    void cancel_policy()
    {
        
        connect_db(2);
    }
    void connect_db(int i = 0, string name =" ")
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
        //To insert Policy Details
        if (i == 0) 
           {
            try {
                pstmt = con->prepareStatement("INSERT INTO Policy(Policy_Id,First_name,Last_name,Gender,DOB,Email,Address,Tobacco_Status,Education,Policy_Product,Life_amount,Life_cover,Annual_Premium,Payment_Method,Payment_tenure,Policy_Status,Payment_Frequency,ADB_rider,CC_rider,Client_ID) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
                pstmt->setString(1, id);
                pstmt->setString(2, fname);
                pstmt->setString(3, lname);
                pstmt->setString(4, g);
                pstmt->setString(5, dob);
                pstmt->setString(6, email_id);
                pstmt->setString(7, address);
                pstmt->setString(8, ts);
                pstmt->setString(9, ed);
                pstmt->setString(10, "Term_Product");
                pstmt->setDouble(11, life_amount);
                pstmt->setInt(12, life_term);
                pstmt->setDouble(13, premium);
                pstmt->setString(14, pm);
                pstmt->setInt(15, tenure);
                pstmt->setString(16, "To be issued");
                pstmt->setString(17, freq);
                pstmt->setDouble(18, a["ADB"]);
                pstmt->setDouble(19, a["CC"]);
                pstmt->setString(20, name);
                pstmt->execute();
            }
            catch (sql::SQLException e)
            {
                cout << "Could not connect to server. Error message: " << e.what() << endl;
                system("pause");
                exit(1);
            }
            }
        //To see the Policies
        else if (i == 1)
        {   
            stmt = con->createStatement();
            string query = "Select * from Policy where Client_ID='" + name + "'";
            result = stmt->executeQuery(query);
            int numColumns = result->getMetaData()->getColumnCount();
            if (result->next())
            {
                id = result->getString(1);
                fname= result->getString(2);
                lname= result->getString(3);
                email_id = result->getString(6);
                address= result->getString(7);
                product= result->getString(10);
                life_amount = result->getDouble(11);
                dob= result->getString(5);
                ts= result->getString(8);
                a["ADB"]= result->getDouble(18);
                a["CC"]= result->getDouble(19);
                premium = result->getDouble(13);
                pm = result->getString(14);
                status = result->getString(16);
                freq= result->getDouble(17);
                cid= result->getString(20);
                do {
                    for (int i = 1; i <= numColumns; ++i) {
                        cout << result->getMetaData()->getColumnName(i) << ": " << result->getString(i) << endl;
                    }
                    cout << "************************" << endl;
                } while (result->next());
            }
            else cout << "No Policies Created" << endl;
        }
        // To Cancel Policy
        else if (i == 2)
        {
            stmt = con->createStatement();
            string query="",uquery2="";
            if (name ==" ") {
                query = "UPDATE Policy SET Policy_Status='Cancelled' where Policy_Id='" + id + "'";
                //uquery2 = "UPDATE Client SET Policy_Nos = 0 where Client_ID = '" + cid + "'";
                //int r2 = stmt->executeUpdate(uquery2);
            }
            else
            {
               query = "UPDATE Policy SET Policy_Status='Cancelled' where Policy_Id='" + name + "'";
            }
            int r = stmt->executeUpdate(query);
            cout << "Policy Cancelled" << r << endl;

        }
        //To update ADB_RIDER
        else if (i == 3)
        {
            try {
                stmt = con->createStatement();
                pstmt = con->prepareStatement("UPDATE Policy SET ADB_rider= ?,CC_rider= ?,Premium=? WHERE Policy_ID= ?");
                pstmt->setDouble(1, a["ADB"]);
                pstmt->setDouble(2, a["CC"]);
                pstmt->setDouble(3, premium);
                pstmt->setString(4, id);
                pstmt->executeUpdate();
                cout << "Policy Updated" << endl;
            }
            catch (sql::SQLException e)
            {
                cout << e.what() << endl;
            }
        }
        //To update life amount
        else if (i == 4)
        {
            try {
                stmt = con->createStatement();
                pstmt = con->prepareStatement("UPDATE Policy SET Life_amount=?,Premium=? WHERE Policy_ID=?");
                pstmt->setDouble(1, life_amount);
                pstmt->setDouble(2, premium);
                pstmt->setString(3, id);
                pstmt->executeUpdate();
                cout << "Policy Updated" << endl;
            }
            catch(sql::SQLException e)
            {
                cout << e.what() << endl;
            }
        }
       
        
    }


};