#include <osg/Group>
#include <osg/Geode>
#include <osg/LightSource>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <sys/time.h>
//#include <chrono>

#include "Ship.h"
#include "Bridge.h"

int main() {
	//for delta time calculation
	timeval t1, t2;
	gettimeofday(&t1, NULL);

	//declare variables
	Ship *s = new Ship();
	Bridge *b = new Bridge();
	osg::ref_ptr<osg::Group> root = new osg::Group;

	//set up root
	root->addChild(b->getTransform());
	root->addChild(s->getTransform());
	osgViewer::Viewer viewer;
	viewer.setSceneData(root);

	//create camera
	osg::ref_ptr<osg::Camera> cam = new osg::Camera;
	cam->setClearColor(osg::Vec4(0.2f, 0.2f, 0.2f, 1));
	cam->setProjectionMatrixAsPerspective(30, 1.0, 0.1, 1000);
	cam->setViewMatrixAsLookAt(osg::Vec3(0.f, -160.f, 700.f), osg::Vec3(0.0f, -160.0f, 0.0f), osg::Vec3(0.0f, -1.0f, 0.0f));
	viewer.setCamera(cam);
	//viewer.setUpViewInWindow(10, 10, 1000, 1000, 0);
	//viewer.setCameraManipulator(new osgGA::TrackballManipulator);

	viewer.realize();

	//start main loop
	while( !viewer.done() ){
		gettimeofday(&t2, NULL);
		double timestep = (t2.tv_sec - t1.tv_sec) * 1000.0;
		timestep += (t2.tv_usec - t1.tv_usec) / 1000.0;
		timestep /= 1000.0;

		t1 = t2;
		//Update bridge and ship
			s->updateShip(timestep);
			b->updatePosition(timestep, *s);

			float timeUntilShip = b->timeUntilShipArrives(*s);
			printf("ship position: %f, ship velocity: %f, bridge angle: %f, time until ship arrives: %f\n", s->getPosition()[1], s->getVelocity()[1], b->getBridgeAngle(), timeUntilShip);

		viewer.frame();
	}
	return 0;
}



