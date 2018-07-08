#include "gtest/gtest.h"

#include "../src/Driver.h"

TEST(test_driver, programa_vacio) {
	Driver d;
	d.comenzarEjecucion("uzvpmxxq", 10);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, push) {
	Driver d;
	d.begin("tpo");
	d.push(6073366);
	d.end("tpo");
	d.comenzarEjecucion("tpo", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 6073366);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, push2) {
	Driver d;
	d.begin("dekuqs");
	d.push(79407791);
	d.push(97539359);
	d.end("dekuqs");
	d.comenzarEjecucion("dekuqs", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 79407791);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 2);
	ASSERT_EQ(d.topePila(), 97539359);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, add0) {
	Driver d;
	d.begin("main");
	d.add();
	d.end("main");
	d.comenzarEjecucion("main", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, add1) {
	Driver d;
	d.begin("jquias");
	d.push(9169741);
	d.add();
	d.end("jquias");
	d.comenzarEjecucion("jquias", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 9169741);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 2);
	ASSERT_EQ(d.topePila(), 9169741);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, add2) {
	Driver d;
	d.begin("czuzkoc");
	d.push(6716144);
	d.push(2082485);
	d.add();
	d.end("czuzkoc");
	d.comenzarEjecucion("czuzkoc", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 6716144);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 2);
	ASSERT_EQ(d.topePila(), 2082485);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 3);
	ASSERT_EQ(d.topePila(), 8798629);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, sub0) {
	Driver d;
	d.begin("sosst");
	d.sub();
	d.end("sosst");
	d.comenzarEjecucion("sosst", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, sub1) {
	Driver d;
	d.begin("uoxnhs");
	d.push(52507392);
	d.sub();
	d.end("uoxnhs");
	d.comenzarEjecucion("uoxnhs", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 52507392);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 2);
	ASSERT_EQ(d.topePila(), -52507392);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, sub2) {
	Driver d;
	d.begin("vbhyfkbl");
	d.push(84912482);
	d.push(54821519);
	d.sub();
	d.end("vbhyfkbl");
	d.comenzarEjecucion("vbhyfkbl", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 84912482);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 2);
	ASSERT_EQ(d.topePila(), 54821519);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 3);
	ASSERT_EQ(d.topePila(), 30090963);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, mul0) {
	Driver d;
	d.begin("atb");
	d.mul();
	d.end("atb");
	d.comenzarEjecucion("atb", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, mul1) {
	Driver d;
	d.begin("yyoo");
	d.push(7506);
	d.mul();
	d.end("yyoo");
	d.comenzarEjecucion("yyoo", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 7506);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 2);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, mul2) {
	Driver d;
	d.begin("rnpwqck");
	d.push(4105);
	d.push(3854);
	d.mul();
	d.end("rnpwqck");
	d.comenzarEjecucion("rnpwqck", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 4105);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 2);
	ASSERT_EQ(d.topePila(), 3854);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 3);
	ASSERT_EQ(d.topePila(), 15820670);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, read_variable_indefinida) {
	Driver d;
	d.begin("e");
	d.push(1);
	d.read("foo");
	d.add();
	d.end("e");
	d.comenzarEjecucion("e", 1);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 1);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 2);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 3);
	ASSERT_EQ(d.topePila(), 1);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, read) {
	for (int tam_ventana = 1; tam_ventana < 10; tam_ventana++) {
		Driver d;
		d.begin("avwsno");
		d.read("foo");
		d.read("foo");
		d.read("foo");
		d.read("foo");
		d.end("avwsno");
		d.comenzarEjecucion("avwsno", tam_ventana);

		ASSERT_EQ(d.instanteActual(), 0);
		ASSERT_FALSE(d.ejecucionFinalizada());

		ASSERT_EQ(d.valorHistoricoVariable("foo", 0), 0);

		d.ejecutarInstruccionActual();
		ASSERT_EQ(d.valorVariable("foo"), 0);
		ASSERT_EQ(d.instanteActual(), 1);
		ASSERT_EQ(d.topePila(), 0);
		ASSERT_FALSE(d.ejecucionFinalizada());

		d.asignarVariable("foo", 94984087);

		ASSERT_EQ(d.valorHistoricoVariable("foo", 0), 0);
		ASSERT_EQ(d.valorHistoricoVariable("foo", 1), 94984087);

		d.ejecutarInstruccionActual();
		ASSERT_EQ(d.valorVariable("foo"), 94984087);
		ASSERT_EQ(d.instanteActual(), 2);
		ASSERT_EQ(d.topePila(), 94984087);
		ASSERT_FALSE(d.ejecucionFinalizada());

		ASSERT_EQ(d.valorHistoricoVariable("foo", 0), 0);
		ASSERT_EQ(d.valorHistoricoVariable("foo", 1), 94984087);
		ASSERT_EQ(d.valorHistoricoVariable("foo", 2), 94984087);

		d.ejecutarInstruccionActual();
		ASSERT_EQ(d.valorVariable("foo"), 94984087);
		ASSERT_EQ(d.instanteActual(), 3);
		ASSERT_EQ(d.topePila(), 94984087);
		ASSERT_FALSE(d.ejecucionFinalizada());

		d.asignarVariable("foo", 21901650);

		ASSERT_EQ(d.valorHistoricoVariable("foo", 0), 0);
		ASSERT_EQ(d.valorHistoricoVariable("foo", 1), 94984087);
		ASSERT_EQ(d.valorHistoricoVariable("foo", 2), 94984087);
		ASSERT_EQ(d.valorHistoricoVariable("foo", 3), 21901650);

		d.ejecutarInstruccionActual();
		ASSERT_EQ(d.valorVariable("foo"), 21901650);
		ASSERT_EQ(d.instanteActual(), 4);
		ASSERT_EQ(d.topePila(), 21901650);
		ASSERT_TRUE(d.ejecucionFinalizada());

		ASSERT_EQ(d.valorHistoricoVariable("foo", 0), 0);
		ASSERT_EQ(d.valorHistoricoVariable("foo", 1), 94984087);
		ASSERT_EQ(d.valorHistoricoVariable("foo", 2), 94984087);
		ASSERT_EQ(d.valorHistoricoVariable("foo", 3), 21901650);
		ASSERT_EQ(d.valorHistoricoVariable("foo", 4), 21901650);
	}
}

TEST(test_driver, read_write) {
	for (int tam_ventana = 1; tam_ventana < 10; tam_ventana++) {
		Driver d;
		d.begin("klb");
		d.push(70435714);
		d.write("bar");
		d.read("bar");
		d.read("bar");
		d.end("klb");
		d.comenzarEjecucion("klb", tam_ventana);

		ASSERT_EQ(d.instanteActual(), 0);
		ASSERT_FALSE(d.ejecucionFinalizada());

		ASSERT_EQ(d.valorHistoricoVariable("bar", 0), 0);

		d.ejecutarInstruccionActual();
		ASSERT_EQ(d.valorVariable("bar"), 0);
		ASSERT_EQ(d.instanteActual(), 1);
		ASSERT_EQ(d.topePila(), 70435714);
		ASSERT_FALSE(d.ejecucionFinalizada());

		ASSERT_EQ(d.valorHistoricoVariable("bar", 0), 0);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 1), 0);

		d.ejecutarInstruccionActual();
		ASSERT_EQ(d.valorVariable("bar"), 70435714);
		ASSERT_EQ(d.instanteActual(), 2);
		ASSERT_EQ(d.topePila(), 0);
		ASSERT_FALSE(d.ejecucionFinalizada());

		ASSERT_EQ(d.valorHistoricoVariable("bar", 0), 0);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 1), 70435714);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 2), 70435714);

		d.ejecutarInstruccionActual();
		ASSERT_EQ(d.valorVariable("bar"), 70435714);
		ASSERT_EQ(d.instanteActual(), 3);
		ASSERT_EQ(d.topePila(), 70435714);
		ASSERT_FALSE(d.ejecucionFinalizada());

		ASSERT_EQ(d.valorHistoricoVariable("bar", 0), 0);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 1), 70435714);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 2), 70435714);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 3), 70435714);

		d.asignarVariable("bar", 60157375);

		ASSERT_EQ(d.valorHistoricoVariable("bar", 0), 0);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 1), 70435714);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 2), 70435714);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 3), 60157375);

		d.ejecutarInstruccionActual();
		ASSERT_EQ(d.valorVariable("bar"), 60157375);
		ASSERT_EQ(d.instanteActual(), 4);
		ASSERT_EQ(d.topePila(), 60157375);
		ASSERT_TRUE(d.ejecucionFinalizada());

		ASSERT_EQ(d.valorHistoricoVariable("bar", 0), 0);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 1), 70435714);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 2), 70435714);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 3), 60157375);
		ASSERT_EQ(d.valorHistoricoVariable("bar", 4), 60157375);
	}
}

TEST(test_driver, jump_rutina_inexistente) {
	Driver d;
	d.begin("mjixfob");
	d.jump("egnsgs");
	d.end("mjixfob");
	d.comenzarEjecucion("mjixfob", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());
	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, jump_rutina_existente) {
	Driver d;
	d.begin("a");
	d.jump("abc");
	d.end("a");

	d.begin("ab");
	d.push(37764564);
	d.add();
	d.end("ab");

	d.begin("abc");
	d.push(84935724);
	d.jump("ab");
	d.end("abc");

	d.comenzarEjecucion("a", 1024);

	ASSERT_EQ(d.instanteActual(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 1);
	ASSERT_EQ(d.topePila(), 0);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 2);
	ASSERT_EQ(d.topePila(), 84935724);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 3);
	ASSERT_EQ(d.topePila(), 84935724);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 4);
	ASSERT_EQ(d.topePila(), 37764564);
	ASSERT_FALSE(d.ejecucionFinalizada());

	d.ejecutarInstruccionActual();
	ASSERT_EQ(d.instanteActual(), 5);
	ASSERT_EQ(d.topePila(), 122700288);
	ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_driver, loop_infinito) {
	Driver d;
	d.begin("a");
	d.jump("a");
	d.end("a");
	d.comenzarEjecucion("a", 1024);

	for (int i = 0; i < 1000; i++) {
		d.ejecutarInstruccionActual();
		ASSERT_FALSE(d.ejecucionFinalizada());
	}
}

// Devuelve un vector con todas las cadenas de longitud n
// formadas con las letras del alfabeto.
vector<string> combinaciones_eq(vector<string> alfabeto, int n) {
	vector<string> v;
	if (n == 0) {
		v.push_back("");
		return v;
	} else {
		for (auto s : combinaciones_eq(alfabeto, n - 1)) {
			for (auto x : alfabeto) {
				v.push_back(x + s);
			}
		}
		return v;
	}
}

// Devuelve un vector con todas las cadenas de longitud entre 1 y n
// formadas con las letras del alfabeto.
vector<string> combinaciones_le(vector<string> alfabeto, int n) {
	vector<string> v;
	for (int i = 1; i <= n; i++) {
		for (auto s : combinaciones_eq(alfabeto, i)) {
			v.push_back(s);
		}
	}
	return v;
}

// Usa la calculadora como un diccionario.
TEST(test_driver, stress_diccionario) {
	int max_tiempo = 10;
	vector<string> alfabeto = {"a", "b", "c"};
	vector<string> nombres_variables = combinaciones_le(alfabeto, 4);
	for (int tam_ventana = 1; tam_ventana <= max_tiempo; tam_ventana++) {
		Driver d;
		d.begin("main");
		for (int t = 0; t < max_tiempo; t++) {
			d.push(t);
		}
		d.end("main");
		d.comenzarEjecucion("main", tam_ventana);

		for (int t = 0; t < max_tiempo; t++) {
			int valor = 1000 * t;
			for (auto v : nombres_variables) {
				d.asignarVariable(v, valor);
				valor++;
			}
			d.ejecutarInstruccionActual();
		}

		for (int t = 0; t < max_tiempo; t++) {
			int valorEsperado = 1000 * t;
			for (auto v : nombres_variables) {
				ASSERT_EQ(
					d.valorHistoricoVariable(v, t),
					valorEsperado
				);
				valorEsperado++;
			}
		}
	}
}

// Escritura y lectura de variables.
TEST(test_driver, stress_read_write) {
	vector<string> alfabeto = {"0", "1"};
	vector<string> v = combinaciones_le(alfabeto, 8);

	Driver d;
	d.begin("main");
	for (int i = 1; i < v.size(); i++) {
		d.read(v[i - 1]);
		d.push(i);
		d.add();
		d.write(v[i]);
	}
	d.end("main");

	d.comenzarEjecucion("main", 101);
	while (!d.ejecucionFinalizada()) {
		d.ejecutarInstruccionActual();
	}

	for (int i = 0; i < v.size(); i++) {
		ASSERT_EQ(d.valorVariable(v[i]), i * (i + 1) / 2);
	}

}

// Stress de llamados a rutinas.
TEST(test_driver, stress_jump) {
	vector<string> alfabeto = {"0", "1"};
	vector<string> r = combinaciones_le(alfabeto, 8);

	Driver d;
	d.begin("main");
	d.jump(r[0]);
	d.end("main");
	for (int i = 0; i < r.size(); i++) {
		d.begin(r[i]);
		d.read("x");
		d.push(1);
		d.add();
		d.write("x");
		if (i != r.size() - 1) {
			d.jump(r[i + 1]);
		}
		d.end(r[i]);
	}

	d.comenzarEjecucion("main", 101);
	while (!d.ejecucionFinalizada()) {
		d.ejecutarInstruccionActual();
	}

	for (int i = 0; i < r.size(); i++) {
		ASSERT_EQ(d.valorHistoricoVariable("x", 5 * i + 1), i);
	}

}

int factorial(int n) {
	int y = 1;
	for (int i = 1; i <= n; i++) {
		y = y * i;
	}
	return y;
}

TEST(test_driver, programa_factorial) {
	for (int a = 0; a < 10; a++) {
		Driver d;
		d.begin("fact");
		d.push(1);
		d.write("y");
		d.jump("loop");
		d.end("fact");

		d.begin("loop");
		d.read("x");
		d.jumpz("end");
		d.read("x");
		d.read("y");
		d.mul();
		d.write("y");
		d.read("x");
		d.push(1);
		d.sub();
		d.write("x");
		d.jump("loop");
		d.end("loop");

		d.comenzarEjecucion("fact", 10);
		d.asignarVariable("x", a);
		while (!d.ejecucionFinalizada()) {
			d.ejecutarInstruccionActual();
		}
		ASSERT_EQ(d.valorVariable("y"), factorial(a));
	}
}

