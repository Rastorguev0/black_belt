#include "statement.h"
#include "object.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace Ast {

  using Runtime::Closure;

  ObjectHolder Assignment::Execute(Closure& closure) {
    return closure[var_name] = right_value->Execute(closure);
  }

  Assignment::Assignment(std::string var, std::unique_ptr<Statement> rv)
    : var_name(move(var)), right_value(move(rv)) {}

  VariableValue::VariableValue(std::string var_name) {
    dotted_ids.push_back(move(var_name));
  }

  VariableValue::VariableValue(std::vector<std::string> dotted_ids)
    : dotted_ids(move(dotted_ids)) {}

  ObjectHolder VariableValue::Execute(Closure& closure) {
    if (!closure.count(dotted_ids[0])) throw runtime_error("Variable unknown");
    ObjectHolder target_obj = closure[dotted_ids[0]];
    for (auto it = dotted_ids.begin() + 1; it < dotted_ids.end(); ++it) {
      target_obj = target_obj.TryAs<Runtime::ClassInstance>()->Fields()[*it];
    }
    return target_obj;
  }

  unique_ptr<Print> Print::Variable(std::string var) {
    return make_unique<Print>(make_unique<VariableValue>(move(var)));
  }

  Print::Print(unique_ptr<Statement> argument) {
    args.push_back(move(argument));
  }

  Print::Print(vector<unique_ptr<Statement>> args)
    : args(move(args)) {}

  ObjectHolder Print::Execute(Closure& closure) {
    bool first = true;
    for (const auto& state : args) {
      if (!first) *output << ' ';
      first = false;
      auto o = state->Execute(closure);
      if (o) o->Print(*output);
      else *output << "None";
    }
    *output << endl;
    return ObjectHolder::None();
  }

  ostream* Print::output = &cout;

  void Print::SetOutputStream(ostream& output_stream) {
    output = &output_stream;
  }

  MethodCall::MethodCall(
    std::unique_ptr<Statement> object,
    std::string method,
    std::vector<std::unique_ptr<Statement>> args)
    : object(move(object)), method(move(method)), args(move(args)) {}

  ObjectHolder MethodCall::Execute(Closure& closure) {
    vector<ObjectHolder> actual_args;
    for (const auto& arg : args) {
      actual_args.push_back(arg->Execute(closure));
    }
    return object->Execute(closure).TryAs<Runtime::ClassInstance>()->Call(method, actual_args);
  }

  ObjectHolder Stringify::Execute(Closure& closure) {
    ostringstream os;
    auto o = argument->Execute(closure);
    if (o) o->Print(os);
    else os << "None";
    return ObjectHolder::Own(Runtime::String{ os.str() });
  }

  ObjectHolder Add::Execute(Closure& closure) {
    using namespace Runtime;
    auto _lhs = lhs->Execute(closure);
    auto _rhs = rhs->Execute(closure);
    if (_lhs.TryAs<ClassInstance>()) {
      if (_lhs.TryAs<ClassInstance>()->HasMethod("__add__", 1)) {
        return _lhs.TryAs<ClassInstance>()->Call("__add__", { ObjectHolder::Share(*_rhs) });
      }
      else throw runtime_error("Add::Execute");
    }
    else {
      if (_lhs.TryAs<String>() && _rhs.TryAs<String>()) {
        return ObjectHolder::Own(Runtime::String{
          _lhs.TryAs<String>()->GetValue() + _rhs.TryAs<String>()->GetValue()
          });
      }
      else {
        if (_lhs.TryAs<Number>() && _rhs.TryAs<Number>()) {
          return ObjectHolder::Own(Runtime::Number{
            _lhs.TryAs<Number>()->GetValue() + _rhs.TryAs<Number>()->GetValue()
            });
        }
        else throw runtime_error("Add::Execute");
      }
    }
  }

  ObjectHolder Sub::Execute(Closure& closure) {
    auto l = lhs->Execute(closure);
    auto r = rhs->Execute(closure);
    if (l.TryAs<Runtime::Number>() && r.TryAs<Runtime::Number>()) {
      return ObjectHolder::Own(Runtime::Number{
        l.TryAs<Runtime::Number>()->GetValue() - r.TryAs<Runtime::Number>()->GetValue()
        });
    }
    else throw runtime_error("Sub::Execute");
  }

  ObjectHolder Mult::Execute(Runtime::Closure& closure) {
    auto l = lhs->Execute(closure);
    auto r = rhs->Execute(closure);
    if (l.TryAs<Runtime::Number>() && r.TryAs<Runtime::Number>()) {
      return ObjectHolder::Own(Runtime::Number{
        l.TryAs<Runtime::Number>()->GetValue() * r.TryAs<Runtime::Number>()->GetValue()
        });
    }
    else throw runtime_error("Mult::Execute");
  }

  ObjectHolder Div::Execute(Runtime::Closure& closure) {
    auto l = lhs->Execute(closure);
    auto r = rhs->Execute(closure);
    if (l.TryAs<Runtime::Number>() && r.TryAs<Runtime::Number>()) {
      return ObjectHolder::Own(Runtime::Number{
        l.TryAs<Runtime::Number>()->GetValue() / r.TryAs<Runtime::Number>()->GetValue()
        });
    }
    else throw runtime_error("Div::Execute");
  }

  ObjectHolder Compound::Execute(Closure& closure) {
    for (const auto& stmt : statements) {
      if (dynamic_cast<Return*>(stmt.get())) {
        return stmt->Execute(closure);
      }
      auto result = stmt->Execute(closure);
      if (dynamic_cast<IfElse*>(stmt.get())) {
        if (result) return result;
      }
    }
    return ObjectHolder::None();
  }

  ObjectHolder Return::Execute(Closure& closure) {
    return statement->Execute(closure);
  }

  ClassDefinition::ClassDefinition(ObjectHolder class_)
    : cls(move(class_)), class_name(cls.TryAs<Runtime::Class>()->GetName()) {}

  ObjectHolder ClassDefinition::Execute(Runtime::Closure& closure) {
    return ObjectHolder::None();
  }

  FieldAssignment::FieldAssignment(
    VariableValue object, std::string field_name, std::unique_ptr<Statement> rv)
    : object(std::move(object)), field_name(std::move(field_name)), right_value(std::move(rv)) {}

  ObjectHolder FieldAssignment::Execute(Runtime::Closure& closure) {
    return object.Execute(closure).TryAs<Runtime::ClassInstance>()->Fields()[field_name]
      = right_value->Execute(closure);
  }

  IfElse::IfElse(
    std::unique_ptr<Statement> condition,
    std::unique_ptr<Statement> if_body,
    std::unique_ptr<Statement> else_body)
    : condition(move(condition)), if_body(move(if_body)), else_body(move(else_body)) {}

  ObjectHolder IfElse::Execute(Runtime::Closure& closure) {
    if (IsTrue(condition->Execute(closure))) {
      if (if_body)
        return if_body->Execute(closure);
    }
    else {
      if (else_body)
        return else_body->Execute(closure);
    }
    return ObjectHolder::None();
  }

  ObjectHolder Or::Execute(Runtime::Closure& closure) {
    return ObjectHolder::Own(Runtime::Bool{
      IsTrue(lhs->Execute(closure)) || IsTrue(rhs->Execute(closure))
      });
  }

  ObjectHolder And::Execute(Runtime::Closure& closure) {
    return ObjectHolder::Own(Runtime::Bool{
      IsTrue(lhs->Execute(closure)) && IsTrue(rhs->Execute(closure))
      });
  }

  ObjectHolder Not::Execute(Runtime::Closure& closure) {
    return ObjectHolder::Own(Runtime::Bool{ !IsTrue(argument->Execute(closure)) });
  }

  Comparison::Comparison(
    Comparator cmp, unique_ptr<Statement> lhs, unique_ptr<Statement> rhs
  ) : comparator(cmp), left(move(lhs)), right(move(rhs)) {
  }

  ObjectHolder Comparison::Execute(Runtime::Closure& closure) {
    return ObjectHolder::Own(Runtime::Bool{
      comparator(left->Execute(closure), right->Execute(closure)) }
    );
  }

  NewInstance::NewInstance(
    const Runtime::Class& class_, std::vector<std::unique_ptr<Statement>> args
  ) : class_(class_), args(std::move(args)) {}

  NewInstance::NewInstance(const Runtime::Class& class_) : NewInstance(class_, {}) {}

  ObjectHolder NewInstance::Execute(Runtime::Closure& closure) {
    auto* new_instance = new Runtime::ClassInstance(class_);
    if (new_instance->HasMethod("__init__", args.size())) {
      std::vector<ObjectHolder> actual_args;
      for (const auto& statement : args) {
        actual_args.push_back(statement->Execute(closure));
      }
      new_instance->Call("__init__", actual_args);
    }

    return ObjectHolder::Share(*new_instance);
  }


} /* namespace Ast */

/*
ObjectHolder inst_class = ObjectHolder::Own(Runtime::ClassInstance{ class_ });
    if (inst_class.TryAs<Runtime::ClassInstance>()->HasMethod("__init__", args.size())) {
      vector<ObjectHolder> actual_args;
      for (const auto& arg : args) {
        actual_args.push_back(arg->Execute(closure));
      }
      inst_class.TryAs<Runtime::ClassInstance>()->Call("__init__", actual_args);
    }
    return inst_class;
*/
