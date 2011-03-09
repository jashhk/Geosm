#include <QResizeEvent>
#include <QLayout>
#include <QPainter>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QIcon>

class ItemHeader : public QFrame {
    Q_OBJECT
public:
    ItemHeader(QWidget *w, QWidget *parent = 0);
    void setItemName(const QString &n);
    void setIcon(const QIcon &i);
    bool isChecked() const
    {
        return (bool)checked;
    }
    
public slots:    
    void setChecked(bool checked);
    
protected:
    bool hitArea(const QPoint &pos) const
    {
        return rect().contains(pos);
    }
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *ev);
    QWidget *m_widget;
    QLabel *m_text;
    QIcon m_icon;
    QSpacerItem *m_spacer;
    QLabel *m_lbl;
    
Q_SIGNALS:
    void clicked(bool checked);
    
private:
    bool checked;
};

class Item : public QWidget {
    Q_OBJECT
public:
    Item(QWidget *body, QWidget *parent = 0);
    void setName(const QString &n) {
        m_header->setItemName(n);
        m_body->setWindowTitle(n);
    }
    void setIcon(const QIcon &i) {
        m_header->setIcon(i);
        m_body->setWindowIcon(i);
    }
    QWidget *body() const {
        return m_body;
    }
signals:
    void opened();
    void closed();
public slots:
    void setOpen(bool o);
private slots:
    void animFinished();
    void valueChanged(QVariant qv);
protected:
    ItemHeader *m_header;
    QWidget *m_body;
    QSize m_size;
};



