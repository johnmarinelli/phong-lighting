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
  gl::BatchRef mBatch;
  gl::GlslProgRef mGlsl;
  CameraPersp mCamera;
  
  glm::vec3 mCameraPosition{3,2,3};
  glm::vec3 mCameraEyePoint{0,0,0};
};

void PhongLightingApp::setup()
{
  mCamera.setPerspective(50.f, getWindowAspectRatio(), 0.1f, 1000.f);
  mCamera.lookAt(mCameraPosition, mCameraEyePoint);
  
  mGlsl = gl::GlslProg::create(loadResource("phong.vert"), loadResource("phong.frag"));
  mGlsl->bind();

  ObjLoader loader{loadResource("sphere.obj")};
  //mSphere = gl::Batch::create(loader, mGlsl);
  mBatch = gl::Batch::create(geom::Cube{}, mGlsl);
  
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
  
  mBatch->draw();
  //mSphere->draw();
}

CINDER_APP( PhongLightingApp, RendererGl )
