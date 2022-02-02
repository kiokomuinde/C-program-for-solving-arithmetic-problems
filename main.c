#include "Stack.h"
#include <stdio.h>

#define MAX_LINE_LENGTH 50


int convertToPostfix(char *infixString, char *postfixString);
int evaluatePostfix(char *postfixString);
Stack s;


int main()
{
	FILE *inputFile, *outputFile;
	inputFile = fopen("p1Input.txt", "r");
	outputFile = fopen("p1Output.txt", "w");
	if(inputFile == NULL){

		perror("Error opening input file");
		return -1;
	}

	if (outputFile == NULL)
	{
		perror("Error creating output file");
		return -1;
	}


	//This string will hold the infix equations that are read from inputFile, one at a time.
	char infixString[MAX_LINE_LENGTH];


	//Use fgets to read the next line from the inputFile.
	//Store the line into infixString.
	//The while loop repeats until there are no more lines in the file.
	while(fgets(infixString, MAX_LINE_LENGTH, inputFile)!=NULL){

		//If the line is blank, skip it.
		if(infixString[0] == '\n')
			continue;

		printf("Current infix string: %s",infixString);
		fprintf(outputFile, "Current infix string: %s",infixString);

		//postfixString is a string to store the equation from szInfixString converted into postfix.
		char postfixString[MAX_LINE_LENGTH];

		//Call the convertToPostfix function (that you are to implement below main).
		 // printf("%s\n", infixString);
		//convertToPostfix(infixString, postfixString);
		//int returnMessage =0;
        int returnMessage = convertToPostfix(infixString,postfixString);


		//convertToPostfix should return an integer letting us know if the infix string was in a valid format.
		//If the format is valid (we returned 0), then we call the evalutaePostfix function (that you are to implement below), and print the result of the evalution.
		//If the format is not valid (we returned something other than 0), then we print the corresponding error message.
		switch(returnMessage)
		{

			case 0: //0 means the infix string had no errors.  Go ahead and evaluate the postfix string.
				printf("Postfix string: %s\n",postfixString);
				int result = evaluatePostfix(postfixString);
				printf("It evaluates to %d.\n",result);

				fprintf(outputFile,"Postfix string: %s\n",postfixString);
				fprintf(outputFile,"It evaluates to %d.",result);
				break;
			case 1:  //1 means the infix string is missing a left parenthesis.
				printf("WARNING: Missing left parenthesis.\n");

				fprintf(outputFile, "WARNING: Missing left parenthesis.");
				break;
			case 2: //2 means the infix string is missing a right parenthesis.
				printf("WARNING: Missing right parenthesis.\n");

				fprintf(outputFile, "WARNING: Missing right parenthesis.");
				break;
			case 3: // 3 means missing operator.
				printf("WARNING: Missing operator.\n");

				fprintf(outputFile, "WARNING: Missing operator.");
				break;
			case 4: //4 means missing operand.
				printf("WARNING: Missing operand.\n");

				fprintf(outputFile, "WARNING: Missing operand.");
				break;
			default:
				printf("WARNING: %d.\n", returnMessage);

				fprintf(outputFile, "WARNING: %d.\n\n", returnMessage);


		}
		printf("\n\n");

		fprintf(outputFile, "\n\n");
	}

	fclose(inputFile);
	fclose(outputFile);

	//Free both the StackImp and the array of elements.
	freeStack(s);

	return 0;
}


/*******
int convertToPostfix(char *infixString, char *postfixString)

Input:
infixString is a character array of length <= MAX_LINE_LENGTH that contains an equation in infix format.
postfixString is a currently empty character array of length <= MAX_LINE_LENGTH that we should fill with a postfix representation of infixString.

Output:
We return an integer based on any errors found in infixString.
If there are no errors, return 0.
If there is a missing (, return 1.
If there is a missing ), return 2.
If there is a missing operator, return 3 (for extra credit).
If there is a missing operand, return 4 (for extra credit).
*********/
int convertToPostfix(char *infixString, char *postfixString){


	char myStack[100];
	int top = -1;

	void pushInfix(char x)
	{
	    myStack[++top] = x;
	}

	char popInfix()
	{
	    if(top == -1)
	        return -1;
	    else
	        return myStack[top--];
	}

	int priority(char x)
	{
	    if(x == '(')
	        return 0;
	    if(x == '+' || x == '-')
	        return 1;
	    if(x == '*' || x == '/')
	        return 2;
	    return 0;
	}

	char exp[100];
    char x;
    int k = 0, j = 0, t=0, p = 0, checkOperators = 0, checkOperands =0;

    while(infixString[j] != '\0')
    {

        if(infixString[0] == '*' || infixString[0] == '/') return 4;

        if(isalnum(infixString[j])){

                if(checkOperands == 1) return 3;

                postfixString[k] = infixString[j];
                k++;
                checkOperands++;
                checkOperators = 0;
        }
         else if(infixString[j] == '('){
            checkOperands =0;
            checkOperators = 0;
            p=p+1;
            pushInfix(infixString[j]);

        }
        else if(infixString[j] == ')')
        {
            t=t+1;
            if(t>p){
              return 1;
            }else if(p>t){
                return 2;
            } else{
            while((x = popInfix()) != '('){
                checkOperands =0;
                checkOperators = 0;
                postfixString[k]= x;
                k++;

            }
            }
        }else if (infixString[j] == '/' || infixString[j] == '*' ||infixString[j] == '+' || infixString[j] == '-')
        {
                checkOperands =0;

                if(infixString[j+2] == '\0') return 4;

                if(checkOperators >0) return 4;

        		while(priority(myStack[top]) >= priority(infixString[j])){
                postfixString[k] = popInfix();
                k++;
        		}
            	pushInfix(infixString[j]);

            	checkOperators++;
        }


        j++;
    }

    while(top != -1)
    {
       postfixString[k] = popInfix();
       k++;
        //printf("%c ",popInfix());
    }
    postfixString[k] = '\0';
    if(t>p){
              return 1;
            }else if(p>t){
                return 2;
            }
    return 0;


}



/************
evaluatePostfix(char *postfixString)

Input:
postfixString is a string of length <= MAX_LINE_LENGTH that contains an equation in postfix representation.
If your convertToPostfix() function is correct, this string should be in a valid postfix format.

Output:
Return an integer representing what the postfix equation evaluated to.
************/
int evaluatePostfix(char *postfixString){

	// Create a stack of capacity equal to expression size
	 s = newStack(strlen(postfixString));
	 int i;

	// See if stack was created successfully
	if (!s) return -1;

	// Scan all characters one by one
	for (i = 0; postfixString[i]; ++i)
	{
		// If the scanned character is an operand (number here),
		// push it to the stack.
		if (isdigit(postfixString[i]))
			push(s, postfixString[i] - '0');

		// If the scanned character is an operator, pop two
		// elements from stack apply the operator
		else
		{
			int val1 = pop(s);
			int val2 = pop(s);
			switch (postfixString[i])
			{
			case '+': push(s, val2 + val1); break;
			case '-': push(s, val2 - val1); break;
			case '*': push(s, val2 * val1); break;
			case '/': push(s, val2/val1); break;
			}
		}
	}
	return pop(s);

}

