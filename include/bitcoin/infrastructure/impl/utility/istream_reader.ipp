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
#ifndef LIBBITCOIN_INFRASTRUCTURE_ISTREAM_READER_IPP
#define LIBBITCOIN_INFRASTRUCTURE_ISTREAM_READER_IPP

#include <bitcoin/infrastructure/utility/data.hpp>
#include <bitcoin/infrastructure/utility/endian.hpp>

namespace libbitcoin {

template <unsigned Size>
byte_array<Size> istream_reader::read_forward()
{
    byte_array<Size> out;
    auto buffer = reinterpret_cast<char*>(out.data());
    stream_.read(buffer, Size);
    return out;
}

template <unsigned Size>
byte_array<Size> istream_reader::read_reverse()
{
    byte_array<Size> out;

    for (unsigned i = 0; i < Size; i++)
        out[Size - (i + 1)] = read_byte();

    return out;
}

template <typename Integer>
Integer istream_reader::read_big_endian()
{
    return from_big_endian_stream_unsafe<Integer>(stream_);
}

template <typename Integer>
Integer istream_reader::read_little_endian()
{
    return from_little_endian_stream_unsafe<Integer>(stream_);
}

} // libbitcoin

#endif
