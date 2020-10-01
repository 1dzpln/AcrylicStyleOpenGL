#ifndef SHADERSETTINGS_H
#define SHADERSETTINGS_H
#include <QColor>
/*! \brief Режимы смешивания. */
enum TintCompositionMode
{
    CM_ADD, ///< Сложение с учетом прозрачности: C=alfa*A+(1-alfa)*B
    CM_EXCLUSION, ///< Исключение с последующим учетом прозрачности C=A+B-2*(A*B) -> D=alfa*C+(1-alfa)*B
    CM_SCREEN, ///< Экран с последующим учетом прозрачности C=A+B-(A*B) -> D=alfa*C+(1-alfa)*B
    CM_MULTIPLY, ///< Умножение с последующим учетом прозрачности C=A*B -> D=alfa*C+(1-alfa)*B
    CM_LIGHTEN ///< Замена светлым с последующим учетом прозрачности max(A*B) -> D=alfa*C+(1-alfa)*B
};
/*! \brief Класс настроек шейдера. */
class AcrylicShaderSettings
{
    int m_blurPassingNumber; ///< Количество проходов для размытия по Гауссу
    QColor m_tintColor; ///< Цвет накладки
    float m_tintOpacity; ///< Прозрачность накладки
    TintCompositionMode m_tintComposMode; ///< Режим смешивания накладки и заднего фона
    float m_noiseOpacity; ///< Прозрачность шума
    float m_borderRelativeSize; ///< Величина границы (рамки)
    int m_backgroundWallpaper; ///< Номер картинки для заднего фона
public:
    AcrylicShaderSettings()
    {
        m_blurPassingNumber = 5;
        m_tintColor = QColor(57,58,53);
        m_tintOpacity = 0.65f;
        m_tintComposMode = CM_ADD;
        m_noiseOpacity = 0.025f;
        m_borderRelativeSize = 0.05f;
        m_backgroundWallpaper = 2;
    }
    /*! \brief Устанавливает количество проходов для размытия по Гауссу.
        \param int blurPassingNumber - количество проходов.*/
    void setBlurPassingNumber(int blurPassingNumber) {m_blurPassingNumber = blurPassingNumber;}
    /*! \brief Возвращает количество проходов для размытия по Гауссу.
        \return количество проходов.*/
    inline int getBlurPassingNumber() const {return m_blurPassingNumber;}
    /*! \brief Устанавливает цвет накладки.
        \param QColor tintColor - цвет накладки.*/
    void setTintColor(QColor tintColor) {m_tintColor = tintColor;}
    /*! \brief Возвращает цвет накладки.
        \return цвет накладки.*/
    inline QColor getTintColor() const {return m_tintColor;}
    /*! \brief Устанавливает прозрачность накладки.
        \param float tintOpacity - прозрачность накладки.*/
    void setTintOpacity(float tintOpacity) {m_tintOpacity = tintOpacity;}
    /*! \brief Возвращает прозрачность накладки.
        \return прозрачность накладки.*/
    inline float getTintOpacity() const {return m_tintOpacity;}
    /*! \brief Устанавливает режим смешивания накладки и заднего фона.
        \param TintCompositionMode tintComposMode - режим смешивания.*/
    void setTintCompositionMode(TintCompositionMode tintComposMode) {m_tintComposMode = tintComposMode;}
    /*! \brief Возвращает режим смешивания накладки и заднего фона.
        \return режим смешивания.*/
    inline TintCompositionMode  getTintCompositionMode() const {return m_tintComposMode;}
    /*! \brief Устанавливает прозрачность шума.
        \param float noiseOpacity - прозрачность шума.*/
    void setNoiseOpacity(float noiseOpacity) {m_noiseOpacity = noiseOpacity;}
    /*! \brief Возвращает прозрачность шума.
        \return прозрачность шума.*/
    inline float getNoiseOpacity() const {return m_noiseOpacity;}
    /*! \brief Устанавливает величину границы (рамки).
        \param float borderRelativeSize - величина границы (рамки).*/
    void setBorderRelativeSize(float borderRelativeSize) {m_borderRelativeSize = borderRelativeSize;}
    /*! \brief Возвращает величину границы (рамки).
        \return величина границы (рамки).*/
    inline float getBorderRelativeSize() const {return m_borderRelativeSize;}
    /*! \brief Устанавливает номер картинки для заднего фона.
        \param int backgroundWallpaper - номер картинки для заднего фона.*/
    void setBackgroundWallpaper(int backgroundWallpaper) {m_backgroundWallpaper = backgroundWallpaper;}
    /*! \brief Возвращает номер картинки для заднего фона.
        \return номер картинки для заднего фона.*/
    inline int getBackgroundWallpaper() const {return m_backgroundWallpaper;}
};
#endif // SHADERSETTINGS_H
