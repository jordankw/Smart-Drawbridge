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

#include "Ship.h"
#include "Bridge.h"


osg::Camera* createCamera(double left, double right, double bottom, double top) {

	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setRenderOrder(osg::Camera::POST_RENDER);
	camera->setAllowEventFocus(false);
	camera->setProjectionMatrix(osg::Matrix::ortho2D(left, right, bottom, top));
	camera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);


	return camera.release();
}
osg::Group* createRoot() {
	osg::ref_ptr<osg::Camera> cam = createCamera(0, 1000, 0, 1000);



	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(-2.f, 3.0f, 0.0f), 1.0f)));
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(2.0f, 3.0f, 0.0f), 1.0f)));

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(cam.get());
	root->addChild(geode.get());


	//osg::ref_ptr<osg::MatrixTransform> f = new osg::MatrixTransform::translate(new osg::Vec3(0.0f, 1.0f, 0.0f));

	return root.release();
}
int main() {
	//Declare variables
	Ship *s = new Ship();
	Bridge *b = new Bridge();
	float timestep = 0.04f;

	//while (1) {

		usleep(timestep * 1000000);
	//}
	osg::ref_ptr<osg::Group> root;
	root = createRoot();

	osgViewer::Viewer viewer;
	viewer.setSceneData(root);

	viewer.setCameraManipulator(new osgGA::TrackballManipulator);
	//viewer.getCamera()->

	viewer.setUpViewInWindow(10, 10, 1000, 1000, 0);



	//return viewer.run();
	viewer.realize();
	while( !viewer.done() ){
		//Update bridge and ship
				s->updateShip(timestep);
				b->updatePosition(timestep, *s);

				//Check for time until ship arrives


				float timeUntilShip = b->timeUntilShipArrives(*s);
				/*
				if (timeUntilShip < 0 && !s->isShipLeaving()) {
					//ship has passed
					s->setShipLeaving();

				} else if (timeUntilShip < 10) {
					if (b->isClosedOrClosing()) {
						b->openBridge();
					}
				}
				*/

				printf("ship position: %f, bridge angle: %f, time until ship arrives: %f\n", s->getPosition()[1], b->getBridgeAngle(), timeUntilShip);


		viewer.frame();
	}




	return 0;
}



