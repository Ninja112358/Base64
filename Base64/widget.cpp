#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

#define HOTKEYID 1001

Widget::Widget(QWidget *parent) : QWidget(parent),ui(new Ui::Widget){
    ui->setupUi(this);
    ui->output_decode->setReadOnly(true);
    ui->output_encode->setReadOnly(true);


    board = QApplication::clipboard();
    //注册热键
    RegisterHotKey((HWND)winId(), HOTKEYID, MOD_CONTROL, VK_E);//虚拟键代码A:0x41
    RegisterHotKey((HWND)winId(), HOTKEYID, MOD_CONTROL, VK_D);
    //qApp->installNativeEventFilter(this);

    QSize laSize= this->size();
    QPixmap image(":/sb.jpg");
    QPixmap image1 = image.scaled(laSize,Qt::IgnoreAspectRatio);//重新调整图像大小以适应窗口
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(image1));
    this->setPalette(palette);
    connect(ui->encode,&QPushButton::clicked,[=](){
        ui->output_encode->setText(Encode(ui->input_encode->toPlainText()));
    });
    connect(ui->decode,&QPushButton::clicked,[=](){
        ui->output_decode->setText(Decode(ui->input_decode->toPlainText()));
    });
}
Widget::~Widget(){
    delete ui;
}
void Widget::on_input_encode_selectionChanged(){
    ui->decode->setShortcut(tr(""));
    ui->encode->setShortcut(tr("Ctrl+Return"));
}
void Widget::on_input_decode_selectionChanged(){
    ui->encode->setShortcut(tr(""));
    ui->decode->setShortcut(tr("Ctrl+Return"));
}
void Widget::resizeEvent(QResizeEvent*){
    QSize laSize= Widget::size();
    QPixmap image(":/sb.jpg");
    QPixmap image1 = image.scaled(laSize,Qt::IgnoreAspectRatio);//重新调整图像大小以适应窗口
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(image1));
    this->setPalette(palette);
}
bool Widget::nativeEventFilter(const QByteArray & eventType, void * message, long * result){
    if ("windows_generic_MSG" == eventType)
    {
        MSG *pMsg = (MSG*)message;
        // 判断Windows消息是否是热键消息且热键为Ctrl+E
        if ((WM_HOTKEY == pMsg->message) && (MOD_CONTROL == (UINT)LOWORD(pMsg->lParam)) && (VK_E == (UINT)HIWORD(pMsg->lParam))){
            board->setText(board->text());
            this->close();
        }
        // 判断Windows消息是否是热键消息且热键为Ctrl+D
        if ((WM_HOTKEY == pMsg->message) && (MOD_CONTROL == (UINT)LOWORD(pMsg->lParam)) && (VK_D == (UINT)HIWORD(pMsg->lParam))){

        }
    }
    return false;  // 必须返回false，否则主窗体会假死
}
