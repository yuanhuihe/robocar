/**
* @brief
*   Action implimentation file
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.10.12
*/
#ifndef ACTION_IMPL_HPP_
#define ACTION_IMPL_HPP_

#include <executive/executive.h>
#include "configdef.hpp"
#include <gpiorw/gpiorw.h>

using namespace ConfigInfo;

namespace Driver
{
    class ActionImpl: public Action
    {
    public:
        ActionImpl(sActionConfig cfgAct)
        {
            cfg = cfgAct;
        }
        virtual ~ActionImpl()
        {
        }

        virtual ActionType getType()
        {
            return (ActionType)cfg.type;
        }

        virtual char* getName()
        {
            return cfg.name;
        }
        
        virtual unsigned int execute(SpeedPercent speed)
        {
            if (speed < 0 || speed>100)
            {
                return EET_SpeedOutOfRange;
            }

            for(int i=0; i< cfg.ctrl_count; i++)
            {
                GPIORW::GPIOWrite(cfg.ctrls[i].pin, cfg.ctrls[i].value);
            }
            return EET_OK;
        }

    protected:
        sActionConfig cfg;
    };
    

} // namespace Driver

#endif //!ACTION_IMPL_HPP_
