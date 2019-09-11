/**
 * @file TimeHandler.cpp
 * @author Giulio Romualdi
 * @copyright  Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 * @date 2019
 */

#include <TimeHandler.h>

void TimeHandler::configure(const std::string& dataName)
{
    m_dataName = dataName;
}

bool TimeHandler::saveData(XBot::MatLogger2::Ptr& logger)
{
    logger->add(m_dataName, yarp::os::Time::now());

    return true;
}
