//-----------------------------------------------------------------------------------------------------------------------------
// think-cell public library
// Copyright (C) 2016-2018 think-cell Software GmbH
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as 
// published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. 
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. 
//
// You should have received a copy of the GNU General Public License along with this program. 
// If not, see <http://www.gnu.org/licenses/>. 
//-----------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------
// Include all header for tc ranges. See the individual headers for details.
//-----------------------------------------------------------------------------------------------------------------------------
// 
// Design choices:
// - To avoid fat iterators when stacking range adaptors, in particular range filters, all per-range and not per-iterator data is stored in the range adaptor object.
// - Thus, range adaptor iterator lifetime is limited to the lifetime of the range. All range adaptor iterators are slim, consisting of a pointer to their range and the "index",
//   which is usually the (slim) iterator of the very-base container.
// - All usual iterator operations are defined in terms of the range and the "index" (similar to cursor from http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1873.html ).
// - Below the range category providing input iterators, there is an even simpler range category which can only plug their elements into a functor passed to operator(). They have no iterators.
// - If the functor returns break_or_continue, the simpler range category is expected to a) heed this and b) return this break_or_continue from its operator() when the enumeration is finished.
// - If the functor does not return break_or_continue, the simpler range category is expected to run over all elements and not to return break_. It may return continue_ or another type or void.
// - Range content constness = base range constness || range adaptor object constness, so an function with argument template< typename Range > Range const& cannot modify the range's elements.
// - Adaptors created around a range rvalue aggregate their base range, e.g., contain it by value.

#pragma once

#include "range_defines.h"

#include "meta.h"
#include "break_or_continue.h"
#include "for_each.h"

#include "index_range.h"
#include "range_adaptor.h"
#include "sub_range.h"
#include "filter_adaptor.h"
#include "transform_adaptor.h"
#include "algorithm.h"
#include "equal.h"
#include "empty.h"
#include "minmax.h"

#include "casts.h"
#include "reference_or_value.h"

namespace tc{
	DEFINE_FN2(tc::size, fn_size); // Prevent ADL of std::size (C++17)
	DEFINE_FN( strlen )
	DEFINE_FN( isasciidigit )
	DEFINE_FN( isasciilower )
	DEFINE_FN( isasciiupper )
	DEFINE_FN( equal );
}
//-----------------------------------------------------------------------------------------------------------------------------
