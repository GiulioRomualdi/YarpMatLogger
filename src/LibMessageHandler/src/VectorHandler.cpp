/**
 * @file VectorHandler.cpp
 * @author Giulio Romualdi
 * @copyright  Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 * @date 2019
 */


#include <yarp/eigen/Eigen.h>

#include <VectorHandler.h>

void VectorHandler::configure(const std::string &portName, const std::string& dataName)
{
    m_port.open(portName);
    m_dataName = dataName;
}

bool VectorHandler::saveData(XBot::MatLogger2::Ptr& logger)
{
    auto data = m_port.read(false);

    // no data available
    if(data == nullptr)
        return false;

    logger->add(m_dataName, yarp::eigen::toEigen(*data));

    return true;
}
