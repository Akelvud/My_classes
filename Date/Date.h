#include <iostream>

class Date
{
  friend std::ostream& operator<<(std::ostream&, Date);

public:
  Date(int = 30, int = 12, int = 1799);
  Date NextDay();
  Date PreviousDay();
  bool IsLeap();
  short WeekNumber();
  short DayOfWeek();
  int Duration(Date date);
  

private:

  int NoD();
  int Day;
  int Month;
  int Year;
  static constexpr int a[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
};
