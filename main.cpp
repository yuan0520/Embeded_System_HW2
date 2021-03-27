#include "mbed.h"

// Initialize a pins to perform analog and digital output functions
// Adjust analog output pin name to your board spec.
AnalogOut  aout(PA_4);
DigitalOut dout(LED1);
AnalogIn ain(PA_5);

int sample = 1000;
float ADCdata[1500];

int main(void)
{
   float freq_scale = 0.25; // when we use AnalogIn, it should be (input freq/100)
   float wavelength_scale = 1 / freq_scale;
   float up_len = 1.0 / 6.0;
   float down_len = 1.0 / 4.0;

   int idx = 0;
   int base = 30;
   int flag = 0;

   while (1) {
      // change the voltage on the digital output pin by 0.1 * VCC
      //  and print what the measured voltage should be (assuming VCC = 3.3v)
      for (float i = 0.0f; i < wavelength_scale; i += up_len) {
            aout = i * freq_scale;

            if(idx < sample){
                ADCdata[idx++] = ain;
            }
            ThisThread::sleep_for(1ms);
      }
      for (float j = wavelength_scale; j > 0.0f; j -= down_len){
            aout = j * freq_scale;

            if(idx < sample){
                ADCdata[idx++] = ain;
            }
            ThisThread::sleep_for(1ms);
      }

      if(idx >= sample && !flag){
          for(int i=0; i<sample; i++){
            //   printf("idx = %d", i);
              printf("%f\r\n", ADCdata[i]);
          }
          flag = 1;
        //   ThisThread::sleep_for(10ms); 
      }
   }
}