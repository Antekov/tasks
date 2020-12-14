#include <cmath>
#include <cstdio>
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

const double PI = atan(1)*4;

typedef std::complex<double> base;
 
void fft (std::vector<base> & a, bool invert) {
	int n = (int) a.size();
	if (n == 1)  return;
 
	std::vector<base> a0 (n/2),  a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i+1];
	}
	fft (a0, invert);
	fft (a1, invert);
 
	double ang = 2*PI/n * (invert ? -1 : 1);
	base w (1),  wn (cos(ang), sin(ang));
	for (int i=0; i<n/2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i+n/2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2,  a[i+n/2] /= 2;
		w *= wn;
	}
}

// Структура, описывающая заголовок WAV файла.
struct WAVHEADER
{
    // WAV-формат начинается с RIFF-заголовка:

    // Содержит символы "RIFF" в ASCII кодировке
    // (0x52494646 в big-endian представлении)
    char chunkId[4];

    // 36 + subchunk2Size, или более точно:
    // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
    // Это оставшийся размер цепочки, начиная с этой позиции.
    // Иначе говоря, это размер файла - 8, то есть,
    // исключены поля chunkId и chunkSize.
    unsigned int chunkSize;

    // Содержит символы "WAVE"
    // (0x57415645 в big-endian представлении)
    char format[4];

    // Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
    // Подцепочка "fmt " описывает формат звуковых данных:

    // Содержит символы "fmt "
    // (0x666d7420 в big-endian представлении)
    char subchunk1Id[4];

    // 16 для формата PCM.
    // Это оставшийся размер подцепочки, начиная с этой позиции.
    unsigned int subchunk1Size;

    // Аудио формат, полный список можно получить здесь http://audiocoding.ru/wav_formats.txt
    // Для PCM = 1 (то есть, Линейное квантование).
    // Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
    unsigned short audioFormat;

    // Количество каналов. Моно = 1, Стерео = 2 и т.д.
    unsigned short numChannels;

    // Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
    unsigned int sampleRate;

    // sampleRate * numChannels * bitsPerSample/8
    unsigned int byteRate;

    // numChannels * bitsPerSample/8
    // Количество байт для одного сэмпла, включая все каналы.
    unsigned short blockAlign;

    // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
    unsigned short bitsPerSample;

    // Подцепочка "data" содержит аудио-данные и их размер.

    // Содержит символы "data"
    // (0x64617461 в big-endian представлении)
    char subchunk2Id[4];

    // numSamples * numChannels * bitsPerSample/8
    // Количество байт в области данных.
    unsigned int subchunk2Size;

    // Далее следуют непосредственно Wav данные.
    };

int main()
{
    FILE *file = fopen("speech.wav", "rb");
    FILE *out = fopen("speech_out.wav", "wb");
    if (!file || !out)
    {
        std::cout << "Failed open file";
        return 0;
    }

    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, file);
    fwrite(&header, sizeof(WAVHEADER), 1, out);

    // Выводим полученные данные
    std::cout << header.chunkId[0] << header.chunkId[1] << header.chunkId[2] << header.chunkId[3] << std::endl;
    printf("Chunk size: %d\n", header.chunkSize);
    std::cout << header.format[0] << header.format[1] << header.format[2] << header.format[3] << std::endl;
    std::cout << header.subchunk1Id[0] << header.subchunk1Id[1] << header.subchunk1Id[2] << header.subchunk1Id[3] << std::endl;
    printf("SubChunkId1: %d\n", header.subchunk1Size);
    printf("Audio format: %d\n", header.audioFormat);
    printf("Channels: %d\n", header.numChannels);
    printf("Sample rate: %d\n", header.sampleRate);
    printf("Bits per sample: %d\n", header.bitsPerSample);
    std::cout << header.subchunk2Id[0] << header.subchunk2Id[1] << header.subchunk2Id[2] << header.subchunk2Id[3] << std::endl;

    // Посчитаем длительность воспроизведения в секундах
    float fDurationSeconds = 1.f * header.subchunk2Size / (header.bitsPerSample / 8) / header.numChannels / header.sampleRate;
    int iDurationMinutes = (int)floor(fDurationSeconds) / 60;
    fDurationSeconds = fDurationSeconds - (iDurationMinutes * 60);
    printf("Duration: %02d:%02.f\n", iDurationMinutes, fDurationSeconds);

    int16_t* data = new int16_t[header.subchunk2Size / 2];
    size_t res = fread(data, sizeof(int16_t), header.subchunk2Size / 2, file);
    
    
    std::cout << "Readed values: " << res << std::endl;

    std::cout << "Data is successfully loaded." << std::endl;

    std::cout << header.subchunk2Size << std::endl;

    int n = header.subchunk2Size / 2, k = 0;

    int m = 0.2 * n;

    while (n > 0) {
        n /= 2;
        k++;
    }

    n = 1 << k;
    std::cout << "Ext size: " << n << std::endl;
    
    std::vector<base> d(n);

    for (int i = 0; i < header.subchunk2Size / 2; i++) {
        d[i] = base(data[i], 0);
    }

    fft(d, false);

    for (int i = m; i < n; i++) {
        d[i] = 0;
    }

    fft(d, true);

    for (int i = 0; i < header.subchunk2Size / 2; i++) {
        data[i] = d[i].real();
    }
    
    fwrite(data, sizeof(int16_t), header.subchunk2Size / 2, out);

    delete[] data;

    fclose(file);
    fclose(out);
    
    return 0;
}
