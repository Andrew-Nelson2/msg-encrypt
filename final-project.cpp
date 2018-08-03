/* -----------------------------------------------------------------------
------
FILE:              finalProjectV4.cpp
DESCRIPTION:
MODIFICATION HISTORY:
Author                   Date                Version
---------------          ----------          --------------
Andrew Nelson           2018-02-05				 			V4
--------------------------------------------------------------------------
--- */



#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//global constants
const int columnSize = 5,
		  rowSize = 5,
		  keywordArraySize = 25,
		  messageArraySize = 125,
		  blockRow = 10,
		  blockColumn = 25;

// function prototypes
void menu();

void caesar();
void inCaesar(int&, int&);
void fileCaesarIn();
void caesarEncoder(char[], int, int);         //parameter: array, key, and message size in characters.
void caesarCipherOutFile();				                  //parameter: array, key
void caesarUserCipherIn();
void fileCipherIn();
void caesarDecoder(int, char[], int, int);

void playfair();
void playfairIn(int&, int&, int&);
void playfairBuildKey(char[], char[rowSize][columnSize], int);
void playfairEncode(char[], char[rowSize][columnSize], int&, int&);
void shift(int&, int&, int&, int&, char&, char&, char[rowSize][columnSize], int&);


void column();
void columnIn(int&, int&, int&);
void columnEncode(char[], char[], char[blockRow][blockColumn], char[blockRow][blockColumn], int&, int&, int, int);
void alphaArray(char[], int);
void buildBlock(char[blockRow][blockColumn], char[], char[], int, int, int, int, char[]);
void blockShift(char[blockRow][blockColumn], char[blockRow][blockColumn], char[], int [], int, int, int, int, char[]);


void processMessage(char[], const int, int&, int&);
void toUpper(char[]);
void findSize(char[], int &);

//const int size;									  //global variable






/*--------------------------------------------------
FUNCTION: main
DESCRIPTION: Provides general info to user and
		     controls program
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED: 2018-02-04
----------------------------------------------------*/



int main()
{
	cout << "Welcome to finalProject.cpp This program will encode or " << endl;
	cout << "decode a message given either from user or file input" << endl;
	cout << "using the Caesar, Playfair, or Columnar transposition" << endl;
	cout << "cypher." << endl;

	menu();
	return 0;
}

/*--------------------------------------------------
FUNCTION:  menu
DESCRIPTION: accepts user choice and calls appropriate
			 function
RECIEVES: n/a
RETURNS: void
NOTES:
LAST MODIFIED: 2018-07-04
----------------------------------------------------*/

void menu()
{
	int choice = 0;
	do
	{
		cout << "Select a cipher." << endl;
		cout << "1. Encrypt/decrypt using Caesar Cipher" << endl;
		cout << "2. Encrypt/decrypt using Playfair Cipher" << endl;
		cout << "3. Encrypt/decrypt using Columnar Transposition" << endl;
		cout << "4. Quit" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1: caesar();
			break;

		case 2:
			playfair();
			break;

		case 3:
			column();
			break;

		case 4: cout << "Goodbye." << endl;
			break;

		default: cout << "Invalid entry" << endl;
			break;

		}
	} while (choice != 4);

}

/*--------------------------------------------------
FUNCTION: caesar
DESCRIPTION: Gives user the option to encode or decode
			 using user input or file input
RECIEVES:
RETURNS: void
NOTES:
LAST MODIFIED:
----------------------------------------------------*/

void caesar()
{
	int choice = 0,
		inSwitch = 0,
		codeSwitch = 0;



	do
	{
		cout << "Caesar Cipher options:" << endl;
		cout << "1. Encode message using keyboard input" << endl;
		cout << "2. Encode message using file input" << endl;
		cout << "3. Decode message using keyboard input" << endl;
		cout << "4. Decode message using file input" << endl;
		cout << "5. Return to main menu" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			inSwitch = 1;
			codeSwitch = 1;
			inCaesar(inSwitch, codeSwitch);
			break;
		case 2:
			inSwitch = 2;
			codeSwitch = 1;
			fileCaesarIn();
			break;
		case 3:
			inSwitch = 1;
			codeSwitch = 2;
			caesarUserCipherIn();
			break;
		case 4:
			inSwitch = 2;
			codeSwitch = 2;
			fileCipherIn();
			break;
		case 5: cout << "Returning to main menu" << endl;
			break;
		default: cout << "invalid entry" << endl;
			break;
		}
	} while (choice != 5);
}


/*--------------------------------------------------
FUNCTION: inCaesar
DESCRIPTION: Takes user input, and sends it to
			 the functions caesarLogFile, and
			caesarEncoder. Asks user for multiple messages.
RECIEVES:
RETURNS: void
NOTES:
LAST MODIFIED:	2018-07-04
----------------------------------------------------*/

void inCaesar(int &inSwitch, int &codeSwitch)
{
	const int charArraySize = 125;
	char	  message[charArraySize],
			  fileNameOutOne[charArraySize],
		      fileNameOutTwo[charArraySize],
		      fileNameInOne[charArraySize],
		      inputDone = 'n';
	int       userKey,
	          messageSize,
		      count,
		      empty = 0,
		      messageCount = 1;

	ofstream  inputFile,
		      outputFileOne,
		      outputFileTwo;

	// loopCount = 0;


	do
	{

		if (inputDone != 'y') //if the user decides to add another message, it appendes the current file
		{
			cout << "User input will be logged in a formatted file that " << endl;
			cout << "can be encoded again later using option 2 in the " << endl;
			cout << "Caesar menu." << endl;
			cout << "Please enter a name for this file: ";
			cin >> fileNameOutOne;
			cout << endl;
			cout << "Encoded message will also be stored in a formatted" << endl;
			cout << "file to be decoded later using option 4 in the" << endl;
			cout << "Caesar menu." << endl;
			cout << "Please enter a name for this file: ";
			cin >> fileNameOutTwo;
			cout << endl;
			outputFileOne.open(fileNameOutOne);
			outputFileTwo.open(fileNameOutTwo);
		}
		cout << "Enter an integer value no greater than 25. this will be used as an encryption key. " << endl;
		cout << "as an encryption key.  " << endl;
		cin >> userKey;
		cout << "Enter message under 125 characters long " << endl;
		cin.ignore();														//necessary because of cin >> userkey. Memory pointed at nothing
		cin.getline(message, 125);


		processMessage(message, charArraySize, messageSize, empty);
		outputFileOne << userKey << endl;
		outputFileOne << message << endl;
		cout << "Message to encode: " << endl;
		cout << message << endl;
		caesarEncoder(message, messageSize, userKey);

		outputFileTwo << userKey << endl;
		outputFileTwo << message << endl;

		cout << "Coded message: " << endl;
		cout << message << endl;
		inputDone = 'y';													//resets inputDone iteration
		cout << "Enter another phrase? (y/n)" << endl;
		cin >> inputDone;
		if (inputDone == 'y')
			messageCount++;
		if (messageCount == 3)
			cout << "Maximum number of messages entered." << endl << endl;
	} while (inputDone == 'y' && messageCount !=3);

	outputFileOne.close();
	outputFileTwo.close();

}


/*--------------------------------------------------
FUNCTION: fileCaesarIn
DESCRIPTION: Reads from caesarMessage.txt and sends
			 the message to caesarEncoder.
RECIEVES:
RETURNS: void
NOTES:
LAST MODIFIED: 2018-07-04
----------------------------------------------------*/

void fileCaesarIn()
{
	ifstream    inputFile;
	ofstream	outputFileOne,
		outputFileTwo;
	const int   textIn = 80;
	char        message[textIn],
		messageTwo[textIn],
		inputFileName[textIn],
		inputFileNameTwo[textIn];
	int         fileKey,
		fileKeyTwo,
		messageSize,
		messageSizeTwo,
		messageCount = 1;

	cout << "Enter file name you want to encode: " << endl;
	cin >> inputFileName;
	inputFile.open(inputFileName);

	inputFile >> fileKey;
	inputFile >> message;
	if (inputFile >> fileKeyTwo)
	{
		inputFile >> messageTwo;
		messageCount++;
	}




	messageSize = 0;												   //resets messageSize
	do                                                                 //Keep track of characters entered
	{
		messageSize++;
	} while (message[messageSize] != '\0');

	if (messageCount == 2)
	{
		messageSizeTwo = 0;
		do
		{
			messageSizeTwo++;
		} while (messageTwo[messageSizeTwo] != '\0');
	}


	cout << "Message to encode: " << endl;
	cout << message << endl;
	if (messageCount == 2)
		cout << messageTwo << endl;

	caesarEncoder(message, messageSize, fileKey);
	if (messageCount == 2)
		caesarEncoder(messageTwo, messageSizeTwo, fileKeyTwo);

	cout << "Decoded message: " << endl;
	cout << message << endl;
	if (messageCount == 2)
		cout << messageTwo << endl << endl;

	inputFile.close();


}


/*--------------------------------------------------
FUNCTION: caesarUserCipherIn
DESCRIPTION: Accepts user input and sends it to caesarDecoder
RECIEVES:
RETURNS: void
NOTES:
LAST MODIFIED: 2018-04-07
----------------------------------------------------*/

void caesarUserCipherIn()
{
	const int userCipherSize = 80;
	int       count,
		      uCipherKey,
		      messageCount = 1,
		      cipherMessageSize;
	char	  userCipher[userCipherSize],
		      userDone;


		cout << "Enter encryption key" << endl;
		cin >> uCipherKey;
		cout << "Enter cipher text" << endl;
		cin.ignore();
		cin.getline(userCipher, 80);

		count = 0;															//resets count for iterations beyond 1
		while (userCipher[count] != '\0')								    //convert message to all uppercase
		{
			userCipher[count] = toupper(userCipher[count]);
			count++;
		}

		cipherMessageSize = 0;                                             //resets cipherMessageSize for ierations beyond 1
		do                                                                 //counts the size of the message input
			cipherMessageSize++;
		while (userCipher[cipherMessageSize] != '\0');
		cout << "Message to decode:" << endl;
		cout << userCipher << endl;
		caesarDecoder(uCipherKey, userCipher, cipherMessageSize,  0); //function call to caesarDecoder //the zero is the index passed from fileCipherIn...not needed here
		cout << "Encoded message: " << endl;
		cout << userCipher << endl << endl;




}

/*--------------------------------------------------
FUNCTION: fileCipherIn
DESCRIPTION: receives an encoded message from
			 caesarMessage.txt and sends it to caesarDecoder
RECIEVES:
RETURNS: void
NOTES:
LAST MODIFIED: 2018-04-07
----------------------------------------------------*/

void fileCipherIn()
{
	ifstream    inputFile;
	ofstream	outputFileOne,
		        outputFileTwo;
	const int   textIn = 80;
	char        message[textIn],
				messageTwo[textIn],
		        inputFileName[textIn],
		        inputFileNameTwo[textIn];
	int         fileKey,
		        fileKeyTwo,
		        messageSize,
		        messageSizeTwo,
		        messageCount = 1;

	cout << "Enter file name you want to decode: " << endl;
	cin >> inputFileName;
	inputFile.open(inputFileName);

	inputFile >> fileKey;
	inputFile >> message;
	if (inputFile >> fileKeyTwo)
	{
		inputFile >> messageTwo;
		messageCount++;
	}




	messageSize = 0;												   //resets messageSize
	do                                                                 //Keep track of characters entered
	{
		messageSize++;
	} while (message[messageSize] != '\0');

	if (messageCount == 2)
	{
		messageSizeTwo = 0;
		do
		{
			messageSizeTwo++;
		} while (messageTwo[messageSizeTwo] != '\0');
	}


	cout << "Message to decode: " << endl;
	cout << message << endl;
	if(messageCount == 2)
	 cout << messageTwo << endl;

	caesarDecoder(fileKey, message, messageSize, 0);
	if(messageCount == 2)
		caesarDecoder(fileKeyTwo, messageTwo, messageSizeTwo, 0);

	cout << "Decrypted message: " << endl;
	cout << message << endl;
	if (messageCount == 2)
		cout << messageTwo << endl << endl;

	inputFile.close();
}

/*--------------------------------------------------
FUNCTION: caesarEncoder
DESCRIPTION: encodes plain text input provided by the
user or plainTextCaesar.txt, encodes it,
and writes it to caesarMessage.txt.
RECIEVES:
RETURNS: void
NOTES:
LAST MODIFIED: 2018-04-07
----------------------------------------------------*/

void caesarEncoder(char message[], int messageSize, int encryptKey)
{
	const int cMessageSize = 125,
		alphabetSize = 26;
	int		  wrapCount = 0,
		wrapAdd,
		addVar = 'A' - 1;											//addition variable for wrapping the array
	char     letterStart = 'A',
		outCaesar[cMessageSize],
		alphabet[alphabetSize];

	//encodes message
	for (int count = 0; count < messageSize; count++)					//count < messageSize supposed to only shift
	{

		message[count] = message[count] + encryptKey;
		if (message[count] > 'Z')								        //wraps around the array in case of 'Z' or higher
		{
			wrapAdd = message[count] - 90;
			message[count] = addVar + wrapAdd;
		}
	}
	//prints a newline in inputFile
	cout << endl;


}

/*--------------------------------------------------
FUNCTION: caesarDecoder
DESCRIPTION: Decodes an encrypted message provided by
			 caesarMessage.txt or the user
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED: 2018-04-07
----------------------------------------------------*/

void caesarDecoder(int key, char message[],const int messageSize, int index)	//also messageSize
{
	const int decMessageSize = 80,
		      addVar = 'Z' + 1;
	int		  wrapSubtract = 0;


	for (int count = index; count < messageSize + index; count++) //replace decMessageSize with messageSize
	{
		message[count] = message[count] - key;
		if (message[count] < 'A')
		{
			wrapSubtract = 65 - message[count];
			message[count] = addVar - wrapSubtract;
		}


	}
	cout << endl;


}


/*--------------------------------------------------
FUNCTION: playfair
DESCRIPTION: playfair main menu
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED: 2018-18-04
----------------------------------------------------*/

void playfair()
{

	int choice;
	int codeSwitch; //encode options set to 1. decode options set to 2
	int inSwitch;   //user input set to 1. file input set to 2
	int codeType = 2; //used to activae certain processes in functions used by other parts of the program

	do
	{
		cout << "Playfair Cipher options:" << endl;
		cout << "1. Encode message using keyboard input" << endl;
		cout << "2. Encode message using file input" << endl;
		cout << "3. Decode message using keyboard input" << endl;
		cout << "4. Decode message using file input" << endl;
		cout << "5. Return to main menu" << endl;
		cin >> choice;
		//do while loop causes option to enter another message not to accept a 'no' answer
		switch (choice)
		{
		case 1:
			codeSwitch = 1;
			inSwitch = 1;
			playfairIn(codeSwitch, inSwitch, codeType);
			break;
		case 2:
			codeSwitch = 1;
			inSwitch = 2;
			playfairIn(codeSwitch, inSwitch, codeType);
			break;
		case 3:
			codeSwitch = 2;
			inSwitch = 1;
			playfairIn(codeSwitch, inSwitch, codeType);
			break;
		case 4:
			codeSwitch = 2;
			inSwitch = 2;
			playfairIn(codeSwitch, inSwitch, codeType);
			break;
		case 5: cout << "Returning to main menu" << endl;
			break;
		default: cout << "invalid entry" << endl;
			break;
		}
	} while (choice != 5);


}

/*--------------------------------------------------
FUNCTION: playfairIn
DESCRIPTION: get keyword and message call all other functions
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED: 2018-25-04
----------------------------------------------------*/
void playfairIn(int &codeSwitch, int &inSwitch, int &codeType)
{
	const int fileNameSize = 25,
			  keywordArraySize = 25,
		      messageArraySize = 125;
	char	  keyword[keywordArraySize],
		      keybox[rowSize][columnSize],
			  message[messageArraySize];
	int	      keywordSize,
			  messageSize;
	char      fileNameOutOne[fileNameSize],
		      fileNameOutTwo[fileNameSize],
		      inputFileName[fileNameSize];
	ofstream  outputFileOne,
		      outputFileTwo;
	ifstream  inputFile;

	//if user input
	if (inSwitch == 1)
	{
		//prompt user to name output files
		if (codeSwitch == 1)
		{
			cout << "User input will be logged in a formatted file that " << endl;
			cout << "can be encoded again later using option 2 in the " << endl;
			cout << "playfair menu." << endl;
			cout << "Please enter a name for this file: ";
			cin >> fileNameOutOne;
			cout << endl;
			cout << "Encoded message will also be stored in a formatted" << endl;
			cout << "file to be decoded later using option 4. in the" << endl;
			cout << "playfair menu." << endl;
			cout << "Please enter a name for this file: ";
			cin >> fileNameOutTwo;
			cout << endl;
		}
		//propt user to name output files
		if (codeSwitch == 2)
		{
			cout << "User input will be logged in a formatted file that " << endl;
			cout << "can be decoded again later using option 4 in the " << endl;
			cout << "playfair menu." << endl;
			cout << "Please enter a name for this file: ";
			cin >> fileNameOutOne;
			cout << endl;
			cout << "Encoded message will also be stored in a formatted" << endl;
			cout << "file to be encoded later using option 4. in the" << endl;
			cout << "playfair menu." << endl;
			cout << "Please enter a name for this file: ";
			cin >> fileNameOutTwo;
			cout << endl;

		}



		cout << "Enter a keyword under 25 characters long" << endl;
		cout << "without using repeated characters." << endl;
		cin.ignore();
		cin.getline(keyword, keywordArraySize);

		if (codeSwitch == 1)
			cout << "Enter message to encode." << endl;
		if (codeSwitch == 2)
			cout << "Enter message to decode." << endl;

		cin.getline(message, messageArraySize);
	}
	//if file input
	if (inSwitch == 2)
	{
		if (codeSwitch == 1)
		{
			cout << "Enter file name you wish to encode " << endl;
			cin >> inputFileName;
			cout << "Output will be stored in a formatted" << endl;
			cout << "file for later decoding." << endl;
			cout << "Please name this file: ";
			cin >> fileNameOutTwo;

		}


		if (codeSwitch == 2)

		{
			cout << "Enter a file name you want to decode: " << endl;
			cin >> inputFileName;
			cout << "Output will be stored in a formatted" << endl;
			cout << "file for later encoding." << endl;
			cout << "Please name this file: ";
			cin >> fileNameOutTwo;
		}


		inputFile.open(inputFileName);
		inputFile >> keywordSize;
		inputFile >> keyword;
		inputFile >> messageSize;
		inputFile >> message;

	}



	    outputFileOne.open(fileNameOutOne);
		outputFileTwo.open(fileNameOutTwo);
		findSize(keyword, keywordSize);
		processMessage(message, messageArraySize, messageSize, codeType);
		playfairBuildKey(keyword, keybox, keywordSize);

		cout << endl;
		cout << "Keyword: " << keyword << endl;
		cout << "Message: " << message << endl;

		//write output files
		if (inSwitch == 1) //this block creates user input files
		{
			outputFileOne << keywordSize << endl;
			outputFileOne << keyword << endl;
			outputFileOne << messageSize << endl;
			outputFileOne << message << endl;
			outputFileOne.close();
		}
		playfairEncode(message, keybox, messageSize, codeSwitch);

		//block creates output file after being encoded/decoded
		outputFileTwo << keywordSize << endl;
		outputFileTwo << keyword << endl;
		outputFileTwo << messageSize << endl;
		outputFileTwo << message << endl;
		outputFileTwo.close();







}

/*--------------------------------------------------
FUNCTION: playfairBuildKey
DESCRIPTION: builds the key block array for playFair
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED:
----------------------------------------------------*/

void playfairBuildKey(char keyword[], char keybox[rowSize][columnSize], int keywordSize)
{
	int       elCount;
	char      letter = 'A';


	toUpper(keyword);
	//loop replaces a consecutively repeated letter with 'X'
	for (int count = 0; count < keywordSize; count++)
	{
		if (keyword[count] == keyword[count + 1])
		{
			keyword[count + 1] = 'X';
		}
	}


	//loop transfers the keyword into the keybox
	elCount = 0;
	for (int i = 0; i < rowSize; i++)							    //nested for loop walks the keybox array
	{
		for (int j = 0; j < columnSize; j++)
		{
			if (elCount < keywordSize)                              //closes any spaces entered by user
			{
				keybox[i][j] = keyword[elCount];					//copies integer from keyword to keybox

			}
			if (keyword[elCount] == ' ')
			{
				j--;
			}
			elCount++;

		}
	}

	//loop adds unused alphabet to the keybox array
	for (int i = 0; i < rowSize; i++)								//nested for loop walks keybox
	{
		for (int j = 0; j < columnSize; j++)
		{
			if (keybox[i][j] < 65 || keybox[i][j] > 90)				//finds the end of the keyword in keybox
			{
				for (int count = 0; count < keywordSize; count++)   //loop walks keyword array
				{
					if (keyword[count] == letter || letter == 'J')	//if the letter is used, skip it. Also restricts 'J'
					{
						letter++;
						//rescans keyword to check for the new letter
						for (int countTwo = 0; countTwo < keywordSize; countTwo++)
						{
							if (keyword[countTwo] == letter)
								letter++;
						}
					}
				}
				keybox[i][j] = letter;								//assign next letter of alphabet to unused keybox element
				letter++;											//increment letter
			}
			//cout << keybox[i][j] << endl;							//test statement
		}
	}

}


/*--------------------------------------------------
FUNCTION: playfairEncode
DESCRIPTION: stores the message letter pair indexes
             and sends them to shift where they are
			 encoded
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED: 2018-25-04
----------------------------------------------------*/


void playfairEncode(char message[], char keybox[rowSize][columnSize], int &messageSize, int &codeSwitch)
{
	int letterSet = 0,
		rowSaveOne,
		rowSaveTwo,
		columnSaveOne,
		columnSaveTwo;
	char letterOne,
		letterTwo;

	while (letterSet < messageSize)
	{
		letterOne = message[letterSet];
		letterTwo = message[letterSet + 1];

		//sets row and column index for first letter
		for(int i = 0; i < rowSize; i++)
		{
			for (int j = 0; j < rowSize; j++)
			{
				if (letterOne == keybox[i][j])
				{
					rowSaveOne = i;
					columnSaveOne = j;
				}
			}
		}
		//sets row and column index for second letter
		for (int p = 0; p < rowSize; p++)
		{
			for (int q = 0; q < columnSize; q++)
			{
				if (letterTwo == keybox[p][q])
				{
					rowSaveTwo = p;
					columnSaveTwo = q;
				}
			}
		}
		shift(rowSaveOne, columnSaveOne, rowSaveTwo, columnSaveTwo, letterOne, letterTwo, keybox, codeSwitch);
		message[letterSet] = letterOne;
		message[letterSet + 1] = letterTwo;
		letterSet = letterSet + 2;
	}
	if (codeSwitch == 1)
		cout << "Encoded message: " << message << endl << endl;
	else if (codeSwitch == 2)
		cout << "Decoded message: " << message << endl << endl;
}

/*--------------------------------------------------
FUNCTION:shift
DESCRIPTION: Performs the necessary playfair cipher
			 shifts to encode the message
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED:
----------------------------------------------------*/
void shift(int &rowSaveOne, int &columnSaveOne, int &rowSaveTwo, int &columnSaveTwo, char &letterOne, char &letterTwo, char keybox[rowSize][columnSize], int &codeSwitch)
{

	//if letters are in the same row, shift the letters to the right. Wrap the array if necessary.
	if (rowSaveOne == rowSaveTwo)
	{
		if (codeSwitch == 1)//if encoding
		{
			//shift right and wrap if necessary
			if (columnSaveOne++ > columnSize)
				letterOne = keybox[rowSaveOne][0];
			else
				letterOne = keybox[rowSaveOne][columnSaveOne++];

			if (columnSaveTwo+1 >= columnSize)
				letterTwo = keybox[rowSaveTwo][0];
			else
				letterTwo = keybox[rowSaveTwo][columnSaveTwo++];
		}
		if (codeSwitch == 2)//if decoding
		{
			//shift left and wrap if necessary
			if (columnSaveOne-- < 0)
				letterOne = keybox[rowSaveOne][4];
			else
				letterOne = keybox[rowSaveOne][columnSaveOne--];

			if (columnSaveTwo-1 < 0)
				letterTwo = keybox[rowSaveTwo][4];
			else
				letterTwo = keybox[rowSaveTwo][columnSaveTwo--];
		}
	}

	//if letters are in the same column, shift the letters down. wrap the array if necessary.
	else if (columnSaveOne == columnSaveTwo)
	{
		if (codeSwitch == 1)//if encoding
		{
			if (rowSaveOne++ > rowSize)
				letterOne = keybox[0][columnSaveOne];
			else letterOne = keybox[rowSaveOne++][columnSaveOne];

			if (rowSaveTwo++ > rowSize)
				letterTwo = keybox[0][columnSaveTwo];
			else letterTwo = keybox[rowSaveTwo++][columnSaveTwo];
		}
		if (codeSwitch == 2)//if decoding
		{
			if (rowSaveOne-- < 0)
				letterOne = keybox[4][columnSaveOne];//test
			else letterOne = keybox[rowSaveOne--][columnSaveOne];

			if (rowSaveTwo-- < 0)
				letterTwo = keybox[4][columnSaveTwo];//test
			else letterTwo = keybox[rowSaveTwo--][columnSaveTwo];
		}

	}

	else if (codeSwitch == 2 && rowSaveOne == rowSaveTwo && columnSaveOne == 4 && columnSaveTwo == 0)
	{
		letterOne = keybox[rowSaveOne][columnSaveOne--];
		letterTwo = keybox[rowSaveTwo][0];
	}
	else if(codeSwitch == 2 && rowSaveOne == rowSaveTwo && columnSaveTwo == 4 && columnSaveOne == 0)
	{
		letterOne = keybox[rowSaveOne][0];
		letterTwo = keybox[rowSaveTwo][columnSaveTwo];
	}


	//columns and rows do not match. swap the corners horizontally
	else
	{
		letterOne = keybox[rowSaveOne][columnSaveTwo];
		letterTwo = keybox[rowSaveTwo][columnSaveOne];
	}
}

/*--------------------------------------------------
FUNCTION: column
DESCRIPTION:
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED:
----------------------------------------------------*/

void column()
{
	int choice = 0;
	int codeSwitch; //encode options set to 1. decode options set to 2
	int inSwitch;   //user input set to 1. file input set to 2
	int codeType = 3;

	do
	{
		cout << "Columnar Transposition Cipher options:" << endl;
		cout << "1. Encode message using keyboard input" << endl;
		cout << "2. Encode message using file input" << endl;
		cout << "3. Decode message using keyboard input" << endl;
		cout << "4. Decode message using file input" << endl;
		cout << "5. Return to main menu" << endl;
		cin >> choice;
															//do while loop causes option to enter another message not to accept a 'no' answer
		switch (choice)
		{
		case 1:
			codeSwitch = 1;
			inSwitch = 1;
			columnIn(codeSwitch, inSwitch, codeType);
			break;
		case 2:
			codeSwitch = 1;
			inSwitch = 2;
			columnIn(codeSwitch, inSwitch, codeType);
			break;
		case 3:
			codeSwitch = 2;
			inSwitch = 1;
			columnIn(codeSwitch, inSwitch, codeType);
			break;
		case 4:
			codeSwitch = 2;
			inSwitch = 2;
			columnIn(codeSwitch, inSwitch, codeType);
			break;
		case 5: cout << "Returning to main menu" << endl;
			break;
		default: cout << "invalid entry" << endl;
			break;
		}
	} while (choice != 5);
}

/*--------------------------------------------------
FUNCTION: columnIn
DESCRIPTION:
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED:
----------------------------------------------------*/

void columnIn(int &codeSwitch, int &inSwitch, int &codeType)
{

	const int fileNameSize = 25,
	          messageArraySize = 120; //max message length is 5 X one less row than the max (because of the keyword) i.e. 120
	int       keywordSize = 0, //passed by reference
		      messageSize = 0; //passed by reference

	ofstream outputFileOne,
		     outputFileTwo;
	ifstream inputFile;
	char	 inputBlock[blockRow][blockColumn],
		     outputBlock[blockRow][blockColumn],
		      message[messageArraySize],
		      keyword[blockColumn],   //keyword has to fit in the first row of blockColumn
		      fileNameOutOne[fileNameSize],
		      fileNameOutTwo[fileNameSize],
		      inputFileName[fileNameSize];




	//if user input
	if (inSwitch == 1)
	{
		if (codeSwitch == 1) //encode option
		{
			cout << "All user input will be written to a formatted file" << endl;
			cout << "that can be encoded later by choosing option 2 in the " << endl;
			cout << "Columnar Transposition Cipher menu." << endl;
			cout << "Please enter a file name: ";
			cin >> fileNameOutOne;
			cout << endl;

			cout << "Encoded message will also be stored in a formatted" << endl;
			cout << "file that can be decoded later using option 4 in " << endl;
			cout << "the Columnar Transposition Cipher menu." << endl;
			cout << "Please enter a file name: ";
			cin >> fileNameOutTwo;
			cout << endl;


			cout << "Enter a keyword under 25 characters long" << endl;
			cout << "Do not use repeated characters" << endl;
		}

		if (codeSwitch == 2) //decode
		{
			cout << "All user input will be written to a formatted file" << endl;
			cout << "that can be decoded later by choosing option 4 in the " << endl;
			cout << "Columnar Transposition Cipher menu." << endl;
			cout << "Please enter a file name: ";
			cin >> fileNameOutOne;
			cout << endl;

			cout << "Decoded message will also be stored in a formatted" << endl;
			cout << "file that can be encoded later using option 2 in " << endl;
			cout << "the Columnar Transposition Cipher menu." << endl;
			cout << "Please enter a file name: ";
			cin >> fileNameOutTwo;
			cout << endl;


			cout << "Enter a keyword under 25 characters long" << endl;
			cout << "Do not use repeated characters" << endl;
		}


		cin.ignore();
		cin.getline(keyword, keywordArraySize);


		if (codeSwitch == 1)
			cout << "Enter message under 125 characters in length to encode: " << endl;
		if (codeSwitch == 2)
			cout << "Enter message under 125 characters in length to decode: " << endl;

		cin.getline(message, messageArraySize);
	}

	//if file input
	if (inSwitch == 2)
	{
		if (codeSwitch == 1)
			cout << "Enter a file name you want to encode: " << endl;
		if (codeSwitch == 2)
			cout << "Enter a file name you want to decode: " << endl;
		cin >> inputFileName;
		inputFile.open(inputFileName);
		inputFile >> keyword;
		inputFile >> message;
	}


	outputFileOne.open(fileNameOutOne);
	outputFileTwo.open(fileNameOutTwo);

	processMessage(keyword, blockColumn, keywordSize, codeType);
	processMessage(message, messageArraySize, messageSize, codeType);

	int rowBuildSize; //used to find the number of rows for the arrays
	if (messageSize % keywordSize == 0)
		rowBuildSize = (messageSize / keywordSize) + 1;
	else rowBuildSize = (messageSize / keywordSize) + 2;


	columnEncode(keyword, message, inputBlock, outputBlock, keywordSize, messageSize, rowBuildSize, codeSwitch);

	//display and enter to file
	cout << endl;
	cout << "Keyword: " << endl;
	cout << keyword << endl;
	cout << "Message: " << endl;
	cout << message << endl << endl;
	cout << "Encoded Message: " << endl;

	outputFileOne << keyword << endl;
	outputFileOne << message << endl;
	outputFileTwo << keyword << endl;

	if (codeSwitch == 1)
	{
		for (int j = 0; j < keywordSize; j++)
		{
			for (int i = 0; i < rowBuildSize - 1; i++)
			{
				cout << outputBlock[i][j];
				outputFileTwo << outputBlock[i][j];
			}
		}
	}

	if (codeSwitch == 2)
	{
		for (int i = 1; i < rowBuildSize; i++)//skipping row 0 to omit the keyword from the solution
		{
			for (int j = 0; j < keywordSize; j++)
			{
				cout << outputBlock[i][j];
				outputFileTwo << outputBlock[i][j];
			}
		}
	}
	cout << endl << endl;

	/*//displays key and message in block output
	cout << "Test outputBlock: " << endl;
	for (int i = 0; i < rowBuildSize; i++)
	{
		for (int j = 0; j < keywordSize; j++)
		{
			cout << outputBlock[i][j];
		}
		cout << endl;
	}*/

}

/*--------------------------------------------------
FUNCTION: columnEncode
DESCRIPTION:
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED:
----------------------------------------------------*/

void columnEncode(char keyword[], char message[], char inputBlock[blockRow][blockColumn], char outputBlock[blockRow][blockColumn], int &keywordSize, int &messageSize, int rowBuildSize, int codeSwitch)
{
	const int arraySize = 25;
	int       alphaCount = 0,
		      positionCount,
		      positionArray[arraySize];
	char      alphaKey[arraySize];



	//copy contents of keyword into alphaKey
	for (int i = 0; i < keywordSize; i++)
		alphaKey[i] = keyword[i];

	alphaArray(alphaKey, keywordSize);


	//build the position array
	for (int j = 0; j < keywordSize; j++)
	{
		positionCount = 1;
		for (int i = 0; i < keywordSize; i++)
		{

			if (keyword[j] == alphaKey[i])
			{
				positionArray[j] = positionCount;
			}
			positionCount++;

		}


	}


	/*cout << "position array: " << endl;
	for (int i = 0; i < keywordSize; i++)
	{
		cout << positionArray[i];
	}*/

	buildBlock(inputBlock, keyword, message, keywordSize, messageSize, rowBuildSize, codeSwitch, alphaKey);
	blockShift(inputBlock, outputBlock, alphaKey, positionArray, keywordSize, messageSize, rowBuildSize, codeSwitch, keyword);





}

/*--------------------------------------------------
FUNCTION: alphaArray
DESCRIPTION:
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED:
----------------------------------------------------*/

void alphaArray(char alphaArray[], int sizeIn)
{
	bool swap;
	int temp;

	do
	{
		swap = false;
		for (int count = 0; count < (sizeIn - 1); count++)
		{
			if (alphaArray[count] > alphaArray[count + 1])
			{
				temp = alphaArray[count];
				alphaArray[count] = alphaArray[count + 1];
				alphaArray[count + 1] = temp;
				swap = true;
			}
		}
	} while (swap);

	alphaArray[sizeIn] = '\0'; //add null terminator to the end of the array to prevent display errors


}

/*--------------------------------------------------
FUNCTION: buildBlock
DESCRIPTION:
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED:
----------------------------------------------------*/

void buildBlock(char inputBlock[blockRow][blockColumn],char keyword[], char message[], int keywordSize, int messageSize, int rowBuildSize, int codeSwitch, char alphaKey[])
{

	int messageCount = 0,
		boxSize,
		boxFill,
		boxComp;



	if (codeSwitch == 1)
	{
		//add keyword to top row of buildBlock
		for (int j = 0; j < keywordSize; j++)
		{
			inputBlock[0][j] = keyword[j];
		}

		//add message to buildBlock
		for (int i = 1; i < rowBuildSize; i++) //starts at second row (i = 1) <------fix: add 'X's when messageCount == messageSize
		{
			for (int j = 0; j < keywordSize; j++)
			{
				if (messageCount != messageSize)
				{
					inputBlock[i][j] = message[messageCount];
					messageCount++;
				}
			}
		}

		boxSize = keywordSize * rowBuildSize;
		boxFill = keywordSize + messageSize;
		boxComp = 1;
		if (boxFill != boxSize)
		{
			for (int i = 0; i < rowBuildSize; i++)
			{
				for (int j = 0; j < keywordSize; j++)
				{
					if (boxComp > boxFill && boxComp <= boxSize)
						inputBlock[i][j] = 'X';
					boxComp++;
				}

			}
		}
	}


	if (codeSwitch == 2)
	{
		messageCount = 0;
		//add keyword to top row of inputBlock
	    for (int j = 0; j < keywordSize; j++)
		{
			inputBlock[0][j] = alphaKey[j];
		}
		//build inputBlock column by column
		for (int j = 0; j < keywordSize; j++)
		{
			for (int i = 1; i < rowBuildSize; i++) //start at 1 because row 0 is already populated with the keyword
			{
				inputBlock[i][j] = message[messageCount];
				messageCount++;

			}

		}
	}
}

/*--------------------------------------------------
FUNCTION: blockShift
DESCRIPTION:
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED:
----------------------------------------------------*/

void blockShift(char inputBlock[blockRow][blockColumn], char outputBlock[blockRow][blockColumn], char alphaKey[], int position[], int keywordSize, int messageSize, int rowBuildSize, int codeSwitch, char keyword[])
{
	if (codeSwitch == 1)
	{
		int	keyRow = 0;

		for (int h = 0; h < keywordSize; h++) //to walk alphaKey
		{
			for (int j = 0; j < keywordSize; j++) //to walk inputBlock colummns
			{
				if (inputBlock[keyRow][j] == alphaKey[h]) //compares the keyword in inputBlock to alphabetized keyword in alphakey
				{
					for (int m = 0; m < rowBuildSize; m++)
					{
						outputBlock[m][h] = inputBlock[m + 1][j]; //m+1 skips the keyword
					}

				}
			}
		}
	}

	//encodes inputBlock and shifts it to outputBlock
	//compares the keyword to alpha key, and shift the
	//entire column.s
	if (codeSwitch == 2)
	{

		for (int m = 0; m < keywordSize; m++) //walks keyword
		{
			for (int n = 0; n < keywordSize; n++) //walks alphaKey
			{
				if (alphaKey[n] == keyword[m])
				{
					for(int q = 0; q < rowBuildSize; q++)
					outputBlock[q][m] = inputBlock[q][n];
				}
			}
		}

	}





}

/*--------------------------------------------------
FUNCTION: toUpper
DESCRIPTION:
RECIEVES:
RETURNS: 0
NOTES:
LAST MODIFIED:
----------------------------------------------------*/

void toUpper(char array[])
{
	int count = 0;													    //resets count for iterations beyond 1
	while (array[count] != '\0')										//convert message to all uppercase
	{
		array[count] = toupper(array[count]);
		count++;
	}
}

/*--------------------------------------------------
FUNCTION: findSize
DESCRIPTION:
RECIEVES:
RETURNS: 0
NOTES:	WORKS
LAST MODIFIED:
----------------------------------------------------*/

void findSize(char array[], int &size)
{
	size = 0;											   //resets messageSize

	do                                                     //Keep track of characters entered
	{
		size++;
	} while (array[size] != '\0');

}

/*--------------------------------------------------
FUNCTION: processMessage
DESCRIPTION:
RECIEVES:
RETURNS: 0
NOTES:	WORKS
LAST MODIFIED:
----------------------------------------------------*/

void processMessage(char message[], const int messageArraySize,int &messageSize, int &codeType)
{

	toUpper(message);
	findSize(message, messageSize);


	//close any spaces
	for (int count = 0; count < messageSize; count++)
	{

		//uses second counter to independantly walk array and shift letters back one to fill the space
		if(message[count] == ' ')
		{
			int countTwo = count;
			while (countTwo < messageArraySize)
			{
				message[countTwo] = message[countTwo + 1];
				countTwo++;
			}
		}
	}
	findSize(message, messageSize); //called a second time to account for closed spaces

	//if message size is not even, add an 'X'
	if (codeType ==2 && messageSize % 2 != 0) //if this is playfair message and the message has an odd number of characters add the 'X'
	{
		message[messageSize] = 'X';
		messageSize++;
		message[messageSize] = '\0';
	}




	findSize(message, messageSize);
}
