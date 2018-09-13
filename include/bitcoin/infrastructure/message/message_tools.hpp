/**
 * Copyright (c) 2017-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BITPRIM_INFRASTRUCTURE_MESSAGE_TOOLS_HPP_
#define BITPRIM_INFRASTRUCTURE_MESSAGE_TOOLS_HPP_

#include <cstddef>
#include <cstdint>

#include <bitcoin/infrastructure/define.hpp>

namespace libbitcoin { 
namespace message {

BI_API size_t variable_uint_size(uint64_t value);

} // namespace message
} // namespace libbitcoin

#endif // BITPRIM_INFRASTRUCTURE_MESSAGE_TOOLS_HPP_
