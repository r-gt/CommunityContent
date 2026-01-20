var view_canvas= document.getElementById("view");
var view = view_canvas.getContext('2d');


var timeline_canvas= document.getElementById("timeline");
var timeline = timeline_canvas.getContext('2d');


view.imageSmoothingEnabled = false;

var exported= document.getElementById("output");


var preview ={width:40, height:40} 

var t=0, t_speed=0.016666666666666666;
var x_offset=320, y_offset=180, scale_x_offset=1, scale_y_offset=1, angle_offset=0;
var play;


const key_track = () => [{
  time: 0, 
  speed: 1, 
  value: 0, 
  ease_in: "NONE", 
  ease_out: "NONE"
}];


const keys = {
  x: key_track(),
  y: key_track(),
  angle: key_track(),
  scale_x: key_track(),
  scale_y: key_track()
};


document.addEventListener('keydown', function(event) {
		
	if(event.code ==="Space"){
		event.preventDefault();
		if(play) play=false;
		else play=true;
	}

		if(event.code ==="Escape"){
		event.preventDefault();
		document.getElementById("show_project_panel").click();

	}
});


  timeline_canvas.addEventListener('contextmenu', function(event) {
	event.preventDefault();
  return false; // Extra safety measure
  });


  
document.getElementById("time_speed").addEventListener('input', (e) => {
	t_speed= 1/Number(e.target.value);
	save_project()
});

document.getElementById("box_width").addEventListener('input', (e) => {
	preview.width= Number(e.target.value);
	save_project();
});

document.getElementById("box_height").addEventListener('input', (e) => {
	preview.height= Number(e.target.value);
	save_project();
});


document.getElementById("x_offset").addEventListener('input', (e) => {
	x_offset= Number(e.target.value);
	save_project();
});

document.getElementById("y_offset").addEventListener('input', (e) => {
	y_offset= Number(e.target.value);
	save_project();
});


document.getElementById("scale_x_offset").addEventListener('input', (e) => {
	scale_x_offset= Number(e.target.value);
	save_project();
});

document.getElementById("scale_y_offset").addEventListener('input', (e) => {
	scale_y_offset= Number(e.target.value);
	save_project();
});


document.getElementById("angle_offset").addEventListener('input', (e) => {
	angle_offset= Number(e.target.value);
	save_project();
});




function toggle_project_panel() {


	if (document.getElementById("project_panel").style.display === "none") {
		document.getElementById("project_panel").style.display = "block";
		document.getElementById("instructions_panel").style.display = "none";

	} else {
		document.getElementById("project_panel").style.display = "none";
		exported.style.display = "none";

	}
}

function show_help() {

	
	if (document.getElementById("instructions_panel").style.display === "none") {
		document.getElementById("project_panel").style.display = "none";
		document.getElementById("instructions_panel").style.display = "block";
	} else {
		document.getElementById("instructions_panel").style.display = "none";
	}
}

function hide_all(){
			document.getElementById("project_panel").style.display = "none";
			document.getElementById("instructions_panel").style.display = "none";
			exported.style.display = "none";

}





window.addEventListener('keydown', function(e) {

	if ((e.ctrlKey || e.metaKey) && e.key === 'z' && !e.shiftKey) {
		e.preventDefault();
		window.history.back();
		// Reload after navigation completes
		setTimeout(() => {
			window.location.reload();
		}, 1);
	}

	else if ((e.ctrlKey || e.metaKey) && e.key === 'y') {
		e.preventDefault();
		window.history.forward();
		// Optional: reload after going forward too
		setTimeout(() => {
			window.location.reload();
		}, 1);
	}
});