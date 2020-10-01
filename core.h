#ifndef CORE_H
#define CORE_H
#include <QLayout>
#include "SceneManager/openglwidget.h"
#include "ResourceManager/shadermanager.h"
#include "ModelManager/modelmanager.h"
#include "ResourceManager/texturemanager.h"

/*! \brief Класс ядра отрисовщика. */
class Core
{
public:
    Core();
    /*! \brief Инициализация ядра.
        \return результат выполнения функции.*/
    bool initCore();
    /*! \brief Возвращает указатель на объект сцены.
        \return указатель на объект сцены.*/
    OpenGLWidget *getScene() const;
private:
    OpenGLWidget *m_scene; ///< Указатель на объект сцены.
    ShaderManager *m_shaderManager; ///< Указатель на объект менеджера шейдеров.
    ModelManager *m_modelManager; ///< Указатель на объект менеджера моделей.
    TextureManager *m_textureManager; ///< Указатель на объект менеджера текстур.
};

#endif // CORE_H
