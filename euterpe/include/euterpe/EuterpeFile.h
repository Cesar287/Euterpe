#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace euterpe {

enum class AudioFormat { Error, NotLoaded, Wav, Aiff };

template <typename T> class EuterpeFile {
public:
  using RawBuffer = std::vector<uint8_t>;
  using AudioBuffer = std::vector<std::vector<T>>;

  EuterpeFile();
  EuterpeFile(const std::string &filePath);

  uint32_t getSampleRate() const { return mSampleRate; }
  uint32_t getBitDepth() const { return mBitDepth; }

private:
  bool loadFromFile(const std::string &filePath);
  bool loadFromBuffer(const RawBuffer &buffer);
  bool parseWavData(const RawBuffer & buffer);
  AudioBuffer mSamples;
  AudioFormat mAudioFormat;
  uint32_t mSampleRate;
  int mBitDepth;
};

template <typename T>
EuterpeFile<T>::EuterpeFile()
    : mAudioFormat(AudioFormat::NotLoaded), mSampleRate(44100), mBitDepth(16) {
  mSamples.resize(1);
  mSamples[0].resize(0);
};

template <typename T> EuterpeFile<T>::EuterpeFile(const std::string &filePath) {
  loadFromFile(filePath);
}

// @TODO : move the read to a file utils class
template <typename T>
bool EuterpeFile<T>::loadFromFile(const std::string &filePath) {
  std::ifstream file(filePath, std::ios::binary);

  if (!file.good()) {
    // @TODO : Report error
    return false;
  }

  RawBuffer dataBuffer;

  file.seekg(0, std::ios::end);
  std::size_t fileSize = file.tellg();
  file.seekg(0, std::ios::beg);

  dataBuffer.resize(fileSize);

  file.read(reinterpret_cast<uint8_t *>(dataBuffer.data(), fileSize));
  file.close();

  if (file.gcount() != fileSize) {
    //@TODO : Report an error
    return false;
  }

  return loadFromBuffer(dataBuffer);
}

template <typename T>
bool EuterpeFile<T>::loadFromBuffer(const RawBuffer &buffer) {}


template <typename T>
bool EuterpeFile<T>::parseWavData(const RawBuffer &buffer) {

}

} // namespace euterpe
