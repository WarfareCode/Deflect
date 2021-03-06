/*********************************************************************/
/* Copyright (c) 2013-2017, EPFL/Blue Brain Project                  */
/*                          Raphael Dumusc <raphael.dumusc@epfl.ch>  */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/*   1. Redistributions of source code must retain the above         */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer.                                                  */
/*                                                                   */
/*   2. Redistributions in binary form must reproduce the above      */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer in the documentation and/or other materials       */
/*      provided with the distribution.                              */
/*                                                                   */
/*    THIS  SOFTWARE  IS  PROVIDED  BY  THE  ECOLE  POLYTECHNIQUE    */
/*    FEDERALE DE LAUSANNE  ''AS IS''  AND ANY EXPRESS OR IMPLIED    */
/*    WARRANTIES, INCLUDING, BUT  NOT  LIMITED  TO,  THE  IMPLIED    */
/*    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  A PARTICULAR    */
/*    PURPOSE  ARE  DISCLAIMED.  IN  NO  EVENT  SHALL  THE  ECOLE    */
/*    POLYTECHNIQUE  FEDERALE  DE  LAUSANNE  OR  CONTRIBUTORS  BE    */
/*    LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,    */
/*    EXEMPLARY,  OR  CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT NOT    */
/*    LIMITED TO,  PROCUREMENT  OF  SUBSTITUTE GOODS OR SERVICES;    */
/*    LOSS OF USE, DATA, OR  PROFITS;  OR  BUSINESS INTERRUPTION)    */
/*    HOWEVER CAUSED AND  ON ANY THEORY OF LIABILITY,  WHETHER IN    */
/*    CONTRACT, STRICT LIABILITY,  OR TORT  (INCLUDING NEGLIGENCE    */
/*    OR OTHERWISE) ARISING  IN ANY WAY  OUT OF  THE USE OF  THIS    */
/*    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                   */
/* The views and conclusions contained in the software and           */
/* documentation are those of the authors and should not be          */
/* interpreted as representing official policies, either expressed   */
/* or implied, of Ecole polytechnique federale de Lausanne.          */
/*********************************************************************/

#ifndef DEFLECT_SERVER_IMAGEJPEGDECOMPRESSOR_H
#define DEFLECT_SERVER_IMAGEJPEGDECOMPRESSOR_H

#include <deflect/api.h>
#include <deflect/defines.h>
#include <deflect/server/types.h>

#include <turbojpeg.h>

#include <QByteArray>

namespace deflect
{
namespace server
{
/**
 * JPEG header information.
 */
struct JpegHeader
{
    int width = 0;
    int height = 0;
    ChromaSubsampling subsampling;
};

/**
 * Decompress Jpeg compressed data.
 */
class ImageJpegDecompressor
{
public:
    DEFLECT_API ImageJpegDecompressor();
    DEFLECT_API ~ImageJpegDecompressor();

    /**
     * Decompress the header of a Jpeg image.
     *
     * @param jpegData The compressed Jpeg data
     * @return The decompressed Jpeg header
     * @throw std::runtime_error if a decompression error occured
     */
    DEFLECT_API JpegHeader decompressHeader(const QByteArray& jpegData);

    /**
     * Decompress a Jpeg image.
     *
     * @param jpegData The compressed Jpeg data
     * @return The decompressed image data in (GL_)RGBA format
     * @throw std::runtime_error if a decompression error occured
     */
    DEFLECT_API QByteArray decompress(const QByteArray& jpegData);

#ifndef DEFLECT_USE_LEGACY_LIBJPEGTURBO

    using YUVData = std::pair<QByteArray, ChromaSubsampling>;

    /**
     * Decompress a Jpeg image to YUV, skipping the YUV -> RGBA conversion step.
     *
     * @param jpegData The compressed Jpeg data
     * @return The decompressed image data in YUV format
     * @throw std::runtime_error if a decompression error occured
     */
    DEFLECT_API YUVData decompressToYUV(const QByteArray& jpegData);

#endif

private:
    /** libjpeg-turbo handle for decompression */
    tjhandle _tjHandle;
};
}
}

#endif
