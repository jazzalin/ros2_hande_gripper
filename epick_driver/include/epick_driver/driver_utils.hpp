// Copyright (c) 2023 PickNik, Inc.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the {copyright_holder} nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include "epick_driver/driver.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>

namespace epick_driver::driver_utils
{

///////////////////////////////////////////////////////////////////////////////
/// Gripper activation request.
///

constexpr uint8_t gACT_mask = 0b00000001;

/** Associate a configuration of bits to GripperActivationAction enum. */
const std::unordered_map<uint8_t, GripperActivationAction>& gACT_lookup()
{
  // clang-format off
  static const std::unordered_map<uint8_t, GripperActivationAction> map{
    { 0b0, GripperActivationAction::Disable },
    { 0b1, GripperActivationAction::Activate },
    };
  // clang-format on
  return map;
}

/**
 * Convert a GripperActivationAction enum into a string.
 * @param gripper_activation_action The enum.
 * @return A string representation of the given enum
 */
const std::string gripper_activation_action_to_string(const GripperActivationAction gripper_activation_action)
{
  // clang-format off
  static std::map<GripperActivationAction, std::string> map = {
    { GripperActivationAction::Disable, "Disable" },
    { GripperActivationAction::Activate, "Activate" },
  };
  // clang-format on
  return map.at(gripper_activation_action);
}

///////////////////////////////////////////////////////////////////////////////
/// Gripper mode.
///

constexpr uint8_t gMOD_mask = 0b00000110;

/** Associate a configuration of bits to the GripperMode enum. */
const std::unordered_map<uint8_t, GripperMode>& gMOD_lookup()
{
  // clang-format off
  static const std::unordered_map<uint8_t, GripperMode> map{
    { 0b00000000, GripperMode::AutomaticMode },
    { 0b00000010, GripperMode::AdvancedMode },
    { 0b00000100, GripperMode::Reserved },
    { 0b00000110, GripperMode::Reserved } };
  // clang-format on
  return map;
}

/**
 * Convert a GripperMode enum into a string.
 * @param gripper_mode The enum.
 * @return A string representation of the given enum
 */
const std::string gripper_mode_to_string(const GripperMode gripper_mode)
{
  // clang-format off
  static std::map<GripperMode, std::string> map = {
    { GripperMode::AutomaticMode, "AutomaticMode" },
    { GripperMode::AdvancedMode, "AdvancedMode" },
    { GripperMode::Reserved, "Reserved" } };
  // clang-format on
  return map.at(gripper_mode);
}

///////////////////////////////////////////////////////////////////////////////
/// Regulate.
///

constexpr uint8_t gGTO_mask = 0b00001000;

/** Associate a configuration of bits to the GripperRegulateAction enum. */
const std::unordered_map<uint8_t, GripperRegulateAction>& gGTO_lookup()
{
  // clang-format off
  static const std::unordered_map<uint8_t, GripperRegulateAction> map{
    { 0b00000000, GripperRegulateAction::StopVacuumGenerator },
    { 0b00001000, GripperRegulateAction::FollowRequestedVacuumParameters } };
  // clang-format on
  return map;
}

/**
 * Convert a GripperRegulateAction enum into a string.
 * @param gripper_regulate_action The enum.
 * @return A string representation of the given enum
 */
const std::string gripper_regulate_action_to_string(const GripperRegulateAction gripper_regulate_action)
{
  // clang-format off
  static std::map<GripperRegulateAction, std::string> map = {
    { GripperRegulateAction::StopVacuumGenerator, "StopVacuumGenerator" },
    { GripperRegulateAction::FollowRequestedVacuumParameters, "FollowRequestedVacuumParameters" } };
  // clang-format on
  return map.at(gripper_regulate_action);
}

///////////////////////////////////////////////////////////////////////////////
/// Activation status.
///

constexpr uint8_t gSTA_mask = 0b00110000;

/** Associate a configuration of bits to the GripperActivationStatus enum. */
const std::unordered_map<uint8_t, GripperActivationStatus>& gSTA_lookup()
{
  // clang-format off
  static const std::unordered_map<uint8_t, GripperActivationStatus> map{
    { 0b00000000, GripperActivationStatus::GripperNotActivated },
    { 0b00010000, GripperActivationStatus::GripperOperational } };
  // clang-format on
  return map;
}

/**
 * Convert a GripperActivationStatus enum into a string.
 * @param gripper_activation_status The enum.
 * @return A string representation of the given enum
 */
const std::string gripper_activation_status_to_string(const GripperActivationStatus gripper_activation_status)
{
  // clang-format off
  static std::map<GripperActivationStatus, std::string> map = {
    { GripperActivationStatus::GripperNotActivated, "GripperNotActivated" },
    { GripperActivationStatus::GripperOperational, "GripperOperational" } };
  // clang-format on
  return map.at(gripper_activation_status);
}

///////////////////////////////////////////////////////////////////////////////
/// Object status
///

constexpr uint8_t gOBJ_mask = 0b11000000;

/** Associate a configuration of bits to the GripperMode enum. */
const std::unordered_map<uint8_t, ObjectDetectionStatus> gOBJ_lookup()
{
  // clang-format off
  static const std::unordered_map<uint8_t, ObjectDetectionStatus> map{
    { 0b00000000, ObjectDetectionStatus::Unknown },
    { 0b01000000, ObjectDetectionStatus::ObjectDetectedAtMinPressure },
    { 0b10000000, ObjectDetectionStatus::ObjectDetectedAtMaxPressure },
    { 0b11000000, ObjectDetectionStatus::NoObjectDetected } };
  // clang-format on
  return map;
}

/**
 * Convert an ObjectDetection enum into a string.
 * @param object_detection The enum.
 * @return A string representation of the given enum
 */
const std::string object_detection_to_string(const ObjectDetectionStatus object_detection)
{
  // clang-format off
  static std::map<ObjectDetectionStatus, std::string> map = {
    { ObjectDetectionStatus::Unknown, "Unknown" },
    { ObjectDetectionStatus::ObjectDetectedAtMinPressure, "ObjectDetectedAtMinPressure" },
    { ObjectDetectionStatus::ObjectDetectedAtMaxPressure, "ObjectDetectedAtMaxPressure" },
    { ObjectDetectionStatus::NoObjectDetected, "NoObjectDetected" },
  };
  // clang-format on
  return map.at(object_detection);
}

///////////////////////////////////////////////////////////////////////////////
/// Gripper fault status
///

constexpr uint8_t gFLT_mask = 0b00001111;

/** Associate a configuration of bits to the FaultStatus enum. */
const std::unordered_map<uint8_t, GripperFaultStatus> gFLT_lookup()
{
  // clang-format off
  static const std::unordered_map<uint8_t, GripperFaultStatus> map{
    { 0b00000000, GripperFaultStatus::NoFault },
    { 0b00000001, GripperFaultStatus::Unknown },
    { 0b00000010, GripperFaultStatus::Unknown },
    { 0b00000011, GripperFaultStatus::PorousMaterialDetected },
    { 0b00000100, GripperFaultStatus::Unknown },
    { 0b00000101, GripperFaultStatus::AcionDelayed },
    { 0b00000110, GripperFaultStatus::GrippingTimeout },
    { 0b00000111, GripperFaultStatus::ActivationBitNotSet },
    { 0b00001000, GripperFaultStatus::MaximumTemperatureExceeded },
    { 0b00001001, GripperFaultStatus::NoCommunicationForAtLeastOneSecond },
    { 0b00001010, GripperFaultStatus::UderMinimumOperatingVoltage },
    { 0b00001011, GripperFaultStatus::AutomaticReleaseInProgress },
    { 0b00001100, GripperFaultStatus::InternalFault },
    { 0b00001101, GripperFaultStatus::Unknown },
    { 0b00001110, GripperFaultStatus::Unknown },
    { 0b00001111, GripperFaultStatus::AutomaticReleaseCompleted }
  };
  // clang-format on
  return map;
}

/**
 * Convert a FaultStatus enum into a string.
 * @param fault_status The enum.
 * @return A string representation of the given enum
 */
const std::string fault_status_to_string(const GripperFaultStatus fault_status)
{
  // clang-format off
  static std::map<GripperFaultStatus, std::string> map = {
    { GripperFaultStatus::NoFault, "NoFault" },
    { GripperFaultStatus::AcionDelayed, "AcionDelayed" },
    { GripperFaultStatus::PorousMaterialDetected, "PorousMaterialDetected" },
    { GripperFaultStatus::GrippingTimeout, "GrippingTimeout" },
    { GripperFaultStatus::ActivationBitNotSet, "ActivationBitNotSet" },
    { GripperFaultStatus::MaximumTemperatureExceeded, "MaximumTemperatureExceeded" },
    { GripperFaultStatus::NoCommunicationForAtLeastOneSecond, "NoCommunicationForAtLeastOneSecond" },
    { GripperFaultStatus::UderMinimumOperatingVoltage, "UderMinimumOperatingVoltage" },
    { GripperFaultStatus::AutomaticReleaseInProgress, "AutomaticReleaseInProgress" },
    { GripperFaultStatus::InternalFault, "InternalFault" },
    { GripperFaultStatus::AutomaticReleaseCompleted, "AutomaticReleaseCompleted" },
    { GripperFaultStatus::Unknown, "Unknown" },
    };
  // clang-format on
  return map.at(fault_status);
}

///////////////////////////////////////////////////////////////////////////////
/// Actuator status
///

constexpr uint8_t gVAS_mask = 0b00000011;

/** Associate a configuration of bits to the ActuatorStatus enum. */
const std::unordered_map<uint8_t, ActuatorStatus> gVAS_lookup()
{
  // clang-format off
  static const std::unordered_map<uint8_t, ActuatorStatus> map{
    { 0b00, ActuatorStatus::Standby },
    { 0b01, ActuatorStatus::Gripping },
    { 0b10, ActuatorStatus::PassiveReleasing },
    { 0b11, ActuatorStatus::ActiveReleasing } };
  // clang-format on
  return map;
}

/**
 * Convert a ActuatorStatus enum into a string.
 * @param actuator_status The enum.
 * @return A string representation of the given enum
 */
const std::string actuator_status_to_string(const ActuatorStatus actuator_status)
{
  // clang-format off
  static std::map<ActuatorStatus, std::string> map = {
    { ActuatorStatus::Standby, "Standby" },
    { ActuatorStatus::Gripping, "Gripping" },
    { ActuatorStatus::PassiveReleasing, "PassiveReleasing" },
    { ActuatorStatus::ActiveReleasing, "ActiveReleasing" } };
  // clang-format on
  return map.at(actuator_status);
}

};  // namespace epick_driver::driver_utils