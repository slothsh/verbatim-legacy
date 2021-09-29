// Stefan "SoulXP" Olivier
// File: validatettml.cpp
// Description: Prototype code for building a TTML tree for run time structure validation

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../../include/config.hpp"
#endif

// Standard headers
#include <iostream>
#include <concepts>
#include <type_traits>

// Third-party headers

// Project headers
#include "../../include/prototype/validatettml.hpp"

// TTML dictionary helpers ---------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

template<class>
struct is_tuple : std::false_type
{};

template<class... Ts>
struct is_tuple<std::tuple<Ts...>> : std::true_type
{};

template<class T>
concept tuple_c = is_tuple<std::decay_t<T>>::value;

template<class...>
struct ValueExpressionNode
{};

template<>
struct ValueExpressionNode<>
{


    auto operator()(const auto& f) const
    {
        return f();
    }
};

template<class Tns, class Tvexpr, class Tvalue, class Tcnd, class Tdoc, class... Rest>
struct ValueExpressionNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc, Rest...>
{
public:
    using this_t = ValueExpressionNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc>;
    using fundamental_t = std::conditional_t<sizeof...(Rest) == 0, this_t, ValueExpressionNode<>>;
    using node_t = std::tuple<Tns, Tvexpr>;
    using next_t = std::conditional_t<sizeof...(Rest) == 0, ValueExpressionNode<>, ValueExpressionNode<Rest...>>;

    ValueExpressionNode() = default;
    ~ValueExpressionNode() = default;

    constexpr ValueExpressionNode(Tns&& _ns, Tvexpr&& _vexpr, Tvalue&& _value, Tcnd&& _conditions, Tdoc&& _documents)
        : fundamental(std::move(_ns), std::move(_vexpr), std::move(_value), std::move(_conditions), std::move(_documents)),
        // expression(std::move(_ns), std::move(_vexpr)),
        // value(std::move(_value)),
        // conditions(std::move(_conditions)),
        // documents(std::move(_documents)),
        next({})
    {}

    template<std::enable_if<sizeof...(Rest) != 0, bool> = true>
    constexpr ValueExpressionNode(Tns&& _ns, Tvexpr&& _vexpr, Tvalue&& _value, Tcnd&& _conditions, Tdoc&& _documents, Rest&&... _rest)
        : fundamental(std::move(_ns), std::move(_vexpr), std::move(_value), std::move(_conditions), std::move(_documents)),
        // expression(std::move(_ns), std::move(_vexpr)),
        // value(std::move(_value)),
        // conditions(std::move(_conditions)),
        // documents(std::move(_documents)),
        next(std::move(_rest)...)
    {}

    template<std::enable_if<sizeof...(Rest) == 0, bool> = true>
    constexpr ValueExpressionNode(Tns&& _ns, Tvexpr&& _vexpr, Tvalue&& _value, Tcnd&& _conditions, Tdoc&& _documents)
        : fundamental(std::move(_ns), std::move(_vexpr), std::move(_value), std::move(_conditions), std::move(_documents)),
        // expression(std::move(_ns), std::move(_vexpr)),
        // value(std::move(_value)),
        // conditions(std::move(_conditions)),
        // documents(std::move(_documents)),
        next({})
    {}

    fundamental_t& operator()() const noexcept
    {
        return this->fundamental;
    }

    size_t total = sizeof...(Rest);
    bool is_leaf = (sizeof...(Rest) == 0) ? true : false;
    fundamental_t         fundamental;
    // node_t              expression;
    // Tvalue              value;
    // Tcnd                conditions;
    // Tdoc                documents;
    next_t              next;    
};

template<class Tns, class Tvexpr, class Tvalue, class Tcnd, class Tdoc, class... Rest>
ValueExpressionNode(Tns&&, Tvexpr&&, Tvalue&&, Tcnd&&, Tdoc&&, Rest&&...) -> ValueExpressionNode<Tns, Tvexpr, Tvalue, Tcnd, Tdoc, Rest...>;

// ------------------------------------------------------------|END|-----------------------------------------------------------|

int main(int argc, char** argv)
{
	using namespace vt::prototype;

    static_assert(MAGIC_ENUM_RANGE_MIN == 0);
    static_assert(MAGIC_ENUM_RANGE_MAX == 256);

    static_assert(mge::enum_integer(NS::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(Tag::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(Attribute::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(ValueExpression::none) == MAGIC_ENUM_RANGE_MAX);
    static_assert(mge::enum_integer(GenericData::none) == MAGIC_ENUM_RANGE_MAX);

    static_assert(mge::enum_integer(NS::IS_NS) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(Tag::IS_TAG) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(Attribute::IS_ATTRIBUTE) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(ValueExpression::IS_VALUE_EXPRESSION) == MAGIC_ENUM_RANGE_MIN);
    static_assert(mge::enum_integer(GenericData::IS_DATA) == MAGIC_ENUM_RANGE_MIN);

    constexpr std::tuple a{ 1, 2, 3, 4 };
    // constexpr ValueExpressionNode b{ NS::tt, ValueExpression::alpha, "hello", 0, 1, ValueExpressionNode{ NS::tt, ValueExpression::alpha, "bye", 0, 1 } };
    ValueExpressionNode b{ NS::tt, ValueExpression::alpha, std::string_view{"hello"}, 0, 1, NS::tt, ValueExpression::alpha, std::string_view{"hello"}, 0, 1, NS::tt, ValueExpression::alpha, std::string_view{"hello"}, 0, 1 };

    std::cout << "\nend\n";
    return 0;
}