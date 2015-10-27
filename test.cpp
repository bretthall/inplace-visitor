#include "inplace-visitor.h"
#include <iostream>

int main ()
{
   auto v1 = boost::variant<int, double, std::string, bool>(1);
   boost::apply_visitor (make_visitor<void> ([](int x) {std::cout << "int = " << x << std::endl;},
                                             [](double x) {std::cout << "Double = " << x << std::endl;},
                                             [](const std::string& x) {std::cout << "String = " << x << std::endl;},
                                             [](auto x) {std::cout << "auto = " << x << std::endl;}),
                         v1);
   v1 = 2.0;
   boost::apply_visitor (make_visitor<void> ([](int x) {std::cout << "int = " << x << std::endl;},
                                             [](double x) {std::cout << "Double = " << x << std::endl;},
                                             [](const std::string& x) {std::cout << "String = " << x << std::endl;},
                                             [](auto x) {std::cout << "auto = " << x << std::endl;}),
                         v1);
   v1 = std::string ("3");
   boost::apply_visitor (make_visitor<void> ([](int x) {std::cout << "int = " << x << std::endl;},
                                             [](double x) {std::cout << "Double = " << x << std::endl;},
                                             [](const std::string& x) {std::cout << "String = " << x << std::endl;},
                                             [](auto x) {std::cout << "auto = " << x << std::endl;}),
                         v1);
   v1 = true;
   boost::apply_visitor (make_visitor<void> ([](int x) {std::cout << "int = " << x << std::endl;},
                                             [](double x) {std::cout << "Double = " << x << std::endl;},
                                             [](const std::string& x) {std::cout << "String = " << x << std::endl;},
                                             [](auto x) {std::cout << "auto = " << x << std::endl;}),
                         v1);

   auto visitor = make_visitor<void> ([](int x) {std::cout << "int = " << x << std::endl;},
                                      [](double x) {std::cout << "Double = " << x << std::endl;},
                                      [](const std::string& x) {std::cout << "String = " << x << std::endl;},
                                      [](auto x) {std::cout << "auto = " << x << std::endl;});
   v1 = 1;
   boost::apply_visitor (visitor, v1);
   v1 = 2.0;
   boost::apply_visitor (visitor, v1);
   v1 = std::string ("3");
   boost::apply_visitor (visitor, v1);
   v1 = true;
   boost::apply_visitor (visitor, v1);

   auto apply = boost::apply_visitor (visitor);
   v1 = 1;
   apply (v1);
   v1 = 2.0;
   apply (v1);
   v1 = std::string ("3");
   apply (v1);
   v1 = true;
   apply (v1);

   auto v2 = boost::variant<int, double>(2);
   v1 = 1;
   boost::apply_visitor (make_visitor<void>(
                            [](int i1, int i2){std::cout << "both int = (" << i1 << "," << i2 << ")" << std::endl;},
                            [](int i1, double i2){std::cout << "int,double = (" << i1 << "," << i2 << ")" << std::endl;},
                            [](auto i1, auto i2){std::cout << "auto,auto = (" << i1 << "," << i2 << ")" << std::endl;}),
                         v1, v2);
   v2 = 2.0;
   boost::apply_visitor (make_visitor<void>(
                            [](int i1, int i2){std::cout << "both int = (" << i1 << "," << i2 << ")" << std::endl;},
                            [](int i1, double i2){std::cout << "int,double = (" << i1 << "," << i2 << ")" << std::endl;},
                            [](auto i1, auto i2){std::cout << "auto,auto = (" << i1 << "," << i2 << ")" << std::endl;}),
                         v1, v2);
   v1 = std::string ("dsflkj");
   boost::apply_visitor (make_visitor<void>(
                            [](int i1, int i2){std::cout << "both int = (" << i1 << "," << i2 << ")" << std::endl;},
                            [](int i1, double i2){std::cout << "int,double = (" << i1 << "," << i2 << ")" << std::endl;},
                            [](auto i1, auto i2){std::cout << "auto,auto = (" << i1 << "," << i2 << ")" << std::endl;}),
                         v1, v2);   

   std::cout << boost::apply_visitor (make_visitor<int> ([](int) {return 1;},
                                                         [](double) {return 2;},
                                                         [](const std::string&) {return 3;},
                                                         [](auto) {return 0;}),
                                      v1) << std::endl;
   v1 = 1;
   std::cout << boost::apply_visitor (make_visitor<int> ([](int) {return 1;},
                                                         [](double) {return 2;},
                                                         [](const std::string&) {return 3;},
                                                         [](auto) {return 0;}),
                                      v1) << std::endl;
      
   return 0;
}
