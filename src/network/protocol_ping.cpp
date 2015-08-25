/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/bitcoin/network/protocol_ping.hpp>

#include <functional>
#include <bitcoin/bitcoin/message/ping_pong.hpp>
#include <bitcoin/bitcoin/network/channel.hpp>
#include <bitcoin/bitcoin/network/timeout.hpp>
#include <bitcoin/bitcoin/network/protocol_base.hpp>
#include <bitcoin/bitcoin/utility/assert.hpp>
#include <bitcoin/bitcoin/utility/random.hpp>
#include <bitcoin/bitcoin/utility/dispatcher.hpp>
#include <bitcoin/bitcoin/utility/threadpool.hpp>

INITIALIZE_TRACK(bc::network::protocol_ping);

namespace libbitcoin {
namespace network {
    
using namespace bc::message;
using std::placeholders::_1;
using std::placeholders::_2;
#define CLASS protocol_ping

protocol_ping::protocol_ping(channel::ptr channel, threadpool& pool,
    const asio::duration& period)
  : protocol_base(channel, pool, period),
    track<protocol_ping>("protocol_ping", LOG_NETWORK)
{
}

void protocol_ping::start()
{
    protocol_base::start();

    // Unfortunately this cannt be set on construct because of the inability of
    // shared_from_this to execute within a constructor.
    set_callback(BIND1(send_ping, _1));

    SUBSCRIBE2(ping, handle_receive_ping, _1, _2);

    // Send initial ping message by simulating first heartbeat.
    callback(error::success);
}

// This is fired by the callback (i.e. base timer and stop handler).
void protocol_ping::send_ping(const code& ec)
{
    if (stopped() || deadline::canceled(ec))
        return;

    const auto nonce = pseudo_random();

    SUBSCRIBE3(pong, handle_receive_pong, _1, _2, nonce);
    SEND1(message::ping(nonce), handle_send_ping, _1);
}

void protocol_ping::handle_receive_ping(const code& ec,
    const message::ping& message)
{
    if (stopped())
        return;

    if (ec)
    {
        log_debug(LOG_NETWORK)
            << "Failure getting ping from [" << authority() << "]";
        stop(error::bad_stream);
        return;
    }

    // Resubscribe to ping messages.
    SUBSCRIBE2(ping, handle_receive_ping, _1, _2);
    SEND1(message::pong(message.nonce), handle_send_pong, _1);
}

void protocol_ping::handle_receive_pong(const code& ec,
    const message::pong& message, uint64_t nonce)
{
    if (stopped())
        return;

    if (ec)
    {
        log_debug(LOG_NETWORK)
            << "Failure getting pong from [" << authority() << "]";
        return;
    }

    if (message.nonce != nonce)
    {
        log_warning(LOG_NETWORK)
            << "Invalid pong nonce from [" << authority() << "]";

        // This could result from message overlap due to a short period,
        // but we assume the response is not as expected and terminate.
        stop(error::bad_stream);
    }
}

void protocol_ping::handle_send_ping(const code& ec) const
{
    if (stopped())
        return;

    if (ec)
        log_debug(LOG_NETWORK)
            << "Failure sending ping to [" << authority() << "] "
            << ec.message();
}

void protocol_ping::handle_send_pong(const code& ec) const
{
    if (stopped())
        return;

    if (ec)
        log_debug(LOG_NETWORK)
            << "Failure sending pong to [" << authority() << "] "
            << ec.message();
}

#undef CLASS

} // namespace network
} // namespace libbitcoin
