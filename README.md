# FormantSynth
# FormantSynth

Формантный синтезатор
автор Баранов Владимир (vsbaranov83@gmail.com)
Лицензия GPL

Build with Qt 5.12.12

Program Homepage
https://sites.google.com/site/appfivedev/moi-programmy/formantnyj-sintezator

To use FormantSynth in multiple voices mode you need to create mixer device.
Put this following strings in  ~/.asoundrc file and restart your machine.
When select plug:dmix device in FormantSynth. Restart FormantSynth.

>>>> content of .asoundrc file >>>>>>>>>>>

pcm.hw3mix {
    type dmix
    ipc_key 1939 # must be unique
    slave {
            pcm "hw:0,0"
            channels 8
            period_size 1024
            buffer_size 4096
            rate 48000
    }
}

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
