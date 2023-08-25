// программа следящего электропривода без обратной связи 

#include <TimerOne.h> 
#include <StepMotor.h> 

#define MEASURE_PERIOD 480 // время периода измерения (* 250 мкс) 
#define numStepsMotor 1900 // число шагов двигателя на оборот 

int timeCount; // счетчик времени 
long sumU; // переменные для суммирования кодов АЦП 
long averageU; // сумма кодов АЦП (среднее значение * 80) 
int currentStep; // текущее положение двигателя 
int setStep; // заданное положение двигателя 

StepMotor myMotor(8, 9, 10, 11); // создаем объект типа StepMotor, задаем выводы для фаз 

void setup() { 
Timer1.initialize(250); // инициализация таймера 1, период 250 мкс 
Timer1.attachInterrupt(timerInterrupt, 250); // обработчик прерываний 
myMotor.setMode(0, false); // шаговый режим, без фиксации при остановке 
myMotor.setDivider(15); // делитель частоты 15 
} 

void loop() { 
// проверка остановки двигателя 
if( myMotor.readSteps() == 0) { 
// двигатель остановился 

// вычисление заданного положения 
setStep = averageU * (numStepsMotor - 1) / 1023 / MEASURE_PERIOD; 

// определение сколько шагов надо сделать 
int stepsToDo; // сколько шагов надо сделать 

stepsToDo = currentStep - setStep; // ошибка рассогласования 

if( abs(stepsToDo) >= (numStepsMotor / 1) ) { 

if((stepsToDo) > 0) stepsToDo -= numStepsMotor; 
else stepsToDo += numStepsMotor; 
} 

myMotor.step(stepsToDo); // запуск двигателя 
currentStep = setStep; // перегрузка текущего положения 
} 
} 

//------------------------------------— обработчик прерывания 250 мкс 
void timerInterrupt() { 
myMotor.control(); // управвление двигателем 

sumU += analogRead(A0); // суммирование кодов АЦП zz
timeCount++; // +1 счетчик выборок усреднения 

// проверка числа выборок усреднения 
if ( timeCount >= MEASURE_PERIOD ) { 
timeCount= 0; 
averageU= sumU; // перегрузка среднего значения 
sumU= 0; 
} 
} 
