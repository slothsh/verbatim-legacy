#include <iostream>
#include <iomanip>
#include <type_traits>
#include <concepts>

// ValidatingTree
// ==================================================

template<class...>
class ValidatingTree
{};

template<class Tvalue>
class ValidatingTree<Tvalue>
{
public:
    using value_t = std::decay_t<Tvalue>;

    constexpr ValidatingTree(Tvalue&& _value)
        : value{_value}
    {}

    value_t value;
};

template<class Tvalue, class... Rest>
class ValidatingTree<Tvalue, Rest...>
{
public:
    using value_t = std::decay_t<Tvalue>;
    using next_t = ValidatingTree<Rest...>;

    constexpr ValidatingTree(Tvalue&& _value, Rest&&... _rest)
        : value{_value},
        next{std::move(_rest)...}
    {}

    value_t value;
    next_t next;
};

template<class T>
ValidatingTree(T t) -> ValidatingTree<T>;

template<class T1, class T2>
ValidatingTree(T1 t1, T2 t2) -> ValidatingTree<T1, T2>;

template<class T, class... Trest>
ValidatingTree(T t, Trest... rest) -> ValidatingTree<T, Trest...>;

// ==================================================

// ValidatingComponents
// ==================================================

template<class Tns, class Ttag>
class Element
{
public:
    using ns_t = std::decay_t<Tns>;
    using tag_t = std::decay_t<Ttag>;

    constexpr Element(Tns&& _ns, Ttag&& _tag)
        : ns{_ns},
        tag{_tag}
    {}

    ns_t ns;
    tag_t tag;
};

struct m_document_empty
{
protected:
    constexpr explicit m_document_empty(size_t&&)
    {}
};

struct m_document_mask
{
protected:
    constexpr explicit m_document_mask(size_t&& _value)
        : documents{_value}
    {}

public:
    size_t documents;
};

struct m_quantifier_empty
{
protected:
    constexpr explicit m_quantifier_empty(size_t&&)
    {}
};

struct m_quantifier_mask
{
protected:
    constexpr explicit m_quantifier_mask(size_t&& _value)
        : quantifiers{_value}
    {}

public:
    size_t quantifiers;
};

struct m_condition_empty
{
protected:
    constexpr explicit m_condition_empty(size_t&&)
    {}
};

struct m_condition_mask
{
protected:
    constexpr explicit m_condition_mask(size_t&& _value)
        : conditions{_value}
    {}

public:
    size_t conditions;
};

struct m_expression_empty
{
protected:
    constexpr explicit m_expression_empty(size_t&&)
    {}
};

struct m_expression
{
protected:
    constexpr explicit m_expression(std::string_view&& _value)
        : expression{_value}
    {}

public:
    std::string_view expression;
};

// ==================================================

// Initializer
// ==================================================

template<class T>
class Initializer
{
public:
    using type_t = T;

    constexpr Initializer(T&& t)
    {
        Initializer<T>::value = t;
        Initializer<T>::initialized = false;
    }

    static type_t value;
    static bool initialized;
};

// ==================================================

// ValidatingElement
// ==================================================

namespace detail
{
    template<bool Add>
    using document_mask_t = std::conditional_t<Add, m_document_mask, m_document_empty>;

    template<bool Add>
    using quantifier_mask_t = std::conditional_t<Add, m_quantifier_mask, m_quantifier_empty>;

    template<bool Add>
    using condition_mask_t = std::conditional_t<Add, m_condition_mask, m_condition_empty>;

    template<bool Add>
    using expression_mask_t = std::conditional_t<Add, m_expression, m_expression_empty>;
}

template<class Tvalue,
            bool add_documents = false, bool add_quantifiers = false, bool add_conditions = false, bool add_expression = false>
class ValidatingElement
    : public detail::document_mask_t<add_documents>,
    public detail::quantifier_mask_t<add_quantifiers>,
    public detail::condition_mask_t<add_conditions>,
    public detail::expression_mask_t<add_expression>
{
public:
    using element_t = std::decay_t<Tvalue>;
    using doc_mask_t = detail::document_mask_t<add_documents>;
    using qty_mask_t = detail::quantifier_mask_t<add_quantifiers>;
    using cnd_mask_t = detail::condition_mask_t<add_conditions>;
    using exp_mask_t = detail::expression_mask_t<add_expression>;

    constexpr ValidatingElement(Tvalue&& _element, size_t&& _total, size_t&& _value1)
        : doc_mask_t{Initializer<size_t>{_value1}},
        qty_mask_t{Initializer<size_t>{_value1}},
        cnd_mask_t{Initializer<size_t>{_value1}},
        exp_mask_t{Initializer<size_t>{_value1}},
        element{_element},
        total{_total}
    {}

    element_t element;
    size_t total;
};

// ==================================================