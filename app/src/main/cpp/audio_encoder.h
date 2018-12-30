#ifndef AUDIO_ENCODER_H
#define AUDIO_ENCODER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef UINT64_C
#define UINT64_C(value)__CONCAT(value,ULL)
#endif

extern "C" {
	#include "libavcodec/avcodec.h"
	#include "libavformat/avformat.h"
	#include "libavutil/avutil.h"
	#include "libswresample/swresample.h"
	#include "libavutil/samplefmt.h"
	#include "libavutil/common.h"
	#include "libavutil/channel_layout.h"
	#include "libavutil/opt.h"
	#include "libavutil/imgutils.h"
	#include "libavutil/mathematics.h"
};

#include "./CommonTools.h"

#ifndef PUBLISH_BITE_RATE
#define PUBLISH_BITE_RATE 64000
#endif

class AudioEncoder {
private:
	AVFormatContext *avFormatContext;
	AVCodecContext *avCodecContext;
	AVStream* audioStream;

	bool isWriteHeaderSuccess;
	double duration;

	FILE* testFile;

	AVFrame *input_frame;
	int buffer_size;
	uint8_t *samples;
	int samplesCursor;
	SwrContext *swrContext;
	uint8_t** convert_data;
	AVFrame* swrFrame;
	uint8_t *swrBuffer;
	int swrBufferSize;

	int publishBitRate;
	int audioChannels;
	int audioSampleRate;

	int totalSWRTimeMills;
	int totalEncodeTimeMills;

	//初始化的时候，要进行的工作
	int alloc_avframe();
	int alloc_audio_stream(const char * codec_name);
	//当够了一个frame之后就要编码一个packet
	void encodePacket();
    void addADTStoPacket(uint8_t* packet, int packetLen);
    void writeAACPakcetToFile(uint8_t* data, int datalen);

public:
	AudioEncoder();
	virtual ~AudioEncoder();

	int init(int bitRate, int channels, int sampleRate, int bitsPerSample, const char* aacFilePath, const char * codec_name);
	int init(int bitRate, int channels, int bitsPerSample, const char* aacFilePath, const char * codec_name);
	void encode(byte* buffer, int size);
	void destroy();
};
#endif //AUDIO_ENCODER_H
