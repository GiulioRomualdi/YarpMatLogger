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

class MessageHandler
{
public:

    virtual bool saveData(XBot::MatLogger2::Ptr& logger) = 0;
};

#endif
