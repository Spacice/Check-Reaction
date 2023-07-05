#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 240), L"Проверь свою реакцию");
	short status = 0;
	/*
	0 - Начальный текст
	1 - Жёлтый цвет
	2 - Зелёный цвет
	3 - Слишком долго
	4 - Слишком быстро
	5 - Экран с результатом
	*/
	time_t startTime = 0;
	time_t randTime = 0;
	time_t endTime = 0;
	srand(clock());

	time_t results[5] = { 0, 0, 0, 0, 0 };
	
	Texture startScreenTex;
	startScreenTex.loadFromFile("startScreen.png");;
	Sprite startScreen;
	startScreen.setTexture(startScreenTex);

	Texture waitingScreenTex;
	waitingScreenTex.loadFromFile("waitingScreen.png");;
	Sprite waitingScreen;
	waitingScreen.setTexture(waitingScreenTex);

	Texture waitingScreen2Tex;
	waitingScreen2Tex.loadFromFile("waitingScreen2.png");;
	Sprite waitingScreen2;
	waitingScreen2.setTexture(waitingScreen2Tex);

	Texture proyobScreenTex;
	proyobScreenTex.loadFromFile("proyobScreen.png");;
	Sprite proyobScreen;
	proyobScreen.setTexture(proyobScreenTex);

	Texture errorScreenTex;
	errorScreenTex.loadFromFile("errorScreen.png");;
	Sprite errorScreen;
	errorScreen.setTexture(errorScreenTex);

	Font font;
	font.loadFromFile("font.ttf");
	Text timeText;
	timeText.setFont(font);
	timeText.setCharacterSize(20);

	while (window.isOpen())
	{
		endTime = clock();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed) {
				if ((status == 0 && Keyboard::isKeyPressed(Keyboard::Enter))) {
					status = 1;
					randTime = 1000 + rand() % 5000;
					startTime = clock();
					endTime = clock();
				}
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (status == 1) status = 4;
			if (status == 2) {
				endTime = clock();
				for (int i = 0; i < 5; i++)
				{
					if (results[i] == 0) {
						results[i] = endTime - startTime;
						break;
					}
					else if (results[i] > endTime - startTime) {
						for (int j = 4; j != i; j--) {
							results[j] = results[j - 1];
						}
						results[i] = endTime - startTime;
						break;
					}
				}
				time_t avg = 0;
				for (int i = 0; i < 5; i++)
					if (results[i] != 0)
						if (i == 0)
							avg = results[i];
						else
							avg = (avg + results[i]) / 2;
					else break;
				timeText.setString(std::to_string(endTime - startTime) + L" мс\nТоп результатов (Ср.: " + std::to_string(avg) + "):\n1. " + std::to_string(results[0]) + "\n2. " + std::to_string(results[1]) + "\n3. " + std::to_string(results[2]) + "\n4. " + std::to_string(results[3]) + "\n5. " + std::to_string(results[4]) + L"\nЧтобы повторить тест, нажмите на ПКМ.");
				status = 5;
			}
		}

		if (Mouse::isButtonPressed(Mouse::Right) && (status == 3 || status == 4 || status == 5)) {
			status = 1;
			randTime = 1000 + rand() % 5000;
			startTime = clock();
			endTime = clock();
		}

		if (endTime - startTime > randTime) {
			if (status == 1) {
				startTime = clock();
				status = 2;
			}
		}

		if (endTime - startTime > 1000.0f && status != 3 && status != 4 && status != 5 && status != 0 && status != 1) status = 3;

		window.clear();
		if (status == 0) window.draw(startScreen);
		if (status == 1) window.draw(waitingScreen);
		if (status == 2 || status == 5) window.draw(waitingScreen2);
		if (status == 3) window.draw(proyobScreen);
		if (status == 4) window.draw(errorScreen);
		if (status == 5) window.draw(timeText);
		window.display();
	}

	return 0;
}