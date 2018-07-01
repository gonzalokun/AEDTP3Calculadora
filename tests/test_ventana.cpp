/*#include "gtest/gtest.h"

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
}*/
