function export_vircon(){
	let t_name = document.getElementById("time_variable").value;
	exported.innerHTML=""

	
	exported.innerHTML=`set_drawing_angle(${angle_offset}`
	
	if(keys.angle.length==1)exported.innerHTML+=");"

		for (i=1; i< keys.angle.length; i++){
			if(keys.angle[i].value!=0)
			exported.innerHTML+= 	`+ease(((${t_name}${(keys.angle[i].time>0)?"-":"+"}${Math.abs(keys.angle[i].time)})*${keys.angle[i].speed}),
									${keys.angle[i].ease_in}, ${keys.angle[i].ease_out})*${keys.angle[i].value}`

			if(i==keys.angle.length-1) exported.innerHTML+=");"
		}

		
		exported.innerHTML+=`<br>set_drawing_scale(${scale_x_offset}`
		if(keys.scale_x.length!=1){
			for (i=1; i< keys.scale_x.length; i++){
				if(keys.scale_x[i].value!=0)
				exported.innerHTML+= 	`+ease(((${t_name}${(keys.scale_x[i].time>0)?"-":"+"}${Math.abs(keys.scale_x[i].time)}) * ${keys.scale_x[i].speed}),
										${keys.scale_x[i].ease_in}, ${keys.scale_x[i].ease_out})*${keys.scale_x[i].value}`

				if(i==keys.scale_x.length-1) exported.innerHTML+=","
			}
		}else exported.innerHTML+=","


		exported.innerHTML+=`${scale_y_offset}`
		if(keys.scale_y.length!=1){
			for (i=1; i< keys.scale_y.length; i++){
				if(keys.scale_y[i].value!=0)
				exported.innerHTML+=	`+ease(((${t_name}${(keys.scale_y[i].time>0)?"-":"+"}${Math.abs(keys.scale_y[i].time)})*${keys.scale_y[i].speed}),
										${keys.scale_y[i].ease_in}, ${keys.scale_y[i].ease_out})*${keys.scale_y[i].value}`
				
				if(i==keys.scale_y.length-1) exported.innerHTML+=");"	
			}
		
		}else exported.innerHTML+=`);`;
		
	



		exported.innerHTML+=`<br>draw_region_rotozoomed_at(${x_offset}`
	

		if(keys.x.length!=1){
			for (i=1; i< keys.x.length; i++){
				if(keys.x[i].value!=0)
				exported.innerHTML+= 	`+ease(((${t_name}${(keys.x[i].time>0)?"-":"+"}${Math.abs(keys.x[i].time)})*${keys.x[i].speed}),
										${keys.x[i].ease_in}, ${keys.x[i].ease_out})*${keys.x[i].value}`
				
				if(i==keys.x.length-1) exported.innerHTML+=","

			}
		
		}else exported.innerHTML+=","

			exported.innerHTML+=`${y_offset}`

		if(keys.y.length!=1){

			for (i=1; i< keys.y.length; i++){
				if(keys.y[i].value!=0)
				exported.innerHTML+=	`+ease(((${t_name}${(keys.y[i].time>0)?"-":"+"}${Math.abs(keys.y[i].time)})*${keys.y[i].speed}),
										${keys.y[i].ease_in}, ${keys.y[i].ease_out})*${keys.y[i].value}`
				
				if(i==keys.y.length-1) exported.innerHTML+=");"
			}
		}else exported.innerHTML+=");"
	

	exported.innerHTML+= `</br>${t_name} +=  ${t_speed};`
	exported.style.display = "block"; // or "flex", "grid", etc. to show it
}