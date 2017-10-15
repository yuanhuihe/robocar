
#include <walkdriver/walkdriver.h>
#include <walkdriver/executive_device.h>
#include "dc_motor_controller.hpp"

namespace WalkDriver
{
    class DCMotor: public ExecutiveDevice
    {
    public:
        DCMotor()
        {
            controller = new DCMotorController();
        }
        DCMotor(DEV_INFO devInfo)
        {
            controller = new DCMotorController();
            controller->setGPIOMap(devInfo);
        }
        virtual ~DCMotor()
        {
            delete controller;
            controller = nullptr;
        }

        virtual ExecutiveDeviceType getType()
        {
            return type;
        }
        
        virtual bool avaliable()
        {
            return controller->avaliable();
        }
        
        virtual void reset()
        {
            
        }

        virtual unsigned int execute(MoveType moveType, MoveSpeed speed)
        {
            if (speed == SL_Stop)
            {
                stop();
                return EET_OK;
            }

            switch (moveType)
            {
            case WalkDriver::MT_MoveForward:
                moveFoward();
                break;
            case WalkDriver::MT_MoveBackward:
                moveBackward();
                break;
            case WalkDriver::MT_Leftward:
            case WalkDriver::MT_Rightward:
            case WalkDriver::MT_BackLeft:
            case WalkDriver::MT_BackRigh:
                return EET_ActionNotSupport;
                break;
            case WalkDriver::MT_Unknown:
            default:
                return EET_UnknownAction;
                break;
            }

            return EET_OK;
        }

    protected:
        ExecutiveDeviceType type = EDT_DC_Motor;
        ExecutiveController* controller;

        void moveFoward()
        {
            controller->setPin(0, PositiveLevel);
            controller->setPin(1, ZeroLevel);
        }
        void moveBackward()
        {
            controller->setPin(0, ZeroLevel);
            controller->setPin(1, PositiveLevel);
        }
        void stop()
        {
            controller->setPin(0, ZeroLevel);
            controller->setPin(1, ZeroLevel);
        }
    };
    

} // namespace WalkDriver
