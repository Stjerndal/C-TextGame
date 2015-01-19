#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "world.h"
#include "actor.h"
#include "corporeal.h"
#include "environment.h"
#include "outdoor.h"
#include "indoor.h"
#include "dialog.h"
#include "directions.hpp"
#include "userinterface.h"

namespace arcus {
	/*
	Actor player;
	Environment curEnvironment;*/

	World::World() 
	: player("Human", "Marcus", 30)
	, envs()
	{
		//curEnvironment = setupWorld();
	}

	

	void World::start() {
		curEnvironment = setupWorld();
		envs[0].getDescription();
		while(1)
			update();
	}

	void World::update() {
		UserInterface::present(present());
		UserInterface::present("What do you do?");
		std::vector<std::string> input;
		input = UserInterface::fetchInput();
		handleInput(input);
	}

	std::string World::present() const{
		//std::cerr << "ptr: " << envs[0] << std::endl;
		//std::cerr << "ptr: " << envs[1] << std::endl;
		//envs[0]->present();
		std::cerr << "ok1" << std::endl;
		return curEnvironment->present();
	}

	bool World::handleInput(const std::vector<std::string>& input) {
		//UserInterface::present(envs[0]->present());
		//UserInterface::present(envs[1]->present());
		//UserInterface::present(envs[2]->present());
		//std::cout << "Handling 0: " << input[0] << ", 1: " << input[1] << std::endl;
		if (input[0].compare(0,2,"go") == 0) {
			Direction_t dir = convertDir(input[1]);
			if(dir != INVALID && curEnvironment->isDirectionOpen(dir))
				player.go(dir);
				curEnvironment = curEnvironment->getNeighbor(dir);
				return true;
		}
	}


	Environment* World::setupWorld() {
		Item fuelCell("Fuel Cells", 100, 5, 42000, "Black", "Fuel cells needed for hyperspace travel.");
		Item berries("Blueberries", 1, 1, 10, "Blue", "Small edible berries.");
		Item stone("Stone", 70, 4, 3, "Grey", "A small stone.");

		std::vector<std::string> bearAnswers;
		bearAnswers.push_back("Hey bear!");
		Dialog bearDialog("Zzzz", bearAnswers);
		std::vector<Dialog> bearDialogs;
		bearDialogs.push_back(bearDialog);

		Corporeal bear("Bear", "Jebo", 40, bearDialogs, "Brown", 70, 30, 10, 200);

		std::vector<std::string> elephantAnswers;
		elephantAnswers.push_back("Hey elephant!");
		Dialog elephantDialog("*Toerroeee!!*", elephantAnswers);
		std::vector<Dialog> elephantDialogs;
		elephantDialogs.push_back(elephantDialog);

		Corporeal elephant("Elephant", "Frank", 40, elephantDialogs, "Grey", 60, 10, 90, 300);

		std::vector<std::string> robotAnswers1;
		robotAnswers1.push_back("U ugly");
		robotAnswers1.push_back("In peace, I come.");
		Dialog robotDialog1("U wot mate?", robotAnswers1);
		std::vector<std::string> robotAnswers2;
		robotAnswers2.push_back("Hmkay, thanks I guess.");
		Dialog robotDialog2("Ok, I'll tell Yeti.", robotAnswers2);
		std::vector<Dialog> robotDialogs;
		robotDialogs.push_back(robotDialog1);
		robotDialogs.push_back(robotDialog2);

		Corporeal robot("robot", "Harry", 40, robotDialogs, "Silver", 50, 30, 70, 200);

		std::vector<std::string> orbisAnswers1;
		orbisAnswers1.push_back("Mountains");
		orbisAnswers1.push_back("Flowers");
		orbisAnswers1.push_back("Rivers");
		orbisAnswers1.push_back("Llamas");
		Dialog orbisDialog1("What can run but never walks, has a mouth but never talks, has a bed but never sleeps, has a head but never weeps?", orbisAnswers1);
		std::vector<std::string> orbisAnswers2;
		orbisAnswers2.push_back("Cool cool.");
		Dialog orbisDialog2("Righto! I'll tell the Yeti!", orbisAnswers2);
		std::vector<std::string> orbisAnswers3;
		orbisAnswers3.push_back("Shit.");
		Dialog orbisDialog3("Wrongo!", orbisAnswers3);
		std::vector<Dialog> orbisDialogs;
		orbisDialogs.push_back(orbisDialog1);
		orbisDialogs.push_back(orbisDialog2);
		orbisDialogs.push_back(orbisDialog3);

		Corporeal orbis("Orbis", "James", 40, orbisDialogs, "White", 30, 60, 80, 150);

		std::vector<std::string> yetiAnswers1;
		yetiAnswers1.push_back("Ok.");;
		Dialog yetiDialog1("You shall not pass.", yetiAnswers1);
		std::vector<std::string> yetiAnswers2;
		yetiAnswers2.push_back("Cool cool.");
		Dialog yetiDialog2("You shall pass.", yetiAnswers2);
		std::vector<Dialog> yetiDialogs;
		yetiDialogs.push_back(yetiDialog1);
		yetiDialogs.push_back(yetiDialog2);;

		Corporeal yeti("Yeti", "James", 40, yetiDialogs, "Blue", 70, 50, 40, 250);


		Outdoor forest1("A dark and gloomy forest.", SUNNY, "Dark Blue");
		forest1.addItem(berries);

		Outdoor forest2("The forest here is actually pretty dark.", RAINY, "Black");
		forest2.addNpc(bear);

		Outdoor glade("A glade in the forest, this area is cleared of trees. To the east you see a tunnel.", SUNNY, "Dark Blue");
		glade.addItem(stone);
		glade.addNpc(orbis);

		Outdoor fields1("Vast grass fields. To the west you see the forest.", SUNNY, "Blue");

		Outdoor fields2("Vast grass fields. To the south you see a tunnel", SUNNY, "Blue");
		fields2.addNpc(elephant);

		Indoor tunnel("A dark tunnel.", 3);
		tunnel.addNpc(robot);

		Outdoor mountain("Mountains surround you. To the south is you see an opening to a cave.", SNOWY, "White");
		mountain.addNpc(yeti);

		Indoor cave("A small cave", 5);
		cave.addItem(fuelCell);



		Outdoor* forest1p = &forest1;
		Outdoor* forest2p = &forest2;
		Outdoor* fields1p = &fields1;
		Outdoor* fields2p = &fields2;
		Outdoor* gladep = &glade;
		Indoor* tunnelp = &tunnel;
		Outdoor* mountainp = &mountain;
		Indoor* cavep = &cave;

		forest1.addNeighbor(fields1p, EAST);
		forest1.openDirection(EAST);
		forest1.addNeighbor(forest2p, SOUTH);
		forest1.openDirection(SOUTH);

		forest2.addNeighbor(forest1p, NORTH);
		forest2.openDirection(NORTH);
		forest2.addNeighbor(fields2p, EAST);
		forest2.openDirection(EAST);
		forest2.addNeighbor(gladep, SOUTH);
		forest2.openDirection(SOUTH);

		fields1.addNeighbor(forest1p, WEST);
		fields1.openDirection(WEST);
		fields1.addNeighbor(fields2p, SOUTH_EAST);
		fields1.openDirection(SOUTH_EAST);

		fields2.addNeighbor(fields1p, NORTH_WEST);
		fields2.openDirection(NORTH_WEST);
		fields2.addNeighbor(forest2p, WEST);
		fields2.openDirection(WEST);
		fields2.addNeighbor(tunnelp, SOUTH);
		fields2.openDirection(SOUTH);

		glade.addNeighbor(forest2p, NORTH);
		glade.openDirection(NORTH);
		glade.addNeighbor(tunnelp, EAST);
		glade.openDirection(EAST);
		glade.addNeighbor(mountainp, SOUTH_EAST);
		glade.openDirection(SOUTH_EAST);

		tunnel.addNeighbor(fields2p, NORTH);
		tunnel.openDirection(NORTH);
		tunnel.addNeighbor(gladep, WEST);
		tunnel.openDirection(WEST);
		tunnel.addNeighbor(mountainp, SOUTH_WEST);
		tunnel.openDirection(SOUTH_WEST);

		mountain.addNeighbor(gladep, NORTH_WEST);
		mountain.openDirection(NORTH_WEST);
		mountain.addNeighbor(tunnelp, NORTH_EAST);
		mountain.openDirection(NORTH_EAST);
		mountain.addNeighbor(cavep, SOUTH);

		cave.addNeighbor(mountainp, NORTH);
		cave.openDirection(NORTH);

		envs.push_back(forest1);
		envs.push_back(forest2);
		envs.push_back(fields1);
		envs.push_back(fields2);
		envs.push_back(glade);
		envs.push_back(tunnel);
		envs.push_back(mountain);
		envs.push_back(cave);

		forest1p->present();
		std::cerr << "ok0" << std::endl;

		return forest1p;
	}

	
	
}
