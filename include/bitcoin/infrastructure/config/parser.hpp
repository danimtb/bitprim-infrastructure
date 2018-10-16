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
#ifndef LIBBITCOIN_INFRASTUCTURE_CONFIG_PARSER_HPP
#define LIBBITCOIN_INFRASTUCTURE_CONFIG_PARSER_HPP

#include <string>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <bitcoin/infrastructure/config/checkpoint.hpp>
#include <bitcoin/infrastructure/define.hpp>

namespace libbitcoin {

// These are just annoyingly long.
using variables_map = boost::program_options::variables_map;
using option_metadata = boost::program_options::option_description;
using options_metadata = boost::program_options::options_description;
using arguments_metadata = boost::program_options::positional_options_description;

namespace config {

enum class load_error { 
    non_existing_file = -1, 
    default_config = 0, 
    success = 1 
};

/// Parse configurable values from environment variables, settings file, and
/// command line positional and non-positional options.
class BI_API parser {
public:
    static 
    std::string format_invalid_parameter(std::string const& message);
    
    static 
    bool get_option(variables_map& variables, std::string const& name);
    
    static 
    boost::filesystem::path get_config_option(variables_map& variables, std::string const& name);

    /// Load command line options (named).
    virtual 
    options_metadata load_options() = 0;

    /// Load command line arguments (positional).
    virtual 
    arguments_metadata load_arguments() = 0;

    /// Load environment variable settings.
    virtual 
    options_metadata load_environment() = 0;

    /// Load configuration file settings.
    virtual 
    options_metadata load_settings() = 0;

protected:
    virtual 
    void load_command_variables(variables_map& variables, int argc, char const* argv[]);

    virtual 
    // int load_configuration_variables(variables_map& variables, std::string const& option_name);
    load_error load_configuration_variables(variables_map& variables, std::string const& option_name);

    virtual    
    load_error load_configuration_variables_path(variables_map& variables, boost::filesystem::path const& config_path);

    virtual 
    void load_environment_variables(variables_map& variables, std::string const& prefix);

};

}} // namespace libbitcoin::config

#endif
