#include "test_runner.h"

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <stack>
#include <string>
#include <variant>

using namespace std;

class Void {};
class Null {};

template<typename Parent>
class Object;

template<typename Parent>
class Array;

template<typename Parent>
class Value;


void Print(ostream& out, int64_t number) {
  out << number;
}

void Print(ostream& out, string_view str) {
  out << "\"";
  for (const auto s : str) {
    if (s == '\"' || s == '\\') out << '\\';
      out << s;
  }
  out << "\"";
}

void Print(ostream& out, bool b) {
  out << boolalpha << b;
}

void Print(ostream& out, Null null) {
  out << "null";
}

void PrintComma(ostream& out, bool& dont_divide) {
  if (!dont_divide) out << ",";
  dont_divide = false;
}

void PrintJson(ostream& out, variant<int64_t, string_view, bool, Null> object, bool& dont_divide) {
  PrintComma(out, dont_divide);
  visit([&out](const auto& obj) {
    Print(out, obj);
    }, object);
}



template<typename Parent>
class Array {
public:
  Array(ostream& out, Parent* parent = nullptr) : output(out), parent(parent) {
    output << "[";
  };
  Array& Number(int64_t number) {
    PrintJson(output, number, empty);
    return *this;
  }
  Array& String(string_view str) {
    PrintJson(output, str, empty);
    return *this;
  }
  Array& Boolean(bool b) {
    PrintJson(output, b, empty);
    return *this;
  }
  Array& Null() {
    PrintJson(output, ::Null{}, empty);
    return *this;
  }
  Array<Array> BeginArray() {
    PrintComma(output, empty);
    return Array<Array>(output, this);
  }
  Parent& EndArray() {
    closed = true;
    output << "]"; 
    return *parent;
  }
  Object<Array> BeginObject() {
    PrintComma(output, empty);
    return Object<Array>(output, this);
  }
  ~Array() {
    if (!closed) EndArray();
  }
private:
  bool empty = true;
  bool closed = false;
  ostream& output;
  Parent* parent = nullptr;
};


template<typename Parent>
class Value {
public:
  Value(ostream& out, Object<Parent>* parent) : output(out), parent(parent) {};
  Object<Parent>& Number(int64_t number) {
    Print(output, number);
    used = true;
    return *parent;
  }
  Object<Parent>& String(string_view str) {
    Print(output, str);
    used = true;
    return *parent;
  }
  Object<Parent>& Boolean(bool b) {
    Print(output, b);
    used = true;
    return *parent;
  }
  Object<Parent>& Null() {
    Print(output, ::Null{});
    used = true;
    return *parent;
  }
  Array<Object<Parent>> BeginArray() {
    used = true;
    return Array<Object<Parent>>(output, parent);
  }
  Object<Object<Parent>> BeginObject() {
    used = true;
    return Object<Object<Parent>>(output, parent);
  }
  ~Value() {
    if (!used) Print(output, ::Null{});
  }
private:
  bool used = false;
  ostream& output;
  Object<Parent>* parent = nullptr;
};


template<typename Parent>
class Object {
public:
  Object(ostream& out, Parent* parent = nullptr) : output(out), parent(parent) {
    output << "{";
  }
  Value<Parent> Key(string_view str) {
    PrintComma(output, empty);
    Print(output, str);
    output << ":";
    return Value<Parent>{output, this};
  }
  Parent& EndObject() {
    closed = true;
    output << "}";
    return *parent;
  }
  ~Object() {
    if (!closed) EndObject();
  }
private:
  bool empty = true;
  bool closed = false;
  ostream& output;
  Parent* parent = nullptr;
};


void PrintJsonString(ostream& out, string_view str) {
  Print(out, str);
}

using ArrayContext = Array<Void>;  // Замените это объявление на определение типа ArrayContext
ArrayContext PrintJsonArray(ostream& out) {
  return ArrayContext{ out };
}

using ObjectContext = Object<Void>;  // Замените это объявление на определение типа ObjectContext
ObjectContext PrintJsonObject(ostream& out) {
  return ObjectContext{ out };
}


void TestArray() {
  ostringstream output;

  {
    auto json = PrintJsonArray(output);
    json
      .Number(5)
      .Number(6)
      .BeginArray()
        .Number(7)
      .EndArray()
      .Number(8)
      .String("bingo!");
  }

  ASSERT_EQUAL(output.str(), R"([5,6,[7],8,"bingo!"])");
}

void TestObject() {
  ostringstream output;

  {
    auto json = PrintJsonObject(output);
    json
      .Key("id1").Number(1234)
      .Key("id2").Boolean(false)
      .Key("").Null()
      .Key("\"").String("\\");
  }

  ASSERT_EQUAL(output.str(), R"({"id1":1234,"id2":false,"":null,"\\"":"\\"})");
}

void TestAutoClose() {
  ostringstream output;

  {
    auto json = PrintJsonArray(output);
    json.BeginArray().BeginObject();
  }

  ASSERT_EQUAL(output.str(), R"([[{}]])");
}

int main() {
  PrintJsonString(std::cout, "Hello, \"world\"");
  // "Hello, \"world\""

  cout << endl;
  PrintJsonArray(std::cout)
    .Null()
    .String("Hello")
    .Number(123)
    .Boolean(false)
    .EndArray();  // явное завершение массива
  // [null,"Hello",123,false]

  cout << endl;
  PrintJsonArray(std::cout)
    .Null()
    .String("Hello")
    .Number(123)
    .Boolean(false);
  // [null,"Hello",123,false]

  cout << endl;
  PrintJsonArray(std::cout)
    .String("Hello")
    .BeginArray()
    .String("World");
  // ["Hello",["World"]]

  cout << endl;
  PrintJsonObject(std::cout)
    .Key("foo")
    .BeginArray()
    .String("Hello")
    .EndArray()
    .Key("foo")  // повторяющиеся ключи допускаются
    .BeginObject()
    .Key("foo");  // закрытие объекта в таком состоянии допишет null в качестве значения
// {"foo":["Hello"],"foo":{"foo":null}}
  
  TestRunner tr;
  RUN_TEST(tr, TestArray);
  RUN_TEST(tr, TestObject);
  RUN_TEST(tr, TestAutoClose);
  return 0;
}
