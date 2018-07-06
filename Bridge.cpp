/*
 * Bridge.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: jordanw1
 */
#include "Bridge.h"

void Bridge::createBridge() {
	position = osg::Vec3(0.0f, 0.0f, 0.0f);
	transform = new osg::MatrixTransform(osg::Matrix::translate(position));

	//add pivot transforms
	leftPivot = new osg::MatrixTransform(osg::Matrix::translate(osg::Vec3(-20.0f, 0.0f, 0.0f)));
	rightPivot = new osg::MatrixTransform(osg::Matrix::translate(osg::Vec3(20.0f, 0.0f, 0.0f)));
	transform->addChild(leftPivot);
	transform->addChild(rightPivot);

	//add bridge pieces
	leftBridge = new osg::Geode();
	rightBridge = new osg::Geode();
	leftBridge->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(10.0f, 0.0f, 0.0f), 20.f, 5.f, 0.5f)));
	rightBridge->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(-10.0f, 0.0f, 0.0f), 20.f, 5.f, 0.5f)));

	//add laser
	rightBridge->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(-20.0f, -250.0f, 0.0f), 0.4f, 500.f, 0.4f)));

	//add sides
	osg::ref_ptr<osg::Geode> sides = new osg::Geode();
	sides->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(45.0f, -250.0f, -10.0f), 50.0f, 1000.0f, 20.0f)));
	sides->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(-45.0f, -250.0f, -10.0f), 50.0f, 1000.0f, 20.0f)));
	transform->addChild(sides);

	leftPivot->addChild(leftBridge);
	rightPivot->addChild(rightBridge);
}

Bridge::Bridge() {
	bs = closed;
	isOpen = false;
	moving = false;
	openAngle = 3.1415926535f / 4;
	timeToOpen = 5.0f; //to calculate bridge opening rate
	bridgeAngle = 0.f;
	timeToClose = 10.f; //time to wait after ship passes before closing the bridge

	createBridge();
}
Bridge::~Bridge() {
}
float Bridge::getBridgeAngle() {
	return bridgeAngle;
}
bool Bridge::isClosedOrClosing() {
	return (bs == closed || bs == closing);
}
void Bridge::openBridge() {
	if (bs != open) {
		printf("\t\topening bridge\n");
		bs = opening;

		//reset timer
		timeToClose = 10.0f;
	}
}
void Bridge::closeBridge() {
	if (bs != closed) {
		printf("\t\tclosing bridge\n");
		bs = closing;
	}
}
void Bridge::applyBridgeRotation(float angle) {
	leftPivot->setMatrix(osg::Matrix::rotate(-angle, osg::Vec3(0.0, 1.0, 0.0)) * osg::Matrix::translate(osg::Vec3(-20.0f, 0.0f, 0.0f)));
	rightPivot->setMatrix(osg::Matrix::rotate(angle, osg::Vec3(0.0, 1.0, 0.0)) * osg::Matrix::translate(osg::Vec3(20.0f, 0.0f, 0.0f)));
}
void Bridge::updatePosition(double timestep, Ship& s) {
	//if ship has passed, start counting down until closing the bridge
	float timeUntilShip = timeUntilShipArrives(s);
	if (timeUntilShip < 0) {
		if (!s.isShipLeaving()) {
			s.setShipLeaving();
		}
	}
	//otherwise, if the ship will arrive 10 seconds after opening the bridge, open the bridge
	else if (timeUntilShip < (10 + timeToOpen)) {
		if (isClosedOrClosing()) {
			openBridge();
		}
	}

	switch (bs) {
	case opening:
		//check whether bridge is fully open. if it is, change bridge state to open
		if (bridgeAngle >= openAngle) {
			bridgeAngle = openAngle;
			bs = open;

			//Update visualization
			applyBridgeRotation(bridgeAngle);

			printf("\t\tbridge opened\n");
		}
		else {
			//Increase angle and rotate bridge pivot transforms
			float incr = timestep * (openAngle / timeToOpen);
			bridgeAngle = bridgeAngle + incr;
		}
		//Update visualization
		applyBridgeRotation(bridgeAngle);
		break;
	case closing:
		//check whether bridge is fully closed. if it is, change bridge state to closed
		if (bridgeAngle <= 0) {
			bridgeAngle = 0;
			bs = closed;
		}
		else {
			//Decrease angle and rotate bridge pivot transforms
			float incr = timestep * (openAngle / timeToOpen);
			bridgeAngle -= incr;
		}

		//Update visualization
		applyBridgeRotation(bridgeAngle);
		break;

	case open:
		//Wait until ship leaves, then close bridge.
		if (s.isShipLeaving()) {
			if (timeToClose > 0) {
				timeToClose -= timestep;
			}
			else {
				closeBridge();
			}
		}
		break;
	}

}
//calculate time until the leading edge of the ship passes the center of the bridge
float Bridge::timeUntilShipArrives(Ship& s) {
	float distanceInMeters = (position[1] - s.getYIntersectionPosition());

	return (distanceInMeters / s.getVelocity()[1]);
}

osg::ref_ptr<osg::MatrixTransform> Bridge::getTransform() {
	return transform;
}
