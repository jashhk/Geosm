#include "FOgreWidget.h"
#include <QKeyEvent>
#include <string>
using namespace std ;



FOgreWidget::FOgreWidget(QWidget* parent,QString strInsName) : QWidget(parent,Qt::WFlags(Qt::MSWindowsOwnDC)),m_strInsName_(strInsName)
{
 m_pSceneManager = NULL ;
 m_pRenderWindow= NULL ;
 m_pDefCamera= NULL ;
 m_pDefViewport= NULL ;
 m_pRoot = NULL ;
 m_pMainEnt= NULL ;
 m_pMainNode= NULL ;
 m_pMainLight = NULL ;

}


FOgreWidget::~FOgreWidget()
{
 // destroy Viewport and RenderWindow
 if( m_pDefViewport )
 {
 m_pRenderWindow->removeViewport(m_pDefViewport->getZOrder());
 m_pDefViewport = NULL ;
 }

 Ogre::Root::getSingleton().detachRenderTarget(m_pRenderWindow);
 m_pRenderWindow = NULL ;

}


void FOgreWidget::paintEvent(QPaintEvent *evt)
{
 Q_UNUSED(evt);
 updateDraw() ;
}

void FOgreWidget::timerEvent(QTimerEvent* evt)
{
 Q_UNUSED(evt);
 updateDraw() ;

}



void FOgreWidget::resizeEvent(QResizeEvent *evt)
{



 QWidget::resizeEvent(evt) ;
}

void FOgreWidget::keyPressEvent(QKeyEvent* evt)
{


 QWidget::keyPressEvent(evt) ;


}


void FOgreWidget::mousePressEvent(QMouseEvent* evt)
{



 QWidget::mousePressEvent(evt) ;

}


void FOgreWidget::wheelEvent(QWheelEvent* evt)
{

 QWidget::wheelEvent(evt) ;
}


bool FOgreWidget::LoadPlugin()
{
 assert(m_pRoot!=NULL) ;

#if defined(_DEGUG) || defined(DEBUG)
 // Load D3D9 Render System(debug)
 m_pRoot->loadPlugin("RenderSystem_Direct3D9_d");

 // Load OpenGL Render System(debug)
 m_pRoot->loadPlugin("RenderSystem_GL_d");

 // Load partical system(debug)
 m_pRoot->loadPlugin("Plugin_ParticleFX_d");

 // Load octree
 m_pRoot->loadPlugin("Plugin_OctreeSceneManager_d");
#else
 // Load D3D9 Render System
 m_pRoot->loadPlugin("RenderSystem_Direct3D9");

 // Load OpenGL Render System
 m_pRoot->loadPlugin("RenderSystem_GL");

 // Load partical system
 m_pRoot->loadPlugin("Plugin_ParticleFX");

 // Load octree
 m_pRoot->loadPlugin("Plugin_OctreeSceneManager");
#endif
 return true;
}


bool FOgreWidget::LoadResource()
{
 // Load resource paths from config file
 Ogre::ConfigFile cf;
 cf.load("resources.cfg");

 // Go through all sections & settings in the file
 Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

 Ogre::String secName, typeName, archName;
 while (seci.hasMoreElements())
 {
  secName = seci.peekNextKey();
  Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
  Ogre::ConfigFile::SettingsMultiMap::iterator i;
  for(i = settings->begin(); i != settings->end(); ++i)
  {
   typeName = i->first;
   archName = i->second;

   Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
    archName, typeName, secName);
  }
 }

 return true;
}

bool FOgreWidget::CreateSceneManager()
{
 assert(m_pRoot);

 m_pSceneManager = m_pRoot->createSceneManager(Ogre::ST_GENERIC);

 return true;
}
bool FOgreWidget::CreateDefaultCamera()
{

 assert(m_pRoot);
 assert(m_pSceneManager);
 assert(m_pRenderWindow);

 //m_pDefCamera = m_pSceneManager->createCamera(strName);
 m_pDefCamera = m_pSceneManager->createCamera("MyCamera");
 m_pDefCamera->setPosition(Ogre::Vector3(0,0,80));
 m_pDefCamera->lookAt(Ogre::Vector3(0,0,-300));
 m_pDefCamera->setNearClipDistance(5);
 m_pDefViewport = m_pRenderWindow->addViewport(m_pDefCamera);
 m_pDefViewport->setBackgroundColour(Ogre::ColourValue(0, 0.0, 0.0, 1));
 m_pDefCamera->setAspectRatio(Ogre::Real(m_pDefViewport->getActualWidth()) / Ogre::Real(m_pDefViewport->getActualHeight()));


 // Make window active and post an update
 m_pRenderWindow->setActive(true);
 m_pRenderWindow->update();



 return true;
}
   // Create Render Window
bool FOgreWidget::CreateRenderWindow()
{

    assert(m_pRoot);

    Ogre::NameValuePairList params;
    params["left"]                 = "0";
    params["top"]                  = "0";
    params["border"]               = "none";

    //params["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)(HWND)winId());
    params["parentWindowHandle"] = Ogre::StringConverter::toString((size_t)(HWND)winId());

    string strName  ;
    strName = m_strInsName_.toStdString() ;
    strName += "_Window" ;

    m_pRenderWindow = m_pRoot->createRenderWindow(strName, width(), height(), false, &params) ;

    if(m_pRenderWindow == NULL) return false;

    return true;
   }


bool FOgreWidget::Initialize( )
{
 // already inited
 if(m_pRoot!= NULL) return true ;


 if(Ogre::Root::getSingletonPtr() == NULL)
 {
   // create scene root with no config file and plugin
   //m_pRoot = new Root("");
  m_pRoot = new Ogre::Root();

   // Load plugin
   //FALSE_RETURN( LoadPlugin(), false );

   // Select Render System
   FALSE_RETURN( SelectRenderSystem(), false );

   m_pRoot->initialise(false);

   // Load Resource
   FALSE_RETURN( LoadResource(), false );
 }
 else
 {
  m_pRoot = Ogre::Root::getSingletonPtr();
     }

  // Create Render Window
  FALSE_RETURN( CreateRenderWindow(), false );

  // Create Scene Manager
  FALSE_RETURN( CreateSceneManager(), false );

  // Create Default Camera and Viewport
  FALSE_RETURN( CreateDefaultCamera(), false );

  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  // Create Scene
  FALSE_RETURN( CreateScene(), false );

  CreateLight() ;

  startTimer(2);
  return false ;
}


// Select Render System
bool FOgreWidget::SelectRenderSystem()
{

 m_pRoot->restoreConfig() ;

 if(m_pRoot->showConfigDialog())
 {
  // If returned true, user clicked OK so initialise
  // Here we choose to let the system create a default rendering window by passing 'true'

  return true;
 }
 else
  exit(0);

 return false ;

}


bool FOgreWidget::CreateScene()
{

 string strName  ;
 strName = m_strInsName_.toStdString() ;
 strName += ".mesh" ;
 m_pMainEnt = m_pSceneManager->createEntity("root_mesh", strName);
 m_pMainNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
 m_pMainNode->attachObject(m_pMainEnt);
 return true ;
}

void FOgreWidget::updateDraw()
{

 if(m_pRenderWindow != NULL)
 {
  //printf("I'm %s\n",m_strInsName_.toStdString().c_str()) ;
  m_pRoot->_fireFrameStarted();
  m_pRenderWindow->update();
  //m_pDefCamera->moveRelative(mDirection);
  //m_pDefCamera->yaw(Ogre::Radian(angleX));
  //m_pDefCamera->pitch(Ogre::Radian(angleY));

  m_pRoot->_fireFrameEnded();
 }

}



void FOgreWidget::CreateLight()
{

 m_pSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
 m_pMainLight = m_pSceneManager->createLight("mainLight");
 m_pMainLight->setPosition(20,80,50);
}
