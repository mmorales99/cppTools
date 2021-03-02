
#define xpixels 1920
#define ypixels 1080

void
mandelbrot_x86(
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
	qi = (ymax-ymin)/(ypixels -1);

	iteraciones++;

	__asm{
		
		horiz:
			verti:
				// p0 = xmin + (p * pi)
				move eax, 1;
				fimul eax, p;
				fimul eax, pi;
				fadd p0, eax;
				fadd p0, xmin;
					
				// q0 = ymin + (q * qi)
				move eax, 1;
				fimul eax, q;
				fimul eax, qi;
				fadd q0, eax;
				fadd q0, ymin;
				
				move xx,0; // xx = 0
				move yy,0; // yy = 0
				
				inter:
					// x = xx*xx - yy*yy + p0 
					fimul  xx,  xx;
					fimul  yy,  yy;
					move  x,  xx;
					fsub  x,  yy;
					fadd x, p0;

					// y = 2*xx*yy + q0
					fimul y,  xx;
					fimul  y, yy;
					fimul  y, 2;
					fadd y,  q0;
					
					// if x*x + y*y > r -> break
					move  xx, x; // xx = x
					move  yy, y; // yy = y

					fimul x, x; // x*x
					fimul y, y; // y*y

					move eax, 0; // x** + y**
					fadd eax, x;
					fadd eax, y;

					cmp eax, r; // if eax > r -> break
					ja exit;

				add k, 1;
				cmp k, iteraciones; // k < iteraciones
				jb inter;
			add q, 1;
			cmp q, ypixels; // q < ypixels
			jb verti;
		add p, 1;
		cmp p, xpixels; // p < xpixels
		jb horiz;
		exit:
	}
}