#include <gtest/gtest.h>
#include "../src/trie.h"
#include <list>

TEST(trie, probandoBorrar){
    trie<int> prueba;
    prueba["hola"] = 1;

}


TEST(trie_test, vacio) {
    trie<int> vacio;
    EXPECT_TRUE(vacio.empty());
    EXPECT_EQ(vacio.count("hola"), 0);
}

TEST(trie_test, asignar) {
    trie<int> singleton;
    singleton["hola"] = 1;
    EXPECT_EQ(singleton["hola"], 1);
    EXPECT_EQ(singleton.size(), 1);
}

TEST(trie_test, obtener) {
    trie<int> sin_prefijos;
    trie<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;


    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    EXPECT_EQ(sin_prefijos["hola"], 1);
    EXPECT_EQ(sin_prefijos["chau"], 2);
    EXPECT_EQ(sin_prefijos["adios"], 3);

    EXPECT_EQ(con_prefijos["c"], 1);
    EXPECT_EQ(con_prefijos["casa"], 2);
    EXPECT_EQ(con_prefijos["casona"], 3);
}

TEST(trie_test, redefinir) {
    trie<int> con_prefijos;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    con_prefijos["c"] =  2;
    EXPECT_EQ(con_prefijos["c"], 2);
    con_prefijos["c"] =  3;
    EXPECT_EQ(con_prefijos["c"], 3);
}


TEST(trie_test, count) {
    trie<int> vacio;
    trie<int> sin_prefijos;
    trie<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

	EXPECT_FALSE(vacio.count("a") == 1);
	EXPECT_FALSE(vacio.count("aaaa") == 1);
	EXPECT_FALSE(vacio.count("adios") == 1);

	EXPECT_TRUE(sin_prefijos.count("hola") == 1);
	EXPECT_TRUE(sin_prefijos.count("chau") == 1);
	EXPECT_TRUE(sin_prefijos.count("adios") == 1);

	EXPECT_FALSE(sin_prefijos.count("h") == 1);
	EXPECT_FALSE(sin_prefijos.count("ho") == 1);
	EXPECT_FALSE(sin_prefijos.count("hol") == 1);

	EXPECT_TRUE(con_prefijos.count("c") == 1);
	EXPECT_TRUE(con_prefijos.count("casa") == 1);
	EXPECT_TRUE(con_prefijos.count("casona") == 1);
	EXPECT_FALSE(con_prefijos.count("ca") == 1);
	EXPECT_FALSE(con_prefijos.count("cas") == 1);
	EXPECT_FALSE(con_prefijos.count("caso") == 1);
}


TEST(trie_test, copiar) {
    trie<int> sin_prefijos;
    trie<int> con_prefijos;
    con_prefijos["holas"] = 2;
    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] = 3;
    EXPECT_TRUE(sin_prefijos.count("hola")==1);
    cout << "agrego"<<endl;
    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;
    trie<int> copia(sin_prefijos);
    EXPECT_TRUE(copia.count("hola")==1);
    EXPECT_EQ(copia["hola"], 1);
	EXPECT_TRUE(copia.count("hola") == 1);
    EXPECT_TRUE(copia["hola"]==1);
    EXPECT_EQ(copia.size(),3);
	EXPECT_TRUE(copia.count("chau") == 1);
	EXPECT_TRUE(copia.count("adios") == 1);

	EXPECT_FALSE(copia.count("h") == 1);
	EXPECT_FALSE(copia.count("ho") == 1);
	EXPECT_FALSE(copia.count("hol") == 1);

	EXPECT_EQ(sin_prefijos["hola"], copia["hola"]);
	EXPECT_EQ(sin_prefijos["chau"], copia["chau"]);
	EXPECT_EQ(sin_prefijos["adios"], copia["adios"]);

	trie<int> copia2(con_prefijos);

	EXPECT_TRUE(copia2.count("c") == 1);
	EXPECT_TRUE(copia2.count("casa") == 1);
	EXPECT_TRUE(copia2.count("casona") == 1);
	EXPECT_FALSE(copia2.count("ca") == 1);
	EXPECT_FALSE(copia2.count("cas") == 1);
	EXPECT_FALSE(copia2.count("caso") == 1);

	EXPECT_EQ(copia2["c"], 1);
	EXPECT_EQ(copia2["casa"], 2);
	EXPECT_EQ(copia2["casona"], 3);
}

TEST(trie_test, no_aliasing) {
    trie<int> singleton;
    singleton["hola"] = 1;

	trie<int> copia(singleton);
	copia["hare"] =  2;
	ASSERT_FALSE(singleton.count("hare") == 1);
}

TEST(trie_test, TrieDeTries) {
    trie<int> vacio;
    trie<int> singleton;
    trie<int> sin_prefijos;
    trie<int> con_prefijos;
    trie<trie<int>> dicc_dicc;

    singleton["hola"] = 1;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    dicc_dicc["vacio"] =  vacio;
    dicc_dicc["singleton"] =  singleton;
    dicc_dicc["sinprefijos"] =  sin_prefijos;
    dicc_dicc["conprefijos"] =  con_prefijos;

	EXPECT_FALSE(dicc_dicc["vacio"].count("hola") == 1);
    EXPECT_EQ(dicc_dicc.size(),4);
	EXPECT_EQ(dicc_dicc["singleton"]["hola"], 1);

	EXPECT_EQ(dicc_dicc["sinprefijos"]["hola"], 1);
	EXPECT_EQ(dicc_dicc["sinprefijos"]["chau"], 2);
	EXPECT_EQ(dicc_dicc["sinprefijos"]["adios"], 3);

	EXPECT_EQ(dicc_dicc["conprefijos"]["c"], 1);
	EXPECT_EQ(dicc_dicc["conprefijos"]["casa"], 2);
	EXPECT_EQ(dicc_dicc["conprefijos"]["casona"], 3);

}


TEST(trie_test, eraseUnicaClave) {
    trie<int> singleton;
    singleton["hola"] = 1;

    EXPECT_TRUE(singleton.count("hola") == 1);
    EXPECT_EQ(singleton.size(), 1);
    singleton.erase("hola");

    EXPECT_FALSE(singleton.count("hola") == 1);
    EXPECT_EQ(singleton.size(), 0);
}


TEST(trie_test, erase) {
    trie<int> sin_prefijos;
    trie<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    con_prefijos.erase("c");
    EXPECT_TRUE(con_prefijos["casa"]==2);
    EXPECT_FALSE(con_prefijos.count("c") == 1);
    EXPECT_TRUE(con_prefijos.count("casa") == 1);
    EXPECT_TRUE(con_prefijos.count("casona") == 1);

    con_prefijos.erase("casona");
    EXPECT_FALSE(con_prefijos.count("casona") == 1);

    EXPECT_TRUE(con_prefijos.count("casa") == 1);

    con_prefijos.erase("casa");
    EXPECT_FALSE(con_prefijos.count("casa") == 1);

    sin_prefijos.erase("hola");
    EXPECT_FALSE(sin_prefijos.count("hola") == 1);

    sin_prefijos.erase("chau");
    EXPECT_FALSE(sin_prefijos.count("chau") == 1);

    sin_prefijos.erase("adios");
    EXPECT_FALSE(sin_prefijos.count("adios") == 1);
}
TEST(trie_test, nuevoTest) {
    trie<int> dic;
    dic["HOLAAA"] = 2;
    dic["Holi"] = 1;
    EXPECT_EQ(dic.size(),2);
    EXPECT_EQ(dic["HOLAAA"],2);
    EXPECT_EQ(dic.count("holaaa"),0);
    EXPECT_EQ(dic.count("Holi"),1);

}

//TEST ADICIONALES, PARA LOS ITERADORES

TEST(trie_test, testAdicional_it){
    trie<int> t;
    t["cas"] = 25;
    trie<int>::ItDiccTrie it(t.nodoSignificado("cas"));
    EXPECT_EQ(it.claveActual(),"cas");
    EXPECT_EQ(*it,25);
    t["cas"] = 30;
    EXPECT_EQ(it.claveActual(),"cas");
    EXPECT_EQ(*it,30);
    t["cas"] = 302;
    EXPECT_EQ(*it,302);
    EXPECT_EQ(it.claveActual(),"cas");

}

TEST(trie_test, testAdicional_it2) {
    trie<list<int> > t;
    list<int> l1;
    l1.push_back(3);
    l1.push_back(32);
    t["l2"] = l1;
    list<int> l2;
    l2.push_back(120);
    l2.push_back(343);
    l2.push_back(232);
    l2.push_back(23);
    t["lu"] = l2;
    trie<list<int> >::ItDiccTrie it(t.nodoSignificado("lu"));
    list<int> aux;
    aux.push_back(120);
    aux.push_back(343);
    aux.push_back(232);
    aux.push_back(23);
    EXPECT_EQ(it.claveActual(),"lu");
    EXPECT_EQ(*it,aux);
}


TEST(trie_test, testAdicional_it3) {
    trie<tuple<int,list<int> > > t;
    list<int> l2;
    l2.push_back(120);
    l2.push_back(343);
    l2.push_back(232);
    l2.push_back(23);
    int n = 12;
    list<int> l1;
    l1.push_back(1);
    list<int> l4 = {4,7,2,5,9,6,3,1,66,3,7};
    int n2 = n+6;
    t["casa"] = make_tuple(n,l1);
    trie<tuple<int,list<int> > >::ItDiccTrie it(t.nodoSignificado("casa"));
    t["casita"] = make_tuple(n,l2);
    t["casito"] = make_tuple(n2,l4);
    EXPECT_EQ(*it, make_tuple(n,l1));
    EXPECT_EQ(it.claveActual(),"casa");
    trie<tuple<int,list<int> > >::ItDiccTrie it2(t.nodoSignificado("casito"));
    EXPECT_EQ(*it2, make_tuple(n2,l4));
    EXPECT_EQ(it2.claveActual(),"casito");

}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
