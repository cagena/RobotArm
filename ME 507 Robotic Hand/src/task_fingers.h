/** @file task_fingers.h
 *  This is the header file for the servo motor task.
 * 
 *  @author Corey Agena, Daniel Ceja, Parker Tenney
 *  @date   November 25, 2022
 */


/** @brief   Task which implements the servo motors.
 *  @details This task sets the servo motors to the pwm recieved from the flex
 *           sensor task.
 */
void task_fingers (void* p_params);