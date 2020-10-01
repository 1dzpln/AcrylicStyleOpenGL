#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_colorDialog = new QColorDialog();
    m_colorDialog->setOption(QColorDialog::ColorDialogOption::NoButtons);
    QObjectList lst = m_colorDialog->children();
    for(int i=0; i<lst.count(); i++)
    {
        if(lst.at(i)->isWidgetType())
        {
            if(QString::compare(lst.at(i)->metaObject()->className(),"QWellArray") == 0
            || QString::compare(lst.at(i)->metaObject()->className(),"QLabel") == 0
            || QString::compare(lst.at(i)->metaObject()->className(),"QPushButton") == 0)
            {
                QWidget *w = (QWidget *) lst.at(i);
                w->hide();
            }
        }
    }
    ui->tintColorLayout->addWidget(m_colorDialog);
    connect(m_colorDialog,SIGNAL(currentColorChanged(const QColor &)), this, SLOT(sl_currentColorChanged(const QColor &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setScene(OpenGLWidget *scene)
{
    if(!scene) return;
    m_scene = scene;
    m_acrylicShaderSettings = m_scene->getAcrylicShaderSettings();
    applyAcrylicShaderSettings();
    ui->sceneLayout->addWidget(m_scene);
}

void MainWindow::applyAcrylicShaderSettings()
{

    ui->blurPassingNumberSBox->setValue(m_acrylicShaderSettings->getBlurPassingNumber());
    ui->blurPassingNumberSlider->setValue(m_acrylicShaderSettings->getBlurPassingNumber());

    m_colorDialog->setCurrentColor(m_acrylicShaderSettings->getTintColor());

    ui->tintOpacityDSBox->setValue(m_acrylicShaderSettings->getTintOpacity());
    ui->tintOpacitySlider->setValue(m_acrylicShaderSettings->getTintOpacity()*1000.0);

    ui->tintCompsitionModeCBox->blockSignals(true);
    ui->tintCompsitionModeCBox->addItem("Add");
    ui->tintCompsitionModeCBox->addItem("Exclusion");
    ui->tintCompsitionModeCBox->addItem("Screen");
    ui->tintCompsitionModeCBox->addItem("Multiply");
    ui->tintCompsitionModeCBox->addItem("Lighten");
    ui->tintCompsitionModeCBox->setCurrentIndex(m_acrylicShaderSettings->getTintCompositionMode());
    ui->tintCompsitionModeCBox->blockSignals(false);

    ui->noiseOpacityDSBox->setValue(m_acrylicShaderSettings->getNoiseOpacity());
    ui->noiseOpacitySlider->setValue(m_acrylicShaderSettings->getNoiseOpacity()*1000.0);

    ui->borderRelativeSizeSBox->setValue(m_acrylicShaderSettings->getBorderRelativeSize()*100.0);
    ui->borderRelativeSizeSlider->setValue(m_acrylicShaderSettings->getBorderRelativeSize()*100.0);

    switch(m_acrylicShaderSettings->getBackgroundWallpaper())
    {
        case 1: ui->btn_background1->setChecked(true); break;
        case 2: ui->btn_background2->setChecked(true); break;
        case 3: ui->btn_background3->setChecked(true); break;
        default: ui->btn_background1->setChecked(true);m_acrylicShaderSettings->setBackgroundWallpaper(1);
    }
}


void MainWindow::on_blurPassingNumberSlider_sliderMoved(int position)
{
    ui->blurPassingNumberSBox->setValue(position);    
    m_acrylicShaderSettings->setBlurPassingNumber(position);
}

void MainWindow::on_blurPassingNumberSBox_valueChanged(int arg1)
{
    ui->blurPassingNumberSlider->setValue(arg1);
    m_acrylicShaderSettings->setBlurPassingNumber(arg1);
}

void MainWindow::on_tintOpacitySlider_sliderMoved(int position)
{
    double value = position/1000.0;
    ui->tintOpacityDSBox->setValue(value);
    m_acrylicShaderSettings->setTintOpacity(value);
}

void MainWindow::on_tintOpacityDSBox_valueChanged(double arg1)
{
    ui->tintOpacitySlider->setValue(arg1*1000.0);
    m_acrylicShaderSettings->setTintOpacity(arg1);
}

void MainWindow::on_noiseOpacitySlider_sliderMoved(int position)
{
    double value = position/1000.0;
    ui->noiseOpacityDSBox->setValue(value);
    m_acrylicShaderSettings->setNoiseOpacity(value);
}

void MainWindow::on_noiseOpacityDSBox_valueChanged(double arg1)
{
    ui->noiseOpacitySlider->setValue(arg1*1000.0);
    m_acrylicShaderSettings->setNoiseOpacity(arg1);
}

void MainWindow::on_borderRelativeSizeSlider_sliderMoved(int position)
{
    ui->borderRelativeSizeSBox->setValue(position);
    m_acrylicShaderSettings->setBorderRelativeSize(position/100.0);
}

void MainWindow::on_borderRelativeSizeSBox_valueChanged(int arg1)
{
    ui->borderRelativeSizeSlider->setValue(arg1);
    m_acrylicShaderSettings->setBorderRelativeSize(arg1/100.0);
}

void MainWindow::sl_currentColorChanged(const QColor &tintColor)
{
    m_acrylicShaderSettings->setTintColor(tintColor);
}

void MainWindow::on_btn_background1_toggled(bool checked)
{
    m_acrylicShaderSettings->setBackgroundWallpaper(1);
    ui->btn_background2->blockSignals(true);
    ui->btn_background3->blockSignals(true);
    ui->btn_background2->setChecked(!checked);
    ui->btn_background3->setChecked(!checked);
    ui->btn_background2->blockSignals(false);
    ui->btn_background3->blockSignals(false);
}

void MainWindow::on_btn_background2_toggled(bool checked)
{
    m_acrylicShaderSettings->setBackgroundWallpaper(2);
    ui->btn_background1->blockSignals(true);
    ui->btn_background3->blockSignals(true);
    ui->btn_background1->setChecked(!checked);
    ui->btn_background3->setChecked(!checked);
    ui->btn_background1->blockSignals(false);
    ui->btn_background3->blockSignals(false);
}

void MainWindow::on_btn_background3_toggled(bool checked)
{
    m_acrylicShaderSettings->setBackgroundWallpaper(3);
    ui->btn_background1->blockSignals(true);
    ui->btn_background2->blockSignals(true);
    ui->btn_background1->setChecked(!checked);
    ui->btn_background2->setChecked(!checked);
    ui->btn_background1->blockSignals(false);
    ui->btn_background2->blockSignals(false);
}

void MainWindow::on_tintCompsitionModeCBox_currentIndexChanged(int index)
{
    m_acrylicShaderSettings->setTintCompositionMode((TintCompositionMode)index);
}
