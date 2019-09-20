

#include <YarpMatLogger/MatrixCollection/Helper.h>


void MatrixCollection::Helper::configure(const std::string& portName)
{
    m_port.open(portName);
}


void MatrixCollection::Helper::sendData()
{
    auto data = m_port.prepare();
    data = m_message;
    m_port.write();
}
