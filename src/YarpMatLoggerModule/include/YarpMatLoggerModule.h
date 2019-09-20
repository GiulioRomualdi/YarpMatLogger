/**
 * @file YarpMatLoggerModule.h
 * @authors Giulio Romualdi <giulio.romualdi@iit.it>
 * @copyright 2019 iCub Facility - Istituto Italiano di Tecnologia
 *            Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 * @date 2019
 */

#ifndef YARP_MAT_LOGGER_MODULE_H
#define YARP_MAT_LOGGER_MODULE_H

// std
#include <fstream>
#include <mutex>
// YARP
#include <yarp/os/RFModule.h>
#include <yarp/os/RpcServer.h>
#include <YarpMatLogger/MessageHandler/MessageHandler.h>

#include <thrifts/YarpMatLoggerCommands.h>

/**
 * RFModule useful to collect data during an experiment.
 */
class YarpMatLoggerModule : public yarp::os::RFModule, public YarpMatLoggerCommands
{
    double m_dT; /**< RFModule period. */
    std::vector<std::shared_ptr<MessageHandler>> m_messages;

    yarp::os::RpcServer m_rpcPort; /**< RPC port. */

    XBot::MatLogger2::Ptr m_logger;

    bool m_isRecording{false};

    std::mutex m_mutex; /**< Mutex. */

public:

    /**
     * Get the period of the RFModule.
     * @return the period of the module.
     */
    double getPeriod() override;

    /**
     * Main function of the RFModule.
     * @return true in case of success and false otherwise.
     */
    bool updateModule() override;

    /**
     * Configure the RFModule.
     * @param rf is the reference to a resource finder object.
     * @return true in case of success and false otherwise.
     */
    bool configure(yarp::os::ResourceFinder &rf) override;



    bool record() final;

    bool stop() final;

    /**
     * Close the RFModule.
     * @return true in case of success and false otherwise.
     */
    bool close() override;
};

#endif
