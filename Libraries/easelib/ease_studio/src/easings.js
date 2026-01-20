let c1=1.70158
let c3=2.70158

function ease(time, ease_in, ease_out){

	let t, eased;

	// these two are used to limit the easing to a normalized float (from 0 to 1)
	// and apparently these help with optimizations too
	if (time <= 0.0) return 0.0;
	else if (time >= 1.0 || (ease_in=="NONE" && ease_out=="NONE")) return 1.0;


	if(time < 0.5 || ease_out=="NONE"){
		// First half: ease in
		if(ease_out=="NONE") t = time;
		else t = time * 2.0;


		if (ease_in == "LINEAR") {
			eased = t;


		}
		if(ease_in !== "NONE"){
			switch(ease_in){

				case "SINE": eased = 1.0 - Math.cos((t * Math.PI) / 2.0); break;

				case "CUBIC": eased = t*t*t; break;

				case "QUINT": eased = t*t*t*t*t; break;

				case "CIRC": eased = 1.0 - Math.sqrt(1.0 - t*t); break;

				case "BACK": eased = c3 * t*t*t - c1 * t*t; break;

			}
			if(ease_out == "NONE") return eased;
			else return eased * 0.5;
		}
		
	}

	if(time >=0.5 || ease_in=="NONE"){

		// Second half: ease out
		if(ease_in=="NONE") t = time;
		else t = (time-0.5) * 2.0;


		if (ease_out == "LINEAR") {
			eased = t;

		}
		if(ease_out != "NONE"){
			let t_inv=(1.0-t);

			switch(ease_out){

				case "SINE": eased = Math.sin((t * Math.PI) / 2.0); break;

				case "CUBIC": eased = 1.0 - t_inv * t_inv * t_inv; break;

				case "QUINT": eased = 1.0 - t_inv * t_inv * t_inv * t_inv * t_inv ; break;

				case "CIRC": eased = Math.sqrt(1.0 - t_inv * t_inv); break;

				case "BACK": eased = 1.0 + c3 * (t-1.0)*(t-1.0)*(t-1.0) + c1 * (t-1.0)*(t-1.0); break;


			}

			if(ease_in == "NONE") return eased;
			else return 0.5 + eased * 0.5;
		}


	}		


}