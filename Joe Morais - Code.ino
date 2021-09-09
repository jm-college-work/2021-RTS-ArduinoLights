// Light 1 variables
int red_1 = 11;
int yellow_1 = 12;
int green_1 = 13;
int btn_1 = 10;

// Light 2 variables
int red_2 = 4;
int yellow_2 = 3;
int green_2 = 2;
int btn_2 = 5;

// Timer variables
int d = 0;
int _2s = 2000;
int _10s = 10000;
int _20s = 20000;
int _30s = 30000;
int light_1_max;
int light_2_max;

// Photoresistor variable
int photo_resistor = A0;

void setup() 
{   
    // Light 1 setup
    pinMode(red_1, OUTPUT);
    pinMode(yellow_1, OUTPUT);
    pinMode(green_1, OUTPUT);
    pinMode(btn_1, INPUT);

    // Light 2 setup
    pinMode(red_2, OUTPUT);
    pinMode(yellow_2, OUTPUT);
    pinMode(green_2, OUTPUT);  
    pinMode(btn_2, INPUT); 

    // Photo resistor setup
    pinMode(photo_resistor, INPUT);
}

void loop() 
{   
    // Check if daylight is detectable and set max values    
    if(analogRead(photo_resistor) > 100)        // Set day timers
    {
        light_1_max = _10s;
        light_2_max = _10s;
    }
    else                                        // Set night timers
    {
        light_1_max = _30s;
        light_2_max = _20s;
    }  
    
    light_1_green(light_1_max);                 // Set light 1 to green for max num of seconds
    light_1_yellow();                           // Set light 1 to yellow
    
    both_red();                                 // Set both lights to red
    
    light_2_green(light_2_max);                 // Set light 2 to green for max num of seconds
    light_2_yellow();                           // Set light 2 to yellow

    both_red();                                 // Set both lights to red
}

/*  Sets light 1 to green
 *  @param max_time the maximum time the light can stay green for (defined by photoresistor) */
void light_1_green(int max_time)
{   
    clear_all();                                // Clear all lights
    digitalWrite(green_1, HIGH);                // Light 1 green on
    digitalWrite(red_2, HIGH);                  // Light 2 red on 
    green_wait(btn_1, btn_2, max_time);         // Wait between 2s and max_time, while waiting for input
}

/*  Sets light 1 to yellow */
void light_1_yellow()
{    
    clear_all();                                // Clear all lights
    digitalWrite(yellow_1, HIGH);               // Light 1 yellow on
    digitalWrite(red_2, HIGH);                  // Light 2 red on
    delay(_2s);                                 // Wait 2s
}

/*  Sets light 2 to green
 *  @param max_time the maximum time the light can stay green for (defined by photoresistor) */
void light_2_green(int max_time)
{   
    clear_all();                                // Clear all lights
    digitalWrite(green_2, HIGH);                // Light 2 green on   
    digitalWrite(red_1, HIGH);                  // Light 1 red on
    green_wait(btn_2, btn_1, max_time);         // Wait between 2s and max_time, while waiting for input
}

/*  Sets light 2 to yellow */
void light_2_yellow()
{    
    clear_all();                                // Clear all lights
    digitalWrite(yellow_2, HIGH);               // Light 2 yellow on
    digitalWrite(red_1, HIGH);                  // Light 1 red on
    delay(_2s);                                 // Wait 2s
}

/*  Sets both lights to red */
void both_red()
{
    clear_all();                                // Clear all lights
    digitalWrite(red_1, HIGH);                  // Light 1 red on
    digitalWrite(red_2, HIGH);                  // Light 2 red on
    delay(_2s);                                 // Wait 2s
}

/*  Waits for a specific amount of time
 *  @param btn_this     the pin number for the button input for THIS traffic light
 *  @param btn_acrosss  the pin number for the button input for the OTHER traffic light
 *  @param max_time     the maximum time the light can stay green for (defined by photoresistor) */
void green_wait(int btn_this, int btn_across, int max_time)
{
    int timer = 0;                              // Create a timer counter
    while(true)                                 // Loop until break
    {  
        // If timer is greater than 2s, AND if THIS traffic light has no cars, AND if OTHER traffic lights has cars.
        if (timer >= _2s && digitalRead(btn_this) == LOW && digitalRead(btn_across) == HIGH)            
            break;  

        // If no buttons has been pressed, exit loop after max_time is reached
        if(timer >= max_time) 
            break; 
        
        delay(100);                             // Wait 100 milliseconds
        timer = timer + 100;                    // Increase timer counter by 100 milliseconds
    }
}

/*  Turns off all lights */
void clear_all()
{
    digitalWrite(green_1, LOW);
    digitalWrite(yellow_1, LOW);
    digitalWrite(red_1, LOW);

    digitalWrite(green_2, LOW);
    digitalWrite(yellow_2, LOW);
    digitalWrite(red_2, LOW);
}
