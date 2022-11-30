/** @file task_flx.h
 *  This is the header file for the flex sensor task.
 * 
 *  @author Corey Agena, Daniel Ceja, Parker Tenney
 *  @date   November 25, 2022
 */


/** @brief   Task which implements the flex sensors.
 *  @details This task reads the voltage from the flex sensors and writes a
 *           pwm value to the respective variable for the corresponding finger.
 */
void task_flx (void* p_params);