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
#ifndef LIBBITCOIN_INFRASTUCTURE_CONFIG_HASH160_HPP
#define LIBBITCOIN_INFRASTUCTURE_CONFIG_HASH160_HPP

#include <iostream>
#include <string>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/math/hash.hpp>

namespace libbitcoin {
namespace config {

/**
 * Serialization helper for a bitcoin 160 bit hash.
 */
class BI_API hash160 {
public:

    /**
     * Default constructor.
     */
    hash160();

    /**
     * Initialization constructor.
     * @param[in]  hexcode  The value to initialize with.
     */
    explicit
    hash160(std::string const& hexcode);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    explicit
    hash160(const short_hash& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    hash160(hash160 const& x);

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    explicit
    operator const short_hash&() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend 
    std::istream& operator>>(std::istream& input, hash160& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend 
    std::ostream& operator<<(std::ostream& output, hash160 const& argument);

private:

    /**
     * The state of this object.
     */
    short_hash value_;
};

} // namespace config
} // namespace libbitcoin

#endif
