/**
 * @file VectorHandler.h
 * @author Giulio Romualdi
 * @copyright  Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 * @date 2019
 */

#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

// std
#include <memory>

// matlogger2
#include <matlogger2/matlogger2.h>

// YARP
#include <yarp/os/BufferedPort.h>
#include <yarp/sig/Vector.h>

// include custom msg library
#include "MessageHandler.h"

class VectorHandler : public MessageHandler
{
    yarp::os::BufferedPort<yarp::sig::Vector> m_port;
    std::string m_dataName;

public:

    void configure(const std::string &portName, const std::string& dataName);

    bool saveData(XBot::MatLogger2::Ptr& logger, const double& time) final;
};

#endif
