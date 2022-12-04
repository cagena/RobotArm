/** @file task_fingers.h
 *  This is the header file for the servo motor task.
 * 
 *  @author Corey Agena
 *  @author Daniel Ceja
 *  @author Parker Tenney
 *  @date   2022-Nov-25
 */


/** @brief   Task which implements the servo motors.
 *  @details This task sets the servo motors to the pwm recieved from the flex
 *           sensor task.
 */
void task_fingers (void* p_params);