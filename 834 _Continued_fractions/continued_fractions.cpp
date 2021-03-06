#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

class Fraction
{
    public:
    int num; // nominator - licznik
    int denom; //denomianator - mianownik
    //konktruktory
    Fraction();
    Fraction(int n, int d);
    //przeladowanie operatorow
    Fraction operator+(Fraction b);
    Fraction operator-(Fraction b);
    Fraction operator*(Fraction b);
    Fraction operator/(Fraction b);
    friend istream& operator>>(istream &input, Fraction &a);
    friend ostream& operator<<(ostream &output, Fraction a);
    //porownywanie
    friend bool operator<(Fraction a, Fraction b);
    friend bool operator>(Fraction a, Fraction b);
    friend bool operator<=(Fraction a, Fraction b);
    friend bool operator>=(Fraction a, Fraction b);
    friend bool operator==(Fraction a, Fraction b);
    //inne
    static int lowest_common_multiple(int a, int b);
    static void continued_fractions(Fraction fr);
    void reduce_fraction(); //skracanie ulamka

};

//konstruktor
Fraction::Fraction()
{
    num=0;
    denom=1;
}

Fraction::Fraction(int n, int d)
{
    this->num=n;
    this->denom=d;
    this->reduce_fraction();
}

//przeciazanie operatorow
Fraction Fraction::operator+(Fraction b)
{
    Fraction result;
    if(this->denom!=b.denom)
    {
        result.num=this->num*b.denom+b.num*this->denom;
        result.denom=this->denom*b.denom;
    }
    else
    {
        result.num=this->num+b.num;
        result.denom=this->denom;
    }
    result.reduce_fraction();
    return result;
}

Fraction Fraction::operator-(Fraction b)
{
    Fraction result;
    if(this->denom!=b.denom)
    {
        result.num=this->num*b.denom-b.num*this->denom;
        result.denom=this->denom*b.denom;
    }
    else
    {
        result.num=this->num-b.num;
        result.denom=this->denom;
    }
    result.reduce_fraction();
    return result;
}

Fraction Fraction::operator*(Fraction b)
{
    Fraction result(num*b.num,denom*b.denom);
    result.reduce_fraction();
    return result;
}

Fraction Fraction::operator/(Fraction b)
{
    Fraction result(num*b.denom,denom*b.num);
    result.reduce_fraction();
    return result;
}

//cin and cout
ostream& operator<<(ostream &output, Fraction a)
{
    output<<a.num;
    if(a.num!=0 && a.denom!=1)
    {
        output<<"|"<<a.denom;
    }
    return output;
}

istream& operator>>(istream &input, Fraction &a)
{
    string fraction_string;
    input>>fraction_string;

    int fraction_bar_position = fraction_string.find("|");

    if(fraction_bar_position!= string::npos)
    {
        string num_string, denom_string;
        num_string=fraction_string.substr(0,fraction_bar_position);
        denom_string=fraction_string.substr(fraction_bar_position+1, denom_string.size()-1);
        a.num=strtol(num_string.c_str(),NULL,10);
        a.denom=strtol(denom_string.c_str(),NULL,10);
    }
    else //no fraction bar found
    {
        a.num=strtol(fraction_string.c_str(),NULL,10);
        a.denom=1;
    }
    a.reduce_fraction();
    return input;
}
//porównywanie
bool operator<(Fraction a, Fraction b)
{
    Fraction fr1(a.num, a.denom);
    Fraction fr2(b.num, b.denom);
    int lcm = Fraction::lowest_common_multiple(fr1.denom,fr2.denom);
    //sprowadzenie do wspolnego mianownika:
    fr1.num=fr1.num*(lcm/fr1.denom);
    fr1.denom=fr1.denom*(lcm/fr1.denom);
    fr2.num=fr2.num*(lcm/fr2.denom);
    fr2.denom=fr2.denom*(lcm/fr2.denom);
    if(fr1.num<fr2.num) return true;
    else return false;
}

bool operator>(Fraction a, Fraction b)
{
    Fraction fr1(a.num, a.denom);
    Fraction fr2(b.num, b.denom);
    int lcm = Fraction::lowest_common_multiple(fr1.denom,fr2.denom);
    //sprowadzenie do wspolnego mianownika:
    fr1.num=fr1.num*(lcm/fr1.denom);
    fr1.denom=fr1.denom*(lcm/fr1.denom);
    fr2.num=fr2.num*(lcm/fr2.denom);
    fr2.denom=fr2.denom*(lcm/fr2.denom);
    if(fr1.num>fr2.num) return true;
    else return false;
}

bool operator<=(Fraction a, Fraction b)
{
    Fraction fr1(a.num, a.denom);
    Fraction fr2(b.num, b.denom);
    int lcm = Fraction::lowest_common_multiple(fr1.denom,fr2.denom);
    //sprowadzenie do wspolnego mianownika:
    fr1.num=fr1.num*(lcm/fr1.denom);
    fr1.denom=fr1.denom*(lcm/fr1.denom);
    fr2.num=fr2.num*(lcm/fr2.denom);
    fr2.denom=fr2.denom*(lcm/fr2.denom);
    if(fr1.num<fr2.num || a==b) return true;
    else return false;
}
bool operator>=(Fraction a, Fraction b)
{
    Fraction fr1(a.num, a.denom);
    Fraction fr2(b.num, b.denom);
    int lcm = Fraction::lowest_common_multiple(fr1.denom,fr2.denom);
    //sprowadzenie do wspolnego mianownika:
    fr1.num=fr1.num*(lcm/fr1.denom);
    fr1.denom=fr1.denom*(lcm/fr1.denom);
    fr2.num=fr2.num*(lcm/fr2.denom);
    fr2.denom=fr2.denom*(lcm/fr2.denom);
    if(fr1.num>fr2.num || a==b) return true;
    else return false;
}
bool operator==(Fraction a, Fraction b)
{
    if(a.num=b.num && a.denom == b.denom) return true;
    else return false;
}

//other methods
void Fraction::reduce_fraction()
{
    //gcd
    int n1=num;
    int n2=denom;
    while(n2 != 0)
    {
       int temp = n2;
       n2 = n1%n2;
       n1=temp;
    }
    //reducing
    num=num/n1;
    denom=denom/n1;
    if(num>0 && denom<0)
    {
        num = -num;
        denom = -denom;
    }
}

int Fraction::lowest_common_multiple(int a, int b)
{
    int result;
    result=(a>b)?a:b;
    do
    {
        if(result%a==0 && result%b==0)
        {
            return result;
        }
        else ++result;
    }
    while(true);
}

void Fraction::continued_fractions(Fraction fr)
{
    vector <int> result;
    if(fr.num>=fr.denom)
    {
        result.push_back(fr.num/fr.denom);
    }
    else
    {
        result.push_back(0);
    }
    do
    {
        fr.num%=fr.denom;
        swap(fr.num, fr.denom);
        result.push_back(fr.num/fr.denom);
    }
    while(fr.denom!=1 && fr.num%fr.denom!=0);


    //wypisanie
    cout<<"["<<result[0]<<";";
    for(int i=1;i<result.size()-1;i++)
    {
        cout<<result[i]<<",";
    }
    cout<<result[result.size()-1]<<"]"<<endl;

}

main()
{
    int num, denum;
    while(cin>>num>>denum)
    {
        if(num==0)
        {
            cout<<"[0]"<<endl;
            continue;
        }
        else if(denum==1)
        {
            cout<<"["<<num<<"]"<<endl;
            continue;
        }
        else if(num%denum==0)
        {
            cout<<"["<<num/denum<<"]"<<endl;
            continue;
        }
        else
        {
            Fraction fr1(num,denum);
            Fraction::continued_fractions(fr1);
        }
    }

return 0;
}