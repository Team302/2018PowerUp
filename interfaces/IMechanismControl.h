/*
 * IMechanismControl.h
 */

#ifndef SRC_INTERFACES_IMECHANISMCONTROL_H_
#define SRC_INTERFACES_IMECHANISMCONTROL_H_


class IMechanismControl
{
	public:

	IMechanismControl() = default;
	virtual ~IMechanismControl() = default;

    //-----------------------------------------------------------------------------------
    // Method:          Periodic
    // Description:     Run the mechanism
    // Returns:         void
    //-----------------------------------------------------------------------------------
    virtual void Periodic() = 0;

};

#endif /* SRC_INTERFACES_IMECHANISMCONTROL_H_ */
