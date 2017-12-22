#include "Key_Switch.h"

void key_switch(void)
{
    switch(key_value)
    {
        case ON_OFF:
	    LED = White;
	    break;
        case Channel:
	    if(input_mode<3)
	    {
	    	LED = White;
	    }
	    if(input_mode == 3)
	    {
	    	LED = Blue;
	    }
	    if(input_mode == 4)
	    {
	    	LED = Red;
	    }
	    if(input_mode == 5)
	    {
	    	LED = Green;
	    }
	    break;
        case VOL_A:
	    LED = Twinkle;
	    break;
	case VOL_B:
	    LED = Twinkle;
	    break;
	case BASS_A:
	    LED = Twinkle;
	    break;
	case BASS_B:
	    LED = Twinkle;
	    break;
	case TREBLE_A:
	    LED = Twinkle;
	    break;
	case TREBLE_B:
	    LED = Twinkle;
	    break;
	case MUTE:
	    LED = Twinkle;
	    break;
	case PLAY_PAUSE:
	    LED = Twinkle;
	    break;
	case BLUETOOTH:
	    LED = Twinkle;
	    break;
	default:
	    break;
    }
    LED_Task(LED);
}
