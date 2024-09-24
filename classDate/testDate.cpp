/* test driver for class Date
 *
 * Author: WXQ#XDU
 *   Date: 2019,2020
 */

/* 本文仅仅进行了简单的测试，还需要对日期的所有计算进行测试，
 * 请大家自行补充。
*/

#include <iostream>

#include "date.hpp"

using namespace std;

using namespace Chrono ;  // module name of class Date and helpers

/*
2016/03/30 + 1个月=2016/4/30  2016/03/31 + 1个月=2016/4/30
2016/12/30 - 1个月=2016/11/30  2016/12/31 - 1个月=2016/11/30
2016/12/31 + 2个月=2017/02/28  2015/12/31 + 2个月=2016/02/29 
2017/02/28 + 1个月=2017/03/28  2016/2/29 + 1个月=2016/03/29
*/
void test_addmonth()
{
    cout << "Function " << __FUNCTION__ << " begin ..." << endl;

    int nerr=0;
    struct t_test_data {
        Date lh;
        int  delta_month;
        Date expected;
    };

    t_test_data  data[] = {
        { Date(30, Date::mar, 2016),  1, Date(30, Date::apr, 2016)},
        { Date(31, Date::mar, 2016),  1, Date(30, Date::apr, 2016)},
        { Date(30, Date::dec, 2016), -1, Date(30, Date::nov, 2016)},
        { Date(31, Date::dec, 2016), -1, Date(30, Date::nov, 2016)},
        { Date(31, Date::dec, 2016), +2, Date(28, Date::feb, 2017)},
        { Date(31, Date::dec, 2015), +2, Date(29, Date::feb, 2016)},
        { Date(28, Date::feb, 2017), +1, Date(28, Date::mar, 2017)},
        { Date(29, Date::feb, 2016), +1, Date(29, Date::mar, 2016)}
    };

    size_t n = sizeof(data) / sizeof(data[0]);
    for(size_t i=0; i<n; ++i){
        Date a(data[i].lh);
        //if( a.add_month(data[i].delta_month).diff( data[i].expected ) !=0 )
        //if( a.add_month(data[i].delta_month) != data[i].expected )
        if( (a += months(data[i].delta_month)) != data[i].expected )
        {
            ++nerr;
            cerr << "testcase " << i+1 << "  fail: (" << data[i].lh.string_rep() 
                 << ").add_month("  << data[i].delta_month << ")=>" << a.string_rep() 
                 << ", expected [" << data[i].expected.string_rep() << "]\n";
        }
    }

    cout << "Function " << __FUNCTION__ << " is done with " << nerr << " errors.\n";
}

// 重载输入操作符，以从输入设备 input 读取日期数据
// 读到的日期数据回填到参数 ret_value :
// Date d;  cin >> d;
istream& operator>> (istream&  input,  Date & ret_value)
{
    int y, m, d;
    if( !(input >> y) ) return input;
    if( !(input >> m) ) return input;
    if( !(input >> d) ) return input;

    //调用构造函数来生成一个临时的日期对象，
    //  构造时自带检查，若无效则抛出异常来报错。
    //异常处理交给调用者吧。
    
    // 仅当正确时才会复制到 ret_value
    ret_value = Date(d, Date::Month(m), y);
    return input;
}

/* 你来定义输出操作符，用于将日期对象显示到输出设备 output
// Date d; ...... ; cout << d;
ostream& operator<< (ostream&  output,  const Date& ret_value)




*/

void test_input()
{
    Date inDate(1, Date::jan,1970), lh(2, Date::feb, 1990), r;
    int number;

    while( true )
    {
        cout << "\nPress ^C , ^Z in MS-Windows to abort.\n";
        cout << "Input a date(yyyy mm dd): " ; cout.flush();
        try {
            if( !(cin >> inDate) ) break;
        }
        catch(...)
        {
            cout << "\t Your date is invalidate.\n\a"; // '\a' for bell 
            continue;
        }
        cout << "\tYour date is [" << inDate.string_rep() << ",week=" << inDate.weekday() << "]\n";

        cout << "Input number of add days: "; cout.flush();
        if( !(cin >> number) ) break;
        lh = inDate;
        try {
            //r = lh.add_day(number); 
            r = inDate + days(number); 
            cout << "    add_days(" << number << ")=>" << r.string_rep() << ",week=" << r.weekday() << "\n";
        }
        catch(...){
            cout << "    result is a unsupported date.\n\a";
        }

        cout << "Input number of add Months: "; cout.flush();
        if( !(cin >> number) ) break;
        lh = inDate;
        try {
            //r = lh.add_month(number);
            r = inDate + months(number);
            cout << "    add_month(" << number << ")=>" << r.string_rep() <<",week=" << r.weekday() << "\n";
        }
        catch(...){
            cout << "    result is a unsupported date.\n\a";
        }

        cout << "Input number of add years: "; cout.flush();
        if( !(cin >> number) ) break;
        lh = inDate;
        try {
            //r = lh.add_year(number);
            r = inDate + years(number);
            cout << "    add_year(" << number << ")=>" << r.string_rep() <<",week=" << r.weekday() << "\n";
        }
        catch(...){
            cout << "    result is a unsupported date.\n\a";
        }
    }
    
}

int main()
{
    cout << "\x0D\x0A" << Date::hello() << ".\n\n";

#ifdef DEBUG
    // 测试缺省日期值 
    {
        Date def1;
        cout << "Default date by hard-coding is " << def1.string_rep() << "(星期" << (def1.weekday()) << ").\n";
        Date::set_default();
        Date def2;
        cout << "New default date is Today  ==> " << def2.string_rep() << "(星期" << (def2.weekday()) << ").\n";
        cout << endl;
    }
    
    test_addmonth();
    cout << endl;
#endif


    test_input();

    return 0;
}