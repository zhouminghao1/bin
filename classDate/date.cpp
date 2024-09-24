/* This file implements the class Date in Chapter 10 of book
 *  "The C++ Programming Language(Special Edition)"
 *
 * Author: WXQ#XDU
 *   Date: 2019,2020
 */

/* 程序设计说明：
1. 关于数据成员（数据结构）的说明
   为便于对比，本文同时声明了 Date 的两种数据结构：
  a. （教材中给出的）基于日、月、年三个分量表示的日期；
  b. （实验要求的）  基于从1970/1/1 以来的天数表示的日期.
  c. 采用 宏 DATE_USE_YMD 区分两种数据结构。
   当编译时定义了该宏，则采用基于日、月、年的表示。
   这个宏你可以在 date.hpp 中用 #define 定义，也可以在开发环境的
   project 配置中定义，或者你用编译器的命令行方式时，如
   g++ -o myPrj.exe -D DATE_USE_YMD *.cpp .

2. 为便于理解，所有函数实现均未考虑执行效率.

3. 为便于使用，部分成员函数定义为 static ，从而使得它们与任何 date 对象
   都无关。
   既可以通过类名限定方式访问它们(Date::...)，也可以通过对象标识调用它们.

4. 当日期超出了 [min_date, max_date]（见下文定义），则用异常报告错误。
*/


/*
         关于 time() 返回值类型 time_t 的最大值
         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

本文的日期计算是基于 C 的库函数 mktime, localtime 来实现的，所以
支持的最小日期是 1970/01/01，最大日期则受限于你所采用的开发环境
和运行环境。
-------------------------


time_t 是个类型别名，它到底是 32 位整数还是64位整数，取决于你所用的开发环境。

对于 32 位的 time_t，能表示的最大时间是 
    2038年1月19日 11:14:07(Asia/Shanghai) ,
再过1秒，time_t数据将变为负数，变为
    1901年12月14日 04:51:44(本地时间).

对于 64 位的 time_t，理论上的最大时间是
   292,277,026,596年12月04日15时30分08秒,
基本不会遇到这类溢出问题。
但在 Visual C++ 中，只能表示到 3000年12月31日23:59:59。
*/


#include <cstdio>   // for snprintf()
#include <ctime>    // for time(), localtime()

#include "date.hpp" // interface declaration of class Date

using namespace std;

// let 'DateHelper' can be used ONLY in this file
namespace {

// Encapsulate all helper data, operations into
// this local class like JAVA manner.
//
// All members is defined in tail of this file
class DateHelper{

public:
    // 辅助函数: 计算指定月份的最后一天(1~31)。
    static int lastDayOfMonth(int yy, int mm);

    // 辅助函数：将指定日期转换为自1970年1月1日以来的天数
    static int convert_YMD2Days(int dd, int mm,  int yy)  ;

    // 辅助函数：将当前日期转换为日、月、年三个分量
    static void convert_Days2YMD(int days, int& dd, int& mm,  int& yy);

    // 由实现决定的日期最大值 和最大天数
    static Chrono::Date max_date;
    static int  max_days;
    
    // 由实现决定的日期最小值  和最小天数
    static Chrono::Date min_date;
    static int  min_days;
    
private:
    static void Seconds2Struct(time_t seconds, struct tm& t);
};



// 定义类型 DateHelper 的静态数据成员
// {{

// 由实现决定的日期最大值 max_date 和最大天数
#if _WIN32 || WIN32 //_MSC_VER  // Microsft Windows
    #if __MINGW32__  // Code::Block(with mingw GCC-32bits) for Windows
        Chrono::Date DateHelper::max_date(31, Chrono::Date::dec, 2037); // 1970/1/1 + 24836 days
        int  DateHelper::max_days = 24836;
    #elif _USE_32BIT_TIME_T  // 用32bits 表示的时间
        Chrono::Date DateHelper::max_date(19, Chrono::Date::jan, 2038); // 1970/1/1 + 24855 days
        int  DateHelper::max_days = 24855;
    #else  // 用 64bits 表示的时间
        Chrono::Date DateHelper::max_date(31, Chrono::Date::dec, 3000); // 1970/1/1 + 376564 days
        int  DateHelper::max_days = 376564;
    #endif
#elif __CYGWIN__  || __CYGWIN32__  // cygwin on Microsft Windows
    Chrono::Date DateHelper::max_date(18, Chrono::Date::jan, 2038); // 1970/1/1 + 24854 days
    int  DateHelper::max_days = 24854;
#else // 其他平台, 最大日期待测试
    Chrono::Date DateHelper::max_date(31, Chrono::Date::dec, 9999); // 1970/1/1 + 2932896 days
    int  DateHelper::max_days = 2932896;
#endif

// 由实现决定的日期最小值 min_date 和最小天数
// 本文中，因为使用 std::localtime() 和 std::mktime() 进行
// 时间转换，所以最小日期不能早于 1970/1/1.
Chrono::Date DateHelper::min_date(1, Chrono::Date::jan, 1970);
int  DateHelper::min_days(0);
//}


}


// 教材 P240 提示：最好将日期类型、与之相关的非成员 定义到同一个“模块”
namespace Chrono {

// 获得支持的最大日期
const Date& Date::max()
{
    return DateHelper::max_date;
}

// 获得支持的最小日期
const Date& Date::min()
{
    return DateHelper::min_date;
}

std::string Date::hello()
{
    string msg("This Date is based on "
                #ifdef DATE_USE_YMD
                    "Y-M-D"
                #else
                    "day number"
                #endif
                ", and supports [");

    msg += min().string_rep();
    msg += ", ";
    msg += max().string_rep();
    msg += "]";

    return msg;
}



// defination of static data member, 
//  its value is hard-coding, birthday of this file
Date Date::default_date(28, Date::may, 2019);

Date::Date(int dd, Month mm,  int yy)
{
// 先处理 缺省情况
    if(0 == yy) yy = this->default_date.year();  //这里示例三种访问静态成员的方式
    if(0 == mm) mm = Date::default_date.month();
    if(0 == dd) dd = default_date.day();

// 检查月、日的有效性
    int lastday = DateHelper::lastDayOfMonth(yy, mm);
    if(dd<1 || lastday<dd)
        throw Bad_date();

    #ifdef DATE_USE_YMD  //如果数据成员是年、月、日三个分量

        y = yy; m = mm; d = dd;

    #else  // 如果数据成员是自 1970/1/1 以来的天数

        days_from_19700101 = DateHelper::convert_YMD2Days(dd, mm, yy);

    #endif

//确认 日期初值不能超出范围
    if( this == &DateHelper::min_date || this == &DateHelper::max_date )
    {
        // 不检查最小和最大日期的初始化
    }
    else  if(this->diff(DateHelper::min_date) <0) // this < min_date
    {
        //print only for debug, not for USER of Date
        printf("%d/%d/%d<min_date %s\n", yy,mm,dd, DateHelper::min_date.string_rep().c_str());

        throw Bad_date(); //throw an object created by constructor of class Bad_date
    }
    else  if(this->diff(DateHelper::max_date) > 0) // max_date < this 
    {
        //print only for debug, not for USER of Date
        printf("%d/%d/%d>max_date %s\n", yy,mm,dd, DateHelper::max_date.string_rep().c_str());

        throw Bad_date();
    }

}


int Date::day() const
{
    #ifdef DATE_USE_YMD
        return d;
    #else
        int dd, mm, yy;
        DateHelper::convert_Days2YMD(this->days_from_19700101, dd, mm, yy);
        return dd;
    #endif
}


Date::Month Date::month() const
{
    #ifdef DATE_USE_YMD
        return m;
    #else
        int dd, mm, yy;
        DateHelper::convert_Days2YMD(this->days_from_19700101, dd, mm, yy);
        return Month(mm);
    #endif
}


int Date::year()  const
{
    #ifdef DATE_USE_YMD
        return y;
    #else
        int dd, mm, yy;
        DateHelper::convert_Days2YMD(this->days_from_19700101, dd, mm, yy);
        return yy;
    #endif
}

// return a string representation for date
std::string Date::string_rep() const
{
    #ifdef DATE_USE_YMD
      // nothing
    #else
        int d, m, y;
        DateHelper::convert_Days2YMD(this->days_from_19700101, d, m, y);
    #endif

    char buffer[15];

#if _MSC_VER  // MS Visual Studio 中没有 snprintf，但有 _snprintf，还有更安全的 sprintf_s
    sprintf_s // _snprintf
#else
    snprintf
#endif
    (buffer, sizeof(buffer), "%04d-%02d-%02d", y, m, d); // ISO format

    return buffer;
}

void Date::char_rep(char s[]) const
{
    string str = string_rep();

    const char* p = str.c_str();
    
    // copy each char from p[] to s[]
    while( *s++ = *p++ ); // just is strcpy(s, p);
}

// the 'static' version
int Date::leapyear(int yy)
{
    // 判断闰年的标准方法
    if (    ( yy % 400 == 0 )
         || ( (yy % 4  == 0)  && (yy % 100 != 0) )
       )
        return 1;
    else
        return 0;
}

// the non'static' version
int  Date::leapyear() const
{
    return leapyear(this->year());
}

Date& Date::add_year(int n)
{
    return add_month( n * 12 ); // 比教材 P231的实现简单
}

Date& Date::add_month(int n)
{
    if( n == 0 )  // 避免多余的计算
        return *this;

    // 提示：这里先用局部量存放计算结果，最后再改变对象自身
    #ifdef DATE_USE_YMD
        int dd(d), yy(y); int mm(m);
    #else
        int dd, yy; int mm;
        DateHelper::convert_Days2YMD(this->days_from_19700101, dd, mm, yy);
    #endif

    yy  += n / 12; // 加/减的 完整年份数
    mm  += n % 12; // 加/减的 不足一年的月份数

    // 新的月份跨年了!!
    if( mm > 12 ) {
        mm -= 12;
        yy += 1;
    }
    else if ( mm < 1 ) {
        mm += 12;
        yy -= 1;
    }

    // 若超过当月的最后一天，则调整为当月的最后一天。
    // Excel、Oracle、MySQL等软件都是这样处理的!!!
    int maxday = DateHelper::lastDayOfMonth(yy, mm);
    if(dd > maxday)
        dd = maxday;

    // 这里创建临时日期对象，借助构造函数来检查所得日期的有效性。
    // 若无效，则由构造函数抛出异常，但 this 对象的值不会发生变化!!!
    Date newDate(dd, Month(mm), yy);

    // 当所得日期有效，this 对象才会变化!!!
    *this = newDate; // copy value

    return *this;
}

Date& Date::add_day(int n)
{
    #ifdef DATE_USE_YMD
        int days = DateHelper::convert_YMD2Days(d, m, y) + n;
        // 检查变化 n 天后的日期是否有效
        if( days < DateHelper::min_days || DateHelper::max_days < days)
            throw Bad_date();

        int mm;
        convert_Days2YMD(days, d, mm, y);
        m = Month(mm);
    #else
        int days = days_from_19700101 + n;
        // 检查变化 n 天后的日期是否有效
        if( days < DateHelper::min_days || DateHelper::max_days < days)
            throw Bad_date();
        days_from_19700101 = days;
    #endif

    return *this;
}

int Date::diff(const Date& rh) const
{
    #ifdef DATE_USE_YMD
        int d1 = DateHelper::convert_YMD2Days(d, m, y);
        int d2 = DateHelper::convert_YMD2Days(rh.d, rh.m, rh.y);
        return d1-d2;
    #else
        return this->days_from_19700101 - rh.days_from_19700101;
    #endif
}

int Date::weekday() const
{
    int days=0;
    #ifdef DATE_USE_YMD
        days = DateHelper::convert_YMD2Days(d, m, y);
    #else
        days = this->days_from_19700101;
    #endif

    // 1970/1/1 is Thursday
    int tm_wday = (4 + days) % 7;
    if (tm_wday < 0)
        tm_wday += 7;
    return tm_wday;
}


Date Date::lastDateInMonth() const
{
    int yy   = this->year();
    Month mm = this->month();
    int dd = DateHelper::lastDayOfMonth(yy, mm);
    return Date(dd, mm, yy);
}


// static member
void Date::set_default(int dd, Month mm, int yy)
{
    // 通过显示调用构造函数获得一个匿名的 Date 对象，并将其
    // 复制到 default_date.
    // 参数的有效性由 构造函数负责.
    Date::default_date = Date(dd, mm, yy);
}

// static member
void Date::set_default()
{
    time_t  now = time(NULL);  // 获得系统当前时间(从1970年1月1日 0:0:0 以来的秒数)

    // 由于 time_t 可能是64位整数，但将其转换为天数需转换为 32 位整数。
    // 当 (now/(24*3600) 不超过 2^31-1 时，下面这个转换是正确的。
    int days = int( (now/(24*3600)) & 0xffffffff ); //从1970年1月1日以来的天数
    int dd, mm, yy;
    DateHelper::convert_Days2YMD(days, dd, mm, yy); // 将天数转换为日、月、年三个分量
    set_default(dd, Month(mm), yy);
}

//END of implementation of class Date

} // end of namespace Chrono 




// ----------------------------------------------------------------
// 辅助类型 DateHelper 的实现, 包括成员函数实现、静态数据成员的定义
//



// static member
int DateHelper::lastDayOfMonth(int yy, int mm)
{
    if( mm < 1 || mm > 12 ) return 0;

    int days_each_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (mm==2 && Chrono::Date::leapyear(yy))
        ? 29
        : days_each_month[mm];
}


// 将指定日期转换为自1970年1月1日以来的天数，并将之返回。
// static member
int DateHelper::convert_YMD2Days(int dd, int mm,  int yy)
{
    struct tm  t;

    t.tm_hour =12;  t.tm_min=1; t.tm_sec=1; t.tm_isdst =0;
    t.tm_year = yy - 1900; t.tm_mon = mm -1; t.tm_mday = dd;
    
    //这个 C 库函数 mktime() 决定了最小、最大日期
    time_t tm = mktime( &t ); // return -1 on error
    if( tm == time_t(-1) )
    {
//      printf("mktime: %d/%d/%d return -1\n", yy,mm, dd);
        return -1;
    }
    else
        return int( (tm/(24*3600)) & 0xffffffff );
}



// 将从1970年1月1日 0:0:0 以来的秒数分解为时间分量
// static member
void DateHelper::Seconds2Struct(time_t seconds, struct tm& t)
{
    struct tm  ret;
    ret.tm_hour =-1;  ret.tm_min=-1; ret.tm_sec=-1;
    ret.tm_year = -1; ret.tm_mon=-1; ret.tm_mday=-1;
    ret.tm_isdst=-1; ret.tm_wday=-1; ret.tm_yday=-1;

//这个 C 库函数 localtime() 决定了最小、最大日期

#if _MSC_VER  // MS Visual Studio 中报告 localtime 不安全，用更安全的 localtime_s
    localtime_s(&ret, &seconds);
#else
    struct tm* p = localtime(&seconds);
    if( p != NULL ) ret = *p;
#endif
    t = ret;
}


// 辅助函数：将从1970/1/1开始的天数 days 转换为日、月、年三个分量
// static member
void DateHelper::convert_Days2YMD(int days, int& dd, int& mm,  int& yy)
{
    // 注意：下面的 time_t(days) ，防止 小整数类型计算溢出，因此先转换为大整数类型.
    time_t tim = time_t(days) * (24*3600) + 3600;
    struct tm  t ;
    Seconds2Struct( tim, t );

    dd = t.tm_mday;
    mm = t.tm_mon + 1;
    yy = t.tm_year + 1900;
}


// END OF FILE
