#include <QWindow>
#include "openglwidget.h"
#include "ResourceManager/shadermanager.h"
#include "ModelManager/modelmanager.h"
#include "ResourceManager/texturemanager.h"
#
#include <QDebug>
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat fmt;
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(fmt);    
    m_shaderManager = nullptr;
    m_modelManager = nullptr;
    m_textureManager = nullptr;
    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
}

void OpenGLWidget::setShaderManagerObject(ShaderManager *shdrMngr)
{
    m_shaderManager = shdrMngr;
}

void OpenGLWidget::setModelManagerObject(ModelManager *modelMngr)
{
    m_modelManager = modelMngr;
}

void OpenGLWidget::setTextureManagerObject(TextureManager *textureMngr)
{
    m_textureManager = textureMngr;
}

AcrylicShaderSettings *OpenGLWidget::getAcrylicShaderSettings()
{
    return m_shaderManager->getAcrylicShaderSettings();
}

void OpenGLWidget::getGraphicsInfo()
{
    #define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
    QOpenGLContext *context = QOpenGLContext::currentContext();
    const GLubyte* glRendererCString = glGetString(GL_RENDERER);
    QString glRendererQString;
    if (glRendererCString)
    {
        glRendererQString = reinterpret_cast<const char*>(glRendererCString);
        qInfo() << glRendererQString;
    }
    const GLubyte* glVendorCString = glGetString(GL_VENDOR);
    QString glVendorQString;
    if (glVendorCString)
    {
        glVendorQString = reinterpret_cast<const char*>(glVendorCString);
        qInfo() << glVendorQString;
    }
    GLint total_mem_kb = 0;
    glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, &total_mem_kb);
    if(total_mem_kb)
    {
        QString memQStr = QString("Total available memory %1 MByte").arg(total_mem_kb/1024);
        qInfo() << memQStr;
    }
    const GLubyte* glVersionCString = glGetString(GL_VERSION);
    QString glVersionQString;
    if (glVersionCString)
    {
        glVersionQString = reinterpret_cast<const char*>(glVersionCString);
        qInfo() << glVersionQString;
    }
    const GLubyte* glShadingVersionCString = glGetString(GL_SHADING_LANGUAGE_VERSION);
    QString glShadingVersionQString;
    if (glShadingVersionCString)
    {
        glShadingVersionQString = reinterpret_cast<const char*>(glShadingVersionCString);
        qInfo() << glShadingVersionQString;
    }
    QString curProfQStr = QString("Current profile Core profile. Version %1.%2").arg(context->format().version().first).arg(context->format().version().second);
    qInfo() << curProfQStr;
}


void OpenGLWidget::initializeGL()
{
    #define PROGRAM_VERTEX_ATTRIBUTE 0
    #define PROGRAM_TEXCOORD_ATTRIBUTE 1

    initializeOpenGLFunctions();
    getGraphicsInfo();
    //AcrylicShader
    m_shaderManager->createShaderProgram("acrylicShader");
    m_shaderManager->makeActiveShader("acrylicShader");
    bool result = true;
    result = result && m_shaderManager->addShaderFromFile(QOpenGLShader::Vertex, ":/Content/Shaders/acrylicShader.vsh");
    result = result && m_shaderManager->addShaderFromFile(QOpenGLShader::Fragment, ":/Content/Shaders/acrylicShader.fsh");
    if(!result) qWarning() << m_shaderManager->errorString();
    m_shaderManager->bindAttributeLocation("aVertexPosition", PROGRAM_VERTEX_ATTRIBUTE);
    m_shaderManager->bindAttributeLocation("aTexCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    m_shaderManager->linkShaderProgram();

    QOpenGLFramebufferObject *fbo = new QOpenGLFramebufferObject(this->size());
    QOpenGLFramebufferObject *fbo1 = new QOpenGLFramebufferObject(this->size());
    m_fboLst.append(fbo); m_fboLst.append(fbo1);
    m_modelManager->generateQuad("Quad");

    m_textureManager->loadTexture(":/Content/Textures/background.png", "background");
    m_textureManager->loadTexture(":/Content/Textures/background2.png", "background2");
    m_textureManager->loadTexture(":/Content/Textures/background3.png", "background3");

    glClearColor(0.75,0.75,0.75,1.0);
    m_timer->start(16);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    switch(getAcrylicShaderSettings()->getBackgroundWallpaper())
    {
        case 1: m_textureManager->bindTexture("background"); break;
        case 2: m_textureManager->bindTexture("background2");  break;
        case 3: m_textureManager->bindTexture("background3"); break;
        default: m_textureManager->bindTexture("background");
    }

    m_fboLst.at(0)->bind();
    m_shaderManager->bindShader("acrylicShader");
    m_shaderManager->setUniformValue("pass",1);
    m_shaderManager->setUniformValue("v_offset",getAcrylicShaderSettings()->getBorderRelativeSize());
    m_shaderManager->setUniformValue("height",(float)this->height());
    m_shaderManager->setUniformValue("width",(float)this->width());
    m_shaderManager->setUniformValue("tintOpacity",getAcrylicShaderSettings()->getTintOpacity());
    QColor tintQColor = getAcrylicShaderSettings()->getTintColor();
    m_shaderManager->setUniformValue("tintColor", tintQColor.redF(), tintQColor.greenF(), tintQColor.blueF());
    m_shaderManager->setUniformValue("noiseOpacity",getAcrylicShaderSettings()->getNoiseOpacity());
    m_shaderManager->setUniformValue("blendMode",getAcrylicShaderSettings()->getTintCompositionMode());
    m_modelManager->getModelByName("Quad")->renderModel();
    m_fboLst.at(0)->release();
    for(int i=0; i<getAcrylicShaderSettings()->getBlurPassingNumber(); i++)
    {
        m_fboLst.at(1)->bind();
        m_shaderManager->setUniformValue("pass",2);
        glBindTexture(GL_TEXTURE_2D, m_fboLst.at(0)->texture());
        m_modelManager->getModelByName("Quad")->renderModelToFBO();
        m_fboLst.at(1)->release();

        m_fboLst.at(0)->bind();
        m_shaderManager->setUniformValue("pass",3);
        glBindTexture(GL_TEXTURE_2D, m_fboLst.at(1)->texture());
        m_modelManager->getModelByName("Quad")->renderModelToFBO();
        m_fboLst.at(0)->release();
    }
    QOpenGLFramebufferObject::bindDefault();
    m_shaderManager->setUniformValue("pass",4);
    glBindTexture(GL_TEXTURE_2D, m_fboLst.at(0)->texture());
    m_modelManager->getModelByName("Quad")->renderModelToFBO();
    m_shaderManager->releaseShader();
    QOpenGLFramebufferObject::bindDefault();
}

void OpenGLWidget::resizeGL(int width, int height)
{
    for(int i = 0; i<m_fboLst.count(); i++)
    {
        QOpenGLFramebufferObject *fbo = m_fboLst.at(i);
        delete fbo;
        m_fboLst[i] = new QOpenGLFramebufferObject(QSize(width, height));
    }
}
