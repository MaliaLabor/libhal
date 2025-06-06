// Copyright 2024 - 2025 Khalil Estell and the libhal contributors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <libhal/dac.hpp>

#include <libhal/error.hpp>

#include <boost/ut.hpp>

namespace hal {
namespace {
class test_dac16 : public hal::dac16
{
public:
  static constexpr auto expected_value = u16(5123);
  float m_passed_value{};
  ~test_dac16() override = default;

private:
  void driver_write(u16 p_value) override
  {
    m_passed_value = p_value;
  }
};
}  // namespace

boost::ut::suite<"dac16_test"> dac16_test = []() {
  {
    using namespace boost::ut;

    "dac interface test"_test = []() {
      using namespace boost::ut;
      // Setup
      test_dac16 test;

      // Exercise
      test.write(test_dac16::expected_value);

      // Verify
      expect(that % test_dac16::expected_value == test.m_passed_value);
    };
  };
};
}  // namespace hal

namespace hal {
namespace {
class test_dac : public hal::dac
{
public:
  static constexpr auto expected_value = float(0.5);
  float m_passed_value{};
  ~test_dac() override = default;

private:
  void driver_write(float p_value) override
  {
    m_passed_value = p_value;
  }
};
}  // namespace

boost::ut::suite<"dac_test"> dac_test = []() {
  {
    using namespace boost::ut;

    "dac interface test"_test = []() {
      using namespace boost::ut;
      // Setup
      test_dac test;

      // Exercise
      test.write(test_dac::expected_value);

      // Verify
      expect(that % test_dac::expected_value == test.m_passed_value);
    };
  };
};
}  // namespace hal
