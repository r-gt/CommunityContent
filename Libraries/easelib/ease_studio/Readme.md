![Ease Studio logo](src/logo.png)

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



# Usage


### 1. ANIMATE
Start by making an animation with Ease Studio as you like.


### 2. EXPORT
after finishing your animation, you can export and use it on your code.


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


_I know Ease Studio is not perfect, if you find issues or have suggestions, contact me! I'll me in the [Vircon 32 Discord server.](https://discord.gg/eEf3UKbJ9p)_

---

_made with Ɛ> by @Palta for everyone!
 under the_ [MIT License](https://opensource.org/license/mit)
