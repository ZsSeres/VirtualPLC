#pragma once
using namespace std;
#include "registers.h"
#include"Inter_Container.h"
//BoolLean Operations
///////////////////////////////////////////////////////////
bool neg(bool input)
{
	return !input;
}

//Two Operand


bool es(bool input1, bool input2)
{
	return (input1 && input2);
}
bool vagy(bool input1, bool input2)
{
	return (input1 || input2);
}
bool nand(bool input1, bool input2)
{
	return !(es(input1, input2));
}

bool nor(bool input1, bool input2)
{
	return !(vagy(input1, input2));
}
bool _xor(bool input1, bool input2)
{
	if (input1 == input2)
	{
		return false;
	}
	else
		return true;
}


//Aritmetic functions
int add(int a, int b)
{
	return a + b;

}
int mul(int a, int b)
{
	return a * b;
}
int sub(int a, int b)
{
	return a - b;
}

//More than two Operand: Looping_Functions:

bool Bool_Looping_Function(bool (*fv_single_param)(bool, bool), bool (*fv_multiple_param)(bool, bool), bool* param, int param_num, bool RLO)
{
	bool result;
	if (param_num == 1)
	{
		result = fv_single_param(param[0], RLO);
	}
	if (param_num >= 2)
	{
		result = fv_multiple_param(param[0], param[1]);
		for (int i = 2; i < param_num; i++)
		{
			result = fv_multiple_param(result, param[i]);
		}
	}
	return result;
}

void AND(Line* line,Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	sw->RLO= Bool_Looping_Function(&es, &es, inter_container->bool_inter_container.param(), inter_container->bool_inter_container.elem_num, sw->RLO);
}

void OR(Line* line,Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	sw->RLO=Bool_Looping_Function(&vagy, &vagy, inter_container->bool_inter_container.param(), inter_container->bool_inter_container.elem_num, sw->RLO);
}

void NAND(Line* line,Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	sw->RLO = Bool_Looping_Function(&nand, &nand, inter_container->bool_inter_container.param(), inter_container->bool_inter_container.elem_num, sw->RLO);
}

void NOR(Line* line,Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	sw->RLO = Bool_Looping_Function(&nor, &nor, inter_container->bool_inter_container.param(), inter_container->bool_inter_container.elem_num, sw->RLO);
}

//XOR-t csak 1 vagy 2 operandusra engedem meg
void XOR(Line* line,Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	if (inter_container->bool_inter_container.elem_num == 1 || inter_container->bool_inter_container.elem_num == 2) {
		sw->RLO = Bool_Looping_Function(&_xor, &_xor, inter_container->bool_inter_container.param(), inter_container->bool_inter_container.elem_num, sw->RLO);
	}
	else
	{
		sw->ERROR=true;
		cout << "Invalid parameter number!" << endl;
	}

}
void NEG(Line* line,Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	if (inter_container->bool_inter_container.elem_num == 0)
	{
		sw->RLO = neg(sw->RLO);
	}
	else if (inter_container->bool_inter_container.elem_num == 1)
		sw->RLO = neg(inter_container->bool_inter_container.get(0));
	else
	{
		sw->ERROR = true;
		cout << "Invalid parameter number!" << endl;
	}
	
}

//ARITMETIC OPERATIONS:
//Mivel csak egész számunk van eddig, nem lesz osztás
/*void Int_Looping_Function( int (*fv_multiple_param)(bool, bool), bool* param, int param_num, int *target)
{
	if (param_num == 1)
	{
		cout << target;
	}
	if (param_num >= 2)
	{
		target = fv_multiple_param(param[0], param[1]);
		for (int i = 2; i < param_num; i++)
		{
			result = fv_multiple_param(result, param[i]);
		}
	}
	return result;
}*/


void Aritmetic_Looping_Function(int (*fv)(int, int),Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container)
{
	int result = user_memory->int_register_container.get_by_name(line->get_parameter(0));
	if (line->get_parameter_num() == 1)
	{
		cout << result<<endl;
	}
	else if (line->get_parameter_num() >= 2) {
		result = fv(inter_container->int_inter_container.get(0),inter_container->int_inter_container.get(1));
		for (int i = 2; i < inter_container->int_inter_container.elem_num; i++)
		{
			result = fv(result,inter_container->int_inter_container.get(i));
		}
		user_memory->int_register_container.set_by_name(line->get_parameter(0), result);
	}
	else {
		sw->ERROR = true;
		cout << "Invalid paramerer number!"<<endl;
	}
}

void ADD(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	Aritmetic_Looping_Function(&add, line, user_memory, sw, inter_container);
}

void SUB(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	Aritmetic_Looping_Function(&sub, line, user_memory, sw, inter_container);
}

void MUL(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	Aritmetic_Looping_Function(&mul, line, user_memory, sw, inter_container);
}

//TODO Kisebb, nagyobb, DEG,INC

void EQUAL(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container,Label_Container* label_container)
{
	if (inter_container->int_inter_container.elem_num == 2) {
		if (inter_container->int_inter_container.get(0) == inter_container->int_inter_container.get(1)) {
			sw->RLO = true;
		}
		else
			sw->RLO = false;
	}
	else
	{
		sw->ERROR = true;
		cout << "Invalid parameter number!"<<endl;
	}
}
///Ugró utasítások
void JMP(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container,Label_Container* label_container)
{
	if (line->get_parameter_num() == 1)//feltétel nélküli ugrás
	{
		sw->STACK = sw->PC;//ha a címkérõl RET-et hívunk akkor hová kell visszatérni
		sw->PC = label_container->find_line_num(line->get_parameter(0))-1;
	}

	//ha ezt megcsináljuk int-re és 0-ra vizsgálunk, akkor egyszerû forciklus is megvalósítható
	if (line->get_parameter_num() == 2)//feltételes ugrás,ha a második parameter true ugrunk, false nem ugrunk
	{
		inter_container->bool_inter_container._do(line, user_memory->bool_register_container, sw);
		if (inter_container->bool_inter_container.element[1] == true)
		{
			sw->STACK = sw->PC;//ha a címkérõl RET-et hívunk akkor hová kell visszatérni
			sw->PC = label_container->find_line_num(line->get_parameter(0))-1;
		}
	}

}

//Visszatérés
void RET(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	sw->PC = sw->STACK;
	sw->STACK = 0;

}

//Kiolvassa a GPIO szintjét
void  GPIO_READ(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	 //cout<<user_memory->periphery_container.gpio_container.read_by_name(line->get_parameter(0));
}

//Beállítja a GPIO szintjét
void  GPIO_WRITE(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	//user_memory->periphery_container.gpio_container.set_by_name(line->get_parameter(0), line->get_parameter(1));
}
//bool bool egyenlõvé tétel:
void EQUBOOLBOOL(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	string firstoperand = line->get_parameter(0);
	bool secondoperand = inter_container->bool_inter_container.element[1];
	if (user_memory->bool_register_container.iscreated(firstoperand))//ha létezik az adott nevû változzó
	{
		user_memory->bool_register_container.get_by_name(firstoperand)->set_value(secondoperand);
	}
}

//int int egyenlõvé tétel:
void EQUINTINT(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	string firstoperand = line->get_parameter(0);
	int secondoperand = inter_container->int_inter_container.element[1];
	if (user_memory->int_register_container.iscreated(firstoperand))//ha létezik az adott nevû változzó
	{
		user_memory->int_register_container.getbyname(firstoperand)->set_value(secondoperand);
	}
}

//bool int egyenlõvé tétel:
void EQUBOOLINT(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	string firstoperand = line->get_parameter(0);
	int secondoperand = inter_container->int_inter_container.element[1];
	bool convertedsecondoperand;
	if (secondoperand = 0)
		convertedsecondoperand = false;
	else if (secondoperand = 1)
		convertedsecondoperand = true;
	else 
	{
		sw->ERROR = true;
		cout << "Invalid conversion!";
		return;
	}
	if (user_memory->bool_register_container.iscreated(firstoperand))//ha létezik az adott nevû változzó
	{
		user_memory->bool_register_container.get_by_name(firstoperand)->set_value(convertedsecondoperand);
	}
}

void EQUINTBOOL(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	string firstoperand = line->get_parameter(0);
	bool secondoperand = inter_container->bool_inter_container.element[1];
	int convertedsecondoperand;
	if (secondoperand == true)
		convertedsecondoperand = 1;
	if (secondoperand == false)
		convertedsecondoperand = 0;
	if (user_memory->int_register_container.iscreated(firstoperand))//ha létezik az adott nevû változzó
	{
		user_memory->int_register_container.getbyname(firstoperand)->set_value(convertedsecondoperand);
	}
}


//Egyenlõvé tevõ operátor:
//Elsõ operandos értékét beállítja a második operanduséra
//Converziók:
//BOOL->INT:
//False->0;TRUE->1
//Elõször INT-INT:
void  EQUALS(Line* line, Memory* user_memory, status_word* sw, Inter_Container* inter_container, Label_Container* label_container)
{
	if (line->get_parameter_num() == 2)//csak 2 operandusra valid 
	{
		inter_container->bool_inter_container._do(line, user_memory->bool_register_container, sw);
		inter_container->int_inter_container._do(line, user_memory->int_register_container, sw);
		sw->ERROR = 0;//itt az inter_containerek generálhatnak hibát, de ki nullázom mert tisztába vagyok vele :3
		
		if (user_memory->gettype(line->get_parameter(0)) == "bool") 
		{
			if ((user_memory->gettype(line->get_parameter(1)) == "bool") || line->get_parameter(1) == "true" || line->get_parameter(1) == "false")
				EQUBOOLBOOL(line, user_memory, sw, inter_container, label_container);//BOOL-BOOL conversion
			else
				EQUBOOLINT(line, user_memory, sw, inter_container, label_container);//BOOL-INT conversion
		}
		if (user_memory->gettype(line->get_parameter(0)) == "int")
		{
			if (user_memory->gettype(line->get_parameter(1)) == "bool" || line->get_parameter(1) == "true" || line->get_parameter(1) == "false")
			{
				EQUINTBOOL(line, user_memory, sw, inter_container, label_container);//INT-BOOL conversion
			}
			else
				EQUINTINT(line, user_memory, sw, inter_container, label_container);//INT-INT conversion
		}
	}
	else 
	{
		sw->ERROR = true;
		cout << "Invalid parameter number";
	}
}

