/** @file task_wrist_arm.h
 *  This is the header file for the wrist and arm task.
 * 
 *  @author Corey Agena
 *  @author Daniel Ceja
 *  @author Parker Tenney
 *  @date   2022-Nov-25
 */


/** @brief   Task which implements the wrist motor control.
 *  @details This task uses the readings from the IMU and sets a position for the wrist.
 */
void task_wrist_arm (void* p_params);