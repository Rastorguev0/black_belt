#pragma once

#include "iterator_range.h"

#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <iosfwd>

struct Date {
  int year, month, day;
};

struct Contact {
  std::string name;
  std::optional<Date> birthday;
  std::vector<std::string> phones;
};

class PhoneBook {
public:
  using ContactRange = IteratorRange<std::vector<Contact>::const_iterator>;
public:
  explicit PhoneBook(std::vector<Contact> contacts);

  ContactRange FindByNamePrefix(std::string_view name_prefix) const;

  void SaveTo(std::ostream& output) const;
private:
  std::vector<Contact> book;
};

PhoneBook DeserializePhoneBook(std::istream& input);