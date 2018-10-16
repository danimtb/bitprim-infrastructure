/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
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
#ifndef LIBBITCOIN_INFRASTUCTURE_CONFIG_BASE16_HPP
#define LIBBITCOIN_INFRASTUCTURE_CONFIG_BASE16_HPP

#include <array>
#include <cstdint>
#include <iostream>
#include <string>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace libbitcoin {
namespace config {

/**
 * Serialization helper for base16 encoded data.
 */
class BI_API base16
{
public:

    /**
     * Default constructor.
     */
    base16() = default;

    /**
     * Initialization constructor.
     * @param[in]  hexcode  The value to initialize with.
     */
    base16(std::string const& hexcode);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    base16(data_chunk const& value);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    template <size_t Size>
    base16(byte_array<Size> const& value)
        : value_(value.begin(), value.end())
    {}

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    base16(base16 const& x);

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type reference.
     */
    operator data_chunk const&() const;

    /**
     * Overload cast to generic data reference.
     * @return  This object's value cast to a generic data.
     */
    operator data_slice() const;

    /**
     * Overload stream in. If input is invalid sets no bytes in argument.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend 
    std::istream& operator>>(std::istream& input, base16& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend 
    std::ostream& operator<<(std::ostream& output, const base16& argument);

private:

    /**
     * The state of this object.
     */
    data_chunk value_;
};

} // namespace config
} // namespace libbitcoin

#endif
