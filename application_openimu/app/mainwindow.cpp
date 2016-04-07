#include "mainwindow.h"
#include "iostream"
#include <QFileDialog>
#include <QPalette>
#include <qlabel.h>
#include "dateselectorlabel.h"
#include "acquisition/SensorReader.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle(QString::fromUtf8("Open-IMU"));
    this->setStyleSheet("background: white");
    plotWidget = new Widget();
    plotWidget->setVisible(false);
    this->setMinimumSize(700,600);
    filesWidget = new QWidget();
    QPalette Pal(palette());

    filesWidget->setMinimumWidth(150);
    filesWidget->setMinimumHeight(580);
    filesWidget->setMaximumWidth(150);

    hLayout = new QHBoxLayout;
    hLayout->addWidget(filesWidget);
     menu = new ApplicationMenuBar(this);
    mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(menu);
    QFont f( "Arial", 12, QFont::ExtraLight);
    QLabel * textLabel = new QLabel("Explorateur");
    textLabel->setFont(f);
    mainLayout->addWidget(textLabel);
    mainLayout->addLayout(hLayout);
    mainLayout->addStretch();
    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    this->setCentralWidget(mainWidget); 


}

void MainWindow:: openFile(){
        QString folderName = QFileDialog::getExistingDirectory(this, tr("Open File"),"/path/to/file/");
        qDebug() << "List items = " << folderName;
        SensorReader *reader = new SensorReader();
        vector<string> x = reader->listFiles(folderName.toStdString());
        QVBoxLayout *filesLayout = new QVBoxLayout;
// To do: better handling, remove this part
        filesWidget = new QWidget();
        filesWidget->setMinimumWidth(150);
        filesWidget->setMinimumHeight(580);
        filesWidget->setMaximumWidth(150);
        hLayout = new QHBoxLayout;
        hLayout->addWidget(filesWidget);

        mainWidget = new QWidget;
        mainLayout = new QVBoxLayout(mainWidget);
        mainLayout->setMargin(0);
        mainLayout->addWidget(menu);
        QFont f( "Arial", 12, QFont::ExtraLight);
        QLabel * textLabel = new QLabel("Explorateur");
        textLabel->setFont(f);
        mainLayout->addWidget(textLabel);
        mainLayout->addLayout(hLayout);
        mainLayout->addStretch();
//************
        foreach (string t , x){
            DateSelectorLabel* fileName = new DateSelectorLabel(t.c_str());
            filesLayout->addWidget(fileName,0,0);
            connect(fileName, SIGNAL(clicked(std::string)), this, SLOT(onDateSelectedClicked(std::string)));
            }

        filesWidget->setLayout(filesLayout);
        filesLayout->addStretch();
        scene = new CustomQmlScene("layout1.qml", this);
        hLayout->addWidget(scene);
        caneva = new Caneva("../../config/layout1.json", scene);
       // caneva->test();
        caneva->setSliderLimitValues(0,10);
        this->setCentralWidget(mainWidget);
}
void MainWindow::onDateSelectedClicked(std::string text){
    caneva->setGraphData(text);
   }

void MainWindow:: computeSteps(){
    qDebug()<<"Lance calcul";
}
