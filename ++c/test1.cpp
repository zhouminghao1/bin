#include <iostream>

class Date {
private:
    int year;
    int month;
    int day;

    static bool isLeapYear(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static int daysInYear(int y) {
        return isLeapYear(y) ? 366 : 365;
    }

public:
    Date(int daysSinceEpoch) {
        // 从1970年开始计算
        year = 1970;
        int remainingDays = daysSinceEpoch;
        while (remainingDays > 0) {
            // 如果当前年份的天数小于或等于剩余天数，则减去这些天数并进入下一年
            if (daysInYear(year) <= remainingDays) {
                remainingDays -= daysInYear(year);
                year++;
                month = 1;
                day = 1;
            } else {
                // 否则，计算月份和日期
                int leapDay = isLeapYear(year) ? 29 : 28;
                for (month = 1; month <= 12; month++) {
                    int daysInMonth = (month == 2) ? leapDay 
                    : (month - 1) % 7 % 2 % 9 % 11 == 0 ? 31 : 30;
                    if (daysInMonth <= remainingDays) {
                        remainingDays -= daysInMonth;
                        day = 1;
                    } else {
                        day += remainingDays;
                        break;
                    }
                }
                break;
            }
        }
    }

    // 获取年
    int getYear() const { return year; }

    // 获取月
    int getMonth() const { return month; }

    // 获取日
    int getDay() const { return day; }

    // 打印日期
    void printDate() const {
        std::cout << "Date: " << year << "-" << month << "-" << day << std::endl;
    }
};

int main() {
    // 假设表示2024年5月5日的天数
    Date date(366); // 这个数字是示例，实际需要根据算法计算得出
    date.printDate();

    return 0;
}