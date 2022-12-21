#include <iostream>


// �����
class fraction {
  friend std::istream& operator>>(std::istream&, fraction&);
  friend std::ostream& operator<<(std::ostream&, fraction);
public:
  fraction();
  fraction(int numerator, int denominator);
  ~fraction();

  fraction operator+(fraction a);
  fraction operator-(fraction b);
  fraction operator*(fraction b);
  fraction operator/(fraction b);

  int Get_numerator();
  int Get_denominator();

  bool zero();


private:
  int get_gcd(int, int);
  // ���������� �����
  void reduction();
  // ���������
  int numerator;
  // �����������
  int denominator;
};
