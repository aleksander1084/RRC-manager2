#ifndef RRCMODULEFLASHER_H
#define RRCMODULEFLASHER_H

#include <QObject>
#include "rrcmodule.h"

/**
 * @brief The RRCModuleFlasher class derived after RRCModule, specifining all parameters of the Flasher module, representation of it
 * @author Aleksander Felisiak
 * @date $Date: 2019/08/17 12:22:00 $
 *
 * Contact: olek.felisiak@gmail.com
 *
 * Created on: Saturday Aug 17th 2019
 */
class RRCModuleFlasher : public RRCModule
{
    Q_OBJECT
public:
    /**
     * @brief RRCModuleFlasher class constructor
     */
    RRCModuleFlasher();
    ~RRCModuleFlasher();

    /**
     * @brief inputMode method returning mode of the input
     * @param input number of the input
     * @return
     */
    int inputMode(int input);

    /**
     * @brief inputMode method setting mode of the input
     * @param input number of the input
     * @param n_mode new mode of the input
     */
    void inputMode(int input, int n_mode);

    /**
     * @brief mode method returning mode of a flasher module
     * @return
     */
    bool mode();

    /**
     * @brief mode method setting mode of the flasher module
     * @param n_mode mode value to set (true for automatic, false for manual)
     */
    void mode(bool n_mode);

    /**
     * @brief flashingPeriod method returning flashing period value as float
     * @return
     */
    float flashingPeriod();

    /**
     * @brief flashingPeriod method setting flashing period
     * @param n_value new value of a flashing period
     */
    void flashingPeriod(float n_value);

    /**
     * @brief timeout returning time to deactivation value
     * @return
     */
    uint16_t timeout();

    /**
     * @brief timeout setting time to deactivation value
     * @param n_value new value
     */
    void timeout(uint16_t n_value);

    /**
     * @brief masterTimeout returning value of a maximum activation duration
     * @return
     */
    uint16_t masterTimeout();

    /**
     * @brief masterTimeout sets value of the maximum activation duration
     * @param n_value new value
     */
    void masterTimeout(uint16_t n_value);

    /**
     * @brief gateDelay returns value of delay for gate to drop
     */
    uint8_t gateDelay();

    /**
     * @brief gateDelay sets value of delay for gate to drop
     * @param n_value
     */
    void gateDelay(uint8_t n_value);

    /**
     * @brief activeInputState returns active state of an input
     * @param input number of an input
     * @return true active HIGH, false active LOW
     */
    bool activeInputState(int input);

    /**
     * @brief activeInputState sets active status of an input
     * @param input number of an input
     * @param n_value new value
     */
    void activeInputState(int input, bool n_value);

    /**
     * @brief inputActivationDelay returns value of the activation delay for an input
     * @param input number of an input
     * @return
     */
    uint8_t inputActivationDelay(int input);

    /**
     * @brief inputActivationDelay sets value of the activation delay for an input
     * @param input number of an input
     * @param n_value new Value
     */
    void inputActivationDelay(int input, uint8_t n_value);

    /**
     * @brief inputDeactivationDelay returns value of the deactivation delay for an input
     * @param input number of an input
     * @return
     */
    uint8_t inputDeactivationDelay(int input);

    /**
     * @brief inputDeactivationDelay sets value of the deactivation delay for an input
     * @param input number of an input
     * @param n_value new value
     */
    void inputDeactivationDelay(int input, uint8_t n_value);




protected:
    Parameter<bool, 1>      *mmode;
    Parameter<uint16_t, 1>     *mflashingPeriod;
    Parameter<uint16_t, 1>  *mtimeout;
    Parameter<uint16_t, 1>  *mmasterTimeout;
    Parameter<uint8_t, 1>   *mactiveInputs;
    Parameter<uint8_t, 1>   *mactivationInputs;
    Parameter<uint8_t, 1>   *mdeactivationInputs;
    Parameter<uint8_t, 1>   *mmaintainInputs;

    //advenced settings
    Parameter<uint8_t, 1>   *mgateDelay;
    Parameter<uint8_t, 1>   *mactiveInputsState;
    Parameter<uint8_t, 6>   *minputActivationDelay;
    Parameter<uint8_t, 6>   *minputDeactivationDelay;

};

#endif // RRCMODULEFLASHER_H
