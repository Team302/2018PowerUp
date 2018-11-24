/*
 * IDrive.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Austin
 */

#ifndef SRC_SUBSYS_INTERFACES_IDRIVE_H_
#define SRC_SUBSYS_INTERFACES_IDRIVE_H_

class IDrive {
public:

	virtual void Drive() = 0;
    virtual const char* GetIdentifier() const = 0;

	IDrive() = default;
	virtual ~IDrive() = default;
};

#endif /* SRC_SUBSYS_INTERFACES_IDRIVE_H_ */
