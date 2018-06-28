#include "gtest/gtest.h"

#include "../src/Ventana.h"

TEST(test_ventana, vacia) {
	Ventana<int> v(100);
	ASSERT_EQ(v.capacidad(), 100);
	ASSERT_EQ(v.tam(), 0);
}

TEST(test_ventana, registrar) {
	Ventana<int> v(5);

	v.registrar(1);
	ASSERT_EQ(v.tam(), 1);
	ASSERT_EQ(v[0], 1);

	v.registrar(2);
	ASSERT_EQ(v.tam(), 2);
	ASSERT_EQ(v[0], 1);
	ASSERT_EQ(v[1], 2);

	v.registrar(3);
	ASSERT_EQ(v.tam(), 3);
	ASSERT_EQ(v[0], 1);
	ASSERT_EQ(v[1], 2);
	ASSERT_EQ(v[2], 3);

	v.registrar(4);
	ASSERT_EQ(v.tam(), 4);
	ASSERT_EQ(v[0], 1);
	ASSERT_EQ(v[1], 2);
	ASSERT_EQ(v[2], 3);
	ASSERT_EQ(v[3], 4);

	v.registrar(5);
	ASSERT_EQ(v.tam(), 5);
	ASSERT_EQ(v[0], 1);
	ASSERT_EQ(v[1], 2);
	ASSERT_EQ(v[2], 3);
	ASSERT_EQ(v[3], 4);
	ASSERT_EQ(v[4], 5);

	v.registrar(6);
	ASSERT_EQ(v.tam(), 5);
	ASSERT_EQ(v[0], 2);
	ASSERT_EQ(v[1], 3);
	ASSERT_EQ(v[2], 4);
	ASSERT_EQ(v[3], 5);
	ASSERT_EQ(v[4], 6);

	v.registrar(7);
	ASSERT_EQ(v.tam(), 5);
	ASSERT_EQ(v[0], 3);
	ASSERT_EQ(v[1], 4);
	ASSERT_EQ(v[2], 5);
	ASSERT_EQ(v[3], 6);
	ASSERT_EQ(v[4], 7);

	v.registrar(8);
	ASSERT_EQ(v.tam(), 5);
	ASSERT_EQ(v[0], 4);
	ASSERT_EQ(v[1], 5);
	ASSERT_EQ(v[2], 6);
	ASSERT_EQ(v[3], 7);
	ASSERT_EQ(v[4], 8);

	v.registrar(9);
	ASSERT_EQ(v.tam(), 5);
	ASSERT_EQ(v[0], 5);
	ASSERT_EQ(v[1], 6);
	ASSERT_EQ(v[2], 7);
	ASSERT_EQ(v[3], 8);
	ASSERT_EQ(v[4], 9);

	v.registrar(10);
	ASSERT_EQ(v.tam(), 5);
	ASSERT_EQ(v[0], 6);
	ASSERT_EQ(v[1], 7);
	ASSERT_EQ(v[2], 8);
	ASSERT_EQ(v[3], 9);
	ASSERT_EQ(v[4], 10);

	v.registrar(11);
	ASSERT_EQ(v.tam(), 5);
	ASSERT_EQ(v[0], 7);
	ASSERT_EQ(v[1], 8);
	ASSERT_EQ(v[2], 9);
	ASSERT_EQ(v[3], 10);
	ASSERT_EQ(v[4], 11);

	v.registrar(12);
	ASSERT_EQ(v.tam(), 5);
	ASSERT_EQ(v[0], 8);
	ASSERT_EQ(v[1], 9);
	ASSERT_EQ(v[2], 10);
	ASSERT_EQ(v[3], 11);
	ASSERT_EQ(v[4], 12);
}


TEST(test_ventana, copiar) {
	Ventana<int> v(5);

	Ventana<int> w0(v);
	ASSERT_EQ(w0.tam(), 0);

	v.registrar(1);
	Ventana<int> w1(v);
	ASSERT_EQ(w1.tam(), 1);
	ASSERT_EQ(w1[0], 1);

	v.registrar(2);
	Ventana<int> w2(v);
	ASSERT_EQ(w2.tam(), 2);
	ASSERT_EQ(w2[0], 1);
	ASSERT_EQ(w2[1], 2);

	v.registrar(3);
	v.registrar(4);
	Ventana<int> w4(v);
	ASSERT_EQ(w4.tam(), 4);
	ASSERT_EQ(w4[0], 1);
	ASSERT_EQ(w4[1], 2);
	ASSERT_EQ(w4[2], 3);
	ASSERT_EQ(w4[3], 4);

	v.registrar(5);
	Ventana<int> w5(v);
	ASSERT_EQ(w5.tam(), 5);
	ASSERT_EQ(w5[0], 1);
	ASSERT_EQ(w5[1], 2);
	ASSERT_EQ(w5[2], 3);
	ASSERT_EQ(w5[3], 4);
	ASSERT_EQ(w5[4], 5);

	v.registrar(6);
	Ventana<int> w6(v);
	ASSERT_EQ(w6.tam(), 5);
	ASSERT_EQ(w6[0], 2);
	ASSERT_EQ(w6[1], 3);
	ASSERT_EQ(w6[2], 4);
	ASSERT_EQ(w6[3], 5);
	ASSERT_EQ(w6[4], 6);

	v.registrar(7);
	Ventana<int> w7(v);
	ASSERT_EQ(w7.tam(), 5);
	ASSERT_EQ(w7[0], 3);
	ASSERT_EQ(w7[1], 4);
	ASSERT_EQ(w7[2], 5);
	ASSERT_EQ(w7[3], 6);
	ASSERT_EQ(w7[4], 7);

	v.registrar(8);
	v.registrar(9);
	v.registrar(10);
	v.registrar(11);
	v.registrar(12);
	Ventana<int> w12(v);
	ASSERT_EQ(w12.tam(), 5);
	ASSERT_EQ(w12[0], 8);
	ASSERT_EQ(w12[1], 9);
	ASSERT_EQ(w12[2], 10);
	ASSERT_EQ(w12[3], 11);
	ASSERT_EQ(w12[4], 12);
}


