/**
 * @file YarpMatLoggerModule.cpp
 * @authors Giulio Romualdi <giulio.romualdi@iit.it>
 * @copyright 2019 iCub Facility - Istituto Italiano di Tecnologia
 *            Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 * @date 2019
 */

// std
#include <iomanip>

// YARP
#include <yarp/os/LogStream.h>
#include <yarp/os/Time.h>
#include <yarp/os/BufferedPort.h>

#include <matlogger2/utils/mat_appender.h>


#include <YarpMatLoggerModule.h>
#include <Utils.hpp>
#include <VectorHandler.h>
#include <MatrixCollectionHandler.h>
#include <TimeHandler.h>

double YarpMatLoggerModule::getPeriod()
{
    return m_dT;
}

bool YarpMatLoggerModule::close()
{
    m_rpcPort.close();
    return true;
}

bool YarpMatLoggerModule::configure(yarp::os::ResourceFinder &config)
{
    // check if the configuration file is empty
    if(config.isNull())
    {
        yError() << "[YarpMatLoggerModule::configure] Empty configuration for the force torque sensors.";
        return false;
    }

    std::string name;
    if(!YarpHelper::getStringFromSearchable(config, "name", name))
    {
        yError() << "[YarpMatLoggerModule::configure] Unable to get a string from searchable";
        return false;
    }
    setName(name.c_str());


    // attach rpc
    std::string rpcPortName = "/" + getName() + "/rpc";
    this->yarp().attachAsServer(this->m_rpcPort);
    if(!m_rpcPort.open(rpcPortName))
    {
        yError() << "[YarpMatLoggerModule::configure] Could not open" << rpcPortName << " RPC port.";
        return false;
    }

    // set the CONFIGModule period
    m_dT = config.check("sampling_time", yarp::os::Value(0.005)).asDouble();

    // instantiate the handler
    yarp::os::Value *dataToSaveValue;
    if(!config.check("data_to_save", dataToSaveValue))
    {
        yError() << "[RobotHelper::configureRobot] Unable to find data_to_save into config file.";
        return false;
    }
    std::vector<std::string> dataToSaveVector;
    if(!YarpHelper::yarpListToStringVector(dataToSaveValue, dataToSaveVector))
    {
        yError() << "[RobotHelper::configureRobot] Unable to convert yarp list into a vector of strings.";
        return false;
    }

    for(const std::string& data : dataToSaveVector)
    {
        auto dataConfig = config.findGroup(data);

        std::string dataType;
        if(!YarpHelper::getStringFromSearchable(dataConfig, "data_type", dataType))
        {
            yError() << "[YarpMatLoggerModule::configure] Unable to get a string from searchable";
            return false;
        }
        std::string portName;
        if(!YarpHelper::getStringFromSearchable(dataConfig, "port_name", portName))
        {
            yError() << "[YarpMatLoggerModule::configure] Unable to get a string from searchable";
            return false;
        }


        if(dataType == "vector")
        {
            std::string label;
            if(!YarpHelper::getStringFromSearchable(dataConfig, "label", label))
            {
                yError() << "[YarpMatLoggerModule::configure] Unable to get a string from searchable";
                return false;
            }

            auto ptr = std::make_shared<VectorHandler>();
            ptr->configure("/" + getName() + "/" + portName, label);
            m_messages.push_back(ptr);
        }
        else if (dataType == "matrix_collection")
        {
            auto ptr = std::make_shared<MatrixCollectionHandler>();
            ptr->configure("/" + getName() + "/" + portName);
            m_messages.push_back(ptr);
        }
    }

    // log the time
    auto ptr = std::make_shared<TimeHandler>();
    ptr->configure("time");
    m_messages.push_back(ptr);

    return true;
}

bool YarpMatLoggerModule::updateModule()
{
    if(m_isRecording)
    {
        for(const auto& message : m_messages)
        {
            message->saveData(m_logger);
        }
    }
// // WalkingMessage *data = nullptr;

    // // try to read data from port
    // auto data = m_dataPort.read(false);

    // if (data != NULL)
    // {
    //     for(const auto & vector: data->vectors)
    //     {
    //         vector.first;

    //     }

    //     // if(!m_stream.is_open())
    //     // {
    //     //     yError() << "[updateModule] No stream is open. I cannot store your data.";
    //     //     return false;
    //     // }

    //     // if(data->size() != m_numberOfValues)
    //     // {
    //     //     yError() << "[updateModule] The size of the vector is not the one expected. Expected: "
    //     //              << m_numberOfValues << " received: " << data->size();
    //     //     return false;
    //     // }

    //     // // write into the file
    //     // double time = yarp::os::Time::now() - m_time0;
    //     // m_stream << time << " ";
    //     // for(int i = 0; i < m_numberOfValues; i++)
    //     //     m_stream << (*data)[i] << " ";

    //     // m_stream << std::endl;
    // }
    return true;
}

bool YarpMatLoggerModule::record()
{
    std::stringstream fileName;
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    fileName << "Dataset_" << std::put_time(&tm, "%Y_%m_%d_%H_%M_%S") << ".mat";
    m_logger = XBot::MatLogger2::MakeLogger(fileName.str());
    auto appender = XBot::MatAppender::MakeInstance();
    appender->add_logger(m_logger);
    appender->start_flush_thread();

    m_isRecording = true;

    return true;
}

bool YarpMatLoggerModule::stop()
{
    m_isRecording = false;

    m_logger.reset();

    return true;
}
