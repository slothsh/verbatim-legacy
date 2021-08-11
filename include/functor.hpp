// Stefan "SoulXP" Olivier
// File: functor.hpp
// Description: helper functor objects

#ifndef VTFUNCTOR_HEADER
#define VTFUNCTOR_HEADER

// Stanard Headers
#include <type_traits>
#include <concepts>

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "config.hpp"
#endif

// Helper Functors -----------------------------------------------------------------------------------------------------1 of 1-|
// ============================================================================================================================|

namespace vt::functional
{
    template<class Tfnc>
    class VTFunctor
    {
        using fnc_t = Tfnc;

    public:
        // constexpr VTFunctor()                           = default;
        // constexpr VTFunctor(const VTFunctor&)           = default;
        // constexpr VTFunctor(VTFunctor&&)                = default;

        constexpr VTFunctor(Tfnc&& fnc) noexcept
            : fnc(fnc)
        {}

        constexpr VTFunctor(const Tfnc&& fnc) noexcept
            : fnc(fnc)
        {}


        constexpr decltype(auto) operator()(auto&&... values)
        {
            this->fnc(values...);
        }

        constexpr decltype(auto) operator()(const auto&&... values) const
        {
            return this->fnc(std::move(values)...);
        }

    private:
        fnc_t fnc;
    };
}

// ------------------------------------------------------------|END|-----------------------------------------------------------|

#endif // VTFUNCTOR_HEADER