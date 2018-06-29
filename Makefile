run: dice cards

	./dice

	./cards
	

dice: dice.cpp
	g++ dice.cpp -o dice
cards: cards.cpp
	g++ cards.cpp -o cards
	

clean:
	rm -f dice
	rm -f cards