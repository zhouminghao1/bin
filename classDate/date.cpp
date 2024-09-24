/* This file implements the class Date in Chapter 10 of book
 *  "The C++ Programming Language(Special Edition)"
 *
 * Author: WXQ#XDU
 *   Date: 2019,2020
 */

/* �������˵����
1. �������ݳ�Ա�����ݽṹ����˵��
   Ϊ���ڶԱȣ�����ͬʱ������ Date ���������ݽṹ��
  a. ���̲��и����ģ������ա��¡�������������ʾ�����ڣ�
  b. ��ʵ��Ҫ��ģ�  ���ڴ�1970/1/1 ������������ʾ������.
  c. ���� �� DATE_USE_YMD �����������ݽṹ��
   ������ʱ�����˸ú꣬����û����ա��¡���ı�ʾ��
   ������������ date.hpp ���� #define ���壬Ҳ�����ڿ���������
   project �����ж��壬�������ñ������������з�ʽʱ����
   g++ -o myPrj.exe -D DATE_USE_YMD *.cpp .

2. Ϊ������⣬���к���ʵ�־�δ����ִ��Ч��.

3. Ϊ����ʹ�ã����ֳ�Ա��������Ϊ static ���Ӷ�ʹ���������κ� date ����
   ���޹ء�
   �ȿ���ͨ�������޶���ʽ��������(Date::...)��Ҳ����ͨ�������ʶ��������.

4. �����ڳ����� [min_date, max_date]�������Ķ��壩�������쳣�������
*/


/*
         ���� time() ����ֵ���� time_t �����ֵ
         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

���ĵ����ڼ����ǻ��� C �Ŀ⺯�� mktime, localtime ��ʵ�ֵģ�����
֧�ֵ���С������ 1970/01/01������������������������õĿ�������
�����л�����
-------------------------


time_t �Ǹ����ͱ������������� 32 λ��������64λ������ȡ���������õĿ���������

���� 32 λ�� time_t���ܱ�ʾ�����ʱ���� 
    2038��1��19�� 11:14:07(Asia/Shanghai) ,
�ٹ�1�룬time_t���ݽ���Ϊ��������Ϊ
    1901��12��14�� 04:51:44(����ʱ��).

���� 64 λ�� time_t�������ϵ����ʱ����
   292,277,026,596��12��04��15ʱ30��08��,
����������������������⡣
���� Visual C++ �У�ֻ�ܱ�ʾ�� 3000��12��31��23:59:59��
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
    // ��������: ����ָ���·ݵ����һ��(1~31)��
    static int lastDayOfMonth(int yy, int mm);

    // ������������ָ������ת��Ϊ��1970��1��1������������
    static int convert_YMD2Days(int dd, int mm,  int yy)  ;

    // ��������������ǰ����ת��Ϊ�ա��¡�����������
    static void convert_Days2YMD(int days, int& dd, int& mm,  int& yy);

    // ��ʵ�־������������ֵ ���������
    static Chrono::Date max_date;
    static int  max_days;
    
    // ��ʵ�־�����������Сֵ  ����С����
    static Chrono::Date min_date;
    static int  min_days;
    
private:
    static void Seconds2Struct(time_t seconds, struct tm& t);
};



// �������� DateHelper �ľ�̬���ݳ�Ա
// {{

// ��ʵ�־������������ֵ max_date ���������
#if _WIN32 || WIN32 //_MSC_VER  // Microsft Windows
    #if __MINGW32__  // Code::Block(with mingw GCC-32bits) for Windows
        Chrono::Date DateHelper::max_date(31, Chrono::Date::dec, 2037); // 1970/1/1 + 24836 days
        int  DateHelper::max_days = 24836;
    #elif _USE_32BIT_TIME_T  // ��32bits ��ʾ��ʱ��
        Chrono::Date DateHelper::max_date(19, Chrono::Date::jan, 2038); // 1970/1/1 + 24855 days
        int  DateHelper::max_days = 24855;
    #else  // �� 64bits ��ʾ��ʱ��
        Chrono::Date DateHelper::max_date(31, Chrono::Date::dec, 3000); // 1970/1/1 + 376564 days
        int  DateHelper::max_days = 376564;
    #endif
#elif __CYGWIN__  || __CYGWIN32__  // cygwin on Microsft Windows
    Chrono::Date DateHelper::max_date(18, Chrono::Date::jan, 2038); // 1970/1/1 + 24854 days
    int  DateHelper::max_days = 24854;
#else // ����ƽ̨, ������ڴ�����
    Chrono::Date DateHelper::max_date(31, Chrono::Date::dec, 9999); // 1970/1/1 + 2932896 days
    int  DateHelper::max_days = 2932896;
#endif

// ��ʵ�־�����������Сֵ min_date ����С����
// �����У���Ϊʹ�� std::localtime() �� std::mktime() ����
// ʱ��ת����������С���ڲ������� 1970/1/1.
Chrono::Date DateHelper::min_date(1, Chrono::Date::jan, 1970);
int  DateHelper::min_days(0);
//}


}


// �̲� P240 ��ʾ����ý��������͡���֮��صķǳ�Ա ���嵽ͬһ����ģ�顱
namespace Chrono {

// ���֧�ֵ��������
const Date& Date::max()
{
    return DateHelper::max_date;
}

// ���֧�ֵ���С����
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
// �ȴ��� ȱʡ���
    if(0 == yy) yy = this->default_date.year();  //����ʾ�����ַ��ʾ�̬��Ա�ķ�ʽ
    if(0 == mm) mm = Date::default_date.month();
    if(0 == dd) dd = default_date.day();

// ����¡��յ���Ч��
    int lastday = DateHelper::lastDayOfMonth(yy, mm);
    if(dd<1 || lastday<dd)
        throw Bad_date();

    #ifdef DATE_USE_YMD  //������ݳ�Ա���ꡢ�¡�����������

        y = yy; m = mm; d = dd;

    #else  // ������ݳ�Ա���� 1970/1/1 ����������

        days_from_19700101 = DateHelper::convert_YMD2Days(dd, mm, yy);

    #endif

//ȷ�� ���ڳ�ֵ���ܳ�����Χ
    if( this == &DateHelper::min_date || this == &DateHelper::max_date )
    {
        // �������С��������ڵĳ�ʼ��
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

#if _MSC_VER  // MS Visual Studio ��û�� snprintf������ _snprintf�����и���ȫ�� sprintf_s
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
    // �ж�����ı�׼����
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
    return add_month( n * 12 ); // �Ƚ̲� P231��ʵ�ּ�
}

Date& Date::add_month(int n)
{
    if( n == 0 )  // �������ļ���
        return *this;

    // ��ʾ���������þֲ�����ż�����������ٸı��������
    #ifdef DATE_USE_YMD
        int dd(d), yy(y); int mm(m);
    #else
        int dd, yy; int mm;
        DateHelper::convert_Days2YMD(this->days_from_19700101, dd, mm, yy);
    #endif

    yy  += n / 12; // ��/���� ���������
    mm  += n % 12; // ��/���� ����һ����·���

    // �µ��·ݿ�����!!
    if( mm > 12 ) {
        mm -= 12;
        yy += 1;
    }
    else if ( mm < 1 ) {
        mm += 12;
        yy -= 1;
    }

    // ���������µ����һ�죬�����Ϊ���µ����һ�졣
    // Excel��Oracle��MySQL������������������!!!
    int maxday = DateHelper::lastDayOfMonth(yy, mm);
    if(dd > maxday)
        dd = maxday;

    // ���ﴴ����ʱ���ڶ��󣬽������캯��������������ڵ���Ч�ԡ�
    // ����Ч�����ɹ��캯���׳��쳣���� this �����ֵ���ᷢ���仯!!!
    Date newDate(dd, Month(mm), yy);

    // ������������Ч��this ����Ż�仯!!!
    *this = newDate; // copy value

    return *this;
}

Date& Date::add_day(int n)
{
    #ifdef DATE_USE_YMD
        int days = DateHelper::convert_YMD2Days(d, m, y) + n;
        // ���仯 n ���������Ƿ���Ч
        if( days < DateHelper::min_days || DateHelper::max_days < days)
            throw Bad_date();

        int mm;
        convert_Days2YMD(days, d, mm, y);
        m = Month(mm);
    #else
        int days = days_from_19700101 + n;
        // ���仯 n ���������Ƿ���Ч
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
    // ͨ����ʾ���ù��캯�����һ�������� Date ���󣬲�����
    // ���Ƶ� default_date.
    // ��������Ч���� ���캯������.
    Date::default_date = Date(dd, mm, yy);
}

// static member
void Date::set_default()
{
    time_t  now = time(NULL);  // ���ϵͳ��ǰʱ��(��1970��1��1�� 0:0:0 ����������)

    // ���� time_t ������64λ������������ת��Ϊ������ת��Ϊ 32 λ������
    // �� (now/(24*3600) ������ 2^31-1 ʱ���������ת������ȷ�ġ�
    int days = int( (now/(24*3600)) & 0xffffffff ); //��1970��1��1������������
    int dd, mm, yy;
    DateHelper::convert_Days2YMD(days, dd, mm, yy); // ������ת��Ϊ�ա��¡�����������
    set_default(dd, Month(mm), yy);
}

//END of implementation of class Date

} // end of namespace Chrono 




// ----------------------------------------------------------------
// �������� DateHelper ��ʵ��, ������Ա����ʵ�֡���̬���ݳ�Ա�Ķ���
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


// ��ָ������ת��Ϊ��1970��1��1������������������֮���ء�
// static member
int DateHelper::convert_YMD2Days(int dd, int mm,  int yy)
{
    struct tm  t;

    t.tm_hour =12;  t.tm_min=1; t.tm_sec=1; t.tm_isdst =0;
    t.tm_year = yy - 1900; t.tm_mon = mm -1; t.tm_mday = dd;
    
    //��� C �⺯�� mktime() ��������С���������
    time_t tm = mktime( &t ); // return -1 on error
    if( tm == time_t(-1) )
    {
//      printf("mktime: %d/%d/%d return -1\n", yy,mm, dd);
        return -1;
    }
    else
        return int( (tm/(24*3600)) & 0xffffffff );
}



// ����1970��1��1�� 0:0:0 �����������ֽ�Ϊʱ�����
// static member
void DateHelper::Seconds2Struct(time_t seconds, struct tm& t)
{
    struct tm  ret;
    ret.tm_hour =-1;  ret.tm_min=-1; ret.tm_sec=-1;
    ret.tm_year = -1; ret.tm_mon=-1; ret.tm_mday=-1;
    ret.tm_isdst=-1; ret.tm_wday=-1; ret.tm_yday=-1;

//��� C �⺯�� localtime() ��������С���������

#if _MSC_VER  // MS Visual Studio �б��� localtime ����ȫ���ø���ȫ�� localtime_s
    localtime_s(&ret, &seconds);
#else
    struct tm* p = localtime(&seconds);
    if( p != NULL ) ret = *p;
#endif
    t = ret;
}


// ��������������1970/1/1��ʼ������ days ת��Ϊ�ա��¡�����������
// static member
void DateHelper::convert_Days2YMD(int days, int& dd, int& mm,  int& yy)
{
    // ע�⣺����� time_t(days) ����ֹ С�������ͼ�������������ת��Ϊ����������.
    time_t tim = time_t(days) * (24*3600) + 3600;
    struct tm  t ;
    Seconds2Struct( tim, t );

    dd = t.tm_mday;
    mm = t.tm_mon + 1;
    yy = t.tm_year + 1900;
}


// END OF FILE
