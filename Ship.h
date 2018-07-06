/*
 * Ship.h
 *
 *  Created on: Jul 6, 2018
 *      Author: jordanw1
 */
#include <stdio.h>
#include <osg/MatrixTransform>
#ifndef SHIP_H_
#define SHIP_H_

class Ship {
private:
	osg::Vec3 position, velocity;
	osg::Vec3 dimensions; //height, length, width of representative rectangular prism
	osg::ref_ptr<osg::MatrixTransform> transform;
	enum ShipState { approaching, leaving };
	ShipState ss;

	void createShip() {
		ss = approaching;
		position = osg::Vec3(0.0f, -500.0f, 0.0f);
		//random velocity in y direction between 10 and 30 m/s
		velocity = osg::Vec3(0.0f, 30.0f, 0.0f);
		dimensions = osg::Vec3(4.0f, 10.0f, 4.0f);
		transform = new osg::MatrixTransform(osg::Matrix::translate(position));
	}
public:
	Ship() {
		createShip();
	}
	~Ship() {
	}
	void setShipLeaving() {
		ss = leaving;
		printf("\t\tship is leaving\n");
	}
	bool isShipLeaving() {
		if (ss == leaving) {
			return true;
		}
		else {
			return false;
		}
	}
	void updateShip(double timestep) {
		position += (velocity * timestep);
		//update matrixtransform;
		transform->setMatrix(osg::Matrix::translate(position));
	}
	osg::Vec3 getPosition() {
		return position;
	}
	osg::Vec3 getDimensions() {
		return dimensions;
	}
	osg::ref_ptr<osg::MatrixTransform> getTransform() {
		return transform;
	}
	osg::Vec3 getVelocity() {
		return velocity;
	}
	float getYIntersectionPosition() {
		//returns position of leading edge of boat
		return position[1] + (dimensions[1] / 2.f);
	}
};

#endif /* SHIP_H_ */
