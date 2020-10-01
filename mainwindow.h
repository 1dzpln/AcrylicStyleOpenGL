#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>

#include "SceneManager/openglwidget.h"
#include "ResourceManager/shadersettings.h"
#include <QTimer>
namespace Ui {
class MainWindow;
}
/*! \brief Класс главного окна. */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*! \brief Устанавливает указатель на объект сцены.
        \param OpenGLWidget *scene - указатель на объект сцены.*/
    void setScene(OpenGLWidget *scene);

private slots:
    /*! \brief Обрабатывает изменение количества проходов для размытия по Гауссу.
        \param int position - позиция на слайдере.*/
    void on_blurPassingNumberSlider_sliderMoved(int position);
    /*! \brief Обрабатывает изменение количества проходов для размытия по Гауссу.
        \param int arg1 - значение поля.*/
    void on_blurPassingNumberSBox_valueChanged(int arg1);
    /*! \brief Обрабатывает изменение прозрачности накладки.
        \param int position - позиция на слайдере.*/
    void on_tintOpacitySlider_sliderMoved(int position);
    /*! \brief Обрабатывает изменение прозрачности накладки.
        \param int arg1 - позиция поля.*/
    void on_tintOpacityDSBox_valueChanged(double arg1);
    /*! \brief Обрабатывает изменение прозрачности шума.
        \param int position - позиция на слайдере.*/
    void on_noiseOpacitySlider_sliderMoved(int position);
    /*! \brief Обрабатывает изменение прозрачности шума.
        \param int arg1 - позиция поля.*/
    void on_noiseOpacityDSBox_valueChanged(double arg1);
    /*! \brief Обрабатывает изменение величины рамки.
        \param int position - позиция на слайдере.*/
    void on_borderRelativeSizeSlider_sliderMoved(int position);
    /*! \brief Обрабатывает изменение величины рамки.
        \param int arg1 - позиция поля.*/
    void on_borderRelativeSizeSBox_valueChanged(int arg1);
    /*! \brief Обрабатывает изменение цвета накладки.
        \param int tintColor - цвет накладки.*/
    void sl_currentColorChanged(const QColor &tintColor);
    /*! \brief Обрабатывает изменение картинки заднего фона.
        \param bool checked - флаг нажатия.*/
    void on_btn_background1_toggled(bool checked);
    /*! \brief Обрабатывает изменение картинки заднего фона.
        \param bool checked - флаг нажатия.*/
    void on_btn_background2_toggled(bool checked);
    /*! \brief Обрабатывает изменение картинки заднего фона.
        \param bool checked - флаг нажатия.*/
    void on_btn_background3_toggled(bool checked);
    /*! \brief Обрабатывает изменение режима смешивания.
        \param int index - индекс режима.*/
    void on_tintCompsitionModeCBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QColorDialog *m_colorDialog; ///< Указатель на объект виджета выбора цвета
    OpenGLWidget *m_scene; ///< Указатель на объект сцены.
    AcrylicShaderSettings *m_acrylicShaderSettings; ///< Указатель на объект с настройками шейдера.
    /*! \brief Применяет настройки шейдера к пользовательскому интерфейсу.*/
    void applyAcrylicShaderSettings();
};

#endif // MAINWINDOW_H
