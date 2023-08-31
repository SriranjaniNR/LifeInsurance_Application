#include<iostream>
#include<unordered_map>
using namespace std;
class Premium_Calculation
{//DEFINE A RATE TABLE BASED ON AGE
    //Grp 1=20-30
    //Grp 2=30-40
    //Grp 3=40-50
    //Grp 4=50-60
    // Fixed term period 40,30,20,10
    //for smoker 
public:
    unordered_map<int, double>rates;
    double premium;
    Premium_Calculation()
    {
        rates[1] = .0015;
        rates[2] = .0030;
        rates[3] = .0045;
        rates[4] = .0060;
        premium = 0.0;
    }
    int get_group(int age)
    {
        if (age >=20 && age < 30)
            return 1;
        else if (age >=30 && age < 40)
            return 2;
        else if (age >=40 && age < 50)
            return 3;
        else if (age >=50 && age <=60)
            return 4;
        else 
            return 0;
}
void calculation(double rate,double sum_assured)
{
    
        premium = rate * sum_assured;
    
}
double base_calculation(double sum_assured,int age,string ts)// Only with life cover
{
    int g = get_group(age);
    transform(ts.begin(), ts.end(), ts.begin(), ::toupper);
    double rate;
        if ("yes" == ts)
            rate = rates[g] + 0.015;
        else
            rate = rates[g];
    //cout << sum_assured << endl;
    calculation(rate, sum_assured);
    return premium;
}
double adb_cal(double cover)
{
    int k = (cover - 25000) / 50000;
    int x = (cover - 25000) - (50000 * k);
    double f = 120.0 / 50000.0;
    float t = x * f;
    double adb = 120 + (k * 120) + t;
    return adb;
}
double cc_cal(double cover)
{
    int k = (cover - 200000) / 300000;
    int x = (cover - 200000) - (300000 * k);
    double f = 3840.0 / 300000.0;
    float t = x * f;
    double cc = 960 + (k * 4800) + t;
    return cc;
}
double final_calculation(float sum_assured,int age, unordered_map<string,int>a,string ts)// Calculation with addons,adjustments and tax;
{
    transform(ts.begin(), ts.end(), ts.begin(), ::toupper);
    double adb = 0,cc=0;
    if (a["ADB"] > 0)
         adb = adb_cal(a["ADB"]);
    if (a["CC"] > 0)
        cc = cc_cal(a["CC"]);
    int g = get_group(age);
    double rate;
    if ("yes" == ts)
        rate = rates[g] + 0.015;
    else
        rate = rates[g];
    calculation(rate, sum_assured);
    premium -= (premium * .03);
    premium = adb + cc +premium;
    return premium;
    
}
};