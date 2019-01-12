#pragma once
#include <map>

enum Method
{
	SEQUENCE,
	OMP,
	MPI
};

const std::map<std::string, Method> methodMap =  
{
	{"SEQUENCE", Method::SEQUENCE},
	{"OMP", Method::OMP},
	{"MPI", Method::MPI}
};