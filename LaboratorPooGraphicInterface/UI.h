#pragma once
#include "service.h"
#include <iostream>
#include<vector>
class UI

{
	Service& serv;

public:

	UI(Service& serv) noexcept : serv{ serv } {};



	void print(const std::vector<Locatar>& locatari) const;


	void start();
};



