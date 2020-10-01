#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <QOpenGLShaderProgram>
#include <QString>
#include "ResourceManager/shadersettings.h"
/*! \brief Структура шейдера. */
struct Shader
{
    QOpenGLShaderProgram* m_shaderProgram;
    QMap<QString, GLuint> m_uniformsLocation;
};
/*! \brief Класс управления шейдерами. */
class ShaderManager
{
public:
    ShaderManager();
    /*! \brief Создает объект шейдерной программы.
        \param const QString &shaderProgramName - имя шейдера.*/
    void createShaderProgram(const QString &shaderProgramName);
    /*! \brief Делает шейдер активным. Если шейдер отсутствует в списке возвращает false. В противном случае true.
        \param const QString &shaderProgramName - имя шейдера.
        \return результат выполнения функции.*/
    bool makeActiveShader(const QString &shaderProgramName);
    /*! \brief Делает текщуий шейдер неактивным.*/
    void deactivteShader();
    /*! \brief Загружает и собирает код шейдера из файла.
        \param QOpenGLShader::ShaderType type - тип шейдера.
        \param const QString &fileName - имя файла кода шейдера.*/
    bool addShaderFromFile(QOpenGLShader::ShaderType type, const QString &fileName);
    /*! \brief Связывает добавленные шейдеры в единую программу.
        \return результат выполнения функции.*/
    bool linkShaderProgram();
    /*! \brief Возвращает строку с ошибкой исполнения.
        \return строка с ошибкой исполнения.*/
    QString errorString() const;
    /*! \brief Связывает имя атрибута шейдера и расположение (позицию).
        \param const QString &atributeName - имя атрибута.
        \param int location - расположение (позицию).*/
    void bindAttributeLocation(const QString &atributeName, int location);
    /*! \brief Делает шейдерную программу активной для текущего контекста.
        \param const QString &shaderProgramName - имя шейдера.*/
    void bindShader(const QString &shaderProgramName);
    /*! \brief Делает шейдерную программу неактивной для текущего контекста.*/
    void releaseShader();
    /*! \brief Устанавливает значение для объекта шейдера.
        \param const QString &uniformName - имя объекта.
        \param GLfloat f - значение.*/
    void setUniformValue(const QString &uniformName, GLfloat f);
    /*! \brief Устанавливает значение для объекта шейдера.
        \param const QString &uniformName - имя объекта.
        \param GLfloat м - значение.*/
    void setUniformValue(const QString &uniformName, GLuint v);
    /*! \brief Устанавливает значение для объекта шейдера.
        \param const QString &uniformName - имя объекта.
        \param GLfloat м - значение.*/
    void setUniformValue(const QString &uniformName, int v);
    /*! \brief Устанавливает значения для объекта шейдера.
        \param const QString &uniformName - имя объекта.
        \param GLfloat x - значение.
        \param GLfloat y - значение.
        \param GLfloat z - значение.*/
    void setUniformValue(const QString &uniformName, GLfloat x, GLfloat y, GLfloat z);
    inline AcrylicShaderSettings *getAcrylicShaderSettings() {return &m_acrylicShaderSettings;};
private:
    QMap<QString, Shader*> m_shadersMap; ///< Ассоциативный массив: имя шейдера - указатель на объект шейдера
    Shader *m_currentShader; ///< Текущий активный шейдер
    QString m_errorStr; ///< Строка с ошибкой
    AcrylicShaderSettings m_acrylicShaderSettings; ///< Объект с настройками шейдера
};

#endif // SHADERMANAGER_H
