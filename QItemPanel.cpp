#include "QItemPanel.h"
#ifndef NO_ITEMPANEL
#include "QItemPanel_p.h"

void ItemHeader::setChecked(bool checked)
{
    this->checked = checked;
    m_lbl->setPixmap(QPixmap(
            isChecked()?":/images/basic set/arrow_down_16.png":":/images/basic set/arrow_up_16.png"
            ));
}

/*! \reimp */
void ItemHeader::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }
    if (hitArea(e->pos())) {
        emit clicked(checked);
        e->accept();
    } else {
        e->ignore();
    }
}

ItemHeader::ItemHeader(QWidget *w, QWidget *parent) : QFrame(parent) {
    m_widget = w;
    checked = true;
    setFrameStyle(QFrame::StyledPanel);
    setFrameRect(rect().adjusted(0, 0, 0, 0));
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    QHBoxLayout *l = new QHBoxLayout(this);
    l->setMargin(0);
    m_spacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    l->addItem(m_spacer);
    m_text = new QLabel;
    QFont f = m_text->font();
    f.setBold(true);
    f.setPixelSize(16);
    m_text->setFont(f);

    m_lbl = new QLabel();
    m_lbl->setPixmap(QPixmap(":/images/basic set/arrow_down_16.png"));
    m_lbl->setMargin(0);
    m_lbl->setFixedSize(16, 16);
    m_lbl->setScaledContents(true);

    l->addWidget(m_text);
    l->addWidget(m_lbl);
}

void ItemHeader::setItemName(const QString &n) {
    m_text->setText(n);
    layout()->invalidate();
    update();
}

void ItemHeader::setIcon(const QIcon &i) {
    m_icon = i;
    if (i.isNull()) {
        m_spacer->changeSize(0,0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    } else {
        m_spacer->changeSize(50,16, QSizePolicy::Fixed, QSizePolicy::Fixed);
    }
    m_spacer->invalidate();
    layout()->invalidate();
    update();
}

void ItemHeader::paintEvent(QPaintEvent *ev) {
    QFrame::paintEvent(ev);
    QPainter p(this);
    m_icon.paint(&p, QRect(2, 1, 32, 32), Qt::AlignCenter,
                 isEnabled() ? QIcon::Normal : QIcon::Disabled,
                 isEnabled() ? QIcon::On : QIcon::Off);
}

Item::Item(QWidget *body, QWidget *parent) : QWidget(parent) {
    m_body = body;
    QVBoxLayout *l = new QVBoxLayout(this);
    l->setSpacing(0);
    l->setMargin(0);
    m_header = new ItemHeader(body);
    
    l->addWidget(m_header);
    l->addWidget(m_body);

    m_body->setVisible(true);
    connect(m_header, SIGNAL(clicked(bool)), this, SLOT(setOpen(bool)));
}

void Item::setOpen(bool o) {
    if (m_header->isChecked() == o) {
        QItemPanel *ip = parent() ? qobject_cast<QItemPanel*>(parent()->parent()->parent()->parent()) : 0;
        if(ip && !ip->isAnimated()){
            ip->setAnimated(true);
            body()->ensurePolished();
            m_size = QLayout::closestAcceptableSize(body(), body()->sizeHint()).expandedTo(QSize(width(), 0));
            body()->setFixedHeight(0);
            body()->show();
            QPropertyAnimation *animation = new QPropertyAnimation(m_body, "geometry");
            QRect g = m_body->geometry();
            g.setHeight(0);
            animation->setStartValue(g);
            g.setHeight(m_size.height());
            animation->setEndValue(g);
            animation->setEasingCurve(QEasingCurve::InOutQuad);
            animation->setDuration(500);
            connect(animation, SIGNAL(valueChanged(QVariant)), SLOT(valueChanged(QVariant)));
            if (!o) {
                animation->setDirection(QAbstractAnimation::Forward);
            } else {
                animation->setDirection(QAbstractAnimation::Backward);
            }
            connect(animation, SIGNAL(finished()), SLOT(animFinished()));
            animation->start(QPropertyAnimation::DeleteWhenStopped);           
        } /*else {
            if(o)
                m_body->show();
            else
                m_body->hide();
			m_header->setChecked(!m_header->isChecked());
        }*/
    }
}

void Item::valueChanged(QVariant qv) {
    QRect r = qv.toRect();
    m_body->setFixedSize(QSize(r.width(), r.height()));
    m_body->update();
}

void Item::animFinished() {
	QItemPanel *ip = parent() ? qobject_cast<QItemPanel*>(parent()->parent()->parent()->parent()) : 0;
    m_body->setFixedHeight(m_size.height());
	ip->setAnimated(false);
	m_header->setChecked(!m_header->isChecked());
    if (m_header->isChecked()){
        m_body->show();
        
    } else {
        m_body->hide();
    }
}

/*!
 *  \class QItemPanel
 *  \brief The QItemPanel widget provides a item panel similar to the one from WindowsXP.(unstable)
 *  \inmodule wwWidgets
 *
 *
 *
 */

QItemPanel::QItemPanel(QWidget *parent) : QWidget(parent)
        /*: QScrollArea(parent)*/ {
    QScrollArea *sa = new QScrollArea(this);
    QVBoxLayout *la = new QVBoxLayout(this);
    la->setMargin(0);
    la->addWidget(sa);
    m_animated = false;
    m_panel = new QWidget(sa->viewport());
    m_panel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);
    m_panel->setObjectName("ww_itempanel_panel");
    m_current = -1;
    QVBoxLayout *l = new QVBoxLayout(m_panel);
    l->setMargin(2);
    l->addStretch();
    sa->setWidget(m_panel);
    sa->setWidgetResizable(true);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
}


QItemPanel::~QItemPanel() {}

void QItemPanel::addItem(QWidget * item, const QString & label) {
    insertItem(itemCount(), item, label);
}

void QItemPanel::addItem(QWidget * item, const QIcon & icon, const QString & label) {
    insertItem(itemCount(), item, icon, label);
}

void QItemPanel::insertItem(int index, QWidget * item, const QString & label) {
    insertItem(index, item, QIcon(), label);
}

void QItemPanel::insertItem(int index, QWidget * item, const QIcon & icon, const QString & label) {
    if (!item) return;
    Item *itm = new Item(item);
    if (label.isNull())
        itm->setName(item->windowTitle());
    else {
        itm->setName(label);
        item->setWindowTitle(label);
    }
    if (icon.isNull()) {
        itm->setIcon(item->windowIcon());
    } else {
        itm->setIcon(icon);
        item->setWindowIcon(icon);
    }
    static_cast<QBoxLayout*>(m_panel->layout())->insertWidget(index, itm);
    m_items.insert(index, itm);

    if (m_items.count()==1) {
        setCurrentIndex(0);
    }
    itm->show();
}

int QItemPanel::itemCount() const {
    return m_items.count();
}

void QItemPanel::removeItem(int index) {
    if (index < 0 || index>=m_items.count()) return;
    Item *itm = static_cast<Item*>(m_items.at(index));
    m_items.removeAt(index);
    if (m_items.count()<=index) {
        setCurrentIndex(m_items.count()-1);
    }
    QWidget *body = itm->body();
    body->setParent(this);
    delete itm;
}

QWidget * QItemPanel::item(int index) const {
    if (index < 0 || index>=m_items.count()) return 0;
    Item *itm = static_cast<Item*>(m_items.at(index));
    return itm ? itm->body() : 0;
}

int QItemPanel::indexOf(QWidget * item) const {
    for (int i=0;i<m_items.count();i++) {
        Item *itm = static_cast<Item*>(m_items.at(i));
        if (item == itm) return i;
    }
    return -1;
}

void QItemPanel::setCurrentIndex(int index) {
    if (index<0 || index>=m_items.count() || index==m_current)
        return;
    if (m_current!=-1) {
        Item *itm = static_cast<Item*>(m_items.at(m_current));
        itm->setOpen(true);
    }
    m_current = index;
    Item *itm = static_cast<Item*>(m_items.at(index));
    itm->setOpen(false);
    emit currentIndexChanged(index);
}

QWidget * QItemPanel::currentItem() const {
    return item(currentIndex());
}

void QItemPanel::setItemIcon(int index, const QIcon & icon) {
    if (index < 0 || index>=m_items.count()) return;
    Item *itm = qobject_cast<Item*>(m_items.at(index));
    if (!itm) return;
    itm->setIcon(icon);

}

void QItemPanel::setItemTitle(int index, const QString & title) {
    if (index < 0 || index>=m_items.count()) return;
    Item *itm = qobject_cast<Item*>(m_items.at(index));
    if (!itm) return;
    itm->setName(title);
}

void QItemPanel::setItemName(int index, const QString & name) {
    if (index < 0 || index>=m_items.count()) return;
    Item *itm = qobject_cast<Item*>(m_items.at(index));
    if (!itm) return;
    itm->body()->setObjectName(name);
}
#endif
