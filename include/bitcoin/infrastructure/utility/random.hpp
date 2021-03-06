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
#ifndef LIBBITCOIN_INFRASTRUCTURE_RANDOM_HPP
#define LIBBITCOIN_INFRASTRUCTURE_RANDOM_HPP

#include <cstdint>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace libbitcoin {

/**
 * Generate a pseudo random number within the domain.
 * @return  The 64 bit number.
 */
BI_API uint64_t pseudo_random();

/**
 * Generate a pseudo random number within [begin, end].
 * @return  The 64 bit number.
 */
BI_API uint64_t pseudo_random(uint64_t begin, uint64_t end);

/**
 * Fill a buffer with randomness using the default random engine.
 * @param[in]  chunk  The buffer to fill with randomness.
 */
BI_API void pseudo_random_fill(data_chunk& chunk);

/**
 * Convert a time duration to a value in the range [max/ratio, max].
 * @param[in]  maximum  The maximum value to return.
 * @param[in]  ratio    The determinant of the minimum duration as the inverse
 *                      portion of the maximum duration.
 * @return              The randomized duration.
 */
BI_API asio::duration pseudo_randomize(const asio::duration& maximum,
    uint8_t ratio=2);

} // namespace libbitcoin

#endif
