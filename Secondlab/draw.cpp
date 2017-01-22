#include <windows.h>
#include "draw.h"

inline void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

void draw_parts(HDC hdc, int r, int x_real, int y_real) {//draw every 1/8 of circle separately

	int y = 0;
	int x = r;
	float d = 0;
	SetPixel(hdc, x + x_real, y + y_real, 50);
	while (x>y) {
		y++;
		if (DC(r, y) < d) x--;
		SetPixel(hdc, x + x_real, y + y_real, 50 * (1 - DC(r, y)));//we draw two pixels in one step for more smooth by method
		SetPixel(hdc, x + x_real - 1, y + y_real, 50 * DC(r, y));
		d = DC(r, y);
	}

	y = 0;
	x = r;
	d = 0;
	SetPixel(hdc, x + x_real, y + y_real, 50);
	while (x> abs(y)) {
		y--;
		if (DC(r, y) < d) x--;
		SetPixel(hdc, x + x_real, y + y_real, 50 * (1 - DC(r, y)));
		SetPixel(hdc, x + x_real - 1, y + y_real, 50 * DC(r, y));
		d = DC(r, y);
	}

	y = r;
	x = 0;
	d = 0;
	SetPixel(hdc, x + x_real, y + y_real, 50);
	while (y> abs(x)) {
		x--;
		if (DC(r, x) < d) y--;
		SetPixel(hdc, x + x_real, y + y_real, 50 * (1 - DC(r, x)));
		SetPixel(hdc, x + x_real, y + y_real - 1, 50 * DC(r, x));
		d = DC(r, x);
	}

	y = r;
	x = 0;
	d = 0;
	SetPixel(hdc, x + x_real, y + y_real, 50);
	while (y> abs(x)) {
		x++;
		if (DC(r, x) < d) y--;
		SetPixel(hdc, x + x_real, y + y_real, 50 * (1 - DC(r, x)));
		SetPixel(hdc, x + x_real, y + y_real - 1, 50 * DC(r, x));
		d = DC(r, x);
	}

	y = -r;
	x = 0;
	d = 0;
	SetPixel(hdc, x + x_real, y + y_real, 50);
	while (abs(y) > abs(x)) {
		x--;
		if (DC(r, x) < d) y++;
		SetPixel(hdc, x + x_real, y + y_real, 50 * (1 - DC(r, x)));
		SetPixel(hdc, x + x_real, y + y_real + 1, 50 * DC(r, x));
		d = DC(r, x);
	}

	y = -r;
	x = 0;
	d = 0;
	SetPixel(hdc, x + x_real, y + y_real, 50);
	while (abs(y) > abs(x)) {
		x++;
		if (DC(r, x) < d) y++;
		SetPixel(hdc, x + x_real, y + y_real, 50 * (1 - DC(r, x)));
		SetPixel(hdc, x + x_real, y + y_real + 1, 50 * DC(r, x));
		d = DC(r, x);
	}

	y = 0;
	x = -r;
	d = 0;
	SetPixel(hdc, x + x_real, y + y_real, 50);
	while (abs(x)>abs(y)) {
		y++;
		if (DC(r, y) < d) x++;
		SetPixel(hdc, x + x_real, y + y_real, 50 * (1 - DC(r, y)));
		SetPixel(hdc, x + x_real + 1, y + y_real, 50 * DC(r, y));
		d = DC(r, y);
	}

	y = 0;
	x = -r;
	d = 0;
	SetPixel(hdc, x + x_real, y + y_real, 50);
	while (abs(x) > abs(y)) {
		y--;
		if (DC(r, y) < d) x++;
		SetPixel(hdc, x + x_real, y + y_real, 50 * (1 - DC(r, y)));
		SetPixel(hdc, x + x_real + 1, y + y_real, 50 * DC(r, y));
		d = DC(r, y);
	}

}


double DC(int r, int y) {//distance to ceil
	double x = sqrt(r*r - y*y);
	return ceil(x) - x;
}


void draw_complex(HDC hdc, int r, int x_real, int y_real) {
	int y1 = 0;
	int y2 = 0;
	int x1 = r;
	int x2 = -r;
	float d1 = 0;
	float d2 = 0;
	SetPixel(hdc, x1 + x_real, y1 + y_real, 50);
	SetPixel(hdc, x2 + x_real, y2 + y_real, 50);
	SetPixel(hdc, x1 + x_real, y2 + y_real, 50);
	SetPixel(hdc, x2 + x_real, y1 + y_real, 50);
	while (abs(x1) > abs(y1) && abs(x2) > abs(y2)) {
		y1++;
		y2--;
		if (DC(r, y1) < d1) x1--;
		if (DC(r, y2) < d2) x2++;
		SetPixel(hdc, x1 + x_real, y1 + y_real, 50 * (1 - DC(r, y1)));
		SetPixel(hdc, x1 + x_real - 1, y1 + y_real, 50 * DC(r, y1));

		SetPixel(hdc, x1 + x_real, -y1 + y_real, 50 * (1 - DC(r, y1)));
		SetPixel(hdc, x1 + x_real - 1, -y1 + y_real, 50 * DC(r, y1));

		SetPixel(hdc, x2 + x_real, y2 + y_real, 50 * (1 - DC(r, y2)));
		SetPixel(hdc, x2 + x_real + 1, y2 + y_real, 50 * DC(r, y2));

		SetPixel(hdc, x2 + x_real, -y2 + y_real, 50 * (1 - DC(r, y2)));
		SetPixel(hdc, x2 + x_real + 1, -y2 + y_real, 50 * DC(r, y2));

		d1 = DC(r, y1);
		d2 = DC(r, y2);
	}

	y1 = r;
	y2 = -r;
	x1 = 0;
	x2 = 0;
	d1 = 0;
	d2 = 0;
	SetPixel(hdc, x1 + x_real, y1 + y_real, 50);
	SetPixel(hdc, x2 + x_real, y2 + y_real, 50);
	SetPixel(hdc, x1 + x_real, y2 + y_real, 50);
	SetPixel(hdc, x2 + x_real, y1 + y_real, 50);
	while (abs(y1) > abs(x1)) {
		x1++;
		x2--;
		if (DC(r, x1) < d1) y1--;
		if (DC(r, x2) < d2) y2++;

		SetPixel(hdc, x1 + x_real, y1 + y_real, 50 * (1 - DC(r, x1)));
		SetPixel(hdc, x1 + x_real, y1 + y_real - 1, 50 * DC(r, x1));

		SetPixel(hdc, -x1 + x_real, y1 + y_real, 50 * (1 - DC(r, x1)));
		SetPixel(hdc, -x1 + x_real, y1 + y_real - 1, 50 * DC(r, x1));

		SetPixel(hdc, x2 + x_real, y2 + y_real, 50 * (1 - DC(r, x2)));
		SetPixel(hdc, x2 + x_real, y2 + y_real + 1, 50 * DC(r, x2));

		SetPixel(hdc, -x2 + x_real, y2 + y_real, 50 * (1 - DC(r, x2)));
		SetPixel(hdc, -x2 + x_real, y2 + y_real + 1, 50 * DC(r, x2));
		d1 = DC(r, x1);
		d2 = DC(r, x2);
	}
}