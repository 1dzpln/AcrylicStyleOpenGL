#include "texturemanager.h"
#include <QOpenGLFunctions>
#include <QImage>

TextureManager::TextureManager()
{

}

bool TextureManager::loadTexture(const QString &textureFile, const QString & textureName)
{
    QOpenGLTexture *texture = new QOpenGLTexture(QImage(textureFile).mirrored());
    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    bool result = texture->create();
    if(result) m_texturesMap.insert(textureName, texture);
    return result;
}

void TextureManager::bindTexture(const QString &textureName)
{
    QOpenGLTexture *texture = m_texturesMap.value(textureName);
    if(texture)
    {
        texture->bind();
    }
}

void TextureManager::releaseTexture(const QString &textureName)
{
    QOpenGLTexture *texture = m_texturesMap.value(textureName);
    if(texture)
    {
        texture->release();
    }
}

