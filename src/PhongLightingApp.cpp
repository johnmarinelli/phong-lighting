#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ObjLoader.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class PhongLightingApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
  void keyDown(KeyEvent event) override;
	void update() override;
	void draw() override;
  
  gl::BatchRef mSphere;
  gl::BatchRef mSphereShaded;
  gl::BatchRef mBatch;
  gl::GlslProgRef mPhongShading;
  gl::GlslProgRef mPhongLighting;
  CameraPersp mCamera;
  
  glm::vec3 mCameraPosition{6,0,3};
  glm::vec3 mCameraEyePoint{3,0,0};
};

void PhongLightingApp::setup()
{
  mCamera.setPerspective(50.f, getWindowAspectRatio(), 0.1f, 1000.f);
  mCamera.lookAt(mCameraPosition, mCameraEyePoint);
  
  mPhongLighting = gl::GlslProg::create(loadResource("phong_lighting.vert"), loadResource("phong_lighting.frag"));
  
  mPhongShading = gl::GlslProg::create(loadResource("phong_shading.vert"),  loadResource("phong_shading.frag"));
  
  mPhongShading->bind();

  ObjLoader loader{loadResource("sphere.obj")};
  mSphere = gl::Batch::create(loader, mPhongLighting);
  mSphereShaded = gl::Batch::create(loader, mPhongShading);
  //mBatch = gl::Batch::create(geom::Cube{}, mPhongShading);
  
  gl::enableDepthWrite();
  gl::enableDepthRead();
}

void PhongLightingApp::mouseDown( MouseEvent event )
{
}

void PhongLightingApp::keyDown(cinder::app::KeyEvent event)
{
  auto input = event.getChar();
  //auto code = event.getCode();
  
  glm::vec3 d{0};
  
  if (input == 'a')
    d.x -= 1;
  else if (input == 'd')
    d.x += 1;
  else if (input == 'w')
    d.y -= 1;
  else if (input == 's')
    d.y += 1;
  
  mCameraPosition += d;
}

void PhongLightingApp::update()
{
  mCamera.lookAt(mCameraPosition,mCameraEyePoint);
}

void PhongLightingApp::draw()
{
	gl::clear(Color(0, 0, 0));
  gl::setMatrices(mCamera);
  
  gl::pushModelMatrix();
  mSphere->draw();
  //gl::popModelMatrix();
  
  //gl::pushModelMatrix();
  gl::translate(glm::vec3{2,0,0});
  gl::rotate(sin(getElapsedFrames()) * 0.1f, glm::vec3{2,0,0});
  
  gl::drawLine(glm::vec3{-1,0,0}, glm::vec3{1,0,0});

  mSphereShaded->draw();
  gl::popModelMatrix();
}

CINDER_APP( PhongLightingApp, RendererGl )
