#ifndef POSES
#define POSES

#include <avr/pgmspace.h>

//Info
//Positions relative to robot placed with its power cable facing ones left and the base serving as its support
//Positions of Id 3 -6 is relative to Id 2 being upright.
//Id: Servo
//Note: Servos could beyond the maximum and minimum values specified below. Determine ones desired motion based on already specified motions and ranges
//Do not cause robot to hit itself or any object. It may cause servos to be unresponsive. In such a scenario, disconenct the robot's USB cable and power cable, then plug back in and continue.
//Id 1: Rotating joint before Id2,  
//      Position in Radians:  Min - max: Anti-clockwise
//                           -pi/2: 1048
//                           0: 2048 
//                           pi/2: 3070
//                           pi:   5000
//Id 2: Horizontal moving joint before Id3, 1050 - 3050, pointing leftwards to point rightwards
//      Vertical position:   2048
//
//Id 3: Vertical moving joint before Id4, 1050 - 3070, pointing downwards to point upwards
//      Horizontal position: 2048
//
//Id 4: Vertical moving joint before Id5, 1050 - 3050, pointing downwards to point upwards, 
//      Horizontal position: 2048 
//
//Id 5: Rotating joint before Id6, 0 - 2048, smaller value - higher value (Anti-clockwise), higher value- smaller value (Clockwise), 
//      Rotate to:
//                Gripper Horizontal: 512
//                Gripper vertical: 205, 815
//
//Id 6: Jaw, 0 - 2048, minimum to maximum opening
//                         
PROGMEM const uint16_t Center[] = {6, 2048, 2048, 2048, 2048, 512, 512};
PROGMEM const uint16_t Home[] = {6,2033, 1698, 1448, 2336, 512, 512};


//7770 puts arm in the right position


//Spiderman
const PROGMEM uint16_t Wave_pos_3[] = {6, 1729, 1476, 1891, 2065, 526, 502};
const PROGMEM uint16_t Spiderman_pos_10[] = {6, 1564, 1077, 1138, 2016, 547, 105};
const PROGMEM uint16_t Wave_pos_1[] = {6, 1709, 1749, 2145, 3100, 526, 502};
const PROGMEM uint16_t Spiderman_pos_4[] = {6, 1437, 1692, 2095, 2402, 765, 136};
const PROGMEM uint16_t Spiderman_pos_5[] = {6, 1481, 1668, 2207, 2564, 630, 128};
const PROGMEM uint16_t Spiderman_pos_6[] = {6, 1501, 1688, 2445, 2754, 546, 97};
const PROGMEM uint16_t Spiderman_pos_7[] = {6, 1553, 1594, 1967, 2427, 546, 98};
const PROGMEM uint16_t r_p_sci_pos_2[] = {6, 1463, 1183, 1528, 2131, 467, 496};
const PROGMEM uint16_t Spiderman_pos_1[] = {6, 1354, 1338, 1446, 2121, 798, 485};
const PROGMEM uint16_t Spiderman_pos_2[] = {6, 1391, 1314, 1551, 2395, 800, 481};
const PROGMEM uint16_t r_p_sci_pos_3[] = {6, 1465, 1520, 1995, 2477, 468, 496};
const PROGMEM uint16_t Wave_pos_2[] = {6, 1704, 1712, 2103, 2597, 528, 502};
const PROGMEM uint16_t Spiderman_pos_3[] = {6, 1356, 1656, 1999, 2196, 944, 224};
const PROGMEM uint16_t Spiderman_pos_8[] = {6, 1629, 1341, 1557, 2158, 545, 97};
const PROGMEM uint16_t r_p_sci_pos_1[] = {6, 1396, 1188, 1255, 2180, 480, 497};
const PROGMEM uint16_t Spiderman_pos_9[] = {6, 1610, 1344, 1338, 2234, 547, 105};


const PROGMEM uint16_t Piano_step1[] = {6, 1131, 2133, 3336, 1563, 526, 745};

const PROGMEM uint16_t Piano_step4[] = {6, 1201, 1490, 1237, 2355, 525, 745};

const PROGMEM uint16_t Piano_step2[] = {6, 1106, 1802, 2417, 1653, 525, 745};
//Piano player

const PROGMEM uint16_t Piano_step3[] = {6, 1175, 1495, 1479, 2216, 525, 745};

const PROGMEM uint16_t Piano_home[] = {6, 1148, 2262, 3287, 2291, 528, 746};

const PROGMEM uint16_t Piano_begin[] = {6, 1398, 1501, 1109, 2105, 610, 671};

const PROGMEM transition_t Piano_player[] = {{0,6} ,{Piano_home,1000} ,{Piano_step1,1000} ,{Piano_step2,1000} ,{Piano_step3,1000} ,{Piano_step4,1000} ,{Piano_begin,1000} };


const PROGMEM transition_t Spiderman[] = {{0,9} ,{Spiderman_pos_1,350} ,{Spiderman_pos_2,350} ,{Spiderman_pos_3,350} ,{Spiderman_pos_4,350} ,{Spiderman_pos_5,350} ,{Spiderman_pos_6,350} ,{Spiderman_pos_7,350} ,{Spiderman_pos_9,350} ,{Spiderman_pos_10,350} };
const PROGMEM transition_t Wave_improved[] = {{0,4} ,{Wave_pos_1,500} ,{Wave_pos_2,500} ,{Wave_pos_3,500} ,{Wave_pos_2,500} };
//const PROGMEM transition_t Rock/Paper/Scissors[] = {{0,3} ,{r_p_sci_pos_1,350} ,{r_p_sci_pos_2,350} ,{r_p_sci_pos_3,350} };
const PROGMEM transition_t Wave[] = {{0,3} ,{Wave_pos_1,500} ,{Wave_pos_2,500} ,{Wave_pos_1,500} };



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
#endif


