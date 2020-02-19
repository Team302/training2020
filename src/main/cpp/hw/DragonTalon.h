/*
* DragonTalon.h
*
* Date Created: Jan 15, 2019
* Author: Jonah Shader
*/

#pragma once

#include <memory>
#include <vector>

#include <frc/SpeedController.h>

#include <controllers/ControlModes.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <hw/usages/MotorControllerUsage.h>

// Third Party Includes
#include <ctre/phoenix/motorcontrol/RemoteSensorSource.h>
#include <ctre/phoenix/ErrorCode.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>


class DragonTalon : public IDragonMotorController
{
    public:

        // Constructors
        DragonTalon() = delete;
        DragonTalon
        (
            MotorControllerUsage::MOTOR_CONTROLLER_USAGE deviceType, 
            int deviceID, 
            int pdpID, 
            int countsPerRev, 
            double gearRatio
        );
        virtual ~DragonTalon() = default;


        // Getters (override)
        double GetRotations() const override;
        double GetRPS() const override;
        MotorControllerUsage::MOTOR_CONTROLLER_USAGE GetType() const override;
        int GetID() const override;
        std::shared_ptr<frc::SpeedController> GetSpeedController() const override;
        double GetCurrent() const override;

        // Setters (override)
        void SetControlMode(ControlModes::CONTROL_TYPE mode) override; //:D
        void Set(double value) override;
        void SetRotationOffset(double rotations) override;
        void SetVoltageRamping(double ramping, double rampingClosedLoop = -1) override; // seconds 0 to full, set to 0 to disable
        void EnableCurrentLimiting(bool enabled) override; 
        void EnableBrakeMode(bool enabled) override; 
        void Invert(bool inverted) override; 
        void SetSensorInverted(bool inverted) override;

        /// @brief  Set the control constants (e.g. PIDF values).
        /// @param [in] ControlData*   pid - the control constants
        /// @return void
        void SetControlConstants(ControlData* controlInfo) override;
        // Method:		SelectClosedLoopProfile
        // Description:	Selects which profile slot to use for closed-loop control
        // Returns:		void
        void SelectClosedLoopProfile(int slot, int pidIndex);// <I> - 0 for primary closed loop, 1 for cascaded closed-loop

        int ConfigSelectedFeedbackSensor
        (
            ctre::phoenix::motorcontrol::FeedbackDevice feedbackDevice, 
            int pidIdx, 
            int timeoutMs
        ); 
        int ConfigSelectedFeedbackSensor
        (
            ctre::phoenix::motorcontrol::RemoteFeedbackDevice feedbackDevice, 
            int pidIdx, 
            int timeoutMs
        ); 
        int ConfigPeakCurrentLimit(int amps, int timeoutMs); 
        int ConfigPeakCurrentDuration(int milliseconds, int timeoutMs); 
        int ConfigContinuousCurrentLimit(int amps, int timeoutMs); 

        void SetAsSlave(int masterCANID); 

        void SetForwardLimitSwitch
        ( 
            bool normallyOpen
        );

        void SetReverseLimitSwitch
        (
            bool normallyOpen
        );

        void SetRemoteSensor
        (
            int                                             canID,
            ctre::phoenix::motorcontrol::RemoteSensorSource deviceType
        ) override;

        void SetDiameter( double diameter ) override;


    private:
        std::shared_ptr<ctre::phoenix::motorcontrol::can::WPI_TalonSRX>  m_talon;
        ControlModes::CONTROL_TYPE m_controlMode;
        MotorControllerUsage::MOTOR_CONTROLLER_USAGE m_type;

        int m_id;
        int m_pdp;
        int m_countsPerRev;
        int m_tickOffset;
        double m_gearRatio;
        double m_diameter;
};

typedef std::vector<DragonTalon*> DragonTalonVector;