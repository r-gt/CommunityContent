

function render_timeline(){
	
	
	if(!t_mouse.left || t_mouse.y<16){
		t_mouse_buffer.x = t_mouse.x;
		cursor_buffer.position = cursor.position;

	}
	
	
	if(cursor.follow){

		cursor.position=t*cursor.zoom-320;
	}else{
		cursor.position= -(t_mouse.x-t_mouse_buffer.x)+cursor_buffer.position;
	}
	//console.log(t_mouse, t_mouse_buffer, (t_mouse.x-t_mouse_buffer.x))

	
	
	timeline.save(); 
	
  		timeline.beginPath();
		timeline.fillStyle = "#11111B";
  		timeline.fillRect(0, 0, timeline_canvas.width, timeline_canvas.height);

		timeline.closePath();


// draw a line at 0,0			
		timeline.beginPath();

		timeline.lineWidth=6;
		timeline.strokeStyle="#6c7086";
		timeline.moveTo(- cursor.position, 0);
		timeline.lineTo(- cursor.position, timeline_canvas.height);
		timeline.stroke();

		timeline.closePath();





		timeline.beginPath();

		for(i=0; i< 640+cursor.zoom ; i+=cursor.zoom){

			timeline.moveTo(i- (cursor.position%cursor.zoom), 0);
			timeline.lineTo(i- (cursor.position%cursor.zoom), timeline_canvas.height);

			timeline.lineWidth = 1;
			timeline.strokeStyle="#181825";

			timeline.stroke();


		}
			timeline.fillStyle="#313244";
			timeline.fillRect(0,0,640,15)

		timeline.closePath();



// Draw all lines first
timeline.beginPath();
timeline.lineWidth = 4;
timeline.strokeStyle = "#313244";

for(i=0; i<5; i++){
    timeline.moveTo(0, 36+25*i);
    timeline.lineTo(timeline_canvas.width, 36+25*i);
}
timeline.stroke();

timeline.closePath();
	


	Object.values(keys).forEach((keyframes, index) => {

		for(let i = 1; i < keyframes.length; i++){
			
			const k = keyframes[i];

			timeline.beginPath();
			timeline.resetTransform();			
			timeline.lineWidth = 4;
		
			timeline.strokeStyle="#7f849c";
			timeline.moveTo(k.time*cursor.zoom-cursor.position, 36+25*index);
			timeline.lineTo((k.time*cursor.zoom-cursor.position)+cursor.zoom/k.speed, 36+25*index)
			
			timeline.stroke();
			
			timeline.closePath();

		}

		
		for(let i = 1; i < keyframes.length; i++){
		
			const k = keyframes[i];

			if(key_selected.position==i && key_selected.type==index) timeline.fillStyle = "#f9e2af"
			else timeline.fillStyle = "#fab387"
			
			timeline.beginPath();
			
			timeline.resetTransform();
			
			timeline.translate(k.time*cursor.zoom-cursor.position, 36+25*index);
			timeline.rotate(Math.PI/4);
			timeline.translate(-8, -8); 
			
			timeline.fillRect(0, 0, 16, 16);
			
			timeline.closePath();
		
		}
	});





	// draw timeline cursor 
	timeline.beginPath();
	timeline.resetTransform();
	timeline.moveTo(t*cursor.zoom - cursor.position, 0);
	timeline.lineTo(t*cursor.zoom - cursor.position, timeline_canvas.height);

	timeline.lineWidth = 2;
	
	timeline.strokeStyle="#f5e0dc";
	
	timeline.stroke();


	timeline.font = "16px Monospace";
	timeline.textAlign = "right";
	timeline.fillStyle = "#a6adc8";
	timeline.strokeStyle = "#11111b";
	timeline.lineWidth = 8;

	for(i=0; i<5; i++){
		let name;
		
		switch(i){
			case 0: name = "X"; break;
			case 1: name = "Y"; break;
			case 2: name = "Angle"; break;
			case 3: name = "Scale X"; break;
			case 4: name = "Scale Y"; break;
		}

		timeline.strokeText(name, timeline_canvas.width-10, 41+25*i);
	    timeline.fillText(name, timeline_canvas.width-10, 41+25*i);

	}


	timeline.closePath();



	timeline.restore();

		keyframe_selector();
	

requestAnimationFrame(render_timeline); 
}

requestAnimationFrame(render_timeline); 





let left_shift_pressed = false;
let a_key_pressed = false;

// Track Shift key state
addEventListener('keydown', (e) => {
	if (e.code === 'ShiftLeft') left_shift_pressed = true;
	
	if ((e.key === 'a' || e.key === 'A') && !a_key_pressed){
		Object.values(keys).forEach((keyframes, index) => {

		    	if(t_mouse.y < 25*(index)+46 && t_mouse.y > 20+25*index){
		    		
					keyframes.push({ time: ((t_mouse.x + cursor.position) / cursor.zoom), speed:1, value: 0, ease_in: "LINEAR", ease_out: "LINEAR" });
					
					key_selected.type = index;
					key_selected.position = keyframes.length-1;
						document.getElementById("time_in").value = keyframes[keyframes.length-1].time;
						document.getElementById("speed_in").value = keyframes[keyframes.length-1].speed;
						document.getElementById("value_in").value = keyframes[keyframes.length-1].value;
						document.getElementById("ease_in_select").value = keyframes[keyframes.length-1].ease_in;
						document.getElementById("ease_out_select").value = keyframes[keyframes.length-1].ease_out;
	
				}
			
			save_project();

		});

		a_key_pressed = true;
	}

	});

	addEventListener('keyup', (e) => {
	  if (e.code === 'ShiftLeft') left_shift_pressed = false;

	   if (e.key === 'a' || e.key === 'A')a_key_pressed = false;
		
	});

	// Single wheel listener that checks the Shift state
timeline_canvas.addEventListener("wheel", (wheel_event) => { 
	wheel_event.preventDefault(); // Prevents page scrolling
	
	if (left_shift_pressed) {
		
		if (wheel_event.deltaY > 0 && cursor.zoom>2) {
		    // Zooming out
		    cursor.position = ((t_mouse.x + cursor.position) / cursor.zoom) * (cursor.zoom - 2) - t_mouse.x;
		    cursor.zoom -= 2;
		    
		} else if (wheel_event.deltaY < 0) {
		    // Zooming in
		    cursor.position = ((t_mouse.x + cursor.position) / cursor.zoom) * (cursor.zoom + 2) - t_mouse.x;
		    cursor.zoom += 2;
		}


	} else {
		
		if (wheel_event.deltaY > 0)t -= t_speed;
		else if (wheel_event.deltaY < 0) t += t_speed;
	}
	
});



timeline_canvas.addEventListener('mousemove', (event) => {

	t_mouse.x = event.offsetX;
    t_mouse.y = event.offsetY;

});


timeline.canvas.addEventListener('mousedown', (event) => {

	t_mouse.left = (event.buttons === 1);
	t_mouse.middle = (event.buttons === 4);
	t_mouse.right = (event.buttons === 2);

});

addEventListener('mouseup', (event) => {

	t_mouse.left = (event.buttons === 1);
	t_mouse.middle = (event.buttons === 4);
	t_mouse.right = (event.buttons === 2);

});

