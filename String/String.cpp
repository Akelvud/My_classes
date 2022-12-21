#include "String.h"

class String
{
  friend std::istream& operator>>(std::istream&, String&);
  friend std::ostream& operator<<(std::ostream&, const String&);

public:
  String(const char* = '\0');
  String(const String&);
  ~String();

  String operator=(String);
  char& operator[](int);
  String operator+(String);
  String& operator+=(String);
  bool operator==(String);
  bool operator!=(String);
  bool operator!();
  String operator()(int, int);

private:
  char* ptr;
  int size = 0;

};
