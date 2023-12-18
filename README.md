# WidowX_Arm_HIWONDER_Bionic_Hand-Interface </h2>


<img src="https://github.com/Osestic/WidowX_Arm_HIWONDER_Bionic_Hand-Interface/assets/42704298/25f37eee-65a8-4e1e-a7c2-306f3ad84e96" width="300"/>

## Description
For our Introduction to Microcontrollers course final project, [Evan Varga](https://www.linkedin.com/in/evan-varga-2a21aa221/) and I embarked on integrating a WidowX Robotic Arm controlled with an Arbotix - M Arduino, a robocontroller, with a HIWONDER Bionic hand controlled by a Tiva C Series TM4C123G microcontroller to perform various hand and arm gestures, play a game and play an instrument. 

Through the microcontroller's Universal Asynchronous Receiver-Transmitter (UART) module, commands can be sent to the microcontroller to cause the fingers of the HIWOnDER bionic hand to move into certain positions through pulse-width modulations. These commands also cause digital signals to be sent through parallel communication to the Arbotix -M robotcontroller. These signals make the WidowX arm move into certain position or perform sequences of positions. All these working together lead to creative gestures and actions being performed.

## Set up
1.	Unscrew the plastic claw piece from the from Widowx Arm.
2.	Screw the HIWONDER BIONIC Hand onto it.
3.	Connect the pins to be configured as pulse-width modulation pins to hand.
4.	Connect the pins to be configured for parallel communication to pins on the Arbotix -M 
Arduino.

### Note:
1.	The codes to be mentioned below contain the specific pins configured for steps 3 and 4 above. Your own pins can be configured as well.
2.	Employ good cable/wire management to ensure proper connections and to easily debug issues which often stem from disconnections. Breadboards are quite useful, and one was used for this project.
3.	When the motors fault out due to exceeding the limits of their possible positions or as safety measures to protect users, they flash red and are disabled. Unplug the power cord and plug back in to rest them. 
4.	Unplug the power cord to relax the motors or run ‘’’PyPose.py’’’ , to be mentioned below.

## Programmed With

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)


## Installation
There are 2 different folders containing the two major pieces of the project:
- [Microcontroller_Hand](https://github.com/Osestic/WidowX_Arm_HIWONDER_Bionic_Hand-Interface/tree/main/Microcontroller_Hand)/

- [Robocontroller_Arm](https://github.com/Osestic/WidowX_Arm_HIWONDER_Bionic_Hand-Interface/tree/main/Robocontroller_Arm)/


As the names imply, the former folder contains the code that programs the microcontroller and the UART that sends commands to the robocontroller using C, and the latter contains the code that programs the robocontroller using C++ and python. 

Steps to install the programs:
1. Download the project in [Microcontroller_Hand](https://github.com/Osestic/WidowX_Arm_HIWONDER_Bionic_Hand-Interface/tree/main/Microcontroller_Hand)/ and run it on Code Composer studio to install it on a Tiva C Series TM4C123G microcontroller.
2. Download the python project in the [Arm_Position_Capture](https://github.com/Osestic/WidowX_Arm_HIWONDER_Bionic_Hand-Interface/tree/main/Robocontroller_Arm/Arm_Position_Capture)/ folder contained in [Robocontroller_Arm](https://github.com/Osestic/WidowX_Arm_HIWONDER_Bionic_Hand-Interface/tree/main/Robocontroller_Arm)/ and run it on a Integrated Development Environment (IDE) or text editor that can support Python 2 such as Pycharm.
3. You may need to install a virtual interpreter for Python 2.
4. Run ```PyPose.py``` from the folder which will bring up the Arm position software.
5. Run ```pypose.ino``` on the robocontroller with Arduino 1.8.5 (Do so for all arduino files). This will work with the python software to capture the position of the robot arm by just moving it and pressing the capture button.
6. Run ```main.ino```, and do so with ```poses.h``` being in its same location. This contains the code that interfaces the robocontroller with the microcontroller. You can create more gestures and include the robot commands in it.

## Usage
To run the current capabilities of the WidowX_Arm_HIWONDER_Bionic_Hand-Interface, do the following:
1. Run the ```main.c``` of the project in Code Composer studio to install it on the microcontroller.
2. Run the ```main.ino```.
3. Type in a character that enacts a specific functionality as specificied in the ```main.c``` mentioned.

The following are pictures of the  WidowX_Arm_HIWONDER_Bionic_Hand-Interface in performing different hand positions.

- Playing the piano is shown below:

--put picture screenshitrand link to videi
[![IMAGE ALT TEXT HERE](https://img.youtu.be/7QV7U6zG5p0?si=95N4K1tDJaiDvBDxE/0.jpg)](https://youtu.be/7QV7U6zG5p0?si=95N4K1tDJaiDvBDx)

https://youtu.be/7QV7U6zG5p0?si=95N4K1tDJaiDvBDx

https://github.com/Osestic/MiDOK_Co-Pilot_App/assets/42704298/2c5c2102-06ed-4d42-a558-b406b375f8a7

https://youtu.be/7QV7U6zG5p0?si=95N4K1tDJaiDvBDx



The Android application demo:


https://github.com/Osestic/MiDOK_Co-Pilot_App/assets/42704298/7a2a0f87-c2e4-47b8-ab71-47bd31dc3c11


https://github.com/Osestic/MiDOK_Co-Pilot_App/assets/42704298/3a2e5abe-4d6a-426d-8236-740e5c12ba74


The web application demo:


https://github.com/Osestic/MiDOK_Co-Pilot_App/assets/42704298/207550aa-21fe-4337-9fe4-13ffdcf4254c



  
### Note
- The AI Python API response time is not as quick as the actual ChatGPT application
- It can take 10 - 60 seconds or more depending on the length/number of tokens of text sent to it
- Not all the buttons are functional, the demo shows those that work

  
## Authors
This project was a result of the collaborative effort of the following groups of persons and myself:
1. Oriekaose Chukwuyem Agholor - AI Python and UI/UX Developer [https://github.com/Osestic]
2. Eyimofe Oladipo - iOS Swift Application Developer 
3. Sarwar Nazrul - Android Kotlin Application Developer [http://github.com/Sarwarnazrul242]
4. Emmanuel Etukudoh - Website Developer [https://github.com/emmanuel-et]
5. Lukas Nilsen - Project, Customer and Market Researcher
6. Bilal Kachir - Graphics and Logo Designer


## License
This project is licensed under the “Commons Clause” License Condition v1.0. See ```LICENSE``` for more information.


## How to Contribute
[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-2.1-4baaaa.svg)](code_of_conduct.md)


## Recommendations
- Ensure you have a strong internet connection to improve the AI API connectivity
- Utilise a faster and more powerful server for quicker AI API response time (You may need to pay for this)
- Adapt the same layout and UI/UX to both the iOS and Android Application
- Allow other persons to use the apps and give feedback
- Act on the feedback accordingly

