#include "descriptions.h"
#include "json.h"
#include "requests.h"
#include "sphere.h"
#include "transport_catalog.h"
#include "utils.h"

#include <iostream>
#include <fstream>

using namespace std;

void Test1();
void Test2();
void Test3();
void Test4();

int main() {
	/*
	Test1();
	Test2();
	Test3();
	Test4();
	*/
	const auto input_doc = Json::Load(cin);
	const auto& input_map = input_doc.GetRoot().AsMap();

	const TransportCatalog db(
		Descriptions::ReadDescriptions(input_map.at("base_requests").AsArray()),
		input_map.at("routing_settings").AsMap()
	);

	Json::PrintValue(
		Requests::ProcessAll(db, input_map.at("stat_requests").AsArray()),
		cout
	);
	cout << endl;
	return 0;
}

void Test1() {
	ifstream input("part_e_san_fail\\input1.json");
	const auto input_doc = Json::Load(input);
	const auto& input_map = input_doc.GetRoot().AsMap();

	const TransportCatalog db(
		Descriptions::ReadDescriptions(input_map.at("base_requests").AsArray()),
		input_map.at("routing_settings").AsMap()
	);

	Json::PrintValue(
		Requests::ProcessAll(db, input_map.at("stat_requests").AsArray()),
		cout
	);
}

void Test2() {
	ifstream input("part_e_san_fail\\input2.json");
	const auto input_doc = Json::Load(input);
	const auto& input_map = input_doc.GetRoot().AsMap();

	const TransportCatalog db(
		Descriptions::ReadDescriptions(input_map.at("base_requests").AsArray()),
		input_map.at("routing_settings").AsMap()
	);

	Json::PrintValue(
		Requests::ProcessAll(db, input_map.at("stat_requests").AsArray()),
		cout
	);
}

void Test3() {
	ifstream input("part_e_san_fail\\input3.json");
	const auto input_doc = Json::Load(input);
	const auto& input_map = input_doc.GetRoot().AsMap();

	const TransportCatalog db(
		Descriptions::ReadDescriptions(input_map.at("base_requests").AsArray()),
		input_map.at("routing_settings").AsMap()
	);

	Json::PrintValue(
		Requests::ProcessAll(db, input_map.at("stat_requests").AsArray()),
		cout
	);
}

void Test4() {
	ifstream input("part_e_san_fail\\input4.json");
	const auto input_doc = Json::Load(input);
	const auto& input_map = input_doc.GetRoot().AsMap();

	const TransportCatalog db(
		Descriptions::ReadDescriptions(input_map.at("base_requests").AsArray()),
		input_map.at("routing_settings").AsMap()
	);

	Json::PrintValue(
		Requests::ProcessAll(db, input_map.at("stat_requests").AsArray()),
		cout
	);
}