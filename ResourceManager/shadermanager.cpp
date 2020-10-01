#include "shadermanager.h"
#include <QOpenGLContext>
ShaderManager::ShaderManager()
{
    m_currentShader = nullptr;
}

void ShaderManager::createShaderProgram(const QString &shaderProgramName)
{
    QOpenGLShaderProgram *shaderProgram = new QOpenGLShaderProgram;
    Shader *shader = new Shader;
    shader->m_shaderProgram = shaderProgram;
    m_shadersMap.insert(shaderProgramName, shader);
}

bool ShaderManager::makeActiveShader(const QString &shaderProgramName)
{
    Shader *shader = m_shadersMap.value(shaderProgramName);
    if(shader)
    {
        m_currentShader = shader;
    }
    return shader;
}

void ShaderManager::deactivteShader()
{
    m_currentShader = nullptr;
}

bool ShaderManager::addShaderFromFile(QOpenGLShader::ShaderType type, const QString &fileName)
{
    bool result = m_currentShader;
    if(result)
    {
        result = m_currentShader->m_shaderProgram->addShaderFromSourceFile(type, fileName);
        if(!result) QString errorStr = m_currentShader->m_shaderProgram->log();
    }    
    return result;
}

bool ShaderManager::linkShaderProgram()
{
    bool result = m_currentShader;
    if(result)
    {
        result = m_currentShader->m_shaderProgram->link();
        if(!result) m_errorStr = m_currentShader->m_shaderProgram->log();
    }    
    return result;
}

QString ShaderManager::errorString() const
{
    return m_errorStr;
}

void ShaderManager::bindAttributeLocation(const QString &atributeName, int location)
{
    if(m_currentShader)
    {
        m_currentShader->m_shaderProgram->enableAttributeArray(location);
        m_currentShader->m_shaderProgram->bindAttributeLocation(atributeName, location);
    }
}

void ShaderManager::bindShader(const QString &shaderProgramName)
{
    Shader *shader = m_shadersMap.value(shaderProgramName);
    if(shader)
    {
        m_currentShader = shader;
        m_currentShader->m_shaderProgram->bind();
    }
}

void ShaderManager::releaseShader()
{
    if(m_currentShader)
    {
        m_currentShader->m_shaderProgram->release();
    }
}

void ShaderManager::setUniformValue(const QString &uniformName, GLfloat f)
{
    if(m_currentShader)
    {
        m_currentShader->m_shaderProgram->setUniformValue(uniformName.toStdString().data(), f);
    }
}

void ShaderManager::setUniformValue(const QString &uniformName, GLuint v)
{
    if(m_currentShader)
    {
        m_currentShader->m_shaderProgram->setUniformValue(uniformName.toStdString().data(), v);
    }
}

void ShaderManager::setUniformValue(const QString &uniformName, int v)
{
    if(m_currentShader)
    {
        m_currentShader->m_shaderProgram->setUniformValue(uniformName.toStdString().data(), v);
    }
}

void ShaderManager::setUniformValue(const QString &uniformName, GLfloat x, GLfloat y, GLfloat z)
{
    if(m_currentShader)
    {
        m_currentShader->m_shaderProgram->setUniformValue(uniformName.toStdString().data(), x,y,z);
    }
}
