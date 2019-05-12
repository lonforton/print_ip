#include <iostream>
#include <type_traits>
#include <list>
#include <vector>

template <typename T>
struct is_char_type
{
  static bool const value = std::is_same<T, char>::value || std::is_same<T, unsigned char>::value;
};

template <typename T>
struct is_numeric_type
{
  static bool const value = !is_char_type<T>::value && std::is_arithmetic<T>::value;
};

template <typename T>
struct is_string_type
{
  static bool const value = std::is_same<T, std::string>::value;
};

template <typename T>
struct is_container_type
{
  static bool const value = false;
};

template <typename T, typename Alloc>
struct is_container_type<std::list<T, Alloc>>
{
  static bool const value = true;
};

template <typename T, typename Alloc>
struct is_container_type<std::vector<T, Alloc>>
{
  static bool const value = true;
};

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
  bool first = true;
  for (const auto &item : vec)
  {
    os << (!first ? "." : "") << static_cast<unsigned int>(item);
    first = false;
  }
  return os;
}

template <typename T>
std::vector<uint8_t> bytes_form(T numeric_ip)
{
  std::vector<uint8_t> bytes;
  for (size_t i = 0; i < sizeof(numeric_ip); ++i)
  {
    uint8_t byte = numeric_ip >> (i * 8); 
    bytes.insert(bytes.begin(), byte);
  }

  return bytes;
}

template <typename T>
typename std::enable_if<is_char_type<T>::value>::type
print_ip(T ip)
{
  std::cout << static_cast<int>(static_cast<unsigned char>(ip)) << std::endl;
}

template <typename T>
typename std::enable_if<is_numeric_type<T>::value>::type
print_ip(T ip)
{
    std::cout << bytes_form(ip) << std::endl;
}

template <typename T>
typename std::enable_if<is_string_type<T>::value>::type
print_ip(T ip)
{
  std::cout << ip << std::endl;
}

template <typename Container>
typename std::enable_if<is_container_type<Container>::value>::type
print_ip(Container &container)
{
  bool first = true;
  for (auto const &item : container)
  {     
      std::cout << (!first ? "." : "") << item;    
      first = false;
  }
  std::cout << std::endl;
}
