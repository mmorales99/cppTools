/*function iterate(x, y, maxiterations) {
    var iterations = 0;
    while (iterations < maxiterations && (rx * rx + ry * ry <= 4)) {
        rx = a * a - b * b + x0;
        ry = 2 * a * b + y0;

        // Next iteration
        a = rx;
        b = ry;
        iterations++;
    }
	*/

#define xpixels 1920
#define ypixels 1080

void 
mandelbrot(
	float xmin,	// minimo en el eje x	->	minimo en la recta real o la recta de representacion	->	Coincide con el eje X del ambito de representacion
	float xmax,	// maximo en el eje x	->	maximo en la recta real o la recta de representacion	->	Coincide con el eje X del ambito de representacion
	float ymin,	// minimo en el eje y	->	minimo en la recta imaginaria o la recta de representacion	->	Coincide con el eje Y del ambito de representacion
	float ymax, // maximo en el eje y	->	maximo en la recta imaginaria o la recta de representacion	->	Coincide con el eje Y del ambito de representacion
	unsigned int iteraciones	// numero de iteraciones a hacer
){
	float pi,	// origen de coordenadas	->	coordenada A
		  qi,	// origen de coordenadas	->	coordenada B
		  p0,	// Coordenada en la recta real
		  q0,	// Coordenada en la recta imaginaria
		  x,	// Coordenada del punto
		  y,	// Coordenada del punto
		  xx,	// Auxiliar de coordenada x
		  yy;	// Auxiliar de coordenada y
	
	int p,	// auxiliar
		q,	// auxiliar
	 	k,	// auxiliar
	 	r = 10000; // valor a partir del cual se considera una funcion divergente no acotada
	
	pi = (xmax-xmin)/(xpixels -1); // cambiar el eje de coordenadas de cartesiano a fractalico, las coordenadas coinciden +-
	qi = (ymax-ymin)/(ypixels-1);

	for(p=0;p<xpixels;p++){					//////////////////////////////////////////////////////////////
		for(q=0;q<ypixels;q++){				//	 Para toda la superficie real-imaginaria se prueba que 	//
			p0=xmin+p*pi;					//	 Coordenada X de la superficie fractalica - p0			//
			q0=ymin+q*qi;					//	 Coordenada Y de la superficie fractalica	- q0		//
			xx=0;							//	++++++++++++++++++++++++++++++++++++++++++++++++++++++	//
			yy=0;							//	++++++++++++++++++++++++++++++++++++++++++++++++++++++	//
			for(k=1;k<=iteraciones;k++){	//	Repetir tantas veces como se quiera aproximar			//
				x = xx*xx - yy*yy+p0;		//	Calcular valor de Z										//
				y = 2*xx*yy+q0;				//	Calcular valor de C										//
				xx = x;						//	++++++++++++++++++++++++++++++++++++++++++++++++++++++	//
				yy = y;						//	++++++++++++++++++++++++++++++++++++++++++++++++++++++	//
			if(x*x + y*y > r){				//	Si cumple que Z^2 + C^2 > CotaSuperior -> no es parte	//
											//	de la conjetura											//
					// añadir al set		//////////////////////////////////////////////////////////////
					break;
				}
			}
		}
	}
}