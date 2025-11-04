#include <cassert>
#include <cstdint>
#include <iostream>

class IPv4 {
public:
  friend auto &operator>>(std::istream &stream, IPv4 &ipv4) {
    std::size_t comp_1 = 0, comp_2 = 0, comp_3 = 0, comp_4 = 0;
    stream >> comp_1;
    stream.ignore();
    stream >> comp_2;
    stream.ignore();
    stream >> comp_3;
    stream.ignore();
    stream >> comp_4;
    assert(comp_1 < 256 && comp_2 < 256 && comp_3 < 256 && comp_4 < 256);
    ipv4.m_comp_1 = static_cast<std::uint8_t>(comp_1);
    ipv4.m_comp_2 = static_cast<std::uint8_t>(comp_2);
    ipv4.m_comp_3 = static_cast<std::uint8_t>(comp_3);
    ipv4.m_comp_4 = static_cast<std::uint8_t>(comp_4);
    return stream;
  }

  friend auto &operator<<(std::ostream &stream, IPv4 const &ipv4) {
    return stream << static_cast<int>(ipv4.m_comp_1) << '.'
                  << static_cast<int>(ipv4.m_comp_2) << '.'
                  << static_cast<int>(ipv4.m_comp_3) << '.'
                  << static_cast<int>(ipv4.m_comp_4) << '\n';
  }

  auto const operator++(int) {
    auto x = *this;
    if (m_comp_4 < 255) {
      m_comp_4++;
    } else if (m_comp_3 < 255) {
      m_comp_3++;
      m_comp_4 = 0;
    } else if (m_comp_2 < 255) {
      m_comp_2++;
      m_comp_4 = 0;
      m_comp_3 = 0;
    } else if (m_comp_1 < 255) {
      m_comp_1++;
      m_comp_4 = 0;
      m_comp_3 = 0;
      m_comp_2 = 0;
    } else {
      std::cout << "address is already 255.255.255.255\n";
    }
    return x;
  }

  auto const operator--(int) {
    auto x = *this;
    if (m_comp_4 != 0) {
      m_comp_4--;
    } else if (m_comp_3 != 0) {
      m_comp_3--;
      m_comp_4 = 255;
    } else if (m_comp_2 != 0) {
      m_comp_2--;
      m_comp_4 = 255;
      m_comp_3 = 255;
    } else if (m_comp_1 != 0) {
      m_comp_1--;
      m_comp_4 = 255;
      m_comp_3 = 255;
      m_comp_2 = 255;
    } else {
      std::cout << "address is already 0.0.0.0\n";
    }
    return x;
  }

  auto &operator++() {
    if (m_comp_4 < 255) {
      m_comp_4++;
    } else if (m_comp_3 < 255) {
      m_comp_3++;
      m_comp_4 = 0;
    } else if (m_comp_2 < 255) {
      m_comp_2++;
      m_comp_4 = 0;
      m_comp_3 = 0;
    } else if (m_comp_1 < 255) {
      m_comp_1++;
      m_comp_4 = 0;
      m_comp_3 = 0;
      m_comp_2 = 0;
    } else {
      std::cout << "address is already 255.255.255.255\n";
    }
    return *this;
  }

  auto &operator--() {
    if (m_comp_4 != 0) {
      m_comp_4--;
    } else if (m_comp_3 != 0) {
      m_comp_3--;
      m_comp_4 = 255;
    } else if (m_comp_2 != 0) {
      m_comp_2--;
      m_comp_4 = 255;
      m_comp_3 = 255;
    } else if (m_comp_1 != 0) {
      m_comp_1--;
      m_comp_4 = 255;
      m_comp_3 = 255;
      m_comp_2 = 255;
    } else {
      std::cout << "address is already 0.0.0.0\n";
    }
    return *this;
  }

private:
  std::uint8_t m_comp_1 = 0;
  std::uint8_t m_comp_2 = 0;
  std::uint8_t m_comp_3 = 0;
  std::uint8_t m_comp_4 = 0;
};

int main() {
  IPv4 ipv4;
  std::cin >> ipv4;
  std::cout << ipv4;

  std::cout << ipv4++;
  std::cout << ipv4;
  std::cout << ++ipv4;
  std::cout << ipv4;

  return 0;
}
