#include "gtest/gtest.h"
#include "../src/Driver.h"
#include <iostream>
using namespace std;

TEST(test_calculadora, variable_no_existe){
    Driver d;
    d.begin("asd");
    d.end("asd");
    d.comenzarEjecucion("asd",99);
    ASSERT_EQ(d.instanteActual(),0);
    ASSERT_EQ(d.valorVariable("a"), 0);

}
TEST(test_calculadora, rutina_vacia) {
    Driver d;
    d.begin("rut");
    d.end("rut");
    d.comenzarEjecucion("rut",99);
    d.ejecutarInstruccionActual();
    ASSERT_TRUE(d.ejecucionFinalizada());
}

TEST(test_calculadora, saltoRutinas){
    Programa p;
    Instruccion i1,i2,i3,i4,i5,i6, i7, i8, i9;
    i1.push(3);
    i2.push(10);
    i3.jump("c");
    i4.sub();
    i5.read("var1");
    i6.add();
    i7.push(13);
    i8.sub();
    i9.jumpz("a");

    p.nuevaRutina("a");
    p.nuevaRutina("b");
    p.nuevaRutina("c");
    p.agregarInstruccion("a", i1);
    p.agregarInstruccion("a", i2);
    p.agregarInstruccion("a", i3);
    p.agregarInstruccion("b", i4);
    p.agregarInstruccion("b", i5);
    p.agregarInstruccion("c", i6);

    Calculadora c;
    c.nuevaCalculadora(p,"a", 5);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.getInstanteActual(), 1);
    EXPECT_EQ(c.getIndiceInstruccionActual(), 0);
    EXPECT_EQ(c.primeroPila(),3);

    c.ejecutarUnPaso();

    EXPECT_EQ(c.getInstanteActual(), 2);
    EXPECT_EQ(c.getIndiceInstruccionActual(), 1);
    EXPECT_EQ(c.primeroPila(), 10);

    c.ejecutarUnPaso();
    EXPECT_EQ(c.getRutinaActual(),"c");
    EXPECT_EQ(c.getIndiceInstruccionActual(), 0);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.primeroPila(), 13);
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();

    EXPECT_EQ(c.getRutinaActual(),"a");

}

TEST(test_calculadora, valorVariableActual){
    Instruccion i1,i2,i3,i4,i5,i6;
    i1.write("x");
    i2.push(1);
    i3.write("y");
    i4.push(9);
    i5.write("x");
    i6.jumpz("b");

    Programa p;
    p.nuevaRutina("a");
    p.agregarInstruccion("a", i1);
    p.agregarInstruccion("a", i2);
    p.agregarInstruccion("a", i3);
    p.agregarInstruccion("a", i4);
    p.agregarInstruccion("a", i5);
    p.agregarInstruccion("a", i6);
    Calculadora c;
    c.nuevaCalculadora(p,"a",20);

    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorActualVariable("x"), 0);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.primeroPila(), 1);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorActualVariable("y"), 1);
    EXPECT_EQ(c.valorActualVariable("xxx"), 0);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.primeroPila(), 9);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorActualVariable("x"), 9);
    c.ejecutarUnPaso();
    EXPECT_FALSE(c.getEjecutando());




}

TEST(test_calculadora, valorVariableInstanteYinstActual){
    Instruccion i1,i2,i3,i4,i5,i6, i7;
    i1.write("x");
    i2.push(100);
    i3.write("x");
    i4.push(10);
    i5.write("x");
    i6.push(1);
    i7.write("x");

    Programa p;
    p.nuevaRutina("a");
    p.agregarInstruccion("a", i1);
    p.agregarInstruccion("a", i2);
    p.agregarInstruccion("a", i3);
    p.agregarInstruccion("a", i4);
    p.agregarInstruccion("a", i5);
    p.agregarInstruccion("a", i6);
    p.agregarInstruccion("a", i7);
    Calculadora c;
    c.nuevaCalculadora(p,"a",20);

    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorActualVariable("x"), 0);

    c.ejecutarUnPaso();
    c.ejecutarUnPaso();

    EXPECT_EQ(c.valorActualVariable("x"), 100);
    EXPECT_EQ(c.valorEnInstante("x", 0), 0); // Ver si empieza en 1 o 0 el instante.
    c.ejecutarUnPaso();

    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorActualVariable("x"), 10);
    EXPECT_EQ(c.getInstanteActual(), 5);
    EXPECT_EQ(c.valorEnInstante("x", 5), 100);

    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorActualVariable("x"), 1);
    EXPECT_EQ(c.getInstanteActual(), 7);
    EXPECT_EQ(c.valorEnInstante("x", 2), 10);
    c.ejecutarUnPaso();
    EXPECT_FALSE(c.getEjecutando());

}

TEST(test_calculadora, asignarVariable){
    Instruccion i1,i2,i3,i4,i5,i6, i7;
    i1.write("x");
    i2.push(100);
    i3.write("x");
    i4.push(10);
    i5.write("x");
    i6.read("x");
    i7.jump("mmm");

    Programa p;
    p.nuevaRutina("a");
    p.agregarInstruccion("a", i1);
    p.agregarInstruccion("a", i2);
    p.agregarInstruccion("a", i3);
    p.agregarInstruccion("a", i4);
    p.agregarInstruccion("a", i5);
    p.agregarInstruccion("a", i6);
    p.agregarInstruccion("a", i7);
    Calculadora c;
    c.nuevaCalculadora(p,"a",20);

    c.ejecutarUnPaso();
    c.asignarVariable("x", 5);
    EXPECT_EQ(c.valorEnInstante("x", 0), 5);
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorEnInstante("x", 1), 100);
    c.asignarVariable("x", 50);
    EXPECT_EQ(c.valorEnInstante("x", 1), 50);
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorEnInstante("x", 2), 10);
    c.asignarVariable("x", 2);
    EXPECT_EQ(c.valorActualVariable("x"), c.getInstanteActual());
    c.ejecutarUnPaso();
    EXPECT_EQ(c.primeroPila(), 2);
    c.ejecutarUnPaso();
    EXPECT_FALSE(c.getEjecutando());
}

TEST(test_calculadora, indiceYrutinaEnSaltos){
    Instruccion i1,i2,i3,i4,i5,i6, i7, i8, i9;

    i1.push(1);
    i2.jumpz("b");
    i3.jump("c");
    i4.write("x");
    i5.jumpz("a");
    i6.jump("b");

    Programa p;
    p.nuevaRutina("a");
    p.nuevaRutina("b");
    p.nuevaRutina("c");

    p.agregarInstruccion("a", i1);
    p.agregarInstruccion("a", i2);
    p.agregarInstruccion("a", i3);
    p.agregarInstruccion("c", i1);
    p.agregarInstruccion("c", i1);
    p.agregarInstruccion("c", i1);
    p.agregarInstruccion("c", i6);
    p.agregarInstruccion("b", i5);
    Calculadora c;
    c.nuevaCalculadora(p,"a",20);

    c.ejecutarUnPaso();
    c.ejecutarUnPaso();

    EXPECT_EQ(c.getRutinaActual(),"a");
    EXPECT_EQ(c.getIndiceInstruccionActual(), 2);


    c.ejecutarUnPaso();
    EXPECT_EQ(c.getRutinaActual(),"c");
    EXPECT_EQ(c.getIndiceInstruccionActual(), 0);

    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    EXPECT_EQ(c.getIndiceInstruccionActual(), 3);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.getRutinaActual(),"b");
    EXPECT_EQ(c.getIndiceInstruccionActual(), 0);
    c.ejecutarUnPaso();
    EXPECT_FALSE(c.getEjecutando());

}
