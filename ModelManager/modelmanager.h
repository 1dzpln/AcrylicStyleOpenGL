#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QString>
#include <QMap>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "ResourceManager/texturemanager.h"

/*! \brief Абстрактный класс модели. */
class Model
{
public:
    Model();
    virtual ~Model() {}
    /*! \brief Чисто виртуальная функция отрисовки объекта */
    virtual void renderModel() = 0;
    /*! \brief Чисто виртуальная функция отрисовки объекта с использованием fbo*/
    virtual void renderModelToFBO() = 0;
    /*! \brief Устанавливает указатель на объект менеджера текстур
        \param TextureManager* textManager - указатель на объект менеджера текстур.*/
    void setTextureManager(TextureManager* textManager);
    QString m_name; ///< Наименование объекта
    TextureManager* m_textureManager; ///< Указатель на объект менеджера текстур
};
/*! \brief Класс моделей-примитивов. */
class SimpleModel : public Model
{
public:
    SimpleModel();
    ~SimpleModel() {}
    void renderModel();
    void renderModelToFBO();
    QOpenGLBuffer m_vbo; ///< Буфер VBO
    QOpenGLVertexArrayObject m_vao; ///< Буфер VAO
    int m_vertCount; ///< Число вершин сетки
};
/*! \brief Класс управления моделями. */
class ModelManager
{
public:
    ModelManager();
    /*! \brief Создает объект (плоскость)
        \param const QString &name - имя объекта.*/
    void generateQuad(const QString &name);
    /*! \brief Возвращает указатель на объект модели
        \param const QString &modelName - имя объекта.
        \return указатель на объект модели.*/
    Model *getModelByName(const QString &modelName) const;
    /*! \brief Устанавливает указатель на объект менеджера текстур
        \param TextureManager* textManager - указатель на объект менеджера текстур.*/
    void setTextureManagerObject(TextureManager* textManager);
private:
    QMap<QString, Model*> m_modelsMap; ///< Ассоциативный массив: имя модели - указатель на объект модели
    TextureManager* m_textureManager; ///< Указатель на объект менеджера текстур
};

#endif // MODELMANAGER_H
