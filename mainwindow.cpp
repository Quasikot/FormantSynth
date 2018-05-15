#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "test.h"
#include "ploter.h"
#include "formantsyntform.h"
#include "sounddriverdialog.h"
#include "nessyntform.h"
#include <QKeyEvent>

Ploter* p;
Ploter* p2;

//double* wavread(const std::string &filename, WAVEFORMATEX *pwfx, int* N);
//double mag(complex_double d);

QString input_file;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //график waveform
    p = new Ploter(ui->waveFrame);
    p->plot->setGeometry(ui->waveFrame->rect());

    //график spectrum
    //p2 = new Ploter(ui->specFrame);
    //p2->plot->setGeometry(ui->specFrame->rect());

    Test test;

    input_file = "oh-yeah-everything-is-fine.wav";
    connect(ui->actionSound_driver, SIGNAL(triggered(bool)), this, SLOT(on_sound_Settings()));


    FormantSyntForm* fwidget = new FormantSyntForm(this);
    ui->tabWidget->insertTab(0,fwidget,QIcon(),"Formant Synt");
    connect(this, SIGNAL(keyPressSig(int)), &fwidget->synt, SLOT(on_key_press(int)));
    connect(this, SIGNAL(keyReleaseSig(int)), &fwidget->synt, SLOT(on_key_release(int)));
    connect(this, SIGNAL(keyPressSig(int)), ui->pianoWidget, SLOT(on_key_press(int)));
    connect(this, SIGNAL(keyReleaseSig(int)), ui->pianoWidget, SLOT(on_key_release(int)));
    connect(ui->pianoWidget, SIGNAL(sigMouseKey(int)), &fwidget->synt, SLOT(on_key_press(int)));


    NesSyntForm* nwidget = new NesSyntForm(this);
    ui->tabWidget->insertTab(1,nwidget,QIcon(),"NES Synt");


    //on_processButton_clicked();
    //on_genButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sound_Settings()
{
    SoundDriverDialog* dialog = new SoundDriverDialog(this);
    dialog->show();
}

/*
void MainWindow::on_genButton_clicked()
{
    Test test;
    //test.test_gen_voice(ui->f_ot->value(), ui->F1->value(), ui->F2->value(),ui->F3->value(), ui->BW->value(), ui->Ncascade->value());


    complex_double** d;
    int rows, cols;
    d = stft(x, N, 1024, 1024, 1024/4, 8000, &rows, &cols);
    p2->clearvals(0);
    for(int n=0; n < N-5000; n++)
    {
        p->setXY(0,n,x[n]);
        p2->setXY(0,n,y[n]);
    }
    p->update_data();
    p2->update_data();

    //взятие fft
    int f =1024;
    double* fdata = (double*)malloc(sizeof(double)*f*2);
    fdata[0] = 0;
    for(int n=0; n < f; n++)
    {
      fdata[2*n+1] = x[n];
      fdata[2*n+2] = 0;
    }
    four1(fdata,f,1);
    p2->clearvals(0);
    p2->d_curves[0]->setStyle(QwtPlotCurve::Sticks);
    for(int n=0; n < f; n++)
    {
        std::complex<double> d(fdata[2*n+1],fdata[2*n+2]);

        //if(abs(d) > 0.01)
        p2->setXY(0,((double)n/1024)*48000,abs(d));
    }

    p2->update_data();
    QApplication::processEvents();

    //PlaySoundA("mmm-2.wav", 0, SND_FILENAME);

}


void MainWindow::on_pushButton_3_clicked()
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> d(0.5, 0.15);

    int time = 100;//abs(ui->dateTimeEdit->time().secsTo(QTime(0,0,0)));
    int SampleRate = 44100;
    int Nsamples = floor(time*SampleRate);
    double* x = zeroes(0, floor(time*SampleRate));
    double level=0;
    int pause_length = 3 * SampleRate;
    int next_pause = pause_length;
    p2->clearvals(0);
    p2->set_autoscale(true);

    for(int n=0; n<Nsamples; ++n)
    {
        x[n] = d(gen);
        //qDebug() << x[n];

        if( n >= next_pause && n <= (next_pause + pause_length) )
        {
            x[n] = 0.1 + d(gen)*level;
        }
        if( n == (next_pause + pause_length) )
        {
            pause_length = (3 + rand()%10) * SampleRate;
            next_pause = n + pause_length;
            level = 0.2 * ((double)rand()/RAND_MAX);
        }
        p2->setXY(0,n,x[n]);

    }
    p2->update_data();
    short* data = (short*)malloc(Nsamples*sizeof(short));

    for(int i=0; i<Nsamples; i++)
        data[i] = x[i] * 32768;

    wavwrite("white_noise.wav",data,Nsamples*2,44100,1);

}
    */


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if( !event->isAutoRepeat() )
      emit keyPressSig(event->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if( !event->isAutoRepeat() )
      emit keyReleaseSig(event->key());
}