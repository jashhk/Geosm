#include "ogreview.h"

OgreView::OgreView(QWidget* parent) : QWidget(parent,Qt::WFlags(Qt::MSWindowsOwnDC))
{
 mRenderWindow = NULL;
 mSceneMgr = NULL;
 mVp = NULL;
 mainEnt = NULL;
 mainNode = NULL;
 //....?���@�Ǳ���?�q����l��
 setupResources();
}

OgreView::~OgreView()
{
 // destroy Viewport and RenderWindow
 if( mVp )
 {
  mRenderWindow->removeViewport(mVp->getZOrder());
  mVp = 0;
 }

 Ogre::Root::getSingleton().detachRenderTarget(mRenderWindow);
 mRenderWindow = 0;

 if(mRoot != NULL){
  delete mRoot;
  mRoot = 0;
 }
}


void OgreView::setupResources()
{
 mRoot = new Ogre::Root();
 Ogre::ConfigFile cf;
 cf.load("resources.cfg");

 Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
 Ogre::String secName, typeName, archName;
 while(seci.hasMoreElements())
 {
  secName = seci.peekNextKey();
  Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
  Ogre::ConfigFile::SettingsMultiMap::iterator i;
  for(i=settings->begin(); i!=settings->end(); ++i){
   typeName = i->first;
   archName = i->second;
   Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
  }
 }

 if(!mRoot->restoreConfig())
  {
   mRoot->showConfigDialog();
  }
 mRoot->initialise(false);
      //�H�W���O?Ogre���q�{�Ƿӷh
}
//?ԣ?���A�N?��`?�����
void OgreView::createScene()
{
  mainEnt = mSceneMgr->createEntity("Head", "ogrehead.mesh");
  mainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
  mainNode->attachObject(mainEnt);
}

void OgreView::createLight()
{

    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mainLight = mSceneMgr->createLight("MainLight");
    mainLight->setPosition(20,80,50);
}

void OgreView::setupView()
{
    if(mRenderWindow)
        return;
  //createRenderWindow,?�M��?�o�ۤv��u�ص��f�F�A�ⵡ�f�y�`���X?....

 Ogre::NameValuePairList params;
 params["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)(HWND)winId());
 mRenderWindow = mRoot->createRenderWindow("View", width(), height(), false, &params);
 //SceneManager
  mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
  //setup camera & viewport
  mCamera = mSceneMgr->createCamera("PlayerCam");
  mCamera->setPosition(Ogre::Vector3(0,0,80));
  mCamera->lookAt(Ogre::Vector3(0,0,-300));
  mCamera->setNearClipDistance(5);
  mVp = mRenderWindow->addViewport(mCamera);
  mVp->setBackgroundColour(Ogre::ColourValue(0, 0.0, 0.0, 1));
 mCamera->setAspectRatio(Ogre::Real(mVp->getActualWidth()) / Ogre::Real(mVp->getActualHeight()));
  //resource
 Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
   createScene();
   createLight();
   startTimer(2);
}

void OgreView::paintEvent(QPaintEvent *evt)
{
 Q_UNUSED(evt);
    if(mRenderWindow == NULL)
        setupView();
  update();
}

void OgreView::timerEvent(QTimerEvent* evt)
{
 Q_UNUSED(evt);
 update();

}

void OgreView::update()
{
 //��u��s?��?�e�A�Ӥ��O?�J��??���`?��
        if(mRenderWindow != NULL){
  mRoot->_fireFrameStarted();
  mRenderWindow->update();

  mCamera->moveRelative(mDirection);
  mCamera->yaw(Ogre::Radian(angleX));
  mCamera->pitch(Ogre::Radian(angleY));

  mRoot->_fireFrameEnded();
 }
}


void OgreView::resizeEvent(QResizeEvent *evt)
{
 Q_UNUSED(evt);
 if (mRenderWindow != NULL){
  mRenderWindow->windowMovedOrResized();
  mCamera->setAspectRatio(Ogre::Real(mVp->getActualWidth()) / Ogre::Real(mVp->getActualHeight()));
 }
}

void OgreView::keyPressEvent(QKeyEvent* evt)
{
 if(mainEnt != NULL && mainNode != NULL){
  switch(evt->key()){
   case Qt::Key_W:
   case Qt::Key_Up:
    rotX = -0.1;
    mainNode->pitch(Ogre::Radian(rotX));
    break;
   case Qt::Key_S:
   case Qt::Key_Down:
    rotX = 0.1;
    mainNode->pitch(Ogre::Radian(rotX));
    break;
   case Qt::Key_A:
   case Qt::Key_Left:
    rotY = -0.1;
    mainNode->yaw(Ogre::Radian(rotY));
    break;
   case Qt::Key_D:
   case Qt::Key_Right:
    rotY = 0.1;
    mainNode->yaw(Ogre::Radian(rotY));
    break;
  }
 }
}


void OgreView::mousePressEvent(QMouseEvent* evt)
{
 if(evt->button() == Qt::LeftButton)
  mouseLeftPressed = true;
 if(evt->button() == Qt::RightButton){
  mouseRightPressed = true;
  mousePos = Ogre::Vector2(evt->x(), evt->y());
 }
 if(evt->button() == Qt::MidButton)
  mouseMiddleBtn = true;
}


void OgreView::wheelEvent(QWheelEvent* evt)
{
 mDirection.z = -evt->delta()/12;
 update();
 mDirection.z = 0;
}
