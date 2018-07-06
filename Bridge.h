/*
 * Bridge.h
 *
 *  Created on: Jul 6, 2018
 *      Author: jordanw1
 */

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include "Ship.h"
#ifndef BRIDGE_H_
#define BRIDGE_H_

class Bridge {
private:
	osg::Vec3 position; //middle point of bridge, also position of laser when bridge closed
	osg::ref_ptr<osg::MatrixTransform> transform, leftPivot, rightPivot;
	bool isOpen, moving;
	float openAngle;
	float timeToOpen;
	float bridgeAngle;
	float timeToClose;

	osg::ref_ptr<osg::Geode> leftBridge, rightBridge;
	enum bridgeState { open, opening, closing, closed };
	bridgeState bs;

	void createBridge();

public:
	Bridge();
	~Bridge();
	float getBridgeAngle();
	bool isClosedOrClosing();
	void openBridge();
	void closeBridge();
	void applyBridgeRotation(float angle);
	void updatePosition(double timestep, Ship& s);
	float timeUntilShipArrives(Ship& s);
	osg::ref_ptr<osg::MatrixTransform> getTransform();


};

#endif /* BRIDGE_H_ */
