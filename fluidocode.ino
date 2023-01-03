

#include "Nextion.h"
#include <Wire.h>
#include <ds3231.h>
 
struct ts t; 




const int role2 = 7;    ////  SERPANTİN
const int kohm120 = 5;
const int kohm150 = 12;
const int kohm180 = 11;
const int kohm220 = 10;


//***************************************************
//burada sıcaklık verisini okumak için kod kısmı
#include <OneWire.h> 

#include <DallasTemperature.h> 

OneWire oneWire(2);

DallasTemperature DS18B20(&oneWire);

DeviceAddress DS18B20adres;

int santigrat;
//*************************************************
//const int led1 = 8;
void kirksekizkohmlukhiz()
{
  digitalWrite(kohm120,LOW);
  digitalWrite(kohm150,LOW);
  digitalWrite(kohm180,LOW);
  digitalWrite(kohm220,HIGH);
}// 48kohm direnç elde ettik
void ellidokuzkohmlukhiz()
{
  digitalWrite(kohm120,HIGH);
  digitalWrite(kohm150,LOW);
  digitalWrite(kohm180,LOW);
  digitalWrite(kohm220,LOW);
} // 59kohm direnç elde ettik
void yetmisikikohmlukhiz()
{
  digitalWrite(kohm120,LOW);
  digitalWrite(kohm150,HIGH);
  digitalWrite(kohm180,LOW);
  digitalWrite(kohm220,HIGH); 
}  // 72kohm direnç elde ettik
void seksenikikohmlukhiz()
{
  digitalWrite(kohm120,HIGH);
  digitalWrite(kohm150,LOW);
  digitalWrite(kohm180,LOW);
  digitalWrite(kohm220,HIGH);
}       // 82kohm direnç elde ettik
void doksandokuzkohmlukhiz()
{
  digitalWrite(kohm120,HIGH);
  digitalWrite(kohm150,HIGH);
  digitalWrite(kohm180,LOW);
  digitalWrite(kohm220,LOW);
} // 99kohm direnç elde ettik
void yuzyirmikohmlukhiz()
{
  digitalWrite(kohm120,LOW);
  digitalWrite(kohm150,HIGH);
  digitalWrite(kohm180,HIGH);
  digitalWrite(kohm220,HIGH); 
}      // 120kohm direnç elde ettik
void yuzellikohmlukhiz()
{
  digitalWrite(kohm120,HIGH);
  digitalWrite(kohm150,LOW);
  digitalWrite(kohm180,HIGH);
  digitalWrite(kohm220,HIGH); 
}  
// 150kohm direnç elde ettik
void yuzseksenkohmlukhiz()
{
  digitalWrite(kohm120,HIGH);
  digitalWrite(kohm150,HIGH);
  digitalWrite(kohm180,LOW);
  digitalWrite(kohm220,HIGH);
} // 180kohm direnç elde ettik
void motordurdurma()
{ 
   digitalWrite(kohm120,HIGH);
   digitalWrite(kohm150,HIGH);
   digitalWrite(kohm180,HIGH);
   digitalWrite(kohm220,HIGH);  
        
}
void ikiyuzyirmikohmlukhiz()
 {
   digitalWrite(kohm120,HIGH);
   digitalWrite(kohm150,HIGH);
   digitalWrite(kohm180,HIGH);
   digitalWrite(kohm220,LOW);  
 }
void n4PopCallback(void *ptr);



NexTimer tm0 = NexTimer(0, 4, "tm0");

char buffer[100] = {0};
uint32_t number_timer = 0;
uint32_t number_enable = 0;
uint32_t number_cycle = 100;

NexText t0 = NexText(0, 2, "t0");    // filte değişimi yazdırma yeri
NexText t1 = NexText(0, 3, "t1");    // çalıştırabilirsiniz yazısı için 
 
NexButton b0 = NexButton(0, 1, "b0");  // ilk sayfadaki ileri sayfa butonu
NexButton b2 = NexButton(1, 2, "b2");  // aşağı azaltma butonunun tanımlanamsı
NexButton b3 = NexButton(1, 3, "b3");  // yukarı arttırma butonunun tanımlanması


NexNumber n0 = NexNumber(1, 1, "n0");  // istenilen tedavi süresi
NexNumber n1 = NexNumber(1, 6, "n1");   // istenilen sıcaklık 
NexNumber n2 = NexNumber(1, 9, "n2");    // istenilen hava akış hızı
NexNumber n3 = NexNumber(1, 10, "n3");   // ölçülen dakika tedavi başladığı andna itibaren
NexNumber n4 = NexNumber(1, 11, "n4");   // ölçülen sıcaklık
NexNumber n5 = NexNumber(1, 12, "n5");   // motorun dönme hızı
NexNumber n6 = NexNumber(1, 14, "n6");  // saniye
NexNumber n7 = NexNumber(1, 25, "n7");  // pulse modu sn aralığı


NexDSButton bt0 = NexDSButton(1, 4,  "bt0");  // tedavi süresi ile değişiklik butonu
NexDSButton bt1 = NexDSButton(1, 5,  "bt1");  // sıcaklığı değiştirme butonu
NexDSButton bt2 = NexDSButton(1, 7,  "bt2");  // motorun  ızını değiştirme butonu
NexDSButton bt3 = NexDSButton(1, 8,  "bt3");  // ön ısıtma başlatma butonu
NexDSButton bt4 = NexDSButton(1, 13,  "bt4");  // start ve pause butonu
NexDSButton bt5 = NexDSButton(1, 15,  "bt5");  // arka plandaki motoru ve serpantini durdurma butonu ama arak aplanda kullanıyorum bu butonu
NexDSButton bt6 = NexDSButton(1, 20,  "bt6");  //  STOP butonu
NexDSButton bt7 = NexDSButton(1, 23,  "bt7");  // stand by kodu butonu
NexDSButton bt8 = NexDSButton(1, 24,  "bt8");  // pulse modu butonu 
NexDSButton bt9 = NexDSButton(1, 26,  "bt9");  // pulse ayarlama butonu

NexTouch *nex_listen_list[] = {

// burada ekrandan aldığım verilerin tanımını yapıyorum hangi komponentlerden veri alıyorsam
// veri aldığım veya veri yolladığım komponenteleri ekrandaki urada yazyorum
// mesela page leri ayzmıyorum gerek yok
  &b2,
  &b3,
  &bt0,
  &bt1,
  &bt2,
  &bt3,
  &bt4,
  &bt5,
  &bt6,
  &bt7,
  &bt8,
  &bt9,
  &tm0, 
  &n4,
  &t0,
  &b0,
  &t1,
  &tm0,
 
 
  NULL
};
void t0PopCallback(void *ptr)
{
dbSerialPrintln("t0PopCallback");
   // t0.setText("");
}
void t1PopCallback(void *ptr)
{
dbSerialPrintln("t1PopCallback");
   // t1.setText("");
}

void b2PushCallback(void *ptr) {  // burada rakamları aşağı çekme butonu aşağı düşürme butonumun ayarlmalı var burada
//void soltarafbas()
  // int31_t ile tanımlaancak olan verinin cinsini tanumlıyorum değişken tanımlıyorum yani burada
  uint32_t number0 = 0;
  uint32_t number1 = 0;
  uint32_t number2 = 0;
  uint32_t number7 = 0;
  uint32_t buton0 = 0;
  uint32_t buton1 = 0;
  uint32_t buton2 = 0;
  uint32_t buton3 = 0;
  uint32_t buton4 = 0;
  uint32_t buton7 = 0;
  uint32_t buton8 = 0;
  uint32_t buton9 = 0;
 // yukarıda tanımladığım değişkenlere ekrandan aldığım verileri atıyorum pointer ile
  n0.getValue(&number0);  // tedavi süresi verisini alıyorum olmasını istediğim tedav süresinin
 n1.getValue(&number1);  //  sıcaklık verisini alıyorum olmasını istediğim sıcaklık verisinin
  n2.getValue(&number2);  //  hava akış hızı varisini aldıyorum olmasını istediğim hızın
  n7.getValue(&number7);  // pulse sn aralığonın verisini alıyorm olmasını istediğim saniye aralığının
  
  bt0.getValue(&buton0);  // tedavi süresini ayarlamak için bastığım buton
  bt1.getValue(&buton1);  // sıcaklığı ayarlama butonu
  bt2.getValue(&buton2);  // motor hzını ayaralma abutonu hava akış hzıı
  bt3.getValue(&buton3);  // ön ısıtma butonu
  bt4.getValue(&buton4);  // start normal modu başlatma butonu
  bt7.getValue(&buton7);  // stand by modu bıtonu
  bt8.getValue(&buton8);  // pulse modu başlatma butonu
  bt9.getValue(&buton9);   // pulse saniye aralığıı ayarlama butonu
  
  if(buton0 > 0 && number0 > 1 && buton1 < 1 && number0 <61 && buton2 < 1 && buton9 < 1)  // tedavi süresini azaltmak için yazılmış olan if komutu
    {
          number0=number0 - 1;
         n0.setValue(number0);
         //t0.setText("bt0-");
     }
  if(buton0 < 1 && buton1 > 0 && number1 > 35 && buton2 < 1 && buton9 < 1) //sıcaklığı azaltmak için yazılmış olan if komutu
     {
          number1=number1 - 1;
          n1.setValue(number1);
          //t0.setText("bt1-");
    }
  if(buton0 < 1 && buton1 < 1 && buton2 > 0 && number2 > 1 && buton9 < 1)   // motor hızını azaltmak için yazılmış olan if komutu
     {
         number2=number2 - 1;
        n2.setValue(number2);
          //t0.setText("bt2-");
     }
 if(buton9 > 0 && number7 > 3 && buton0 < 1  && buton2 < 1 && buton1 < 1)  // tedavi süresini azaltmak için yazılmış olan if komutu
     {
          number7=number7 - 1;
          n7.setValue(number7);
          //t0.setText("bt0-");
     }
}

void b3PushCallback(void *ptr) {   /// buradaki sayıları yukarı doğru arttırmak için ayaılmış olan kısım
 // void soltarafbas()
  //  aşağıdaki komponent numaralrı yukarıdaki aşağı düşürme kısmı ile aynıdır yamıyoru o yüzden
  // ekrandna aldığım verileri tanımlayacağım değişkenelri tanımlıyorum burada
  uint32_t number0 = 0;
  uint32_t number1 = 0;
  uint32_t number2 = 0;
  uint32_t number7 = 0;
  uint32_t buton0 = 0;
  uint32_t buton1 = 0;
  uint32_t buton2 = 0;
  uint32_t buton3 = 0;
  uint32_t buton9 = 0;
  // ekrandan aldığım verileri yyarıda tanımladığım değişkenlere atıyorum
  n0.getValue(&number0);
  n1.getValue(&number1);
  n2.getValue(&number2);
  n7.getValue(&number7);
  bt0.getValue(&buton0);
  bt1.getValue(&buton1);
  bt2.getValue(&buton2);
  bt3.getValue(&buton3);
  bt9.getValue(&buton9);
  
  if(buton0 > 0 && number0 < 60  && buton1 < 1  && buton2 < 1 && buton9 < 1)
  {  // tedavi süresini arttırmak için yazılmış olan if komutu
      number0=number0 + 1;
      n0.setValue(number0);
  }
  
  if(buton0 < 1 && buton1 > 0 && number1 < 55  && buton2 < 1 && buton9 < 1)
  {   // sıcaklığı arttırmak için yazılmış olan if komutu
      number1=number1 + 1;
      n1.setValue(number1);
     
  }
  
  if(buton0 < 1 && buton1 < 1  && buton2 > 0 && number2 < 8 && buton9 < 1)
  {   // motor dönme hızını arttırmak için yazılmış olan if komutu
      number2=number2 + 1;
      n2.setValue(number2);
 
  }
  if(buton9 > 0 && buton0 < 1 && number7 <6 && buton2 < 1 && buton1 < 1)  // tedavi süresini azaltmak için yazılmış olan if komutu
     {
          number7=number7 + 1;
          n7.setValue(number7);
          
     }
  
}
void bt3PushCallback(void *ptr) {  // ön ısıtma modunun başlaması için buton kodu  tanımlamalar yukarıdaki kodlar ile aynı zaten
  // ön ısıtmayı ayarlamak için değiştirecek olduğum değişkenlerin tanımlamasını ve pointerlarını tanımaldım
  uint32_t number0 = 0;
  uint32_t number1 = 0;
  uint32_t number2 = 0;
  uint32_t number3 = 0;
  uint32_t number6 = 0;
  uint32_t buton3 = 0;
  n0.getValue(&number0);
  n1.getValue(&number1);
  n2.getValue(&number2);
  n3.getValue(&number3);
  n6.getValue(&number6);
  bt3.getValue(&buton3);
  int motor_pwm = 0;
  

  
  if(buton3 > 0)
  {  // okuduğum sıcaklık verisi , ekrandan aldığık sıcaklık verisi ve sıcaklığa göre mootr dönme hızını 
    //  motora ve ekrana yazdırma işlemleri var aşağıda
    uint32_t buton3 = 0;  // buton 3 verisini kaydedeceğim değişlken
    uint32_t scaklk = 0;  // ekrana yazdıracağım sıcaklık verisiin yeri
    uint32_t want_scaklk = 0;   // ekrnada n adlığım ortamın olmasını istediğim sıcaklık değerinin değişkeni
    uint32_t curspeed =0;   // ekrana yazdırdığım moot rhızı 3 ile 10 arasında ki
    uint32_t wantspeed =0;  // ekrandan girilen hzı değeri
    
  
    n5.getValue(&curspeed);   // motorun anlık değişken hızının ayzılacağı yerdeki veriyi çekiyorum öndce
    n4.getValue(&scaklk);   // ortamın değişke sıcaklıını yazdırcağım yerin verisinni çekiyorum burada
    bt3.getValue(&buton3);   // ön ısıtma abutonunun durumunu kontrol ediyorum 1 ve 0 
    n1.getValue(&want_scaklk);  // ortamın gelmesini istediğim sıcaklık değeri
 
   // motor dönme hızını 6. kademye ayarlıyorum
    n1.getValue(&want_scaklk);   // ortamın gelemsi gereken sıcaklık dğerini tekrardan check ediyorum  
    n2.getValue(&wantspeed);     
        
                //digitalWrite(role2, HIGH);     
                // bu aağısı sıcaklık sensörünün okunma kodu 
                DS18B20.requestTemperatures();  
                santigrat = DS18B20.getTempC(DS18B20adres);
                if(santigrat<100)
                {
                scaklk=santigrat;  // sensörden okunan değeri scaklık değerine atıyorum
                }
                delay(1);
               if(scaklk<100)
                {
                n4.setValue(scaklk);  // sensör değerini ekraan ayzdırıyorum
                }  // scaklık değerini ekrana yazdırıyorum
                curspeed = map(scaklk, 20 , want_scaklk , 1 , 4);   // ortamın olması gereken sıcaklık değerin motor hızına oranlıyorum 
                delay(1);
                if(curspeed<9)
                {
                n5.setValue(curspeed);  // sıcaklık ile orantılı olarak değişen motor hızı ekran yazdırıyorum kademe değerini
                } 
                 if(number0 > number3 )  // tedav süresi, tedavi uygulan zamana eşit değilse
                   {
                   //digitalWrite(led1, LOW); 
                    if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                  
                   }
          if(scaklk >( want_scaklk - 2 ))   // sensördeki sıcaklık verisi ortam sıcaklığını geçinse serpantin kapanıyor
                {
                  digitalWrite(role2,LOW);  // serpantin kapnıyor sıcaklık eşik değerini geçtiği için
                }
         if(scaklk < want_scaklk)
                {
                  digitalWrite(role2,HIGH);  // sıcaklık eşik dğerinden aşağıya düştüğü için serpantini yeniden açyorum
         }
          
  if(number0 == number3 || number0 < number3)  // tedavi süresi, geçen zmana eşit olursa diye koşul  motor ve serpantini kapatıyorum 
   { // TEDAVİ BİTTİ YANİ
    motordurdurma();
    
    digitalWrite(role2, LOW);
   }
  if(scaklk > 55)
         {
     digitalWrite(role2,LOW);
   }
   }
        
  

}

void bt4PushCallback(void *ptr) {
// START PAUSE butonu için gerekli olan ve kullanacağım değişken ve pointerları tanımlıyorum 
    int emergency_heat = 0;
    uint32_t buton4 = 0;
    uint32_t scaklk = 0;
    uint32_t curspeed =0;
    uint32_t wantspeed =0;
    uint32_t dakka = 0;
    uint32_t snye =0;
    uint32_t SURE =0;
    uint32_t want_scaklk = 0;
    int motor_pwm = 0;
    n0.getValue(&SURE);  /// tedavi edecegim süre sınırı 
    n3.getValue(&dakka);  // tedavi züerinden geçen dakka versini alıyorum
    n6.getValue(&snye);  // tedavde geçen saiyeyi alıyorum
    n2.getValue(&wantspeed);
    n1.getValue(&want_scaklk);  // ortamın gelmesni istedğim sıcaklık değerini ekrand adeğiştirdiğim için alıyorum değeri
  
    n5.getValue(&curspeed);  // ekan yazdırdığım mootr hızının değerini alıyorum 
    n4.getValue(&scaklk);   // ekrana ayzhdırdığım sensör değerinin verisini alıyorum
    bt4.getValue(&buton4); 
    uint32_t buton6 = 0;
    bt6.getValue(&buton6);// start pause buronunun konumunu alıyorum 1 vwya 0
         if(buton4 > 0 && buton6 > 0) {   
                  /// sıcaklık verisii ayzdırdığım yeer yukarısı ile aynı    
                DS18B20.requestTemperatures();
                santigrat = DS18B20.getTempC(DS18B20adres);
                if(santigrat<100)
                {
                scaklk=santigrat;
                }
                delay(1);
                if(scaklk<100)
                {
                n4.setValue(scaklk);  // sensör değerini ekraan ayzdırıyorum
                }
                curspeed = map(scaklk, 20 , want_scaklk , 1 , 4);  // motorun hızını isteediğim sıcaklık değri ile orantılıyorum
                delay(1);
                if(curspeed<9)
                {
                n5.setValue(curspeed);  // sıcaklık deeğri ile rtanlanmış olan motor hız kadme değerini ekrana ayzdırıyorum 2 ile 10 arsaı
                }
                if(SURE > dakka )  // tedav süresi, tedavi uygulan zamana eşit değilse
                   {
                 if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                  
                  }
                emergency_heat= want_scaklk + 8;  // ortamın gelmesini istediğim sıcaklık değerinde n 8 derece fazla sıcaklığagelirse ortam seerpantin kapanıyor sıcaklık düşsün diye
         if(scaklk >= (want_scaklk - 2))   // sensördeki sıcaklık verisi ortam sıcaklığını geçinse serpantin kapanıyor
                {
                  digitalWrite(role2,LOW);  // serpantin kapnıyor sıcaklık eşik değerini geçtiği için
                }
         if(scaklk < (want_scaklk - 2))
                {
                  digitalWrite(role2,HIGH);  // sıcaklık eşik dğerinden aşağıya düştüğü için serpantini yeniden açyorum
         }
                          
         }
         if(buton4 >! 0 )  //  START PAUSE butonuna basılı durumda değilse motor ve serpantin kapalı durumda
         {
           motordurdurma();
          
          digitalWrite(role2, LOW);
          //digitalWrite(led1, HIGH); 
         }
         if(scaklk > 55)
         {
          digitalWrite(role2,LOW);
         }

   if(SURE == dakka ||SURE < dakka)  // tedavi süresi, geçen zmana eşit olursa diye koşul  motor ve serpantini kapatıyorum 
   { // TEDAVİ BİTTİ YANİ
    
    motordurdurma();
    
    digitalWrite(role2, LOW);
   }  

 } 
void bt5PushCallback(void *ptr) {   /// ARKA PLANDA PAUSE TUŞUNA BASILDIKTAN SONRA EKRANDAN GELEN MOTORU VE SERPANTİNİ KAPATMA KOMUTU
  // EKRANDA PAUSEYE BASILDIKTAN 1 SANİYE SONRA BU BUTONA BASILDI DİYE KOMUT GELİYOR EKAND AKÜÇÜK BİR YERDE BULUNAMAZ
  // STARTA BASTIKTAN 1 SANİYE SONRA BU BUTONA BASILDI SİNYALİNİ VERİDİRİYORUM EKRAN AYZILIMINDAN DOLAYISYLA MOTORUM STOP OLUYOR REZİSTANSIM KAPANIYOR
  // VE EKRANDA DEĞİŞİKLİK YAPMAM DAHA DA KOLAYLAŞIYOR ÇÜNKÜ START BUTONU AKTİFKEN TIMER SAYIYOR VE SERİ PORTU MEŞGUL ETTİĞİ İÇİN KOLAY KOLAY DEĞİŞİKLİK YAPAMIYORUM

  // BU UTON SADECE MOTOR VE REZİSTANSI KAPATMA İÇİN ARAKA PLANDA KULLANIYORUM

  // 2 İF KOŞUUD MOTORU KAPATMAYA YÖNELİK 1 İKEND E0 İKEDNE MOTORU KAPATMAY AAYARLI BUTON 
    uint32_t buton5 = 0;
    bt5.getValue(&buton5);
    if(buton5 > 0) {
 
       motordurdurma();
       
       digitalWrite(role2, LOW);
    }
    else
    {

     // digitalWrite(led1, LOW);
     motordurdurma();
      
      digitalWrite(role2, LOW);
    }
}
void bt6PushCallback(void *ptr) {
   // STOP BUTONUDUR TEDAVİYİ ANİDEN BİTİRİ SÜREYİ SIFIRLAR HERŞEYE BAŞTAN BAŞLARSIN START İLE AYNI ANDA GÖRÜNMEZ STARTA BASILDIKTAN SONRA EKTANDA BELİRİR VE STOPA BASILDIĞINDA HER ŞEY SIFIRLANIR
   // MOTOR VE SERPANTİNİDE KAPATIR 
    uint32_t buton6 = 0;
    bt6.getValue(&buton6);
    if(buton6 < 1) {
       motordurdurma();
       
       digitalWrite(role2, LOW);
    }
    else
    {
      motordurdurma();
      
       digitalWrite(role2, LOW);
    }
}


void bt7PushCallback(void *ptr) {
  // ön ısıtmayı ayarlamak için değiştirecek olduğum değişkenlerin tanımlamasını ve pointerlarını tanımaldım
  uint32_t number0 = 0;
  uint32_t number1 = 0;
  uint32_t number2 = 0;
  uint32_t number3 = 0;
  uint32_t number6 = 0;
  uint32_t buton3 = 0;
  uint32_t buton7 = 0;

  n0.getValue(&number0);
  n1.getValue(&number1);
  n2.getValue(&number2);
  n3.getValue(&number3);
  n6.getValue(&number6);
  bt3.getValue(&buton3);
  bt7.getValue(&buton7);
  int motor_pwm = 0;
  
  if(buton7 > 0)
  {  // okuduğum sıcaklık verisi , ekrandan aldığık sıcaklık verisi ve sıcaklığa göre mootr dönme hızını 
    //  motora ve ekrana yazdırma işlemleri var aşağıda
  
    uint32_t scaklk = 0;  // ekrana yazdıracağım sıcaklık verisiin yeri
    uint32_t want_scaklk = 0;   // ekrnada n adlığım ortamın olmasını istediğim sıcaklık değerinin değişkeni
    uint32_t curspeed =0;   // ekrana yazdırdığım moot rhızı 3 ile 10 arasında ki
    uint32_t wantspeed =0;  // ekrandan girilen hzı değeri
    
    n5.getValue(&curspeed);   // motorun anlık değişken hızının ayzılacağı yerdeki veriyi çekiyorum öndce
    n4.getValue(&scaklk);   // ortamın değişke sıcaklıını yazdırcağım yerin verisinni çekiyorum burada
    n1.getValue(&want_scaklk);  // ortamın gelmesini istediğim sıcaklık değeri
 
   // motor dönme hızını 6. kademye ayarlıyorum
    n1.getValue(&want_scaklk);   // ortamın gelemsi gereken sıcaklık dğerini tekrardan check ediyorum  
    n2.getValue(&wantspeed);     
        
                //digitalWrite(role2, HIGH);     
                // bu aağısı sıcaklık sensörünün okunma kodu 
                DS18B20.requestTemperatures();
                santigrat = DS18B20.getTempC(DS18B20adres);
                if(santigrat<100)
                {
                scaklk=santigrat;  // sensörden okunan değeri scaklık değerine atıyorum
                }
                delay(1);
               if(scaklk<100)
                {
                n4.setValue(scaklk);  // sensör değerini ekraan ayzdırıyorum
                }  // scaklık değerini ekrana yazdırıyorum
                curspeed = map(scaklk, 20 , want_scaklk , 1 , 4);   // ortamın olması gereken sıcaklık değerin motor hızına oranlıyorum 
                delay(1);
                if(curspeed<9)
                {
                n5.setValue(curspeed);  // sıcaklık ile orantılı olarak değişen motor hızı ekran yazdırıyorum kademe değerini
                }
                 if(number0 > number3 )  // tedav süresi, tedavi uygulan zamana eşit değilse
                   {
                  
                   if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                         
                    }    // 1 satır yukarıda oranlanmış pwm değerini yazırıyorum arduinodan RÖLE ye
          
          if(scaklk > want_scaklk)   // sensördeki sıcaklık verisi ortam sıcaklığını geçinse serpantin kapanıyor
                {
                  digitalWrite(role2,LOW);  // serpantin kapnıyor sıcaklık eşik değerini geçtiği için
                }
         if(scaklk < want_scaklk)
                {
                  digitalWrite(role2,HIGH);  // sıcaklık eşik dğerinden aşağıya düştüğü için serpantini yeniden açyorum
         }
          
  if(number0 == number3 || number0 < number3)  // tedavi süresi, geçen zmana eşit olursa diye koşul  motor ve serpantini kapatıyorum 
   { // TEDAVİ BİTTİ YANİ
  
    motordurdurma();
    digitalWrite(role2, LOW);
   }
  if(scaklk > 55)
         {
          digitalWrite(role2,LOW);
   }
   }
    if(buton7 < 1)
    {
      motordurdurma() ;
      digitalWrite(role2, LOW);
    }
     
}
void bt8PushCallback(void *ptr) {
// START PAUSE butonu için gerekli olan ve kullanacağım değişken ve pointerları tanımlıyorum 
    int emergency_heat = 0;
    uint32_t buton8 = 0;
    uint32_t scaklk = 0;
    uint32_t curspeed =0;
    uint32_t wantspeed =0;
    uint32_t dakka = 0;
    uint32_t snye =0;
    uint32_t SURE =0;
    uint32_t want_scaklk = 0;
    int motor_pwm = 0;
    uint32_t pulse =0;
    n7.getValue(&pulse);
    n0.getValue(&SURE);  /// tedavi edeceim süre sınırı 
    n3.getValue(&dakka);  // tedavi züerinden geçen dakka versini alıyorum
    n6.getValue(&snye);  // tedavde geçen saiyeyi alıyorum
    n2.getValue(&wantspeed);
    
    n1.getValue(&want_scaklk);  // ortamın gelmesni istedğim sıcaklık değerini ekrand adeğiştirdiğim için alıyorum değeri
  
    n5.getValue(&curspeed);  // ekan yazdırdığım mootr hızının değerini alıyorum 
    n4.getValue(&scaklk);   // ekrana ayzhdırdığım sensör değerinin verisini alıyorum
    bt8.getValue(&buton8); 
    uint32_t buton6 = 0;
    bt6.getValue(&buton6);// start pause buronunun konumunu alıyorum 1 vwya 0
         if(buton8 > 0 && buton6 > 0) {   
                  /// sıcaklık verisii ayzdırdığım yeer yukarısı ile aynı    
                DS18B20.requestTemperatures();
                santigrat = DS18B20.getTempC(DS18B20adres);
                if(santigrat<100)
                {
                scaklk=santigrat;
                }
                delay(1);
                if(scaklk<100)
                {
                n4.setValue(scaklk);  // sensör değerini ekraan ayzdırıyorum
                }
                curspeed = map(scaklk, 20 , want_scaklk , 1 , 4);  // motorun hızını isteediğim sıcaklık değri ile orantılıyorum
                delay(1);
               if(curspeed<9)
               {
                n5.setValue(curspeed);  // sıcaklık deeğri ile rtanlanmış olan motor hız kadme değerini ekrana ayzdırıyorum 2 ile 10 arsaı
               } 
                if(SURE > dakka )  // tedav süresi, tedavi uygulan zamana eşit değilse
                   {
                    if(pulse==3)  // pulse modunda 3 sn pulse istiyorsam o saniye geldiğinde pwm i full yapıyorum ki motor max hızda dönsün 
                    {
                      if(snye >= 0 && snye <= 26)   
                      {
                     if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                  
                      }
                      if(snye > 26 && snye <= 30)
                      {
                        ikiyuzyirmikohmlukhiz;
                      }
                      if(snye > 30 && snye <= 55)
                      {
                      if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                  
                      }
                      if(snye > 55 && snye <= 59)
                      {
                        ikiyuzyirmikohmlukhiz;
                      }
                    }
                    if(pulse==4)  //  4 sn puls eyapsın istediğim kod ksmı
                    {
                      if(snye >= 0 && snye <= 25)
                      {
                      if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                  
                      }
                      if(snye > 25 && snye <= 30)
                      {
                       ikiyuzyirmikohmlukhiz;  
                      }
                      if(snye > 30 && snye <= 54)
                      {
                       if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                  
                      }
                      if(snye > 54 && snye <= 59)
                      {
                       ikiyuzyirmikohmlukhiz;  
                      }
                    }
                    if(pulse==5)
                    {
                      if(snye >= 0 && snye <= 24)
                      {
                       if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                  
                      }
                      if(snye > 24 && snye <= 30)
                      {
                        ikiyuzyirmikohmlukhiz; 
                      }
                      if(snye > 30 && snye <= 53)
                      {
                       if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                  
                      }
                      if(snye > 53 && snye <= 59)
                      {
                        ikiyuzyirmikohmlukhiz; 
                      }
                    }
                    if(pulse==6)
                    {
                      if(snye >= 0 && snye <= 23)
                      {
                     if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                  
                      }
                      if(snye > 23 && snye <= 30)
                      {
                      ikiyuzyirmikohmlukhiz; 
                      }
                      if(snye > 30 && snye <= 52)
                      {
                       if(wantspeed == 1)
                    {
                     yuzseksenkohmlukhiz(); 
                    }
                    
                    
                    if(wantspeed == 2)
                    {
                      yuzellikohmlukhiz(); 
                       
                    }
 
                    if(wantspeed == 3)
                    {
                     yuzyirmikohmlukhiz();   
                    }
         
                    if(wantspeed == 4)
                    {
                     doksandokuzkohmlukhiz();   
                    }
                
                   if(wantspeed == 5)
                    {
                     seksenikikohmlukhiz();   
                    }
                 
                    
                    if(wantspeed == 6)
                    {
                      yetmisikikohmlukhiz(); 
                    }
                    
                    if(wantspeed == 7)
                    {
                     ellidokuzkohmlukhiz(); 
                    }
                
                    if(wantspeed == 8)
                    {
                    kirksekizkohmlukhiz();   
                    }
                  
                      }
                      if(snye > 52 && snye <= 59)
                      {
                        ikiyuzyirmikohmlukhiz;  
                      }
                    }
                   //digitalWrite(led1, LOW); 
                 }
                emergency_heat= want_scaklk + 8;  // ortamın gelmesini istediğim sıcaklık değerinde n 8 derece fazla sıcaklığagelirse ortam seerpantin kapanıyor sıcaklık düşsün diye
         if(scaklk >= (want_scaklk - 2))   // sensördeki sıcaklık verisi ortam sıcaklığını geçinse serpantin kapanıyor
                {
                  digitalWrite(role2,LOW);  // serpantin kapnıyor sıcaklık eşik değerini geçtiği için
                }
         if(scaklk < (want_scaklk - 2))
                {
                  digitalWrite(role2,HIGH);  // sıcaklık eşik dğerinden aşağıya düştüğü için serpantini yeniden açyorum
         }
                          
         }
         if(buton8 >! 0 )  //  START PAUSE butonuna basılı durumda değilse motor ve serpantin kapalı durumda
         {
          motordurdurma(); 
          digitalWrite(role2, LOW);
          //digitalWrite(led1, HIGH); 
         }
         if(scaklk > 55)
         {
          digitalWrite(role2,LOW);
         }
         
   if(SURE == dakka ||SURE < dakka)  // tedavi süresi, geçen zmana eşit olursa diye koşul  motor ve serpantini kapatıyorum 
   { // TEDAVİ BİTTİ YANİ
  
    motordurdurma(); 
    digitalWrite(role2, LOW);
   } 

 } 
void tm0TimerCallback(void *ptr)
{
    
    
}
void n4PopCallback(void *ptr)
{
    dbSerialPrintln("n4PopCallback");
          // n4.setValue(50);
}
void setup() {
  
    Serial.begin(9600);
   
    DS18B20.begin();

    DS18B20.getAddress(DS18B20adres, 0);

    DS18B20.setResolution(DS18B20adres, 12);

//**********************************
 
    pinMode(role2, OUTPUT);
    
    pinMode(kohm120, OUTPUT);
    pinMode(kohm150, OUTPUT);
    pinMode(kohm180, OUTPUT);
    pinMode(kohm220, OUTPUT);

    motordurdurma();
 //****************************************

  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
 
   nexInit();
   b2.attachPush(b2PushCallback, &b2);
   b3.attachPush(b3PushCallback, &b3);

   bt3.attachPush(bt3PushCallback, &bt3);
   
   bt4.attachPush(bt4PushCallback, &bt4);
   
   bt5.attachPush(bt5PushCallback, &bt5);
   
   bt6.attachPush(bt6PushCallback, &bt6);

   bt7.attachPush(bt7PushCallback, &bt7);

   bt8.attachPush(bt8PushCallback, &bt8);

   tm0.attachTimer(tm0TimerCallback);

   n4.attachPop(n4PopCallback);


   DS3231_get(&t);
  
    if(t.mon > 7)  ///  burada filtre değişimi için alrmın verilecei 6 ay sınırı zaten pili çıkarttığımda süre 01,01,2000 tarihine sıfırlıyor zaten pili çıkartmak yeterli süreyi sıfırlamk için 
 {
 
    t0.setText("FILTER CHANGE");
 }

    t1.setText("Calistirilabilir");

   dbSerialPrintln("setup done");
  // pinMode(led1, OUTPUT);

   tm0.enable();
   
}
void loop(void) {
   
   nexLoop(nex_listen_list);
   
     
}
