#ifndef OGREVIEW_H
#define OGREVIEW_H

#include <QWidget>

class OgreView : public QWidget
{
 Q_OBJECT

public:
 OgreView(QWidget* parent );
 ~OgreView();
 //QSize minimumSizeHint() const;
 //QSize sizeHint() const;
protected:
 void setupView();//?建Ogre使用的?容，?景?容
 void update();//通?它，手?更新?景?容
 void setupResources();//
 void createScene();
 void createLight();
 void resizeEvent(QResizeEvent* evt);//窗口可能?放
 void timerEvent(QTimerEvent* evt);//可以?一???更新窗口
 void paintEvent(QPaintEvent* evt);//呵，?然得?理了
        //消息??
 void keyPressEvent(QKeyEvent* evt);
 void keyReleaseEvent(QKeyEvent* evt);
 void mousePressEvent(QMouseEvent* evt);
 void mouseReleaseEvent(QMouseEvent* evt);
 void mouseMoveEvent(QMouseEvent* evt);
 void wheelEvent(QWheelEvent* evt);

 //有?Ogre
 Ogre::RenderWindow* mRenderWindow;
 Ogre::SceneManager* mSceneMgr;
 Ogre::Camera* mCamera;
 Ogre::Viewport* mVp;
 Ogre::Root* mRoot;
 Ogre::Light* mainLight;
  Ogre::Entity* mainEnt;
 Ogre::SceneNode* mainNode;
 //一些控制?量，?有完全列出
 Ogre::Vector3 mDirection;
 Ogre::Real mRotate;

};

#endif // OGREVIEW_H
