#include "yellow_pages.h"

#include <algorithm>
#include <tuple>
#include <set>

namespace YellowPages {

  bool operator < (const Name& lhs, const Name& rhs) {
    return make_tuple(lhs.value(), lhs.type()) < make_tuple(rhs.value(), rhs.type());
  }

  bool operator < (const Phone& lhs, const Phone& rhs) {
    return
      make_tuple(lhs.formatted(), lhs.type(), lhs.country_code(), lhs.local_code(),
        lhs.number(), lhs.extension(), lhs.description())
      <
      make_tuple(rhs.formatted(), rhs.type(), lhs.country_code(), rhs.local_code(),
        rhs.number(), rhs.extension(), rhs.description());
  }

  bool operator < (const Url& lhs, const Url& rhs) {
    return lhs.value() < rhs.value();
  }


  Company Merge(const Signals& signals_, const Providers& providers) {
    if (signals_.empty()) return Company();

    Signals signals(signals_);
    std::sort(signals.begin(), signals.end(),
      [&providers](const Signal& lhs, const Signal& rhs) {
        return providers.at(lhs.provider_id()).priority() > providers.at(rhs.provider_id()).priority();
      });

    Company result;
    auto get_priority = [&providers](const Signal& s) { return providers.at(s.provider_id()).priority(); };

    //ADD ADDRESS
    auto address_signal = std::find_if(
      signals.begin(), signals.end(), [](const Signal& s) {return s.company().has_address(); }
    );
    if (address_signal != signals.end()) {
      *result.mutable_address() = address_signal->company().address();
    }

    //ADD NAMES
    std::set<Name> names_set;
    auto names_begin = std::find_if(
      signals.begin(), signals.end(), [](const Signal& s) { return s.company().names_size() > 0; }
    );
    for (auto it = names_begin; it != signals.end() && get_priority(*it) == get_priority(*names_begin); ++it) {
      for (const auto& name : it->company().names()) {
        if (!names_set.count(name)) {
          auto res_name = result.add_names();
          *res_name = name;
          names_set.insert(name);
        }
      }
    }

    //ADD PHONES
    std::set<Phone> phones_set;
    auto phones_begin = std::find_if(
      signals.begin(), signals.end(), [](const Signal& s) { return s.company().phones_size() > 0; }
    );
    for (auto it = phones_begin; it != signals.end() && get_priority(*it) == get_priority(*phones_begin); ++it) {
      for (const auto& phone : it->company().phones()) {
        if (!phones_set.count(phone)) {
          auto res_phone = result.add_phones();
          *res_phone = phone;
          phones_set.insert(phone);
        }
      }
    }

    //ADD URLS
    std::set<Url> urls_set;
    auto urls_begin = std::find_if(
      signals.begin(), signals.end(), [](const Signal& s) { return s.company().urls_size() > 0; }
    );
    for (auto it = urls_begin; it != signals.end() && get_priority(*it) == get_priority(*urls_begin); ++it) {
      for (const auto& url : it->company().urls()) {
        if (!urls_set.count(url)) {
          auto res_url = result.add_urls();
          *res_url = url;
          urls_set.insert(url);
        }
      }
    }

    //ADD WORKING TIME
    auto time_signal = std::find_if(
      signals.begin(), signals.end(), [](const Signal& s) {return s.company().has_working_time(); }
    );
    if (time_signal != signals.end()) {
      *result.mutable_working_time() = time_signal->company().working_time();
    }

    return result;
  }

}
