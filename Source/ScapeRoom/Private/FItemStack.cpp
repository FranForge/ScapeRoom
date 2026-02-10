// Fill out your copyright notice in the Description page of Project Settings.


#include "FItemStack.h"

FItemStack::FItemStack() : ItemDef(nullptr), Quantity(0) {}

FItemStack::FItemStack(UItemDefinition* ItemDef, int32 Quantity) : ItemDef(ItemDef), Quantity(Quantity) {}

FItemStack::~FItemStack()
{
}
