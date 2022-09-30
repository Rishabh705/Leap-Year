#include <iostream>
#include <string>
#include <cctype>
using namespace std;
string months[4][12] = {{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"}, {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}, {"31", "28", "31", "30", "31", "30", "31", "31", "30", "31", "30", "31"}};
string lower(string str1)
{
    for (int i = 0; i < str1.length(); i++)
        str1[i] = tolower(str1[i]);
    return str1;
}
class LeapYear
{
    string date;

public:
    LeapYear(string d)
    {
        date = d;
    }
    bool checkLeap()
    {
        int w = stoi(date.substr(date.length() - 4));
        if (w % 400 == 0)
            return true;
        if (w % 100 == 0)
            return false;
        if (w % 4 == 0)
            return true;
        return false;
    }
};
class InputSeparator
{
public:
    string d, m, y, day, year;
    InputSeparator(string date)
    {
        d = date.substr(0, 2);
        y = date.substr(date.length() - 4);
        m = date.substr(2, date.length() - 6);
    }
};
class ValidInput
{
    bool month_check = false, day_check = false, year_check = false, without_slash = false;
    bool checkDay(int mm, string months[4][12], string day, bool g)
    {
        try
        {
            bool day_ch = false;
            for (size_t i = 0; i < 12; i++)
            {
                if (mm == stoi(months[2][i]))
                {
                    if (mm == 2 && g == true)
                    {
                        if (stoi(day) >= 1 && stoi(day) <= 29)
                            day_ch = true;
                        break;
                    }
                    else if (mm == 2 && g == false)
                    {
                        if (stoi(day) >= 1 && stoi(day) <= 28)
                            day_ch = true;
                        break;
                    }
                    else
                    {
                        if (stoi(day) >= 1 && stoi(day) <= stoi(months[3][i]))
                            day_ch = true;
                        break;
                    }
                }
            }
            return day_ch;
        }
        catch (...)
        {
            return 0;
        }
    }

public:
    int dd, yy, mm;
    bool checkValidity(string date)
    {
        try
        {
            int ctr = 0;
            for (size_t i = 0; i < date.length(); i++)
            {
                if (date[i] == '.' | date[i] == '-' | date[i] == '/')
                    ctr++;
            }
            if (ctr == 2 | ctr == 0)
            {
                string d, m, y, day, month, year;
                InputSeparator ip(date);
                d = ip.d;
                y = ip.y;
                m = ip.m;
                int j = 0, alp = 0;
                for (int i = 0; i < y.length(); i++)
                {
                    if (isdigit(y[i]))
                    {
                        year[j] = y[i];
                        
                        j++;
                    }
                    else
                    {

                        alp++;
                        break;
                    }
                }
                if (j == 4 && alp == 0)
                {
                    yy = stoi(y);
                    if (yy >= 1582)
                        year_check = true;
                    else
                        return false;
                }
                j = 0, alp = 0;
                month.resize(50);
                for (int i = 0; i < m.length(); i++)
                {
                    if (isdigit(m[i]))
                    {
                        month[j] = m[i];
                        j++;
                    }
                    else
                    {
                        if (i != 0 && i != m.length() - 1)
                        {
                            alp++;
                            break;
                        }
                    }
                }
                if (j == 2 && alp == 0)
                {
                    mm = stoi(month);
                    if (mm > 0 && mm < 13)
                        month_check = true;
                    else
                        return false;
                }
                else if (j == 1)
                {
                    if (m[1] == '/' | m[1] == '.' | m[1] == '-')
                    {
                        mm = stoi(m.substr(0, 1));
                        if (mm > 0 && mm < 13)
                            month_check = true;
                        else
                            return false;
                    }
                    else if ((m[0] == '/' | m[0] == '.' | m[0] == '-') && (m[2] == '/' | m[2] == '.' | m[2] == '-'))
                    {
                        mm = stoi(m.substr(1, 2));
                        if (mm > 0 && mm < 13)
                            month_check = true;
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else if (j == 0)
                {
                    if ((m[0] == '/' | m[0] == '.' | m[0] == '-') && (m[m.length() - 1] == '/' | m[m.length() - 1] == '.' | m[m.length() - 1] == '-'))
                        month = m.substr(1, m.length() - 2);
                    else if (m[m.length() - 1] == '/' | m[m.length() - 1] == '.' | m[m.length() - 1] == '-')
                        month = m.substr(0, m.length() - 1);
                    else
                        month = m;
                    for (size_t i = 0; i < 12; i++)
                    {
                        if (lower(month).compare(lower(months[0][i])) == 0 | lower(month).compare(lower(months[1][i])) == 0)
                        {
                            mm = stoi(months[2][i]);
                            month_check = true;
                            break;
                        }
                    }
                    if (month_check == false)
                    {
                        string h;
                        h = h.append(1, d[1]);
                        h = h.append(m);
                        for (size_t i = 0; i < 12; i++)
                        {
                            if (((lower(h).compare(lower(months[0][i]))) == 0 | lower(h).compare(lower(months[1][i])) == 0))
                            {
                                mm = stoi(months[2][i]);
                                month = h;
                                month_check = true;
                                without_slash = true;
                                break;
                            }
                        }
                    }
                    if (month_check == false)
                        return false;
                }
                else
                    return false;
                LeapYear o(date);
                bool g = o.checkLeap();
                day.resize(50);
                j = 0, alp = 0;
                for (int i = 0; i < d.length(); i++)
                {
                    if (isdigit(d[i]))
                    {
                        day[j] = d[i];
                        j++;
                    }
                    else
                    {
                        if (i != 0 && i != d.length() - 1)
                        {
                            alp++;
                            break;
                        }
                    }
                }
                if (j == 1)
                {
                    if (d[1] == '/' | d[1] == '.' | d[1] == '-' | (without_slash == true))
                    {
                        dd = stoi(d.substr(0, 1));
                        day_check = checkDay(mm, months, day, g);
                        if (day_check == false)
                            return false;
                    }
                    else
                        return false;
                }
                else if (j == 2 && alp == 0)
                {
                    dd = stoi(d.substr(0, 2));
                    day_check = checkDay(mm, months, day, g);
                    if (day_check == false)
                        return false;
                }
                return (month_check && day_check && year_check);
            }
            else
                return false;
        }
        catch (...)
        {
            return 0;
        }
    }
};
class TwoDates
{
public:
    void dateChecker(string d, ValidInput obj, LeapYear ob)
    {
        bool valid, leap;
        valid = obj.checkValidity(d);
        if (valid == false)
            cout << d << " is invalid date.\n";
        else
        {
            cout << d << " is valid date.\n";
            leap = ob.checkLeap();
            if (leap == true)
                cout << d << " is leap year.\n\n";
            else
                cout << d << " is not leap year.\n\n";
        }
    }

private:
    string date1, date2;
    int dd1, dd2, mm1, mm2, yy1, yy2;
    int getLeapYears(int y, int mn)
    {
        int yr = y;
        if (mn > 0)
        {
            if (mn <= 2)
                yr--;
            return yr / 4 - yr / 100 + yr / 400;
        }
        else
            return 0;
    }
    int calcDays()
    {
        long int n1 = yy1 * 365 + dd1;
        for (int i = 0; i < mm1 - 1; i++)
            n1 += stoi(months[3][i]);
        n1 += getLeapYears(yy1, mm1);
        long int n2 = yy2 * 365 + dd2;
        for (int i = 0; i < mm2 - 1; i++)
            n2 += stoi(months[3][i]);
        n2 += getLeapYears(yy2, mm2);
        return (n2 - n1);
    }

public:
    TwoDates(string d1, string d2)
    {
        date1 = d1;
        date2 = d2;
        ValidInput ob1, ob2;
        LeapYear o1(d1), o2(d2);
        dateChecker(d1, ob1, o1);
        dateChecker(d2, ob2, o2);
    }
    int operation()
    {
        ValidInput ob1, ob2;
        LeapYear o1(date1), o2(date2);
        bool check1 = ob1.checkValidity(date1);
        bool check2 = ob2.checkValidity(date2);
        if (check1 && check2)
        {
            dd1 = ob1.dd;
            dd2 = ob2.dd;
            mm1 = ob1.mm;
            mm2 = ob2.mm;
            yy1 = ob1.yy;
            yy2 = ob2.yy;
            return abs(calcDays());
        }
        else
            return 0;
    }
};
int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        ValidInput obj;
        bool f = obj.checkValidity(argv[1]);
        if (f == true)
        {
            cout << "Valid input.\n";
            LeapYear ob(argv[1]);
            bool c = ob.checkLeap();
            if (c == true)
                cout << "Entered year is leap year.\n";
            else
                cout << "Entered year is not a leap year.\n";
        }
        else
            cout << "Invalid date!\n";
    }
    else if (argc == 3)
    {
        TwoDates obj(argv[1], argv[2]);
        ValidInput ob;
        LeapYear o1(argv[1]), o2(argv[2]);
        cout << "Calculating Difference between dates...\n";
        if (obj.operation())
            cout << "Day difference is : " << obj.operation();
        else
            cout << "Day difference is : " << 0 << endl;
    }
    else
        cout << "Incorrect format\n";
    return 0;
}
