#include <cstddef>
#include <memory>
#include <utility>

template <typename T>
struct Allocator {
  T* buf = nullptr;
  size_t cp = 0;

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

  static T* Allocate(size_t n) {
    return static_cast<T*>(operator new(sizeof(T) * n));
  }

  static void Deallocate(T* buf) {
    operator delete(buf);
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
