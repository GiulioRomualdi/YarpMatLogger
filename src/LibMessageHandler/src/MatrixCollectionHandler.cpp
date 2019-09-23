/**
 * @file MatrixCollectionhandler.cpp
 * @author Giulio Romualdi
 * @copyright  Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 * @date 2019
 */

// YARP
#include <yarp/eigen/Eigen.h>

#include <YarpMatLogger/MessageHandler/MatrixCollectionHandler.h>

#include <iostream>

void MatrixCollectionHandler::configure(const std::string &portName)
{
    m_port.open(portName);

    return;
}

bool MatrixCollectionHandler::saveData(XBot::MatLogger2::Ptr& logger, const double& time)
{
    MatrixCollection::Msg* data = m_port.read(false);

    // no data available
    if(data == nullptr)
        return false;

    // log all the vectors
    for(auto const& vector : data->vectors)
    {
        logger->add(vector.first, yarp::eigen::toEigen(vector.second));
        logger->add(vector.first + "_time", time);
    }

    // log all the matrices
    for(auto const& matrix : data->matrices)
    {
        logger->add(matrix.first, yarp::eigen::toEigen(matrix.second));
        logger->add(matrix.first + "_time", time);
    }

    return true;
}
