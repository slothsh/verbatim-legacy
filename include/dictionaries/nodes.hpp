// Stefan "SoulXP" Olivier
// File: node_tt_tt.hpp
// Description: TTML dictionary entry for tt:tt tag

#ifndef VTNODEENTRIES_HEADER
#define VTNODEENTRIES_HEADER

// Configuration headers
#ifndef VTCONFIG_HEADER
#include "../config.hpp"
#endif

// Project headers
#include "../node.hpp"
#include "attributes.hpp"

namespace vt::dictionary::detail
{
    using namespace magic_enum::bitwise_operators;
    using magic_enum::enum_integer;

    using vexpression_t         = ValueExpressionNode<NS, ValueExpression>;
    using content_data_t        = ContentNode<NS, GenericData>;
    using content_tag_t         = ContentNode<NS, Tag>;

    using grp = constants::ByteGroup;
    using doc = constants::TTMLDocument;
    using cnd = constants::NodeCondition;
    using qty = constants::NodeQuantifier;
}

#endif // VTNODEENTRIES_HEADER