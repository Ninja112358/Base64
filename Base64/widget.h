#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QByteArray>
#include "base64.h"
#include <QClipboard>
#include <string.h>
#include <QMainWindow>
#include <windows.h>
#include <string>
#include "keyboard.h"
#include <QAbstractNativeEventFilter>

namespace Ui {
class Widget;
}
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool nativeEventFilter(const QByteArray & eventType, void * message, long * result);
    QClipboard *board;

    QString Encode(QString str){
        Base64 b64;
        std::string IO = str.toStdString();
        char* be = new char[b64.GetEnCodeNum(IO.size())];
        b64.EnCode((unsigned char*)IO.c_str(), IO.size() + 1, (unsigned char*)be);
        IO = be;

        delete[] be;

        return QString::fromStdString(IO).toUtf8();
    }
    QString Decode(QString str){
        Base64 b64;
        std::string IO = str.toStdString();
        char* bd = new char[b64.GetDeCodeNum(sizeof(IO.size()))];
        b64.DeCode((unsigned char*)IO.c_str(), IO.size() + 1, (unsigned char*)bd);
        IO = bd;

        delete[] bd;

        return QString::fromStdString(IO).toUtf8();
    }
private slots:
    void on_input_encode_selectionChanged();
    void on_input_decode_selectionChanged();
private:
    Ui::Widget *ui;
    void resizeEvent(QResizeEvent*);

};
#endif // WIDGET_H
