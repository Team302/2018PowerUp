/*
 * PrimitiveEnums.h
 *
 */

#ifndef SRC_AUTON_PRIMITIVEENUMS_H_
#define SRC_AUTON_PRIMITIVEENUMS_H_


       enum PRIMITIVE_IDENTIFIER
         {
             UNKNOWN_PRIMITIVE = -1,
             DO_NOTHING,
             HOLD_POSITION,
             DRIVE_DISTANCE,
             DRIVE_TIME,
             DRIVE_TO_CUBE,
             TURN_ANGLE_ABS,
             TURN_ANGLE_REL,
			 DRIVE_TO_WALL,
			 TURN_TO_CUBE,
			 DRIVE_LIDAR_DISTANCE,
             MAX_AUTON_PRIMITIVES
         };


#endif /* SRC_AUTON_PRIMITIVEENUMS_H_ */
