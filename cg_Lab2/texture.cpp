#include <iostream>
#include "texture.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
    m_pImage = NULL;
}


bool Texture::Load()
{
    //для загрузки из файла и подготовки памяти для загрузки в OpenGL
    try {
        m_pImage = new Magick::Image(m_fileName); //Этот вызов загружает текстуру в память, которая задана private и не может быть напрямую использована OpenGL.
        m_pImage->write(&m_blob, "RGBA"); //Затем мы записываем изображение в объект Magick::Blob используя формат RGBA
    }
    catch (Magick::Error& Error) {
        std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
        return false;
    }

    glGenTextures(1, &m_textureObj); //генерирует указанное число объектов текстур и помещает их в указатель на массив GLuint
    glBindTexture(m_textureTarget, m_textureObj); //сообщает OpenGL объект текстуры, который относится ко всем вызовам, связанным с текстурами, до тех пор, пока новый объект текстур не будет передан
    glTexImage2D(m_textureTarget, 0, GL_RGB, m_pImage->columns(), m_pImage->rows(), -0.50, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data()); //функция для загрузки главной части объекта текстуры
    /*Здесь мы указываем фильтры, которые будут использованы для увеличения и минимализации*/
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}
//привязываем объект текстур
void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}