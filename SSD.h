#pragma once
class SSD
{
private:
	int brzinaUpisa;
	int brzinaCitanja;
	int kapacitet;
public:
	SSD(int brzinaUpisa, int brzinaCitanja, int kapacitet) {
		this->brzinaCitanja = brzinaCitanja;
		this->brzinaUpisa = brzinaUpisa;
		this->kapacitet = kapacitet;
	}
};

