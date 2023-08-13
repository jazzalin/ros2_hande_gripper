/*
 * Copyright (c) 2022, Giovanni Remigi
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <gtest/gtest.h>

#include "epick_driver/data_utils.hpp"
#include "epick_driver/default_driver.hpp"
#include "epick_driver/default_driver_utils.hpp"

#include "mock/mock_serial.hpp"

namespace epick_driver::test
{
using ::testing::_;
using ::testing::Return;
using ::testing::SaveArg;

/**
 * Here we test the driver activation command.
 */
TEST(TestDefaultDriver, activate)
{
  uint8_t slave_address = 0x09;

  // clang-format off
  const std::vector<uint8_t> expected_command{
    slave_address,
    static_cast<uint8_t>(default_driver_utils::FunctionCode::PresetMultipleRegisters),
    // Address of the first requested register - MSB, LSB.
    0x03, 0xE8,
    // Number of registers requested - MSB, LSB.
    0x00, 0x03,
    // Number of data bytes to follow.
    0x06,
    // Value written in the first register - MSB, LSB.
    0x01, 0x00,
    // Value written in the second register - MSB, LSB.
    0x00, 0x00,
    // Value written in the third register - MSB, LSB.
    0x00, 0x00,
    // CRC-16
    0x72, 0xE1
  };
  // clang-format on

  std::vector<uint8_t> actual_command;
  auto serial = std::make_unique<MockSerial>();
  EXPECT_CALL(*serial, write(_)).WillOnce(SaveArg<0>(&actual_command));

  auto driver = std::make_unique<epick_driver::DefaultDriver>(std::move(serial), slave_address);
  driver->activate();

  ASSERT_THAT(data_utils::to_hex(actual_command), data_utils::to_hex(expected_command));
}

/**
 * Here we test the driver deactivation command.
 */
TEST(TestDefaultDriver, deactivate)
{
  const uint8_t slave_address = 0x09;

  // clang-format off
  const std::vector<uint8_t> expected_command{
    slave_address,
    static_cast<uint8_t>(default_driver_utils::FunctionCode::PresetMultipleRegisters),
    // Address of the first requested register - MSB, LSB.
    0x03, 0xE8,
    // Number of registers requested - MSB, LSB.
    0x00, 0x03,
    // Number of data bytes to follow.
    0x06,
    // Value written in the first register - MSB, LSB.
    0x00, 0x00,
    // Value written in the second register - MSB, LSB.
    0x00, 0x00,
    // Value written in the third register - MSB, LSB.
    0x00, 0x00,
    // CRC-16
    0x73, 0x30
  };
  // clang-format on

  std::vector<uint8_t> actual_command;
  auto serial = std::make_unique<MockSerial>();
  EXPECT_CALL(*serial, write(_)).WillOnce(SaveArg<0>(&actual_command));

  auto driver = std::make_unique<epick_driver::DefaultDriver>(std::move(serial), slave_address);
  driver->deactivate();

  ASSERT_THAT(data_utils::to_hex(actual_command), data_utils::to_hex(expected_command));
}

TEST(TestDefaultDriver, set_max_vacuum_pressure)
{
  uint8_t slave_address = 0x09;

  // clang-format off
  const std::vector<uint8_t> expected_command{
    slave_address,
    static_cast<uint8_t>(default_driver_utils::FunctionCode::PresetSingleRegister),
    // Address of the first requested register - MSB, LSB.
    0x03, 0xE9,
    // Value written in the first register - MSB, LSB.
    0x00, 0x19, // Absolute pressure 25kPa, vacuum pressure -75kPa.
    // CRC-16
    0x98, 0xF8
  };
  // clang-format on

  std::vector<uint8_t> actual_command;
  auto serial = std::make_unique<MockSerial>();
  EXPECT_CALL(*serial, write(_)).WillOnce(SaveArg<0>(&actual_command));

  auto driver = std::make_unique<epick_driver::DefaultDriver>(std::move(serial), slave_address);
  driver->set_max_vacuum_pressure(-75);

  ASSERT_THAT(data_utils::to_hex(actual_command), data_utils::to_hex(expected_command));
}

}  // namespace epick_driver::test
