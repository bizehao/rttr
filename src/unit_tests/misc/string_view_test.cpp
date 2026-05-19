/************************************************************************************
*                                                                                   *
*   Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>                           *
*                                                                                   *
*   This file is part of RTTR (Run Time Type Reflection)                            *
*   License: MIT License                                                            *
*                                                                                   *
*   Permission is hereby granted, free of charge, to any person obtaining           *
*   a copy of this software and associated documentation files (the "Software"),    *
*   to deal in the Software without restriction, including without limitation       *
*   the rights to use, copy, modify, merge, publish, distribute, sublicense,        *
*   and/or sell copies of the Software, and to permit persons to whom the           *
*   Software is furnished to do so, subject to the following conditions:            *
*                                                                                   *
*   The above copyright notice and this permission notice shall be included in      *
*   all copies or substantial portions of the Software.                             *
*                                                                                   *
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
*   SOFTWARE.                                                                       *
*                                                                                   *
*************************************************************************************/

#include <rttr/type>
#include <rttr/std::string_view.h>

#include <iostream>
#include <memory>
#include <functional>
#include <type_traits>

#include <catch/catch.hpp>
#include <string_view>

using namespace rttr;


/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - std::string_view()", "[std::string_view]")
{
    std::string_view text;

    CHECK(text.empty() == true);
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - std::string_view(const std::string_view&)", "[std::string_view]")
{
    std::string_view text1;
    std::string_view text2 = text1;
    std::string_view text3 = "Hello World";
    std::string_view text4 = text3;

    CHECK(text1.empty() == true);
    CHECK(text2.empty() == true);
    CHECK(text3.empty() == false);
    CHECK(text4.empty() == false);
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - std::string_view(const char*)", "[std::string_view]")
{
    std::string_view text("Hello World");

    CHECK(text.empty() == false);
    CHECK(text == "Hello World");
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - std::string_view(const char*, std::size_t)", "[std::string_view]")
{
    std::string_view text("Hello World", 5);

    CHECK(text.empty() == false);
    CHECK(text == "Hello");
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - std::string_view(std::string)", "[std::string_view]")
{
    std::string string = "Hello World";
    std::string_view text(string);

    CHECK(text.empty() == false);
    CHECK(text == "Hello World");
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - operator=(const basic_std::string_view&)", "[std::string_view]")
{
    std::string_view obj1 = "Hello";
    std::string_view obj2 = "World";
    obj1 = obj2;

    CHECK(obj1 == "World");
    CHECK(obj2 == "World");
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - swap()", "[std::string_view]")
{
    std::string_view obj1 = "Hello";
    std::string_view obj2 = "World";
    obj1.swap(obj2);

    CHECK(obj1 == "World");
    CHECK(obj2 == "Hello");
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - size(), length(), max_size(), empty()", "[std::string_view]")
{
    std::string_view text = "Hello World";

    CHECK(text.size()       == 11);
    CHECK(text.length()     == 11);
    CHECK(text.max_size()   == 11);
    CHECK(text.empty()      == false);
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - front(), back(), data()", "[std::string_view]")
{
    std::string_view text = "Hello World";

    CHECK(std::string_view(&text.front(), 1) == "H");
    CHECK(std::string_view(&text.back(), 1)  == "d");
    CHECK(std::string_view(text.data())      == "Hello World");
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - begin(), end(), cbegin(), cend()", "[std::string_view]")
{
    auto string_literal = "Hello World";
    std::string_view text = string_literal;

    CHECK(*text.begin() == *"H");
    CHECK(text.end() == string_literal + std::char_traits<char>::length(string_literal));

    CHECK(*text.cbegin() == *"H");
    CHECK(text.cend() == string_literal + std::char_traits<char>::length(string_literal));
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - rbegin(), rend(), crbegin(), crend()", "[std::string_view]")
{
    auto string_literal = "Hello World";
    std::string_view text = string_literal;

    CHECK(*text.rbegin() == *"d");
    CHECK(text.rend() == std::string_view::reverse_iterator(string_literal));

    CHECK(*text.crbegin() == *"d");
    CHECK(text.crend() == std::string_view::reverse_iterator(string_literal));
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - operator[]", "[std::string_view]")
{
    std::string_view text1 = "Hello World";
    std::string text2(text1);
    for (std::size_t i = 0; i < text2.length(); ++i)
    {
        CHECK(text1[i] == text2[i]);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - remove_prefix()", "[std::string_view]")
{
    std::string_view text = "Hello World";
    text.remove_prefix(6);

    CHECK(text == "World");
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - remove_suffix()", "[std::string_view]")
{
    std::string_view text = "Hello World";
    text.remove_suffix(6);

    CHECK(text == "Hello");
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - std::string operator()", "[std::string_view]")
{
    std::string_view text = "Hello World";
    std::string string_value(text);

    CHECK(string_value == "Hello World");
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - to_string", "[std::string_view]")
{
    std::string_view text = "Hello World";
    std::string string_value = text.to_string();

    CHECK(string_value == "Hello World");
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - operator==()", "[std::string_view]")
{
    std::string_view text1 = "Hello World";
    std::string_view text2 = "Hello World";
    std::string_view text3;
    std::string_view text4 = "Other";

    CHECK(text1 == text2);
    CHECK(text1 == std::string("Hello World") );

    // negative
    CHECK( !(text1 == text3) );
    CHECK( !(text1 == text4) );
}

/////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("std::string_view - operator!=()", "[std::string_view]")
{
    std::string_view text1 = "Hello World";
    std::string_view text2 = "Hello World";
    std::string_view text3;
    std::string_view text4 = "Other";

    CHECK(text1 == text2);
    // negative
    CHECK( !(text1 == text3) );
    CHECK( !(text1 == text4) );
}

/////////////////////////////////////////////////////////////////////////////////////////
