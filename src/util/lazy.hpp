#pragma once

#include <utility>

template <typename T>
struct lazy final {

  private:
    char buff[sizeof(T)];

  public:
    template <typename... Args>
    void emplace(Args&&... args) noexcept
    {
        new (reinterpret_cast<void*>(buff)) T{std::forward<Args>(args)...};
    }
    T value() noexcept
    {
        return *reinterpret_cast<T*>(buff);
    }
    T& ref() noexcept
    {
        return *reinterpret_cast<T*>(buff);
    }

    ~lazy()
    {
        reinterpret_cast<T*>(buff)->~T();
    }
};
