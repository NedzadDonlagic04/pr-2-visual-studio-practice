#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
#include<memory>
#include<chrono>
#include<thread>
#include<limits>

class TimeDuringDay {
	std::unique_ptr<int> _hours{};
	std::unique_ptr<int> _minutes{};
	std::unique_ptr<int> _seconds{};

public:
	TimeDuringDay();
	TimeDuringDay(const int, const int, const int);
	TimeDuringDay(const TimeDuringDay&);
		
	~TimeDuringDay();

	[[nodiscard]] static bool isValidHour(const int) noexcept;
	[[nodiscard]] static bool isValidMinute(const int) noexcept;
	[[nodiscard]] static bool isValidSecond(const int) noexcept;
	
	void convertExtraSecondsMinutes() noexcept;
	
	void setHours(const int);
	void setMinutes(const int);
	void setSeconds(const int);

	void setAll(const int, const int, const int);
	void setAll(const TimeDuringDay&);

	[[nodiscard]] int getHours() const noexcept;
	[[nodiscard]] int getMinutes() const noexcept;
	[[nodiscard]] int getSeconds() const noexcept;
	[[nodiscard]] std::string getFormattedTime() const;
	
	TimeDuringDay& operator=(const TimeDuringDay&);
	[[nodiscard]] bool operator==(const TimeDuringDay&) const noexcept;
	[[nodiscard]] bool operator!=(const TimeDuringDay&) const noexcept;
	[[nodiscard]] TimeDuringDay operator+(const TimeDuringDay&) const;

	TimeDuringDay& operator++() noexcept;
	TimeDuringDay operator++(int) noexcept;

	friend std::ostream& operator<<(std::ostream&, const TimeDuringDay&);
};

namespace utils {
	void sleep(const long long);

	void printErrorMsg(const char* const);

	void clearBuffer();

	template<typename NumberType, typename Callback>
	void enterNum(NumberType&, const char* const, Callback = [](const int) { return true; });
}

void enterTimeDuringDay(TimeDuringDay&, const char * const);

int main() {
	TimeDuringDay timeDuringDayStart{};
	TimeDuringDay timeDuringDayEnd{};

	enterTimeDuringDay(timeDuringDayStart, "Enter the starting time for the timer\n");
	std::cout << std::endl;
	enterTimeDuringDay(timeDuringDayEnd, "Enter the ending time for the timer\n");
	std::cout << std::endl;

	// This is done so that in the for loop we print the ending time as well
	timeDuringDayEnd++;

	std::cout << "Timer started:\n";
	
	for (; timeDuringDayStart != timeDuringDayEnd; timeDuringDayStart++) {
		std::cout << '\r' << timeDuringDayStart.getFormattedTime();
		utils::sleep(1000);
	}
	
	std::cout << '\n' << "Timer reached it's end\n";

	return 0;
}

// --------------------------------------
// TimeDuringDay members definition
// --------------------------------------

// private members

// public members

TimeDuringDay::TimeDuringDay()
	: _hours{ new int{0} }
	, _minutes{ new int{0} }
	, _seconds{ new int{0} }
{}

TimeDuringDay::TimeDuringDay(const TimeDuringDay& timeDuringDay) 
	: _hours{ new int{0} }
	, _minutes{ new int{0} }
	, _seconds{ new int{0} }
{
	this->setAll(timeDuringDay);
}

TimeDuringDay::TimeDuringDay(const int hours, const int minutes, const int seconds)
	: _hours{ new int{0} }
	, _minutes{ new int{0} }
	, _seconds{ new int{0} }
{
	this->setAll(hours, minutes, seconds);
}

TimeDuringDay::~TimeDuringDay() {
	// Debugging
	// std::cout << "Destructor\n";

	this->_seconds = nullptr;
	this->_minutes = nullptr;
	this->_hours = nullptr;
}

bool TimeDuringDay::isValidHour(const int hours) noexcept {
	return hours >= 0;
}

bool TimeDuringDay::isValidMinute(const int minutes) noexcept {
	return minutes >= 0;
}

bool TimeDuringDay::isValidSecond(const int seconds) noexcept {
	return seconds >= 0;
}

void TimeDuringDay::convertExtraSecondsMinutes() noexcept {
	*this->_minutes += *this->_seconds / 60;
	*this->_seconds %= 60;

	*this->_hours += *this->_minutes / 60;
	*this->_minutes %= 60;

	*this->_hours %= 24;
}

void TimeDuringDay::setHours(const int hours) {
	if (!TimeDuringDay::isValidHour(hours)) {
		throw std::invalid_argument("Hours can't be a negative number\n");
	}

	*this->_hours = hours;
}

void TimeDuringDay::setMinutes(const int minutes) {
	if (!TimeDuringDay::isValidMinute(minutes)) {
		throw std::invalid_argument("Minutes can't be a negative number\n");
	}

	*this->_minutes = minutes;
}

void TimeDuringDay::setSeconds(const int seconds) {
	if (!TimeDuringDay::isValidSecond(seconds)) {
		throw std::invalid_argument("Seconds can't be a negative number\n");
	}

	*this->_seconds = seconds;
}

void TimeDuringDay::setAll(const int hours, const int minutes, const int seconds) {
	this->setSeconds(seconds);
	this->setMinutes(minutes);
	this->setHours(hours);

	this->convertExtraSecondsMinutes();
}

void TimeDuringDay::setAll(const TimeDuringDay& timeDuringDay) {
	this->setSeconds(timeDuringDay.getSeconds());
	this->setMinutes(timeDuringDay.getMinutes());
	this->setHours(timeDuringDay.getHours());
	
	this->convertExtraSecondsMinutes();
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

	formattedTime << std::setw(2) << std::setfill('0') << this->getHours() << ":";
	formattedTime << std::setw(2) << std::setfill('0') << this->getMinutes() << ":";
	formattedTime << std::setw(2) << std::setfill('0') << this->getSeconds();

	return formattedTime.str();
}

TimeDuringDay& TimeDuringDay::operator=(const TimeDuringDay& rhs) {
	this->setAll(rhs);

	return *this;
}

bool TimeDuringDay::operator==(const TimeDuringDay& rhs) const noexcept {
	return	this->getHours() == rhs.getHours()
			&& this->getMinutes() == rhs.getMinutes() 
			&& this->getSeconds() == rhs.getSeconds();
}

bool TimeDuringDay::operator!=(const TimeDuringDay& rhs) const noexcept {
	return !(*this == rhs);
}

TimeDuringDay TimeDuringDay::operator+(const TimeDuringDay& rhs) const {
	const TimeDuringDay temp{ 
		this->getHours() + rhs.getHours(), 
		this->getMinutes() + rhs.getMinutes(), 
		this->getSeconds() + rhs.getSeconds() 
	};

	return temp;
}

TimeDuringDay& TimeDuringDay::operator++() noexcept {
	this->setAll(this->getHours(), this->getMinutes(), this->getSeconds() + 1);

	return *this;
}

TimeDuringDay TimeDuringDay::operator++(int) noexcept {
	TimeDuringDay temp{ *this };

	++*this;

	return temp;
}

// --------------------------------------
// Global functions definition
// --------------------------------------

std::ostream& operator<<(std::ostream& os, const TimeDuringDay& timeDuringDay) {
	os << timeDuringDay.getFormattedTime();
	return os;
}

namespace utils {
	void sleep(const long long miliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
	}

	void printErrorMsg(const char* const errorMsg) {
		std::cerr << "\033[31m";
		std::cerr << errorMsg;
		std::cerr << "\033[37m";
	}

	void clearBuffer() {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	template<typename NumberType, typename Callback>
	void enterNum(NumberType& num, const char* const outputMsg, Callback isValidNumber) {
		bool repeatLoop{};

		do {
			repeatLoop = false;

			std::cout << outputMsg;
			std::cin >> num;

			if (std::cin.fail()) {
				repeatLoop = true;
				clearBuffer();
				printErrorMsg("Unos nije validan broj\n");
			}
			else if (!isValidNumber(num)) {
				repeatLoop = true;
				clearBuffer();
			}
		} while (repeatLoop);

		// To ignore any following inputs after the valid one
		clearBuffer();
	}
}

void enterTimeDuringDay(TimeDuringDay& timeDuringDay, const char* const outputMsg) {
	int hours{};
	int minutes{};
	int seconds{};

	std::cout << outputMsg;

	utils::enterNum(hours, "Enter hours: ", 
		[](const int num) {
			if (!TimeDuringDay::isValidHour(num)) {
				utils::printErrorMsg("Invalid hours entered\n");
				return false;
			}
			return true;
		}
	);
	utils::enterNum(minutes, "Enter minutes: ", 
		[](const int num) {
			if (!TimeDuringDay::isValidMinute(num)) {
				utils::printErrorMsg("Invalid minutes entered\n");
				return false;
			}
			return true;
		}
	);
	utils::enterNum(seconds, "Enter seconds: ", 
		[](const int num) {
			if (!TimeDuringDay::isValidSecond(num)) {
				utils::printErrorMsg("Invalid seconds entered\n");
				return false;
			}
			return true;
		}
	);

	// Debuggin
	// std::cout << hours << ' ' << minutes << ' ' << seconds << '\n';
	timeDuringDay.setAll(hours, minutes, seconds);
}