#pragma once
#include"stdafx.h"
typedef struct TRAFFIC_RECORD
{
	double value;
	BOOL isConnected;
}TrafficRecords;

//timer
#define GRIDTIMER		1		
#define NETTIMER		2		
//grid 
#define GRIDXSIZE	10		
#define GRIDYSIZE	10		
//scroll speed
#define GRIDSCROLLXSPEED -1		
#define GRIDSCROLLYSPEED 0		

#define GRIDGRANULATRITY 2		
//update speed
#define NETUPDATESPEED	1000	
#define GRIDUPDATESPEED 50		

