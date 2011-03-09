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
 void setupView();//?��Ogre�ϥΪ�?�e�A?��?�e
 void update();//�q?���A��?��s?��?�e
 void setupResources();//
 void createScene();
 void createLight();
 void resizeEvent(QResizeEvent* evt);//���f�i��?��
 void timerEvent(QTimerEvent* evt);//�i�H?�@???��s���f
 void paintEvent(QPaintEvent* evt);//���A?�M�o?�z�F
        //����??
 void keyPressEvent(QKeyEvent* evt);
 void keyReleaseEvent(QKeyEvent* evt);
 void mousePressEvent(QMouseEvent* evt);
 void mouseReleaseEvent(QMouseEvent* evt);
 void mouseMoveEvent(QMouseEvent* evt);
 void wheelEvent(QWheelEvent* evt);

 //��?Ogre
 Ogre::RenderWindow* mRenderWindow;
 Ogre::SceneManager* mSceneMgr;
 Ogre::Camera* mCamera;
 Ogre::Viewport* mVp;
 Ogre::Root* mRoot;
 Ogre::Light* mainLight;
  Ogre::Entity* mainEnt;
 Ogre::SceneNode* mainNode;
 //�@�Ǳ���?�q�A?�������C�X
 Ogre::Vector3 mDirection;
 Ogre::Real mRotate;

};

#endif // OGREVIEW_H
