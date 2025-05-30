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

#include <libhal/units.hpp>

#include "helpers.hpp"

#include <boost/ut.hpp>

namespace hal {

boost::ut::suite<"lengths_test"> lengths_test = []() {
  using namespace hal::literals;
  using namespace boost::ut;
  constexpr float meters_in_inches = 0.0254f;
  constexpr float meters_in_yards = 0.9144f;
  constexpr float meters_in_miles = 1609.344f;

  // ensuring that the expected value is returned upon creation
  "Lengths_Type UDL_Creation Test"_test = []() {
    meters micrometer = 1.0_um, millimeter = 1.0_mm, meter = 1.0_m,
           kilometer = 1.0_km, inch = 1.0_inch, yard = 1.0_yards,
           mile = 1.0_miles;

    expect(that %
           compare_floats({ .a = micrometer,
                            .b = static_cast<float>(1.0f / std::micro::den) }));
    expect(that %
           compare_floats({ .a = millimeter,
                            .b = static_cast<float>(1.0f / std::milli::den) }));
    expect(that % compare_floats({ .a = meter, .b = 1.0f }));
    expect(that %
           compare_floats({ .a = kilometer,
                            .b = static_cast<float>(1.0f * std::kilo::num) }));
    expect(that % compare_floats({ .a = inch, .b = meters_in_inches }));
    expect(that % compare_floats({ .a = yard, .b = meters_in_yards }));
    expect(that % compare_floats({ .a = mile, .b = meters_in_miles }));
  };

  // ensuring that when you overwrite another UDL of type Lengths
  // it will remain the value from the assigned variable
  "Lengths_Type Equality Test"_test = []() {
    meters micrometer = 1.0_um, millimeter = 1.0_mm, meter = 1.0_m,
           kilometer = 1.0_km, inch = 1.0_inch, yard = 1.0_yards,
           mile = 1.0_miles;
    meter = micrometer;
    expect(that % compare_floats({ .a = meter, .b = micrometer }));

    meter = millimeter;
    expect(that % compare_floats({ .a = meter, .b = millimeter }));

    meter = kilometer;
    expect(that % compare_floats({ .a = meter, .b = kilometer }));

    meter = inch;
    expect(that % compare_floats({ .a = meter, .b = inch }));

    meter = yard;
    expect(that % compare_floats({ .a = meter, .b = yard }));

    meter = mile;
    expect(that % compare_floats({ .a = meter, .b = mile }));
  };

  // ensures that all micrometer math operators work
  "Lengths_Type Micrometer_Calculation Test"_test = []() {
    meters micrometer_result = 1.0_um * 1000.0f;
    expect(that % compare_floats({ .a = micrometer_result, .b = 1.0_mm }));

    micrometer_result /= 1000.0f;
    expect(that % compare_floats({ .a = micrometer_result, .b = 1.0_um }));

    micrometer_result = 1.0_um + 1.0_um;
    expect(that % compare_floats({ .a = micrometer_result, .b = 2.0_um }));

    micrometer_result -= 1.0_um;
    expect(that % compare_floats({ .a = micrometer_result, .b = 1.0_um }));
  };

  // ensures that all millimeter math operators work
  "Lengths_Type Millimeter_Calculation Test"_test = []() {
    meters millimeter_result = 1.0_mm * 1000.0f;
    expect(that % compare_floats({ .a = millimeter_result, .b = 1.0_m }));

    millimeter_result /= 1000.0f;
    expect(that % compare_floats({ .a = millimeter_result, .b = 1.0_mm }));

    millimeter_result = 1.0_mm + 1.0_mm;
    expect(that % compare_floats({ .a = millimeter_result, .b = 2.0_mm }));

    millimeter_result -= 1.0_mm;
    expect(that % compare_floats({ .a = millimeter_result, .b = 1.0_mm }));
  };

  // ensures that all meter math operators work
  "Lengths_Type Meter_Calculation Test"_test = []() {
    meters meter_result = 1.0_m * 1000.0f;
    expect(that % compare_floats({ .a = meter_result, .b = 1.0_km }));

    meter_result /= 1000.0f;
    expect(that % compare_floats({ .a = meter_result, .b = 1.0_m }));

    meter_result = 1.0_m + 1.0_m;
    expect(that % compare_floats({ .a = meter_result, .b = 2.0_m }));

    meter_result -= 1.0_m;
    expect(that % compare_floats({ .a = meter_result, .b = 1.0_m }));
  };

  // ensures that all kilometer math operators work
  "Lengths_Type Kilometer_Calculation Test"_test = []() {
    meters kilometer_result = 1.0_km * 1000.0f;
    expect(that % compare_floats({ .a = kilometer_result, .b = 1000.0_km }));

    kilometer_result /= 1000.0f;
    expect(that % compare_floats({ .a = kilometer_result, .b = 1.0_km }));

    kilometer_result = 1.0_km + 1.0_km;
    expect(that % compare_floats({ .a = kilometer_result, .b = 2.0_km }));

    kilometer_result -= 1.0_km;
    expect(that % compare_floats({ .a = kilometer_result, .b = 1.0_km }));
  };

  // ensures that all inch math operators work
  "Lengths_Type Inch_Calculation Test"_test = []() {
    meters inch_result = 1.0_inch * 1000.0f;
    expect(that % compare_floats({ .a = inch_result, .b = 1000.0_inch }));

    inch_result /= 1000.0f;
    expect(that % compare_floats({ .a = inch_result, .b = 1.0_inch }));

    inch_result = 1.0_inch + 1.0_inch;
    expect(that % compare_floats({ .a = inch_result, .b = 2.0_inch }));

    inch_result -= 1.0_inch;
    expect(that % compare_floats({ .a = inch_result, .b = 1.0_inch }));
  };

  // ensures that all yard math operators work
  "Lengths_Type Yards_Calculation Test"_test = []() {
    meters yard_result = 1.0_yards * 1000.0f;
    expect(that % compare_floats({ .a = yard_result, .b = 1000.0_yards }));

    yard_result /= 1000.0f;
    expect(that % compare_floats({ .a = yard_result, .b = 1.0_yards }));

    yard_result = 1.0_yards + 1.0_yards;
    expect(that % compare_floats({ .a = yard_result, .b = 2.0_yards }));

    yard_result -= 1.0_yards;
    expect(that % compare_floats({ .a = yard_result, .b = 1.0_yards }));
  };

  // ensures that all mile math operators work
  "Lengths_Type Miles_Calculation Test"_test = []() {
    meters mile_result = 1.0_miles * 1000.0f;
    expect(that % compare_floats({ .a = mile_result, .b = 1000.0_miles }));

    mile_result /= 1000.0f;
    expect(that % compare_floats({ .a = mile_result, .b = 1.0_miles }));

    mile_result = 1.0_miles + 1.0_miles;
    expect(that % compare_floats({ .a = mile_result, .b = 2.0_miles }));

    mile_result -= 1.0_miles;
    expect(that % compare_floats({ .a = mile_result, .b = 1.0_miles }));
  };
};
}  // namespace hal
