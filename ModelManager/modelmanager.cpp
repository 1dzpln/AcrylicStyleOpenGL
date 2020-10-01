#include "modelmanager.h"
#include "simplemeshdata.h"
#include <QOpenGLFunctions>

Model::Model()
{
    m_textureManager = nullptr;
}

void Model::setTextureManager(TextureManager *textManager)
{
    m_textureManager = textManager;
}

SimpleModel::SimpleModel()
{
    m_vertCount = 0;
}

void SimpleModel::renderModel()
{    
    m_vao.bind();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    QOpenGLFunctions *func = QOpenGLContext::currentContext()->functions();
    func->glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertCount);
    m_textureManager->releaseTexture("background");
}

void SimpleModel::renderModelToFBO()
{

    m_vao.bind();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    QOpenGLFunctions *func = QOpenGLContext::currentContext()->functions();
    func->glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertCount);

}

ModelManager::ModelManager()
{
    m_modelsMap = QMap<QString, Model*>();
    m_textureManager = nullptr;
}

void ModelManager::generateQuad(const QString &name)
{
    SimpleModel *model = new SimpleModel;
    model->m_name = name;
    model->m_vao.create();
    model->m_vao.bind();
    model->m_vbo.create();
    model->m_vbo.bind();
    model->m_vbo.setUsagePattern(QOpenGLBuffer::StreamDraw);
    model->m_vbo.allocate(g_quadData, 16 * sizeof(GLfloat));
    model->m_vertCount = g_quadVerticesCount;
    QOpenGLFunctions *func = QOpenGLContext::currentContext()->functions();
    func->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)nullptr);
    func->glEnableVertexAttribArray(0);
    func->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    func->glEnableVertexAttribArray(1);
    model->m_vbo.release();
    m_modelsMap.insert(name, static_cast<Model*>(model));
    model->setTextureManager(m_textureManager);
}

Model *ModelManager::getModelByName(const QString &modelName) const
{
    return m_modelsMap.value(modelName);
}

void ModelManager::setTextureManagerObject(TextureManager *textManager)
{
    m_textureManager = textManager;
}


