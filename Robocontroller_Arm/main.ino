
#include <ax12.h>
#include <BioloidController.h>

#include "poses.h"


#include <avr/pgmspace.h>

#define INTERRUPT1 3
#define COM0 4
#define COM1 5
#define COM2 6
#define COM3 7


BioloidController bioloid = BioloidController(1000000);

const int SERVOCOUNT = 6;
int id;
int pos;
int system_counter;
boolean IDCheck;
boolean RunCheck;

const int num_motors = 6;



/*
//Default number position
const PROGMEM uint16_t No_Motion_Num_Display[] = {6, 1801, 1340, 1433, 2949, 514, 140};

//Hand shake
const PROGMEM uint16_t Hand_shake_up[] = {6,2033, 1698, 1550, 2336, 512, 512};
const PROGMEM uint16_t Hand_shake_down[] = {6,2033, 1698, 1448, 2336, 512, 512};

//Thumbs up
const PROGMEM uint16_t Thumbs_up[] = {6, 1515, 1322, 1914, 1201, 284, 681};

//Thumbs down
const PROGMEM uint16_t Thumbs_down[] = {6, 1277, 1296, 1938, 1318, 502, 1023};

//Okay
const PROGMEM uint16_t Okay_Pos[] = {6, 1428, 1453, 1591, 3099, 850, 727};

//Rock Paper Scissors
const PROGMEM transition_t Rock_Paper_Scissors[] = {{0,9} ,{r_p_sci_pos_1,350} ,{r_p_sci_pos_2,350} ,{r_p_sci_pos_3,350} ,{r_p_sci_pos_2,350} ,{r_p_sci_pos_1,350} ,{r_p_sci_pos_2,350} ,{r_p_sci_pos_3,350} ,{r_p_sci_pos_2,350} ,{r_p_sci_pos_1,500} };
//{{0,3} ,{r_p_sci_pos_1,350} ,{r_p_sci_pos_2,350} ,{r_p_sci_pos_3,350} };

const PROGMEM uint16_t High_5_Reach_Stars[] = {6, 5000, 2048, 3070, 2048, 205, 0};

//Default pos lo
//const PROGMEM uint16_t  r_p_sci_pos_1[] = {6, 1396, 1188, 1255, 2180, 480, 497};
*/
//To load individual positions
void ArmMovement(PROGMEM uint16_t positions[], const int index, int interpolateSpeed);

//To load a sequence of positions
void ArmSequencer(PROGMEM transition_t sequence[], const int index);

void setup(){
   pinMode(0,OUTPUT);  
   pinMode(INTERRUPT1, OUTPUT);
   
   //initialize variables 
   id = 1;
   pos = 0;
   IDCheck = 1;
   RunCheck = 0;
   system_counter =0;
   
   //open serial port
   Serial.begin(9600);
   delay (500);   
   Serial.println("###########################");    
   Serial.println("Serial Communication Established."); 
 

  
   MenuOptions();
   RunCheck = 1;
  

}


void loop(){

   
     
     int inByte = Serial.read();
    
     int comInput; // = '0';
     comInput = CommunicationPinGet();



   //Code to test with serial communication if parallel communication with microcontroller is unavailable
      
    ////if (inByte == '1')
   // {
    

 
     // Serial.println("###########################");
     //// Serial.print("Digital communication established ");
     // Serial.println("###########################");
      //Serial.println(inByte);
      

     

      //else
      //{
        /*
        Serial.println("###########################");
        Serial.println("Digital communication was not established ");
        Serial.println("###########################");
        */
     // }

   


    //Menu for communication
    switch (comInput) {


      case 1:    
      Serial.println("Digital communication inititated 1"); 
      ArmMovement(No_Motion_Num_Display,num_motors,2000);
      break;
      
      case 2:
     
      Serial.println("Digital communication inititated 2"); 
      ArmMovement(Okay_Pos,num_motors,2000);
      break;
     

      
      case 5: 
      Serial.println("Digital communication inititated 5");
      ArmMovement(Thumbs_up,num_motors,3000);
      break; 

      case 6: 
      Serial.println("Digital communication inititated 6");
      ArmMovement(Thumbs_down,num_motors,3000);
      break;

      case 7:

      //Serial.println("Digital communication inititated 15"); 
      //ArmMovement(Piano_begin,num_motors,1000); 
      //break;
 
      Serial.println("Digital communication inititated 7"); 
      ArmSequencer(Spiderman, 10);
      break;

/*
     case 12:    //Handshake
     {
       Serial.println("Digital communication inititated 5"); 
            ArmMovement(Hand_shake_up,num_motors,500);
            ArmMovement(Hand_shake_down,num_motors,200);   
     }


     break;

     case 21:    
      {
        Serial.println("Digital communication inititated 6"); 
         //ArmSequencer(Spiderman, 10)
      break;     

     case 8:
      Serial.println("Digital communication inititated 8"); 
      break;

*/
     case 9:  
     Serial.println("Digital communication inititated 9"); 
     break;

     case 10:  
     Serial.println("Digital communication inititated 10"); 
     ArmSequencer(Rock_Paper_Scissors,250);
     delay(2000);
     break;
      
     case 11:
     Serial.println("Digital communication inititated 11");
     ArmSequencer(Wave_improved,500);
     break;

     case 12: //Piano_player
     Serial.println("Digital communication inititated 12");
     ArmSequencer(Piano_player,250);
     break;

     
     case 13: //Hold for piano
     Serial.println("Digital communication inititated 13"); 
    // ArmMovement(Piano_begin,num_motors,1000); 
     break;

     case 14: //Hold for rock papee sci
     Serial.println("Digital communication inititated 14"); 
     ArmMovement(r_p_sci_pos_1,num_motors,500);  
     break;

     case 15: //Hold for piano
     Serial.println("Digital communication inititated 15"); 
     ArmMovement(Piano_begin,num_motors,1000); 
     break;
      
     default:
     break;
    
    } 

       
}
    


void ScanServo(){
  id = 1;  
  Serial.println("###########################");
  Serial.println("Starting Servo Scanning Test.");
  Serial.println("###########################");
      
  while (id <= SERVOCOUNT){
  pos =  ax12GetRegister(id, 36, 2);
  Serial.print("Servo ID: ");
  Serial.println(id);
  Serial.print("Servo Position: ");
  Serial.println(pos);
  
  if (pos <= 0){
  Serial.println("###########################");
  Serial.print("ERROR! Servo ID: ");
  Serial.print(id);
  Serial.println(" not found. Please check connection and verify correct ID is set.");
  Serial.println("###########################"); 
  IDCheck = 0;
  }
  
  id = (id++)%SERVOCOUNT;
  delay(1000);
  }
  if (IDCheck == 0){
    Serial.println("###########################");
    Serial.println("ERROR! Servo ID(s) are missing from Scan. Please check connection and verify correct ID is set.");
    Serial.println("###########################");  
  }
  else{
  Serial.println("All servo IDs present.");
  }
    if (RunCheck == 1){
    MenuOptions();
  }

}


/*
void CheckVoltage(){  
   // wait, then check the voltage (LiPO safety)
  float voltage = (ax12GetRegister (1, AX_PRESENT_VOLTAGE, 1)) / 10.0;
  Serial.println("###########################");   
  Serial.print ("System Voltage: ");
  Serial.print (voltage);
  Serial.println (" volts.");
  if (voltage < 10.0){
    Serial.println("Voltage levels below 10v, please charge battery.");
    
    //Serial.println("Resetting Arduino now");
    //wdt_reset(); // Reset the watchdog timer
    //while(1);    // Enter an infinite loop to allow the reset to occur
  }  
  if (voltage > 10.0){
  Serial.println("Voltage levels nominal.");
  }
    if (RunCheck == 1){
      MenuOptions();
  }
      Serial.println("###########################"); 
}
*/
void ArmSequencer(PROGMEM transition_t sequence[], const int index)
{
  
      bioloid.playSeq(sequence);
             
      while(bioloid.playing)
     {
       bioloid.play();
     
     }

         
     MenuOptions();
}
void ArmMovement(PROGMEM uint16_t positions [], const int index, int interpolateSpeed){
  
   // interrupts();
    delay(100);                    // recommended pause
    bioloid.loadPose(positions);   // load the pose from FLASH, into the nextPose buffer
    bioloid.readPose();            // read in current servo positions to the curPose buffer
    Serial.println("###########################");
   
    //Serial.println("Moving servos to centered position");
    Serial.println("###########################");    
    
    
    bioloid.interpolateSetup(interpolateSpeed); // setup for interpolation from current->next over 1/2 a second Original :1000
    while(bioloid.interpolating > 0){  // do this while we have not reached our new pose
        bioloid.interpolateStep();     // move servos, if necessary. 
        
    }
    
    if (RunCheck == 1){
      MenuOptions();
  }
}




void MoveTest(){
  Serial.println("###########################");
  Serial.println("Initializing Movement Sign Test");  
  Serial.println("###########################");
  delay(500);  
  id = 1;
  pos = 2048;
 
// Base Servo Test

  Serial.println("Moving Servo ID: 1");
  
  while(pos >= 1500){  
  SetPosition(1, pos);
  pos = pos--;
  delay(10);
  }

  while(pos <= 2048){  
  SetPosition(1, pos);
  pos = pos++;
  delay(10);
  }
  
  delay(500);

// Shoulder Servo Test  
  
  Serial.println("Moving Servo IDs: 2 "); 
  while(pos >= 1500){  
  SetPosition(2, pos);
  pos = pos--;
  delay(10);
  }

  while(pos <= 2048){  
  SetPosition(2, pos);
  pos = pos++;
  delay(10);
  }

  delay(500);
  
// Elbow Servo Test  

  Serial.println("Moving Servo IDs: 3 "); 
  while(pos <= 2400){  
  SetPosition(3, pos);
  pos = pos++;
  delay(10);
  }

  while(pos >= 2048){  
  SetPosition(3, pos);
  pos = pos--;
  delay(10);
  }

  delay(500);


  //Wrist Servo Test
  
  Serial.println("Moving Servo ID: 4");
  
  while(pos <= 2500){  
  SetPosition(4, pos);
  pos = pos++;
  delay(10);
  }

  while(pos >= 2048){  
  SetPosition(4, pos);
  pos = pos--;
  delay(10);
  }
  
  delay(500);  
 
 pos = 512; 
  
  //Wrist Rotate Servo Test  

  Serial.println("Moving Servo ID: 5");
  
  while(pos >= 312){  
  SetPosition(5, pos);
  pos = pos--;
  delay(10);
  }

  while(pos <= 512){  
  SetPosition(5, pos);
  pos = pos++;
  delay(10);
  }
  
  delay(500);   
  
  //Gripper Servo Test  
  
    Serial.println("Moving Servo ID: 6");
  
  while(pos >= 312){  
  SetPosition(6, pos);
  pos = pos--;
  delay(10);
  }

  while(pos <= 512){  
  SetPosition(6, pos);
  pos = pos++;
  delay(10);
  }
  
  delay(500);   
 
    if (RunCheck == 1){
   MenuOptions();
  }
  
}



void MenuOptions(){
  
    Serial.println("###########################"); 
    Serial.println("Please enter option 1-10 to perform any of the movements or gestures below.");             
    Serial.println("1)  Number display");   
    Serial.println("2)  Okay"); 
    Serial.println("3)  "); 
    Serial.println("4)  ");     
    Serial.println("5)  Thumbs Up");            
    Serial.println("6)  Thumbs down"); 
    Serial.println("7)  Spiderman"); 
    Serial.println("10) Rock, Paper, Scissors");  
    Serial.println("12) Piano player");                    
    Serial.println("###########################"); 
}

void RelaxServos(){
  id = 1;
  Serial.println("###########################");
  Serial.println("Relaxing Servos.");
  Serial.println("###########################");    
  while(id <= SERVOCOUNT){
    Relax(id);
    id = (id++)%SERVOCOUNT;
    delay(50);
  }
   if (RunCheck == 1){
      MenuOptions();
  }
}

void LEDTest(){
    id = 1;
  Serial.println("###########################");
  Serial.println("Running LED Test");
  Serial.println("###########################");    
  while(id <= SERVOCOUNT){
    ax12SetRegister(id, 25, 1);
    Serial.print("LED ON - Servo ID: ");
    Serial.println(id);
    delay(500); //Oriekaose: was 3000
    ax12SetRegister(id, 25, 0);  
    Serial.print("LED OFF - Servo ID: ");
    Serial.println(id);    
    delay(500);    
    id++; //changing to id++
  }
  
   if (RunCheck == 1){
      MenuOptions();
  }
}




//int CommunicationPinGet(bool, bool, bool, bool);

int CommunicationPinGet()
{
   pinMode(COM0,INPUT);
   pinMode(COM1,INPUT);
   pinMode(COM2,INPUT);
   pinMode(COM3,INPUT);
   
   int gesture_num = 0;

   gesture_num += (8*digitalRead(COM0));
   gesture_num += (4*digitalRead(COM1));
   gesture_num += (2*digitalRead(COM2));
   gesture_num += (1*digitalRead(COM3));


   Serial.print("The pins read are: ");
   Serial.print(digitalRead(COM0));
    Serial.print(digitalRead(COM1));
     Serial.print(digitalRead(COM2));
      Serial.println(digitalRead(COM3));

   return gesture_num;
}
