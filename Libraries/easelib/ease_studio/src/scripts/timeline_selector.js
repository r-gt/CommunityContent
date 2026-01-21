let cursor={position:-32, zoom:32, follow:false};
let t_mouse = {x:0,y:0, left:false, middle:false, right:false};

let cursor_buffer={position:0, zoom:30};
let t_mouse_buffer={x:0,y:0, left:false};


var key_selected = {type:0, position:1};

key_selected.type=null;
key_selected.position=null;

// Update in real time as user types

document.getElementById("time_in").addEventListener('input', (e) => {
	Object.values(keys)[key_selected.type][key_selected.position].time = Number(e.target.value);
	save_project();
 
});

document.getElementById("speed_in").addEventListener('input', (e) => {
	Object.values(keys)[key_selected.type][key_selected.position].speed = Number(e.target.value);
 	save_project();

});

document.getElementById("value_in").addEventListener('input', (e) => {
	Object.values(keys)[key_selected.type][key_selected.position].value = Number(e.target.value);
	save_project();
	
});

document.getElementById("ease_in_select").addEventListener('input', (e) => {
	Object.values(keys)[key_selected.type][key_selected.position].ease_in = e.target.value;
	save_project();
	
});

document.getElementById("ease_out_select").addEventListener('input', (e) => {
	Object.values(keys)[key_selected.type][key_selected.position].ease_out = e.target.value;
	save_project();
	
});





function keyframe_selector(){

			if(t_mouse.y < 16 && t_mouse.left){

				t=(t_mouse.x+cursor.position)/cursor.zoom;
			
			}

	
	Object.values(keys).forEach((keyframes, index) => {

		for(let i = 1; i < keyframes.length; i++){
			const k = keyframes[i];

		    
		    if(t_mouse.y < 25*(index)+46 && t_mouse.y > 20+25*index){
		    	if(t_mouse.x > k.time*cursor.zoom-cursor.position-10 && t_mouse.x < k.time*cursor.zoom-cursor.position+10){
		        
					if(t_mouse.left ){
						key_selected.type = index;
						key_selected.position = i;
						document.getElementById("time_in").value = k.time;
						document.getElementById("speed_in").value = k.speed;
						document.getElementById("value_in").value = k.value;
						document.getElementById("ease_in_select").value = k.ease_in;
						document.getElementById("ease_out_select").value = k.ease_out;
		    	
					}else if(t_mouse.right){

						keyframes.splice(i,1); //remove keyframe!!!
						
						key_selected.type = undefined;
						key_selected.position = undefined;

						document.getElementById("time_in").value = undefined;
						document.getElementById("speed_in").value = undefined;
						document.getElementById("value_in").value = undefined;
						document.getElementById("ease_in_select").value = undefined;
						document.getElementById("ease_out_select").value = undefined;
						save_project();

						
					}
				}
		    
			}
			
		}
		
	});

}


