#include "Date.h"

Date::Date(int D, int M, int Y)
{
  Day = D;
  Month = M;
  Year = Y;
}

Date Date::NextDay()
{
  Date Ans(Day, Month, Year);
  int DM;
  Ans.Day++;
  if (Month == 2 && (Year % 400 == 0 || (Year % 100 != 0 && Year % 4 == 0))) {
      DM = 29;
  }
  else {
    DM = a[Month];
  }

  if (Ans.Day > DM) {
    Ans.Day = 1;
    Ans.Month++;
    if (Ans.Month > 12) {
      Ans.Month = 1;
      Ans.Year++;
    }
  }
  return Ans;
}

Date Date::PreviousDay()
{
  Date Ans(Day, Month, Year);
  Ans.Day--;

  if (Ans.Day == 0) {
    Ans.Month--;
    if (Ans.Month == 0) {
      Ans.Month = 12;
      Ans.Year--;
    }
    int DM;
    
    if (Ans.Month == 2 && (Ans.Year % 400 == 0 || (Ans.Year % 100 != 0 && Ans.Year % 4 == 0))) {
      DM = 29;
    }
    else {
      DM = a[Ans.Month];
    }
    
    Ans.Day = DM;

  }

  return Ans;  
}

bool Date::IsLeap()
{
  return (Year % 400 == 0 || (Year % 100 != 0 && Year % 4 == 0));
}



short Date::WeekNumber()
{
  Date date(1, 1, Year);
  int D = date.NoD() + 4;

  int N = 1;
  D = 7 - D % 7 - 1;
  int DN = NoD() - date.NoD();
  std::cout << DN << "\n";

  while (D <= DN) {
    N++;
    D += 7;
  }


  return N;
}

short Date::DayOfWeek()
{
  int D = NoD() + 4;

  return D % 7 + 1;
}



int Date::NoD()
{
  int D = 0;
  for (int i = 0; i < Year; i++) {
    D += 365 + (i % 400 == 0 || (i % 100 != 0 && i % 4 == 0));
  }

  for (int i = 1; i < Month; i++) {
    int DN;
    if (i == 2 && (Year % 400 == 0 || (Year % 100 != 0 && Year % 4 == 0))) {
      DN = 29;
    }
    else {
      DN = a[i];
    }
    D += DN;
  }

  D += Day;
  
  return D;
}

int Date::Duration(Date date)
{
  int ans = NoD() - date.NoD();
  if (ans < 0) ans = -ans;

  return ans;
}

std::ostream& operator<<(std::ostream& out, Date date)
{
  if (date.Day < 10) out << 0;
  out << date.Day << '.';
  if (date.Month < 10) out << 0;
  out << date.Month << '.';
  out << date.Year;
  return out;
}


