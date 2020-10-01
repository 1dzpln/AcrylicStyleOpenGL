#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <QString>
#include <QOpenGLTexture>
#include <QMap>
/*! \brief Класс управления текстурами. */
class TextureManager
{
public:
    TextureManager();
    /*! \brief Загружает текстуру
        \param const QString & textureFile - файл текстуры.
        \param const QString & textureName - имя текстуры.
        \return результат выполнения.*/
    bool loadTexture(const QString & textureFile, const QString & textureName);
    /*! \brief Делает текстуру активной
        \param const QString & textureName - имя текстуры.*/
    void bindTexture(const QString & textureName);
    /*! \brief Делает текстуру неактивной
        \param const QString & textureName - имя текстуры.*/
    void releaseTexture(const QString & textureName);
private:
    QMap<QString, QOpenGLTexture*> m_texturesMap; ///< Ассоциативный массив: имя текстуры - указатель на объект текстуры
};

#endif // TEXTUREMANAGER_H
