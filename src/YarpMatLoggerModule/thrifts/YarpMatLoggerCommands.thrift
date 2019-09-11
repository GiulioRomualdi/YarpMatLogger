/**
 * @file YarpMatLoggerCommands.thrift
 * @authors Giulio Romualdi <giulio.romualdi@iit.it>
 * @copyright 2019 iCub Facility - Istituto Italiano di Tecnologia
 *            Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 * @date 2019
 */

service YarpMatLoggerCommands
{
    /**
     * Call this method to record the robot.
     * @return true/false in case of success/failure;
     */
    bool record();

    /**
     * Run the stop the recording
     * @return true/false in case of success/failure;
     */
    bool stop();
}
