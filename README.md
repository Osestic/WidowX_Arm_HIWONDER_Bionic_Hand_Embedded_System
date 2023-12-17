# WidowX_Arm_HIWONDER_Bionic_Hand-Interface </h2>


<img src="https://github.com/Osestic/WidowX_Arm_HIWONDER_Bionic_Hand-Interface/assets/42704298/25f37eee-65a8-4e1e-a7c2-306f3ad84e96" width="300"/>

Evan Varga [Evan Varga](https://www.linkedin.com/in/evan-varga-2a21aa221/)) and I embarked on integrating a WidowX Robotic Arm controlled by an Arbotix - M Arduino with a robotic hand controlled by a Tiva C Series TM4C123G microcontroller. Through the micrcontroller's Universal Asynchronous Receiver-Transmitter module, commands were sent to the microcontroller to make the hand and arm perform creative gestures and actions.


## Description

In today's healthcare landscape, we're facing unprecedented challenges. 
The nursing shortage and an alarming rise in professional burnout have put strains on our healthcare system. 
Our team is proud to present MiDOK, an innovative AI-powered diagnostic co-pilot application designed specifically to support and enhance the capabilities of healthcare professionals and individuals training to join the healthcare field.

MiDOK utilizes a unique AI-prompting mechanism.
Through a series of button-based selections and checkboxes, healthcare professionals can narrow down a vast spectrum of medical conditions, receiving targeted lists of potential diagnoses. 
This precision ensures that the suggestions offered are both relevant and accurate.

It's important to understand that MiDOK isn't intended to replace the expertise of our doctors and nurses. 
Instead, it offers a supplementary tool to aid in the diagnosis process. 
By presenting an array of potential diagnoses based on the input data, MiDOK gives doctors more information.
We also understand the importance of accessibility in today's fast-paced world. 
That's why we've made MiDOK available across various platforms. We have the app for both Apple and Android devices as well as the web, making MiDOK readily available at your fingertips.

Beyond MiDOK’s healthcare application, it also emerges as a tool for individuals training to join the healthcare field. MiDOK simplifies the learning curve of healthcare schooling by offering AI-driven insights into potential diagnoses based on patient symptoms and data. 
Trainees can compare their assessments with MiDOK's suggestions, facilitating a hands-on learning experience that's informative. By simulating real-world scenarios, MiDOK builds confidence in making decisions. 
It's not just a tool for current healthcare professionals but it's also ensuring a more informed and prepared next generation of medical experts.

In essence, MiDOK represents a harmonious fusion of advanced artificial intelligence technology and medical expertise.
By bridging the gap between these two worlds, we aim to provide a solution that ensures every patient receives timely, accurate, and efficient care, even in the face of the ongoing challenges in our healthcare system.


## Built With
![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![ChatGPT](https://img.shields.io/badge/chatGPT-74aa9c?style=for-the-badge&logo=openai&logoColor=white)
![Swift](https://img.shields.io/badge/swift-F54A2A?style=for-the-badge&logo=swift&logoColor=white)
![Kotlin](https://img.shields.io/badge/kotlin-%237F52FF.svg?style=for-the-badge&logo=kotlin&logoColor=white)
![HTML5](https://img.shields.io/badge/html5-%23E34F26.svg?style=for-the-badge&logo=html5&logoColor=white)
![CSS3](https://img.shields.io/badge/css3-%231572B6.svg?style=for-the-badge&logo=css3&logoColor=white)
![TypeScript](https://img.shields.io/badge/typescript-%23007ACC.svg?style=for-the-badge&logo=typescript&logoColor=white)


## Installation
There are three different folders containing the projects for the iOS version and Android version of the app respectively.
- Ios application: Run the Swift project contained in ```Ios_app/```
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

