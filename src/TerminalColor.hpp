#ifndef TERMINALCOLOR_HPP
#define TERMINALCOLOR_HPP

#include <ostream>
#include <string>

struct RGB
{
    int red_;
    int green_;
    int blue_;
};

class TerminalColor
{
  protected:
    std::string esc_seq_;
    RGB rgb_;

    TerminalColor(const RGB& rgb) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const TerminalColor& obj);
};

class FGColor : public TerminalColor
{
    const std::string attr_ = "38";

  public:
    FGColor(const int r, const int g, const int b) noexcept;

    operator std::string() noexcept;
};

class BGColor : public TerminalColor
{
    const std::string attr_ = "48";

  public:
    BGColor(const int r, const int g, const int b) noexcept;

    operator std::string() noexcept;
};

#endif
