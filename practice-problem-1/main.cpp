#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
#include<memory>

class TimeDuringDay {
	std::unique_ptr<int> _hours{};
	std::unique_ptr<int> _minutes{};
	std::unique_ptr<int> _seconds{};

	void setAll(const int, const int, const int);
	void setAll(const TimeDuringDay&);
public:
	TimeDuringDay();
	TimeDuringDay(const int, const int, const int);
	TimeDuringDay(const TimeDuringDay&);
		
	~TimeDuringDay();
	
	void setHours(int);
	void setMinutes(int);
	void setSeconds(int);

	[[nodiscard]] int getHours() const noexcept;
	[[nodiscard]] int getMinutes() const noexcept;
	[[nodiscard]] int getSeconds() const noexcept;
	[[nodiscard]] std::string getFormattedTime() const;
	
	TimeDuringDay& operator=(const TimeDuringDay&);
	[[nodiscard]] bool operator==(const TimeDuringDay&);
	[[nodiscard]] TimeDuringDay operator+(const TimeDuringDay&);

	friend std::ostream& operator<<(std::ostream&, const TimeDuringDay&);
};

int main() {
	TimeDuringDay timeDuringDay{ 5, 44, 3 };
	
	try {
		TimeDuringDay timeDuringDay2{ 5, 45, 43 };

		std::cout << timeDuringDay2 << std::endl;
	}
	catch (const std::invalid_argument& error) {
		std::cerr << error.what() << std::endl;
	}
	
	std::cout << timeDuringDay << std::endl;

	return 0;
}

// --------------------------------------
// TimeDuringDay members definition
// --------------------------------------


// private members

void TimeDuringDay::setAll(const int hours, const int minutes, const int seconds) {
	this->setHours(hours);
	this->setMinutes(minutes);
	this->setSeconds(seconds);
}


void TimeDuringDay::setAll(const TimeDuringDay& timeDuringDay) {
	this->setHours(timeDuringDay.getHours());
	this->setMinutes(timeDuringDay.getMinutes());
	this->setSeconds(timeDuringDay.getSeconds());
}

// public members

TimeDuringDay::TimeDuringDay()
	: _hours{ new int{0} }
	, _minutes{ new int{0} }
	, _seconds{ new int{0} }
{}

TimeDuringDay::TimeDuringDay(const TimeDuringDay& timeDuringDay) 
	: _hours{ new int{} }
	, _minutes{ new int{} }
	, _seconds{ new int{} }
{
	this->setAll(timeDuringDay);
}

TimeDuringDay::TimeDuringDay(const int hours, const int minutes, const int seconds)
	: _hours{ new int{} }
	, _minutes{ new int{} }
	, _seconds{ new int{} }
{
	this->setAll(hours, minutes, seconds);
}

TimeDuringDay::~TimeDuringDay() {
	// Debugging
	// std::cout << "Destructor\n";

	this->_hours = nullptr;
	this->_minutes = nullptr;
	this->_seconds = nullptr;
}

void TimeDuringDay::setHours(int hours) {
	if (hours < 0 || hours > 23) {
		throw std::invalid_argument("Hours have to be a number in the interval [0, 23]\n");
	}

	*this->_hours = hours;
}

void TimeDuringDay::setMinutes(int minutes) {
	if (minutes < 0 || minutes > 59) {
		throw std::invalid_argument("Minutes have to be a number in the interval [0, 59]\n");
	}

	*this->_minutes = minutes;
}

void TimeDuringDay::setSeconds(int seconds) {
	if (seconds < 0 || seconds > 59) {
		throw std::invalid_argument("Seconds have to be a number in the interval [0, 59]\n");
	}

	*this->_seconds = seconds;
}

int TimeDuringDay::getHours() const noexcept {
	return *this->_hours;
}

int TimeDuringDay::getMinutes() const noexcept {
	return *this->_minutes;
}

int TimeDuringDay::getSeconds() const noexcept {
	return *this->_seconds;
}

std::string TimeDuringDay::getFormattedTime() const {
	std::ostringstream formattedTime{};

	formattedTime << std::setw(2) << std::setfill('0') << *this->_hours << ":";
	formattedTime << std::setw(2) << std::setfill('0') << *this->_minutes << ":";
	formattedTime << std::setw(2) << std::setfill('0') << *this->_seconds;

	return formattedTime.str();
}

TimeDuringDay& TimeDuringDay::operator=(const TimeDuringDay& rhs) {
	this->setAll(rhs);

	return *this;
}

// --------------------------------------
// Global functions definition
// --------------------------------------

std::ostream& operator<<(std::ostream& os, const TimeDuringDay& timeDuringDay) {
	os << timeDuringDay.getFormattedTime();
	return os;
}