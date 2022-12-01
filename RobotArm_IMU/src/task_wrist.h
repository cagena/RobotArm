/** @file task_wrist.h
 *  This is the header file for the Wrist task.
 * 
 *  @author Corey Agena, Daniel Ceja, Parker Tenney
 *  @date   November 25, 2022
 */


/** @brief   Task which implements the wrist motor control.
 *  @details This task uses the readings from the IMU and sets a position for the wrist.
 */
void task_wrist (void* p_params);