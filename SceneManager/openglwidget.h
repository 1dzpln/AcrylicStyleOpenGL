#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QTimer>
class ShaderManager;
class ModelManager;
class TextureManager;
class AcrylicShaderSettings;
/*! \brief Класс сцены. */
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OpenGLWidget(QWidget *parent = nullptr);
    /*! \brief Устанавливает указатель на объект менеджера шейдеров.
        \param ShaderManager* shaderMngr - указатель на объект менеджера шейдеров.*/
    void setShaderManagerObject(ShaderManager* shaderMngr);
    /*! \brief Устанавливает указатель на объект менеджера моделей.
        \param ModelManager* modelMngr) - указатель на объект менеджера моделей.*/
    void setModelManagerObject(ModelManager* modelMngr);
    /*! \brief Устанавливает указатель на объект менеджера текстур.
        \param TextureManager* textureMngr - указатель на объект менеджера текстур.*/
    void setTextureManagerObject(TextureManager* textureMngr);
    /*! \brief Возвращает указатель на объект настроек шейдера.
        \return результат указатель на объект настроек шейдера.*/
    AcrylicShaderSettings *getAcrylicShaderSettings();
    /*! \brief Получает информацию о графическом ускорителе.*/
    void getGraphicsInfo();
private:
    ShaderManager *m_shaderManager; ///< указатель на объект менеджера шейдеров.
    ModelManager *m_modelManager; ///< указатель на объект менеджера моделей.
    TextureManager *m_textureManager; ///< указатель на объект менеджера текстур.
    QList<QOpenGLFramebufferObject*> m_fboLst; ///< Список буферов fbo.
    QTimer *m_timer; ///< Таймер отрисовки.
protected:
    /*! \brief Переопределенная функция инициализации.*/
    void initializeGL() override;
    /*! \brief Переопределенная функция отрисовки.*/
    void paintGL() override;
    /*! \brief Переопределенная функция изменения размера виджета.
    \param int width - ширина виджета.
    \param int height - высота виджета.*/
    void resizeGL(int width, int height) override;
};

#endif // OPENGLWIDGET_H
