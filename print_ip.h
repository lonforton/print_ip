/**
 * @name print_ip header for printing ip_adressees in various formats
 */

#include <iostream>
#include <type_traits>
#include <list>
#include <vector>

/**
 * @brief Check if type is char or unsigned char
 * @return true - type is char or unsigned char, false - otherwise
 */
template <typename T>
struct is_char
{
  static bool const value = std::is_same<T, char>::value || std::is_same<T, unsigned char>::value;
};

/**
 * @brief Char type value helper
 * @return true - type is char, false - otherwise
 */
template <typename T>
constexpr bool is_char_v = is_char<T>::value;

/**
 * @brief Check if type is numeric 
 * @return true - type is numeric, false - otherwise
 */
template <typename T>
struct is_numeric
{
  static bool const value = !is_char<T>::value && std::is_arithmetic<T>::value;
};

/**
 * @brief Numeric type value helper
 * @return true - type is numeric, false - otherwise
 */
template <typename T>
constexpr bool is_numeric_v = is_numeric<T>::value;

/**
 * @brief Check if type is string 
 * @return true - type is string, false - otherwise
 */
template <typename T>
struct is_string
{
  static bool const value = std::is_same<T, std::string>::value;
};

/**
 * @brief String type value helper
 * @return true - type is string, false - otherwise
 */
template <typename T>
constexpr bool is_string_v = is_string<T>::value;

/**
 * @brief Helper for checking if type is container 
 * @return false - always
 */
template <typename T>
struct is_container
{
  static bool const value = false;
};

/**
 * @brief Container type value helper
 * @return true - type is container, false - otherwise
 */
template <typename T>
constexpr bool is_container_v = is_container<T>::value;

/**
 * @brief Check if type is std::list 
 * @return true - type is std::list
 */
template <typename T, typename Alloc>
struct is_container<std::list<T, Alloc>>
{
  static bool const value = true;
};

/**
 * @brief Check if type is std::vector 
 * @return true - type is std::vector
 */
template <typename T, typename Alloc>
struct is_container<std::vector<T, Alloc>>
{
  static bool const value = true;
};

/**
 * @brief Helper template for vector print 
 * @return 
 */
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

/**
 * @brief Tranform numeric ip adress to vector of bytes
 * @param [in] numeric_ip representation as numeric type
 * @return vector containing bytes
 */
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

/**
 * @brief print for char types
 * @param [in] ip representation as char type
 * @return 
 */
template <typename T>
typename std::enable_if<is_char_v<T>>::type
print_ip(T ip)
{
  std::cout << static_cast<int>(static_cast<unsigned char>(ip)) << std::endl;
}

/**
 * @brief print for numeric types
 * @param [in] ip representation as numeric type
 * @return 
 */
template <typename T>
typename std::enable_if<is_numeric_v<T>>::type
print_ip(T ip)
{
    std::cout << bytes_form(ip) << std::endl;
}

/**
 * @brief print for std::string
 * @param [in] ip representation as string type
 * @return 
 */
template <typename T>
typename std::enable_if<is_string_v<T>>::type
print_ip(T ip)
{
  std::cout << ip << std::endl;
}

/**
 * @brief print for containers types
 * @param [in] container representation as std container type
 * @return 
 */
template <typename Container>
typename std::enable_if<is_container_v<Container>>::type
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
