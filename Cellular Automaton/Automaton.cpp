#include <SFML/Graphics.hpp>

unsigned const int WIDTH = 1000;
unsigned const int HEIGHT = 1000;

unsigned const int SPEED = 1000;

bool table[WIDTH][HEIGHT] = { false };

class ant {
private:
	unsigned int posX, posY;
	unsigned int direction;					//0 = UP	1 = RIGHT	2 = DOWN	3 = LEFT

	void flip(sf::Image*image) {
		if (table[posX][posY] == false) {
			table[posX][posY] = true;
			image->setPixel(posX, posY, sf::Color::White);
		} else {
			table[posX][posY] = false;
			image->setPixel(posX, posY, sf::Color::Black);
		}
	}

	void move() {
		switch (direction) {
		case 0:
			if (posY == HEIGHT - 1) {
				posY = 0;
			} else {
				posY++;
			}
			break;
		case 1:
			if (posX == WIDTH - 1) {
				posX = 0;
			} else {
				posX++;
			}
			break;
		case 2:
			if (posY == 0) {
				posY = HEIGHT - 1;
			} else {
				posY--;
			}
			break;
		case 3:
			if (posX == 0) {
				posX = WIDTH - 1;
			} else {
				posX--;
			}
			break;
		}
	}

public:
	ant() {
		posX = floor(WIDTH / 2);
		posY = floor(HEIGHT / 2);
		direction = 0;
	}

	void step(sf::Image*image) {
		if (table[posX][posY] == false) {	//White square
			if (direction != 3) {				//Turn right
				direction++;
			} else {
				direction = 0;
			}

			flip(image);								//Flip cell
			move();								//Move

		} else {							//Black square
			if (direction != 0) {
				direction--;
			} else {
				direction = 3;
			}

			flip(image);
			move();
		}
	}
};

int main() {

	ant myAnt;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),"Cellular Automaton",sf::Style::Close);

	sf::Image image;
	image.create(WIDTH, HEIGHT, sf::Color::Black);

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite sprite(texture);
	sprite.setTexture(texture);

	while (window.isOpen()) {
		sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				window.close();
			}

			for (int i = 0; i < SPEED; i++) {
				myAnt.step(&image);
			}

			texture.loadFromImage(image);
			sprite.setTexture(texture);
			window.clear();
			window.draw(sprite);
			window.display();
	}

	return 0;
}