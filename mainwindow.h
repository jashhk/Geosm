/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <qvalidator.h>
#include <qlineedit.h>
#include "Input.h"
#include "Result.h"
#include "cal.h"
#include "helpdialog.h"
#include <QSpinBox>
#include <QAction>
#include <QDockWidget>
#include <QToolButton>
#include <QToolBar>

QT_BEGIN_NAMESPACE
class QAction;
class QListWidget;
class QMenu;
class QTextEdit;
class QPlainTextEdit;
QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:

private:
    QPlainTextEdit *textEdit;
    QPlainTextEdit *textEdit_output;
    QDoubleSpinBox *tw;
    QDoubleSpinBox *lc;
    QDoubleSpinBox *vc;
    QDoubleSpinBox *cb;
    QDoubleSpinBox *da;
    QDoubleSpinBox *speed;
    QDoubleSpinBox *ta_one;
    QDoubleSpinBox *ta_two;
    QDoubleSpinBox *ta_three;

    QString curFile;
    QDockWidget *dock;
    QDockWidget *dock_realtime;
    QDockWidget *dock_output;
    QAction *toogleDockAct;

    //QListWidget *customerList;
    //QListWidget *paragraphsList;
    QMenu *fileMenu;

    QMenu *helpMenu;
    QMenu *viewMenu;
    QToolBar *fileToolBar;
    QAction *newAct;
    QAction *exportAct;
    QAction *exitAct;
    QAction *aboutDeAct;
    QAction *helpAct;
    QToolButton *menuToolButton;

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

private slots:
    void newFile();
    void about();
    void help();
    void calculation();
    void isAllowSave();
    bool isErrExists();
    bool save();
    void toogleAllDockWidget();
    void toogleDockActText();
    void changeToolButtonStyle(Qt::Orientation a){
        if(a==Qt::Horizontal){
            menuToolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
            fileToolBar->adjustSize();
        } else if (a==Qt::Vertical){
            menuToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            fileToolBar->adjustSize();
        }
    }
    void emptySLOT(){ return; }

};
//! [0]

#endif
