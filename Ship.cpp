/*
 * Ship.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: jordanw1
 */

#include "Ship.h"

void Ship::createShip() {
		ss = approaching;
		position = osg::Vec3(0.0f, -400.0f, 0.0f);
		//random velocity in y direction between 10 and 30 m/s
		srand(time(NULL));
		float randomVelocity = 10.f + (((float)rand() / (float)RAND_MAX) * 20.f);

		velocity = osg::Vec3(0.0f, randomVelocity, 0.0f);
		dimensions = osg::Vec3(8.0f, 20.0f, 8.0f);
		transform = new osg::MatrixTransform(osg::Matrix::translate(position));

		shipBox = new osg::Geode();
		shipBox->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), dimensions[0], dimensions[1], dimensions[2])));
		transform->addChild(shipBox);

}


