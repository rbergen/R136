#pragma once

// templates/items.h

#include "types/base.h"

namespace item
{
	template<class L>
	constexpr L combines_with(L value) { return -(value + 2); }

	constexpr AnimateID combines_with(ItemID item) { return static_cast<AnimateID>(combines_with(to_value(item))); }
	constexpr ItemID combines_with(AnimateID animate) { return static_cast<ItemID>(combines_with(to_value(animate))); }

	constexpr bool is_combines_with(AnimateID value)
	{
		std::underlying_type_t<AnimateID> base_value = to_value(combines_with(value));
		return base_value >= 0 && base_value < to_value(ItemID::COUNT);
	}
}
