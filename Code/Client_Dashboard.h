#include<iostream>
#include"Policy_Dashboard.h"
using namespace std;
class Client_Dashboard:public Policy_Dashboard
{
public:
int c;
void print_details(string username)// To see Client details and choose
{ system("cls");
cout<<"Name:"<<username<<endl;
cout<<"No.of policies issued: 0"<<endl;
cout<<"Account Balance: 0"<<endl;
cout<<"1.Choose to create a policy\n2.Choose to Cancel policy\n3.Choose to see the policies"<<endl;
cin>>c;
switch(c)
{
case 1:
policy_proposal();
break;
case 2:
cancel_policy();
break;
case 3:
list_of_policies();
break;
}
}
void policy_proposal()// Creation of policy
{
create_policy();
}
void cancel_policy()//Option to Cancel Policy
{
cout<<"CancelPolicy"<<endl;
}
void list_of_policies()//To view the List of Policy
{
cout<<"The List"<<endl;
}
void refund()
{
//to initaite a refund request
}

};