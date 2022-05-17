#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
using namespace sf;

class SimpFigure {
public:
	//SimpFigure() : _coor(Vector2f(0, 0)), _speed(0.0f), _arc(0.0f) {};
	SimpFigure(float x, float y) : _coor(Vector2f(x, y)), _speed(0.0f), _arc(0.0f) {};
	void Turn(float direct);
	void Acceleration(float direct);
	void Slow();
	void Stop();
	void Respos();
	Vector2f coor() const;
	float speed();
	float max_speed();
	float arc();
	float arc_step();
	Vector2f speedV();
	virtual void MoveShape() = 0;
	virtual void Rotate(float direct) = 0;
	virtual void Respawn() = 0;
private:
	bool CheckMaxSpeed();
	Vector2f _coor;
	float _arc;
	float _speed;
	float const MAX_SPEED = 8.0f, VAL_ACC = 0.30f, ARC_STEP = M_PI / 60;
};

class Dot : public SimpFigure, public CircleShape {
public:
	//Dot() : CircleShape(), SimpFigure() {}
	Dot(float x, float y, float r) : CircleShape(r), SimpFigure(x, y) {}
	void MoveShape();
	void Rotate(float direct);
	void Respawn();
	size_t getPointCount() const override { return 1ull; }
	Vector2f getPoint(std::size_t index) const override;
};

class Line : public SimpFigure, public RectangleShape {
public:
	//Line() : RectangleShape(Vector2f(20.0f, 3.0f)), SimpFigure(), _lenght(20.f) {}
	Line(float x, float y, float l) : RectangleShape(Vector2f(l, 3.0f)), SimpFigure(x, y), _lenght(l) {}
	void MoveShape();
	void Rotate(float direct);
	void Respawn();
	float lenght();
	size_t getPointCount() const override { return 1ull; }
	Vector2f getPoint(std::size_t index) const override;
private:
	float _lenght;
};

class MyWin : public RenderWindow {
public:
	MyWin(unsigned int win_w, unsigned int win_h, ContextSettings settings) : RenderWindow(VideoMode(win_w, win_h), "SFML works!", sf::Style::Titlebar | sf::Style::Close, settings), win_h(win_h), win_w(win_w) {}
	void drawD(Dot d);
	void drawL(Line l);
	void CheckColisD(Dot &d);
	void CheckColisL(Line &l);
private:
	unsigned int win_w, win_h;
};