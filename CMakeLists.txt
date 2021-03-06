#
# Copyright (c) 2017-2018 Bitprim Inc.
#
# This file is part of Bitprim.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.4)

# bitprim-infrastructure
#==============================================================================
project(bitprim-infrastructure
  VERSION 0.11.0
  LANGUAGES CXX C)


#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#  # using Clang
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#  # using GCC
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
#  # using Intel C++
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
#  # using Visual Studio C++
#endif()
#if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#  # using regular Clang or AppleClang
#endif()

# message(CMAKE_CXX_COMPILER_ID)
# message(${CMAKE_CXX_COMPILER_ID})


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Check for baseline language coverage in the compiler for the C++14 standard.
#------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Process options.
#==============================================================================

# Implement --use-conan
#------------------------------------------------------------------------------
option(USE_CONAN "Use Conan Build Tool." OFF)
option(NO_CONAN_AT_ALL "Conan totally disabled." OFF)

if (NO_CONAN_AT_ALL)
  set(USE_CONAN OFF)
endif()


# Inherit --enable-shared and define BOOST_TEST_DYN_LINK.
#------------------------------------------------------------------------------
option(ENABLE_SHARED "" OFF)

# Implement POSITION_INDEPENDENT_CODE
#------------------------------------------------------------------------------
option(ENABLE_POSITION_INDEPENDENT_CODE "Enable POSITION_INDEPENDENT_CODE property" ON)

# Implement --with-tests and declare WITH_TESTS.
#------------------------------------------------------------------------------
option(WITH_TESTS "Compile with unit tests." ON)
option(WITH_TESTS_NEW "Compile with unit tests." OFF)

# Implement --with-examples and declare WITH_EXAMPLES.
#------------------------------------------------------------------------------
option(WITH_EXAMPLES "Compile with examples." OFF)


# Implement --with-icu and define BOOST_HAS_ICU and output ${icu}.
#------------------------------------------------------------------------------
option(WITH_ICU "Compile with International Components for Unicode." OFF)
if (WITH_ICU)
  add_definitions(-DWITH_ICU -DBOOST_HAS_ICU)
  if (NO_CONAN_AT_ALL)
    message(FATAL_ERROR "WITH_ICU not yet implemented")
  endif (NO_CONAN_AT_ALL)
endif()

# Implement --with-png and output ${png}.
#------------------------------------------------------------------------------
option(WITH_PNG "Compile with Libpng support." OFF)
if (WITH_PNG)
  add_definitions(-DWITH_PNG)
endif()


set(BITPRIM_BUILD_NUMBER "-" CACHE STRING "Specify the Bitprim Build Number.")
# message(${BITPRIM_BUILD_NUMBER})


# message( STATUS "1 NO_CONAN_AT_ALL: " ${NO_CONAN_AT_ALL} )
# message( STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR} )
# message( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )

if (EXISTS ${CMAKE_SOURCE_DIR}/bitprimbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/bitprimbuildinfo.cmake)
else()
    message( STATUS "bitprimbuildinfo doent exists")
endif()



# get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
# foreach( d ${DirDefs} )
#     message( STATUS "Found Define: " ${d} )
# endforeach()
# message( STATUS "DirDefs: " ${DirDefs} )

# remove_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
# remove_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)

# get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
# foreach( d ${DirDefs} )
#     message( STATUS "Found Define: " ${d} )
# endforeach()
# message( STATUS "DirDefs: " ${DirDefs} )

# if (NOT NO_CONAN_AT_ALL)
#   if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#       include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#       conan_basic_setup()

#       get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
#       foreach( d ${DirDefs} )
#         message( STATUS "Found Define: " ${d} )
#       endforeach()
#       message( STATUS "DirDefs: " ${DirDefs} )
  
#       remove_definitions(-D_GLIBCXX_USE_CXX11_ABI)

#       get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
#       foreach( d ${DirDefs} )
#         message( STATUS "Found Define: " ${d} )
#       endforeach()
#       message( STATUS "DirDefs: " ${DirDefs} )

#   else()
#       message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
#   endif()
# endif()


set(Boost_DEBUG ON)

# Check dependencies.
#==============================================================================

if (NO_CONAN_AT_ALL)
  # Require Boost of at least version 1.56.0 and output ${boost_CPPFLAGS/LDFLAGS}.
  #------------------------------------------------------------------------------
  if (NOT ENABLE_SHARED)
    set(Boost_USE_STATIC_LIBS ON)
  endif()

  if (MSVC)
    find_package(
      Boost 1.56.0 REQUIRED
      COMPONENTS atomic chrono date_time filesystem iostreams locale log log_setup program_options regex system thread unit_test_framework
    )
  else()
    find_package(
      Boost 1.56.0 REQUIRED
      COMPONENTS chrono date_time filesystem iostreams locale log program_options regex system thread unit_test_framework
    )
  endif()
endif()



# Require pthread and output ${pthread_CPPFLAGS/LIBS}.
#------------------------------------------------------------------------------
find_package(Threads REQUIRED)  #TODO(fernando): manage with conan

# Require png of at least version 1.6.25 and output ${png_CPPFLAGS/LIBS/PKG}.
#------------------------------------------------------------------------------
if (WITH_PNG)
    if (NO_CONAN_AT_ALL)
        find_package(PNG 1.6.25 REQUIRED)

        add_library(png INTERFACE IMPORTED)
        set_target_properties(png PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${PNG_INCLUDE_DIRS}"
            INTERFACE_LINK_LIBRARIES "${PNG_LIBRARIES}"
            INTERFACE_COMPILE_DEFINITIONS "${PNG_DEFINITIONS}")
    endif(NO_CONAN_AT_ALL)
endif()


# Require rt if on linux and output ${rt_LIBS}.
#------------------------------------------------------------------------------

# Require icu-i18n of at least version 51.2 and output ${icu_i18n_CPPFLAGS/LIBS/PKG}.
#------------------------------------------------------------------------------


if (NOT USE_CONAN)
# Require secp256k1 of at least version 0.0.1 and output ${secp256k1_CPPFLAGS/LIBS/PKG}.
#------------------------------------------------------------------------------
  if (NOT TARGET secp256k1)
    find_package(secp256k1 0.0.01 REQUIRED) 
  endif()
endif()


if (UNIX)
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/lib/cmake")
elseif (WIN32)
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "cmake")
endif()

# Set flags.
#==============================================================================
include(CheckCXXCompilerFlag)

# Including common functions
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(BitprimTools)


# Warn on all stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wall _has_all_warning_flag)
else()
  _add_c_compile_flag(-W4 _has_all_warning_flag)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Warn on extra stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wextra _has_extra_warning_flag)
endif()

# Be really annoying.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wpedantic _has_pedantic_warning_flag)
if (_has_pedantic_warning_flag)
  _add_c_compile_flag(-pedantic _has_pedantic_flag)
endif()

# Conform to style.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-missing-braces _has_no_missing_braces_warning_flag)

# Conflict in stdlib under clang. Enabled in clang only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-mismatched-tags _has_no_mismatched_tags_warning_flag)

# Clean up boost 1.55 headers. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wno-deprecated-declarations _has_no_deprecated_declarations_warning_flag)

# Protect stack.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector _has_stack_protector_flag)

# Protect stack comprehensively.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector-all _has_stack_protector_all_flag)

# Hide internal functions from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-hidden _has_visibility_hidden_flag)

# Hide inlines from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-inlines-hidden _has_visibility_inlines_hidden_flag)

# Target Windows Vista. Enabled in msvc only.
#------------------------------------------------------------------------------
if (MSVC) # OR MINGW)
  add_definitions(-D_WIN32_WINNT=0x0600)
endif()

# Build
#==============================================================================

# src/bitprim-infrastructure.la => ${libdir}
#------------------------------------------------------------------------------
set(MODE STATIC)
if (ENABLE_SHARED)
  set(MODE SHARED)
endif()

set(bitprim_infrastructure_sources 

        src/error.cpp
        # src/multi_crypto_support.cpp
        src/version.cpp


        src/log/file_collector.cpp
        src/log/file_collector_repository.cpp
        src/log/file_counter_formatter.cpp
        src/log/sink.cpp
        # src/log/statsd_sink.cpp
        src/log/udp_client_sink.cpp
        
        src/message/message_tools.cpp

        src/unicode/console_streambuf.cpp
        src/unicode/ifstream.cpp
        src/unicode/ofstream.cpp
        src/unicode/unicode.cpp
        src/unicode/unicode_istream.cpp
        src/unicode/unicode_ostream.cpp
        src/unicode/unicode_streambuf.cpp
        
        src/utility/binary.cpp
        src/utility/conditional_lock.cpp
        src/utility/deadline.cpp
        src/utility/dispatcher.cpp
        src/utility/flush_lock.cpp
        src/utility/interprocess_lock.cpp
        src/utility/istream_reader.cpp
        src/utility/monitor.cpp
        src/utility/ostream_writer.cpp
        
        src/utility/png.cpp
        src/utility/prioritized_mutex.cpp

        src/utility/random.cpp
        src/utility/scope_lock.cpp
        src/utility/sequencer.cpp
        src/utility/sequential_lock.cpp
        # src/utility/socket.cpp
        src/utility/string.cpp
        src/utility/thread.cpp
        src/utility/threadpool.cpp
        src/utility/work.cpp
      )



add_library(bitprim-infrastructure ${MODE} ${bitprim_infrastructure_sources})

if (ENABLE_POSITION_INDEPENDENT_CODE)
    set_property(TARGET bitprim-infrastructure PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)



#set_target_properties(bitprim-infrastructure PROPERTIES CXX_VISIBILITY_PRESET hidden)
#set_target_properties(bitprim-infrastructure PROPERTIES CXX_VISIBILITY_PRESET internal)

#-fvisibility=default|internal|hidden|protected


target_include_directories(bitprim-infrastructure PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  
if (NOT ENABLE_SHARED)
    target_compile_definitions(bitprim-infrastructure PUBLIC -DBI_STATIC) #TODO(fernando): manage with Conan????
endif()

target_compile_definitions(bitprim-infrastructure PUBLIC -DBITPRIM_BUILD_NUMBER="\\"${BITPRIM_BUILD_NUMBER}\\"") #TODO(fernando): manage with Conan????

target_include_directories(bitprim-infrastructure SYSTEM PUBLIC ${Boost_INCLUDE_DIR})

if (NOT NO_CONAN_AT_ALL)
  target_link_libraries(bitprim-infrastructure PUBLIC ${CONAN_LIBS})
else()
  if (MSVC)
    target_link_libraries(bitprim-infrastructure PUBLIC
      ${Boost_ATOMIC_LIBRARY}
      ${Boost_LOG_SETUP_LIBRARY}
    )
  endif()

  target_link_libraries(bitprim-infrastructure PUBLIC
    ${Boost_CHRONO_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_IOSTREAMS_LIBRARY}
    ${Boost_LOCALE_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_REGEX_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
  )
endif()

target_link_libraries(bitprim-infrastructure PUBLIC ${CMAKE_THREAD_LIBS_INIT})  #TODO(fernando): manage with Conan????

# if (NO_CONAN_AT_ALL)
    if (MINGW) #(WIN32)
        target_link_libraries(bitprim-infrastructure PUBLIC ws2_32 wsock32)
    endif()
# endif()

if (WITH_PNG)
    if (NO_CONAN_AT_ALL)
        target_link_libraries(bitprim-infrastructure PUBLIC png)
    endif (NO_CONAN_AT_ALL)
endif()

if (NOT USE_CONAN)
  target_link_libraries(bitprim-infrastructure PUBLIC secp256k1)
endif()

_group_sources(bitprim-infrastructure "${CMAKE_CURRENT_LIST_DIR}")

# Tests
#==============================================================================

if (WITH_TESTS OR WITH_TESTS_NEW)
  enable_testing()
endif()

# local: test/bitprim_infrastructure_test
#------------------------------------------------------------------------------
if (WITH_TESTS)

  add_executable(bitprim_infrastructure_test
        test/main.cpp
        test/unicode/unicode.cpp
        test/unicode/unicode_istream.cpp
        test/unicode/unicode_ostream.cpp
        test/utility/binary.cpp
        test/utility/collection.cpp
        test/utility/data.cpp
        test/utility/endian.cpp
        test/utility/png.cpp
        test/utility/random.cpp
        test/utility/serializer.cpp
        test/utility/stream.cpp
        test/utility/thread.cpp
        # test/utility/variable_uint_size.cpp
    )

# Simplified Test Project for testing Packaging purposes

  # add_executable(bitprim_infrastructure_test
  # test/main.cpp
  # )

    target_link_libraries(bitprim_infrastructure_test PUBLIC bitprim-infrastructure)

_group_sources(bitprim_infrastructure_test "${CMAKE_CURRENT_LIST_DIR}/test")

#    TODO: Fer: chequear si hay nuevos tests en los makefiles (no Cmake)
  _add_tests(bitprim_infrastructure_test
    binary_tests
    collection_tests
    data_tests
    # TODO: encrypted_tests ???
    endian_tests

    # TODO: printer_tests ???

    random_tests
    serializer_tests
    stream_tests
    thread_tests
    unicode_istream_tests
    unicode_ostream_tests
    unicode_tests
    )

  if (WITH_PNG)
    _add_tests(bitprim_infrastructure_test png_tests)
  endif()
endif()

if (WITH_TESTS_NEW)

  add_custom_target(testsfer ALL
      COMMAND ${CMAKE_CTEST_COMMAND} -C Debug --output-on-failure -R "test.+"
      COMMENT "Build and run all the unit tests.")

  add_executable(bitprim_infrastructure_test_new
          test_new/main.cpp
  )

  target_link_libraries(bitprim_infrastructure_test_new PUBLIC bitprim-infrastructure)

  # _group_sources(bitprim_infrastructure_test_new "${CMAKE_CURRENT_LIST_DIR}/test_new")

  add_test(NAME test.new_tests COMMAND bitprim_infrastructure_test_new)

  add_dependencies(testsfer test.new_tests)

#    add_test(
#            NAME test.infrastructure.new_tests
#            COMMAND ${target}
#            --run_test=${_test_name}
#            --show_progress=no
#            --detect_memory_leak=0
#            --report_level=no
#            --build_info=yes)

endif()

# Examples
#==============================================================================
# local: examples/bitprim_infrastructure_examples
#------------------------------------------------------------------------------
if (WITH_EXAMPLES)
  add_executable(bitprim_infrastructure_examples
    examples/main.cpp)


  target_link_libraries(bitprim_infrastructure_examples PUBLIC bitprim-infrastructure)

  _group_sources(bitprim_infrastructure_examples "${CMAKE_CURRENT_LIST_DIR}/examples")
endif()

# Install
#==============================================================================
install(TARGETS bitprim-infrastructure EXPORT bitprim-infrastructure
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

#install(EXPORT bitprim-infrastructureTargets
#
#)

set(_bitprim_infrastructure_headers
    # bitcoin/infrastructure/multi_crypto_support.hpp
    bitcoin/infrastructure/compat.h
    bitcoin/infrastructure/compat.hpp
    bitcoin/infrastructure/constants.hpp
    bitcoin/infrastructure/define.hpp
    bitcoin/infrastructure/error.hpp
    bitcoin/infrastructure/handlers.hpp
    bitcoin/infrastructure/version.hpp

    bitcoin/infrastructure/impl/log/features/counter.ipp
    bitcoin/infrastructure/impl/log/features/gauge.ipp
    bitcoin/infrastructure/impl/log/features/metric.ipp
    bitcoin/infrastructure/impl/log/features/rate.ipp
    bitcoin/infrastructure/impl/log/features/timer.ipp


    bitcoin/infrastructure/impl/utility/array_slice.ipp
    bitcoin/infrastructure/impl/utility/collection.ipp
    bitcoin/infrastructure/impl/utility/data.ipp
    bitcoin/infrastructure/impl/utility/deserializer.ipp
    bitcoin/infrastructure/impl/utility/endian.ipp
    bitcoin/infrastructure/impl/utility/istream_reader.ipp
    bitcoin/infrastructure/impl/utility/ostream_writer.ipp
    bitcoin/infrastructure/impl/utility/pending.ipp    
    bitcoin/infrastructure/impl/utility/resubscriber.ipp
    bitcoin/infrastructure/impl/utility/serializer.ipp
    bitcoin/infrastructure/impl/utility/subscriber.ipp
    bitcoin/infrastructure/impl/utility/track.ipp

    bitcoin/infrastructure/log/attributes.hpp
    bitcoin/infrastructure/log/file_char_traits.hpp
    bitcoin/infrastructure/log/file_collector.hpp
    bitcoin/infrastructure/log/file_collector_repository.hpp
    bitcoin/infrastructure/log/file_counter_formatter.hpp
    bitcoin/infrastructure/log/rotable_file.hpp    
    bitcoin/infrastructure/log/severity.hpp
    bitcoin/infrastructure/log/sink.hpp
    bitcoin/infrastructure/log/source.hpp
    # bitcoin/infrastructure/log/statsd_sink.hpp
    bitcoin/infrastructure/log/statsd_source.hpp
    bitcoin/infrastructure/log/udp_client_sink.hpp

    bitcoin/infrastructure/log/features/counter.hpp
    bitcoin/infrastructure/log/features/gauge.hpp
    bitcoin/infrastructure/log/features/metric.hpp
    bitcoin/infrastructure/log/features/rate.hpp
    bitcoin/infrastructure/log/features/timer.hpp

    bitcoin/infrastructure/message/message_tools.hpp

    bitcoin/infrastructure/unicode/console_streambuf.hpp
    bitcoin/infrastructure/unicode/file_lock.hpp
    bitcoin/infrastructure/unicode/ifstream.hpp
    bitcoin/infrastructure/unicode/ofstream.hpp
    bitcoin/infrastructure/unicode/unicode.hpp
    bitcoin/infrastructure/unicode/unicode_istream.hpp
    bitcoin/infrastructure/unicode/unicode_ostream.hpp
    bitcoin/infrastructure/unicode/unicode_streambuf.hpp

    bitcoin/infrastructure/utility/array_slice.hpp
    bitcoin/infrastructure/utility/asio.hpp
    bitcoin/infrastructure/utility/assert.hpp
    bitcoin/infrastructure/utility/atomic.hpp
    bitcoin/infrastructure/utility/binary.hpp
    bitcoin/infrastructure/utility/collection.hpp
    bitcoin/infrastructure/utility/color.hpp
    bitcoin/infrastructure/utility/conditional_lock.hpp
    bitcoin/infrastructure/utility/container_sink.hpp
    bitcoin/infrastructure/utility/container_source.hpp
    bitcoin/infrastructure/utility/data.hpp
    bitcoin/infrastructure/utility/deadline.hpp
    bitcoin/infrastructure/utility/decorator.hpp
    bitcoin/infrastructure/utility/delegates.hpp
    bitcoin/infrastructure/utility/deserializer.hpp
    bitcoin/infrastructure/utility/dispatcher.hpp
    bitcoin/infrastructure/utility/enable_shared_from_base.hpp
    bitcoin/infrastructure/utility/endian.hpp
    bitcoin/infrastructure/utility/exceptions.hpp
    bitcoin/infrastructure/utility/flush_lock.hpp
    bitcoin/infrastructure/utility/interprocess_lock.hpp
    bitcoin/infrastructure/utility/istream_reader.hpp
    bitcoin/infrastructure/utility/monitor.hpp
    bitcoin/infrastructure/utility/noncopyable.hpp
    bitcoin/infrastructure/utility/ostream_writer.hpp
    bitcoin/infrastructure/utility/pending.hpp

    bitcoin/infrastructure/utility/png.hpp
    bitcoin/infrastructure/utility/prioritized_mutex.hpp

    bitcoin/infrastructure/utility/random.hpp
    bitcoin/infrastructure/utility/reader.hpp
    bitcoin/infrastructure/utility/resubscriber.hpp
    bitcoin/infrastructure/utility/scope_lock.hpp
    bitcoin/infrastructure/utility/sequencer.hpp
    bitcoin/infrastructure/utility/sequential_lock.hpp
    bitcoin/infrastructure/utility/serializer.hpp
    # bitcoin/infrastructure/utility/socket.hpp    
    bitcoin/infrastructure/utility/string.hpp
    bitcoin/infrastructure/utility/subscriber.hpp
    bitcoin/infrastructure/utility/synchronizer.hpp
    bitcoin/infrastructure/utility/thread.hpp
    bitcoin/infrastructure/utility/threadpool.hpp
    bitcoin/infrastructure/utility/timer.hpp
    bitcoin/infrastructure/utility/track.hpp
    bitcoin/infrastructure/utility/work.hpp
    bitcoin/infrastructure/utility/writer.hpp
    
    bitcoin/bitcoin.hpp
    )

foreach (_header ${_bitprim_infrastructure_headers})
  get_filename_component(_directory "${_header}" DIRECTORY)
  install(FILES "include/${_header}" DESTINATION "include/${_directory}")
endforeach()

# Export
#==============================================================================
include(CMakePackageConfigHelpers)

export(EXPORT bitprim-infrastructure
  FILE "${CMAKE_CURRENT_BINARY_DIR}/bitprim-infrastructureTargets.cmake")
export(PACKAGE bitprim-infrastructure)

if (UNIX)
  set(_config_package_location "lib/cmake")
elseif (WIN32)
  set(_config_package_location "cmake")
endif()

install(EXPORT bitprim-infrastructure
  FILE bitprim-infrastructureTargets.cmake
  DESTINATION ${_config_package_location})

configure_file(bitprim-infrastructureConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/bitprim-infrastructureConfig.cmake"
  @ONLY)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/bitprim-infrastructureConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/bitprim-infrastructureConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/bitprim-infrastructureConfigVersion.cmake"
  DESTINATION ${_config_package_location})
