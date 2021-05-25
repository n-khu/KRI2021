#include "mainwindow.h"
#include "ui_mainwindow.h"

int heightRobot = 30;
int widthRobot = 35;

int CYAN = 1;
int MAGENTA = 2;
int TEAM = CYAN;

int KIRI = 1;
int KANAN = 2;
int FIELD = KIRI;

int formationMode = 0;
int markingMode = 0;
int strategyMode = 0;
int robotChosen = 3;

int flagResetST2 = 0;
int flagResetST3 = 0;
int flagResetGK = 0;

int scoreUS;
int scoreOPP;

int dataTCP1;
int dataTCP2;
int dataTCP3;

std::string bufferTCP = "a";
std::string bufferTCPtemp;

struct robot
{
    int type[5];
    int coor_x[5];
    int coor_y[5];
    int dist_ball;
    int reset_x[5];
    int reset_y[5];
    int angle_ball;
    int yaw;
    int mark;
    int x_ball[3];
    int y_ball[3];
} striker_1, striker_2, striker_3, keeper;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("ENSPARTAN BASESTATION - Farrel");

    mudp = new UDP(this);
    mtcp = new TCP(this);

    mudp->start();

    connect(ui->label_lapangan, SIGNAL(Mouse_Pressed()),    this, SLOT(mouseClicked()));
    connect(ui->label_lapangan, SIGNAL(Mouse_Pos()),        this, SLOT(mouseCurrentPos()));

    connect(ui->pushButton_formasiA, SIGNAL(released()), this, SLOT(formationButtonClicked()));
    connect(ui->pushButton_formasiB, SIGNAL(released()), this, SLOT(formationButtonClicked()));
    connect(ui->pushButton_formasiC, SIGNAL(released()), this, SLOT(formationButtonClicked()));
    connect(ui->pushButton_formasiD, SIGNAL(released()), this, SLOT(formationButtonClicked()));

    connect(ui->btnLB, SIGNAL(released()), this, SLOT(markingModeButtonClicked()));
    connect(ui->btnLM, SIGNAL(released()), this, SLOT(markingModeButtonClicked()));
    connect(ui->btnLT, SIGNAL(released()), this, SLOT(markingModeButtonClicked()));
    connect(ui->btnMB, SIGNAL(released()), this, SLOT(markingModeButtonClicked()));
    connect(ui->btnMM, SIGNAL(released()), this, SLOT(markingModeButtonClicked()));
    connect(ui->btnMT, SIGNAL(released()), this, SLOT(markingModeButtonClicked()));
    connect(ui->btnRB, SIGNAL(released()), this, SLOT(markingModeButtonClicked()));
    connect(ui->btnRM, SIGNAL(released()), this, SLOT(markingModeButtonClicked()));
    connect(ui->btnRT, SIGNAL(released()), this, SLOT(markingModeButtonClicked()));

    connect(ui->btnKOCYAN,      SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnFKCYAN,      SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnGKCYAN,      SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnTICYAN,      SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnCORCYAN,     SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnPENCYAN,     SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnKOMAGENTA,   SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnFKMAGENTA,   SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnGKMAGENTA,   SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnTIMAGENTA,   SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnCORMAGENTA,  SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnPENMAGENTA,  SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnSTART,       SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnSTOP,        SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnPARKING,     SIGNAL(released()), this, SLOT(refboxButtonClicked()));
    connect(ui->btnDROPBALL,    SIGNAL(released()), this, SLOT(refboxButtonClicked()));

    connect(ui->pushButton_strategy1, SIGNAL(released()), this, SLOT(strategyButtonClicked()));
    connect(ui->pushButton_strategy2, SIGNAL(released()), this, SLOT(strategyButtonClicked()));
    connect(ui->pushButton_strategy3, SIGNAL(released()), this, SLOT(strategyButtonClicked()));
    connect(ui->pushButton_strategy4, SIGNAL(released()), this, SLOT(strategyButtonClicked()));

    connect(this, SIGNAL(TeamFieldReady()), this,   SLOT(updateScore()));
    connect(this, SIGNAL(TCPReady()),       this,   SLOT(updateScore()));
//    connect(this, SIGNAL(TCPReady()),       this,   SLOT(tcpHeader(int,int,int)));

    connect(ui->pushButton_connect_refbox,SIGNAL(released()),   this,   SLOT(connectRefbox()));
    connect(mtcp,   SIGNAL(TCPStatusChanged(std::string)),      this,   SLOT(updateTCPStatus(std::string)));
    connect(this,   SIGNAL(TCPReady()),                         this,   SLOT(updateTCPLabel()));
    connect(this,   SIGNAL(TCPManualChanged(std::string)),      this,   SLOT(updateTCPStatus(std::string)));

    connect(mudp,SIGNAL(rcvUDPData(int,int,int,int,int,int,int,int)),   this,SLOT(updateUDPStatus(int,int,int,int,int,int,int,int)));
    connect(this,SIGNAL(UDPReady()),                                    this,SLOT(updateUDPLabel()));
    connect(this,SIGNAL(UDPSendReady(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int)),
            mudp,SLOT(updateUDPSendStatus(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int)));

    connect(this,SIGNAL(MousePositioningReady()),   this,   SLOT(updateOdometryRobot()));
    connect(this,SIGNAL(MarkingModeReady()),        this,   SLOT(updateOdometryRobot()));
    connect(this,SIGNAL(FormationReady()),          this,   SLOT(updateOdometryRobot()));
    connect(this,SIGNAL(TeamFieldReady()),          this,   SLOT(updateOdometryRobot()));
    connect(this,SIGNAL(UDPReady()),                this,   SLOT(updateOdometryRobot()));
    connect(this,SIGNAL(TCPReady()),                this,   SLOT(updateOdometryRobot()));

    connect(this,SIGNAL(MousePositioningReady()),   this,SLOT(updateUDPLabel()));
    connect(this,SIGNAL(FormationReady()),          this,SLOT(updateUDPLabel()));
    connect(this,SIGNAL(MarkingModeReady()),        this,SLOT(updateUDPLabel()));
    connect(this,SIGNAL(TCPReady()),                this,SLOT(updateUDPLabel()));

    connect(ui->pushButton_submitteamfield,SIGNAL(released()),this,SLOT(updateTeamAndField()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rotateRobot(int a)
{
    QApplication::processEvents();

    QPixmap ship(":/new/prefix1/GK");
    QPixmap rotate(ship.size());

    QPainter p(&rotate);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    p.translate(rotate.size().width() / 2, rotate.size().height() / 2);
    p.rotate(a);
    p.translate(-rotate.size().width() / 2, -rotate.size().height() / 2);

    p.drawPixmap(0, 0, ship);
    p.end();

    ui->label_robotkeeper->setPixmap(rotate);
}

void MainWindow::coordinate(int a, int b, int c, int d, int e, int f)
{
    ui->label_robotstriker_3->setGeometry(QRect(a-ui->label_robotstriker_3->size().width()/2,b-ui->label_robotstriker_3->size().height()/2,widthRobot,heightRobot));
    ui->label_robotstriker_2->setGeometry(QRect(c-ui->label_robotstriker_2->size().width()/2,d-ui->label_robotstriker_2->size().height()/2,widthRobot,heightRobot));
    ui->label_robotkeeper->setGeometry(QRect(e-ui->label_robotkeeper->size().width()/2,f-ui->label_robotkeeper->size().height()/2,widthRobot,heightRobot));
}

void MainWindow::coordinate2(int a,int b,int c,int d,int e,int f)
{
    ui->label_robotstriker_3_2->setGeometry(QRect(a-ui->label_robotstriker_3_2->size().width()/2,b-ui->label_robotstriker_3_2->size().height()/2,widthRobot,heightRobot));
    ui->label_robotstriker_2_2->setGeometry(QRect(c-ui->label_robotstriker_2_2->size().width()/2,d-ui->label_robotstriker_2_2->size().height()/2,widthRobot,heightRobot));
    ui->label_robotkeeper_2->setGeometry(QRect(e-ui->label_robotkeeper_2->size().width()/2,f-ui->label_robotkeeper_2->size().height()/2,widthRobot,heightRobot));
}

void MainWindow::coordinate3(int a, int b, int c, int d, int e, int f)
{
    striker_3.coor_x[2] = a;
    striker_3.coor_y[2] = b;
    striker_2.coor_x[2] = c;
    striker_2.coor_y[2] = d;
    keeper.coor_x[2] = e;
    keeper.coor_y[2] = f;
}

//----------------FUNGSI KEYBOARD----------------//

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        QApplication::exit();
    }
    if(event->key() == Qt::Key_1){
        ui->label_robotstatus->setText("KEEPER");
        robotChosen = 1;
    }
    else if(event->key() == Qt::Key_2){
        ui->label_robotstatus->setText("STRIKER 2");
        robotChosen = 2;
    }
    else if(event->key() == Qt::Key_3){
        ui->label_robotstatus->setText("STRIKER 3");
        robotChosen = 3;
    }
    else if(event->key() == Qt::Key_4){
        ui->label_robotstatus->setText("STRIKER 1");
        robotChosen = 4;
    }
}

//----------------FUNGSI MOUSE----------------//

void MainWindow::mouseClicked()
{
    if(robotChosen == 1)    //KEEPER
    {
        flagResetGK = 1;
        keeper.coor_x[1] = ui->label_lapangan->x + 340;
        keeper.coor_y[1] = ui->label_lapangan->y;
//        ui->label_58->setText(QString("%1, %2").arg(keeper.coor_x[1]).arg(keeper.coor_y[1]));
    }
    if(robotChosen == 4)    //STRIKER 1
    {
        flagResetST3 = 1;
        striker_1.coor_x[1] = ui->label_lapangan->x + 340;
        striker_1.coor_y[1] = ui->label_lapangan->y;
//        ui->label_40->setText(QString("%1, %2").arg(striker_1.coor_x[1]).arg(striker_1.coor_y[1]));
    }
    if(robotChosen == 2)    //STRIKER 2
    {
        flagResetST2 = 1;
        striker_2.coor_x[1] = ui->label_lapangan->x + 340;
        striker_2.coor_y[1] = ui->label_lapangan->y;
//        ui->label_25->setText(QString("%1, %2").arg(striker_2.coor_x[1]).arg(striker_2.coor_y[1]));

    }
    if(robotChosen == 3)    //STRIKER 3
    {
        flagResetST3 = 1;
        striker_3.coor_x[1] = ui->label_lapangan->x + 340;
        striker_3.coor_y[1] = ui->label_lapangan->y;
//        ui->label_2->setText(QString("%1, %2").arg(striker_3.coor_x[1]).arg(striker_3.coor_y[1]));
    }

    emit MousePositioningReady();
}

void MainWindow::mouseCurrentPos()
{
    ui->label_44->setText(QString("%1, %2").arg(ui->label_lapangan->x).arg(ui->label_lapangan->y));
}

//----------------FUNGSI BUTTON----------------//

void MainWindow::refboxButtonClicked()
{
    QPushButton * button = (QPushButton*) sender();

    if(button->text() == "KickOff C")
    {
        bufferTCP = "KICKOFF CYAN";
    }
    if(button->text() == "FreeKick C")
    {
        bufferTCP = "FREEKICK CYAN";
    }
    if(button->text() == "GoalKick C")
    {
        bufferTCP = "GOALKICK CYAN";
    }
    if(button->text() == "Throw In C")
    {
        bufferTCP = "THROWIN CYAN";
    }
    if(button->text() == "Corner C")
    {
        bufferTCP = "CORNER CYAN";
    }
    if(button->text() == "Penalty C")
    {
        bufferTCP = "PENALTY CYAN";
    }
    if(button->text() == "KickOff M")
    {
        bufferTCP = "CORNER MAGENTA";
    }
    if(button->text() == "FreeKick M")
    {
        bufferTCP = "FREEKICK MAGENTA";
    }
    if(button->text() == "GoalKick M")
    {
        bufferTCP = "GOALKICK MAGENTA";
    }
    if(button->text() == "Throw In M")
    {
        bufferTCP = "THROWIN MAGENTA";
    }
    if(button->text() == "Corner M")
    {
        bufferTCP = "CORNER MAGENTA";
    }
    if(button->text() == "Penalty M")
    {
        bufferTCP = "PENALTY MAGENTA";
    }
    if(button->text() == "Start")
    {
        bufferTCP = "START";
    }
    if(button->text() == "Stop")
    {
        bufferTCP = "STOP";
    }
    if(button->text() == "DropBall")
    {
        bufferTCP = "DROPPED BALL";
    }
    if(button->text() == "Parking")
    {
        bufferTCP = "PARKING";
    }
    emit TCPReady();
    emit TCPManualChanged(bufferTCP);

//    qDebug() << 1;
}

void MainWindow::formationButtonClicked()
{
    QPushButton * button = (QPushButton*) sender();
    ui->label_formationstatus->setText(button->text());

    if(button->text() == "A")
    {
        ui->label_formationstatus->setStyleSheet("background-color: rgb(52, 101, 164)");
        formationMode = 1;
    }
    else if(button->text() == "B")
    {
        ui->label_formationstatus->setStyleSheet("background-color: rgb(52, 101, 164)");
        formationMode = 2;
    }
    else if(button->text() == "C")
    {
        ui->label_formationstatus->setStyleSheet("background-color: rgb(92, 53, 102)");
        formationMode = 3;
    }
    else if(button->text() == "D")
    {
        ui->label_formationstatus->setStyleSheet("background-color: rgb(92, 53, 102)");
        formationMode = 4;
    }

    flagResetGK = 0;
    flagResetST2 = 0;
    flagResetST3 = 0;

    emit FormationReady();
}

void MainWindow::markingModeButtonClicked()
{
    QPushButton * button = (QPushButton*) sender();
    ui->label_fieldmodestatus->setText(button->text());

    if(button->text() == "LT")
    {
        ui->label_fieldmodestatus->setStyleSheet("background-color: rgb(186, 189, 182)");
        markingMode = 1;
    }
    else if(button->text() == "MT")
    {
        ui->label_fieldmodestatus->setStyleSheet("background-color: rgb(186, 189, 182)");
        markingMode = 4;
    }
    else if(button->text() == "RT")
    {
        ui->label_fieldmodestatus->setStyleSheet("background-color: rgb(186, 189, 182)");
        markingMode = 7;
    }
    else if(button->text() == "LM")
    {
        ui->label_fieldmodestatus->setStyleSheet("background-color: rgb(136, 138, 133)");
        markingMode = 2;
    }
    else if(button->text() == "MM")
    {
        ui->label_fieldmodestatus->setStyleSheet("background-color: rgb(136, 138, 133)");
        markingMode = 5;
    }
    else if(button->text() == "RM")
    {
        ui->label_fieldmodestatus->setStyleSheet("background-color: rgb(136, 138, 133)");
        markingMode = 8;
    }
    else if(button->text() == "LB")
    {
        ui->label_fieldmodestatus->setStyleSheet("background-color: rgb(85, 87, 83)");
        markingMode = 3;
    }
    else if(button->text() == "MB")
    {
        ui->label_fieldmodestatus->setStyleSheet("background-color: rgb(85, 87, 83)");
        markingMode = 6;
    }
    else if(button->text() == "RB")
    {
        ui->label_fieldmodestatus->setStyleSheet("background-color: rgb(85, 87, 83)");
        markingMode = 9;
    }

    flagResetGK = 0;
    flagResetST2 = 0;
    flagResetST3 = 0;

    emit MarkingModeReady();
}

void MainWindow::strategyButtonClicked()
{
    QPushButton * button = (QPushButton*) sender();
    ui->label_strategystatus->setText(button->text());

    if(button->text() == "1")
    {
        ui->label_strategystatus->setStyleSheet("background-color: rgb(115, 210, 22);");
        strategyMode = 1;
    }
    else if(button->text() == "2")
    {
        ui->label_strategystatus->setStyleSheet("background-color: rgb(164, 0, 0);");
        strategyMode = 2;
    }
    else if(button->text() == "3")
    {
        ui->label_strategystatus->setStyleSheet("background-color: rgb(196, 160, 0);");
        strategyMode = 3;
    }
    else if(button->text() == "4")
    {
        ui->label_strategystatus->setStyleSheet("background-color: rgb(206, 92, 0);");
        strategyMode = 4;
    }
}

//----------------FUNGSI TCP----------------//

void MainWindow::tcpHeader(int a, int b, int c)
{
    dataTCP1 = a;
    dataTCP2 = b;
    dataTCP3 = c;
}

void MainWindow::connectRefbox()
{
    mtcp->start();
}

void MainWindow::updateTCPStatus(std::string rcvString)
{
    bufferTCP = rcvString;

    if(bufferTCP == "WELCOME")              tcpHeader(1, 1, 0);
    else if(bufferTCP == "START")           tcpHeader(1, 2, 0);
    else if(bufferTCP == "STOP")            tcpHeader(1, 3, 0);
    else if(bufferTCP == "RESET")           tcpHeader(1, 4, 0);
    else if(bufferTCP == "FIRST HALF")      tcpHeader(1, 5, 0);
    else if(bufferTCP == "SECOND HALF")     tcpHeader(1, 6, 0);
    else if(bufferTCP == "HALF TIME")       tcpHeader(1, 7, 0);
    else if(bufferTCP == "END GAME")        tcpHeader(1, 8, 0);
    else if(bufferTCP == "DROPPED BALL")    tcpHeader(2, 1, 1);
    else if(bufferTCP == "PARKING")         tcpHeader(2, 1, 2);

    else if(bufferTCP == "KICKOFF CYAN")    tcpHeader(2, 2, 1);
    else if(bufferTCP == "FREEKICK CYAN")   tcpHeader(2, 2, 2);
    else if(bufferTCP == "GOALKICK CYAN")   tcpHeader(2, 2, 3);
    else if(bufferTCP == "THROWIN CYAN")    tcpHeader(2, 2, 4);
    else if(bufferTCP == "CORNER CYAN")     tcpHeader(2, 2, 5);
    else if(bufferTCP == "PENALTY CYAN")    tcpHeader(2, 2, 6);
    else if(bufferTCP == "GOAL CYAN")       tcpHeader(2, 2, 7);
    else if(bufferTCP == "REPAIR IN CYAN")  tcpHeader(2, 2, 8);
    else if(bufferTCP == "REPAIR OUT CYAN") tcpHeader(2, 2, 9);

    else if(bufferTCP == "KICKOFF MAGENTA")     tcpHeader(2, 3, 1);
    else if(bufferTCP == "FREEKICK MAGENTA")    tcpHeader(2, 3, 2);
    else if(bufferTCP == "GOALKICK MAGENTA")    tcpHeader(2, 3, 3);
    else if(bufferTCP == "THROWIN MAGENTA")     tcpHeader(2, 3, 4);
    else if(bufferTCP == "CORNER MAGENTA")      tcpHeader(2, 3, 5);
    else if(bufferTCP == "PENALTY MAGENTA")     tcpHeader(2, 3, 6);
    else if(bufferTCP == "GOAL MAGENTA")        tcpHeader(2, 3, 7);
    else if(bufferTCP == "REPAIR IN MAGENTA")   tcpHeader(2, 3, 8);
    else if(bufferTCP == "REPAIR OUT MAGENTA")  tcpHeader(2, 3, 9);

//    qDebug() << dataTCP1 << dataTCP2 << dataTCP3;

    emit TCPReady();
}

//----------------FUNGSI UDP----------------//

void MainWindow::updateUDPStatus(int a, int b, int c, int d, int e, int f, int g, int h)
{
//    qDebug() << QString::number(a) << QString::number(b) << QString::number(c);

    if(a == 30)
    {
        striker_2.coor_x[4] = b;
        striker_2.coor_y[4] = c;
        striker_2.dist_ball = d;
        striker_2.angle_ball = e;
        striker_2.x_ball[0] = f;
        striker_2.y_ball[0] = g;
        striker_2.yaw = h;
        ui->label_22->setText("GOOD");
    }
    if(a == 60)
    {
        striker_3.coor_x[4] = b;
        striker_3.coor_y[4] = c;
        striker_3.dist_ball = d;
        striker_3.angle_ball = e;
        striker_3.x_ball[0] = f;
        striker_3.y_ball[0] = g;
        striker_3.yaw = h;
        ui->label_7->setText("GOOD");
    }
    if(a == 90)
    {
        keeper.coor_x[4] = b;
        keeper.coor_y[4] = c;
        keeper.dist_ball = d;
        keeper.angle_ball = e;
        keeper.x_ball[0] = f;
        keeper.y_ball[0] = g;
        keeper.yaw = h;
        ui->label_55->setText("GOOD");
    }

    emit UDPReady();
}

//----------------FUNGSI LABEL----------------//

void MainWindow::updateUDPLabel()
{
    //----------------LABEL CRNT POS----------------//

    ui->label->setText(QString("%1, %2").arg(striker_3.coor_x[4]).arg(striker_3.coor_y[4]));
    ui->label_18->setText(QString("%1, %2").arg(striker_2.coor_x[4]).arg(striker_2.coor_y[4]));
    ui->label_51->setText(QString("%1, %2").arg(keeper.coor_x[4]).arg(keeper.coor_y[4]));

    //----------------LABEL RESET POS----------------//

    ui->label_2->setText(QString("%1, %2").arg(striker_3.coor_x[2]).arg(striker_3.coor_y[2]));
    ui->label_25->setText(QString("%1, %2").arg(striker_2.coor_x[2]).arg(striker_2.coor_y[2]));
    ui->label_58->setText(QString("%1, %2").arg(keeper.coor_x[2]).arg(keeper.coor_y[2]));

    //----------------LABEL YAW----------------//

    ui->label_3->setText(QString::number(striker_3.yaw));
    ui->label_27->setText(QString::number(striker_2.yaw));
    ui->label_60->setText(QString::number(keeper.yaw));

    //----------------LABEL R BALL----------------//

    ui->label_4->setText(QString::number(striker_3.dist_ball));
    ui->label_23->setText(QString::number(striker_2.dist_ball));
    ui->label_56->setText(QString::number(keeper.dist_ball));

    //----------------LABEL ANGLE BALL----------------//

    ui->label_5->setText(QString::number(striker_3.angle_ball));
    ui->label_19->setText(QString::number(striker_2.angle_ball));
    ui->label_52->setText(QString::number(keeper.angle_ball));

    //----------------LABEL X,Y BALL----------------//

    ui->label_6->setText(QString("%1, %2").arg(striker_3.x_ball[0]).arg(striker_3.y_ball[0]));
    ui->label_15->setText(QString("%1, %2").arg(striker_2.x_ball[0]).arg(striker_2.y_ball[0]));
    ui->label_48->setText(QString("%1, %2").arg(keeper.x_ball[0]).arg(keeper.y_ball[0]));

}

void MainWindow::updateTCPLabel()
{
    ui->label_refboxstatus->setText(QString::fromStdString(bufferTCP));

    QFont f( "Arial", 14, QFont::Bold);

    if(bufferTCP == "GOAL CYAN" || bufferTCP == "KICKOFF CYAN" || bufferTCP == "FREEKICK CYAN" || bufferTCP == "GOALKICK CYAN"
            || bufferTCP == "PENALTY CYAN" || bufferTCP == "CORNER CYAN" || bufferTCP == "THROWIN CYAN" || bufferTCP == "REPAIR IN CYAN"
            || bufferTCP == "REPAIR OUT CYAN")
    {
        ui->label_refboxstatus->setStyleSheet("background-color: rgb(114, 159, 207); color: rgb(255, 255, 255);");
        ui->label_refboxstatus->setFont(f);
    }
    else if(bufferTCP == "GOAL MAGENTA" || bufferTCP == "KICKOFF MAGENTA" || bufferTCP == "FREEKICK MAGENTA" || bufferTCP == "GOALKICK MAGENTA"
            || bufferTCP == "PENALTY MAGENTA" || bufferTCP == "CORNER MAGENTA" || bufferTCP == "THROWIN MAGENTA" || bufferTCP == "REPAIR IN MAGENTA"
            || bufferTCP == "REPAIR OUT MAGENTA")
    {
        ui->label_refboxstatus->setStyleSheet("background-color: rgb(117, 80, 123); color: rgb(255, 255, 255);");
        ui->label_refboxstatus->setFont(f);
    }
    else
    {
        ui->label_refboxstatus->setStyleSheet("background-color: rgb(138, 226, 52); color: rgb(255, 255, 255);");
        ui->label_refboxstatus->setFont(f);
    }
//    qDebug() << QString::fromStdString(bufferTCP);
}

void MainWindow::updateOdometryRobot()
{
    if(FIELD == KIRI)
    {
        if(TEAM == CYAN)
        {
            if(bufferTCP == "WELCOME" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(640,150,540,290,390,220);
            }
            else if(bufferTCP == "DROPPED BALL" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 4)
                    {
                        coordinate3(590,60,530,190,390,220);
                    }
                    else
                    {
                        coordinate3(590,390,530,260,390,220);
                    }
                }
                else
                {
                    if(markingMode == 4)
                    {
                        coordinate3(590,60,590,160,390,220);
                    }
                    else
                    {
                        coordinate3(590,290,590,390,390,220);
                    }
                }
            }
            else if(bufferTCP == "KICKOFF CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1)
                {
                    coordinate3(650,150,650,360,390,220);
                }
                else if(formationMode == 2)
                {
                    coordinate3(650,360,650,150,390,220);
                }
                else if(formationMode == 3)
                {
                    coordinate3(650,150,570,220,390,220);
                }
                else
                {
                    coordinate3(570,150,650,220,390,220);
                }
            }
            else if(bufferTCP == "FREEKICK CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 1)
                    {
                        coordinate3(480,50,590,50,390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(480,220,590,220,390,220);
                    }
                    else if(markingMode == 3)
                    {
                        coordinate3(480,390,590,390,390,220);
                    }
                    else if(markingMode == 4)
                    {
                        coordinate3(670,50,670,140,390,220);
                    }
                    else if(markingMode == 5)
                    {
                        coordinate3(670,220,670,310,390,220);
                    }
                    else if(markingMode == 6)
                    {
                        coordinate3(670,390,670,300,390,220);
                    }
                    else if(markingMode == 7)
                    {
                        coordinate3(860,50,620,50,390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(860,220,640,310,390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(860,390,620,390,390,220);
                    }
                    else
                    {
                        coordinate3(480,390,590,390,390,220);
                    }
                }
                else
                {
                    if(markingMode == 1)
                    {
                        coordinate3(480,50,570,130,390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(480,220,610,290,390,220);
                    }
                    else if(markingMode == 3)
                    {
                        coordinate3(480,390,610,290,390,220);
                    }
                    else if(markingMode == 4)
                    {
                        coordinate3(670,50,780,50,390,220);
                    }
                    else if(markingMode == 5)
                    {
                        coordinate3(670,220,780,220,390,220);
                    }
                    else if(markingMode == 6)
                    {
                        coordinate3(670,390,780,300,390,220);
                    }
                    else if(markingMode == 7)
                    {
                        coordinate3(860,50,620,50,390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(860,220,640,310,390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(860,390,620,300,390,220);
                    }
                    else
                    {
                        coordinate3(480,220,610,290,390,220);
                    }
                }
            }
            else if(bufferTCP == "CORNER CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 7)
                    {

                        coordinate3(970,10,880,40,390,220);
                    }
                    else
                    {
                        coordinate3(970,430,880,400,390,220);
                    }
                }
                else
                {
                    if(markingMode == 7)
                    {
                        coordinate3(970,10,820,120,390,220);
                    }
                    else
                    {
                        coordinate3(970,430,820,240,390,220);
                    }
                }
            }
            else if(bufferTCP == "GOAL CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(560,200,560,240,390,220);
            }
            else if(bufferTCP == "GOALKICK CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(450,190,520,190,390,220);
                }
                else
                {
                    coordinate3(450,250,520,250,390,220);
                }
            }
            else if(bufferTCP == "PENALTY CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {

                coordinate3(580,220,380,50,390,220);
            }
            else if(bufferTCP == "THROWIN CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(580,170,540,290,390,220);
            }
            else if(bufferTCP == "KICKOFF MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(560,240,560,190,390,220);
                }
                else
                {
                    coordinate3(580,190,540,240,390,220);
                }
            }
            else if(bufferTCP == "FREEKICK MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 7)
                    {
                        coordinate3(630,70,590,160,390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(580,190,550,250,390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(630,400,590,310,390,220);
                    }
                    else
                    {
                        coordinate3(580,190,550,250,390,220);
                    }
                }
                else
                {
                    if(markingMode == 7)
                    {
                        coordinate3(630,70,630,130,390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(580,250,580,190,390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(630,310,630,370,390,220);
                    }
                    else
                    {
                        coordinate3(580,250,580,190,390,220);
                    }
                }
            }
            else if(bufferTCP == "CORNER MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 1)
                    {
                        coordinate3(510,70,510,140,390,220);
                    }
                    else
                    {
                        coordinate3(510,390,510,320,390,220);
                    }
                }
                else
                {
                    if(markingMode == 1)
                    {
                        coordinate3(510,70,570,140,390,220);
                    }
                    else
                    {
                        coordinate3(510,390,570,320,390,220);
                    }
                }
            }
            else if(bufferTCP == "GOAL MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(550,200,550,240,390,220);
            }
            else if(bufferTCP == "GOALKICK MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(570,180,570,250,390,220);
                }
                else
                {
                    coordinate3(580,200,540,260,390,220);
                }
            }
            else if(bufferTCP == "PENALTY MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(400,40,400,80,390,220);
            }
            else if(bufferTCP == "THROWIN MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(550,200,550,240,390,220);
            }
        }
        else if (TEAM == MAGENTA)
        {
            if(bufferTCP == "WELCOME" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(640,150,540,290,390,220);
            }
            else if(bufferTCP == "DROPPED BALL" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 4)
                    {
                        coordinate3(590,60,530,190,390,220);
                    }
                    else
                    {
                        coordinate3(590,390,530,260,390,220);
                    }
                }
                else
                {
                    if(markingMode == 4)
                    {
                        coordinate3(590,60,590,160,390,220);
                    }
                    else
                    {
                        coordinate3(590,290,590,390,390,220);
                    }
                }
            }
            else if(bufferTCP == "KICKOFF MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1)
                {
                    coordinate3(650,150,650,360,390,220);
                }
                else if(formationMode == 2)
                {
                    coordinate3(650,360,650,150,390,220);
                }
                else if(formationMode == 3)
                {
                    coordinate3(650,150,570,220,390,220);
                }
                else
                {
                    coordinate3(570,150,650,220,390,220);
                }
            }
            else if(bufferTCP == "FREEKICK MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 1)
                    {
                        coordinate3(480,50,590,50,390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(480,220,590,220,390,220);
                    }
                    else if(markingMode == 3)
                    {
                        coordinate3(480,390,590,390,390,220);
                    }
                    else if(markingMode == 4)
                    {
                        coordinate3(670,50,670,140,390,220);
                    }
                    else if(markingMode == 5)
                    {
                        coordinate3(670,220,670,310,390,220);
                    }
                    else if(markingMode == 6)
                    {
                        coordinate3(670,390,670,300,390,220);
                    }
                    else if(markingMode == 7)
                    {
                        coordinate3(860,50,620,50,390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(860,220,640,310,390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(860,390,620,390,390,220);
                    }
                    else
                    {
                        coordinate3(480,390,590,390,390,220);
                    }
                }
                else
                {
                    if(markingMode == 1)
                    {
                        coordinate3(480,50,570,130,390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(480,220,610,290,390,220);
                    }
                    else if(markingMode == 3)
                    {
                        coordinate3(480,390,610,290,390,220);
                    }
                    else if(markingMode == 4)
                    {
                        coordinate3(670,50,780,50,390,220);
                    }
                    else if(markingMode == 5)
                    {
                        coordinate3(670,220,780,220,390,220);
                    }
                    else if(markingMode == 6)
                    {
                        coordinate3(670,390,780,300,390,220);
                    }
                    else if(markingMode == 7)
                    {
                        coordinate3(860,50,620,50,390,220);
                    }
                    else if(markingMode == 8)
                    {

                        coordinate3(860,220,640,310,390,220);
                    }
                    else
                    {
                        coordinate3(860,390,620,300,390,220);
                    }
                }
            }
            else if(bufferTCP == "CORNER MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 7)
                    {

                        coordinate3(970,10,880,40,390,220);
                    }
                    else
                    {
                        coordinate3(970,430,880,400,390,220);
                    }
                }
                else
                {
                    if(markingMode == 7)
                    {
                        coordinate3(970,10,820,120,390,220);
                    }
                    else
                    {
                        coordinate3(970,430,820,240,390,220);
                    }
                }
            }
            else if(bufferTCP == "GOAL MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(560,200,560,240,390,220);
            }
            else if(bufferTCP == "GOALKICK MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(450,190,520,190,390,220);
                }
                else
                {
                    coordinate3(450,250,520,250,390,220);
                }
            }
            else if(bufferTCP == "PENALTY MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {

                coordinate3(580,220,380,50,390,220);
            }
            else if(bufferTCP == "THROWIN MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(580,170,540,290,390,220);
            }
            else if(bufferTCP == "KICKOFF CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(560,240,560,190,390,220);
                }
                else
                {
                    coordinate3(580,190,540,240,390,220);
                }
            }
            else if(bufferTCP == "FREEKICK CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 7)
                    {
                        coordinate3(630,70,590,160,390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(580,190,550,250,390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(630,400,590,310,390,220);
                    }
                    else
                    {
                        coordinate3(580,190,550,250,390,220);
                    }
                }
                else
                {
                    if(markingMode == 7)
                    {
                        coordinate3(630,70,630,130,390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(580,250,580,190,390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(630,310,630,370,390,220);
                    }
                    else
                    {
                        coordinate3(580,250,580,190,390,220);
                    }
                }
            }
            else if(bufferTCP == "CORNER CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 1)
                    {
                        coordinate3(510,70,510,140,390,220);
                    }
                    else
                    {
                        coordinate3(510,390,510,320,390,220);
                    }
                }
                else
                {
                    if(markingMode == 1)
                    {
                        coordinate3(510,70,570,140,390,220);
                    }
                    else
                    {
                        coordinate3(510,390,570,320,390,220);
                    }
                }
            }
            else if(bufferTCP == "GOAL CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(550,200,550,240,390,220);
            }
            else if(bufferTCP == "GOALKICK CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(570,180,570,250,390,220);
                }
                else
                {
                    coordinate3(580,200,540,260,390,220);
                }
            }
            else if(bufferTCP == "PENALTY CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(400,40,400,80,390,220);
            }
            else if(bufferTCP == "THROWIN CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(550,200,550,240,390,220);
            }
        }
    }
    else
    {
        if (TEAM == CYAN)
        {
            if(bufferTCP == "WELCOME" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(-640+688+688,150,688+688-540,290,688+688-390,220);
            }
            else if(bufferTCP == "DROPPED BALL" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 4)
                    {
                        coordinate3(688+688-590,60,688+688-530,190,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-590,390,688+688-530,260,688+688-390,220);
                    }
                }
                else
                {
                    if(markingMode == 4)
                    {
                        coordinate3(688+688-590,60,688+688-590,160,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-590,290,688+688-590,390,688+688-390,220);
                    }
                }
            }
            else if(bufferTCP == "KICKOFF CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1)
                {
                    coordinate3(688-650+688,150,688-650+688,360,688-390+688,220);
                }
                else if(formationMode == 2)
                {
                    coordinate3(688-650+688,360,688-650+688,150,688-390+688,220);
                }
                else if(formationMode == 3)
                {
                    coordinate3(688-650+688,150,688-570+688,220,688-390+688,220);
                }
                else
                {
                    coordinate3(688+688-570,150,688+688-650,220,688+688-390,220);
                }
            }
            else if(bufferTCP == "FREEKICK CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 7)
                    {
                        coordinate3(688+688-480,50,688+688-590,50,688+688-390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(688+688-480,220,688+688-590,220,688+688-390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(688+688-480,390,688+688-590,390,688+688-390,220);
                    }
                    else if(markingMode == 4)
                    {
                        coordinate3(688+688-670,50,688+688-670,140,688+688-390,220);
                    }
                    else if(markingMode == 5)
                    {
                        coordinate3(688+688-670,220,688+688-670,310,688+688-390,220);
                    }
                    else if(markingMode == 6)
                    {
                        coordinate3(688+688-670,390,688+688-670,300,688+688-390,220);
                    }
                    else if(markingMode == 1)
                    {
                        coordinate3(688+688-860,50,688+688-620,50,688+688-390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(688+688-860,220,688+688-640,310,688+688-390,220);
                    }
                    else if(markingMode == 3)
                    {
                        coordinate3(688+688-860,390,688+688-620,390,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-860,220,688+688-640,310,688+688-390,220);
                    }

                }
                else
                {
                    if(markingMode == 7)
                    {
                        coordinate3(688+688-480,50,688+688-570,130,688+688-390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(688+688-480,220,688+688-610,220,688+688-390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(688+688-480,390,688+688-610,290,688+688-390,220);
                    }
                    else if(markingMode == 4)
                    {
                        coordinate3(688+688-670,50,688+688-780,50,688+688-390,220);
                    }
                    else if(markingMode == 5)
                    {
                        coordinate3(688+688-670,220,688+688-780,220,688+688-390,220);
                    }
                    else if(markingMode == 6)
                    {
                        coordinate3(688+688-670,390,688+688-780,390,688+688-390,220);
                    }
                    else if(markingMode == 1)
                    {
                        coordinate3(688+688-860,50,688+688-620,140,688+688-390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(688+688-860,220,688+688-640,310,688+688-390,220);
                    }
                    else if(markingMode == 3)
                    {
                        coordinate3(688+688-860,390,688+688-620,300,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-480,220,688+688-610,290,688+688-390,220);
                    }
                }
            }
            else if(bufferTCP == "CORNER CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 1)
                    {
                        coordinate3(688+688-970,10,688+688-880,40,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-970,430,688+688-880,400,688+688-390,220);
                    }
                }
                else
                {
                    if(markingMode == 1)
                    {
                        coordinate3(688+688-970,10,688+688-820,120,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-970,430,688+688-820,240,688+688-390,220);
                    }
                }
            }
            else if(bufferTCP == "GOAL CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-560,200,688+688-560,240,688+688-390,220);
            }
            else if(bufferTCP == "GOALKICK CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(688+688-450,190,688+688-520,190,688+688-390,220);
                }
                else
                {
                    coordinate3(688+688-450,250,688+688-520,250,688+688-390,220);
                }
            }
            else if(bufferTCP == "PENALTY CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-580,220,688+688-380,50,688+688-390,220);
            }
            else if(bufferTCP == "THROWIN CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-580,170,688+688-540,290,688+688-390,220);
            }
            else if(bufferTCP == "KICKOFF MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(688+688-560,240,688+688-560,190,688+688-390,220);
                }
                else
                {
                    coordinate3(688+688-580,190,688+688-540,240,688+688-390,220);
                }
            }
            else if(bufferTCP == "FREEKICK MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 1)
                    {
                        coordinate3(688+688-630,70,688+688-590,160,688+688-390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(688+688-580,190,688+688-550,250,688+688-390,220);
                    }
                    else if(markingMode == 3)
                    {
                        coordinate3(688+688-630,400,688+688-590,310,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-580,190,688+688-550,250,688+688-390,220);
                    }
                }
                else
                {
                    if(markingMode == 1)
                    {
                        coordinate3(688+688-630,70,688+688-630,130,688+688-390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(688+688-580,250,688+688-580,190,688+688-390,220);
                    }
                    else if(markingMode == 3)
                    {
                        coordinate3(688+688-630,310,688+688-630,370,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-580,250,688+688-580,190,688+688-390,220);
                    }
                }
            }
            else if(bufferTCP == "CORNER MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 7)
                    {
                        coordinate3(688+688-510,70,688+688-510,140,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-510,390,688+688-510,320,688+688-390,220);
                    }
                }
                else
                {
                    if(markingMode == 7)
                    {
                        coordinate3(688+688-510,70,688+688-570,140,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-510,390,688+688-570,320,688+688-390,220);
                    }
                }
            }
            else if(bufferTCP == "GOAL MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-550,200,688+688-550,240,688+688-390,220);
            }
            else if(bufferTCP == "GOALKICK MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(688+688-570,180,688+688-570,250,688+688-390,220);
                }
                else
                {
                    coordinate3(688+688-580,200,688+688-540,260,688+688-390,220);
                }
            }
            else if(bufferTCP == "PENALTY MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-400,40,688+688-400,80,688+688-390,220);
            }
            else if(bufferTCP == "THROWIN MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-550,200,688+688-550,240,688+688-390,220);
            }
        }
        else if (TEAM == MAGENTA)
        {
            if(bufferTCP == "WELCOME" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(-640+688+688,150,688+688-540,290,688+688-390,220);
            }
            else if(bufferTCP == "DROPPED BALL" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 4)
                    {
                        coordinate3(688+688-590,60,688+688-530,190,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-590,390,688+688-530,260,688+688-390,220);
                    }
                }
                else
                {
                    if(markingMode == 4)
                    {
                        coordinate3(688+688-590,60,688+688-590,160,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-590,290,688+688-590,390,688+688-390,220);
                    }
                }
            }
            else if(bufferTCP == "KICKOFF MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1)
                {
                    coordinate3(688-650+688,150,688-650+688,360,688-390+688,220);
                }
                else if(formationMode == 2)
                {
                    coordinate3(688-650+688,360,688-650+688,150,688-390+688,220);
                }
                else if(formationMode == 3)
                {
                    coordinate3(688-650+688,150,688-570+688,220,688-390+688,220);
                }
                else
                {
                    coordinate3(688+688-570,150,688+688-650,220,688+688-390,220);
                }
            }
            else if(bufferTCP == "FREEKICK MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 7)
                    {
                        coordinate3(688+688-480,50,688+688-590,50,688+688-390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(688+688-480,220,688+688-590,220,688+688-390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(688+688-480,390,688+688-590,390,688+688-390,220);
                    }
                    else if(markingMode == 4)
                    {
                        coordinate3(688+688-670,50,688+688-670,140,688+688-390,220);
                    }
                    else if(markingMode == 5)
                    {
                        coordinate3(688+688-670,220,688+688-670,310,688+688-390,220);
                    }
                    else if(markingMode == 6)
                    {
                        coordinate3(688+688-670,390,688+688-670,300,688+688-390,220);
                    }
                    else if(markingMode == 1)
                    {
                        coordinate3(688+688-860,50,688+688-620,50,688+688-390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(688+688-860,220,688+688-640,310,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-860,390,688+688-620,390,688+688-390,220);
                    }
                }
                else
                {
                    if(markingMode == 7)
                    {
                        coordinate3(688+688-480,50,688+688-570,130,688+688-390,220);
                    }
                    else if(markingMode == 8)
                    {
                        coordinate3(688+688-480,220,688+688-610,290,688+688-390,220);
                    }
                    else if(markingMode == 9)
                    {
                        coordinate3(688+688-480,390,688+688-570,310,688+688-390,220);
                    }
                    else if(markingMode == 4)
                    {
                        coordinate3(688+688-670,50,688+688-780,50,688+688-390,220);
                    }
                    else if(markingMode == 5)
                    {
                        coordinate3(688+688-670,220,688+688-780,220,688+688-390,220);
                    }
                    else if(markingMode == 6)
                    {
                        coordinate3(688+688-670,390,688+688-780,390,688+688-390,220);
                    }
                    else if(markingMode == 1)
                    {
                        coordinate3(688+688-860,50,688+688-620,50,688+688-390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(688+688-860,220,688+688-640,310,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-860,390,688+688-620,390,688+688-390,220);
                    }
                }
            }
            else if(bufferTCP == "CORNER MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 1)
                    {
                        coordinate3(688+688-970,10,688+688-880,40,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-970,430,688+688-880,400,688+688-390,220);
                    }
                }
                else
                {
                    if(markingMode == 1)
                    {
                        coordinate3(688+688-970,10,688+688-820,120,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-970,430,688+688-820,240,688+688-390,220);
                    }
                }
            }
            else if(bufferTCP == "GOAL MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-560,200,688+688-560,240,688+688-390,220);
            }
            else if(bufferTCP == "GOALKICK MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(688+688-450,190,688+688-520,190,688+688-390,220);
                }
                else
                {
                    coordinate3(688+688-450,250,688+688-520,250,688+688-390,220);
                }
            }
            else if(bufferTCP == "PENALTY MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-580,220,688+688-380,50,688+688-390,220);
            }
            else if(bufferTCP == "THROWIN MAGENTA" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-580,170,688+688-540,290,688+688-390,220);
            }
            else if(bufferTCP == "KICKOFF CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(688+688-560,240,688+688-560,190,688+688-390,220);
                }
                else
                {
                    coordinate3(688+688-580,190,688+688-540,240,688+688-390,220);
                }
            }
            else if(bufferTCP == "FREEKICK CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 1)
                    {
                        coordinate3(688+688-630,70,688+688-590,160,688+688-390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(688+688-580,190,688+688-550,250,688+688-390,220);
                    }
                    else if(markingMode == 3)
                    {
                        coordinate3(688+688-630,400,688+688-590,310,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-580,190,688+688-550,250,688+688-390,220);
                    }
                }
                else
                {
                    if(markingMode == 1)
                    {
                        coordinate3(688+688-630,70,688+688-630,130,688+688-390,220);
                    }
                    else if(markingMode == 2)
                    {
                        coordinate3(688+688-580,250,688+688-580,190,688+688-390,220);
                    }
                    else if(markingMode == 3)
                    {
                        coordinate3(688+688-630,310,688+688-630,370,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-580,250,688+688-580,190,688+688-390,220);
                    }
                }
            }
            else if(bufferTCP == "CORNER CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    if(markingMode == 7)
                    {
                        coordinate3(688+688-510,70,688+688-510,140,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-510,390,688+688-510,320,688+688-390,220);
                    }
                }
                else
                {
                    if(markingMode == 7)
                    {
                        coordinate3(688+688-510,70,688+688-570,140,688+688-390,220);
                    }
                    else
                    {
                        coordinate3(688+688-510,390,688+688-570,320,688+688-390,220);
                    }
                }
            }
            else if(bufferTCP == "GOAL CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-550,200,688+688-550,240,688+688-390,220);
            }
            else if(bufferTCP == "GOALKICK CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                if(formationMode == 1 || formationMode == 2)
                {
                    coordinate3(688+688-570,180,688+688-570,250,688+688-390,220);
                }
                else
                {
                    coordinate3(688+688-580,200,688+688-540,260,688+688-390,220);
                }
            }
            else if(bufferTCP == "PENALTY CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-400,40,688+688-400,80,688+688-390,220);
            }
            else if(bufferTCP == "THROWIN CYAN" && (flagResetGK == 0 && flagResetST2 == 0 && flagResetST3 == 0))
            {
                coordinate3(688+688-550,200,688+688-550,240,688+688-390,220);
            }
        }
    }

    if(bufferTCP == "START" || bufferTCP == "STOP")
    {
        striker_3.coor_x[2] = 350;
        striker_3.coor_y[2] = 330;
        striker_2.coor_x[2] = 350;
        striker_2.coor_y[2] = 370;
        keeper.coor_x[2] = 350;
        keeper.coor_y[2] = 410;
    }

    if(flagResetGK == 1)
    {
        keeper.coor_x[2] = keeper.coor_x[1];
        keeper.coor_y[2] = keeper.coor_y[1];
    }
    if(flagResetST2 == 1)
    {
        striker_2.coor_x[2] = striker_2.coor_x[1];
        striker_2.coor_y[2] = striker_2.coor_y[1];
    }
    if(flagResetST3 == 1)
    {
        striker_3.coor_x[2] = striker_3.coor_x[1];
        striker_3.coor_y[2] = striker_3.coor_y[1];
    }

    ui->label_45->setText(QString::number(flagResetST3));
    ui->label_46->setText(QString::number(flagResetST2));
    ui->label_47->setText(QString::number(flagResetGK));

    //-----------STRIKER3 POSITIONING----------//
    striker_3.coor_x[2] - 340 < 0   ? striker_3.coor_x[2] = 340     : striker_3.coor_x[2] = striker_3.coor_x[2];
    striker_3.coor_y[2] < 0         ? striker_3.coor_y[2] = 0       : striker_3.coor_y[2] = striker_3.coor_y[2];
    striker_3.coor_x[2] > 1036      ? striker_3.coor_y[2] = 1036    : striker_3.coor_y[2] = striker_3.coor_y[2];
    striker_3.coor_y[2] > 472       ? striker_3.coor_y[2] = 472     : striker_3.coor_y[2] = striker_3.coor_y[2];
    striker_3.coor_x[4] - 340 < 0   ? striker_3.coor_x[4] = 340     : striker_3.coor_x[4] = striker_3.coor_x[4];
    striker_3.coor_y[4] < 0         ? striker_3.coor_y[4] = 0       : striker_3.coor_y[4] = striker_3.coor_y[4];
    striker_3.coor_x[4] > 1036      ? striker_3.coor_y[4] = 1036    : striker_3.coor_y[4] = striker_3.coor_y[4];
    striker_3.coor_y[4] > 472       ? striker_3.coor_y[4] = 472     : striker_3.coor_y[4] = striker_3.coor_y[4];

    //-----------STRIKER2 POSITIONING----------//
    striker_2.coor_x[2] - 340 < 0   ? striker_2.coor_x[2] = 340     : striker_2.coor_x[2] = striker_2.coor_x[2];
    striker_2.coor_y[2] < 0         ? striker_2.coor_y[2] = 0       : striker_2.coor_y[2] = striker_2.coor_y[2];
    striker_2.coor_x[2] > 1036      ? striker_2.coor_y[2] = 1036    : striker_2.coor_y[2] = striker_2.coor_y[2];
    striker_2.coor_y[2] > 472       ? striker_2.coor_y[2] = 472     : striker_2.coor_y[2] = striker_2.coor_y[2];
    striker_2.coor_x[4] - 340 < 0   ? striker_2.coor_x[4] = 340     : striker_2.coor_x[4] = striker_2.coor_x[4];
    striker_2.coor_y[4] < 0         ? striker_2.coor_y[4] = 0       : striker_2.coor_y[4] = striker_2.coor_y[4];
    striker_2.coor_x[4] > 1036      ? striker_2.coor_y[4] = 1036    : striker_2.coor_y[4] = striker_2.coor_y[4];
    striker_2.coor_y[4] > 472       ? striker_2.coor_y[4] = 472     : striker_2.coor_y[4] = striker_2.coor_y[4];

    //-----------KEEPER POSITIONING----------//
    keeper.coor_x[2] - 340 < 0      ? keeper.coor_x[2] = 340        : keeper.coor_x[2] = keeper.coor_x[2];
    keeper.coor_y[2] < 0            ? keeper.coor_y[2] = 0          : keeper.coor_y[2] = keeper.coor_y[2];
    keeper.coor_x[2] > 1036         ? keeper.coor_y[2] = 1036       : keeper.coor_y[2] = keeper.coor_y[2];
    keeper.coor_y[2] > 472          ? keeper.coor_y[2] = 472        : keeper.coor_y[2] = keeper.coor_y[2];
    keeper.coor_x[4] - 340 < 0      ? keeper.coor_x[4] = 340        : keeper.coor_x[4] = keeper.coor_x[4];
    keeper.coor_y[4] < 0            ? keeper.coor_y[4] = 0          : keeper.coor_y[4] = keeper.coor_y[4];
    keeper.coor_x[4] > 1036         ? keeper.coor_y[4] = 1036       : keeper.coor_y[4] = keeper.coor_y[4];
    keeper.coor_y[4] > 472          ? keeper.coor_y[4] = 472        : keeper.coor_y[4] = keeper.coor_y[4];

    coordinate(striker_3.coor_x[4],striker_3.coor_y[4],striker_2.coor_x[4],striker_2.coor_y[4],keeper.coor_x[4],keeper.coor_y[4]);
    coordinate2(striker_3.coor_x[2],striker_3.coor_y[2],striker_2.coor_x[2],striker_2.coor_y[2],keeper.coor_x[2],keeper.coor_y[2]);

//    rotateRobot(keeper.yaw);

    if(bufferTCPtemp != bufferTCP)
    {
        flagResetGK = 0;
        flagResetST2 = 0;
        flagResetST3 = 0;
        bufferTCPtemp = bufferTCP;
    }

    emit UDPSendReady(striker_3.coor_x[2],striker_3.coor_y[2],striker_2.coor_x[2],striker_2.coor_y[2],keeper.coor_x[2],keeper.coor_y[2],
            striker_3.coor_x[4],striker_3.coor_y[4],striker_2.coor_x[4],striker_2.coor_y[4],keeper.coor_x[4],keeper.coor_y[4],striker_3.yaw,
            striker_2.yaw,keeper.yaw,FIELD,TEAM,formationMode,markingMode,dataTCP1,dataTCP2,dataTCP3);

    qDebug() << dataTCP1 << dataTCP2 << dataTCP3;
}

void MainWindow::updateTeamAndField()
{
    QString team;
    QString field;
    team = ui->comboBox_team->currentText();
    field = ui->comboBox_field->currentText();

    if(team == "CYAN")
    {
        TEAM = CYAN;
        ui->label_teamstatus->setStyleSheet("background-color: rgb(52, 101, 164);");
        ui->label_enspartan->setStyleSheet("background-color: rgb(52, 101, 164);");
        ui->label_opponent->setStyleSheet("background-color: rgb(117, 80, 123);");
        ui->label_score_enspartan->setStyleSheet("color: rgb(52, 101, 164);");
        ui->label_score_opponent->setStyleSheet("color: rgb(117, 80, 123);");
    }
    else
    {
        TEAM = MAGENTA;
        ui->label_teamstatus->setStyleSheet("background-color: rgb(117, 80, 123);");
        ui->label_enspartan->setStyleSheet("background-color: rgb(117, 80, 123);");
        ui->label_opponent->setStyleSheet("background-color: rgb(52, 101, 164);");
        ui->label_score_enspartan->setStyleSheet("color: rgb(117, 80, 123);");
        ui->label_score_opponent->setStyleSheet("color: rgb(52, 101, 164);");
    }

    if(field == "KIRI") FIELD = KIRI;
    else FIELD = KANAN;

    ui->label_teamstatus->setText(team);
    ui->label_fieldstatus->setText(field);
    emit TeamFieldReady();
}

void MainWindow::updateScore()
{
    if((bufferTCP == "GOAL CYAN" && TEAM == CYAN) || (bufferTCP == "GOAL MAGENTA" && TEAM == MAGENTA))
    {
        scoreUS += 1;
        ui->label_score_enspartan->setText(QString::number(scoreUS));
    }
    else if((bufferTCP == "GOAL CYAN" && TEAM == MAGENTA) || (bufferTCP == "GOAL MAGENTA" && TEAM == CYAN))
    {
        scoreOPP += 1;
        ui->label_score_opponent->setText(QString::number(scoreOPP));
    }
}
