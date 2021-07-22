// Stefan "SoulXP" Olivier
// File: node.hpp
// Description: Namespace enumerations for various XML types

#ifndef NODE_HEADER
#define NODE_HEADER

#include <magic_enum.hpp>
#include <new>

namespace vt
{
	namespace xml
	{
		enum class NS
		{
			one, two, three, four,
			none
		};

		enum class Tag
		{
			one, two, three, four,
			none
		};

		enum class Attribute
		{
			one, two, three, four,
			none
		};

		enum class ValueExpression
		{
			one, two, three, four,
			none
		};

		enum class ContentTypes
		{
			one, two, three, four,
			none 
		};

		enum class ContentOptions
		{
			one, two, three, four,
			none
		};

		template<typename T>
		struct NodeID
		{
			T					type = T();
			std::string_view	name = magic_enum::enum_name(T::none);
		};

		template<typename T>
		struct AttributeOption
		{
			NodeID<T>			        expression;
			std::string_view	        values[1];
			size_t 				        value_default   = 0;
		};

		template<typename T>
		struct AttribureItem
		{
			constexpr AttribureItem()          = default;
			constexpr AttribureItem(NodeID<T> a, size_t b, auto c[])
				: attribute(a), conditions(b)
			{
				for (int i = 0; i < 1; i++) {
					this->options[i] = c[i];
				}
			}

			NodeID<T>										attribute;
			size_t											conditions = 0;
			size_t 											documents = 0;
			AttributeOption<ValueExpression>				options[1];		
		};

		template<class I>
		struct TTMLEntry
		{
			constexpr TTMLEntry()                         = default;
			constexpr TTMLEntry(NodeID<NS> a, NodeID<Tag> b, auto c[])
				: ns(a), tag(b)
			{
				for (int i = 0; i < 3; i++) {
					this->attributes[i] = c[i];
				}
			}

			~TTMLEntry()						= default;
			NodeID<NS>							ns;
			NodeID<Tag>							tag;
			size_t								documents = 0;
			AttribureItem<Attribute> 			attributes[3];	
		};

		template<size_t Size>
		struct TTMLDictionary
		{
			TTMLDictionary() 					= default;
			~TTMLDictionary() 					= default;
			NodeID<NS>							ns;
			TTMLEntry<void> 					entries[Size];
		};

		constexpr inline auto sum(auto... Args)
		{
			return (Args + ... + 1);
		}

		template<auto... Entries>
		constexpr inline auto InitDictionary()
		{
			using namespace magic_enum;
			TTMLDictionary<sizeof...(Entries)> dictionary{};
			constexpr auto ns = NS::one;
			constexpr auto ns_name = enum_name(NS::one);
			constexpr auto tag = Tag::one;
			constexpr auto tag_name = enum_name(Tag::one);
			constexpr auto attr = Attribute::one;
			constexpr auto attr_name = enum_name(Attribute::one);
			constexpr auto expr = ValueExpression::one;
			constexpr auto expr_name = enum_name(ValueExpression::one);
			constexpr AttributeOption<ValueExpression> expressions[] = { {{expr, expr_name}, {"Hello World!"}, 1} };
			constexpr AttribureItem<Attribute> attributes[] = {{{attr, attr_name}, 1, expressions}, {{attr, attr_name}, 1, expressions}, {{attr, attr_name}, 1, expressions}}; 
			constexpr TTMLEntry<void> entries = { {ns, ns_name}, {tag, tag_name}, attributes };

			return dictionary;
		}

		template<typename T>
		constexpr inline auto e(T t)
		{
			return magic_enum::enum_name(t);
		}

		template<class T>
		constexpr inline size_t CountInit(const T t[])
		{
			size_t i = 0;
			using namespace magic_enum;
			while (t[i] != T::none) i++;
			return i;
		}

		constexpr int fnc()
		{
			constexpr int a = 1;
			return a;
		}
	}
}

/*
	Interface:
		constexpr TTMLDictionary dictionary(Entries);

		std::array

		MakeTTMLEntries
			NS::one
			Tag::one
*/

#endif //NODE_HEADER