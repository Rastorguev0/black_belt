#include "phone_book.h"
#include "contact.pb.h"
#include <algorithm>

using namespace std;

PhoneBook::PhoneBook(vector<Contact> contacts) {
  sort(contacts.begin(), contacts.end(),
    [](const Contact& lhs, const Contact& rhs) {
      return lhs.name < rhs.name;
    });

  book = move(contacts);
}

PhoneBook::ContactRange PhoneBook::FindByNamePrefix(string_view name_prefix) const {
  if (name_prefix.empty()) {
    return ContactRange{ book.begin(), book.end() };
  }
  else {
    struct Comp {
      bool operator() (const Contact& c, const string_view& v) const { return c.name.compare(0, v.size(), v) < 0; }
      bool operator() (const string_view& v, const Contact& c) const { return c.name.compare(0, v.size(), v) > 0; }
    };
    const auto range = equal_range(book.begin(), book.end(), name_prefix, Comp{});
    return ContactRange{range.first, range.second};
  }
}


auto BuildDate(const Date& d) {
  PhoneBookSerialize::Date result;
  result.set_day(d.day);
  result.set_month(d.month);
  result.set_year(d.year);
  return result;
}

auto BuildDate(const PhoneBookSerialize::Date& d) {
  return Date{
    .year = d.year(),
    .month = d.month(),
    .day = d.day()
  };
}

auto BuildContact(const Contact& c) {
  PhoneBookSerialize::Contact result;
  result.set_name(c.name);
  if (c.birthday) {
    *result.mutable_birthday() = BuildDate(c.birthday.value());
  }
  for (const auto& n : c.phones) {
    result.add_phone_number(n);
  }
  return result;
}

auto BuildContact(const PhoneBookSerialize::Contact& c) {
  Contact result;
  result.name = c.name();
  if (c.has_birthday()) {
    result.birthday = BuildDate(c.birthday());
  }
  for (const auto& n : c.phone_number()) {
    result.phones.push_back(n);
  }
  return result;
}


void PhoneBook::SaveTo(ostream& output) const {
  PhoneBookSerialize::ContactList list;
  for (const auto& c: book) {
    auto contact = list.add_contact();
    *contact = BuildContact(c);
  }
  list.SerializePartialToOstream(&output);
}

PhoneBook DeserializePhoneBook(istream& input) {
  PhoneBookSerialize::ContactList list;
  list.ParseFromIstream(&input);
  vector<Contact> parsed_contacts;
  for (const auto& contact : list.contact()) {
    parsed_contacts.push_back(BuildContact(contact));
  }
  return PhoneBook(move(parsed_contacts));
}