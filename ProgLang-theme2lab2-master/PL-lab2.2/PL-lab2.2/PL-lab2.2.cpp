#include <windows.h> 
#include <iostream>
#include <random>
#include <vector>
#include <thread>
#include <future>
using namespace std;

class SimpleTimer {
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	SimpleTimer() : m_beg(clock_t::now()) { }

	double elapsed() const {
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

class Answer {
public:
	int minValue;
	int maxValue;
	int minIndex;
	int maxIndex;

	Answer(int localMin, int localMax, int localMinIndex, int localMaxIndex) {
		minValue = localMin;
		maxValue = localMax;
		minIndex = localMinIndex;
		maxIndex = localMaxIndex;
	}

	Answer() {
		minValue = INT_MAX;
		maxValue = INT_MIN;
		minIndex = 0;
		maxIndex = 0;
	}
};

vector<int> arr;

void getValueOfAnswerParameters(promise <Answer>& prms, int leftIdx, int rightIdx) {
	Answer threadAnswer = Answer(INT_MAX, INT_MIN, 0, 0);

	for (int i = leftIdx; i <= rightIdx; i++) {
		if (arr[i] > threadAnswer.maxValue) {
			threadAnswer.maxValue = arr[i];
			threadAnswer.maxIndex = i;
		}

		if (arr[i] < threadAnswer.minValue) {
			threadAnswer.minValue = arr[i];
			threadAnswer.minIndex = i;
		}
	}

	prms.set_value(threadAnswer);
}

void getAnAnswer(int i) {
	Answer globalAnswer = Answer(INT_MAX, INT_MIN, 0, 0);
	vector <thread> threads(i);
	vector <promise <Answer> > promises(i);

	int left_border = 0;
	int right_border = 0;

	cout << "\nThreads: " << i << "\n";

	SimpleTimer timer;

	for (int j = 0; j < i; j++) {
		left_border = right_border;
		right_border = left_border + (arr.size() / i) + 1;

		if (j + 1 == i) {
			right_border = arr.size() - 1;
		}

		threads[j] = thread(getValueOfAnswerParameters, ref(promises[j]), left_border, right_border);
	}

	for (int j = 0; j < i; j++) {
		threads[j].join();

		Answer localAnswer = promises[j].get_future().get();
		if (localAnswer.maxValue > globalAnswer.maxValue) {
			globalAnswer.maxIndex = localAnswer.maxIndex;
			globalAnswer.maxValue = localAnswer.maxValue;
		}

		if (localAnswer.minValue < globalAnswer.minValue) {
			globalAnswer.minIndex = localAnswer.minIndex;
			globalAnswer.minValue = localAnswer.minValue;
		}
	}

	cout << "Time passed: " << timer.elapsed() << "s" << endl << endl;
}


int main() {
	mt19937 mersenne;          //rnd
	mersenne.seed(time(0));

	cout << "Input length of array: ";
	int arrLength;
	cin >> arrLength;

	for (int i = 0; i < arrLength; i++) {
		arr.push_back(mersenne());
	}

	for (int i = 2; i <= 16; i *= 2) {
		getAnAnswer(i);
	}

	return 0;
}

