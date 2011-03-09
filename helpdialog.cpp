#include "helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent)
{
    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("OK"), QDialogButtonBox::AcceptRole);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    QGridLayout *mainLayout = new QGridLayout;
    QLabel *iconLabel = new QLabel();
    QLabel *titleText = new QLabel();
    QLabel *versionText = new QLabel();
    QLabel *licenceText = new QLabel();
    QLabel *creditText = new QLabel();
    QLabel *contentText = new QLabel();
    QLabel *extraText = new QLabel();

    iconLabel->setPixmap(QPixmap(":/images/icon.png"));
    titleText->setText("<font color=\"#3e3e3e\" size=\"+2\"><b>Geometric Simulating Marine Technology</b></font>");
    versionText->setText("2.2r8532");
    creditText->setText(tr("Credits"));
    contentText->setText(tr("Project Manager: Chan Wai San\n"
                            "Senior Programmer: Lam Chun Lok Jash\n\n"
                            "Programmer:\n"
                            "Cheung Wing Shan\n"
                            "Hysen Sin\n\n"
                            "Engineering Consultant:\n"
                            "Hogan Yan\n"
                            "King Wong\n"
                            "Jack Heung\n"
                            "Philip Mok\n"));
    licenceText->setText(tr("Copyright 2010-2011 Willow Project. All rights reserved."));
    extraText->setText(tr("<font color=\"#a0a0a4\"><i>GEOSM are either registered trademarks or trademarks of Willow Project in HKSAR and/or other countries.</i></font>"));
    extraText->setWordWrap(true);

	mainLayout->addWidget(iconLabel, 0, 0, -1, 1, Qt::AlignTop);
	mainLayout->addWidget(titleText, 0, 1);
	mainLayout->addWidget(versionText, 1, 1);
	mainLayout->addWidget(creditText, 3, 1);
	mainLayout->addWidget(contentText, 4, 1);
	mainLayout->addWidget(licenceText, 6, 1);
	mainLayout->addWidget(extraText, 7, 1);
	mainLayout->addWidget(buttonBox, 8, 1, 1, -1);
    setLayout(mainLayout);

    setWindowTitle(tr("About GEOSM"));
}
