#include "gtest/gtest.h"
#include <iostream>
#include "../src/Instruccion.h"
using namespace std;


TEST(test_instruccion, instrConstSinParam) {
    Instruccion i;
    ASSERT_TRUE(i.getOp() == oNada);
    ASSERT_TRUE(i.nombreRutina() == "");
    i.setRutina("RutinaUno");
    ASSERT_FALSE(i.nombreRutina() == "");
    ASSERT_TRUE(i.nombreRutina() == "RutinaUno");
}

TEST(test_instruccion, instrCambiadas){
    Instruccion i("r");
    ASSERT_TRUE(i.nombreRutina()=="r");
    ASSERT_TRUE(i.constanteNumerica()==0);
    ASSERT_TRUE(i.nombreVariable() == "");
    i.sub();
    ASSERT_TRUE(i.nombreVariable() == "");
    ASSERT_TRUE(i.getOp()==oSub);
    i.add();
    ASSERT_TRUE(i.nombreVariable()=="");
    ASSERT_FALSE(i.getOp()==oSub);
    ASSERT_TRUE(i.getOp()==oAdd);
    ASSERT_FALSE(i.getOp()==oWrite);
    i.write("x");
    ASSERT_FALSE(i.getOp()==oSub);
    ASSERT_FALSE(i.getOp()==oAdd);
}
TEST(test_instruccion, compotamientosDiferentes){
    Instruccion i;
    ASSERT_TRUE(i.nombreRutina()=="");
    ASSERT_TRUE(i.constanteNumerica()==0);
    ASSERT_TRUE(i.nombreVariable() == "");
    ASSERT_FALSE(i.getOp()==oWrite);
    i.write("w");
    ASSERT_TRUE(i.getOp()==oWrite);
    i.read("w");
    ASSERT_FALSE(i.getOp()==oWrite);
    ASSERT_TRUE(i.getOp()==oRead);
    ASSERT_TRUE(i.nombreRutina()=="");
    ASSERT_TRUE(i.constanteNumerica()==0);
    ASSERT_TRUE(i.nombreVariable() == "w");
    ASSERT_TRUE(i.constanteNumerica()==0);
    i.push(2);
    ASSERT_TRUE(i.nombreVariable() == "");
    ASSERT_TRUE(i.getOp() == oPush);
    ASSERT_TRUE(i.nombreRutina() == "");
    i.setRutina("NuevaRutina");
    ASSERT_TRUE(i.constanteNumerica()==2);
    ASSERT_TRUE(i.nombreRutina() == "NuevaRutina");
}

TEST(test_instruccion, instrConstConParam) {
    Instruccion i("Rutina");
    ASSERT_FALSE(i.nombreRutina() == "");
    ASSERT_TRUE(i.getOp() == oNada);
    i.add();
    ASSERT_TRUE(i.getOp() == oAdd);
    ASSERT_FALSE(i.getOp() == oPush);
    ASSERT_FALSE(i.getOp() == oSub);
    ASSERT_FALSE(i.getOp() == oMul);
    ASSERT_FALSE(i.getOp() == oWrite);
    ASSERT_FALSE(i.getOp() == oRead);
    ASSERT_FALSE(i.getOp() == oJump);
    ASSERT_FALSE(i.getOp() == oJumpz);
    ASSERT_EQ(i.constanteNumerica(),0);
    ASSERT_TRUE(i.nombreVariable()=="");
}

TEST(test_instruccion,instrWriteRead) {
    Instruccion i("R");
    i.read("x");
    ASSERT_EQ(i.nombreVariable(),"x");
    ASSERT_EQ(i.getOp(), oRead);
    ASSERT_EQ(i.constanteNumerica(),0);
}

TEST(test_instruccion, instrPush) {
    Instruccion i("R");
    i.push(2);
    ASSERT_EQ(i.getOp(),oPush);
    ASSERT_EQ(i.nombreRutina(),"R");
    ASSERT_EQ(i.nombreVariable(),"");
    ASSERT_EQ(i.constanteNumerica(),2);
}
