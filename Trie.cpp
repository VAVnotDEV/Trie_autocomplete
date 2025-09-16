#include "Trie.h"

TrieNode* getNewNode()
{
	//выделяем память под новый узел
	struct TrieNode* pNode = new TrieNode;

	//устанавливаем флаг конца слова в false;
	pNode->isEndWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = nullptr;

	return pNode;
}

//Алгоритм:
//	Взять символ от вставляемого ключа.
//		Проверить, что нет дочернего узла с таким символом.
//		Присвоить узлу по индексу взятого символа новый узел.
//		Присвоить текущему узлу только созданный дочерний.
//		Повторять с п. 1, пока в ключе есть символы.
//		Установить флаг конца слова для последнего узла.

void insert(TrieNode* root, std::string key)
{
	TrieNode* node = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';

		if (!node->children[index])
			node->children[index] = getNewNode();

		node->children[index]->freq++;
		
		node = node->children[index];
	}

	node->isEndWord = true;
}

bool search(TrieNode* root, std::string key)
{
	TrieNode* node = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';

		if (!node->children[index])
			return false;

		node = node->children[index];
	}

	return (node && node->isEndWord);
}

bool isEmpty(TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return false;

	return true;

}

TrieNode* remove(TrieNode* root, std::string key, int depth)
{
	if (!root)
		return nullptr;
	// Если дошли до конца ключа
	if (depth == key.size())
	{
		// Этот узел больше не конец слова
		// поэтому снимаем метку
		if (root->isEndWord)
			root->isEndWord = false;
		//Если ключ является префиксом, удаляем его
		if (isEmpty(root))
		{
			delete (root);
			root = nullptr;
		}

		return root;
	}

	// Пока не дошли до конца ключа или определили, 
	// что его нет в дереве, рекурсивно вызываем для ребенка
	// соответствующего символа
	int index = key[depth] - 'a';
	root->children[index] = remove(root->children[index], key, depth + 1);
	// Если у корня нет дочернего слова
	// (удален только один его дочерний элемент),
	// и он не заканчивается другим словом.
	if (isEmpty(root) && root->isEndWord == false)
	{
		delete (root);
		root = nullptr;
	}
	return root;
}

void findMinPrefixes(TrieNode* root, char buf[], int ind, std::string& res)
{

	if (!root) return;

	if (root->freq == 1)
	{
		res += buf;
		res += ' ';
		std::cout << res << '\n';
		return;
	}

	for (int i = 0; i < ALPHABET_SIZE; ++i)
	{
		if (root->children[i])
		{
			buf[ind] = i + 'a';
			buf[ind + 1] = '\0';
			findMinPrefixes(root->children[i], buf, ind + 1, res);
		}
	}
}


void autocomplete(TrieNode* root, std::string& key)
{	
	if (!root)
		return;

	TrieNode* node = root;
	int index = 0;

	for (int i = 0; i < key.length(); i++)
	{
		if (key[i] == 32)
		{
			node = root;
			continue;
		}

		index = key[i] - 'a';

		if (!node->children[index])
			return;

		node = node->children[index];
	}

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (node->children[i])
		{
			if (node->children[i]->isEndWord)
			{
				key.push_back(char(i + 'a'));
				return;
			}

			key.push_back(char(i + 'a'));
			node = node->children[i];
			i = 0;
		}
	}
}
	

