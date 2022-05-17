#include "figure.h"

using namespace sf;
//SimpleFigure
void SimpFigure::Turn(float direct) {
	_arc += direct * ARC_STEP;
	if (_arc >   M_PI) _arc -= 2 * M_PI;
	if (_arc <	-M_PI) _arc += 2 * M_PI;
}

void SimpFigure::Acceleration(float direct) {
	_speed += direct * VAL_ACC;
	if (_speed > MAX_SPEED) _speed -= direct * VAL_ACC;
}

void SimpFigure::Slow() {
	if (_speed > VAL_ACC / 3) _speed -= VAL_ACC / 3;
	else if (_speed < -VAL_ACC / 3) _speed += VAL_ACC / 3;
	else SimpFigure::Stop();
}

void SimpFigure::Stop() {
	_speed = 0.0f;
}

void SimpFigure::Respos() {
	_arc = 0.0f;
	SimpFigure::Stop();
}

Vector2f SimpFigure::coor() const { return _coor; }

float SimpFigure::speed() { return _speed; }

float SimpFigure::max_speed() { return MAX_SPEED; }

float SimpFigure::arc() { return _arc;}

float SimpFigure::arc_step() { return ARC_STEP; }

Vector2f SimpFigure::speedV() {
	float x = _speed * sin(_arc), y = _speed * (-cos(_arc));;
	return Vector2f(x, y);
}

bool SimpFigure::CheckMaxSpeed() {
	if (abs(_speed) > MAX_SPEED) return true;
	return false;
}


//Dot
void Dot::MoveShape(){
	move(speedV());
}

void Dot::Rotate(float direct) {
	Turn(direct);
}

void Dot::Respawn() {
	Respos();
	setPosition(coor());
}

Vector2f Dot::getPoint(std::size_t index) const{
	return coor();
}


//Line
float Line::lenght() { return _lenght; }

void Line::MoveShape() {
	move(speedV());
}

void Line::Rotate(float direct) {
	Turn(direct);
	float degr_arc = direct * arc_step() * 180 / M_PI;
	rotate(degr_arc);
	float delt = 0.5f * _lenght;
	float delt_x =  delt * sin(direct * arc_step()) * sin(arc());
	float delt_y = -delt * sin(direct * arc_step()) * cos(arc());
	move(Vector2f(delt_x, delt_y));
}

void Line::Respawn() {
	float deg_rot = -arc() * 180 / M_PI;
	rotate(deg_rot);
	Respos();
	setPosition(coor());
}

Vector2f Line::getPoint(std::size_t index) const {
	return coor();
}

//MyWin
void MyWin::CheckColisD(Dot &d) {
	Vector2f cr = d.getPosition();

	if (cr.x < 0.f) 
		d.setPosition(Vector2f(2.f, cr.y));
	else if (cr.x > win_w - d.getRadius() * 2.f) 
		d.setPosition(Vector2f(win_w - d.getRadius() * 2.f - 2.f, cr.y));

	if (cr.y < 0.f) d.setPosition(Vector2f(cr.x, 2.f));
	else if (cr.y > win_h - d.getRadius() * 2.f) 
		d.setPosition(Vector2f(cr.x, win_h - d.getRadius() * 2.f - 2.f));
}

void MyWin::CheckColisL(Line& l) {
	Vector2f cr1 = l.getPosition();
	Vector2f dl( l.lenght() * cos(l.arc()), l.lenght() * sin(l.arc()) );
	Vector2f cr2 = cr1 + dl;

	if (cr1.x < 0.f)
		l.setPosition( Vector2f(2.f, cr1.y) );
	else if (cr1.x > win_w)
		l.setPosition( Vector2f(win_w + abs(dl.x) - 2.f, cr1.y) );

	if (cr1.y < 0.f) l.setPosition( Vector2f(cr1.x, 2.f) );
	else if (cr1.y > win_h)
		l.setPosition( Vector2f(cr1.x, win_h - 2.f) );

	if (cr2.x < 0.f)
		l.setPosition( Vector2f(abs(dl.x) + 2.f, cr1.y) );
	else if (cr2.x > win_w)
		l.setPosition( Vector2f(win_w - abs(dl.x) - 2.f, cr1.y) );

	if (cr2.y < 0.f) l.setPosition( Vector2f(cr1.x, abs(dl.y) + 2.f) );
	else if (cr2.y > win_h)
		l.setPosition( Vector2f(cr1.x, win_h - abs(dl.y) - 2.f) ) ;
	
}



void MyWin::drawD(Dot d) {
	CheckColisD(d);
	//std::cout << d.getPosition().x<< ' '<< d.getPosition().y << std::endl;
	if (abs(d.speed()) < d.max_speed() / 3) {
		draw(d);
	}

	else {
		Vector2f spV = -d.speedV() * 5.f, cr = d.getPosition() + spV;
		int alfa = 51, alfeRed = 250;
		Color col = Color(alfeRed, alfa, alfa);
		float rad = d.getRadius() * 1.2f, dR = (rad - d.getRadius()), arc = d.arc();
		for (int i = 1; i < 5; i++) {
			cr += Vector2f(- dR * sin(arc), -dR * cos(arc));
			CircleShape c(rad);
			c.setPosition(cr);
			c.setFillColor(col);

			draw(c);

			dR *= 1.2f;
			alfa += 51;
			//alfeRed = 50;
			col = Color(alfeRed, alfa, alfa);
			rad *= 1.2f;
			cr += spV * 1.2f;
		}
		draw(d);
	}
}

void MyWin::drawL(Line l) {
	CheckColisL(l);
	if (abs(l.speed()) < l.max_speed() / 3) {
		draw(l);
	}

	else {
		Vector2f spV = -l.speedV() * 3.f, cr = l.getPosition() + spV;
		int alfa = 15, alfaBlue = 125;
		Color col = Color(alfa, alfa, alfaBlue);
		float ln = l.lenght() * 1.2f, arc = l.arc() * 180.f / M_PI, dL = (ln - l.lenght()) / 2.f;
		for (int i = 1; i < 4; i++) {
			RectangleShape ra(Vector2f(ln, 3.f));
			cr += Vector2f(-dL * cos(arc), -dL * sin(arc));
			ra.setPosition(cr);
			ra.setFillColor(col);
			ra.rotate(arc);

			draw(ra);

			dL *= 1.2f;
			alfa += 10;
			alfaBlue -= 50;
			col = Color(alfa, alfa, alfaBlue);
			ln *= 1.2f;
			cr += spV * 1.2f;
		}
		draw(l);
	}
}
