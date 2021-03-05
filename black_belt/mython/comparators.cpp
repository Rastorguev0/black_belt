#include "comparators.h"
#include "object.h"
#include "object_holder.h"

#include <functional>
#include <optional>
#include <sstream>

using namespace std;

namespace Runtime {

  bool Equal(ObjectHolder lhs, ObjectHolder rhs) {
    auto l = lhs.TryAs<Runtime::String>();
    auto r = rhs.TryAs<Runtime::String>();
    if (l && r) {
      return l->GetValue() == r->GetValue();
    }
    else {
      auto l = lhs.TryAs<Runtime::Number>();
      auto r = rhs.TryAs<Runtime::Number>();
      if (l && r) {
        return l->GetValue() == r->GetValue();
      }
      else throw runtime_error("");
    }
  }

  bool Less(ObjectHolder lhs, ObjectHolder rhs) {
    auto l = lhs.TryAs<Runtime::String>();
    auto r = rhs.TryAs<Runtime::String>();
    if (l && r) {
      return l->GetValue() < r->GetValue();
    }
    else {
      auto l = lhs.TryAs<Runtime::Number>();
      auto r = rhs.TryAs<Runtime::Number>();
      if (l && r) {
        return l->GetValue() < r->GetValue();
      }
      else throw runtime_error("");
    }
  }


} /* namespace Runtime */
