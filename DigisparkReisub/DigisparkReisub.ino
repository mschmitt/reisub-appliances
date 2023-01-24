#include "DigiKeyboard.h"

// USB HID Scan code for SysRq
#define SYSRQ 0x46 

#define LED 1

/*
Sketch for the Digispark to send REISUB emergency boot sequence
to a Linux host. 

##### To develop and/or test this on Linux, by all means disable #####
##### the SysRq invocations used by this sketch:                 #####

- sudo sysctl kernel.sysrq=256 
- Kernel will print warning messages only. -> dmesg -w

Reading materials:

- https://www.kernel.org/doc/html/latest/admin-guide/sysrq.html
- https://digistump.com/board/index.php/topic,2839.0.html
- https://github.com/digistump/DigistumpArduino/blob/master/digistump-avr/libraries/DigisparkKeyboard/DigiKeyboard.h
- https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
- https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
- Previous link is super misguiding, but helps when looking at showkey -s
- SHOWKEY(1)

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.
*/


void magicSysRq(int key){
  digitalWrite (LED, HIGH);
  DigiKeyboard.update();

  // This is where the pressing happens
  DigiKeyboard.sendKeyPress(SYSRQ, MOD_ALT_LEFT);
  DigiKeyboard.sendKeyPress(key, MOD_ALT_LEFT);
  DigiKeyboard.sendKeyPress(0, 0);
  
  DigiKeyboard.delay(500);
  digitalWrite(LED, LOW);
}

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  DigiKeyboard.delay(1000);

  magicSysRq(KEY_R);            // R = unraw
  DigiKeyboard.delay(1000);
  magicSysRq(KEY_E);            // E = SIGTERM all
  DigiKeyboard.delay(1000);
  magicSysRq(KEY_I);            // I = SIGKILL all
  DigiKeyboard.delay(1000);
  magicSysRq(KEY_S);            // S = Emergency FS sync
  DigiKeyboard.delay(5000);
  magicSysRq(KEY_U);            // U = Remount all read-only
  DigiKeyboard.delay(5000);
  magicSysRq(KEY_B);            // B = Reboot
  digitalWrite (LED, HIGH);
}

void loop() {
  // nothing
}
