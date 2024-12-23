#include "module.h"
#include <QGridLayout>
#include <QString>
#include <QDoubleValidator>
#include <QMessageBox>
#include <iostream>
#include <cmath>

Module::Module():QWidget()
{
    QObject::connect(le1, SIGNAL(textEdited(QString)), this, SLOT(le1Changed()));
    QObject::connect(le2, SIGNAL(textEdited(QString)), this, SLOT(le2Changed()));
    QObject::connect(le3, SIGNAL(textEdited(QString)), this, SLOT(le3Changed()));
    QObject::connect(le4, SIGNAL(textEdited(QString)), this, SLOT(le4Changed()));
    QObject::connect(s1, SIGNAL(valueChanged(int)), this, SLOT(s1Moved()));
    QObject::connect(s2, SIGNAL(valueChanged(int)), this, SLOT(s2Moved()));
    QObject::connect(s3, SIGNAL(valueChanged(int)), this, SLOT(s3Moved()));
    QObject::connect(s4, SIGNAL(valueChanged(int)), this, SLOT(s4Moved()));
    QGridLayout *l = new QGridLayout;
    lsystem->setAlignment(Qt::AlignCenter);
    l->addWidget(lsystem, 0, 1, 1, 1);
    l->addWidget(l1, 1, 0, 1, 1);
    l->addWidget(l2, 4, 0, 1, 1);
    l->addWidget(l3, 7, 0, 1, 1);
    l->addWidget(l4, 10, 0, 1, 1);
    l->addWidget(le1, 1, 1, 1, 2);
    l->addWidget(le2, 4, 1, 1, 2);
    l->addWidget(le3, 7, 1, 1, 2);
    l->addWidget(le4, 10, 1, 1, 2);
    l->addWidget(s1, 2, 0, 2, 3);
    l->addWidget(s2, 5, 0, 2, 3);
    l->addWidget(s3, 8, 0, 2, 3);
    l->addWidget(s4, 11, 0, 2, 3);
    this->setLayout(l);
}

void Module::s1Moved(){
    le1->setText(QString::number(s1->value()));
    if(sliderRecalc){
    le1Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}

void Module::s2Moved(){
    le2->setText(QString::number(s2->value()));
    if(sliderRecalc){
    le2Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}

void Module::s3Moved(){
    le3->setText(QString::number(s3->value()));
    if(sliderRecalc){
    le3Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}

void Module::s4Moved(){
    le4->setText(QString::number(s4->value()));
    if(sliderRecalc){
    le4Changed(true);
    }
    sliderRecalc = true;
    emit sliderMoved();
}

void Module::leChanged(QLineEdit* le, int min, int max, bool needRecalc){
    if(le->text().toDouble() > max){
        outOfRangeError(75);
        le->setText(QString::number(max));
    }
    if(le->text().toDouble() < min){
        outOfRangeError(79);
        le->setText(QString::number(min));
    }
    switch(type){
    case RGB:
        color.setRgb(le1->text().toDouble(), le2->text().toDouble(), le3->text().toDouble());
        break;
    case CMYK:
        color.setCmyk((le1->text().toDouble()*2.55),
            (le2->text().toDouble()*2.55),
            (le3->text().toDouble()*2.55),
                      ( le4->text().toDouble())*2.55);
        break;
    case HLS:
        color.setHsl((le1->text().toDouble()*2.55),
                     (le3->text().toDouble()*2.55),
                     (le2->text().toDouble()*2.55));
        break;
    }
    if(!needRecalc){
        setSliders();
        emit changed();
    }

    recalc = true;
}

void Module::le1Changed(bool a){
    switch(type){
        case RGB:
        leChanged(le1, 0, 255, a);
        break;
    case CMYK:
        leChanged(le1, 0, 100, a);
        break;
    case HLS:
        leChanged(le1, 0, 100, a);
        break;
    }
}

void Module::le2Changed(bool a){
    switch(type){
        case RGB:
        leChanged(le2, 0, 255, a);
        break;
    case CMYK:
        leChanged(le2, 0, 100, a);
        break;
    case HLS:
        leChanged(le2, 0, 100, a);
        break;
    }
}

void Module::le3Changed(bool a){
    switch(type){
        case RGB:
        leChanged(le3, 0, 255, a);
        break;
    case CMYK:
        leChanged(le3, 0, 100, a);
        break;
    case HLS:
        leChanged(le3, 0, 100, a);
        break;
    }
}

void Module::le4Changed(bool a){
    leChanged(le4, 0, 100, a);
}

void Module::outOfRangeError(int s){
    QMessageBox::information(NULL,QObject::tr("Warning"),tr("Value out of range! " ));
    std::cout<<s;
}

void Module::setSliders(){
    s1->blockSignals(true);
    s2->blockSignals(true);
    s3->blockSignals(true);
    s4->blockSignals(true);

    s1->setValue(le1->text().toInt());
    s2->setValue(le2->text().toInt());
    s3->setValue(le3->text().toInt());
    s4->setValue(le4->text().toInt());

    s1->blockSignals(false);
    s2->blockSignals(false);
    s3->blockSignals(false);
    s4->blockSignals(false);

}

void Module::setType(enum::type t){
    type = t;
    QDoubleValidator* v1 = new QDoubleValidator();
    QDoubleValidator* v2 = new QDoubleValidator();
    QDoubleValidator* v3 = new QDoubleValidator();
    QDoubleValidator* v4 = new QDoubleValidator();
    switch (t)
    {
    case type::RGB:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("RGB");
        l1->setText("R");
        l2->setText("G");
        l3->setText("B");
        v1->setRange(0.0,255.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 255);
        v2->setRange(0.0,255.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 255);
        v3->setRange(0.0,255.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 255);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    case type::CMYK:
        l4->show();
        le4->show();
        s4->show();
        lsystem->setText("CMYK");
        l1->setText("C");
        l2->setText("M");
        l3->setText("Y");
        l4->setText("K");
        v1->setRange(0.0,100.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 100);
        v2->setRange(0.0,100.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 100);
        v3->setRange(0.0,100.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 100);
        v4->setRange(0.0,100.0, 2);
        v4->setNotation(QDoubleValidator::StandardNotation);
        s4->setRange(0, 100);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        le4->setValidator(v4);
        break;
    case type::HLS:
        l4->hide();
        le4->hide();
        s4->hide();
        lsystem->setText("HLS");
        l1->setText("H");
        l2->setText("L");
        l3->setText("S");
        v1->setRange(0.0,100.0, 2);
        v1->setNotation(QDoubleValidator::StandardNotation);
        s1->setRange(0, 100);
        v2->setRange(0.0,100.0, 2);
        v2->setNotation(QDoubleValidator::StandardNotation);
        s2->setRange(0, 100);
        v3->setRange(0.0,100.0, 2);
        v3->setNotation(QDoubleValidator::StandardNotation);
        s3->setRange(0, 100);
        le1->setValidator(v1);
        le2->setValidator(v2);
        le3->setValidator(v3);
        break;
    }
    setColor(color);
}

void Module::setColor(QColor col){
    color = col;
    switch(type){
    case type::RGB:
        setRGB();
        break;
    case type::CMYK:
        setCMYK();
        break;
    case type::HLS:
        setHLS();
        break;
    }
    setSliders();
}

void Module::setRGB(){
    if(le1->text() != (QString::number(color.red()))){
    le1->setText(QString::number(color.red()));
    }
    if(le2->text() != (QString::number(color.green()))){
    le2->setText(QString::number(color.green()));
    }
    if(le3->text() != (QString::number(color.blue()))){
    le3->setText(QString::number(color.blue()));
    }
}

void Module::setCMYK(){
    int cyanValue = color.cyan()/2.55;
    int magentaValue = color.magenta()/2.55;
    int yellowValue = color.yellow()/2.55;
    int blackValue = color.black ()/2.55;

    if(le1->text() != (QString::number(cyanValue))){
        le1->setText(QString::number(cyanValue));
    }
    if(le2->text() != (QString::number(magentaValue))){
        le2->setText(QString::number(magentaValue));
    }
    if(le3->text() != (QString::number(yellowValue))){
        le3->setText(QString::number(yellowValue));
    }
    if(le4->text() != (QString::number(blackValue))){
        le4->setText(QString::number(blackValue));
    }
}

void Module::setHLS(){
    int hueValue = color.hue()/2.55;
    int lightnessValue = color.lightness()/2.55;
    int saturationValue = color.saturation()/2.55;
    if(color.hslHue()>=0 && le1->text() != QString::number(hueValue)){
        le1->setText(QString::number(hueValue));
    }else if(color.hslHue() < 0 && le1->text() != "0"){
        le1->setText("0");
    }
    if(le2->text() != QString::number(lightnessValue)){
    le2->setText(QString::number(lightnessValue));
    }
    if(le3->text() != QString::number(saturationValue)){
    le3->setText(QString::number(saturationValue));
    }
}
