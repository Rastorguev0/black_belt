#include <map>
#include <iostream>
#include <string>
#include <vector>

// Serialization

template <typename T>
void Serialize(T pod, std::ostream& out);

void Serialize(const std::string& str, std::ostream& out);

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out);

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);

template <typename T>
void Serialize(T pod, std::ostream& out) {
  out.write(reinterpret_cast<const char*>(&pod), sizeof(pod));
}

void Serialize(const std::string& str, std::ostream& out) {
  Serialize(str.size(), out);
  out.write(str.c_str(), str.size());
}

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out) {
  Serialize(data.size(), out);
  for (const auto& item : data) {
    Serialize(item, out);
  }
}

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out) {
  Serialize(data.size(), out);
  for (const auto& [key, value] : data) {
    Serialize(key, out);
    Serialize(value, out);
  }
}


// Deserialization

template <typename T>
void Deserialize(std::istream& in, T& pod);

void Deserialize(std::istream& in, std::string& str);

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data);

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);

template <typename T>
void Deserialize(std::istream& in, T& pod) {
  in.read(reinterpret_cast<char*>(&pod), sizeof(pod));
}

void Deserialize(std::istream& in, std::string& str) {
  size_t size = 0;
  Deserialize(in, size);
  str = std::string(size, ' ');
  in.read(str.data(), size);
}

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data) {
  size_t size = 0;
  Deserialize(in, size);
  data.reserve(size);
  for (size_t  i = 0; i < size; ++i) {
    T tmp{};
    Deserialize(in, tmp);
    data.push_back(std::move(tmp));
  }
}

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data) {
  size_t size = 0;
  Deserialize(in, size);
  for (size_t i = 0; i < size; ++i) {
    T1 tmp_key{};
    T2 tmp_value{};
    Deserialize(in, tmp_key);
    Deserialize(in, tmp_value);
    data[std::move(tmp_key)] = std::move(tmp_value);
  }
}
