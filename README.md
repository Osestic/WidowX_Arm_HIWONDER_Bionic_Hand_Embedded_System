# WidowX_Arm_HIWONDER_Bionic_Hand-Interface </h2>


<img src="https://github.com/Osestic/WidowX_Arm_HIWONDER_Bionic_Hand-Interface/assets/42704298/25f37eee-65a8-4e1e-a7c2-306f3ad84e96" width="300"/>

## Description
For our Introduction to Microcontrollers course final project, [Evan Varga](https://www.linkedin.com/in/evan-varga-2a21aa221/) and I embarked on integrating a WidowX Robotic Arm controlled with an Arbotix - M Arduino, a robocontroller, with a HIWONDER Bionic hand controlled by a Tiva C Series TM4C123G microcontroller to perform various hand and arm gestures, play a game and play an instrument. 

Through the microcontroller's Universal Asynchronous Receiver-Transmitter module, commands can be sent to the microcontroller to cause the fingers of the HIWOnDER bionic hand to move into certain positions through pulse-width modulations. These commands cause digital signals to be sent through parallel communication to the Arbotix -M robotcontroller. These signals make the WidowX arm move into certain position or perform sequences of positions. All these working together lead to creative gestures and actions being performed.


## Built With

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)


## Installation
There are 2 different folders containing the two major pieces of the project..
- Ios application: Run the Swift project contained in [Microcontroller_Hand](https://github.com/Osestic/WidowX_Arm_HIWONDER_Bionic_Hand-Interface/tree/main/Microcontroller_Hand)/
- Android application: Run the Kotlin project contained in ```Android_app/src```
- Web application: Run the project contained in ```Web_app/```

These applications have to be connected to the AI API for the application. They are currently connected to our own Python API. 

To create yours: 
- Place the ```start_api.py```, ```MiDOK_Python_AI_API.py``` and the ```requirements.txt``` in your own
GitHub repository
- Connect the repository to a free API hosting site like [https://render.com/], which is what we used
- Replace the link to our API in both the Swift and Kotlin code with your API link provided by the hosting
- Create an OpenAI account and generate an API key for you to use for the Python API
- Ensure you use environment variables to prevent your key from being exposed


## Usage
Run the applications and provide any relevant information as you click through the app and interact with it.

The iOS application demo:


https://github.com/Osestic/MiDOK_Co-Pilot_App/assets/42704298/2c5c2102-06ed-4d42-a558-b406b375f8a7





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

