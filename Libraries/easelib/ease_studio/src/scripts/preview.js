

  
setInterval(function(){

	let values = {
	  x: x_offset,
	  y: y_offset,
	  angle: angle_offset,
	  scale_x: scale_x_offset,
	  scale_y: scale_y_offset
	};

	for(const [prop, keyframes] of Object.entries(keys)){
	  for(let i = 0; i < keyframes.length; i++){
	    const k = keyframes[i];
	    values[prop] += ease((t - k.time) * k.speed, k.ease_in, k.ease_out) * k.value;
	  }
	}



	//once calulated, is time to draw everything

	view.save(); 

 	view.beginPath();
	view.fillStyle = "#11111B"; // Set the desired color
  	view.fillRect(0, 0, view_canvas.width, view_canvas.height);
	view.closePath();


	view.beginPath();
	view.lineWidth=1;
	view.strokeStyle="#181825";
	
	for(x=0; x<320;x+=20){

		view.moveTo(0, x);
		view.lineTo(640,x);
		view.stroke();
	}

	for(y=0; y<640;y+=20){

		view.moveTo(y, 0);
		view.lineTo(y,320);
		view.stroke();
	}

	view.closePath();



	view.beginPath();

	view.strokeStyle="#a6e3a1";

	view.translate(values.x, values.y);
	view.rotate(values.angle);
	view.scale(values.scale_x, values.scale_y);

	view.lineWidth = 4;
	view.strokeRect(-preview.width/2, -preview.height/2, preview.width, preview.height);
	view.closePath();



	view.beginPath();
	view.moveTo(0, 0); // center point
	view.lineTo(0, -preview.height/2); // top border
	view.stroke();
	view.closePath()

	view.restore();
	if(play==true) t+=t_speed;



},16.666666666666668)