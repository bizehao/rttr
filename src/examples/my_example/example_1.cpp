#include <format>
#include <iostream>
#include <print>
#include <rttr/registration.h>
#include <rttr/registration>
#include <rttr/type>

using namespace rttr;

[[=metadata("test1", std::vector{1,2,3,4})]]
[[=metadata("test2", std::vector{5,6,7,8})]]
[[=metadata("test3", std::vector{9,10,11,12})]]
[[=metadata("test4", "123213")]]
void testfun(int a = 1, double b = 3.14, float c = 66.6f, std::string d = "hello", char e = 'B')
{
    std::cout << std::format("a: {}, b: {}, c: {}, d: {}, e: {}\n", a, b, c, d, e);
}

//todo: 为class添加metadata
[[=metadata("test4", "123213")]]
struct TestOperator
{
    void operator()(int a)
    {
        constexpr auto info = std::meta::current_function();
        constexpr auto a_info = std::meta::parameters_of(info)[0];

        const int& x = [:std::meta::variable_of(a_info):]; // OK，x 指代 int_arg

        std::cout << std::format("{}", std::meta::display_string_of(info));
    }

    void operator+(int a) const
    {
        constexpr auto info = std::meta::current_function();
        std::cout << std::format("{}", std::meta::display_string_of(info));
    }

    operator int() const
    {
        return 100;
    }
};




RTTR_REGISTRATION
{
    registration::do_method<^^testfun>();
    registration::do_class<^^TestOperator>();

    // auto data = registration::get_metadata<^^testfun>();
    // for (auto&& [k, v] : data)
    // {
    //     std::cout << std::format("{}, {}", k, v.get_type().get_name()) << std::endl;;
    // }
}
//不支持模板函数
//会忽略const
//会忽略匿名union成员变量
//只检测public成员，处理protected和private没有意义
//会排除&&函数
int main()
{

    // using namespace std::string_literals;
    auto md = type::get_global_method("testfun");

    std::vector<int> arr{1,2,3};
    rttr::variant vv = md.get_metadata("test2");

    std::cout << vv.get_type().get_name() << std::endl;

    //bool b = vv.is_sequential_container();

    std::span<const int> barr;
    vv.convert(barr);

    // std::span<int> vec;
    // auto view_vec = vv.create_sequential_view();
    // for (auto& it : view_vec)
    // {
    //     std::cout << it.to_string()<< std::endl;
    // }

    int _d = 0;

    // md.invoke({});
    // md.invoke({}, 2);
    // md.invoke({}, 3, 6.24);
    // md.invoke({}, 4, 6.24, 33.3f);
    // md.invoke({}, 5, 6.24, 33.3f, "world"s);
    // md.invoke({}, 6, 6.24, 33.3f, "world"s, 'Z');
    //
    //
    // md.invoke({}, 7, 6.24, 33.3f, "world"s, 'Z', 'H');

    // auto type_TestOperator = type::get<TestOperator>();
    // auto mm = type_TestOperator.get_method("()");
    // TestOperator obj;
    // mm.invoke(obj, 55);
    //
    //
    // variant vv = obj;
    // int kk = 0;
    // bool bb = vv.convert(kk);

    return 0;
}