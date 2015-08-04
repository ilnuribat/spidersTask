#include <stdio.h>
#include <vector>
#define STEPS 6   //Всего ходов
#define MAX 5     //Количество дырок

using namespace std;

//Все возможные ходы таракана
vector<vector<int>> spiders;

//в каких клетках был таракан. Для рекурсии
int oneStep[STEPS + 1];

void makeRecursive(int currentStep) {
	//currentStep - который ход сейчас
	
	//Мы сходили 6 раз, прекращаем рекурсию
	if (currentStep > STEPS) {
		//индексация с единицы, а не с нуля
		vector<int> trueSteps(1);
		
		//загоняем готовый ход в общую коллекцию
		for(int i = 1; i <= STEPS; i ++)
			trueSteps.push_back(oneStep[i]);
		spiders.push_back(trueSteps);
		return;
	}
	//Если таракан прижался к левому краю, у него только 1 возможный ход, направо
	if (oneStep[currentStep - 1] == 1) {
		oneStep[currentStep] = 2;
		makeRecursive(currentStep + 1);
	}
	//Соответственно, если прижался на правый бок - ходим налево
	else if (oneStep[currentStep - 1] == MAX) {
		oneStep[currentStep] = MAX - 1;
		makeRecursive(currentStep + 1);
	}
	//Если стоим посередине, то можем ходить как налево, так и направо
	else {
		oneStep[currentStep] = oneStep[currentStep - 1] - 1;//Ход влево
		makeRecursive(currentStep + 1);
		oneStep[currentStep] = oneStep[currentStep - 1] + 1;//Ход вправо
		makeRecursive(currentStep + 1);
	}
}

void initAllSpiders() {
	//Перебор стартовых точек
	for(int i = 1; i <= MAX; i++)
	{
		oneStep[1] = i;
		makeRecursive(2);
	}
}

//Покрывает ли наш ход все возможные ходы таракана
void check(int i1, int i2, int i3, int i4, int i5, int i6) {
	//по умолчанию - да, покарывает
	bool victory = true;
	for(int i = 0; i < spiders.size(); i ++)
		if(spiders[i][1] != i1 &&
			spiders[i][2] != i2 &&
			spiders[i][3] != i3 &&
			spiders[i][4] != i4 &&
			spiders[i][5] != i5 &&
			spiders[i][6] != i6)
			//Нашли ход, при котором таракан смог убежать от нас
				victory = false;
	if(victory)
		printf("%d %d %d %d %d %d\n", i1, i2, i3, i4, i5, i6);
}

int main() {
	initAllSpiders();
	
	//Достаточно глупый перебор всех возможных ходов
	//Так как ходов ровно 6, почему бы и не накидать вложенных циклов. 
	//6^5 = 7776, всевозможных тараканьих ходов - 72.
	for(int i1 = 1; i1 <= MAX; i1 ++)
		for(int i2 = 1; i2 <= MAX; i2 ++)
			for(int i3 = 1; i3 <= MAX; i3 ++)
				for(int i4 = 1; i4 <= MAX; i4 ++)
					for(int i5 = 1; i5 <= MAX; i5 ++)
						for(int i6 = 1; i6 <= MAX; i6 ++)
							check(i1, i2, i3, i4, i5, i6);
	return 0;
}
