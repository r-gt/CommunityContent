
function save_project(is_file=false){
let save ={x_offset, y_offset, t_speed, scale_x_offset, scale_y_offset, angle_offset, preview, keys, t};

	if(is_file){
	const blob = new Blob([JSON.stringify(save)], { type: 'application/json' });
  
	// Create a temporary URL for the blob
	const url = URL.createObjectURL(blob);
  
	// Create a temporary link element
	const a = document.createElement('a');
	a.href = url;
	a.download = "project";
  
	a.click();

	URL.revokeObjectURL(url);
	}else{

	const encoded = btoa(JSON.stringify(save));
	window.location.hash = encoded;
	}
}

function load_project(){


		const hash = window.location.hash.slice(1);
		if (!hash)return null;

		const load = JSON.parse(atob(hash));

	preview.width = load.preview.width;
	preview.height = load.preview.height;

	keys.x= load.keys.x;
	keys.y = load.keys.y;
	keys.angle = load.keys.angle;
	keys.scale_x = load.keys.scale_x;
	keys.scale_y = load.keys.scale_y;	
	
	t_speed = load.t_speed;
	t = load.t;
	document.getElementById("time_speed").value =1/load.t_speed;
	x_offset = document.getElementById("x_offset").value  = load.x_offset;
	y_offset = document.getElementById("y_offset").value = load.y_offset;
	scale_x_offset = document.getElementById("scale_x_offset").value = load.scale_x_offset;
	scale_y_offset = document.getElementById("scale_y_offset").value = load.scale_y_offset;
	angle_offset = document.getElementById("angle_offset").value = load.angle_offset;
	

}


document.getElementById('load').addEventListener('change', (event)=> {
  
	const file = event.target.files[0];
	if (file) {
	 	const reader = new FileReader();
	 	reader.onload = (e) => {
	    	const load = JSON.parse(e.target.result);
			
			preview.width = load.preview.width;
			preview.height = load.preview.height;

			keys.x= load.keys.x;
			keys.y = load.keys.y;
			keys.angle = load.keys.angle;
			keys.scale_x = load.keys.scale_x;
			keys.scale_y = load.keys.scale_y;	
			
			t_speed = load.t_speed;
			t = load.t;
			document.getElementById("time_speed").value =1/load.t_speed;
			
			x_offset = document.getElementById("x_offset").value  = load.x_offset;
			y_offset = document.getElementById("y_offset").value = load.y_offset;
			scale_x_offset = document.getElementById("scale_x_offset").value = load.scale_x_offset;
			scale_y_offset = document.getElementById("scale_y_offset").value = load.scale_y_offset;
			angle_offset = document.getElementById("angle_offset").value = load.angle_offset;

			save_project(); // updates url hash too

	  };

	  reader.readAsText(file);
	}


});


document.addEventListener('DOMContentLoaded', ()=> { load_project(); });