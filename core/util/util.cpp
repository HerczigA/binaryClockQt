#include "util.h"

namespace MainAppComponents
{

void Props::setProps(const Properties& props)
{
    mProps = props;
}

const Operation Props::getRequestType() const
{
    return mRequestType;
}

}