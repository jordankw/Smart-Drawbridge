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

#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osgViewer/Viewer>




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

int main() {
	osg::ref_ptr<osg::Camera> cam = createCamera(0, 1000, 0, 1000);



	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(-2.f, 0.0f, 0.0f), 1.0f)));
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(2.0f, 0.0f, 0.0f), 1.0f)));

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(cam.get());
	root->addChild(geode.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	//viewer.realize();

	//while(1) {
		//viewer.frame();
	//}
	return viewer.run();
}



