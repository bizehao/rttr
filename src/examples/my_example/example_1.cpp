#include <format>
#include <iostream>
#include <print>
#include <rttr/registration.h>
#include <rttr/registration>
#include <rttr/type>

using namespace rttr;

void testfun(int a = 1, double b = 3.14, float c = 66.6f, std::string d = "hello", char e = 'B')
{
    std::cout << std::format("a: {}, b: {}, c: {}, d: {}, e: {}\n", a, b, c, d, e);
}

RTTR_REGISTRATION
{
    registration::do_method<^^testfun>();
}
//不支持模板函数
//会忽略const
//会忽略匿名union成员变量
//只检测public成员，处理protected和private没有意义
//会排除&&函数
int main()
{
    using namespace std::string_literals;
    auto md = type::get_global_method("testfun");

    md.invoke({});
    md.invoke({}, 2);
    md.invoke({}, 3, 6.24);
    md.invoke({}, 4, 6.24, 33.3f);
    md.invoke({}, 5, 6.24, 33.3f, "world"s);
    md.invoke({}, 6, 6.24, 33.3f, "world"s, 'Z');


    md.invoke({}, 7, 6.24, 33.3f, "world"s, 'Z', 'H');

    return 0;
}