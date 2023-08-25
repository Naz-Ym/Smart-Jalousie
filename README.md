
# Short discription
Arduino is used as a central node that integrates peripheral system and is responsible for jalousie control. 
As a control unit, it has to process incoming data and use this data to drive actuators. 
Brightness of surroundings is read from photoresistor and then this data is used to control stepper motor. 
Photoresistor is polled every 250ms in order to minimize power consumption and to avoid motor bouncing. 
Position of a stepper motor is kept as a variable and is used to fluently and dynamically control jalousie. 
As a result, brightness of surroundings is directly mapped to the inclination angle of jalousie. 