#include "Trie.h"
#include <conio.h>

//ЗАДАЧА: В качестве итогового задания вам необходимо реализовать программу, выполняющую автодопление введенного слова по изначально заданному словарю.
//То есть, вам необходимо построить дерево, которое будет словарем, а затем выполнить проверку и предложить подходящие варианты слов по введенной части.
//Дополнение можно реализовываться как по нажатию какой - либо клавиши, так и любым другим способом.После нажатия программа не должна завершаться и ждать нового ввода от пользователя.

int main()
{
	setlocale(LC_ALL, "");
	TrieNode* root = getNewNode();
	
	insert(root, "cat");
	insert(root, "call");
	insert(root, "cult");
	insert(root, "run");
	insert(root, "runer");
	insert(root, "rut");


	std::string text;


	//Слова можно вводить как через так и после нажатия enter автодополнение будет работать.
	//Если слово является префиксом другого слова при повторном нажатий TAB слово дополниться, пример r -> TAB -> run -> TAB -> runner. 

	while (true)
	{
		system("cls");
		std::cout << "\t***Автодополнение***\n" "TAB - Автодополнение слова\n" "Backspace - удалить символ\n" "ESC - Выход\n";
		std::cout << "\n\nText: " << text;
		char ch = _getch();

		if (ch == 9)
		{
			autocomplete(root, text);
		}
		else if (ch == 8)
		{
			if (!text.empty())
				text.pop_back();

			else continue;
		}
		else if (ch == 27)
			break;
		else if (ch == 13)
		{
			text.clear();
		}
		else if (ch >= 32 && ch <= 126)
		{
			
			text.push_back(ch);
		}	
	}

	return 0;
}