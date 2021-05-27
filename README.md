# Mass Effect Camera Motion Calculator
This is a small tool to automatically calculate the positional and rotational values for a matinee camera at any given number of time points between the start and end of its motion, across multiple InterpDatas.
<p>The calculated results are for smooth, uninterrupted, linear camera motion between its start and end times.</p>

## Usage
Double-click _MECamCalc.exe_. A terminal window will be opened.
<p>On the opened terminal, you'll be prompted to input the required information to calculate the values. This is what normal usage would look like:</p>

```
How many InterpDatas does the camera movement span? 4
InterpData 1 length in seconds: 5 
At what time in InterpData 1 does the movement begin? 3.75
InterpData 2 length in seconds: 4.16 
InterpData 3 length in seconds: 2.1 
InterpData 4 length in seconds: 7.212 
At what time in InterpData 4 does the movement end? 4.4
Starting position as comma separated values (x,y,z): -2391.71, -51000.11, 1431.7
Starting rotation as comma separated values (x,y,z): 0, 19.1693, -117.4392
Ending position as comma separated values (x,y,z): -2408.41, -51032.3, 1444.4
Ending rotation as comma separated values (x,y,z): 0, 25.35, -113.74
For how many time points do you want to calculate values? 3
In which InterpData (1 to n) does time point 1 happen? 1
At what time of it does time point 1 happen? 5
In which InterpData (1 to n) does time point 2 happen? 3
At what time of it does time point 2 happen? 0.75
In which InterpData (1 to n) does time point 3 happen? 4
At what time of it does time point 3 happen? 0
```
After this, the results will be:

```
STARTING POINT
InterpData 1, at time 3.75
----------------------------
Position: -2391.71 -51000.11 1431.70
Rotation: 0.00 19.17 -117.44

TIME POINT 1:
InterpData 1, at time 5.00
----------------------------
Position: -2393.46 -51003.49 1433.03
Rotation: 0.00 19.82 -117.05

TIME POINT 2:
InterpData 3, at time 0.75
----------------------------
Position: -2400.35 -51016.76 1438.27
Rotation: 0.00 22.37 -115.53

TIME POINT 3:
InterpData 4, at time 0.00
----------------------------
Position: -2402.24 -51020.41 1439.71
Rotation: 0.00 23.07 -115.11

ENDING POINT
InterpData 4, at time 4.40
----------------------------
Position: -2408.41 -51032.30 1444.40
Rotation: 0.00 25.35 -113.74

Press Enter to exit the program
```

## Important
As version 1.0.2, the input is not validated. However, there should be no issues as long as you input numerical values when prompted.