/**
 * @file MatrixCollectionHandler.h
 * @author Giulio Romualdi
 * @copyright  Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 * @date 2019
 */

#ifndef MATRIX_COLLECTION_HANDLER_H
#define MATRIX_COLLECTION_HANDLER_H

// std
#include <memory>

// YARP
#include <yarp/os/BufferedPort.h>

// include custom msg library
#include "Msg.h"

#include "MessageHandler.h"

class MatrixCollectionHandler : public MessageHandler
{
    yarp::os::BufferedPort<MatrixCollection::Msg> m_port;

public:

    void configure(const std::string &portName);

    bool saveData(XBot::MatLogger2::Ptr& logger, const double& time) final;
};

#endif
