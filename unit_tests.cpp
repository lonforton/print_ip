#define BOOST_TEST_MODULE allocator_test_module

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <iostream>

#include "print_ip.h"

BOOST_AUTO_TEST_SUITE(print_ip_test_suite)

/**
 * @brief Helper redirection fot tests
 */
struct cout_redirect 
{
  cout_redirect(std::streambuf * new_buffer) 
  : old (std::cout.rdbuf(new_buffer))
  { }

  ~cout_redirect( ) 
  {
    std::cout.rdbuf(old);
  }

  private:
    std::streambuf *old;
};

BOOST_AUTO_TEST_CASE(char_type_test)
{
  boost::test_tools::output_test_stream output;
  {
    cout_redirect redirect(output.rdbuf());

    char ip_char = -1;
    print_ip(ip_char);
  }
  BOOST_CHECK(output.is_equal("255\n"));
}

BOOST_AUTO_TEST_CASE(short_type_test)
{
    boost::test_tools::output_test_stream output;
  {
    cout_redirect redirect(output.rdbuf());

  short ip_short = 0;
  print_ip(ip_short);
  }
  BOOST_CHECK(output.is_equal("0.0\n"));
}

BOOST_AUTO_TEST_CASE(int_type_test)
{
    boost::test_tools::output_test_stream output;
  {
    cout_redirect redirect(output.rdbuf());

  int ip_int = 2130706433;
  print_ip(ip_int);
  }
  BOOST_CHECK(output.is_equal("127.0.0.1\n"));
}

BOOST_AUTO_TEST_CASE(long_type_test)
{
    boost::test_tools::output_test_stream output;
  {
    cout_redirect redirect(output.rdbuf());

  long long ip_long = 8875824491850138409;
  print_ip(ip_long);
  }
  BOOST_CHECK(output.is_equal("123.45.67.89.101.112.131.41\n"));
}

BOOST_AUTO_TEST_CASE(string_type_test)
{
    boost::test_tools::output_test_stream output;
  {
    cout_redirect redirect(output.rdbuf());

  std::string ip_string("9.69.222.182");
  print_ip(ip_string);
  }
  BOOST_CHECK(output.is_equal("9.69.222.182\n"));
}

BOOST_AUTO_TEST_CASE(vector_type_test)
{
    boost::test_tools::output_test_stream output;
  {
    cout_redirect redirect(output.rdbuf());

  std::vector<int> ip_vector{192, 168, 0, 100};
  print_ip(ip_vector);
  }
  BOOST_CHECK(output.is_equal("192.168.0.100\n"));
}

BOOST_AUTO_TEST_CASE(list_type_test)
{
    boost::test_tools::output_test_stream output;
  {
    cout_redirect redirect(output.rdbuf());

  std::list<int> ip_list = {8, 16, 24, 32};
  print_ip(ip_list);
  }
  BOOST_CHECK(output.is_equal("8.16.24.32\n"));
}


BOOST_AUTO_TEST_SUITE_END()