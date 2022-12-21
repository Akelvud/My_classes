#include "RationalNumber"

fraction::fraction(int numerator, int denominator) {
  this->numerator = numerator;
  this->denominator = denominator;
}

fraction::~fraction() {}

int fraction::Get_numerator() { return this->numerator; }

int fraction::Get_denominator() { return this->denominator; }

// Сокращение дроби
void fraction::reduction() {
  if (denominator < 0) {
    numerator = -numerator;
    denominator = -denominator;
  }
  int gcd = get_gcd(numerator, denominator);

  numerator /= gcd;
  denominator /= gcd;
}

//Сумма дробей
fraction fraction::operator+(fraction a) {
  fraction ans;

  int common_denominator = this->denominator * a.denominator /
    get_gcd(this->denominator, a.denominator);

  ans.numerator = this->numerator * (common_denominator / this->denominator) +
    a.numerator * (common_denominator / a.denominator);

  ans.denominator = common_denominator;

  ans.reduction();
  return ans;
}

//Разность дробей
fraction fraction::operator-(fraction a) {
  fraction ans;

  int common_denominator = this->denominator * a.denominator /
    get_gcd(this->denominator, a.denominator);

  ans.numerator = this->numerator * (common_denominator / this->denominator) -
    a.numerator * (common_denominator / a.denominator);

  ans.denominator = common_denominator;

  ans.reduction();
  return ans;
}

//Произведение дробей
fraction fraction::operator*(fraction a) {
  fraction ans;
  int gcd1 = get_gcd(this->numerator, a.denominator);
  int gcd2 = get_gcd(this->denominator, a.numerator);

  ans.numerator = (this->numerator / gcd1) * (a.numerator / gcd2);
  ans.denominator = (this->denominator / gcd2) * (a.denominator / gcd1);

  ans.reduction();
  return ans;
}

//Деление дробь
fraction fraction::operator/(fraction a) {
  int c = a.numerator;
  a.numerator = a.denominator;
  a.denominator = c;
  fraction b;

  b.numerator = this->numerator;
  b.denominator = this->denominator;

  b = b * a;
  return b;
}

//Ввод дроби
std::ostream& operator<<(std::ostream& out, fraction OutFraction) {
  out << OutFraction.Get_numerator();

  if (OutFraction.Get_denominator() != 1) {
    out << "/" << OutFraction.Get_denominator();
  }

  return out;
}

//Вывод дроби
std::istream& operator>>(std::istream& in, fraction& InFraction) {
  std::string str;
  in >> str;

  int InType = 0;
  bool negative = 0;

  for (int i = 0; i < str.size(); i++) {
    switch (str[i]) {
    case '/':
      InType = 1;
      break;

    case '.':
      InType = 2;
      break;
    case '-':
      negative = 1 - negative;
      break;
    default:
      break;
    }
  }

  int numerator = 0;
  int denominator = 0;

  if (InType == 0) {
    denominator = 1;
    for (int i = 0; i < str.size(); i++) {
      if (str[i] == '-') {
        continue;
      }
      else {
        numerator = numerator * 10 + int(str[i] - '0');
      }
    }
  }

  if (InType == 1) {
    bool f = 0;

    for (int i = 0; i < str.size(); i++) {
      if (str[i] == '-') {
        continue;
      }
      else if (str[i] == '/') {
        f = 1;
      }
      else {
        if (!f) {
          numerator = numerator * 10 + int(str[i] - '0');
        }
        else {
          denominator = denominator * 10 + int(str[i] - '0');
        }
      }
    }
  }

  if (InType == 2) {
    bool f = 0;
    denominator = 1;

    for (int i = 0; i < str.size(); i++) {
      if (str[i] == '-') {
        continue;
      }
      else if (str[i] == '.') {
        f = 1;
      }
      else {
        numerator = numerator * 10 + int(str[i] - '0');
        if (f) denominator *= 10;
      }
    }
  }

  InFraction = fraction(numerator * (1 - ((negative == 1) * 2)), denominator);
  InFraction.reduction();

  return in;
}

bool fraction::zero()
{
  if (this->numerator == 0) return 1;
  return 0;
}

// НОК
int fraction::get_gcd(int a, int b) {
  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (a && b) {
    if (a > b) {
      a %= b;
    }
    else {
      b %= a;
    }
  }

  if (a > b) {
    return a;
  }
  else {
    return b;
  }
}
