#ifndef HAPPYBIRSDAY_H
#define HAPPYBIRSDAY_H

#include <QString>
#include <map>
#include <vector>
#include "freqtable.h"

void generate_voice(double f, int sample_offset, double time, double F1, double F2, double F3, double BW, int Ncascade,
                    std::vector<short>* output_samples);


struct Notestruct
{
    char note;
    float t_start;
    float t_end;
};

class Happybirsday
{
public:
    FreqTable freq_table;

    Happybirsday();
    void generate_song(std::vector<Notestruct>& song);
    std::vector<Notestruct> parse_hb_notes(QString file);
    void parse_notes_table(QString file); // creates note2fre table

};

#endif // HAPPYBIRSDAY_H