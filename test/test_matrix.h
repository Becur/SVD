#pragma once

int main/*TestMatrix*/();

void TestEqual();
void TestCopyMove();
void TestGetSize();
void TestEmpty();
void TestCorrect();
void TestRandomAccess();
void TestSwap();
void TestPushBack();
void TestPopBack();

void TestAdding();
void TestUnarySign();
void TestAddNum();
void TestAddMatrix();

void TestMultiplication(const float error_rate);
void TestMultNum(const float error_rate);
void TestMultMatrix();

void TestNormalize(const float error_rate);

void TestTransp();

void TestPrint();

void TestParceCSRFormat();