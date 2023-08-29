//#include "common.h"

#ifndef _common_h_
#include "common.h"
#define _common_h_
#endif

//////////////////////////////////////////////////////////////
//
//			Some common functions
//
//////////////////////////////////////////////////////////////
digitList* multiplyDigitLists(digitList* L1, digitList* L2);

void destroyDL(digitList* L) {
	digitList* p = L;
	while(p!=NULL) {
		digitList* del = p;
		p = p-> getNextDigit();
		delete del;
	}
}

digitList *digitize(char str[80])
{
	
	digitList*	L = 0;
	digitList*	node;

	bool factorial = false;
	bool exponent = false;
	int iFactorial;
	int iExponent;
	int i;

	for(i = 0;; i++)
	{
		if(str[i] < '0' || str[i] > '9') {
			if(str[i] == '!') {
				factorial = true;
				iFactorial = i;
				break;
			}
			else if(str[i]=='^') {
				exponent = true;
				iExponent = i;
				break;
			}
			else {
				break;
			}
		}

		node = new digitList(str[i] - '0', L);
		L = node;
	}

	

	if(factorial) {

		if(L->digit==0 && L->nextDigit == NULL) {
			destroyDL(L);
			return digitize(1);
		}

		int increase = 1;

		digitList* f = digitize(1);
		digitList* c = L;	


		while(compareDigitLists(f,L) < 0) {
			c = multiplyDigitLists(c,f);			
			digitList* del = f;
			increase++;
			f = digitize(increase);
			destroyDL(del);
		}

		destroyDL(f);

		L = c;

		return L;		
	}

	if(exponent) {

		digitList* time = 0;
		digitList* M;

		for(int i = iExponent+1; i< strlen(str); i++) {
			if(str[i] < '0' || str[i] > '9')	break;

			M = new digitList(str[i] - '0', time);
			time = M;
		}
	

		int increase = 0;

		digitList* c = digitize(1);
		digitList* f = new digitList;


		while(compareDigitLists(f,time)<0) {
			c = multiplyDigitLists(L,c);
			digitList* del = f;
			increase ++;
			f = digitize(increase);
			destroyDL(del);
		}

		destroyDL(f);
		destroyDL(time);
		
		

		L = c;
	}

	return L;

}

digitList *trimDigitList(digitList* L)
{
	digitList* t = L;
	digitList* pre = L;

	digitList* savePre = NULL;
	digitList* zeroSequence = NULL;
	bool sequence = false;
	while(t!=NULL) {
		if (t -> digit == 0) {
			if (sequence == false) {
				zeroSequence = t;
				sequence = true;
				savePre = pre;
			}
		}

		else {
			savePre = NULL;
			zeroSequence = NULL;
			sequence = false;
		}

		pre = t;

		t = t -> nextDigit;
	}

	if(savePre!=NULL) {
		bool check = false;
		if(zeroSequence == L) {
			check = true;
		}
		savePre -> nextDigit = NULL;
		digitList* del = zeroSequence;
		while(del!=NULL) {
			digitList* d = del;
			del = del -> nextDigit;
			delete d;
		}

		if(check) {
			return digitize(0);
			
		}
	}

	return L;
}

digitList *subDigitLists(int b, digitList* L1, digitList* L2)
{
	
	if (L1 == NULL && L2 == NULL) {return NULL;}
	else if (L2 == NULL) {
		
		int t = L1 ->getDigit() - b;
		return new digitList(t, subDigitLists(0,L1 ->getNextDigit(), NULL));
	}
	else {
		int t;
		if (L2 -> getDigit()+b > L1 -> getDigit()) {
			t = (10 - (L2 -> getDigit() + b)) + L1 -> getDigit();
			
			return new digitList(t, subDigitLists(1, L1 -> getNextDigit(), L2 -> getNextDigit()));
		}
		else {
			t = L1 -> getDigit() - L2 -> getDigit() -b;
			
			return new digitList(t, subDigitLists(0, L1 -> getNextDigit(), L2 -> getNextDigit()));
		}
	}
	
}

Integer Integer::leftDigits(int n)
{
	return Integer(sign,digits->leftDigits(n));
}

Integer Integer::rightDigits(int n)
{
	return Integer(sign,digits->rightDigits(n));
}

digitList* shiftHelper(digitList* p, int n) {
	if(n==0) {return p;}

	digitList * q= new digitList;
	q -> digit = 0;
	q -> nextDigit = shiftHelper(p, n-1);

	return q;
}

Integer	Integer::shift(int n)
{
	Integer res = Integer(sign,shiftHelper(digits,n));
	return res;
}//Not so helpful


Integer computeValue(int operatorNum)
{
	Integer		L1, L2	 ;//L3, L4 does not belong to program, test only

	L1 = operandArr[0];

	cout<<"here";



	for(int i = 0; i<operatorNum; i++)
	{
		L2 = operandArr[i+1];
		switch(operatorArr[i])
		{
		case '+':
			L1 = L1 + L2;
			break;
		case '-':
			L1 = L1 - L2;
			break;
		case '*':
			L1 = L1 * L2;
		}

	}

	return L1;
}
///////////////////////////////////////////////////////////////////////////
//
//		Some methods of Integer class
//
////////////////////////////////////////////////////////////////////
Integer Integer::operator +(Integer L)
{
	Integer result;
	if(sign == L.sign) {
		result = Integer(sign, addDigitLists(0, digits, L.digits));
	}
	else {
		if(sign == -1) {
			int cmp = compareDigitLists(digits, L.digits);
			if(cmp == 1) {
				result = Integer(-1,subDigitLists(0,digits,L.digits));
			}
			else if(cmp == -1) {
				result = Integer(1,subDigitLists(0,L.digits,digits));
			}
			else {
				result = Integer(1,digitize(0));
			}
		}

		else {
			int cmp = compareDigitLists(digits, L.digits);
			if (cmp == 1) {
				result = Integer(1,subDigitLists(0,digits,L.digits));
			}
			else if (cmp == -1) {
				result = Integer(-1,subDigitLists(0,L.digits,digits));
			}
			else {
				result = Integer(1,digitize(0));
			}
		}
	}

	return result.trimDigit();
}

Integer Integer::operator -(Integer L)
{
	Integer result;
	if(sign == L.sign) {
		int cmp = compareDigitLists(digits,L.digits);
		if(cmp == 1) {
			result = Integer(sign, subDigitLists(0, digits, L.digits));
		}
		else if (cmp == -1) {
			result = Integer(-sign, subDigitLists(0,L.digits,digits));
		}
		else {
			result = Integer(1,digitize(0));
		}
	}
	else {
		if(sign == -1) {
			result = Integer(-1, addDigitLists(0,digits,L.digits));
		}
		else {
			result = Integer(1,addDigitLists(0,digits,L.digits));
		}
	}

	return result.trimDigit();
}

digitList* multiplyDigitLists(digitList* L1, digitList* L2) {
	if(L1 == NULL || L2 == NULL) {
		return NULL;
	}

	digitList* p1 = digitize(L1 -> digit * L2 -> digit);



	digitList* p2 = multiplyDigitLists(L1->rightDigits(L1->length()-1),L2->leftDigits(1));
	digitList* p3 = multiplyDigitLists(L1->leftDigits(1),L2->rightDigits(L2->length()-1));

	digitList* p4 = addDigitLists(0,p2,p3);

	digitList* p5 = multiplyDigitLists(L1->rightDigits(L1->length()-1),L2->rightDigits(L2->length()-1));


	digitList* res = addDigitLists(0, addDigitLists(0,p1,shiftHelper(p4,1)) ,shiftHelper(p5,2));

	return res;
}

Integer Integer::operator *(Integer Y)
{

	if(sign!=Y.sign) {
		return Integer(-1,trimDigitList(multiplyDigitLists(digits,Y.digits)));
	}
	return Integer(1,trimDigitList(multiplyDigitLists(digits,Y.digits)));
}
