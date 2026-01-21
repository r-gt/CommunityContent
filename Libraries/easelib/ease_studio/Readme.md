![Ease Studio logo](https://files.catbox.moe/aeus61.png)

---

### What is Ease Studio?
Ease studio is a tool designed to create **complex concatenated easings** in cooperation with **easelib** for Vircon32 games, demos, bios, etc.


### What can it do?

Ease Studio offers:
- Keyframes timeline editor.
- Real time preview.
- Saving and loading projects.
- Exporting to Vircon.
- _Some_ Vircon code optimizations.

What Ease Studio won't do:
- Directly turn animation into v32 cart.
- Replace After Effects (probably)

---

# Instalation
 You _don't_ install Ease Studio as a normal program, instead you download studio.html file, or you can also download the source code (in the src folder), both ways are valid.  
 _you can also try it [here.](https://htmlpreview.github.io/?https://raw.githubusercontent.com/vircon32/CommunityContent/refs/heads/main/Libraries/easelib/ease_studio/studio.html)_


# Usage


### 1. ANIMATE
Start by making an animation with Ease Studio as you like.


### 2. EXPORT
After finishing your animation, you can export and use it on your code.


### INTO THE CARTRIDGE

#### 1. Include the libraries you need  
~~~c
#include "easings.h"
#include "video.h"
#include "time.h"
~~~

#### 2. define your region
~~~
void main(void){

    select_texture(0);
    select_region(0);
    define_region_center(0,0,31,31);

    // please change all these values depending on your needs. :p
}
~~~

#### 3. Paste the exported code into your loop

~~~
    while(1){
        clear_screen(color_black);

        set_drawing_angle(0);
        set_drawing_scale(1,1);
        draw_region_rotozoomed_at(320,180);
        t += 0.016666666666666666;

        end_frame();

    }

~~~

# Requirements
Ease Studio doesn't ask for much, only a decent web browser:
* Mozilla Firefox (tested, working)
* Chromium/Chrome (tested, working)
* WebKit/Safari (tested, mostly working)
* QT Web engine (tested, working)
* Netscape Navigator (tested, not working)

Ease Studio does not support touchscreens, this doesn't mean it won't work on phones, if you connect mouse and keyboard to your phone, you can use it.

Does timeline or preview look bad? try using 100% or 200% zoom, in between values might not look correctly.
  
<br/><br/>

_I know Ease Studio is not perfect, if you find issues or have suggestions, contact me! I'll be in the [Vircon 32 Discord server.](https://discord.gg/eEf3UKbJ9p)_

---

_made with Ɛ> by @Palta for everyone!
 under the_ [MIT License](https://opensource.org/license/mit)
