#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/dll.h>

using namespace std;
using namespace YAML;

class Hiker {
public:
	double speed;
	//bool crossed;
	string name;

};

class Bridge {
public:
	vector<Hiker> hikers;
	int length;

};

void operator >> (const YAML::Node& node, Hiker& hiker) {
	hiker.name = node["name"].as<std::string>();
	hiker.speed = node["speed"].as<double>();
}

void operator >> (const YAML::Node& node, Bridge& bridge) {

	bridge.length = node["length"].as<int>();
	
	const YAML::Node& hikers = node["hikers"];
	for (int i = 0; i < hikers.size(); i++)
	{
		Hiker hiker;
		hikers[i] >> hiker;
		bridge.hikers.push_back(hiker);
	}
}

void LoadConfiguration(vector<Bridge> &bridges)
{
	YAML::Node doc;
	ifstream fin("C:\\Users\\Yulya Zeveleva\\source\\repos\\HikersProblem\\x64\\Release\\bridges-config.yaml");
	//ifstream fin("bridges-config.yaml");
	if (!fin)
		cout << "While opening a file an error is encountered" << endl;
	else
		cout << "File is successfully opened" << endl;
	
	try
	{
		doc = YAML::Load(fin);
	}
	catch (YAML::ParserException & e) {
		std::cout << e.what() << endl;;
	}
	fin.close();
		
	for (int i = 0; i < doc.size(); i++) {
		Bridge bridge;
		doc[i] >> bridge;
		//std::cout << bridge.length << endl;

		bridges.push_back(bridge);
	}
}

double SlowestPairsFirst(vector<Hiker> hikers)
{
	// first 2 fastest ones cross the bridge
	// then the 1st fastest returns
	double bringBackTime = (100 / hikers[1].speed) * 2 + 100 / hikers[0].speed;
	double firstRunTime = 100 / hikers[1].speed + 100 / hikers[0].speed;
	double crossTime=0;
	crossTime += firstRunTime;
	for (int i = hikers.size() - 1; i >= 2; i -= 2)
	{
		// if one left
		if (i == 2)
		{
			crossTime += 100 / hikers[i].speed;
			
			return crossTime;
		}
		crossTime += 100 / hikers[i].speed;
		crossTime += bringBackTime;
	}
	crossTime -= 100 / hikers[0].speed;
	
	return crossTime;
}

double FastestRunner(vector<Hiker> hikers)
{
	double crossTime = 0;
	double bringBackTime = 100 / hikers[0].speed;
	for (int i = hikers.size() - 1; i >= 1; i --)
	{
		// if one left no need to return
		if (i == 1)
		{
			crossTime += 100 / hikers[i].speed;
			
			return crossTime;
		}
		crossTime += 100 / hikers[i].speed;
		crossTime += bringBackTime;
	}
	return crossTime;
}
bool myfunction(Hiker h1, Hiker h2) { return (h1.speed > h2.speed); }

double FindMinCrossingTime(Bridge& bridge)
{
	vector<Hiker> hikers = bridge.hikers;
	int length = bridge.length;
	double crossTime = 0;

	std::sort(hikers.begin(), hikers.end(), myfunction);

	//There are 2 approaches to the solution that depend on the base conditions
	//
	// 1. maintain the fastest runners at the opposit sides of the bridge;
	//    let the slowest pairs cross and 
	//    then returne the torch to the other side by one of the 2 fastest runners
	// 2. let the fastest runner go back and forth across the bridge and take the rest 
	//    to the other side
	//
	// The result is the minimun of the 2 above

	double crossTime1 = SlowestPairsFirst(hikers);
	double crossTime2 = FastestRunner(hikers);
	cout << " \"Slowest pair first\" finished in " << crossTime1 << endl;
	cout << " \"Fastest runner\" finished in " << crossTime2 << endl;
	return min(crossTime1, crossTime2);
}

void main()
{
	vector<Bridge> bridges;
	LoadConfiguration(bridges);
	double minCrossingTime = 0;
	for (auto bridge : bridges)
	{
		cout << "Bridge of length " << bridge.length << endl;
		minCrossingTime+= FindMinCrossingTime(bridge);
	}
	cout << "Crossing time " << minCrossingTime;
}
