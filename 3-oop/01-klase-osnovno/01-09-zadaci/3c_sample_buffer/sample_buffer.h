#ifndef SAMPLE_BUFFER_H
#define SAMPLE_BUFFER_H

class SampleBuffer
{
private:
    int** mPtrSamples;     // Pokazivač na polja uzoraka pojedinih kanala
    int* mPtrSampleCounts; // Pokazivač na polje brojeva spremljenih uzoraka
    int mChannelCount;     // Broj ADC kanala
    int mCapacity;         // Kapacitet svakog kanala

public:
    // Stvara spremnik s odabranim brojem kanala i kapacitetom svakog kanala
    SampleBuffer(int channelCount, int capacity);

    // Stvara neovisnu kopiju spremnika sa svim njegovim kanalima
    SampleBuffer(const SampleBuffer& refSource);
    
    // Oslobađa sva dinamički alocirana polja spremnika
    ~SampleBuffer();
    
    // Dodaje uzorak u odabrani kanal ako ima slobodnog mjesta
    bool add_sample(int channel, int sample);
    
    // Vraća kapacitet svakog kanala
    int get_capacity() const;
    
    // Vraća broj spremljenih uzoraka odabranog kanala
    int get_sample_count(int channel) const;
    
    // Vraća spremljeni uzorak na zadanom indeksu odabranog kanala
    int get_sample(int channel, int index) const;
    
    // Vraća broj ADC kanala
    int get_channel_count() const;
};

#endif