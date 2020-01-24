
//====================================================================================================================================================
// Copyright 2020 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

// C++ includes
#include <string>
#include <memory>

// frc includes
#include <frc/smartdashboard/SmartDashboard.h>

// team 302 includes
#include <controllers/chassis/ChassisStateMgr.h>
#include <controllers/chassis/ArcadeDrive.h>
#include <controllers/chassis/GTADrive.h>
#include <controllers/chassis/TankDrive.h>

using namespace std;

ChassisStateMgr::ChassisStateMgr() : m_arcade(),
                                     m_gta(),
                                     m_tank(),
                                     m_currentDrive(),
                                     m_currentState( ChassisStateMgr::CHASSIS_STATE::AUTON)
{
    
    // pick drive mode
    m_driveModeChooser.SetDefaultOption( m_driveModeArcade, m_driveModeArcade);
    m_driveModeChooser.AddOption( m_driveModeGTA, m_driveModeGTA );
    m_driveModeChooser.AddOption( m_driveModeTank, m_driveModeTank );


    // Create a chassis Object passing the chasis and controller objects
    m_arcade = make_unique<ArcadeDrive>();
    m_tank = make_unique<TankDrive>();
    m_gta = make_unique<GTADrive>();
    m_currentDrive = m_arcade;

    SmartDashboard::PutData("Drive Mode", &m_driveModeChooser);

}

void ChassisStateMgr::Init()
{
    m_driveModeSelected = m_driveModeChooser.GetSelected();
    if(m_driveModeSelected == m_driveModeArcade) 
    {
        m_currentDrive == m_arcade;
    }
    else if ( m_driveModeSelected == m_driveModeGTA )
    {
        m_currentDrive = m_gta;
    }
    else if ( m_driveModeSelected == m_driveModeTank )
    {
        m_currentDrive = m_tank;
    }
    else
    {
        m_currentDrive = m_arcade;
    }
    m_currentDrive->Init();
    m_currentDrive->Run();
}

void ChassisStateMgr::RunCurrentState()
{
    if ( m_currentState == CHASSIS_STATE::TELEOP )
    {
        m_currentDrive->Run();
    }
}

void ChassisStateMgr::SetState( ChassisStateMgr::CHASSIS_STATE state )
{
    m_currentState = state;
    if ( m_currentState == CHASSIS_STATE::TELEOP )
    {
        m_currentDrive->Run();
    }

}