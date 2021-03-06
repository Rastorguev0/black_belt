#include "object.h"
#include "statement.h"

#include <sstream>
#include <string_view>
#include <cassert>

using namespace std;

namespace Runtime {

void ClassInstance::Print(std::ostream& os) {
  if (HasMethod("__str__", 0)) {
    Call("__str__", {})->Print(os);
  }
  else os << this;
}

bool ClassInstance::HasMethod(const std::string& method, size_t argument_count) const {
  if (auto m = cls.GetMethod(method)) {
    if (m->formal_params.size() == argument_count) return true;
  }
  return false;
}

const Closure& ClassInstance::Fields() const {
  return fields;
}

Closure& ClassInstance::Fields() {
  return fields;
}

ClassInstance::ClassInstance(const Class& cls)
  : cls(cls) {
  fields["self"] = ObjectHolder::Share(*this);
}

ObjectHolder ClassInstance::Call(const std::string& method, const std::vector<ObjectHolder>& actual_args) {
  if (!HasMethod(method, actual_args.size())) throw runtime_error("Clas Instance::Call");
  else {
    auto m = cls.GetMethod(method);
    Closure closure = Fields();
    for (size_t i = 0; i < actual_args.size(); ++i) {
      closure[m->formal_params[i]] = actual_args[i];
    }
    return m->body->Execute(closure);
  }
}

Class::Class(std::string name, std::vector<Method> methods, const Class* parent)
  : name(move(name)), parent(parent) {
  for (auto&& m : methods) {
    own_methods[m.name] = move(m);
  }
}

const Method* Class::GetMethod(const std::string& name) const {
  if (own_methods.count(name)) return &own_methods.at(name);
  else if (parent) {
    if (auto m = parent->GetMethod(name)) return m;
  }
  return nullptr;
}

void Class::Print(ostream& os) {
  os << name;
}

const std::string& Class::GetName() const {
  return name;
}

void Bool::Print(std::ostream& os) {
  os << (GetValue() ? "True" : "False");
}

bool Bool::IsTrue() const {
  return GetValue();
}

template<>
bool ValueObject<int>::IsTrue() const {
  return value;
}

template<>
bool ValueObject<string>::IsTrue() const {
  return value.size() != 0;
}

template<>
bool ValueObject<bool>::IsTrue() const {
  return value;
}

bool Object::IsTrue() const {
  return true;
}

} /* namespace Runtime */
