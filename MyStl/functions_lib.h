#pragma once
//BoolLean Operations
//Two Operand


bool es(bool input1, bool input2)
{
	return (input1 && input2);
}
bool vagy(bool input1, bool input2)
{
	return (input1 || input2);
}




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

