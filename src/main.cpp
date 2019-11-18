#include <arduino.h>
#include "IRremote.h"
#include "HID-Project.h"
#include "Keymap.h"

int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);

decode_results results;

struct RemoteKeyMap {
  uint32_t        IRcode;
  KeyboardKeycode keyCode;
};

// reference: https://kodi.wiki/view/Keyboard_controls
const RemoteKeyMap keyMap[] = {
{ IR_VOL_UP ,KEY_VOLUME_UP },
{ IR_VOL_UP_ALT  ,KEY_VOLUME_UP },
{ IR_VOL_UP_ALT_1  ,KEY_VOLUME_UP },

{ IR_VOL_DOWN ,KEY_VOLUME_DOWN },
{ IR_VOL_DOWN_ALT  ,KEY_VOLUME_DOWN },
{ IR_VOL_DOWN_ALT_1  ,KEY_VOLUME_DOWN },

{ IR_MEDIA_PAUSE ,KEY_SPACE },
{ IR_MEDIA_PAUSE_ALT  ,KEY_SPACE },
{ IR_MEDIA_PAUSE_ALT_1  ,KEY_SPACE },

{ IR_MEDIA_PLAY ,KEY_P },
{ IR_MEDIA_PLAY_ALT  ,KEY_P },
{ IR_MEDIA_PLAY_ALT_1  ,KEY_P },

{ IR_MEDIA_STOP ,KEY_X },
{ IR_MEDIA_STOP_ALT  ,KEY_X },
{ IR_MEDIA_STOP_ALT_1  ,KEY_X },

{ IR_KEY_LEFT_ARROW ,KEY_LEFT_ARROW },
{ IR_KEY_LEFT_ARROW_ALT ,KEY_LEFT_ARROW },
{ IR_KEY_LEFT_ARROW_ALT_1  ,KEY_LEFT_ARROW },
{ IR_KEY_LEFT_ARROW_ALT_2  ,KEY_LEFT_ARROW },

{ IR_KEY_RIGHT_ARROW ,KEY_RIGHT_ARROW },
{ IR_KEY_RIGHT_ARROW_ALT ,KEY_RIGHT_ARROW },
{ IR_KEY_RIGHT_ARROW_ALT_1  ,KEY_RIGHT_ARROW },
{ IR_KEY_RIGHT_ARROW_ALT_2  ,KEY_RIGHT_ARROW },

{ IR_KEY_UP_ARROW ,KEY_UP_ARROW },
{ IR_KEY_UP_ARROW_ALT ,KEY_UP_ARROW },
{ IR_KEY_UP_ARROW_ALT_1  ,KEY_UP_ARROW },
{ IR_KEY_UP_ARROW_ALT_2  ,KEY_UP_ARROW },

{ IR_KEY_DOWN_ARROW ,KEY_DOWN_ARROW },
{ IR_KEY_DOWN_ARROW_ALT ,KEY_DOWN_ARROW },
{ IR_KEY_DOWN_ARROW_ALT_1  ,KEY_DOWN_ARROW },
{ IR_KEY_DOWN_ARROW_ALT_2  ,KEY_DOWN_ARROW },

{ IR_KEY_OK ,KEY_RETURN },
{ IR_KEY_OK_ALT  ,KEY_RETURN },
{ IR_KEY_OK_ALT_1  ,KEY_RETURN },

{ IR_KEY_BACK ,KEY_BACKSPACE },
{ IR_KEY_BACK_ALT  ,KEY_BACKSPACE },
{ IR_KEY_BACK_ALT_1  ,KEY_BACKSPACE },

{ IR_KEY_EXIT ,KEY_ESC },

{ IR_KEY_REWIND ,KEY_R },
{ IR_KEY_REWIND_ALT  ,KEY_R },
{ IR_KEY_REWIND_ALT_1  ,KEY_R },

{ IR_KEY_FOWARD ,KEY_F },
{ IR_KEY_FOWARD_ALT  ,KEY_F },
{ IR_KEY_FOWARD_ALT_1 ,KEY_F }
};

const int keyMapSize = sizeof(keyMap) / sizeof(RemoteKeyMap);
const long interval = 100;    
unsigned long previousMillis = 0; 

void setup()
{
  // Serial.begin(9600);
  irrecv.enableIRIn();
  BootKeyboard.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  // simple debounce
  if (currentMillis - previousMillis >= interval) {
    if (irrecv.decode(&results)) {
      // Serial.print("0x");
      // Serial.println(results.value, HEX);
      previousMillis = currentMillis;
      for (int i = 0; i < keyMapSize; i++) {
        if (keyMap[i].IRcode == results.value) {
          BootKeyboard.press(keyMap[i].keyCode);              
          break;
        }
      }
    }  
  } else {
    BootKeyboard.releaseAll();
    irrecv.resume();
  }
}