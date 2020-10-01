#include "core.h"

Core::Core()
{
}

bool Core::initCore()
{
    m_textureManager = new TextureManager;
    m_shaderManager = new ShaderManager;
    m_modelManager = new ModelManager;
    m_scene = new OpenGLWidget;
    m_scene->setTextureManagerObject(m_textureManager);
    m_modelManager->setTextureManagerObject(m_textureManager);
    m_scene->setShaderManagerObject(m_shaderManager);
    m_scene->setModelManagerObject(m_modelManager);
    return false;
}

OpenGLWidget *Core::getScene() const
{
    return m_scene;
}
