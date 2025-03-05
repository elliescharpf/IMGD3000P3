#include <stdlib.h>
#include "EventOut.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "Dust.h"
#include "Shape.h"

Dust::Dust() {
	setType("Dust");
	setSolidness(df::SPECTRAL);

	// Set velocity for downward movement
	setVelocity(df::Vector(0, (float)1.0 / (rand() % 9 + 2)));

	setAltitude(0); // Background

	// Start at a random horizontal position at the top of the screen
	df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
		(float)(-10)); // Slightly off-screen at the top
	setPosition(p);

	// Draw falling particles
	df::Shape s;
	s.setColor(df::WHITE);
	s.setType(df::SQUARE);
	s.setSize(5 * getVelocity().getMagnitude());
	setShape(s);
}

// Event handler
int Dust::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	return 0; // Ignored event
}

// Reset position when the particle moves out of bounds
void Dust::out() {
	df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
		(float)(-10)); // Reset to the top
	setPosition(p);

	// Reset downward velocity
	setVelocity(df::Vector(0, (float)1.0 / (rand() % 9 + 2)));

	// Update shape size based on speed
	df::Shape s;
	s.setColor(df::WHITE);
	s.setType(df::SQUARE);
	s.setSize(5 * getVelocity().getMagnitude());
	setShape(s);
}
