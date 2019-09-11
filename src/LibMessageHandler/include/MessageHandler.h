/**
 * @file MessageHandler.h
 * @author Giulio Romualdi
 * @copyright  Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 * @date 2019
 */

#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

// std
#include <memory>

// matlogger2
#include <matlogger2/matlogger2.h>

// YARP
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Searchable.h>
#include <yarp/sig/Vector.h>

// include custom msg library
#include <MatrixCollection.h>

class MessageHandler
{
public:

    virtual void configure(const std::string &portName, const std::string& dataName) = 0;

    virtual bool saveData(XBot::MatLogger2::Ptr& logger) = 0;
};

#endif
