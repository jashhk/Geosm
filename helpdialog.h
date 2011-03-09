#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QLabel>

class HelpDialog : public QDialog
{
    Q_OBJECT
public:
    explicit HelpDialog(QWidget *parent = 0);

 private:
     QDialogButtonBox *buttonBox;

signals:

public slots:

};

#endif // HELPDIALOG_H
