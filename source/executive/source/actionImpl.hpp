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

using namespace ConfigInfo;

namespace Driver
{
    class ActionImpl: public Action
    {
    public:
        ActionImpl(sAction act)
        {
            act_data = act;
        }

        virtual ~ActionImpl()
        {
        }

        virtual char* getName()
        {
            return act_data.name;
        }

        virtual int getExecuteBodyID()
        {
            return act_data.parent_id;
        }

        int getId()
        {
            return act_data.id;
        }
        
    protected:
        sAction act_data;
    };
    

} // namespace Driver

#endif //!ACTION_IMPL_HPP_
