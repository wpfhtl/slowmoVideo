/*
 * class to export a movie using ffmpeg
*/

#ifndef _FFMPEG_WRITER
#define _FFMPEG_WRITER

#include <QImage>
#include <QtCore/QProcess>
#include <QtCore/QRegExp>

#include "video_enc.h"

// Against the «UINT64_C not declared» message.
// See: http://code.google.com/p/ffmpegsource/issues/detail?id=11
#ifdef __cplusplus
 #ifndef __STDC_CONSTANT_MACROS
 #define __STDC_CONSTANT_MACROS
 #ifdef _STDINT_H
  #undef _STDINT_H
 #endif
 # include <stdint.h>
 #endif // __STDC_CONSTANT_MACROS
#endif

extern "C" {
// ffmpeg libs
#include "../lib/ffmpegEncode_sV.h"
}

class VideoFFMPEG : public QObject, public VideoWriter {
	Q_OBJECT
	
    int mHeight;
    int mWidth;
    double movieFPS;

	 char* m_filename;
	 char* m_vcodec;
    VideoOut_sV *m_videoOut;
    
private:
	static QRegExp regexFrameNumber;
	QProcess *process;
	
public:
    VideoFFMPEG(int width,int height,double fps,const char *vcodec,const char* vquality,const char *filename);
    ~VideoFFMPEG();
    
    int writeFrame(const QImage& frame);
    int exportFrames(QString filepattern, RenderTask_sV *progress);
    
    private slots:

    /**
     *  Checks the progress of the ffmpeg threads by reading their stderr
    */
    void slotProgressUpdate();
};

#endif // _FFMPEG_WRITER
