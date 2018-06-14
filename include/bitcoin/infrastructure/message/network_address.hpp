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
#ifndef LIBBITCOIN_INFRASTRUCTURE_MESSAGE_NETWORK_ADDRESS_HPP
#define LIBBITCOIN_INFRASTRUCTURE_MESSAGE_NETWORK_ADDRESS_HPP

#include <cstdint>
#include <istream>
#include <vector>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
#include <bitcoin/infrastructure/utility/reader.hpp>
#include <bitcoin/infrastructure/utility/writer.hpp>

namespace libbitcoin {
namespace message {

typedef byte_array<16> ip_address;

class BI_API network_address
{
public:
    typedef std::vector<network_address> list;

    static network_address factory_from_data(uint32_t version,
        const data_chunk& data, bool with_timestamp);
    static network_address factory_from_data(uint32_t version,
        std::istream& stream, bool with_timestamp);
    static network_address factory_from_data(uint32_t version,
        reader& source, bool with_timestamp);
    static size_t satoshi_fixed_size(uint32_t version,
        bool with_timestamp);

    network_address();

    // BI_CONSTCTOR required for declaration of constexpr address types.
    BI_CONSTCTOR network_address(uint32_t timestamp, uint64_t services,
        const ip_address& ip, uint16_t port)
      : timestamp_(timestamp), services_(services), ip_(ip), port_(port)
    {
    }

    network_address(uint32_t timestamp, uint64_t services, ip_address&& ip,
        uint16_t port);

    network_address(const network_address& other);
    network_address(network_address&& other);

    // Starting version 31402, addresses are prefixed with a timestamp.
    uint32_t timestamp() const;
    void set_timestamp(uint32_t value);

    uint64_t services() const;
    void set_services(uint64_t value);

    ip_address& ip();
    const ip_address& ip() const;
    void set_ip(const ip_address& value);
    void set_ip(ip_address&& value);

    uint16_t port() const;
    void set_port(uint16_t value);

    bool from_data(uint32_t version, const data_chunk& data,
        bool with_timestamp);
    bool from_data(uint32_t version, std::istream& stream,
        bool with_timestamp);
    bool from_data(uint32_t version, reader& source, bool with_timestamp);
    data_chunk to_data(uint32_t version, bool with_timestamp) const;
    void to_data(uint32_t version, std::ostream& stream,
        bool with_timestamp) const;
    void to_data(uint32_t version, writer& sink, bool with_timestamp) const;
    bool is_valid() const;
    void reset();
    size_t serialized_size(uint32_t version, bool with_timestamp) const;

    network_address& operator=(network_address&& other);
    network_address& operator=(const network_address& other);

    bool operator==(const network_address& other) const;
    bool operator!=(const network_address& other) const;

private:
    uint32_t timestamp_;
    uint64_t services_;
    ip_address ip_;
    uint16_t port_;
};

// version::services::none
BI_CONSTEXPR uint32_t no_services = 0;
BI_CONSTEXPR uint32_t no_timestamp = 0;
BI_CONSTEXPR uint16_t unspecified_ip_port = 0;
BI_CONSTEXPR ip_address unspecified_ip_address
{
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00
    }
};

// Defaults to full node services.
BI_CONSTEXPR network_address unspecified_network_address
{
    no_timestamp,
    no_services,
    unspecified_ip_address,
    unspecified_ip_port
};

} // namespace message
} // namespace libbitcoin

#endif
