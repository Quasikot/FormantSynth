#ifndef SYNTEZER_H
#define SYNTEZER_H

#include <QVariant>
#include <map>
#include <QString>
#include <QElapsedTimer>
#include "alsadriver.h"
#include "freqtable.h"
#include "key2notetable.h"
#include "buffer.h"

class Syntezer : public QObject
{
    Q_OBJECT
public:
    AlsaDriver*          alsa;
    std::map<int,Buffer*>       key2noteBuffer;
    FreqTable                   freq_table;
    Key2NoteTable               key2note;

    Syntezer();    
    void parse_freqs_table(QString file);
    void out_pcm(short* buffer, int len);
    void drop_pcm_frames();
    virtual Buffer* play_note(char note, double duration, double velocity)=0;
    bool isEnabled() { return bEnabled; }
    void out_buffer(Buffer* buf);

    void prepareKeyTable();

signals:
    void sigNote(char note);
    void sigDisableNote(char note);

public slots:
    virtual void on_key_press(int key_code);
    virtual void on_key_release(int key_code);
    void on_Timer();

private:
    QElapsedTimer        key_time;
    bool                 bEnabled;
    bool                 bKeyPressed;

};

#endif // SYNTEZER_H