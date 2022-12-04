/** @file task_flx.h
 *  This is the header file for the flex sensor task.
 * 
 *  @author Corey Agena
 *  @author Daniel Ceja
 *  @author Parker Tenney
 *  @date   2022-Nov-25
 */


/** @brief   Task which implements the flex sensors.
 *  @details This task reads the voltage from the flex sensors and writes a
 *           pwm value to the respective variable for the corresponding finger.
 */
void task_flx (void* p_params);