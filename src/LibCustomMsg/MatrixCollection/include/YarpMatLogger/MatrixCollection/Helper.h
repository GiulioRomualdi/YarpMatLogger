#include <iDynTree/yarp/YARPConversions.h>
#include <yarp/os/BufferedPort.h>

#include "Msg.h"


namespace MatrixCollection
{
    class Helper
    {
        Msg m_message;
        yarp::os::BufferedPort<Msg> m_port;



    public:
        template <typename T>
        void addVector(const std::string& label, const T& vector)
        {
            iDynTree::toYarp(vector, m_message.vectors[label]);
            return;
        };

        template <typename T>
        void addMatrix(const std::string& label, const T& matrix)
        {
            iDynTree::toYarp(matrix, m_message.matrices[label]);
            return;
        };

        void configure(const std::string& portName);

        void sendData();


    };
};
