#include <cstddef>
#include <memory>
#include <utility>

template <typename T>
struct Allocator {
  T* buf = nullptr;
  size_t cp = 0;

  static T* Allocate(size_t n) {
    return static_cast<T*>(operator new(sizeof(T) * n));
  }

  static void Deallocate(T* buf) {
    operator delete(buf);
  }

  Allocator() = default;
  Allocator(size_t n) {
    buf = Allocate(n);
    cp = n;
  }

  void Swap(Allocator& other) {
    std::swap(buf, other.buf);
    std::swap(cp, other.cp);
  }

  Allocator(const Allocator& other) = delete;
  Allocator(Allocator&& other) {
    Swap(other);
  }

  Allocator& operator = (const Allocator& other) = delete;
  Allocator& operator = (Allocator&& other) {
    Swap(other);
    return *this;
  }

  T* operator + (size_t index) {
    return buf + index;
  }
  const T* operator + (size_t index) const {
    return buf + index;
  }

  T& operator [] (size_t index) {
    return buf[index];
  }
  const T& operator [] (size_t index) const {
    return buf[index];
  }

  ~Allocator() {
    Deallocate(buf);
  }
};

template <typename T>
class Vector {
public:
  Vector() = default;
  Vector(size_t n);
  Vector(const Vector& other);
  Vector(Vector&& other);

  ~Vector();

  Vector& operator = (const Vector& other);
  Vector& operator = (Vector&& other) noexcept;

  void Reserve(size_t n);

  void Resize(size_t n);

  void PushBack(const T& elem);
  void PushBack(T&& elem);

  template <typename ... Args>
  T& EmplaceBack(Args&&... args);

  void PopBack();

  size_t Size() const noexcept;

  size_t Capacity() const noexcept;

  void Swap(Vector& other);

  const T& operator[](size_t i) const;
  T& operator[](size_t i);

  // В данной части задачи реализуйте дополнительно эти функции:
  using iterator = T*;
  using const_iterator = const T*;

  iterator begin() noexcept;
  iterator end() noexcept;

  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  // Тут должна быть такая же реализация, как и для константных версий begin/end
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // Вставляет элемент перед pos
  // Возвращает итератор на вставленный элемент
  iterator Insert(const_iterator pos, const T& elem);
  iterator Insert(const_iterator pos, T&& elem);

  // Конструирует элемент по заданным аргументам конструктора перед pos
  // Возвращает итератор на вставленный элемент
  template <typename ... Args>
  iterator Emplace(const_iterator it, Args&&... args);

  // Удаляет элемент на позиции pos
  // Возвращает итератор на элемент, следующий за удалённым
  iterator Erase(const_iterator it);

private:
  Allocator<T> data;
  size_t sz = 0;
};


template<typename T>
Vector<T>::Vector(size_t n) : data(n) {
  std::uninitialized_value_construct_n(data.buf, n);
  sz = n;
}

template<typename T>
Vector<T>::Vector(const Vector& other) : data(other.sz) {
  std::uninitialized_copy_n(other.data.buf, other.sz, data.buf);
  sz = other.sz;
}

template<typename T>
Vector<T>::Vector(Vector&& other) {
  Swap(other);
}

template<typename T>
Vector<T>::~Vector() {
  std::destroy_n(data.buf, sz);
}

template<typename T>
Vector<T>& Vector<T>::operator = (const Vector& other) {
  if (this == &other) return *this;
  if (other.sz > data.cp) {
    Vector<T> tmp(other);
    Swap(tmp);
  }
  else {
    for (size_t i = 0; i < sz && i < other.sz; ++i) {
      data[i] = other[i];
    }
    if (sz > other.sz) {
      std::destroy_n(data.buf + other.sz, sz - other.sz);
    }
    else if (sz < other.sz) {
      std::uninitialized_copy_n(
        other.data.buf + sz, other.sz - sz, data.buf + sz
      );
    }
  }
  sz = other.sz;
  return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator = (Vector&& other) noexcept {
  Swap(other);
  return *this;
}

template<typename T>
void Vector<T>::Reserve(size_t n) {
  if (n > data.cp) {
    Allocator<T> tmp(n);
    std::uninitialized_move_n(data.buf, sz, tmp.buf);
    std::destroy_n(data.buf, sz);
    data.Swap(tmp);
  }
}

template<typename T>
void Vector<T>::Resize(size_t n) {
  Reserve(n);
  if (n < sz) {
    std::destroy_n(data.buf + n, sz - n);
  }
  else if (sz < n) {
    std::uninitialized_value_construct_n(
      data.buf + sz, n - sz
    );
  }
  sz = n;
}

template<typename T>
void Vector<T>::PushBack(const T& elem) {
  if (data.cp == sz) {
    Reserve(sz == 0 ? 1 : sz * 2);
  }
  new (data + sz) T(elem);
  ++sz;
}

template<typename T>
void Vector<T>::PushBack(T&& elem) {
  if (data.cp == sz) {
    Reserve(sz == 0 ? 1 : sz * 2);
  }
  new (data + sz) T(std::move(elem));
  ++sz;
}

template<typename T>
template <typename ... Args>
T& Vector<T>::EmplaceBack(Args&&... args) {
  if (data.cp == sz) {
    Reserve(sz == 0 ? 1 : sz * 2);
  }
  auto last = new (data + sz) T(std::forward<Args>(args)...);
  ++sz;
  return *last;
}

template<typename T>
void Vector<T>::PopBack() {
  std::destroy_at(data + sz - 1);
  sz--;
}

template<typename T>
size_t Vector<T>::Size() const noexcept {
  return sz;
}

template<typename T>
size_t Vector<T>::Capacity() const noexcept {
  return data.cp;
}

template<typename T>
void Vector<T>::Swap(Vector& other) {
  data.Swap(other.data);
  std::swap(sz, other.sz);
}

template<typename T>
const T& Vector<T>::operator[](size_t i) const {
  return data[i];
}

template<typename T>
T& Vector<T>::operator[](size_t i) {
  return data[i];
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
  return data.buf;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
  return data + sz;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept {
  return data.buf;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept {
  return data + sz;
}

// Тут должна быть такая же реализация, как и для константных версий begin/end
template<typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept {
  return data.buf;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept {
  return data + sz;
}

// Вставляет элемент перед pos
// Возвращает итератор на вставленный элемент
template<typename T>
typename Vector<T>::iterator Vector<T>::Insert(const_iterator pos, const T& elem) {
  if (sz == 0) {
    PushBack(elem);
    return begin();
  }
  const size_t pos_i = pos - cbegin();
  if (sz == data.cp) {
    Allocator<T> tmp(sz == 0 ? 1 : sz * 2);
    std::uninitialized_move_n(data.buf, pos_i, tmp.buf);
    std::destroy_n(data.buf, pos_i);
    new (tmp + pos_i) T(elem);
    std::uninitialized_move_n(data + pos_i, sz - pos_i, tmp + pos_i + 1);
    std::destroy_n(data + pos_i, sz - pos_i);
    data.Swap(tmp);
    sz++;
    return data + pos_i;
  }
  else {
    for (auto i = end() - 1; i >= pos; --i) {
      std::uninitialized_move_n(i, 1, i + 1);
      std::destroy_at(i);
    }
    sz++;
    new (data + pos_i) T(elem);
    return data + pos_i;
  }
}

template<typename T>
typename Vector<T>::iterator Vector<T>::Insert(const_iterator pos, T&& elem) {
  if (sz == 0) {
    PushBack(std::move(elem));
    return begin();
  }
  const size_t pos_i = pos - cbegin();
  if (sz == data.cp) {
    Allocator<T> tmp(sz == 0 ? 1 : sz * 2);
    std::uninitialized_move_n(data.buf, pos_i, tmp.buf);
    std::destroy_n(data.buf, pos_i);
    new (tmp + pos_i) T(std::move(elem));
    std::uninitialized_move_n(data + pos_i, sz - pos_i, tmp + pos_i + 1);
    std::destroy_n(data + pos_i, sz - pos_i);
    data.Swap(tmp);
    sz++;
    return data + pos_i;
  }
  else {
    for (auto i = end() - 1; i >= pos; --i) {
      std::uninitialized_move_n(i, 1, i + 1);
      std::destroy_at(i);
    }
    sz++;
    new (data + pos_i) T(std::move(elem));
    return data + pos_i;
  }
}

// Конструирует элемент по заданным аргументам конструктора перед pos
// Возвращает итератор на вставленный элемент
template<typename T>
template <typename ... Args>
typename Vector<T>::iterator Vector<T>::Emplace(const_iterator pos, Args&&... args) {
  return Insert(pos, T(std::forward<Args>(args)...));
}

// Удаляет элемент на позиции pos
// Возвращает итератор на элемент, следующий за удалённым
template<typename T>
typename Vector<T>::iterator Vector<T>::Erase(const_iterator pos) {
  size_t pos_i = pos - cbegin();
  std::destroy_at(pos);
  for (auto i = data + pos_i + 1; i < end(); ++i) {
    std::uninitialized_move_n(i, 1, i - 1);
    std::destroy_at(i);
  }
  sz--;
  return data + pos_i;
}