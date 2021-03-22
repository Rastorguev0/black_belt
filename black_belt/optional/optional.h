#include <utility>

// Исключение этого типа должно генерироваться при обращении к "пустому" Optional в функции Value
struct BadOptionalAccess {
};

template <typename T>
class Optional {
private:
  // alignas нужен для правильного выравнивания блока памяти
  alignas(T) unsigned char data[sizeof(T)];
  bool defined = false;

public:
  Optional() = default;
  Optional(const T& elem);
  Optional(T&& elem);
  Optional(const Optional& other);
  Optional(Optional&& other);

  Optional& operator=(const T& elem);
  Optional& operator=(T&& elem);
  Optional& operator=(const Optional& other);
  Optional& operator=(Optional&& other);

  bool HasValue() const;

  // Эти операторы не должны делать никаких проверок на пустоту.
  // Проверки остаются на совести программиста.
  T& operator*();
  const T& operator*() const;
  T* operator->();
  const T* operator->() const;

  // Генерирует исключение BadOptionalAccess, если объекта нет
  T& Value();
  const T& Value() const;

  void Reset();

  ~Optional();
};

template<typename T>
Optional<T>::Optional(const T& elem) {
  new (data) T(elem);
  defined = true;
}

template<typename T>
Optional<T>::Optional(T&& elem) {
  new (data) T(std::move(elem));
  defined = true;
}

template<typename T>
Optional<T>::Optional(const Optional& other) {
  *this = other;
}

template<typename T>
Optional<T>::Optional(Optional&& other) {
  *this = std::move(other);
}

template<typename T>
Optional<T>& Optional<T>::operator=(const T& elem) {
  if (defined) {
    (*this).operator*() = elem;
  }
  else {
    new (data) T(elem);
    defined = true;
  }
  return *this;
}

template<typename T>
Optional<T>& Optional<T>::operator=(T&& elem) {
  if (defined) {
    (*this).operator*() = elem;
  }
  else {
    new (data) T(std::move(elem));
    defined = true;
  }
  return *this;
}

template<typename T>
Optional<T>& Optional<T>::operator=(const Optional& other) {
  if (defined && other.defined) {
    (*this).operator*() = *other;
  }
  else if (defined) {
    (*this).operator*().~T();
  }
  else if (other.defined) {
    new (data) T{*other};
  }
  defined = other.defined;
  return *this;
}

template<typename T>
Optional<T>& Optional<T>::operator=(Optional&& other) {
  if (defined && other.defined) {
    (*this).operator*() = std::move(*other);
  }
  else if (defined) {
    (*this).operator*().~T();
  }
  else if (other.defined) {
    new (data) T{std::move(*other)};
  }
  defined = other.defined;
  return *this;
}

template<typename T>
bool Optional<T>::HasValue() const {
  return defined;
}

template<typename T>
T& Optional<T>::operator*() {
  return *reinterpret_cast<T*>(&data);
}

template<typename T>
const T& Optional<T>::operator*() const {
  return *reinterpret_cast<const T*>(&data);
}

template<typename T>
T* Optional<T>::operator->() {
  return reinterpret_cast<T*>(&data);
}

template<typename T>
const T* Optional<T>::operator->() const {
  return reinterpret_cast<const T*>(&data);
}

template<typename T>
T& Optional<T>::Value() {
  if (!defined) throw BadOptionalAccess{};
  return *reinterpret_cast<T*>(&data);
}

template<typename T>
const T& Optional<T>::Value() const {
  if (!defined) throw BadOptionalAccess{};
  return *reinterpret_cast<const T*>(&data);
}

template<typename T>
void Optional<T>::Reset() {
  if (defined) {
    reinterpret_cast<T*>(&data)->~T();
  }
  defined = false;
}

template<typename T>
Optional<T>::~Optional() {
  if (defined) {
    (*this).operator*().~T();
  }
  defined = false;
}