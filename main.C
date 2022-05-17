#include <main.h>
#include <stdio.h>

char buffer[4];
int i = 0;
int16 diz, unite;
boolean flag = 0;
int16 distMax = 100;
int16 dist, time  ;
int d, c,u;

#INT_TIMER1
void  TIMER1_isr(void) 
{
   set_timer1(0);


}
#int_RDA
void RDA_isr(void) 
{
   buffer[i] = getc();
    if(buffer[0] == ':' && flag == 0 ){
        i++;
        if(i>=4){
            i = 0;
            flag = 1;
        }
    }
 
}


void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_oscillator(False);
   
  
     while(true){
      
      // essayer de lire valeur du capteur
      output_high(pin_c1);
      delay_us(20);
      output_low(pin_c1);
      
      while(!input(pin_c0)){} //attendre que la pin echo soit HIGH
      
      set_timer1(0);
      
      while(input(pin_c0)){} //attendre que la pin echo soit HIGH
      time = get_timer1();               
      dist = time*0.028;  
      printf("La distance est : %ld \n" , dist);
      printf("\n\n");
      delay_ms(250);
    

      
      if(dist<100){
         output_high(PIN_E2);

      }else{
         output_low(PIN_E2);
         output_high(PIN_E1);
      }
      

      delay_ms(250);
     }

}