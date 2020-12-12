#include "mainwindow.h"
#include "ui_mainwindow.h"

class Customer{
public:

QString name;
QString surname;
QString phone;
QDate from_date;
QDate to_date;
int DaysOfLiving;
QString Adress;
int PassportID;

};

class Hotel{

    QDate StartDate;
    QDate EndDate;
    int controlCorrectStartDay = 0;
    int controlCorrectEndDay = 0;

public:

    void GetStartDayOfVisiting(QDate checkin){
        controlCorrectStartDay = 0;

        StartDate = checkin;
//        if(checkin.isNull() != NULL){
//            return 25;
//        }else{
//            controlCorrectStartDay = 1;
//        }

    }
    void  GetEndDayOfVisiting(QDate checkout){
        controlCorrectEndDay = 0;

        EndDate = checkout;

//        if(checkout.isNull() != NULL){
//            return 25;
//        }else{
//            controlCorrectEndDay = 1;
//        }

    }

    bool ControllSuccess(){
        if(controlCorrectStartDay == 1 && controlCorrectEndDay == 1){
            return true;
        }else{
            return false;
        }
    }
    QDate SetDateStart(){
        return StartDate;
    }
    QDate SetDateEnd(){
        return EndDate;
    }

//    QString FindAvailablePlaceForDates(){

//        QDate Start = SetDateStart();
//        QDate End = SetDateEnd();

//        int check = 0;

//        for(int i = 0;i<15;i++){

//        }

//    }

    int GetLongBetweenDays(){
        int longdaysbetween = 0;
//correct initialize

        int Start = StartDate.day();
        int End = EndDate.day();

        longdaysbetween = End - Start;
        return longdaysbetween;
    }

   virtual void RoomInfo() = 0;

   Hotel(){}
   virtual ~Hotel(){};

};

//Hotel HotelVariable;



class StandartRoom:public Hotel{

private:
//variable of class\\\\\\\\\\\\\\\\\
//   class Customer standartCustomer;

    QDate DateCur;

    struct Booking{
        bool isFree;
        QDate AllDays;
        class Customer standartCustomer;
    };
    struct Booking Bookings[180];

  //  };

    int roomcount;
    int seatsnumber; //count of places in room
    int windowscount;
    int roomarea;
    float DailyCost;
    QString HouseholdAppliances;
  // typedef struct HotelGuest HotelGuestStandart[15];


    int AvailableStandartRoom = -1;
    int Maximal;
    int SavedI;
    QString NameSave;
    QString SurnameSave;
    QString PhoneSave;
    QString AdressSave;
    int PassportIDsave;
public:


     StandartRoom(){
         QDate DayVariable;
     QDate DayCur = DayVariable.currentDate();

         for(int i = 0;i<180;i++){
           Bookings[i].AllDays = DayCur.addDays(i);
            Bookings[i].isFree = true;
         }

         //did 12 12 2020 unavailable
         //UnAvailableDayCreate();

//date of class give

         Bookings[25].standartCustomer.name = "Anton";
          Bookings[25].standartCustomer.surname = "Antonovych";
         Bookings[25].standartCustomer.phone = "0986155669";
         bool check;
       check = Bookings[25].standartCustomer.from_date.setDate(2020,12,15);
         check = Bookings[25].standartCustomer.to_date.setDate(2020,12,16);
         Bookings[25].standartCustomer.PassportID = 2013;
         Bookings[25].standartCustomer.Adress = "Lviv Region,street Ivasuka";
         Bookings[25].standartCustomer.DaysOfLiving = (Bookings[25].standartCustomer.to_date.day())-(Bookings[25].standartCustomer.from_date.day());
     }

     void StartInitialize(){
//         QDate DayVariable;
//     QDate DayCur = DayVariable.currentDate();

//         for(int i = 0;i<180;i++){
//           Bookings[i].AllDays = DayCur.addDays(i);
//            Bookings[i].isFree = true;
//         }

         StandartRoom();
         UnAvailableDayCreate();

     }

     void NewCustomer(QString GetName,QString GetSurname,QString GetPhoneNumber,QString GetAdress,int GetPassportID){
      NameSave = GetName;
      SurnameSave =GetSurname;
      PhoneSave = GetPhoneNumber;
      AdressSave = GetAdress;
      PassportIDsave = GetPassportID;
     }
     void CustomerInitialize(int structNum){
         Bookings[structNum].standartCustomer.name = NameSave;
          Bookings[structNum].standartCustomer.surname = SurnameSave;
         Bookings[structNum].standartCustomer.phone = PhoneSave;
         bool check;

         //
       Bookings[structNum].standartCustomer.from_date=SetDateStart();
       Bookings[structNum].standartCustomer.to_date=SetDateEnd();

         //
         Bookings[structNum].standartCustomer.PassportID = PassportIDsave;
         Bookings[structNum].standartCustomer.Adress = AdressSave;
         Bookings[structNum].standartCustomer.DaysOfLiving = (Bookings[structNum].standartCustomer.to_date.day())-(Bookings[structNum].standartCustomer.from_date.day());

         //prikol

     }

     void UnAvailableDayCreate(){

         QDate date;
         bool check;
           check = date.setDate(2020,12,20);
         for(int i = 0;i<180;i++){
         if(Bookings[i].AllDays == date){
               if(Bookings[i].isFree){
                   Bookings[i].isFree = false;
               }

         }
  }
}
     void CalculateDaysOfLiving(){




         for(int i = 0;i<180;i++){


         QDate dayStart,dayEnd;

         dayStart = Bookings[i].standartCustomer.from_date;
         dayEnd = Bookings[i].standartCustomer.to_date;

//         int year1,year2;
//         year1 = dayStart.year();
//         year2 = dayEnd.year();
//         int month1,month2;
//         month1 = dayStart.month();
//         month2 = dayEnd.month();
//         int day1,day2;
//         day1 = dayStart.day();
//         day2 = dayEnd.day();

//         if(year2-year1 != 0){
//          month2 += (year2-year1)*12;
//         }
//         int monthCount;
//        monthCount = month2 - month1;

//         int daysCount = (monthCount * 30 + day2) - day1;
         int daysCount;

         daysCount =  dayStart.daysTo(dayEnd);

                 //day2-day1;

         Bookings[i].standartCustomer.DaysOfLiving = daysCount;

         }
         //Bookings[179].standartCustomer.DaysOfLiving = 15;

     }

     void LongestLivingDays(){
         int max = 0;
         int saveI = 0;
         for(int i = 0;i<180;i++){

          if(Bookings[i].standartCustomer.DaysOfLiving>max){
          max = Bookings[i].standartCustomer.DaysOfLiving;
          saveI = i;
          Maximal = max;
          SavedI = saveI;
          }

         }



     }

     int GetCurrentMaxDaysOfLiving(){
         return Maximal;
     }
     int GetCurrentSavedIPos(){
         return SavedI;
     }


     QString LookedForCustomerInfo(int saveI){
         QString Info;
         QString FromDate,ToDate,LivesDays,Passportid;
         //from date ?to date ?daysoflivind ?adress?passport ID
         Info = "Name is " + Bookings[saveI].standartCustomer.name +"\n" + "Surname is " + Bookings[saveI].standartCustomer.surname + "\n"+
                 + "Phone number is " + Bookings[saveI].standartCustomer.phone + "\n"+ "From Date is " + Bookings[saveI].standartCustomer.from_date.toString() + "\n"+
                 + "To Date is " + Bookings[saveI].standartCustomer.to_date.toString() + "\n"+ "Days of living is " + LivesDays.setNum(Bookings[saveI].standartCustomer.DaysOfLiving) + "\n" +
                 +"Customer passport id is " + Passportid.setNum(Bookings[saveI].standartCustomer.PassportID) + "\n";

         return Info;
     }



     void GetRoom(int num){

         //function for saving our free room number
       // int availableRoomNumber = num;
        // there must be function which get availableRoomNumber or this func with return int value and i will check its correctly in main func
            AvailableStandartRoom = num;
        //return availableRoomNumber;

     }

     int SetRoom(){
         return AvailableStandartRoom;
     }


     void BookStandartRoom(QDate Start,QDate End){

         //
         //CalculateDaysOfLiving();
         int check = 0;
         int saveI;
         //QDate DayEnd = SetDateEnd();
         //QDate DateStart = SetDateStart();
         for(int i = 0;i<180;i++){
         if(Bookings[i].AllDays == Start){

           for(int s = i;End!=Start;s++){

             Bookings[s].isFree = false;
             CustomerInitialize(i);
            Start = Start.addDays(1);
           }
             //}
         }

           //  while(Bookings[i].AllDays.addDays(s+1) != SetDateEnd().addDays(-1)){
//                 if(Bookings[i].isFree){
//                  Bookings[i].isFree = false;
//                  CustomerInitialize(i);
//                   saveI = i;
//                  }else{
//                     check++;
//                 }

             //}
           //  while(check !=1){

//             if(Bookings[i].isFree){

//               }

     }

 }

         //move between days and add customer for this days




   bool FindPlaceForDay(QDate Start,QDate End){
        //QDate Day = SetDateStart();



//       int countDays;
//       //QDate start = SetDateStart();
//       //QDate end = SetDateEnd();
//       int month1,month2;
//       month2 = end.month();
//       if(end.year() - start.year()!=0){
//       month2 += 12*(end.year()-start.year());
//       }
//       month1 = start.month();
//       int countmonth = month2 -month1;
//       countDays  = (countmonth*30+end.day()) - start.day();



//       int counting = 0;
//       int FalseVariable = 0;
//       for(int i = 0;i<180;i++){
//       if(Bookings[i].AllDays == SetDateStart()){

//         for(int s = i;DayEnd!=DateStart;s++){

//           Bookings[s].isFree = false;
//           CustomerInitialize(i);
//          DateStart = DateStart.addDays(1);
//         }
//           //}
//       }
       // countDays = SetDateEnd()-SetDateStart();
       int check = 0;
       //QDate DayEnd = SetDateEnd();
       //QDate DayStart = SetDateStart();
         for(int i = 0;i<180;i++){
          //add for few days cycle
         if(Bookings[i].AllDays == Start){
             for(int s = i;End!=Start;s++){

               if(Bookings[s].isFree){
                 check = 1;
               }else{
                   return false;
               }
               Start = Start.addDays(1);
         }
             return true;
            //Standart[0].
    }

         }
        // return false;
//         if(counting == countDays){
//          return true;
//         }else if(FalseVariable == 1){
//         return false;
//         }




     }


     QString FuncInfoStruct(){



QString str2;
         QString str;
           for(int i = 0;i<180;i++){

              QString boolText = Bookings[i].isFree? "true" : "false";
              str+=  Bookings[i].AllDays.toString("dd.MM.yyyy")+" " + boolText + " \n";
           }

         //  str+=str2.setNum(DailyCost);

           return str;
     }
//      void InitializeDays(Booking Bookingzz){


//  //        for(int i = 0;i<180;i++){
//             Bookingzz.AllDays = DateCur.addDays(0);
//  //        }

//      }






    virtual void RoomInfo(){
        roomcount = 2;
        seatsnumber =2;
        windowscount = 1;
        roomarea = 25.0;
        DailyCost = 500;
        HouseholdAppliances = "something";
    }
     QString GetRoomInfo(){
         QString RoomsC,RoomsS,RoomsW,RoomsR,RoomsD;

         QString Info = "StandartRoom info:\nRoom count equal " + RoomsC.setNum(roomcount)+"\n " + "Seats number equal " + RoomsS.setNum(seatsnumber)+"\n " +
                 + "Windows count equal " + RoomsW.setNum(windowscount)+"\n " + "Room area is " + RoomsR.setNum(roomarea) + " square meters"+"\n " +
                 + "Daily Cost is  " + RoomsD.setNum(DailyCost)+"\n " + "HouseHoldAppliances are " + HouseholdAppliances +"\n ";

         return Info;
     }


     //in class customerInfo
     QString CustomerInfo(){
         QString Info;
         QString FromDate,ToDate,LivesDays,Passportid;
         //from date ?to date ?daysoflivind ?adress?passport ID
         Info = "Name is " + Bookings[0].standartCustomer.name +"\n" + "Surname is " + Bookings[0].standartCustomer.surname + "\n"+
                 + "Phone number is " + Bookings[0].standartCustomer.phone + "\n"+ "From Date is " + Bookings[0].standartCustomer.from_date.toString() + "\n"+
                 + "To Date is " + Bookings[0].standartCustomer.to_date.toString() + "\n"+ "Days of living is " + LivesDays.setNum(Bookings[0].standartCustomer.DaysOfLiving) + "\n" +
                 +"Customer passport id is " + Passportid.setNum(Bookings[0].standartCustomer.PassportID) + "\n";

         return Info;
     }


};

class DeluxeRoom: public Hotel{
private:

   // struct HotelGuest{

   //  };

  //   typedef struct HotelGuest HotelGuestDeluxe[5];
    int roomcount;
    int seatsnumber; //count of places in room
    int windowscount;
    float roomarea;
    float DailyCost;
    QString HouseholdAppliances;

    //add special opportunities

public:

    //function quest info
    //function room features





//  virtual void FuncPassportID(int id){

//        PassportID = id;

//    }

// virtual void RoomInfo();



     virtual void RoomInfo(){
         roomcount = 2;
         seatsnumber =2;
         windowscount = 1;
         roomarea = 25;
         DailyCost = 500;
         HouseholdAppliances = "";
         //special opportunities
     }

    DeluxeRoom(){};
    virtual ~DeluxeRoom(){};
};


StandartRoom Standart[15];
DeluxeRoom Deluxe[5];

class Main{

  public:

    QString ALLinfo(){
         QString Info;
        for(int i = 0;i<15;i++){
            QString iNum;

        Info  +="Standart room number "+ iNum.setNum(i+1) + ":\n " + Standart[i].FuncInfoStruct()+"\n\n\n\n _____";


        }
        return Info;
    }



    QString FindPlace(){

        QString Find;
        QString PutNumber;
        QDate startDay = Standart->SetDateStart();
        QDate endDay = Standart->SetDateEnd();
        for(int i = 0;i<15;i++){



            if(Standart[i].FindPlaceForDay(startDay,endDay) == true){
                Find = "We have available standart room,it's number is "+PutNumber.setNum(i+1) + "\n"+FindRes(1);
                Standart->GetRoom(i);
                return Find;
            }

//           if(Standart[i].NumberOfRoom() > 0){

//            // доступитись до класу  StandartRoom там знайти відповідно за вказаною датою місце й повернути сюди номер вільної кімнати(першої знайденої)
//        }

    }

            //availables dates for customer visiting add,if his day of visiting is unavailable
            Find = "We have not available standart rooms,maybe such date as (propose for customer about available days of visiting)\n"+FindRes(0);
            Standart->GetRoom(-1);
  //add function which will get result of this work and will printf room info or not
        return Find;
}
    QString FindRes(int res){

        if(res == 1){
       QString Information = Standart->GetRoomInfo();
        return Information;
        }
        else {
             QString Information = "";
             return Information;
        }
    }


    QString FindTheLongestLivingCustomer(){

        QString resultCustomer;
//        for(int i = 0;i<15;i++){
//        Standart[i].CalculateDaysOfLiving();
//        }

        int curMax=0;
        int curSavedI=0;
        int SaveRoomNum=0;
        for(int i = 0;i<15;i++){
         Standart[i].CalculateDaysOfLiving();
         Standart[i].LongestLivingDays();
         int SaveMax;
         int SaveI;
         if(i==0){
           curMax = Standart[i].GetCurrentMaxDaysOfLiving();
           curSavedI = Standart[i].GetCurrentSavedIPos();
           SaveRoomNum = i;
         }
         SaveMax = Standart[i].GetCurrentMaxDaysOfLiving();
         SaveI = Standart[i].GetCurrentSavedIPos();
         if(curMax<SaveMax){
         curMax = SaveMax;
         curSavedI = SaveI;
         SaveRoomNum = i;
         }


        }

        resultCustomer = Standart[SaveRoomNum].LookedForCustomerInfo(curSavedI);
        //function which get (curSavedI) ,SaveRoomNum call it and return QString Customer info

        //відповідно до кімнати ,та відповідно до позиції в структурі
        //доступаємось до чела та виводимо його кількість днів жизні в готелі


       return resultCustomer;
    }

//    void BookStandartRoom(int room){

//        //
//        CalculateDaysOfLiving();
//        int check = 0;
//        int saveI;
//        QDate DayEnd = SetDateEnd();
//        QDate DateStart = SetDateStart();
//        for(int i = 0;i<180;i++){
//        if(Bookings[i].AllDays == SetDateStart()){

//          for(int s = i;DayEnd!=DateStart;s++){

//            Standart[room].Bookings[s].isFree = false;
//            Standart[room].CustomerInitialize(i);
//           DateStart = DateStart.addDays(1);
//          }
//            //}
//        }


//    }

//}


};



Main MainVariable;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i = 0;i<15;i++){
        Standart[i].RoomInfo();
        Standart[i].StartInitialize();

    }
//    for(int j = 0;j<15;j++){
//        Deluxe[j]

//    }

//    QCalendarWidget *calendarWidget;
//    calendarWidget->setGridVisible(true);

//   QDate day =  calendarWidget->minimumDate();
//    QString str1;

//    ui->label_DateSub->setText(day.toString());




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    ui->label_StartDay->setText("Start date " + date.toString("dd.MM.yyyy"));
    Standart->GetStartDayOfVisiting(date);

    //incorrect check of correctrly (
    int errorcode;
    //errorcode = Standart->GetStartDayOfVisiting(date);
    if(errorcode == 25){
         ui->label_StartDay->setText("Start date incorrect.");
    }
    // end of this incorrect check

    //Add message box signal which will be say to user that end date should be biggest than start

}

void MainWindow::on_calendarWidget_2_clicked(const QDate &date2)
{

    ui->label_EndDay->setText("End date "+ date2.toString("dd.MM.yyyy"));
    Standart->GetEndDayOfVisiting(date2);

    //incorrect check of correctrly (
    int errorcode;
  //  errorcode = Standart->GetEndDayOfVisiting(date2);
    if(errorcode == 25){
        ui->label_EndDay->setText("End date incorrect.");
    }
    // end of this incorrect check



    //Add message box signal which will be check (if end date biggest than start) if not say about error and ask to choose another date

}

void MainWindow::on_pushButton_clicked()
{
//    if(Standart->ControllSuccess()!=true){

//        ui->label_DateSub->setText("Look like,we have'nt get input date(( ");
//    }else{



//    QDate StartDate = Standart->SetDateStart();
//    QDate EndDate = Standart->SetDateEnd();

//     ui->label->setText("Start date " + StartDate.toString("dd.MM.yyyy"));
//      ui->label_2->setText("End date "+ EndDate.toString("dd.MM.yyyy"));

//      //int longbetweenvisitingDays = HotelVariable.GetLongBetweenDays();

//      QString strDays;
//      ui->label_DateSub->setText("Longs is " + strDays.setNum(Standart->GetLongBetweenDays()) + "");
//    }


    //array all dates between current and end
    QDate dateCur,dateEnd,dateD;


    dateCur = dateD.currentDate();
   int CountOfDays = 180;

  dateEnd =dateCur.addDays(CountOfDays);


  //generation days in array

  QDate AllDays[CountOfDays];


  for(int i = 0;i<CountOfDays;i++){
   AllDays[i] = dateCur.addDays(i);
  }

QString str;

  for(int i = 0;i<CountOfDays;i++){
     str+=  AllDays[i].toString("dd.MM.yyyy")+" \n";
  }

 // QString returnedStr = Standart[14].FuncInfoStruct();

 //ui->textEdit->setText(MainVariable.ALLinfo()+'\n');



 // find place for input date (now 1 date)


 ui->textEdit ->setText(MainVariable.FindPlace());





//  for(int i = 0;i<count;i++){
//  ui->textEdit->setText(string[i]);
//  }
    QString strDays;
  ui->label_DateSub->setText("Day is  " +dateCur.toString("dd.MM.yyyy") + " " + dateEnd.toString("dd.MM.yyyy")+"");
// ui->label_2->setText("Day is  " +dateEnd.toString("dd.MM.yyyy") + "");


}



void MainWindow::on_pushButton_Find_Customer_clicked()
{
    QString GetInfo = Standart->CustomerInfo();
    ui->textEdit->setText(GetInfo);

}



void MainWindow::on_pushButton_Book_clicked()
{
    QString Name = ui ->lineEdit_name->text();
      //int Nnumber = atoi(Nfind.toStdString().c_str());
    QString Surname = ui ->lineEdit_surname->text();
    QString Phone = ui ->lineEdit_phone->text();
    QString Adress = ui ->lineEdit_Adress->text();
    QString PassportIDGet = ui ->lineEdit_PassportID->text();
      int PassportID = atoi(PassportIDGet.toStdString().c_str());
      Standart->NewCustomer(Name,Surname,Phone,Adress,PassportID);
    //getnewcustomerdate

      for(int i = 0;i<15;i++){
       Standart[i].CalculateDaysOfLiving();
      }
    int RoomNum = Standart->SetRoom();
QString Room;
QDate Start = Standart->SetDateStart();
QDate End = Standart->SetDateEnd();
   // int RoomNum = 0;
    if(RoomNum == -1){
        ui->textEdit->setText("there aren't rooms for your dates sorry.");}
     else{

        //for(int i = 0; i<2;i++){
           Standart[RoomNum].BookStandartRoom(Start,End);
           ui->textEdit->setText(MainVariable.ALLinfo()+"\n\n\n"+ Room.setNum(RoomNum + 1)+"\n");

        }

}



void MainWindow::on_pushButton_LiveLongest_clicked()
{

    //FindTheLongestLivingCustomer call to this func
    //call with one of number
    QString LongestCustomer;
   LongestCustomer =  MainVariable.FindTheLongestLivingCustomer();
    ui->textEdit->setText(LongestCustomer);



}
