#include"playfair.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char* NewString(const char* text)
{
	int newSize = strlen(text);
	char* newText = (char*)calloc(newSize + 1, sizeof(char));
	newText[newSize] = 0; // koniec retazca

	for (int i = 0; i < strlen(text); i++)
		newText[i] = text[i];

	return newText;
}

void ToUpper(char* text)
{
	for (int i = 0; i < strlen(text); i++)
		text[i] = toupper(text[i]);
}

void ReplaceW(char* text)
{
	int textLength = strlen(text);

	for (int i = 0; i < textLength; i++)
	{
		if (text[i] == 'W')
			text[i] = 'V';
	}
}

bool MatrixValuesContainsChar(char matrixValues[], char value)
{
	for (int i = 0; i < 25; i++)
	{
		if (matrixValues[i] == value)
        			return true;
	}

	return false;
}

void FillMatrix(char matrix[][5], char* key)
{
	char abeceda[] = "ABCDEFGHIJKLMNOPQRSTUVXYZ";
	char matrixValues[25];
    for (int i = 0; i < 25; i++){
        matrixValues[i] = 0;
}
	// pridam do matrixValues key (duplicitne znaky pridam iba raz)
	int iMatrixValue = 0;
	for (int i = 0; i < strlen(key); i++)
    	{
		if (!MatrixValuesContainsChar(matrixValues, key[i]))
			matrixValues[iMatrixValue++] = key[i];
	}

	// pridam do matrixValues zvysok abecedy (duplicitne znaky nepridam)
	for (int i = 0; i < 25; i++)
	{
		if (!MatrixValuesContainsChar(matrixValues, abeceda[i]))
			matrixValues[iMatrixValue++] = abeceda[i];
	}

	// preklopim matrixValues do matice
	iMatrixValue = 0;
    	for (int iRow = 0; iRow < 5; iRow++)
		for (int iCol = 0; iCol < 5; iCol++)
			matrix[iRow][iCol] = matrixValues[iMatrixValue++];
}

void AddX(char** text)
{

char* oldText = *text;
	int oldSize = strlen(oldText);
	int newSize = oldSize;
	char* newText;

	// pripocitam 1 za kazde rovnake susedne znaky (okrem susednych X)
	for (int i = 1; i < strlen(oldText); i+=2)
		if (oldText[i - 1] == oldText[i])
			newSize++;

	// pripocitam 1, ak je cislo neparne
	if (newSize % 2 > 0)
		newSize++;
	newText = (char*)calloc(newSize + 1, sizeof(char));
	newText[newSize] = 0; // koniec retazca
	newText[newSize - 1] = 'X'; // dam na koniec X; ak ho netreba, tak sa prepise

	// prekopirujem oldText do newText a vlozim X medzi kazde rovnake susedne znaky (okrem susednych X)
	for (int iOld = 0, iNew = 0; iOld < oldSize; iOld+=2)
    	{
		if (iOld + 1 == oldSize) {
			newText[iNew++] = oldText[iOld];
		}
		else {
			if (oldText[iOld] == oldText[iOld + 1] && oldText[iOld] != 'X')
			{
				newText[iNew++] = oldText[iOld];
				newText[iNew++] = 'X';
				newText[iNew++] = oldText[iOld + 1];
			}
            			else
			{
				newText[iNew++] = oldText[iOld];
				newText[iNew++] = oldText[iOld + 1];
			}
		}
	}

	free(oldText); // uvolnim stary smernik
	*text = newText; // vratim si novy smernik

}

void RemoveSpace(char** text)
{
	char* oldText = *text;
	int newSize = strlen(oldText);
	char* newText;

	for (int i = 0; i < strlen(oldText); i++)
		if (oldText[i] == ' ')
			newSize--;

	newText = (char*)calloc(newSize + 1, sizeof(char));
	newText[newSize] = 0; // koniec retazca
    	for (int iOld = 0, iNew = 0; iOld < strlen(oldText); iOld++)
		if (oldText[iOld] != ' ')
			newText[iNew++] = oldText[iOld];

	free(oldText); // uvolnim stary smernik
	*text = newText; // vratim si novy smernik
}

bool IsValid(const char* text, bool alowW)
{
	for (int i = 0; i < strlen(text); i++)
	{
		// platne znaky: A-Z, a-z, medzera
		if ((text[i] >= 'A' && text[i] <= 'Z') ||
        			(text[i] >= 'a' && text[i] <= 'z') ||
			text[i] == ' ')
		{
			continue;
		}

		return false;
	}

	for (int i = 0; i < strlen(text); i++)
	{
		if (text[i] == 'W')
			return false;
	}

	return true;
}
char* Encrypt(char matrix[][5], char* text)
{
	int newSize = strlen(text);
	char* newText;
	int rowA, colA, rowB, colB;

	newSize += (newSize / 2) - 1; // po kazdom druhom znaku pridam medzeru
	// pripocitam 1, ak je cislo neparne
	if (newSize % 2 > 0)
		newSize++;

	newText = (char*)calloc(newSize + 1, sizeof(char));
	newText[newSize] = 0; // koniec retazca
	for (int iOld = 0, iNew = 0; iOld < strlen(text); iOld+=2)
	{
		// pridam medzeru medzi zasifrovane dvojice
		if (iNew > 0)
			newText[iNew++] = ' ';

		rowA = -1;
		colA = -1;
		rowB = -1;
		colB = -1;

		// najdem suradnice rowA, colA, rowB, colB v matici
		for (int iRow = 0; iRow < 5; iRow++)
		{
			for (int iCol = 0; iCol < 5; iCol++)
            {
				if (matrix[iRow][iCol] == text[iOld])
				{
					rowA = iRow;
					colA = iCol;
				}
				if (matrix[iRow][iCol] == text[iOld + 1])
				{
					rowB = iRow;
					colB = iCol;
				}
			}
		}

		// na rozdielnych riadkoch a stlpcoch matice 5x5, nahradia sa pismenami na priesecnikoch danych stlpcov a riadkov
		if (rowA != rowB && colA != colB)
		{
        	newText[iNew++] = matrix[rowA][colB];
			newText[iNew++] = matrix[rowB][colA];
		}
		// v rovnakom stlpci matice 5x5, nahradia sa pismenami pod nimi
		else if (colA == colB)
		{
			newText[iNew++] = matrix[(rowA + 1) % 5][colA];
			newText[iNew++] = matrix[(rowB + 1) % 5][colB];
		}
		// na rovnakom riadku matice 5x5, nahradia sa pismenami napravo od nich
		else //if (rowA == rowB)
		{
        newText[iNew++] = matrix[rowA][(colA + 1) % 5];
			newText[iNew++] = matrix[rowB][(colB + 1) % 5];
		}
	}

	return newText;
}

char* Decrypt(char matrix[][5], char* text)
{
	int newSize = strlen(text);
	char* newText;
	int rowA, colA, rowB, colB;

	newText = (char*)calloc(newSize + 1, sizeof(char));
	newText[newSize] = 0; // koniec retazca
    for (int iOld = 0, iNew = 0; iOld < strlen(text); iOld += 2)
	{
		rowA = -1;
		colA = -1;
		rowB = -1;
		colB = -1;

		// najdem suradnice rowA, colA, rowB, colB v matici
		for (int iRow = 0; iRow < 5; iRow++)
		{
			for (int iCol = 0; iCol < 5; iCol++)
			{
				if (matrix[iRow][iCol] == text[iOld])
				{
					rowA = iRow;
					colA = iCol;
                    }
				if (matrix[iRow][iCol] == text[iOld + 1])
				{
					rowB = iRow;
					colB = iCol;
				}
			}
		}

		// na rozdielnych riadkoch a stlpcoch matice 5x5, nahradia sa pismenami na priesecnikoch danych stlpcov a riadkov
		if (rowA != rowB && colA != colB)
		{
        	newText[iNew++] = matrix[rowA][colB];
			newText[iNew++] = matrix[rowB][colA];
		}
		// v rovnakom stlpci matice 5x5, nahradia sa pismenami pod nimi (+5, aby som nedostal "-1 % 5")
		else if (colA == colB)
		{
			newText[iNew++] = matrix[(rowA - 1 + 5) % 5][colA];
			newText[iNew++] = matrix[(rowB - 1 + 5) % 5][colB];
		}
		// na rovnakom riadku matice 5x5, nahradia sa pismenami napravo od nich (+5, aby som nedostal "-1 % 5")
		else //if (rowA == rowB)
		{
        	newText[iNew++] = matrix[rowA][(colA - 1 + 5) % 5];
			newText[iNew++] = matrix[rowB][(colB - 1 + 5) % 5];
		}
	}

	return newText;
}


char* playfair_encrypt(const char* key, const char* text)
{
	char* newKey;
	char* newText;
	char* newResult;
	char matrix[5][5];

        if (key == NULL || text == NULL || !IsValid(key,true) || !IsValid(text,true)){
		return NULL;
            }
	newKey = NewString(key);
	RemoveSpace(&newKey);
	if(newKey[0] == 0)
	{
		free(newKey);
        return NULL;
	}

    ToUpper(newKey);
    	ReplaceW(newKey);
	FillMatrix(matrix, newKey);

	newText = NewString(text);
	RemoveSpace(&newText);
	ToUpper(newText);
	ReplaceW(newText);
	AddX(&newText);
	newResult = Encrypt(matrix, newText);

	free(newKey);
	free(newText);
	return newResult;
}
char* playfair_decrypt(const char* key, const char* text)
{
	char* newKey;
	char* newText;
	char* newResult;
	char matrix[5][5];

	if (key == NULL || text == NULL || !IsValid(key,true) || !IsValid(text, false))
		return NULL;

	newKey = NewString(key);
	RemoveSpace(&newKey);
    if(newKey[0] == 0)
	{
		free(newKey);
        return NULL;
	}
    ToUpper(newKey);
	ReplaceW(newKey);
	FillMatrix(matrix, newKey);

    newText = NewString(text);
	RemoveSpace(&newText);
	ToUpper(newText);
	newResult = Decrypt(matrix, newText);

	free(newKey);
	free(newText);
	return newResult;
}

