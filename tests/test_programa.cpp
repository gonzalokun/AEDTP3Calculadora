#include "gtest/gtest.h"
#include <iostream>
#include "../src/Programa.h"

using namespace std;
typedef string rutina;

TEST(test_programa, testProgramaVacio){
    Programa p;
    EXPECT_EQ(p.getRutinas().size(),0);
    rutina r1 = "Rutina1";
    Instruccion i1;
    Instruccion i2;
    p.nuevaRutina(r1);
    p.agregarInstruccion(r1,i1);
    EXPECT_EQ(p.getRutinas().size(),1);
    EXPECT_EQ(p.longitud(r1),1);
    p.agregarInstruccion(r1,i2);
    EXPECT_EQ(p.longitud(r1),2);

}

TEST(test_programa, programaRaro) {
    Programa p;
    Instruccion i1;
    i1.push(5);
    ASSERT_EQ(p.getRutinas().size(),0);
    p.nuevaRutina("A");
    EXPECT_EQ(p.longitud("A"),0);
    p.agregarInstruccion("B",i1);//agrego rutina que no existe, internamente la crea
    i1.push(2);
    EXPECT_EQ(p.longitud("B"),1);
    p.agregarInstruccion("B",i1);
    EXPECT_EQ(p.getRutinas().size(),2);
    i1.add();
    p.agregarInstruccion("B",i1);
    EXPECT_EQ(p.getRutinas().size(),2);
    EXPECT_EQ(p.longitud("B"),3);
}

TEST(test_programa, programaRaro2) {
    Programa p;
    Instruccion i;
    i.push(4);
    i.write("x");
    i.push(10);
    p.nuevaRutina("A");
    p.agregarInstruccion("A",i);
    //La instruccion que vale es la ultima;
    EXPECT_EQ(p.instruccion("A", p.longitud("B")-1).getOp(),oPush);
    EXPECT_EQ(p.instruccion("A", p.longitud("B")-1).constanteNumerica(),10);

}

TEST(test_programa, testPrograma) {
    Programa p;
    rutina r1 = "rut1", r2="rut2", r3="rut3";
    Instruccion i1,i2,i3,i4,i5,i6;
    i1.push(3);
    i2.push(10);
    i3.sub();
    i4.sub();
    i5.read("var1");
    i6.add();
    p.nuevaRutina(r1);
    EXPECT_EQ(p.getRutinas().size(),1);
    p.nuevaRutina(r2);
    p.nuevaRutina(r3);
    EXPECT_EQ(p.getRutinas().size(),3);
    EXPECT_EQ(p.longitud(r1),0);
    p.agregarInstruccion(r1,i1);
    p.agregarInstruccion(r1,i1);
    p.agregarInstruccion(r1,i2);
    p.agregarInstruccion(r2,i5);
    EXPECT_EQ(p.longitud(r1),3);
    EXPECT_EQ(p.longitud(r2),1);
    EXPECT_EQ(p.longitud(r3),0);
    EXPECT_EQ(p.instruccion(r1,0).nombreRutina(), r1);
    EXPECT_EQ(p.instruccion(r1,1).nombreRutina(), r1);
    EXPECT_EQ(p.instruccion(r1,2).nombreRutina(), r1);
    EXPECT_EQ(p.instruccion(r2,0).nombreVariable(),"var1");
    EXPECT_EQ(p.instruccion(r1,0).getOp(),oPush);
    EXPECT_EQ(p.instruccion(r1,1).getOp(),oPush);
    EXPECT_EQ(p.instruccion(r1,2).getOp(),oPush);
    EXPECT_EQ(p.instruccion(r2,0).getOp(),oRead);
}
