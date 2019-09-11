/**
 * @file MatrixCollectionhandler.cpp
 * @author Giulio Romualdi
 * @copyright  Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 * @date 2019
 */

// YARP
#include <yarp/eigen/Eigen.h>

#include <MatrixCollectionHandler.h>


void MatrixCollectionHandler::configure(const std::string &portName)
{
    m_port.open(portName);

    return;
}

bool MatrixCollectionHandler::saveData(XBot::MatLogger2::Ptr& logger)
{
    auto data = m_port.read(false);

    // no data available
    if(data == nullptr)
        return false;

    // log all the vectors
    for(auto const& vector : data->vectors)
        logger->add(vector.first, yarp::eigen::toEigen(vector.second));

    // log all the matrices
    for(auto const& matrix : data->matrices)
        logger->add(matrix.first, yarp::eigen::toEigen(matrix.second));

    return true;
}
