///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014-2015 libbitcoin developers (see COPYING).
//
//        GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
//
///////////////////////////////////////////////////////////////////////////////
#ifndef LIBBITCOIN_INFRASTRUCTURE_BITCOIN_HPP
#define LIBBITCOIN_INFRASTRUCTURE_BITCOIN_HPP

/**
 * API Users: Include only this header. Direct use of other headers is fragile
 * and unsupported as header organization is subject to change.
 *
 * Maintainers: Do not include this header internal to this library.
 */

#include <bitcoin/infrastructure/compat.h>
#include <bitcoin/infrastructure/compat.hpp>
#include <bitcoin/infrastructure/constants.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/error.hpp>
#include <bitcoin/infrastructure/handlers.hpp>
#include <bitcoin/infrastructure/version.hpp>
#include <bitcoin/infrastructure/chain/block.hpp>
#include <bitcoin/infrastructure/chain/chain_state.hpp>
#include <bitcoin/infrastructure/chain/compact.hpp>
#include <bitcoin/infrastructure/chain/header.hpp>
#include <bitcoin/infrastructure/chain/history.hpp>
#include <bitcoin/infrastructure/chain/input.hpp>
#include <bitcoin/infrastructure/chain/input_point.hpp>
#include <bitcoin/infrastructure/chain/output.hpp>
#include <bitcoin/infrastructure/chain/output_point.hpp>
#include <bitcoin/infrastructure/chain/point.hpp>
#include <bitcoin/infrastructure/chain/point_iterator.hpp>
#include <bitcoin/infrastructure/chain/point_value.hpp>
#include <bitcoin/infrastructure/chain/points_value.hpp>
#include <bitcoin/infrastructure/chain/script.hpp>
#include <bitcoin/infrastructure/chain/stealth.hpp>
#include <bitcoin/infrastructure/chain/transaction.hpp>
#include <bitcoin/infrastructure/chain/witness.hpp>
#include <bitcoin/infrastructure/config/authority.hpp>
#include <bitcoin/infrastructure/config/base16.hpp>
#include <bitcoin/infrastructure/config/base2.hpp>
#include <bitcoin/infrastructure/config/base58.hpp>
#include <bitcoin/infrastructure/config/base64.hpp>
#include <bitcoin/infrastructure/config/checkpoint.hpp>
#include <bitcoin/infrastructure/config/directory.hpp>
#include <bitcoin/infrastructure/config/endpoint.hpp>
#include <bitcoin/infrastructure/config/hash160.hpp>
#include <bitcoin/infrastructure/config/hash256.hpp>
#include <bitcoin/infrastructure/config/parameter.hpp>
#include <bitcoin/infrastructure/config/parser.hpp>
#include <bitcoin/infrastructure/config/printer.hpp>
#include <bitcoin/infrastructure/config/settings.hpp>
#include <bitcoin/infrastructure/config/sodium.hpp>
#include <bitcoin/infrastructure/formats/base_10.hpp>
#include <bitcoin/infrastructure/formats/base_16.hpp>
#include <bitcoin/infrastructure/formats/base_58.hpp>
#include <bitcoin/infrastructure/formats/base_64.hpp>
#include <bitcoin/infrastructure/formats/base_85.hpp>
#include <bitcoin/infrastructure/log/attributes.hpp>
#include <bitcoin/infrastructure/log/file_char_traits.hpp>
#include <bitcoin/infrastructure/log/file_collector.hpp>
#include <bitcoin/infrastructure/log/file_collector_repository.hpp>
#include <bitcoin/infrastructure/log/file_counter_formatter.hpp>
#include <bitcoin/infrastructure/log/rotable_file.hpp>
#include <bitcoin/infrastructure/log/severity.hpp>
#include <bitcoin/infrastructure/log/sink.hpp>
#include <bitcoin/infrastructure/log/source.hpp>
#include <bitcoin/infrastructure/log/statsd_sink.hpp>
#include <bitcoin/infrastructure/log/statsd_source.hpp>
#include <bitcoin/infrastructure/log/udp_client_sink.hpp>
#include <bitcoin/infrastructure/log/features/counter.hpp>
#include <bitcoin/infrastructure/log/features/gauge.hpp>
#include <bitcoin/infrastructure/log/features/metric.hpp>
#include <bitcoin/infrastructure/log/features/rate.hpp>
#include <bitcoin/infrastructure/log/features/timer.hpp>
#include <bitcoin/infrastructure/machine/interpreter.hpp>
#include <bitcoin/infrastructure/machine/number.hpp>
#include <bitcoin/infrastructure/machine/opcode.hpp>
#include <bitcoin/infrastructure/machine/operation.hpp>
#include <bitcoin/infrastructure/machine/program.hpp>
#include <bitcoin/infrastructure/machine/rule_fork.hpp>
#include <bitcoin/infrastructure/machine/script_pattern.hpp>
#include <bitcoin/infrastructure/machine/script_version.hpp>
#include <bitcoin/infrastructure/machine/sighash_algorithm.hpp>
#include <bitcoin/infrastructure/math/checksum.hpp>
#include <bitcoin/infrastructure/math/crypto.hpp>
#include <bitcoin/infrastructure/math/elliptic_curve.hpp>
#include <bitcoin/infrastructure/math/hash.hpp>
#include <bitcoin/infrastructure/math/limits.hpp>
#include <bitcoin/infrastructure/math/stealth.hpp>
#include <bitcoin/infrastructure/math/uint256.hpp>
#include <bitcoin/infrastructure/message/address.hpp>
#include <bitcoin/infrastructure/message/alert.hpp>
#include <bitcoin/infrastructure/message/alert_payload.hpp>
#include <bitcoin/infrastructure/message/block.hpp>
#include <bitcoin/infrastructure/message/block_transactions.hpp>
#include <bitcoin/infrastructure/message/compact_block.hpp>
#include <bitcoin/infrastructure/message/fee_filter.hpp>
#include <bitcoin/infrastructure/message/filter_add.hpp>
#include <bitcoin/infrastructure/message/filter_clear.hpp>
#include <bitcoin/infrastructure/message/filter_load.hpp>
#include <bitcoin/infrastructure/message/get_address.hpp>
#include <bitcoin/infrastructure/message/get_block_transactions.hpp>
#include <bitcoin/infrastructure/message/get_blocks.hpp>
#include <bitcoin/infrastructure/message/get_data.hpp>
#include <bitcoin/infrastructure/message/get_headers.hpp>
#include <bitcoin/infrastructure/message/header.hpp>
#include <bitcoin/infrastructure/message/headers.hpp>
#include <bitcoin/infrastructure/message/heading.hpp>
#include <bitcoin/infrastructure/message/inventory.hpp>
#include <bitcoin/infrastructure/message/inventory_vector.hpp>
#include <bitcoin/infrastructure/message/memory_pool.hpp>
#include <bitcoin/infrastructure/message/merkle_block.hpp>
#include <bitcoin/infrastructure/message/messages.hpp>
#include <bitcoin/infrastructure/message/network_address.hpp>
#include <bitcoin/infrastructure/message/not_found.hpp>
#include <bitcoin/infrastructure/message/ping.hpp>
#include <bitcoin/infrastructure/message/pong.hpp>
#include <bitcoin/infrastructure/message/prefilled_transaction.hpp>
#include <bitcoin/infrastructure/message/reject.hpp>
#include <bitcoin/infrastructure/message/send_compact.hpp>
#include <bitcoin/infrastructure/message/send_headers.hpp>
#include <bitcoin/infrastructure/message/transaction.hpp>
#include <bitcoin/infrastructure/message/verack.hpp>
#include <bitcoin/infrastructure/message/version.hpp>
#include <bitcoin/infrastructure/unicode/console_streambuf.hpp>
#include <bitcoin/infrastructure/unicode/file_lock.hpp>
#include <bitcoin/infrastructure/unicode/ifstream.hpp>
#include <bitcoin/infrastructure/unicode/ofstream.hpp>
#include <bitcoin/infrastructure/unicode/unicode.hpp>
#include <bitcoin/infrastructure/unicode/unicode_istream.hpp>
#include <bitcoin/infrastructure/unicode/unicode_ostream.hpp>
#include <bitcoin/infrastructure/unicode/unicode_streambuf.hpp>
#include <bitcoin/infrastructure/utility/array_slice.hpp>
#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/assert.hpp>
#include <bitcoin/infrastructure/utility/atomic.hpp>
#include <bitcoin/infrastructure/utility/binary.hpp>
#include <bitcoin/infrastructure/utility/collection.hpp>
#include <bitcoin/infrastructure/utility/color.hpp>
#include <bitcoin/infrastructure/utility/conditional_lock.hpp>
#include <bitcoin/infrastructure/utility/container_sink.hpp>
#include <bitcoin/infrastructure/utility/container_source.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
#include <bitcoin/infrastructure/utility/deadline.hpp>
#include <bitcoin/infrastructure/utility/decorator.hpp>
#include <bitcoin/infrastructure/utility/delegates.hpp>
#include <bitcoin/infrastructure/utility/deserializer.hpp>
#include <bitcoin/infrastructure/utility/dispatcher.hpp>
#include <bitcoin/infrastructure/utility/enable_shared_from_base.hpp>
#include <bitcoin/infrastructure/utility/endian.hpp>
#include <bitcoin/infrastructure/utility/exceptions.hpp>
#include <bitcoin/infrastructure/utility/flush_lock.hpp>
#include <bitcoin/infrastructure/utility/interprocess_lock.hpp>
#include <bitcoin/infrastructure/utility/istream_reader.hpp>
#include <bitcoin/infrastructure/utility/monitor.hpp>
#include <bitcoin/infrastructure/utility/noncopyable.hpp>
#include <bitcoin/infrastructure/utility/ostream_writer.hpp>
#include <bitcoin/infrastructure/utility/pending.hpp>
#include <bitcoin/infrastructure/utility/png.hpp>
#include <bitcoin/infrastructure/utility/prioritized_mutex.hpp>
#include <bitcoin/infrastructure/utility/pseudo_random.hpp>
#include <bitcoin/infrastructure/utility/reader.hpp>
#include <bitcoin/infrastructure/utility/resubscriber.hpp>
#include <bitcoin/infrastructure/utility/scope_lock.hpp>
#include <bitcoin/infrastructure/utility/sequencer.hpp>
#include <bitcoin/infrastructure/utility/sequential_lock.hpp>
#include <bitcoin/infrastructure/utility/serializer.hpp>
#include <bitcoin/infrastructure/utility/socket.hpp>
#include <bitcoin/infrastructure/utility/string.hpp>
#include <bitcoin/infrastructure/utility/subscriber.hpp>
#include <bitcoin/infrastructure/utility/synchronizer.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>
#include <bitcoin/infrastructure/utility/threadpool.hpp>
#include <bitcoin/infrastructure/utility/timer.hpp>
#include <bitcoin/infrastructure/utility/track.hpp>
#include <bitcoin/infrastructure/utility/work.hpp>
#include <bitcoin/infrastructure/utility/writer.hpp>
#include <bitcoin/infrastructure/wallet/bitcoin_uri.hpp>
#include <bitcoin/infrastructure/wallet/dictionary.hpp>
#include <bitcoin/infrastructure/wallet/ec_private.hpp>
#include <bitcoin/infrastructure/wallet/ec_public.hpp>
#include <bitcoin/infrastructure/wallet/ek_private.hpp>
#include <bitcoin/infrastructure/wallet/ek_public.hpp>
#include <bitcoin/infrastructure/wallet/ek_token.hpp>
#include <bitcoin/infrastructure/wallet/encrypted_keys.hpp>
#include <bitcoin/infrastructure/wallet/hd_private.hpp>
#include <bitcoin/infrastructure/wallet/hd_public.hpp>
#include <bitcoin/infrastructure/wallet/message.hpp>
#include <bitcoin/infrastructure/wallet/mini_keys.hpp>
#include <bitcoin/infrastructure/wallet/mnemonic.hpp>
#include <bitcoin/infrastructure/wallet/payment_address.hpp>
#include <bitcoin/infrastructure/wallet/qrcode.hpp>
#include <bitcoin/infrastructure/wallet/select_outputs.hpp>
#include <bitcoin/infrastructure/wallet/stealth_address.hpp>
#include <bitcoin/infrastructure/wallet/stealth_receiver.hpp>
#include <bitcoin/infrastructure/wallet/stealth_sender.hpp>
#include <bitcoin/infrastructure/wallet/uri.hpp>
#include <bitcoin/infrastructure/wallet/uri_reader.hpp>

#endif
