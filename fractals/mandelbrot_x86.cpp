
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
		c = 2,
	 	r = 10000; // valor a partir del cual se considera una funcion divergente no acotada
	
	pi = (xmax-xmin)/(xpixels -1); // cambiar el eje de coordenadas de cartesiano a fractalico, las coordenadas coinciden +-
	qi = (ymax-ymin)/(ypixels -1);

	iteraciones++;

	__asm{
		
		horiz:
			verti:
				// p0 = xmin + (p * pi)
				mov EAX, 1;
				fmul p;
				fmul pi;
				fadd p0;
				mov EAX, xmin;
				fadd p0;
				mov p0, EAX;
					
				// q0 = ymin + (q * qi)
				mov EAX, 1;
				fmul q;
				fmul qi;
				fadd q0;
				mov EAX, ymin;
				fadd q0;
				
				mov xx,0; // xx = 0
				mov yy,0; // yy = 0
				
				inter:
					// x = xx*xx - yy*yy + p0 
					mov EAX, xx;
					fmul  xx;
					mov x, EAX;
					mov EAX, yy;
					fmul  yy;
					mov EAX, x;
					fsub  yy;
					fadd p0;
					mov x, EAX;

					// y = 2*xx*yy + q0
					mov EAX, y;
					fmul xx;
					fmul yy;
					fmul c;
					fadd q0;
					mov y, EAX;
					
					// if x*x + y*y > r -> break
					mov EAX, x;
					mov xx, EAX; // xx = x
					mov EAX, y;
					mov yy, EAX; // yy = y

					mov EAX, x;
					fmul x; // x*x
					mov x, EAX;

					mov EAX, y;
					fmul y; // y*y
					mov y, EAX;

					fadd x; // x** + y**

					fcom r; // if EAX > r -> break
					ja exit;

				add k, 1;
				mov EBX, k;
				cmp EBX, iteraciones; // k < iteraciones
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