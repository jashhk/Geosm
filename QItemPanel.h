#ifndef QITEMPANEL_H
#define QITEMPANEL_H

#if defined(QT_NO_TOOLBUTTON) || defined(QT_NO_SCROLLAREA)
#define NO_ITEMPANEL
#endif

#ifndef NO_ITEMPANEL
#include <QScrollArea>
#include <QList>
#include <QIcon>

class QItemPanel : public QWidget/*QScrollArea*/ {
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated)
public:
    QItemPanel(QWidget *parent = 0);
    ~QItemPanel();
    void addItem(QWidget *item, const QString &label = QString());
    void addItem(QWidget *item, const QIcon &icon, const QString &label = QString());

    void insertItem(int index, QWidget *item, const QString &label = QString());
    void insertItem(int index, QWidget *item, const QIcon &icon, const QString &label = QString());
    void removeItem(int index);
    int itemCount() const;
    QWidget *item(int index) const;
    QWidget *currentItem() const;
    int indexOf(QWidget *item) const;
    void setItemIcon(int index, const QIcon &icon);
    void setItemTitle(int index, const QString &title);
    void setItemName(int index, const QString &name);
    int currentIndex() const { return m_current; }
    bool isAnimated() const { return m_animated; }
    //void setCurrentItem(QWidget *item);
public slots:
    void setCurrentIndex(int index);
    void setAnimated(bool a){ m_animated = a; }
signals:
    void currentIndexChanged(int);
private:
    QList<QWidget*> m_items;
    QWidget *m_panel;
    int m_current;
    bool m_animated;
};

#endif
#endif