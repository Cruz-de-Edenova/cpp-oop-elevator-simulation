#include "sample_buffer.h"

/* ============================================================
                        klasa SampleBuffer
   ============================================================ */

// Stvara spremnik s odabranim brojem kanala i kapacitetom svakog kanala
SampleBuffer::SampleBuffer(int channelCount, int capacity)
    : mChannelCount{channelCount}, 
      mCapacity{capacity}  
{
    mPtrSamples = new int*[mChannelCount];
    
    // Alocira zasebno polje uzoraka za svaki kanal
    for (int i{0}; i < mChannelCount; ++i)
    {
        mPtrSamples[i] = new int[mCapacity];
    }
    
    mPtrSampleCounts = new int[mChannelCount]{0};
}

// Stvara neovisnu kopiju spremnika sa svim njegovim kanalima
SampleBuffer::SampleBuffer(const SampleBuffer& refSource)
    : mPtrSamples{new int*[refSource.mChannelCount]},
      mPtrSampleCounts{new int[refSource.mChannelCount]},
      mChannelCount{refSource.mChannelCount},
      mCapacity{refSource.mCapacity}
{
    for (int channel{0}; channel < mChannelCount; ++channel)
    {
        // Alocira polje uzoraka za odabrani kanal
        mPtrSamples[channel] = new int[mCapacity];
    
        // Kopira broj spremljenih uzoraka odabranog kanala
        mPtrSampleCounts[channel] = refSource.mPtrSampleCounts[channel];
    
        // Kopira sve spremljene uzorke odabranog kanala
        for (int index{0}; index < mPtrSampleCounts[channel]; ++index)
        {
            mPtrSamples[channel][index] = refSource.mPtrSamples[channel][index];
        }
    }    
}

// Oslobađa sva dinamički alocirana polja spremnika
SampleBuffer::~SampleBuffer()
{
    for (int i{0}; i < mChannelCount; ++i)
    {
        delete[] mPtrSamples[i];
    }
    
    delete[] mPtrSamples;
    delete[] mPtrSampleCounts;
}

// Dodaje uzorak u odabrani kanal ako ima slobodnog mjesta
bool SampleBuffer::add_sample(int channel, int sample)
{
    if (mPtrSampleCounts[channel] < mCapacity)
    {
        mPtrSamples[channel][mPtrSampleCounts[channel]] = sample;
        ++(mPtrSampleCounts[channel]);
        return true;
    }

    return false;
}

// Vraća kapacitet svakog kanala
int SampleBuffer::get_capacity() const
{
    return mCapacity;
}

// Vraća broj spremljenih uzoraka odabranog kanala
int SampleBuffer::get_sample_count(int channel) const
{
    return mPtrSampleCounts[channel];
}

// Vraća spremljeni uzorak na zadanom indeksu odabranog kanala
int SampleBuffer::get_sample(int channel, int index) const
{
    return mPtrSamples[channel][index];
}

// Vraća broj ADC kanala
int SampleBuffer::get_channel_count() const
{
    return mChannelCount;
}
