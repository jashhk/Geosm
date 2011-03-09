//! [0]
#include <QtGui>
#include <Qfont>
#include "mainwindow.h"
#include "mainwindow_p.h"
#include "QItemPanel.h"

MainWindow::MainWindow()
{
    tw = new QDoubleSpinBox;
    lc = new QDoubleSpinBox;
    vc = new QDoubleSpinBox;
    cb = new QDoubleSpinBox;
    da = new QDoubleSpinBox;
    speed = new QDoubleSpinBox;
    ta_one = new QDoubleSpinBox;
    ta_two = new QDoubleSpinBox;
    ta_three = new QDoubleSpinBox;
    //textEdit = new QPlainTextEdit();
    //QTabWidget *tabWidget = new QTabWidget;
    QTabBar *tabBar = new QTabBar;
    QStackedWidget *stackedWidget = new QStackedWidget;
    QWidget *simulation = new QWidget;
    QWidget *statistic = new QWidget;
    QWidget *report = new QWidget;
    
    //Total Weight
    tw->setRange(0.0,999999999.0);
    tw->setDecimals(2);
    //Longtitude Center of Gravity
    lc->setRange(0.0,999999999.0);
    lc->setDecimals(2);
    //Vertical Center of Gravity
    vc->setRange(0.0,999999999.0);
    vc->setDecimals(2);
    //Chine Beam Angle
    cb->setRange(0.0,90.0);
    cb->setDecimals(2);
    //Deadrise Angle
    da->setRange(0.0,30.0);
    da->setDecimals(2);
    //Speed
    speed->setRange(0.0,999999999.0);
    speed->setDecimals(2);
    //1
    ta_one->setRange(2.0, 24.0);
    ta_one->setSingleStep(0.1);
    ta_one->setDecimals(2);
    //2
    ta_two->setRange(2.0, 24.0);
    ta_two->setSingleStep(0.1);
    ta_two->setDecimals(2);
    //3
    ta_three->setRange(2.0, 24.0);
    ta_three->setSingleStep(0.1);
    ta_three->setDecimals(2);

    // setCentralWidget(textEdit);
    setDockOptions(QMainWindow::AnimatedDocks);
    setCentralWidget(stackedWidget);

    //tabWidget->addTab(simulation, QIcon(":/images/basic set/video_16.png"), tr("Simulation"));
    //tabWidget->addTab(statistic, QIcon(":/images/basic set/statistics_16.png"), tr("Statistic"));
    //tabWidget->addTab(report, QIcon(":/images/basic set/document_pencil_16.png"), tr("Report"));
    ////////////////////////////////////////////////////
    tabBar->addTab(QIcon(":/images/basic set/video_16.png"), tr("Simulation"));
    stackedWidget->addWidget(simulation);
    tabBar->addTab(QIcon(":/images/basic set/statistics_16.png"), tr("Statistic"));
    stackedWidget->addWidget(statistic);
    tabBar->addTab(QIcon(":/images/basic set/document_pencil_16.png"), tr("Report"));
    stackedWidget->addWidget(report);

    connect(tabBar,SIGNAL(currentChanged(int)),stackedWidget,SLOT(setCurrentIndex(int)));
    ////////////////////////////////////////////////////
    //createActions();
    //createMenus();

    createStatusBar();
    createDockWindows();
    createToolBars();
    
    /*connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));*/
    setWindowIcon(QIcon(":/images/icon.png"));
    setUnifiedTitleAndToolBarOnMac(true);
    this->setMenuWidget(tabBar);
}


void MainWindow::newFile()
{
   tw->setValue(0.00);
   lc->setValue(0.00);
   vc->setValue(0.00);
   cb->setValue(0.00);
   da->setValue(0.00);
   speed->setValue(0.00);
   ta_one->setValue(2.00);
   ta_two->setValue(2.00);
   ta_three->setValue(2.00);
}
bool MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}
bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << tw->text();
        out << tr(" ");
        out << lc->text();
        out << tr(" ");
        out << vc->text();
        out << tr(" ");
        out << cb->text();
        out << tr(" ");
        out << da->text();
        out << tr(" ");
        out << speed->text();
        out << tr(" ");
        out << ta_one->text();
        out << tr(" ");
        out << ta_two->text();
        out << tr(" ");
        out << ta_three->text();
        out << tr(" ");
        out << textEdit_output->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

   // setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

/*void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit_output->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}*/

void MainWindow::calculation()
{
    Result r = calMain( Input(tw->text().toDouble(),
                              lc->text().toDouble(),
                              vc->text().toDouble(),
                              cb->text().toDouble(),
                              da->text().toDouble(),
                              speed->text().toDouble(),
                              ta_one->text().toDouble(),
                              ta_two->text().toDouble(),
                              ta_three->text().toDouble()) );

    int errCount = 0;

    textEdit_output->clear();

    for ( errCount = 0 ; r.get_msg(errCount) != "" ; errCount++ )
    {
        textEdit_output->appendPlainText(tr(r.get_msg(errCount).c_str()));
    }
    if ( errCount == 0 )
   {
        textEdit_output->appendPlainText(tr(r.isStable()?"Stable":"Unstable"));
        textEdit_output->appendPlainText(tr("EHP = ") + QString::number(r.get_EHP()));
       // QMessageBox::about(this, tr("Calculation"),tr(r.isStable()?"Stable":"Unstable"));
       // QMessageBox::about(this, tr("Calculation"),tr("EHP = ") + QString::number(r.get_EHP()));
    }
    isAllowSave();
}

bool MainWindow::isErrExists()
{
    if ( tw->text()!=tr("0.00") &&
         lc->text()!=tr("0.00") &&
         vc->text()!=tr("0.00") &&
         cb->text()!=tr("0.00") &&
         da->text()!=tr("0.00") &&
         speed->text()!=tr("0.00") &&
         ta_one->text()!=tr("0.00") &&
         ta_two->text()!=tr("0.00") &&
         ta_three->text()!=tr("0.00") )
    {
        Result r = calMain( Input(tw->text().toDouble(),
                              lc->text().toDouble(),
                              vc->text().toDouble(),
                              cb->text().toDouble(),
                              da->text().toDouble(),
                              speed->text().toDouble(),
                              ta_one->text().toDouble(),
                              ta_two->text().toDouble(),
                              ta_three->text().toDouble()) );

        return ( r.get_msg(0) != "" ) ? true : false;
    }

    return true;
}

void MainWindow::about()
{
    HelpDialog aboutDia(this);
    aboutDia.exec();
}

void MainWindow::help()
{
    QMessageBox aboutMsg;
    aboutMsg.setIconPixmap(QPixmap(":/images/basic set/help_64.png"));
    aboutMsg.setWindowTitle(tr("Help"));
    aboutMsg.setText(tr("This help menu provides an operative description about GEOSM."));
    aboutMsg.setInformativeText(tr("Step 1: Users are required to new a project\n"
                                   "Step 2: Users are able to input data by the spin box from the calculation widge\n"
                                   "Step 3: Users need to re-input data while there are invalid input\n"
                                   "Step 4: Result will be shown in the Result widget locates in the buttom left corner\n"
                                   "Step 5: User can view the 3D simulation in the main windows\n"
                                   "Step 6: Users can save the result by selecting appropriate directory"));
    aboutMsg.exec();
}

void MainWindow::isAllowSave()
{
    if ( !isErrExists() )
    {
        exportAct->setEnabled(true);
    }
    else
    {
       exportAct->setEnabled(false);
    }
}

void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setStatusTip(tr("Create a new file"));
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    exportAct = new QAction(QIcon(":/images/save.png"),tr("&Export"), this);
    exportAct->setStatusTip(tr("Export file"));
    exportAct->setShortcuts(QKeySequence::Save);
    exportAct->setEnabled(false);
    connect(exportAct, SIGNAL(triggered()), this, SLOT(save()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("Exit the application"));
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutDeAct = new QAction(tr("&About Us"), this);
    aboutDeAct->setStatusTip(tr("Show the detail of Naval Engineering System"));
    connect(aboutDeAct, SIGNAL(triggered()), this, SLOT(about()));

    helpAct = new QAction(QIcon(":/images/help.png"),tr("&Context help"), this);
    helpAct->setStatusTip(tr("Show help"));
    helpAct->setShortcuts(QKeySequence::HelpContents);
    connect(helpAct, SIGNAL(triggered()), this, SLOT(help()));

}

/*void MainWindow::changePrecision(int decimals)
{
    doubleSpinBox->setDecimals(3);
}*/

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(exportAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);


    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutDeAct);
    helpMenu->addAction(helpAct);
}

void MainWindow::createToolBars()
{
    menuToolButton = new QToolButton;
    QMenu *toolBarMenu = new QMenu(menuToolButton);
    fileToolBar = addToolBar(tr("Main toolbar"));

    QIcon newFileIcon(":/images/basic set/document_32.png");
    newFileIcon.addFile(":/images/basic set/document_16.png", QSize(16, 16));
    newAct = toolBarMenu->addAction(newFileIcon, tr("&New file"), this, SLOT(newFile()), QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    toolBarMenu->addAction(QIcon(":/images/basic set/folder_16.png"), tr("&Open file"), this, SLOT(emptySLOT()), QKeySequence::Open);
    QIcon saveFileIcon(":/images/basic set/save_32.png");
    saveFileIcon.addFile(":/images/basic set/save_16.png", QSize(16, 16));
    exportAct = toolBarMenu->addAction(saveFileIcon,tr("&Save file"), this, SLOT(save()), QKeySequence::Save);;
    exportAct->setStatusTip(tr("Save file"));
    exportAct->setEnabled(false);
    toolBarMenu->addAction(tr("Save &as..."), this, SLOT(emptySLOT()), QKeySequence::SaveAs);
    toolBarMenu->addSeparator();

    QMenu *preferenceMenu = toolBarMenu->addMenu(tr("&Preference"));
    preferenceMenu->addAction(QIcon(":/images/basic set/settings_16.png"), tr("&Setting"), this, SLOT(emptySLOT()), QKeySequence::Preferences);
    preferenceMenu->addSeparator();
    toogleDockAct = preferenceMenu->addAction(tr("Hide all side panels"), this, SLOT(toogleAllDockWidget()));
    preferenceMenu->addAction(dock->toggleViewAction());
    preferenceMenu->addAction(dock_realtime->toggleViewAction());
    preferenceMenu->addAction(dock_output->toggleViewAction());
    preferenceMenu->addSeparator();
    preferenceMenu->addAction(fileToolBar->toggleViewAction());

    QMenu *helpMenu = toolBarMenu->addMenu(tr("&Help"));
    QIcon helpIcon(":/images/basic set/help_32.png");
    helpIcon.addFile(":/images/basic set/help_16.png", QSize(16, 16));
    helpAct = helpMenu->addAction(helpIcon ,tr("Context &help"), this, SLOT(help()), QKeySequence::HelpContents);
    helpAct->setStatusTip(tr("Show help"));
    helpMenu->addSeparator();
    aboutDeAct = helpMenu->addAction(QIcon(":/images/basic set/info_16.png"), tr("&About GEOSM"), this, SLOT(about()));
    aboutDeAct->setStatusTip(tr("Show the detail of Naval Engineering System"));
    toolBarMenu->addSeparator();
	
    exitAct = toolBarMenu->addAction(tr("E&xit"), this, SLOT(close()), QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
	
    QAction *menuAct = new QAction(QIcon(":/images/basic set/home_32.png"), tr("Menu"), this);
    menuToolButton->setDefaultAction(menuAct);
    menuToolButton->setPopupMode(QToolButton::InstantPopup);
    menuToolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    menuToolButton->setMenu(toolBarMenu);
	
    fileToolBar->setIconSize(QSize(32, 32));
    fileToolBar->addWidget(menuToolButton);
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(exportAct);
    fileToolBar->addAction(helpAct);
    //setMenuWidget(menuToolButton);
    connect(fileToolBar,SIGNAL(orientationChanged(Qt::Orientation)),this,SLOT(changeToolButtonStyle(Qt::Orientation)));
}

void MainWindow::toogleAllDockWidget()
{
    if(dock->isHidden()||dock_realtime->isHidden()||dock_output->isHidden())
    {
        dock->setVisible(true);
        dock_realtime->setVisible(true);
        dock_output->setVisible(true);
    }
    else
    {
        dock->close();
        dock_realtime->close();
        dock_output->close();
    }
}

void MainWindow::toogleDockActText()
{
    if(dock->isHidden()||dock_realtime->isHidden()||dock_output->isHidden())
    {
        toogleDockAct->setText(tr("Show all side panels"));
    }
    else
    {
        toogleDockAct->setText(tr("Hide all side panels"));
    }
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Willow Project All Rights Reserved @ 2011"));
}

void MainWindow::createDockWindows()
{
    dock = new QDockWidget(tr("Properties of ship"));
    connect(dock, SIGNAL(visibilityChanged(bool)), this, SLOT(toogleDockActText()));
    dock->setMinimumWidth(300);
    //dock->setMinimumHeight(600);
    //dock->setMaximumHeight(600);
    dock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QItemPanel *itemPanel = new QItemPanel();
    QWidget *centerOfGravity = new QWidget();
    QWidget *characteristics = new QWidget();
    QWidget *centerOfTrimAngle = new QWidget();
	QFormLayout *centerOfGravityForm = new QFormLayout();
    QFormLayout *characteristicsForm = new QFormLayout();
    QFormLayout *centerOfTrimAngleForm = new QFormLayout();
	QHBoxLayout *speedBoxLayout = new QHBoxLayout();

        QComboBox *CGUnit = new QComboBox;
        CGUnit->addItem(tr("m(meter)"));
        CGUnit->addItem(tr("ft(foot)"));
        CGUnit->addItem(tr("in(inch)"));
        CGUnit->addItem(tr("yd(yard)"));
        CGUnit->addItem(tr("mi(mile)"));
        QComboBox *characterUnit = new QComboBox();
        characterUnit->addItem(tr("m(meter)"));
        characterUnit->addItem(tr("ft(foot)"));
        characterUnit->addItem(tr("in(inch)"));
        characterUnit->addItem(tr("yd(yard)"));
        characterUnit->addItem(tr("mi(mile)"));
        QComboBox *speedUnit = new QComboBox;
        speedUnit->addItem(tr("m/s(meter/sec)"));
        speedUnit->addItem(tr("m/min(meter/minute)"));
        speedUnit->addItem(tr("km/h(kilometer/hour)"));
        speedUnit->addItem(tr("in/s(inch/sec)"));
        speedUnit->addItem(tr("ft/s(foot/sec)"));
        speedUnit->addItem(tr("yd/min(foot/minute)"));
        speedUnit->addItem(tr("yd/s(yard/sec)"));
        speedUnit->addItem(tr("yd/min(yard/minute)"));
        speedUnit->addItem(tr("yd/s(yard/sec)"));
        speedUnit->addItem(tr("mi/min(mile/min)"));
        speedUnit->addItem(tr("mi/h(mile/hour)"));
        speedUnit->addItem(tr("kn,kt(knot)"));
        speedUnit->addItem(tr("kt[UK](knot)"));

	centerOfGravityForm->addRow(tr("Unit"),CGUnit);
	//centerOfGravityForm->addRow(centerOfGravityLabel);
	centerOfGravityForm->addRow(tr("Horizonal"),lc);
    //lc->setValidator(new QDoubleValidator(this));
	centerOfGravityForm->addRow(tr("Vertical"),vc);
    //characteristicsForm->addRow(characteristicsLabel);
        characteristicsForm->addRow(tr("Length Unit"),characterUnit);
	characteristicsForm->addRow(tr("Chine beam length"),cb);
	characteristicsForm->addRow(tr("Deadrise Angle"),da);
	speedBoxLayout->addWidget(speed);
        speedBoxLayout->addWidget(speedUnit);
	characteristicsForm->addRow(tr("Speed (ft/s)"),speedBoxLayout);
	characteristicsForm->addRow(tr("Weight"),tw);
    //centerOfTrimAngleForm->addRow(centerOfTrimAngleLabel);
	centerOfTrimAngleForm->addRow(tr("First"),ta_one);
	centerOfTrimAngleForm->addRow(tr("Second"),ta_two);
	centerOfTrimAngleForm->addRow(tr("Third"),ta_three);
    
	centerOfGravity->setLayout(centerOfGravityForm);
    characteristics->setLayout(characteristicsForm);
    centerOfTrimAngle->setLayout(centerOfTrimAngleForm);

    itemPanel->addItem(centerOfGravity, tr("Center of Gravity"));
    itemPanel->addItem(characteristics, tr("Characteristics"));
    itemPanel->addItem(centerOfTrimAngle, tr("Trim Angle"));
    
    dock->setWidget(itemPanel);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    
    connect(tw, SIGNAL(valueChanged(double)), this, SLOT(calculation()));
    connect(lc, SIGNAL(valueChanged(double)), this, SLOT(calculation()));
    connect(vc, SIGNAL(valueChanged(double)), this, SLOT(calculation()));
    connect(cb, SIGNAL(valueChanged(double)), this, SLOT(calculation()));
    connect(da, SIGNAL(valueChanged(double)), this, SLOT(calculation()));
    connect(speed, SIGNAL(valueChanged(double)), this, SLOT(calculation()));
    connect(ta_one, SIGNAL(valueChanged(double)), this, SLOT(calculation()));
    connect(ta_two, SIGNAL(valueChanged(double)), this, SLOT(calculation()));
    connect(ta_three, SIGNAL(valueChanged(double)), this, SLOT(calculation()));
////////////////////////////////////////////////////////////////////////////////////////
    dock_realtime = new QDockWidget(tr("Realtime data"), this);
    dock_realtime->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    dock_realtime->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    addDockWidget(Qt::RightDockWidgetArea, dock_realtime);
////////////////////////////////////////////////////////////////////////////////////////
    dock_output = new QDockWidget(tr("Result"), this);
    dock_output->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    dock_output->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);

    textEdit_output = new QPlainTextEdit;
    textEdit_output->setEnabled(false);
    dock_output->setWidget(textEdit_output);

    addDockWidget(Qt::RightDockWidgetArea, dock_output);
}

CloseButton::CloseButton(QWidget *parent)
    : QAbstractButton(parent)
{
    setFocusPolicy(Qt::NoFocus);
#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
#endif
#ifndef QT_NO_TOOLTIP
    setToolTip(tr("Close Tab"));
#endif
    resize(sizeHint());
}

QSize CloseButton::sizeHint() const
{
    ensurePolished();
    int width = style()->pixelMetric(QStyle::PM_TabCloseIndicatorWidth, 0, this);
    int height = style()->pixelMetric(QStyle::PM_TabCloseIndicatorHeight, 0, this);
    return QSize(width, height);
}

void CloseButton::enterEvent(QEvent *event)
{
    if (isEnabled())
        update();
    QAbstractButton::enterEvent(event);
}

void CloseButton::leaveEvent(QEvent *event)
{
    if (isEnabled())
        update();
    QAbstractButton::leaveEvent(event);
}

void CloseButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QStyleOption opt;
    opt.init(this);
    opt.state |= QStyle::State_AutoRaise;
    if (isEnabled() && underMouse() && !isChecked() && !isDown())
        opt.state |= QStyle::State_Raised;
    if (isChecked())
        opt.state |= QStyle::State_On;
    if (isDown())
        opt.state |= QStyle::State_Sunken;

    if (const QTabBar *tb = qobject_cast<const QTabBar *>(parent())) {
        int index = tb->currentIndex();
        QTabBar::ButtonPosition position = (QTabBar::ButtonPosition)style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition, 0, tb);
        if (tb->tabButton(index, position) == this)
            opt.state |= QStyle::State_Selected;
    }

    style()->drawPrimitive(QStyle::PE_IndicatorTabClose, &opt, &p, this);
}
