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

#pragma once

#include <states/IState.h>
#include <controllers/ControlData.h>  
#include <subsys/IMechanism.h>
#include <hw/DragonLimelight.h>


class LimelightAim : public IState
{
    public:
        LimelightAim
        (
            ControlData* controlData,
            double target
        );
        void Init() override;
        void Run() override;
        bool AtTarget() const override;
        void UpdateTarget( double target );
    private:
        ControlData* m_controlData;
        bool m_atTarget;
        double m_target;
        IMechanism* m_turret;
        std::shared_ptr<DragonLimelight> m_limelight;
        double m_targetPosition;
        bool m_start;
};
