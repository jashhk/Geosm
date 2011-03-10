#ifndef __FOGRE_WIDGET_H__
#define __FOGRE_WIDGET_H__

#include <QWidget>

//#include <QtCore\QtGlobal>

//#ifndef uint
//typedef unsigned int uint;
//#endif

//#include <QVector>



// 如果?假就返回
#ifndef FALSE_RETURN
#define FALSE_RETURN(h, r) if(!h) return r;
#endif


#ifndef _DEGUG
#define _DEGUG
#endif //_DEGUG

#include <QEvent>
#include "Ogre.h"
#include "OgreConfigFile.h"


class FOgreWidget : public QWidget
{
 Q_OBJECT
public:
 FOgreWidget(QWidget* parent ,QString strInsName);
 ~FOgreWidget();
 //QSize minimumSizeHint() const;
 //QSize sizeHint() const;

protected:


 //////////////////////////////////////////////////////////////////////////
 // 事件?理函?

 void resizeEvent(QResizeEvent* evt);//窗口可能?放


 void timerEvent(QTimerEvent* evt);//可以?一???更新窗口


 void paintEvent(QPaintEvent* evt);//呵，?然得?理了


 void keyPressEvent(QKeyEvent* evt);
 //void keyReleaseEvent(QKeyEvent* evt);


 void mousePressEvent(QMouseEvent* evt) ;


 //void mouseReleaseEvent(QMouseEvent* evt);
 //void mouseMoveEvent(QMouseEvent* evt);


 void wheelEvent(QWheelEvent* evt);


 bool LoadPlugin() ;

 bool LoadResource() ;

 bool CreateSceneManager() ;

 bool CreateRenderWindow() ;

 bool CreateDefaultCamera() ;
 bool SelectRenderSystem() ;

 bool CreateScene()  ;


 void updateDraw() ;

 void CreateLight() ;

 Ogre::SceneManager* m_pSceneManager ;
 Ogre::RenderWindow* m_pRenderWindow;

 Ogre::Camera* m_pDefCamera;
 Ogre::Viewport* m_pDefViewport;

 Ogre::Root* m_pRoot ;

 Ogre::Entity *  m_pMainEnt;
 Ogre::SceneNode*   m_pMainNode;

 Ogre::Light* m_pMainLight;
public :
  bool Initialize() ;
private:
 QString  m_strInsName_ ;
};


#endif //__FOGRE_WIDGET_H__
