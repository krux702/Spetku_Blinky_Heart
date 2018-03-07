 
/* Spetku heart blinky do */

#include <SoftPWM.h>

#define TURN_ON_DELAY 800
#define TURN_OFF_DELAY 1100
#define NEXT_LED 90         
#define ON_OFF_WEIGHT 165    // between 0 - 255, lower means more leds turn on
#define LED_ON 75            // on led brightness
#define EFFECTS 9

#define NUM_LEDS 10
// define LEDs in a repeating array to simplify patterns
int leds[] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};

int weight = 170;

uint8_t last_rand_num = 0;
uint8_t rand_num = 0;

void setup()
{
  // seed based on analog pin 7
  randomSeed(analogRead(0));

  // Initialize soft PWM
  SoftPWMBegin();

  // Setup pins
  for(int i = 0 ; i < NUM_LEDS ; i++)
  {
    SoftPWMSet(leds[i], 0);
    SoftPWMSetFadeTime(leds[i], TURN_ON_DELAY, TURN_OFF_DELAY);
  }
}

void readTouch(long delaytime)
{
  long dc = 0;
  while(dc < delaytime)
  {
    dc = dc + 5;
    // read analog input 1
    if(digitalRead(15))
    {
        for(int i = 0 ; i < NUM_LEDS ; i++)
        {
          SoftPWMSetPercent(leds[i], LED_ON);
        }
        delay(TURN_ON_DELAY);
        for(int i = 0 ; i < NUM_LEDS ; i++)
        {
          SoftPWMSetPercent(leds[i], 5);
        }
        delay(TURN_OFF_DELAY);
    }
    delay(5);
  }
}

void loop()
{
  // pick a random number that doesn't match our last sequence
  while(rand_num == last_rand_num && rand_num < EFFECTS + 1)
  {
    rand_num = random(1, EFFECTS + 1);
  }
  last_rand_num = rand_num;

// for debugging  
//int  rand_num = 8;

  switch(rand_num) {
    case 1:

      // chase
      for(int n = 0 ; n < 5 ; n++)
      {
        for(int i = 0 ; i < NUM_LEDS ; i++)
        {
          SoftPWMSetPercent(leds[i+1], LED_ON);
          readTouch(TURN_ON_DELAY/3);
          SoftPWMSetPercent(leds[i], 0);
        }     
      }
      break;

    case 2:

      // fade up
      for(int n = 0 ; n < 4 ; n++)
      {
        for(int i = 0 ; i < NUM_LEDS ; i++)
        {
          SoftPWMSetPercent(leds[i], 0);
        }
        readTouch(TURN_OFF_DELAY);
        SoftPWMSetPercent(leds[0], LED_ON);
        readTouch(TURN_ON_DELAY/3);
        for(int i = 1 ; i < NUM_LEDS / 2 + 1 ; i++)
        {
          SoftPWMSetPercent(leds[i], LED_ON);
          SoftPWMSetPercent(leds[NUM_LEDS - i], LED_ON);
          readTouch(TURN_ON_DELAY/3);
        }
        readTouch(TURN_ON_DELAY/2);
      }  
      break;

    case 3:

      // pulse
      for(int n = 0 ; n < 4 ; n++)
      {
        for(int i = 0 ; i < NUM_LEDS ; i++)
        {
          SoftPWMSetPercent(leds[i], LED_ON);
        }
        readTouch(TURN_ON_DELAY);
        for(int i = 0 ; i < NUM_LEDS ; i++)
        {
          SoftPWMSetPercent(leds[i], 5);
        }
        readTouch(TURN_OFF_DELAY);
      }
      break;

    case 4:

      // twinkle
      for(int n = 0 ; n < 180 ; n++)
      {
        // choose random LED  
        uint8_t rand_num = random(NUM_LEDS);
        if(random(255) > ON_OFF_WEIGHT)
        {
          // turn a LED on
          SoftPWMSetPercent(leds[rand_num], LED_ON);
        }
        else
        {
          // turn a LED off
          SoftPWMSetPercent(leds[rand_num], 1);
        }
        readTouch(NEXT_LED);
      }
      break;
      
    case 5:
    
      /*
        7,8
        6,9
        5,0
        4,1
        3,2
      */
      // side sweep
      for(int n = 0; n < 3; n++)
      {
        int led1 = 7;
        int led2 = 8;    
    
        for(int i = 0; i < 5; i++)
        {
          SoftPWMSetPercent(leds[led1 + 1], 0);
          SoftPWMSetPercent(leds[led2 - 1], 0);
          SoftPWMSetPercent(leds[led1], LED_ON);
          SoftPWMSetPercent(leds[led2], LED_ON);
          readTouch(TURN_ON_DELAY/3);
          led1--;
          led2++;
        }
        SoftPWMSetPercent(leds[led1], 0);
        SoftPWMSetPercent(leds[led2], 0);
        readTouch(TURN_ON_DELAY/3);
      }   
      break;

    case 6:

      // fade up and down
      for(int n = 0 ; n < 4 ; n++)
      {
        for(int i = 0 ; i < NUM_LEDS ; i++)
        {
          SoftPWMSetPercent(leds[i], 0);
        }
        readTouch(TURN_OFF_DELAY);
        SoftPWMSetPercent(leds[0], LED_ON);
        readTouch(TURN_ON_DELAY/3);
        for(int i = 1 ; i < NUM_LEDS / 2 + 1 ; i++)
        {
          SoftPWMSetPercent(leds[i], LED_ON - (LED_ON/6 * i));
          SoftPWMSetPercent(leds[NUM_LEDS - i], LED_ON - (LED_ON/6 * i));
          readTouch(TURN_ON_DELAY/3);
        }
        readTouch(TURN_ON_DELAY/2);
      }  
      break;

    case 7:
        
      /*
      
        0,10
        1,9
        2,8
        3,7
        4,6
        5,5
      
      */

      // upward rolly fade do
      for(int n = 0 ; n < 4 ; n++)
      {
        int inc=2;
        for(int i = 0 ; i < 6 ; i++)
        {
          SoftPWMSetPercent(leds[i], inc );
          SoftPWMSetPercent(leds[10 - i], inc );
          inc = inc * 2;
          readTouch(TURN_ON_DELAY/((8-i+3)/2));
        }
        readTouch(TURN_ON_DELAY/4);

        for(int i = 5 ; i >= 0 ; i--)
        {
          SoftPWMSetPercent(leds[i], 0 );
          SoftPWMSetPercent(leds[10 - i], 0 );
          readTouch(TURN_ON_DELAY/(i+3));
        }
        readTouch(TURN_OFF_DELAY);

      }  
      break;

    case 8:
        
      /*
      
        0,10
        1,9
        2,8
        3,7
        4,6
        5,5
      
      */

      // upward rolly fade do
      for(int n = 0 ; n < 4 ; n++)
      {
        int inc=2;
        for(int i = 5 ; i >= 0 ; i--)
        {
          SoftPWMSetPercent(leds[i], inc );
          SoftPWMSetPercent(leds[10 - i], inc );
          inc = inc * 2;
          readTouch(TURN_ON_DELAY/((8-i+3)/2));
        }
        readTouch(TURN_ON_DELAY/4);

        for(int i = 0 ; i < 6 ; i++)
        {
          SoftPWMSetPercent(leds[i], 0 );
          SoftPWMSetPercent(leds[10 - i], 0 );
          readTouch(TURN_ON_DELAY/(i+3));
        }
        readTouch(TURN_OFF_DELAY);

      }  
      break;

    case 9:
    
      // two led bounce
      int led1 = 10;
      int led2 = 0;    
      int i=0;
      while(i < 40)
      {
        i++;

        led1++;
        if(led1 > 19)
        {
          led1 = 10;
        }

        led2--;
        if(led2 < 0)
        {
          led2 = 9;
        }

        SoftPWMSetPercent(leds[led1 - 1], 0);
        SoftPWMSetPercent(leds[led2 + 1], 0);
        SoftPWMSetPercent(leds[led1], LED_ON);
        SoftPWMSetPercent(leds[led2], LED_ON);
        readTouch(TURN_ON_DELAY/3);
      }
      break;


  }

  // turn leds off
  for(int i = 0 ; i < NUM_LEDS ; i++)
  {
    SoftPWMSetPercent(leds[i], 0);
  }
  readTouch(TURN_OFF_DELAY);

}

