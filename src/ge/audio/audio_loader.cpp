#include "ge/audio/audio_loader.hpp"
#include <ge/utils/log.hpp>
#include <vector>
#include <stb_vorbis.h>


ge::AudioInfos ge::AudioLoader::load(const std::string &filename)
{
    AudioInfos infos;
    int error;
    stb_vorbis* vorbis = stb_vorbis_open_filename(filename.c_str(), &error, nullptr);
    if (!vorbis) {
        fprintf(stderr, "Failed to open Ogg Vorbis file: %s\n", filename.c_str());
        std::cout << error << std::endl;
        return infos;
    }

    // Obtenir les informations sur le fichier
    int channels = vorbis->channels;
    int sampleRate = vorbis->sample_rate;

    // Déterminer le format audio
    ALenum format;
    if (channels == 1)
        format = AL_FORMAT_MONO16;
    else if (channels == 2)
        format = AL_FORMAT_STEREO16;
    else {
        fprintf(stderr, "Unsupported number of channels: %d\n", channels);
        stb_vorbis_close(vorbis);
        return infos;
    }

    // Lire les données audio
    const int bufferSize = 4096;
    std::vector<short> samples;
    samples.reserve(bufferSize);

    while (true) {
        short tempBuffer[bufferSize];
        int numSamples = stb_vorbis_get_samples_short_interleaved(vorbis, channels, tempBuffer, bufferSize);
        if (numSamples <= 0)
            break;

        samples.insert(samples.end(), tempBuffer, tempBuffer + numSamples * channels);
    }
    stb_vorbis_close(vorbis);
    infos.channels = channels;
    infos.data = samples;
    infos.format = format;
    infos.sample_rate = sampleRate;
    infos.size = sizeof(short) * samples.size();
    return infos;
}
