#include <QTransform>
//#include <QtMath>
#include "formantsynthsvg.h"


FormantSynthSvg::FormantSynthSvg(QWidget *parent) : SvgWidget(parent)
{
    minRotateAngle = -270;
    maxRotateAngle = 0;
    SvgLoad("./images/formant_synth.svg");
    LoadDom("./images/formant_synth.svg");
    QPointF center = findPathCenter("F9");
    rotateNode("F9", center, -270);
    setStroke("F9", Qt::red);    
    LoadRenderDOM();
    SaveDom("./images/formant_synth_dom.svg");

    //Init Sliders
    for(int i=1; i < 10; i++)
    {
        QString name = QString("F%1").arg(i);
        QRectF rect = getPath(name).boundingRect();
        float w = rect.width();
        rect.setX(rect.center().x() - w );
        rect.setY(rect.center().y() - w );
        rect.setWidth(w*2);
        rect.setHeight(w*2);
        freqSliders[i] = Slider(rect, name);
    }

    //Init buttons
    buttons[0] = Button(getEllipse("A_but"),"A_but");
    buttons[1] = Button(getEllipse("I_but"),"I_but");
    buttons[2] = Button(getEllipse("O_but"),"O_but");
    buttons[3] = Button(getEllipse("E_but"),"E_but");

    setFocus();
}

void  FormantSynthSvg::mousePressEvent(QMouseEvent* event)
{
    QPoint pos = event->pos();
    //pos.setY(height() - pos.y());
    QPointF p = mapToViewbox(pos, viewbox);
    for(int i=0; i < 4; i++)
    {
        if( buttons[i].rect.contains(p) )
        {
            setFill(buttons[i].name,Qt::red,1);
            switch(i)
            {
                case 0:
                    emit sigA_but();
                break;
                case 1:
                    emit sigI_but();
                break;
                case 2:
                    emit sigO_but();
                break;
                case 3:
                    emit sigE_but();
                break;
            }
        }
        else
            setFill(buttons[i].name,QColor("#0e541b"),1);
    }
    LoadRenderDOM();
    repaint();

}

void  FormantSynthSvg::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint pos = event->pos();
    QPointF p = mapToViewbox(pos, viewbox);
    for(int i=0; i < 4; i++)
        setFill(buttons[i].name,QColor("#0e541b"),1);
    LoadRenderDOM();
    repaint();
}


double Slider::findNearestPointOnCircle(QPointF mouse, QPointF center, float R)
{
    double  X,Y,d, minD=100000000;
    double  min_angle;
    double  degree2rad = M_PI / 180.;
    for(double angle=0; angle < 360; angle+=0.1)
    {
        X = center.x() + R * cos( degree2rad * angle );
        Y = center.y() + R * sin( degree2rad * angle );
        d = (mouse.x() - X)*(mouse.x() - X) + (mouse.y() - Y)*(mouse.y() - Y);
        if(minD!=qMin(d, minD))
            min_angle = angle;
        minD = qMin(d, minD);
    }
    value = ((min_angle) / 360) * 10000;
    return min_angle-20;
}

void  FormantSynthSvg::mouseMoveEvent(QMouseEvent* event)
{

    QPoint pos = event->pos();
    //pos.setY(height() - pos.y());
    QPointF p = mapToViewbox(pos, viewbox);

    float angle;
    for(int i=0; i < 10; i++)
    {
        angle = freqSliders[i].findNearestPointOnCircle(p, freqSliders[i].rect.center(),
                                                           freqSliders[i].rect.width());
        if( freqSliders[i].rect.contains(p) )
        {
            fprintf(stderr,"value %f\n", freqSliders[i].value);
            setStroke(freqSliders[i].name, freqSliders[i].activeColor);
            rotateNode(freqSliders[i].name, freqSliders[i].rect.center(), angle);
            setText(freqSliders[i].name + "g",
                    QString::number(int(freqSliders[i].value)) + " Hz");
        }
        else
            setStroke(freqSliders[i].name, freqSliders[i].defaultColor);
    }
    for(int i=0; i < 4; i++)
    {
        if( buttons[i].rect.contains(p) )
            setFill(buttons[i].name,Qt::red,1);
        else
            setFill(buttons[i].name,QColor("#0e541b"),1);
    }
    LoadRenderDOM();
    repaint();
}

void FormantSynthSvg::paintEvent(QPaintEvent* event)
{
    /*
    painter.fillRect(this->rect(),Qt::red);
    painter.drawPixmap(this->rect(),QPixmap::fromImage(background));
    */
    SvgWidget::paintEvent(event);
}
